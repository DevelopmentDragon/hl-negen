/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
/*

===== weapons.cpp ========================================================

  functions governing the selection/use of weapons for players

*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "soundent.h"
#include "decals.h"
#include "gamerules.h"

extern CGraph	WorldGraph;

#define NOT_USED 255

DLL_GLOBAL	short	g_sModelIndexLaser;// holds the index for the laser beam
DLL_GLOBAL  const char *g_pModelNameLaser = "sprites/laserbeam.spr";
DLL_GLOBAL	short	g_sModelIndexLaserDot;// holds the index for the laser beam dot
DLL_GLOBAL	short	g_sModelIndexFireball;// holds the index for the fireball
DLL_GLOBAL	short	g_sModelIndexSmoke;// holds the index for the smoke cloud
DLL_GLOBAL	short	g_sModelIndexWExplosion;// holds the index for the underwater explosion
DLL_GLOBAL	short	g_sModelIndexBubbles;// holds the index for the bubbles model
DLL_GLOBAL	short	g_sModelIndexBloodDrop;// holds the sprite index for the initial blood
DLL_GLOBAL	short	g_sModelIndexBloodSpray;// holds the sprite index for splattered blood

ItemInfo CBasePlayerItem::ItemInfoArray[MAX_WEAPONS];
AmmoInfo CBasePlayerItem::AmmoInfoArray[MAX_AMMO_SLOTS];

extern int gmsgCurWeapon;

MULTIDAMAGE gMultiDamage;

#define TRACER_FREQ		4			// Tracers fire every fourth bullet


//=========================================================
// MaxAmmoCarry - pass in a name and this function will tell
// you the maximum amount of that type of ammunition that a 
// player can carry.
//=========================================================
int MaxAmmoCarry( int iszName )
{
	for ( int i = 0;  i < MAX_WEAPONS; i++ )
	{
		if ( CBasePlayerItem::ItemInfoArray[i].pszAmmo1 && !strcmp( STRING(iszName), CBasePlayerItem::ItemInfoArray[i].pszAmmo1 ) )
			return CBasePlayerItem::ItemInfoArray[i].iMaxAmmo1;
		if ( CBasePlayerItem::ItemInfoArray[i].pszAmmo2 && !strcmp( STRING(iszName), CBasePlayerItem::ItemInfoArray[i].pszAmmo2 ) )
			return CBasePlayerItem::ItemInfoArray[i].iMaxAmmo2;
	}

	ALERT( at_console, "MaxAmmoCarry() doesn't recognize '%s'!\n", STRING( iszName ) );
	return -1;
}

	
/*
==============================================================================

MULTI-DAMAGE

Collects multiple small damages into a single damage

==============================================================================
*/

//
// ClearMultiDamage - resets the global multi damage accumulator
//
void ClearMultiDamage(void)
{
	gMultiDamage.pEntity = NULL;
	gMultiDamage.amount	= 0;
	gMultiDamage.type = 0;
}


//
// ApplyMultiDamage - inflicts contents of global multi damage register on gMultiDamage.pEntity
//
// GLOBALS USED:
//		gMultiDamage

void ApplyMultiDamage(entvars_t *pevInflictor, entvars_t *pevAttacker )
{
	Vector		vecSpot1;//where blood comes from
	Vector		vecDir;//direction blood should go
	TraceResult	tr;
	
	if ( !gMultiDamage.pEntity )
		return;

	gMultiDamage.pEntity->TakeDamage(pevInflictor, pevAttacker, gMultiDamage.amount, gMultiDamage.type );
}


// GLOBALS USED:
//		gMultiDamage

void AddMultiDamage( entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int iDamageId)
{
	if ( !pEntity )
		return;
	
	gMultiDamage.type |= iDamageId;

	if ( pEntity != gMultiDamage.pEntity )
	{
		ApplyMultiDamage(pevInflictor,pevInflictor); // UNDONE: wrong attacker!
		gMultiDamage.pEntity	= pEntity;
		gMultiDamage.amount		= 0;
	}

	gMultiDamage.amount += flDamage;
}

/*
================
SpawnBlood
================
*/
void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage)
{
	UTIL_BloodDrips( vecSpot, g_vecAttackDir, bloodColor, (int)flDamage );
}


int DamageDecal( CBaseEntity *pEntity, int iDamageId )
{
	if ( !pEntity )
		return (DECAL_GUNSHOT1 + RANDOM_LONG(0,4));
	
	return pEntity->DamageDecal( iDamageId );
}

void DecalGunshot( TraceResult *pTrace, int iBulletType )
{
	// Is the entity valid
	if ( !UTIL_IsValidEntity( pTrace->pHit ) )
		return;

	if ( VARS(pTrace->pHit)->solid == SOLID_BSP || VARS(pTrace->pHit)->movetype == MOVETYPE_PUSHSTEP )
	{
		CBaseEntity *pEntity = NULL;
		// Decal the wall with a gunshot
		if ( !FNullEnt(pTrace->pHit) )
			pEntity = CBaseEntity::Instance(pTrace->pHit);

		if (IsBullet(iBulletType))
		{
			// smoke and decal
			UTIL_GunshotDecalTrace(pTrace, DamageDecal(pEntity, ID_DMG_GENERIC));
		}
		else
		{
			UTIL_DecalTrace( pTrace, DamageDecal( pEntity, ID_DMG_GENERIC ) );
		}
	}
}

//
// EjectBrass - tosses a brass shell from passed origin at passed velocity
//
void EjectBrass ( const Vector &vecOrigin, const Vector &vecVelocity, float rotation, int model, int soundtype )
{
	// FIX: when the player shoots, their gun isn't in the same position as it is on the model other players see.

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, vecOrigin );
		WRITE_BYTE( TE_MODEL);
		WRITE_COORD( vecOrigin.x);
		WRITE_COORD( vecOrigin.y);
		WRITE_COORD( vecOrigin.z);
		WRITE_COORD( vecVelocity.x);
		WRITE_COORD( vecVelocity.y);
		WRITE_COORD( vecVelocity.z);
		WRITE_ANGLE( rotation );
		WRITE_SHORT( model );
		WRITE_BYTE ( soundtype);
		WRITE_BYTE ( 25 );// 2.5 seconds
	MESSAGE_END();
}


#if 0
// UNDONE: This is no longer used?
void ExplodeModel( const Vector &vecOrigin, float speed, int model, int count )
{
	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, vecOrigin );
		WRITE_BYTE ( TE_EXPLODEMODEL );
		WRITE_COORD( vecOrigin.x );
		WRITE_COORD( vecOrigin.y );
		WRITE_COORD( vecOrigin.z );
		WRITE_COORD( speed );
		WRITE_SHORT( model );
		WRITE_SHORT( count );
		WRITE_BYTE ( 15 );// 1.5 seconds
	MESSAGE_END();
}
#endif

int giAmmoIndex = 0;

// Precaches the ammo and queues the ammo info for sending to clients
void AddAmmoNameToAmmoRegistry(const char* szAmmoname)
{
	// make sure it's not already in the registry
	for (int i = 0; i < MAX_AMMO_SLOTS; i++)
	{
		if (!CBasePlayerItem::AmmoInfoArray[i].pszName)
			continue;

		if (stricmp(CBasePlayerItem::AmmoInfoArray[i].pszName, szAmmoname) == 0)
			return; // ammo already in registry, just quit
	}

	ASSERT(giAmmoIndex < MAX_AMMO_SLOTS);
	if (giAmmoIndex >= MAX_AMMO_SLOTS)
		giAmmoIndex = 0;

	CBasePlayerItem::AmmoInfoArray[giAmmoIndex].pszName = szAmmoname;
	CBasePlayerItem::AmmoInfoArray[giAmmoIndex].iId = giAmmoIndex;   // yes, this info is redundant

	giAmmoIndex++;
	//ALERT(at_console, "%s is at index %d\n", szAmmoname, giAmmoIndex);
}

// We call this to precache all ammo types. This was made for the new HUD system
// ORDER MATTERS
void UTIL_PrecacheAllAmmo(void)
{
	//===========================
	// Melee weapons don't have ammo register
	// Question/ Fists
	AddAmmoNameToAmmoRegistry("social");
	//===========================

	//===========================
	// Glock
	AddAmmoNameToAmmoRegistry("9mm");

	// .357 Python
	AddAmmoNameToAmmoRegistry("357");

	// .38 Caliber
	AddAmmoNameToAmmoRegistry("38");

	// .44SW
	AddAmmoNameToAmmoRegistry("44sw");

	// Tranq darts
	AddAmmoNameToAmmoRegistry("tranqdart");
	AddAmmoNameToAmmoRegistry("poisondart");

	// Flare Gun
	AddAmmoNameToAmmoRegistry("miniflare");
	//===========================

	//===========================
	// Buckshot (12 gauge)
	AddAmmoNameToAmmoRegistry("buckshot");

	// Hunting (25 gauge)
	AddAmmoNameToAmmoRegistry("25g");

	// Super (20 gauge)
	AddAmmoNameToAmmoRegistry("20g");
	//===========================

	//===========================
	// MP5
	AddAmmoNameToAmmoRegistry("9mmh");
	AddAmmoNameToAmmoRegistry("40mm");

	// M4
	AddAmmoNameToAmmoRegistry("556nato");
	AddAmmoNameToAmmoRegistry("smokegrenade");

	// Nailgun
	AddAmmoNameToAmmoRegistry("nails");

	// AK-47
	AddAmmoNameToAmmoRegistry("762r");
	AddAmmoNameToAmmoRegistry("her");
	//===========================

	//===========================
	// M249
	AddAmmoNameToAmmoRegistry("556h");

	// M60
	AddAmmoNameToAmmoRegistry("762h");

	// Chaingun
	AddAmmoNameToAmmoRegistry("10g");

	// Minigun
	AddAmmoNameToAmmoRegistry("12mm");
	AddAmmoNameToAmmoRegistry("spike");
	//===========================

	//===========================
	// Grenade Launcher
	AddAmmoNameToAmmoRegistry("50mm");

	// Flamethrower
	AddAmmoNameToAmmoRegistry("fuel");
	AddAmmoNameToAmmoRegistry("hell");

	// RPG
	AddAmmoNameToAmmoRegistry("rockets");

	// LAWS
	AddAmmoNameToAmmoRegistry("66mm");

	// ROCKET RIFLE
	AddAmmoNameToAmmoRegistry("riflerocket");
	//===========================

	//===========================
	// Crossbow
	AddAmmoNameToAmmoRegistry("bolts");
	AddAmmoNameToAmmoRegistry("boltpoison");

	// Torque Bow
	AddAmmoNameToAmmoRegistry("arrow");
	AddAmmoNameToAmmoRegistry("arrowexp");

	// M40A1
	AddAmmoNameToAmmoRegistry("762");

	// Autosniper
	AddAmmoNameToAmmoRegistry("308");
	AddAmmoNameToAmmoRegistry("338");
	//===========================

	//Energy
	//===========================
	AddAmmoNameToAmmoRegistry("mfcells");
	AddAmmoNameToAmmoRegistry("cells");
	AddAmmoNameToAmmoRegistry("plutonium");
	AddAmmoNameToAmmoRegistry("uranium");
	AddAmmoNameToAmmoRegistry("hydrogen");
	//===========================

	// Organic
	//===========================
	AddAmmoNameToAmmoRegistry("chub");
	AddAmmoNameToAmmoRegistry("snarks");
	AddAmmoNameToAmmoRegistry("supersnarks");
	AddAmmoNameToAmmoRegistry("hornets");
	AddAmmoNameToAmmoRegistry("shockbolts");
	AddAmmoNameToAmmoRegistry("spore");
	AddAmmoNameToAmmoRegistry("penguin");
	//===========================

	// Support
	//===========================
	AddAmmoNameToAmmoRegistry("medical");
	AddAmmoNameToAmmoRegistry("virus");
	AddAmmoNameToAmmoRegistry("chargejuice");
	AddAmmoNameToAmmoRegistry("flare");
	//===========================

	// Grenades
	//===========================
	AddAmmoNameToAmmoRegistry("handgrenade");
	AddAmmoNameToAmmoRegistry("hegrenade");
	AddAmmoNameToAmmoRegistry("concgrneade");
	AddAmmoNameToAmmoRegistry("gasgrenade");
	AddAmmoNameToAmmoRegistry("incgrenade");
	AddAmmoNameToAmmoRegistry("flashbang");
	AddAmmoNameToAmmoRegistry("dynamite");
	AddAmmoNameToAmmoRegistry("molotov");
	AddAmmoNameToAmmoRegistry("freezegrenade");
	AddAmmoNameToAmmoRegistry("empgrenade");
	//===========================

	// Traps
	//===========================
	AddAmmoNameToAmmoRegistry("tripmine");
	AddAmmoNameToAmmoRegistry("satchel");
	AddAmmoNameToAmmoRegistry("timebomb");
	AddAmmoNameToAmmoRegistry("proxbomb");
	AddAmmoNameToAmmoRegistry("landmine");
	AddAmmoNameToAmmoRegistry("nailmine");
	AddAmmoNameToAmmoRegistry("mirv");
	AddAmmoNameToAmmoRegistry("calptrop");
	AddAmmoNameToAmmoRegistry("detpack");
	//===========================
}


// Precaches the weapon and queues the weapon info for sending to clients
void UTIL_PrecacheOtherWeapon( const char *szClassname )
{
	edict_t	*pent;

	pent = CREATE_NAMED_ENTITY( MAKE_STRING( szClassname ) );
	if ( FNullEnt( pent ) )
	{
		ALERT ( at_console, "NULL Ent in UTIL_PrecacheOtherWeapon\n" );
		return;
	}
	
	CBaseEntity *pEntity = CBaseEntity::Instance (VARS( pent ));

	if (pEntity)
	{
		ItemInfo II;
		pEntity->Precache( );
		memset( &II, 0, sizeof II );
		if ( ((CBasePlayerItem*)pEntity)->GetItemInfo( &II ) )
		{
			CBasePlayerItem::ItemInfoArray[II.iId] = II;
			memset(&II, 0, sizeof II);
		}
	}

	REMOVE_ENTITY(pent);
}

// called by worldspawn
void W_Precache(void)
{
	memset(CBasePlayerItem::ItemInfoArray, 0, sizeof(CBasePlayerItem::ItemInfoArray));
	// We need this to prevent weird behavior with the weapon_question index
	for (int i = 0; i < 128; i++)
	{
		//if (i >= WEAPON_CURRENTMAX)
		CBasePlayerItem::ItemInfoArray[i].iId = -1;
	}

	memset(CBasePlayerItem::AmmoInfoArray, 0, sizeof(CBasePlayerItem::AmmoInfoArray));
	giAmmoIndex = 0;

	// The index of all ammo is precached here
	UTIL_PrecacheAllAmmo();

	// custom items...

	// common world objects
	UTIL_PrecacheOther( "item_suit" );
	UTIL_PrecacheOther( "item_battery" );
	UTIL_PrecacheOther( "item_longjump" );

	// crowbar
	//UTIL_PrecacheOtherWeapon( "weapon_crowbar" );

	// glock
	//UTIL_PrecacheOtherWeapon( "weapon_glock" );
	//UTIL_PrecacheOther( "ammo_9mm" );

	// mp5
	UTIL_PrecacheOtherWeapon( "weapon_mp5" );
	UTIL_PrecacheOther( "ammo_40mm" );
	UTIL_PrecacheOther( "ammo_9mmh" );

	UTIL_PrecacheOther( "weaponbox" );// container for dropped deathmatch weapons


	g_sModelIndexFireball = PRECACHE_MODEL ("sprites/zerogxplode.spr");// fireball
	g_sModelIndexWExplosion = PRECACHE_MODEL ("sprites/WXplo1.spr");// underwater fireball
	g_sModelIndexSmoke = PRECACHE_MODEL ("sprites/steam1.spr");// smoke
	g_sModelIndexBubbles = PRECACHE_MODEL ("sprites/bubble.spr");//bubbles
	g_sModelIndexBloodSpray = PRECACHE_MODEL ("sprites/bloodspray.spr"); // initial blood
	g_sModelIndexBloodDrop = PRECACHE_MODEL ("sprites/blood.spr"); // splattered blood 

	g_sModelIndexLaser = PRECACHE_MODEL( (char *)g_pModelNameLaser );
	g_sModelIndexLaserDot = PRECACHE_MODEL("sprites/laserdot.spr");


	// used by explosions
	PRECACHE_MODEL ("models/grenade.mdl");
	PRECACHE_MODEL ("sprites/explode1.spr");

	PRECACHE_SOUND ("weapons/debris1.wav");// explosion aftermaths
	PRECACHE_SOUND ("weapons/debris2.wav");// explosion aftermaths
	PRECACHE_SOUND ("weapons/debris3.wav");// explosion aftermaths

	PRECACHE_SOUND ("weapons/grenade_hit1.wav");//grenade
	PRECACHE_SOUND ("weapons/grenade_hit2.wav");//grenade
	PRECACHE_SOUND ("weapons/grenade_hit3.wav");//grenade

	PRECACHE_SOUND ("weapons/bullet_hit1.wav");	// hit by bullet
	PRECACHE_SOUND ("weapons/bullet_hit2.wav");	// hit by bullet
	
	PRECACHE_SOUND ("items/weapondrop1.wav");// weapon falls to the ground

}


 

TYPEDESCRIPTION	CBasePlayerItem::m_SaveData[] = 
{
	DEFINE_FIELD(CBasePlayerItem, m_pPlayer, FIELD_CLASSPTR),
	DEFINE_FIELD(CBasePlayerItem, m_pNext, FIELD_CLASSPTR),
	DEFINE_FIELD(CBasePlayerItem, m_iId, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayerItem, m_fWeaponUpgrades, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayerItem, m_iWeaponLooks, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayerItem, m_flBlockAmount, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerItem, m_flBlockAmount, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerItem, m_flBlockCooldown, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerItem, m_flBlockRegen, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerItem, m_flWeaponAnimTime, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerItem, m_fWeaponStatusFlags, FIELD_FLAG),
};
IMPLEMENT_SAVERESTORE( CBasePlayerItem, CBaseAnimating );


TYPEDESCRIPTION	CBasePlayerWeapon::m_SaveData[] = 
{
#if defined( CLIENT_WEAPONS )
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextPrimaryAttack, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextSecondaryAttack, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextTertiaryAttack, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextQuaternaryAttack, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextQuinaryAttack, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextWeaponIdle, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextReload, FIELD_FLOAT),
#else	// CLIENT_WEAPONS
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextPrimaryAttack, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextSecondaryAttack, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextTertiaryAttack, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextQuaternaryAttack, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextQuinaryAttack, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextReload, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextWeaponIdle, FIELD_TIME),
#endif	// CLIENT_WEAPON


	DEFINE_FIELD(CBasePlayerWeapon, m_flNextRecoil, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerWeapon, m_flInitialRecoilCooldown, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayerWeapon, m_flIncrementalRecoilCooldown, FIELD_FLOAT),
};

IMPLEMENT_SAVERESTORE( CBasePlayerWeapon, CBasePlayerItem );

void CBasePlayerItem :: SetObjectCollisionBox( void )
{
	pev->absmin = pev->origin + Vector(-24, -24, 0);
	pev->absmax = pev->origin + Vector(24, 24, 16); 
}


//=========================================================
// Sets up movetype, size, solidtype for a new weapon. 
//=========================================================
void CBasePlayerItem :: FallInit( void )
{
	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_BBOX;

	UTIL_SetOrigin( pev, pev->origin );
	UTIL_SetSize(pev, Vector( 0, 0, 0), Vector(0, 0, 0) );//pointsize until it lands on the ground.
	
	SetTouch( &CBasePlayerItem::DefaultTouch );
	SetThink(&CBasePlayerItem::FallThink );

	pev->nextthink = gpGlobals->time + 0.1;
}

//=========================================================
// FallThink - Items that have just spawned run this think
// to catch them when they hit the ground. Once we're sure
// that the object is grounded, we change its solid type
// to trigger and set it in a large box that helps the
// player get it.
//=========================================================
void CBasePlayerItem::FallThink ( void )
{
	pev->nextthink = gpGlobals->time + 0.1;

	if ( pev->flags & FL_ONGROUND )
	{
		// clatter if we have an owner (i.e., dropped by someone)
		// don't clatter if the gun is waiting to respawn (if it's waiting, it is invisible!)
		if ( !FNullEnt( pev->owner ) )
		{
			int pitch = 95 + RANDOM_LONG(0,29);
			EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "items/weapondrop1.wav", 1, ATTN_NORM, 0, pitch);	
		}

		// lie flat
		pev->angles.x = 0;
		pev->angles.z = 0;

		Materialize(); 
	}
}

//=========================================================
// Materialize - make a CBasePlayerItem visible and tangible
//=========================================================
void CBasePlayerItem::Materialize( void )
{
	if ( pev->effects & EF_NODRAW )
	{
		// changing from invisible state to visible.
		EMIT_SOUND_DYN( ENT(pev), CHAN_WEAPON, "items/suitchargeok1.wav", 1, ATTN_NORM, 0, 150 );
		pev->effects &= ~EF_NODRAW;
		pev->effects |= EF_MUZZLEFLASH;
	}

	pev->solid = SOLID_TRIGGER;

	UTIL_SetOrigin( pev, pev->origin );// link into world.
	SetTouch (&CBasePlayerItem::DefaultTouch);
	SetThink (NULL);

}

//=========================================================
// AttemptToMaterialize - the item is trying to rematerialize,
// should it do so now or wait longer?
//=========================================================
void CBasePlayerItem::AttemptToMaterialize( void )
{
	float time = g_pGameRules->FlWeaponTryRespawn( this );

	if ( time == 0 )
	{
		Materialize();
		return;
	}

	pev->nextthink = gpGlobals->time + time;
}

//=========================================================
// CheckRespawn - a player is taking this weapon, should 
// it respawn?
//=========================================================
void CBasePlayerItem :: CheckRespawn ( void )
{
	switch ( g_pGameRules->WeaponShouldRespawn( this ) )
	{
	case GR_WEAPON_RESPAWN_YES:
		Respawn();
		break;
	case GR_WEAPON_RESPAWN_NO:
		return;
		break;
	}
}

//=========================================================
// Respawn- this item is already in the world, but it is
// invisible and intangible. Make it visible and tangible.
//=========================================================
CBaseEntity* CBasePlayerItem::Respawn( void )
{
	// make a copy of this weapon that is invisible and inaccessible to players (no touch function). The weapon spawn/respawn code
	// will decide when to make the weapon visible and touchable.
	CBaseEntity *pNewWeapon = CBaseEntity::Create( (char *)STRING( pev->classname ), g_pGameRules->VecWeaponRespawnSpot( this ), pev->angles, pev->owner );

	if ( pNewWeapon )
	{
		pNewWeapon->pev->effects |= EF_NODRAW;// invisible for now
		pNewWeapon->SetTouch( NULL );// no touch
		pNewWeapon->SetThink(&CBasePlayerItem::AttemptToMaterialize );

		DROP_TO_FLOOR ( ENT(pev) );

		// not a typo! We want to know when the weapon the player just picked up should respawn! This new entity we created is the replacement,
		// but when it should respawn is based on conditions belonging to the weapon that was taken.
		pNewWeapon->pev->nextthink = g_pGameRules->FlWeaponRespawnTime( this );
	}
	else
	{
		ALERT ( at_console, "Respawn failed to create %s!\n", STRING( pev->classname ) );
	}

	return pNewWeapon;
}

void CBasePlayerItem::DefaultTouch( CBaseEntity *pOther )
{
	// if it's not a player, ignore
	if ( !pOther->IsPlayer() )
		return;

	CBasePlayer *pPlayer = (CBasePlayer *)pOther;

	// can I have this?
	if ( !g_pGameRules->CanHavePlayerItem( pPlayer, this ) )
	{
		if ( gEvilImpulse101 )
		{
			UTIL_Remove( this );
		}
		return;
	}

	if (pOther->AddPlayerItem( this ))
	{
		AttachToPlayer( pPlayer );
		EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/gunpickup2.wav", 1, ATTN_NORM);
	}

	SUB_UseTargets( pOther, USE_TOGGLE, 0 ); // UNDONE: when should this happen?
}

// Perform upgrade
void CBasePlayerItem::Upgrade(CBasePlayerItem* pOriginal)
{
	if (IsUpgradeable(pOriginal))
		pOriginal->m_fWeaponUpgrades |= m_fWeaponUpgrades;

}

// Check whether or not this item can be duplicated, do note this is only never called
// when we already own of this weapon. We can grab a duplicate if we still have space for the ammo it uses
// or if it has upgrades we're missing. Otherwise do not do this
BOOL CBasePlayerItem::CanDuplicate(CBasePlayerItem* pOriginal)
{
	if (IsUpgradeable(pOriginal))
	{
		return TRUE;
	}
	else
	{
		// Here goes the code to check if the player can have more of either primary or secondary ammo types
	}

	return FALSE;
}

// Weapon should only be redeployed if it is upgradeable and we upgrade it, otherwise, do not redeploy on pickup
BOOL CBasePlayerItem::ShouldRedeploy(CBasePlayerItem* pOriginal)
{
	if (pOriginal->m_pPlayer)
	{
		if (pOriginal->m_pPlayer->m_pActiveItem)
		{
			if (FClassnameIs(pOriginal->m_pPlayer->m_pActiveItem->pev, STRING(pev->classname)))
			{
				if (IsUpgradeable(pOriginal))
					return TRUE;
			}
		}
	}

	return FALSE;
}

void CBasePlayerItem::UpdateSpot(void)
{
	return;
}
void CBasePlayerItem::ActivateSpot(void)
{
	return;
}
void CBasePlayerItem::DeactivateSpot(void)
{
	return;
}
void CBasePlayerItem::SuspendSpot(float flTime)
{
	return;
}
float CBasePlayerItem::GetSpotRender(void)
{
	return 0.0f;
}
float CBasePlayerItem::SetDotRenderTime(float flTime)
{
	return 0.0f;
}
BOOL CBasePlayerItem::SpotEnabled(void)
{
	return FALSE;
}

//============================================================================================================================

BOOL CanAttack( float attack_time, float curtime, BOOL isPredicted )
{
#if defined( CLIENT_WEAPONS )
	if ( !isPredicted )
#else
	if ( 1 )
#endif
	{
	return (attack_time <= curtime) ? TRUE : FALSE;
	}
	else
	{
	return (attack_time <= 0.0) ? TRUE : FALSE;
	}
}

void CBasePlayerWeapon::ReloadStart(void) {};
void CBasePlayerWeapon::ReloadStartToMid(void) {};
void CBasePlayerWeapon::ReloadMid(void) {};
void CBasePlayerWeapon::ReloadMidToEnd(void) {};
void CBasePlayerWeapon::ReloadEnd(void) {};
void CBasePlayerWeapon::ReloadEndToStart(void) {};
void CBasePlayerWeapon::ReloadCheck(void) {};

// Viewmodel animation saving crap goes here
void CBasePlayerWeapon::UpdateAnimationInfo(void)
{
	// Sanity check as always
	if (m_pPlayer)
	{
		// Get all the handles you need
		int iAnim = m_pPlayer->pev->savedvanim;
		float flFramerate = m_pPlayer->pev->savedvframerate;
		const animinfo_t* animInfo = &(weaponAnimInfoArray[m_iId].pWeaponAnimInfoArray[iAnim]);
		float flModelFramerate = (float)(animInfo->framerate);
		float flModelNumFrames = (float)(animInfo->numframes - 1);

		// Multiply by server frame rate as it applies after the model framerate
		float flFinalTime = (flModelNumFrames / flModelFramerate) * fabs(flFramerate);

		// Increment time, don't do it if the time is 
		if (!(animInfo->looping) && m_flWeaponAnimTime < flFinalTime)
			m_flWeaponAnimTime += gpGlobals->frametime;

		// Save the fucking thing
		m_pPlayer->pev->savedvframe = (byte)((float)255.0f * (m_flWeaponAnimTime / flFinalTime));

		// Reset if this animation is looping and do it depending on the sign of the server framerate
		if (animInfo->looping)
		{
			if (m_flWeaponAnimTime >= flFinalTime)
			{
				m_flWeaponAnimTime = 0.0f;
				if (m_pPlayer->pev->savedvframe > 0)
					m_pPlayer->pev->savedvframe = (byte)0;
				else
					m_pPlayer->pev->savedvframe = (byte)255.0f;
			}
		}
	}
	else
	{
		m_flWeaponAnimTime = 0.0f;
	}
}

void CBasePlayerWeapon::ItemPostFrame(void)
{
	//m_fWeaponStatusFlags = BIT64(63);
	//ALERT(at_console, "Weapon Status is %llu.\n", m_fWeaponStatusFlags);

	// Update animation information here
	UpdateAnimationInfo();

	// Reload start routine
	if (InReload())
	{
		if (InReloadMidToEnd()) ReloadMidToEnd();
		else if (InReloadEndToStart()) ReloadEndToStart();
		else if (InReloadStartToMid()) ReloadStartToMid();
		else if (InReloadEnd()) ReloadEnd();
		else if (InReloadMid()) ReloadMid();
		else if (InReloadStart()) ReloadStart();
	}

	if ((m_pPlayer->pev->button & IN_ATTACK5) && CanQuinaryAttack())
	{
		QuinaryAttack();
		m_pPlayer->pev->button &= ~IN_ATTACK5;
	}
	else if ((m_pPlayer->pev->button & IN_ATTACK4) && CanQuaternaryAttack())
	{
		QuaternaryAttack();
		m_pPlayer->pev->button &= ~IN_ATTACK4;
	}
	else if ((m_pPlayer->pev->button & IN_ATTACK3) && CanTertiaryAttack() )
	{
		TertiaryAttack();
		m_pPlayer->pev->button &= ~IN_ATTACK3;
	}
	else if ((m_pPlayer->pev->button & IN_ATTACK2) && CanSecondaryAttack() )
	{
		SecondaryAttack();
		m_pPlayer->pev->button &= ~IN_ATTACK2;
	}
	else if ((m_pPlayer->pev->button & IN_ATTACK) && CanPrimaryAttack() )
	{
		PrimaryAttack();
	}
	else if ( m_pPlayer->pev->button & IN_RELOAD && CanReload() && !InReload() ) 
	{
		// reload when reload is pressed, or if no buttons are down and weapon is empty.
		Reload();
	}
	else if (!(m_pPlayer->pev->button & (IN_ATTACK | IN_ATTACK2 | IN_ATTACK3 | IN_ATTACK4 | IN_ATTACK5)))
	{
		// no fire buttons down

		m_fFireOnEmpty = FALSE;

		if ( !IsUseable() && m_flNextPrimaryAttack < ( UseDecrement() ? 0.0 : gpGlobals->time ) ) 
		{
			// weapon isn't useable, switch.
			if ( !(iFlags() & ITEM_FLAG_NOAUTOSWITCHEMPTY) && g_pGameRules->GetNextBestWeapon( m_pPlayer, this ) )
			{
				m_flNextPrimaryAttack = ( UseDecrement() ? 0.0 : gpGlobals->time ) + 0.3;
				return;
			}
		}
		else
		{

		}

		WeaponIdle( );
		return;
	}
	
	// catch all
	if ( ShouldWeaponIdle() )
	{
		WeaponIdle();
	}
}

void CBasePlayerItem::DestroyItem( void )
{
	if ( m_pPlayer )
	{
		// if attached to a player, remove. 
		m_pPlayer->RemovePlayerItem( this );
	}

	Kill( );
}

void CBasePlayerItem::DestroyItemAlt(void)
{
	if (m_pPlayer)
	{
		m_pPlayer->RemovePlayerItemAlt(this);
	}

	Kill();
}

int CBasePlayerItem::AddToPlayer( CBasePlayer *pPlayer )
{
	m_pPlayer = pPlayer;

	return TRUE;
}

void CBasePlayerItem::Drop( void )
{
	SetTouch( NULL );
	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time + .1;
}

void CBasePlayerItem::Kill( void )
{
	SetTouch( NULL );
	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time + .1;
}

void CBasePlayerItem::Holster( int skiplocal /* = 0 */ )
{ 
	m_pPlayer->pev->viewmodel = 0; 
	m_pPlayer->pev->weaponmodel = 0;
}

void CBasePlayerItem::AttachToPlayer ( CBasePlayer *pPlayer )
{
	pev->movetype = MOVETYPE_FOLLOW;
	pev->solid = SOLID_NOT;
	pev->aiment = pPlayer->edict();
	pev->effects = EF_NODRAW; // ??
	pev->modelindex = 0;// server won't send down to clients if modelindex == 0
	pev->model = iStringNull;
	pev->owner = pPlayer->edict();
	pev->nextthink = gpGlobals->time + .1;
	SetTouch( NULL );
	SetThink( NULL );
}

// Return number of Ammo Types
int CBasePlayerItem::GetNumAmmoTypes(void)
{
	// Sanity check or in case weapon truly doesn't have this kind of array info
	if (!GetWeaponInfo())
		return 0;

	return (int)GetWeaponInfo()->size();
}

// Is this a valid ammo type index?
BOOL CBasePlayerItem::ValidAmmoTypeIndex(int iAmmoTypeIndex)
{
	if (iAmmoTypeIndex > -1 && iAmmoTypeIndex < GetNumAmmoTypes())
		return TRUE;

	return FALSE;
}

// Return number of alternate ammo type for a specific ammo type
int CBasePlayerItem::GetNumAltAmmoTypes(int iAmmoTypeIndex)
{
	// Sanity check or in case weapon truly doesn't have this kind of array info
	if (!ValidAmmoTypeIndex(iAmmoTypeIndex))
		return 0;

	return (int)GetWeaponInfo()->at(iAmmoTypeIndex).ammoTypes.size();
}

// Is this a valid alt ammo type index
BOOL CBasePlayerItem::ValidAltAmmoTypeIndex(int iAmmoTypeIndex, int iAmmoAltTypeIndex)
{
	if (iAmmoAltTypeIndex > -1 && iAmmoAltTypeIndex < GetNumAltAmmoTypes(iAmmoTypeIndex))
		return TRUE;

	return FALSE;
}

// Get the total numer of ammo types supported by this
int CBasePlayerItem::GetTotalNumAmmoTypes(void)
{
	int result = 0;

	for (int i = 0; i < GetNumAmmoTypes(); i++)
	{
		result += GetNumAltAmmoTypes(i);
	}

	return result;
}

// Get minimum bound of ammo type 
int CBasePlayerItem::GetAmmoTypeMinBound(int iAmmoTypeIndex)
{
	int result = -1;

	if (!ValidAmmoTypeIndex(iAmmoTypeIndex))
		return result;

	result = 0;

	for (int i = 0; i < (int)GetWeaponInfo()->size(); i++)
	{
		if (i == iAmmoTypeIndex)
			break;

		result += (int)GetWeaponInfo()->at(i).ammoTypes.size();
	}

	return result;
}

// Get maximum bound of ammo type
int CBasePlayerItem::GetAmmoTypeMaxBound(int iAmmoTypeIndex)
{
	if (!GetWeaponInfo())
		return -1;

	if (iAmmoTypeIndex >= (int)GetWeaponInfo()->size())
		return -1;

	int result = (int)GetWeaponInfo()->at(0).ammoTypes.size() - 1;

	for (int i = 0; i < (int)GetWeaponInfo()->size(); i++)
	{
		if (i == iAmmoTypeIndex)
			break;

		result += (int)GetWeaponInfo()->at(i).ammoTypes.size();
	}

	return result;
}

// Get Number of Clips
int CBasePlayerItem::GetNumClips(void)
{
	// No weapon info means no clip!
	if (!GetWeaponInfo())
		return 0;

	int result = 0;

	for (int i = 0; i < GetWeaponInfo()->size(); i++)
	{
		result += GetWeaponInfo()->at(i).numClips;
	}

	return result;
}

// UNIVERSAL: Check whether the input clip index is valid or not
BOOL CBasePlayerItem::ValidClipIndex(int iClipIndex)
{
	if (iClipIndex > -1 && iClipIndex < GetNumClips())
		return TRUE;

	return FALSE;
}

// Integer (int): GetClipAmmoType
// Integer (int) iClipIndex: Index of the clip for which we're checking the ammo type. 
// Return the ammo type of the clip at iClipIndex.
// Return the ammo type the clip belongs you.
int CBasePlayerItem::GetClipAmmoType(int iClipIndex)
{
	int result = -1;

	if (!ValidClipIndex(iClipIndex))
		return result;

	for (int i = 0; i < GetNumAmmoTypes(); i++)
	{
		int minVal = GetAmmoTypeMinBound(i);
		int maxVal = GetAmmoTypeMaxBound(i);

		if (range(iClipIndex, minVal, maxVal))
		{
			result = i;
			break;
		}
	}

	return result;
}

int CBasePlayerItem::GetClipAmmoLegalIndex(int iClipIndex)
{
	int result = -1;

	if (!GetWeaponInfo() || !UsesAmmo() || !ValidClipIndex(iClipIndex))
		return result;

	// Whole buch of checks needed for this
	if (ValidAmmoTypeIndex(GetClipAmmoType(iClipIndex)))
	{
		result = GetClipAmmoType(iClipIndex);
	}

	return result;
}

// Get ammo index of the clip at index iClipIndex
int CBasePlayerItem::GetClipAmmoIndex(int iClipIndex)
{
	int result = -1;

	int iAmmoTypeIndex = GetClipAmmoLegalIndex(iClipIndex);

	if (ValidAmmoTypeIndex(iAmmoTypeIndex))
	{
		if (GetAmmoIndexArray() && GetLegalAmmoTypes())
		{
			result = GetLegalAmmoTypes()->at(iAmmoTypeIndex).at(GetAmmoIndexArray()[iAmmoTypeIndex]);
		}
	}

	return result;

}

// Return the ammo type loaded for a specific ammo type index, note, clips sharing the same ammo type use the same index on the ammo index array
int CBasePlayerItem::GetCurrentAmmoType(int iAmmoTypeIndex)
{
	if (ValidAmmoTypeIndex(iAmmoTypeIndex) && GetAmmoIndexArray())
	{
		return GetAmmoIndexArray()[iAmmoTypeIndex];
	}

	return -1;
}

// Return the ammo type loaded for a specific ammo type index, note, clips sharing the same ammo type use the same index on the ammo index array
void CBasePlayerItem::SetCurrentAmmoType(int iAmmoTypeIndex, int iSetTo)
{
	if (ValidAmmoTypeIndex(iAmmoTypeIndex))
	{
		if (ValidAltAmmoTypeIndex(iAmmoTypeIndex, iSetTo))
		{
			if (GetAmmoIndexArray())
				GetAmmoIndexArray()[iAmmoTypeIndex] = iSetTo;
		}
	}
}

//  Get the value of clip
int CBasePlayerItem::GetClip(int iClipIndex)
{
	if (ValidClipIndex(iClipIndex))
	{
		if (GetClipArray())
		{
			//ALERT(at_console, "Found it!\n");
			int* iResult = GetClipArray();
			return GetClipArray()[iClipIndex];
		}
		else
		{
			//ALERT(at_console, "Clip array not found.\n");
		}
	}

	return WEAPON_CLIP_INVALID;
}

// Get the maximum clip capacity of that clip
int CBasePlayerItem::GetMaxClip(int iClipIndex)
{
	if (ValidClipIndex(iClipIndex))
	{
		if (GetMaxClipArray())
		{
			return GetMaxClipArray()[iClipIndex];
		}
	}

	return WEAPON_CLIP_INVALID;
}

// Does this weapon use ammo at all? The check is simple, check whether or not if we have at least one ammo type
BOOL CBasePlayerItem::UsesAmmo(void)
{
	return (GetNumAmmoTypes() > 0) ? TRUE : FALSE;
}

// Does this weapon use this specific ammo index?
BOOL CBasePlayerItem::UsesAmmoIndex(int iAmmoIndex)
{
	// Sanity
	if (!GetLegalAmmoTypes() || !ValidAmmoIndex(iAmmoIndex))
		return FALSE;

	// Loop through the legalAmmoType vector, we've already performed a sanity check before hand
	for (int i = 0; i < (int)GetLegalAmmoTypes()->size(); i++)
	{
		for (int y = 0; y < (int)GetLegalAmmoTypes()->at(i).size(); y++)
		{
			if (GetLegalAmmoTypes()->at(i).at(y) == iAmmoIndex)
				return TRUE;
		}
	}

	// Nothing found, carry on
	return FALSE;
}

// Does this weapon use this specific ammo designated by name?
BOOL CBasePlayerItem::UsesAmmoName(const char* szAmmoName)
{
	// Sanity
	if (!GetLegalAmmoTypes())
		return FALSE;

	int ammoIndex = GetAmmoIndex(szAmmoName);

	return UsesAmmoIndex(ammoIndex);
}

// Does this weapon have the infinite reserve ammo cheat?
// First, check for whether or not we're even checking for cheats
// Second, check if we're checking for weapon cheats
BOOL CBasePlayerItem::HasInfiniteReserveAmmoCheat(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	// Place this check so we don't have to do it with every function that checks for infinite cheat
	if (!HasFlags64(fCheckFlags, AMMO_CHECK_INFINITE_CHEAT))
		return FALSE;

	if (HasFlags(g_iAmmoCheat, SV_INF_AMMO_RESERVE_OVERRIDE) && HasFlags64(fCheckFlags, AMMO_CHECK_SERVER_INFINITE_CHEAT))
	{
		return HasFlags(g_iAmmoCheat, SV_INF_AMMO_RESERVE);
	}
	else if (m_pPlayer)
	{
		if (m_pPlayer->HasCheatFlags(CFL_INF_AMMORO) && HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE_CHEAT))
		{
			return m_pPlayer->HasCheatFlags(CFL_INF_AMMOR);
		}
		else
		{
			//goto HasInfiniteReserveAmmoCheatNoPlayerOverride;
			if (HasCheatFlags(CFL_INF_AMMORO) && HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE_CHEAT))
			{
				return HasCheatFlags(CFL_INF_AMMOR);
			}
			else
			{
				goto HasInfiniteReserveAmmoCheatNoPlayerOverride;
			}
		}
	}
	else
	{
	HasInfiniteReserveAmmoCheatNoPlayerOverride:
		if (m_pPlayer)
			return (BOOL)(HasFlags(g_iAmmoCheat, SV_INF_AMMO_RESERVE) || HasCheatFlags(CFL_INF_AMMOR) || m_pPlayer->HasCheatFlags(CFL_INF_AMMOR));
		else
			return (BOOL)(HasFlags(g_iAmmoCheat, SV_INF_AMMO_RESERVE) || HasCheatFlags(CFL_INF_AMMOR));
	}

	// By default, return false
	return FALSE;
}

// Regular infinite reserve ammo is checked with ammo indices equal to -1
// Default flags: Apart from the cheat flags defaults, we also apply the owner flag because in standard situations, we always check whether the owner has ammo, not the weapon itself
// However, that behavior changes when the check is done on the weapon having no owner
BOOL CBasePlayerItem::HasInfiniteReserveAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	// No point in going through all of the hassle if the weapon does not use ammo
	if (!UsesAmmo())
		return FALSE;

	// Place this check so we don't have to do it with every function that checks for infinite cheat
	if (!HasFlags64(fCheckFlags, AMMO_CHECK_INFINITE_ALL, FC_ANY))
		return FALSE;

	// Check for cheats is done inside of that function
	if (HasInfiniteReserveAmmoCheat(fCheckFlags))
		return TRUE;

	// Check player reserve
	if (m_pPlayer)
	{
		if (HasFlags64(fCheckFlags, AMMO_CHECK_INFINITE_NOCHEAT, FC_ANY))
		{
			// If we have a player, first check only for the legal ammo types from the ammo indices array
			for (int x = 0; x < (int)GetLegalAmmoTypes()->size(); x++)
			{
				for (int y = 0; y < (int)GetLegalAmmoTypes()->at(x).size(); y++)
				{
					if (ValidAmmoIndex(GetLegalAmmoTypes()->at(x).at(y)))
					{
						int index = GetLegalAmmoTypes()->at(x).at(y);
						if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE))
						{
							if (m_pPlayer->PureHasAmmoIndex(index) == -1)
								return TRUE;
						}

						if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE))
						{
							if (PureHasAmmoIndex(index) == -1)
								return TRUE;
						}
					}
				}
			}
		}
	}
	else
	{
		// If we're sticking with default behavior, do this
		if (HasFlags64(fCheckFlags, AMMO_CHECK_DEFAULT))
		{
			SetFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE, TRUE);
			SetFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE, FALSE);
		}

		if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE))
		{
			// Loop over the weapon's own reserve
			for (int y = 0; y < GetAmmoRegisterySize(); y++)
			{
				if (PureHasAmmoIndex(y) == -1)
					return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasReserveAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	if (!UsesAmmo())
		return FALSE;

	// Check for cheats is done inside of that function
	if (HasInfiniteReserveAmmoCheat(fCheckFlags))
		return TRUE;

	// Check player reserve
	if (m_pPlayer)
	{
		if (HasFlags64(fCheckFlags, AMMO_CHECK_RESERVE_FLAGS, FC_ANY))
		{
			// If we have a player, first check only for the legal ammo types from the ammo indices array
			for (int x = 0; x < (int)GetLegalAmmoTypes()->size(); x++)
			{
				for (int y = 0; y < (int)GetLegalAmmoTypes()->at(x).size(); y++)
				{
					if (ValidAmmoIndex(GetLegalAmmoTypes()->at(x).at(y)))
					{
						int index = GetLegalAmmoTypes()->at(x).at(y);

						if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER | AMMO_CHECK_WEAPON))
						{
							if (m_pPlayer->PureHasAmmoIndex(index))
								return TRUE;
						}

						if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER))
						{
							if (m_pPlayer->PureHasPositiveAmmoIndex(index))
								return TRUE;
						}

						if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON))
						{
							if (PureHasPositiveAmmoIndex(index))
								return TRUE;
						}
					}
				}
			}
		}
	}
	else
	{
		// If we're sticking with default behavior, do this
		if (HasFlags64(fCheckFlags, AMMO_CHECK_DEFAULT))
		{
			SetFlags64(fCheckFlags, AMMO_CHECK_WEAPON, TRUE);
			SetFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE, TRUE);
			SetFlags64(fCheckFlags, AMMO_CHECK_OWNER, FALSE);
			SetFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE, FALSE);
		}

		// Loop over the weapon's own reserve
		for (int y = 0; y < GetAmmoRegisterySize(); y++)
		{
			if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_NOCHEAT))
			{
				if (PureHasAmmoIndex(y))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE))
			{
				if (PureHasInfiniteAmmoIndex(y))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER))
			{
				if (PureHasPositiveAmmoIndex(y))
					return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasInfiniteReserveAmmoIndex(int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	// Don't bother if we don't use ammo
	if (!UsesAmmo())
		return FALSE;

	// If ammo index is not valid, return false
	if (!ValidAmmoIndex(iAmmoIndex))
		return FALSE;

	// Check for inifnites if valid
	if (HasInfiniteReserveAmmoCheat(fCheckFlags))
		return TRUE;

	if (m_pPlayer)
	{
		if (HasFlags64(fCheckFlags, AMMO_CHECK_RESERVE_FLAGS, FC_ANY))
		{
			if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE))
			{
				if (m_pPlayer->PureHasInfiniteAmmoIndex(iAmmoIndex))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE))
			{
				if (PureHasInfiniteAmmoIndex(iAmmoIndex))
					return TRUE;
			}
		}
	}
	else
	{
		// If we're sticking with default behavior, do this
		if (HasFlags64(fCheckFlags, AMMO_CHECK_DEFAULT))
		{
			SetFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE, TRUE);
			SetFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE, FALSE);
		}

		if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE))
		{
			if (PureHasInfiniteAmmoIndex(iAmmoIndex))
				return TRUE;
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasReserveAmmoIndex(int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	// If ammo index is not valid, return false
	if (!ValidAmmoIndex(iAmmoIndex))
		return FALSE;

	// Check for inifnites if valid
	if (HasInfiniteReserveAmmoCheat(fCheckFlags))
		return TRUE;

	if (m_pPlayer)
	{
		if (HasFlags64(fCheckFlags, AMMO_CHECK_RESERVE_FLAGS, FC_ANY))
		{
			if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE))
			{
				if (m_pPlayer->PureHasInfiniteAmmoIndex(iAmmoIndex))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER))
			{
				if (m_pPlayer->PureHasPositiveAmmoIndex(iAmmoIndex))
				{
					return TRUE;
				}
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE))
			{
				if (PureHasInfiniteAmmoIndex(iAmmoIndex))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON))
			{
				if (PureHasPositiveAmmoIndex(iAmmoIndex))
					return TRUE;
			}
		}
	}
	else
	{
		// If we're sticking with default behavior, do this
		if (HasFlags64(fCheckFlags, AMMO_CHECK_DEFAULT))
		{
			SetFlags64(fCheckFlags, AMMO_CHECK_WEAPON, TRUE);
			SetFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE, TRUE);
			SetFlags64(fCheckFlags, AMMO_CHECK_OWNER, FALSE);
			SetFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE, FALSE);
		}

		if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_NOCHEAT))
		{
			if (PureHasAmmoIndex(iAmmoIndex))
				return TRUE;
		}

		if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE))
		{
			if (PureHasInfiniteAmmoIndex(iAmmoIndex))
				return TRUE;
		}

		if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER))
		{
			if (PureHasPositiveAmmoIndex(iAmmoIndex))
				return TRUE;
		}
	}

	return FALSE;
}

// This is for ammo types
BOOL CBasePlayerItem::HasInfiniteReserveAmmoType(int iAmmoTypeIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	if (!ValidAmmoTypeIndex(iAmmoTypeIndex))
		return FALSE;

	if (!UsesAmmo())
		return FALSE;

	if (HasInfiniteReserveAmmoCheat(fCheckFlags))
		return TRUE;

	for (int i = 0; i < (int)GetLegalAmmoTypes()->at(iAmmoTypeIndex).size(); i++)
	{
		int iIndex = GetLegalAmmoTypes()->at(iAmmoTypeIndex).at(i);

		if (!ValidAmmoIndex(iIndex))
			continue;

		if (m_pPlayer)
		{
			if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE))
			{
				if (m_pPlayer->PureHasInfiniteAmmoIndex(iIndex))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE))
			{
				if (PureHasInfiniteAmmoIndex(iIndex))
					return TRUE;
			}
		}
		else
		{
			if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE))
			{
				if (PureHasInfiniteAmmoIndex(iIndex))
					return TRUE;
			}
		}
	}

	return FALSE;
}

// This is for ammo types, note, called alt type (sub types instead)
BOOL CBasePlayerItem::HasReserveAmmoType(int iAmmoTypeIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	if (!ValidAmmoTypeIndex(iAmmoTypeIndex))
		return FALSE;

	if (!UsesAmmo())
		return FALSE;

	if (HasInfiniteReserveAmmoCheat(fCheckFlags))
		return TRUE;

	for (int i = 0; i < (int)GetLegalAmmoTypes()->at(iAmmoTypeIndex).size(); i++)
	{
		int iIndex = GetLegalAmmoTypes()->at(iAmmoTypeIndex).at(i);

		if (!ValidAmmoIndex(iIndex))
			continue;

		if (m_pPlayer)
		{
			if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER_INFINITE))
			{
				if (m_pPlayer->PureHasInfiniteAmmoIndex(iIndex))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_OWNER))
			{
				if (m_pPlayer->PureHasPositiveAmmoIndex(iIndex))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE))
			{
				if (PureHasInfiniteAmmoIndex(iIndex))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON))
			{
				if (PureHasPositiveAmmoIndex(iIndex))
					return TRUE;
			}
		}
		else
		{
			if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON_INFINITE))
			{
				if (PureHasInfiniteAmmoIndex(iIndex))
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_WEAPON))
			{
				if (PureHasPositiveAmmoIndex(iIndex))
					return TRUE;
			}
		}
	}

	return FALSE;
}

// Do not use this for normal gameplay since it's a string based operation, rather use it for cheats and console commands
BOOL CBasePlayerItem::HasInfiniteReserveAmmoName(const char* szAmmoName, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	return HasInfiniteReserveAmmoIndex(GetAmmoIndex(szAmmoName), fCheckFlags);
}

// Do not use this for normal gameplay since it's a string based operation, rather use it for cheats and console commands
BOOL CBasePlayerItem::HasReserveAmmoName(const char* szAmmoName, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	return HasReserveAmmoIndex(GetAmmoIndex(szAmmoName), fCheckFlags);
}

// UNIVERSAL:
BOOL CBasePlayerItem::HasInfiniteClipAmmoCheat(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	// Place this check so we don't have to do it with every function that checks for infinite cheat
	if (!HasFlags64(fCheckFlags, AMMO_CHECK_INFINITE_CHEAT))
		return FALSE;

	if (HasFlags(g_iAmmoCheat, SV_INF_AMMO_CLIP_OVERRIDE) && HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_SERVER_INFINTE_CHEAT))
	{
		return HasFlags(g_iAmmoCheat, SV_INF_AMMO_CLIP);
	}
	else if (m_pPlayer)
	{
		if (m_pPlayer->HasCheatFlags(CFL_INF_AMMOC) && HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_OWNER_INFINITE_CHEAT))
		{
			return m_pPlayer->HasCheatFlags(CFL_INF_AMMOC);
		}
		else
		{
			//goto HasInfiniteReserveAmmoCheatNoPlayerOverride;
			if (HasCheatFlags(CFL_INF_AMMOC) && HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_SERVER_INFINTE_CHEAT))
			{
				return HasCheatFlags(CFL_INF_AMMOC);
			}
			else
			{
				goto HasInfiniteClipAmmoCheatNoPlayerOverride;
			}
		}
	}
	else
	{
	HasInfiniteClipAmmoCheatNoPlayerOverride:
		if (m_pPlayer)
			return (BOOL)(HasFlags(g_iAmmoCheat, SV_INF_AMMO_CLIP) || HasCheatFlags(CFL_INF_AMMOC) || m_pPlayer->HasCheatFlags(CFL_INF_AMMOC));
		else
			return (BOOL)(HasFlags(g_iAmmoCheat, SV_INF_AMMO_CLIP) || HasCheatFlags(CFL_INF_AMMOC));
	}

	// By default, return false
	return FALSE;
}

BOOL CBasePlayerItem::HasInfiniteClipAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	if (!UsesAmmo())
		return FALSE;

	if (GetNumClips() < 1)
		return FALSE;

	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	for (int i = 0; i < GetNumClips(); i++)
	{
		if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_INFINITE))
		{
			if (GetClip(i) == -1)
				return TRUE;
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasClipAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	if (!UsesAmmo())
		return FALSE;

	if (GetNumClips() < 1)
		return FALSE;

	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	for (int i = 0; i < GetNumClips(); i++)
	{
		if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_INFINITE))
		{
			if (GetClip(i) == -1)
				return TRUE;
		}

		if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP))
		{
			if (GetClip(i) > 0)
				return TRUE;
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasInfiniteClipAmmoTypeIndex(int iAmmoType, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	if (!UsesAmmo())
		return FALSE;

	if (GetNumClips() < 1)
		return FALSE;

	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	for (int i = 0; i < GetNumAmmoTypes(); i++)
	{
		if (i == iAmmoType)
		{
			for (int y = GetAmmoTypeMinBound(iAmmoType); y < GetAmmoTypeMaxBound(iAmmoType); y++)
			{
				if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_INFINITE))
				{
					if (GetClip(y) == -1)
						return TRUE;
				}

				if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP))
				{
					if (GetClip(y) > 0)
						return TRUE;
				}
			}

			break;
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasClipAmmoTypeIndex(int iAmmoType, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	if (!UsesAmmo())
		return FALSE;

	if (GetNumClips() < 1)
		return FALSE;

	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	for (int i = 0; i < GetNumAmmoTypes(); i++)
	{
		if (i == iAmmoType)
		{
			for (int y = GetAmmoTypeMinBound(iAmmoType); y < GetAmmoTypeMaxBound(iAmmoType); y++)
			{
				if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP))
				{
					if (GetClip(y) > 0)
						return TRUE;
				}
			}

			break;
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasInfiniteClipAmmoIndex(int iClipIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	if (!UsesAmmo())
		return FALSE;

	if (GetNumClips() < 1)
		return FALSE;

	if (!ValidClipIndex(iClipIndex))
		return FALSE;

	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_INFINITE))
	{
		if (GetClip(iClipIndex) == -1)
			return TRUE;
	}

	return FALSE;
}

// Regular ammo checks with optional infinite checks
BOOL CBasePlayerItem::HasClipAmmoIndex(int iClipIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	if (!UsesAmmo())
		return FALSE;

	if (GetNumClips() < 1)
		return FALSE;

	if (!ValidClipIndex(iClipIndex))
		return FALSE;

	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_INFINITE))
	{
		if (GetClip(iClipIndex) == -1)
			return TRUE;
	}

	if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP))
	{
		if (GetClip(iClipIndex) > 0)
			return TRUE;
	}

	return FALSE;
}

// Check whether a specific clip has an infinite amount of a specific ammo type
BOOL CBasePlayerItem::HasInfiniteClipAmmoIndexSpecific(int iClipIndex, int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	// If the weapon does not use ammo or either clip/ammo index are invalid, return FALSE
	if (!UsesAmmo() || !ValidClipIndex(iClipIndex) || !ValidAmmoIndex(iAmmoIndex))
		return FALSE;

	// If the cheat for infinite clip is there, stop and return TRUE
	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_INFINITE))
	{
		if (GetAmmoIndexArray())
		{
			if (GetClipAmmoIndex(iClipIndex) == iAmmoIndex)
			{
				if (GetClip(iClipIndex) == -1)
					return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasClipAmmoIndexSpecific(int iClipIndex, int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	// If the weapon does not use ammo or either clip/ammo index are invalid, return FALSE
	if (!UsesAmmo() || !ValidClipIndex(iClipIndex) || !ValidAmmoIndex(iAmmoIndex))
		return FALSE;

	// If the cheat for infinite clip is there, stop and return TRUE
	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	if (GetAmmoIndexArray())
	{
		if (GetClipAmmoIndex(iClipIndex) == iAmmoIndex)
		{
			if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_INFINITE))
			{
				if (GetClip(iClipIndex) == -1)
					return TRUE;
			}

			if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP))
			{
				if (GetClip(iClipIndex) > 0)
					return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasInfiniteClipAmmoIndexArray(int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	// If the weapon does not use ammo or either clip/ammo index are invalid, return FALSE
	if (!UsesAmmo() || !ValidAmmoIndex(iAmmoIndex))
		return FALSE;

	// If the cheat for infinite clip is there, stop and return TRUE
	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	// Loop over all the clips, yeehaw
	if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_INFINITE))
	{
		if (GetAmmoIndexArray())
		{
			for (int i = 0; i < GetNumClips(); i++)
			{
				if (GetClipAmmoIndex(i) == iAmmoIndex)
				{
					if (GetClip(i) == -1)
						return TRUE;
				}
			}
		}
	}

	return FALSE;
}

BOOL CBasePlayerItem::HasClipAmmoIndexArray(int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	// If the weapon does not use ammo or either clip/ammo index are invalid, return FALSE
	if (!UsesAmmo() || !ValidAmmoIndex(iAmmoIndex))
		return FALSE;

	// If the cheat for infinite clip is there, stop and return TRUE
	if (HasInfiniteClipAmmoCheat(fCheckFlags))
		return TRUE;

	// Loop over all the clips, yeehaw
		if (GetAmmoIndexArray())
		{
			for (int i = 0; i < GetNumClips(); i++)
			{
				if (GetClipAmmoIndex(i) == iAmmoIndex)
				{
					if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP_INFINITE))
					{
						if (GetClip(i) == -1)
							return TRUE;
					}

					if (HasFlags64(fCheckFlags, AMMO_CHECK_CLIP))
					{
						if (GetClip(i) > 0)
							return TRUE;
					}
				}
			}
		}

	return FALSE;
}

// General ammo check for this
BOOL CBasePlayerItem::HasAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	return BOOL(HasClipAmmo() || HasReserveAmmo());
}

BOOL CBasePlayerItem::HasAmmoType(int iAmmoTypeIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	return BOOL(HasClipAmmoTypeIndex(iAmmoTypeIndex, fCheckFlags) || HasReserveAmmoType(iAmmoTypeIndex, fCheckFlags));
}

BOOL CBasePlayerItem::HasAmmoIndex(int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	return (BOOL)(HasClipAmmoIndexArray(iAmmoIndex, fCheckFlags) || HasReserveAmmoIndex(iAmmoIndex, fCheckFlags));
}

BOOL CBasePlayerItem::HasAmmoName(const char* szAmmoName, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS)
{
	int iAmmoIndex = GetAmmoIndex(szAmmoName);

	return HasAmmoIndex(iAmmoIndex, fCheckFlags);
}

/*
=====================
CBasePlayerItem :: SetClip

Set Clip to specific value
=====================
*/
void CBasePlayerItem::SetClip(int iClipIndex, int iAmount)
{
	if (GetClipArray())
	{
		if (ValidClipIndex(iClipIndex))
			GetClipArray()[iClipIndex] = iAmount;
	}
}

/*
=====================
CBasePlayerItem :: SetMaxClip

Set Max Clip to specific value
=====================
*/
void CBasePlayerItem::SetMaxClip(int iClipIndex, int iAmount)
{
	if (GetMaxClipArray())
	{
		if (ValidClipIndex(iClipIndex))
			GetMaxClipArray()[iClipIndex] = iAmount;
	}
}

/*
=====================
CBasePlayerItem :: IncrementClip

Increment the amount of ammo in the clip
=====================
*/
void CBasePlayerItem::IncrementClip(int iClipIndex, int iAmount)
{
	SetClip(iClipIndex, min(GetClip(iClipIndex) + iAmount, GetMaxClip(iClipIndex)));
	// If there's no desynch, make it so that the number of chambered rounds is always lesser or equal to the max number of chambered rounds
	if (!HasWeaponFlags(WEAPON_FLAG_DESYNCH_CHAMBER, FC_ANY))
		SetChamberedRounds(iClipIndex, min(GetMaxChamberedRounds(iClipIndex), GetClip(iClipIndex)));
}

/*
=====================
CBasePlayerItem :: DecrementClip

Decrement the amount of ammo in the clip
=====================
*/
void CBasePlayerItem::DecrementClip(int iClipIndex, int iAmount = 1)
{
	//SetClip(iClipIndex, bound(0, GetClip(iClipIndex) - iAmount, GetMaxClip(iClipIndex) + GetMaxChamberedRounds(iClipIndex)));
	SetClip(iClipIndex, max(0, GetClip(iClipIndex) - iAmount));
	// If there's no desynch, make it so that the number of chambered rounds is always lesser or equal to the max number of chambered rounds
	if (!HasWeaponFlags(WEAPON_FLAG_DESYNCH_CHAMBER, FC_ANY))
		SetChamberedRounds(iClipIndex, min(GetMaxChamberedRounds(iClipIndex), GetClip(iClipIndex)));
}

/*
=====================
CBasePlayerItem :: GetChamaberedRounds

Decrement the amount of ammo in the clip
=====================
*/
int CBasePlayerItem::GetChamberedRounds(int iClipIndex)
{
	if (ValidClipIndex(iClipIndex))
	{
		if (GetChamberedArray())
		{
			return GetChamberedArray()[iClipIndex];
		}
	}

	return -1;
}

void CBasePlayerItem::SetChamberedRounds(int iClipIndex, int iAmount = 1)
{
	if (ValidClipIndex(iClipIndex))
	{
		if (GetChamberedArray())
		{
			GetChamberedArray()[iClipIndex] = iAmount;
		}
	}
}

int CBasePlayerItem::GetMaxChamberedRounds(int iClipIndex)
{
	if (ValidClipIndex(iClipIndex))
	{
		if (GetMaxChamberedArray())
		{
			return GetMaxChamberedArray()[iClipIndex];
		}
	}

	return -1;
}

int CBasePlayerItem::GetTargetAmmoIndex(int iAmmoTypeIndex)
{
	if (GetTargetAmmoIndexArray())
	{
		if (ValidAmmoTypeIndex(iAmmoTypeIndex))
		{
			return GetTargetAmmoIndexArray()[iAmmoTypeIndex];
		}
	}

	return -1;
}

void CBasePlayerItem::SetTargetAmmoIndex(int iAmmoTypeIndex, int iTargetAmmoTypeIndex)
{
	if (GetTargetAmmoIndexArray())
	{
		if (ValidAmmoTypeIndex(iAmmoTypeIndex) && ValidAltAmmoTypeIndex(iAmmoTypeIndex, iTargetAmmoTypeIndex))
		{
			GetTargetAmmoIndexArray()[iAmmoTypeIndex] = iTargetAmmoTypeIndex;
		}
	}
}

// Finish
void CBasePlayerItem::IncrementChamberedRounds(int iClipIndex, int iAmount = 1)
{
	SetChamberedRounds(iClipIndex, bound(0, GetChamberedRounds(iClipIndex) + iAmount, GetMaxChamberedRounds(iClipIndex)));
}

void CBasePlayerItem::DecrementChamberedRounds(int iClipIndex, int iAmount = 1)
{
	SetChamberedRounds(iClipIndex, bound(0, GetChamberedRounds(iClipIndex) - iAmount, GetMaxChamberedRounds(iClipIndex)));
}

void CBasePlayerItem::SetMaxChamberedRounds(int iClipIndex, int iAmount =1)
{
	if (ValidClipIndex(iClipIndex))
	{
		if (GetChamberedArray())
		{
			GetChamberedArray()[iClipIndex] = iAmount;
		}
	}
}

int CBasePlayerItem::GetPreReloadClip(int iClipIndex)
{
	if (ValidClipIndex(iClipIndex))
	{
		if (GetPreReloadClipArray())
		{
			return GetPreReloadClipArray()[iClipIndex];
		}
	}

	return -1;
}

void CBasePlayerItem::SetPreReloadClip(int iClipIndex, int iAmount)
{
	if (ValidClipIndex(iClipIndex))
	{
		if (GetPreReloadClipArray())
		{
			GetPreReloadClipArray()[iClipIndex] = iAmount;
		}
	}
}

// CALLED THROUGH the newly-touched weapon's instance. The existing player weapon is pOriginal
int CBasePlayerWeapon::AddDuplicate( CBasePlayerItem *pOriginal )
{
	return ExtractAmmo( (CBasePlayerWeapon *)pOriginal );
}


int CBasePlayerWeapon::AddToPlayer( CBasePlayer *pPlayer )
{
	int bResult = CBasePlayerItem::AddToPlayer( pPlayer );

	pPlayer->pev->weapons |= (1<<m_iId);

	if (bResult)
		return AddWeapon( );
	return FALSE;
}

int CBasePlayerWeapon::UpdateClientData(CBasePlayer* pPlayer)
{
	BOOL bSend = FALSE;
	int state = 0;
	if (pPlayer->m_pActiveItem == this)
	{
		if (pPlayer->m_fOnTarget)
			state = WEAPON_IS_ONTARGET;
		else
			state = 1;
	}

	// Forcing send of all data!
	if (!pPlayer->m_fWeapon)
	{
		bSend = TRUE;
	}

	// This is the current or last weapon, so the state will need to be updated
	if (this == pPlayer->m_pActiveItem ||
		this == pPlayer->m_pClientActiveItem)
	{
		if (pPlayer->m_pActiveItem != pPlayer->m_pClientActiveItem)
		{
			bSend = TRUE;
		}
	}

	// If the ammo, state, or fov has changed, update the weapon
	if (GetClip(0) != m_iClientClip ||
		state != m_iClientWeaponState ||
		pPlayer->m_iFOV != pPlayer->m_iClientFOV)
	{
		bSend = TRUE;
	}

	if (bSend)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, NULL, pPlayer->pev);
		WRITE_BYTE(state);
		WRITE_BYTE(m_iId);
		WRITE_BYTE(GetClip(0));
		MESSAGE_END();

		m_iClientClip = GetClip(0);
		m_iClientWeaponState = state;
		pPlayer->m_fWeapon = TRUE;
	}

	if (m_pNext)
		m_pNext->UpdateClientData(pPlayer);

	return 1;
}


void CBasePlayerWeapon::SendWeaponAnim(int iAnim, float flFramerate, byte byFrame, int skiplocal)
{
	if (UseDecrement())
		skiplocal = 1;
	else
		skiplocal = 0;
	m_pPlayer->pev->weaponanim = iAnim;
	m_pPlayer->pev->savedvanim = iAnim;
	m_pPlayer->pev->savedvframerate = flFramerate;
	m_pPlayer->pev->savedvframe = byFrame;

	// Calc the weapon anim time
	const animinfo_t* animInfo = &(weaponAnimInfoArray[m_iId].pWeaponAnimInfoArray[iAnim]);
	float flModelFramerate = (float)(animInfo->framerate);
	float flModelNumFrames = (float)(animInfo->numframes - 1);

	// Multiply by server frame rate as it applies after the model framerate
	float flFinalTime = (flModelNumFrames / flModelFramerate) * fabs(flFramerate);
	m_flWeaponAnimTime = flFinalTime * ((float)m_pPlayer->pev->savedvframe / (float)255.0f);

#if defined( CLIENT_WEAPONS )
	if (skiplocal && ENGINE_CANSKIP(m_pPlayer->edict()))
		return;
#endif

	MESSAGE_BEGIN(MSG_ONE, SVC_WEAPONANIM, NULL, m_pPlayer->pev);
	WRITE_LONG(iAnim);						// sequence number
	WRITE_FLOAT(flFramerate);						// sequence number
	WRITE_CHAR(byFrame);
	MESSAGE_END();
}

//=========================================================
// IsUseable - this function determines whether or not a 
// weapon is useable by the player in its current state. 
// (does it have ammo loaded? do I have any ammo for the 
// weapon?, etc)
//=========================================================
BOOL CBasePlayerWeapon :: IsUseable( void )
{
	if ( UsesAmmo() )
	{
		if ( !HasAmmo(AMMO_CHECK_DEFAULT_PARAMS) )
		{
			// clip is empty (or nonexistant) and the player has no more ammo of this type. 
			return FALSE;
		}
	}

	return TRUE;
}

// CanDeploy: Default function for when a weapon can deploy a weapon or not
BOOL CBasePlayerWeapon :: CanDeploy( void )
{
	BOOL bHasAmmo = 0;

	// If the weapon does not use ammo at all, deploy
	if (UsesAmmo())
	{
		if (!HasAmmo(AMMO_CHECK_DEFAULT_PARAMS))
			return FALSE;
	}

	return TRUE;
}

BOOL CBasePlayerWeapon :: DefaultDeploy( char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal /* = 0 */, int body )
{
	if (!CanDeploy( ))
		return FALSE;

	m_pPlayer->TabulateAmmo();
	m_pPlayer->pev->viewmodel = MAKE_STRING(szViewModel);
	m_pPlayer->pev->weaponmodel = MAKE_STRING(szWeaponModel);
	strcpy( m_pPlayer->m_szAnimExtention, szAnimExt );
	SendWeaponAnim( iAnim, 1.0f, (byte)0, skiplocal );

	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;

	return TRUE;
}

BOOL CBasePlayerWeapon :: PlayEmptySound( void )
{
	if (m_iPlayEmptySound)
	{
		EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/357_cock1.wav", 0.8, ATTN_NORM);
		m_iPlayEmptySound = 0;
		return 0;
	}
	return 0;
}

void CBasePlayerWeapon :: ResetEmptySound( void )
{
	m_iPlayEmptySound = 1;
}

//=========================================================
//=========================================================

void CBasePlayerWeapon::Holster( int skiplocal /* = 0 */ )
{ 
	UnsetReload(); // cancel any reload in progress.
	m_pPlayer->pev->viewmodel = 0; 
	m_pPlayer->pev->weaponmodel = 0;
}

// Default clip in for most weapons
void CBasePlayerWeapon::DefaultReloadClipIn(int iClipIndex)
{
	int iAmmoIndex = GetClipAmmoIndex(iClipIndex);
	BOOL hasAmmo = HasReserveAmmoIndex(iAmmoIndex, AMMO_CHECK_DEFAULT_PARAMS);
	BOOL hasInfiniteAmmo = HasInfiniteReserveAmmo(AMMO_CHECK_DEFAULT_PARAMS);
	int numMaxChamberedRounds = GetMaxChamberedRounds(iClipIndex);
	BOOL bWasNotEmpty = (GetPreReloadClip(iClipIndex) > 0) ? TRUE : FALSE;

	if (!hasAmmo)
		return;

	if (GetClip(iClipIndex) >= GetMaxClip(iClipIndex) + bWasNotEmpty * numMaxChamberedRounds)
		return;

	// We need to make sure we know what j really is because it got confusing.
	// j should be the amount inserted into the clip and removed from the ammo stash
	// Depending on whether or not we've removed ammo from the clip, we have two different values for j

	// j is equal to max clip or less if re-pooling is enabled, other j is equal to the difference
	int j = min(GetMaxClip(iClipIndex) - (GetPreReloadClip(iClipIndex) <= -1) * GetClip(iClipIndex), m_pPlayer->GetAmmo(iAmmoIndex));

	if (j <= 0 && !hasInfiniteAmmo)
		return;

	SetClip(iClipIndex, GetClip(iClipIndex) + j);
	SetChamberedRounds(iClipIndex, min(GetClip(iClipIndex), numMaxChamberedRounds));
	SetPreReloadClip(iClipIndex, -1);

	if (m_pPlayer)
	{
		if (!hasInfiniteAmmo)
		{
			m_pPlayer->SetAmmo(iAmmoIndex, max(0, m_pPlayer->GetAmmo(iAmmoIndex) - j));
			ALERT(at_console, "Ammo end: %d\n", m_pPlayer->GetAmmo(iAmmoIndex));
		}

		// Tabulate
		m_pPlayer->TabulateAmmo();
	}
}

// Default function for putting ammo into the clip
void CBasePlayerWeapon::DefaultReloadClipOut(int iClipIndex)
{
	int iAmmoIndex = GetClipAmmoIndex(iClipIndex);
	BOOL hasInfiniteAmmo = HasInfiniteReserveAmmo(AMMO_CHECK_DEFAULT_PARAMS);
	int numChamberedRounds = GetChamberedRounds(iClipIndex);

	if (HasClipAmmoIndex(iClipIndex, AMMO_CHECK_DEFAULT_PARAMS))
	{
		if (!hasInfiniteAmmo)
		{
			ALERT(at_console, "Ammo before: %d\n", m_pPlayer->GetAmmo(iAmmoIndex));
			m_pPlayer->SetAmmo(iAmmoIndex, m_pPlayer->GetAmmo(iAmmoIndex) + (GetClip(iClipIndex) - numChamberedRounds));
			ALERT(at_console, "Ammo after: %d\n", m_pPlayer->GetAmmo(iAmmoIndex));
		}
		
		SetPreReloadClip(iClipIndex, GetClip(iClipIndex));
		SetClip(iClipIndex, 0 + numChamberedRounds);
	}

	// Check for player, then tabulate
	if (m_pPlayer)
		m_pPlayer->TabulateAmmo();
}

//=========================================================
// New Negentropy functions
//=========================================================

void CBasePlayerAmmo::Spawn(void)
{
	Precache();
	SET_MODEL(ENT(pev), STRING(pev->model));

	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_TRIGGER;
	UTIL_SetSize(pev, Vector(-16, -16, 0), Vector(16, 16, 16));

	UTIL_SetOrigin(pev, pev->origin);

	SetTouch(&CBasePlayerAmmo::DefaultTouch);
}

CBaseEntity* CBasePlayerAmmo::Respawn(void)
{
	pev->effects |= EF_NODRAW;
	SetTouch(NULL);

	UTIL_SetOrigin(pev, g_pGameRules->VecAmmoRespawnSpot(this));// move to wherever I'm supposed to repawn.

	SetThink(&CBasePlayerAmmo::Materialize);
	pev->nextthink = g_pGameRules->FlAmmoRespawnTime(this);

	return this;
}

void CBasePlayerAmmo::Materialize(void)
{
	if (pev->effects & EF_NODRAW)
	{
		// changing from invisible state to visible.
		EMIT_SOUND_DYN(ENT(pev), CHAN_WEAPON, "items/suitchargeok1.wav", 1, ATTN_NORM, 0, 150);
		pev->effects &= ~EF_NODRAW;
		pev->effects |= EF_MUZZLEFLASH;
	}

	SetTouch(&CBasePlayerAmmo::DefaultTouch);
}

void CBasePlayerAmmo::DefaultTouch(CBaseEntity* pOther)
{
	if (!pOther->IsPlayer())
	{
		return;
	}

	if (AddAmmo(pOther))
	{
		if (g_pGameRules->AmmoShouldRespawn(this) == GR_AMMO_RESPAWN_YES)
		{
			Respawn();
		}
		else
		{
			SetTouch(NULL);
			SetThink(&CBaseEntity::SUB_Remove);
			pev->nextthink = gpGlobals->time + .1;
		}
	}
	else if (gEvilImpulse101)
	{
		// evil impulse 101 hack, kill always
		SetTouch(NULL);
		SetThink(&CBaseEntity::SUB_Remove);
		pev->nextthink = gpGlobals->time + .1;
	}
}

BOOL CBasePlayerAmmo::AddAmmo(CBaseEntity* pOther)
{
	if (pOther->GiveAmmo(m_iAmmoAmount, (char*)(STRING(m_szAmmoType)), pOther->GetMaxAmmo(STRING(m_szAmmoType))) != -1)
	{
		TraceResult tr = UTIL_GetGlobalTrace();
		UTIL_EmitAmbientSound(ENT(pev), tr.vecEndPos, STRING(m_szPickupSound), VOL_NORM, ATTN_NORM, 0, PITCH_NORM);
		return TRUE;
	}
	return FALSE;
}

void CBasePlayerAmmo::KeyValue(KeyValueData* pkvd)
{
	if (FStrEq(pkvd->szKeyName, "m_szAmmoType"))
	{
		m_szAmmoType = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_szPickupSound"))
	{
		m_szPickupSound = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_iAmmoAmount"))
	{
		m_iAmmoAmount = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

CBasePlayerAmmo::CBasePlayerAmmo(void)
{
	m_szPickupSound = iStringNull;
	m_szAmmoType = iStringNull;
	m_szModel = iStringNull;
	m_iAmmoAmount = 0;
}

void CBasePlayerAmmo::Precache(void)
{
	// Preache default model defined by m_szModel if no default models are found
	if (!pev->model)
		pev->model = m_szModel;

	PRECACHE_MODEL((char*)STRING(pev->model));
	PRECACHE_SOUND((char*)(STRING(m_szPickupSound)));
}

TYPEDESCRIPTION CBasePlayerAmmo::m_SaveData[] =
{
	DEFINE_FIELD(CBasePlayerAmmo, m_szAmmoType, FIELD_STRING),
	DEFINE_FIELD(CBasePlayerAmmo, m_szPickupSound, FIELD_STRING),
	DEFINE_FIELD(CBasePlayerAmmo, m_szModel, FIELD_STRING),
	DEFINE_FIELD(CBasePlayerAmmo, m_iAmmoAmount, FIELD_INTEGER),
};

IMPLEMENT_SAVERESTORE(CBasePlayerAmmo, CBaseEntity);

//=========================================================
// called by the new item with the existing item as parameter
//
// if we call ExtractAmmo(), it's because the player is picking up this type of weapon for 
// the first time. If it is spawned by the world, m_iDefaultAmmo will have a default ammo amount in it.
// if  this is a weapon dropped by a dying player, has 0 m_iDefaultAmmo, which means only the ammo in 
// the weapon clip comes along. 
//=========================================================
int CBasePlayerWeapon::ExtractAmmo( CBasePlayerWeapon *pWeapon )
{
	int	iReturn = FALSE;
	int iExtraPrimary = 0;
	int iExtraSecondary = 0;

	// Only perform this if pWeapon is also the caller for the function, that means we're picking a new weapon, so don't touch clip
	// If not, check for whether or not the weapon has a greater max clip capacity, if so, swap them and perform as normal
	// Then check whether the clip uses primary or secondary ammo type and increment extras appropriately and set to 0
	if (pWeapon != this)
	{
		
	}

	return iReturn;
}
	
//=========================================================
// RetireWeapon - no more ammo for this gun, put it away.
//=========================================================
void CBasePlayerWeapon::RetireWeapon( void )
{
	// first, no viewmodel at all.
	m_pPlayer->pev->viewmodel = iStringNull;
	m_pPlayer->pev->weaponmodel = iStringNull;
	//m_pPlayer->pev->viewmodelindex = NULL;

	g_pGameRules->GetNextBestWeapon( m_pPlayer, this );
}

void FindHullIntersection(const Vector& vecSrc, TraceResult& tr, float* mins, float* maxs, edict_t* pEntity)
{
	int			i, j, k;
	float		distance;
	float* minmaxs[2] = { mins, maxs };
	TraceResult tmpTrace;
	Vector		vecHullEnd = tr.vecEndPos;
	Vector		vecEnd;

	distance = 1e6f;

	vecHullEnd = vecSrc + ((vecHullEnd - vecSrc) * 2);
	UTIL_TraceLine(vecSrc, vecHullEnd, dont_ignore_monsters, pEntity, &tmpTrace);
	if (tmpTrace.flFraction < 1.0)
	{
		tr = tmpTrace;
		return;
	}

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			for (k = 0; k < 2; k++)
			{
				vecEnd.x = vecHullEnd.x + minmaxs[i][0];
				vecEnd.y = vecHullEnd.y + minmaxs[j][1];
				vecEnd.z = vecHullEnd.z + minmaxs[k][2];

				UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, pEntity, &tmpTrace);
				if (tmpTrace.flFraction < 1.0)
				{
					float thisDistance = (tmpTrace.vecEndPos - vecSrc).Length();
					if (thisDistance < distance)
					{
						tr = tmpTrace;
						distance = thisDistance;
					}
				}
			}
		}
	}
}

//*********************************************************
// weaponbox code:
//*********************************************************

LINK_ENTITY_TO_CLASS( weaponbox, CWeaponBox );

TYPEDESCRIPTION	CWeaponBox::m_SaveData[] = 
{
	DEFINE_ARRAY( CWeaponBox, m_rgAmmo, FIELD_INTEGER, MAX_AMMO_SLOTS ),
	DEFINE_ARRAY( CWeaponBox, m_rgiszAmmo, FIELD_STRING, MAX_AMMO_SLOTS ),
	DEFINE_ARRAY( CWeaponBox, m_rgpPlayerItems, FIELD_CLASSPTR, MAX_ITEM_TYPES ),
	DEFINE_FIELD( CWeaponBox, m_cAmmoTypes, FIELD_INTEGER ),
};

IMPLEMENT_SAVERESTORE( CWeaponBox, CBaseEntity );

//=========================================================
//
//=========================================================
void CWeaponBox::Precache( void )
{
	PRECACHE_MODEL("models/w_weaponbox.mdl");
}

//=========================================================
//=========================================================
void CWeaponBox :: KeyValue( KeyValueData *pkvd )
{
	if ( m_cAmmoTypes < MAX_AMMO_SLOTS )
	{
		PackAmmo( ALLOC_STRING(pkvd->szKeyName), atoi(pkvd->szValue) );
		m_cAmmoTypes++;// count this new ammo type.

		pkvd->fHandled = TRUE;
	}
	else
	{
		ALERT ( at_console, "WeaponBox too full! only %d ammotypes allowed\n", MAX_AMMO_SLOTS );
	}
}

//=========================================================
// CWeaponBox - Spawn 
//=========================================================
void CWeaponBox::Spawn( void )
{
	Precache( );

	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_TRIGGER;

	UTIL_SetSize( pev, g_vecZero, g_vecZero );

	SET_MODEL( ENT(pev), "models/w_weaponbox.mdl");
}

//=========================================================
// CWeaponBox - Kill - the think function that removes the
// box from the world.
//=========================================================
void CWeaponBox::Kill( void )
{
	CBasePlayerItem *pWeapon;
	int i;

	// destroy the weapons
	for ( i = 0 ; i < MAX_ITEM_TYPES ; i++ )
	{
		pWeapon = m_rgpPlayerItems[ i ];

		while ( pWeapon )
		{
			pWeapon->SetThink(&CBaseEntity::SUB_Remove);
			pWeapon->pev->nextthink = gpGlobals->time + 0.1;
			pWeapon = pWeapon->m_pNext;
		}
	}

	// remove the box
	UTIL_Remove( this );
}

//=========================================================
// CWeaponBox - Touch: try to add my contents to the toucher
// if the toucher is a player.
//=========================================================
void CWeaponBox::Touch( CBaseEntity *pOther )
{
	if ( !(pev->flags & FL_ONGROUND ) )
	{
		return;
	}

	if ( !pOther->IsPlayer() )
	{
		// only players may touch a weaponbox.
		return;
	}

	if ( !pOther->IsAlive() )
	{
		// no dead guys.
		return;
	}

	CBasePlayer *pPlayer = (CBasePlayer *)pOther;
	int i;

// dole out ammo
	for ( i = 0 ; i < MAX_AMMO_SLOTS ; i++ )
	{
		if ( !FStringNull( m_rgiszAmmo[ i ] ) )
		{
			// there's some ammo of this type. 
			pPlayer->GiveAmmo( m_rgAmmo[ i ], (char *)STRING( m_rgiszAmmo[ i ] ), MaxAmmoCarry( m_rgiszAmmo[ i ] ) );

			//ALERT ( at_console, "Gave %d rounds of %s\n", m_rgAmmo[i], STRING(m_rgiszAmmo[i]) );

			// now empty the ammo from the weaponbox since we just gave it to the player
			m_rgiszAmmo[ i ] = iStringNull;
			m_rgAmmo[ i ] = 0;
		}
	}

// go through my weapons and try to give the usable ones to the player. 
// it's important the the player be given ammo first, so the weapons code doesn't refuse 
// to deploy a better weapon that the player may pick up because he has no ammo for it.
	for ( i = 0 ; i < MAX_ITEM_TYPES ; i++ )
	{
		if ( m_rgpPlayerItems[ i ] )
		{
			CBasePlayerItem *pItem;

			// have at least one weapon in this slot
			while ( m_rgpPlayerItems[ i ] )
			{
				//ALERT ( at_console, "trying to give %s\n", STRING( m_rgpPlayerItems[ i ]->pev->classname ) );

				pItem = m_rgpPlayerItems[ i ];
				m_rgpPlayerItems[ i ] = m_rgpPlayerItems[ i ]->m_pNext;// unlink this weapon from the box

				if ( pPlayer->AddPlayerItem( pItem ) )
				{
					pItem->AttachToPlayer( pPlayer );
				}
			}
		}
	}

	EMIT_SOUND( pOther->edict(), CHAN_ITEM, "items/gunpickup2.wav", 1, ATTN_NORM );
	SetTouch(NULL);
	UTIL_Remove(this);
}

//=========================================================
// CWeaponBox - PackWeapon: Add this weapon to the box
//=========================================================
BOOL CWeaponBox::PackWeapon( CBasePlayerItem *pWeapon )
{
	// is one of these weapons already packed in this box?
	if ( HasWeapon( pWeapon ) )
	{
		return FALSE;// box can only hold one of each weapon type
	}

	if ( pWeapon->m_pPlayer )
	{
		if ( !pWeapon->m_pPlayer->RemovePlayerItem( pWeapon ) )
		{
			// failed to unhook the weapon from the player!
			return FALSE;
		}
	}

	int iWeaponSlot = pWeapon->iItemSlot();
	
	if ( m_rgpPlayerItems[ iWeaponSlot ] )
	{
		// there's already one weapon in this slot, so link this into the slot's column
		pWeapon->m_pNext = m_rgpPlayerItems[ iWeaponSlot ];	
		m_rgpPlayerItems[ iWeaponSlot ] = pWeapon;
	}
	else
	{
		// first weapon we have for this slot
		m_rgpPlayerItems[ iWeaponSlot ] = pWeapon;
		pWeapon->m_pNext = NULL;	
	}

	pWeapon->pev->spawnflags |= SF_NORESPAWN;// never respawn
	pWeapon->pev->movetype = MOVETYPE_NONE;
	pWeapon->pev->solid = SOLID_NOT;
	pWeapon->pev->effects = EF_NODRAW;
	pWeapon->pev->modelindex = 0;
	pWeapon->pev->model = iStringNull;
	pWeapon->pev->owner = edict();
	pWeapon->SetThink( NULL );// crowbar may be trying to swing again, etc.
	pWeapon->SetTouch( NULL );
	pWeapon->m_pPlayer = NULL;

	//ALERT ( at_console, "packed %s\n", STRING(pWeapon->pev->classname) );

	return TRUE;
}

//=========================================================
// CWeaponBox - PackAmmo
//=========================================================
BOOL CWeaponBox::PackAmmo( int iszName, int iCount )
{
	int iMaxCarry;

	if ( FStringNull( iszName ) )
	{
		// error here
		ALERT ( at_console, "NULL String in PackAmmo!\n" );
		return FALSE;
	}
	
	iMaxCarry = MaxAmmoCarry( iszName );

	if ( iMaxCarry != -1 && iCount > 0 )
	{
		//ALERT ( at_console, "Packed %d rounds of %s\n", iCount, STRING(iszName) );
		GiveAmmo( iCount, (char *)STRING( iszName ), iMaxCarry );
		return TRUE;
	}

	return FALSE;
}

//=========================================================
// CWeaponBox - GiveAmmo
//=========================================================
int CWeaponBox::GiveAmmo( int iCount, char *szName, int iMax, int *pIndex/* = NULL*/ )
{
	int i;

	for (i = 1; i < MAX_AMMO_SLOTS && !FStringNull( m_rgiszAmmo[i] ); i++)
	{
		if (stricmp( szName, STRING( m_rgiszAmmo[i])) == 0)
		{
			if (pIndex)
				*pIndex = i;

			int iAdd = min( iCount, iMax - m_rgAmmo[i]);
			if (iCount == 0 || iAdd > 0)
			{
				m_rgAmmo[i] += iAdd;

				return i;
			}
			return -1;
		}
	}
	if (i < MAX_AMMO_SLOTS)
	{
		if (pIndex)
			*pIndex = i;

		m_rgiszAmmo[i] = MAKE_STRING( szName );
		m_rgAmmo[i] = iCount;

		return i;
	}
	ALERT( at_console, "out of named ammo slots\n");
	return i;
}

//=========================================================
// CWeaponBox::HasWeapon - is a weapon of this type already
// packed in this box?
//=========================================================
BOOL CWeaponBox::HasWeapon( CBasePlayerItem *pCheckItem )
{
	CBasePlayerItem *pItem = m_rgpPlayerItems[pCheckItem->iItemSlot()];

	while (pItem)
	{
		if (FClassnameIs( pItem->pev, STRING( pCheckItem->pev->classname) ))
		{
			return TRUE;
		}
		pItem = pItem->m_pNext;
	}

	return FALSE;
}

//=========================================================
// CWeaponBox::IsEmpty - is there anything in this box?
//=========================================================
BOOL CWeaponBox::IsEmpty( void )
{
	int i;

	for ( i = 0 ; i < MAX_ITEM_TYPES ; i++ )
	{
		if ( m_rgpPlayerItems[ i ] )
		{
			return FALSE;
		}
	}

	for ( i = 0 ; i < MAX_AMMO_SLOTS ; i++ )
	{
		if ( !FStringNull( m_rgiszAmmo[ i ] ) )
		{
			// still have a bit of this type of ammo
			return FALSE;
		}
	}

	return TRUE;
}

//=========================================================
//=========================================================
void CWeaponBox::SetObjectCollisionBox( void )
{
	pev->absmin = pev->origin + Vector(-16, -16, 0);
	pev->absmax = pev->origin + Vector(16, 16, 16); 
}


void CBasePlayerWeapon::PrintState( void )
{
	ALERT( at_console, "primary:  %f\n", m_flNextPrimaryAttack );
	ALERT( at_console, "idle   :  %f\n", m_flNextWeaponIdle );

	ALERT( at_console, "nextrl :  %f\n", m_flNextReload );
	ALERT( at_console, "nextpum:  %f\n", m_flNextPump );
}

