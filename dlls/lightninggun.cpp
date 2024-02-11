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

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "soundent.h"
#include "basemonster.h"
#include "gamerules.h"

#ifndef CLIENT_DLL
#define TESLA_ORB_VELOCITY_MAX	1250

LINK_ENTITY_TO_CLASS(proj_teslaorb, CTeslaOrb);

CTeslaOrb::CTeslaOrb(void)
{

}

CTeslaOrb* CTeslaOrb::OrbCreate(BOOL bExplode)
{
	// Create a new entity with CCrossbowBolt private data
	CTeslaOrb* pOrb = GetClassPtr((CTeslaOrb*)NULL);
	pOrb->pev->classname = MAKE_STRING("proj_teslaorb");	// g-cont. enable save\restore
	pOrb->Spawn();

	return pOrb;
}

void CTeslaOrb::Spawn()
{
	Precache();
	pev->movetype = MOVETYPE_FLY;
	pev->solid = SOLID_BBOX;

	pev->gravity = 0.5;
	SET_MODEL(ENT(pev), "models/proj_teslaorb.mdl");
	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
	pev->dmg = 40;

	SetTouch(&CTeslaOrb::OrbTouch);
	SetThink(&CTeslaOrb::OrbThink);
	pev->nextthink = gpGlobals->time + 0.2;
}


void CTeslaOrb::Precache()
{
	PRECACHE_MODEL("models/crossbow_bolt.mdl");
	PRECACHE_SOUND("weapons/crossbow/hitbod.wav");
	PRECACHE_SOUND("weapons/crossbow/hit.wav");
	PRECACHE_SOUND("weapons/crossbow/fly.wav");
	PRECACHE_SOUND("weapons/crossbow/exp.wav");
	PRECACHE_SOUND("fvox/beep.wav");
	m_iTrail = PRECACHE_MODEL("sprites/lgtning.spr");
}


int	CTeslaOrb::Classify(void)
{
	return	CLASS_NONE;
}

void CTeslaOrb::OrbTouch(CBaseEntity* pOther)
{
	SetTouch(NULL);
	SetThink(NULL);

	TraceResult tr = UTIL_GetGlobalTrace();
	entvars_t* pevOwner = NULL;

	if (pev->owner)
		pevOwner = VARS(pev->owner);

	pev->owner = NULL; // can't traceline attack owner if this is set

	// UNDONE: this needs to call TraceAttack instead
	//ClearMultiDamage( );

	int iContents = UTIL_PointContents(pev->origin);
	int iScale = 10;

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
	WRITE_BYTE(TE_EXPLOSION);
	WRITE_COORD(pev->origin.x);
	WRITE_COORD(pev->origin.y);
	WRITE_COORD(pev->origin.z);
	if (iContents != CONTENTS_WATER)
	{
		WRITE_SHORT(g_sModelIndexFireball);
	}
	else
	{
		WRITE_SHORT(g_sModelIndexWExplosion);
	}
	WRITE_BYTE(iScale); // scale * 10
	WRITE_BYTE(15); // framerate
	WRITE_BYTE(TE_EXPLFLAG_NOSOUND);
	MESSAGE_END();

	EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/crossbow/exp.wav", VOL_NORM, 0.3f);


	if (pOther)
	{
		if (pOther->pev->takedamage)
		{
//			pOther->TraceAttack(pevOwner, gSkillData.plrDmgCrossbowBolt + pev->dmg / 2, pev->velocity.Normalize(), &tr, DMG_BULLET | DMG_NEVERGIB, ID_DMG_CROSSBOW_BOLT);
		}
	}

//	::RadiusDamage(pev->origin, pev, pevOwner, gSkillData.plrDmgCrossbowBolt, 128, CLASS_NONE, DMG_BLAST | DMG_ALWAYSGIB, ID_DMG_CROSSBOW_BOLT);

//	UTIL_DecalTrace(&tr, DECAL_OFSMSCORCH1 + RANDOM_LONG(0, 2));

	pev->velocity = Vector(0, 0, 0);
	// play body "thwack" sound

	EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/crossbow/hitbod.wav", 1, ATTN_NORM);

	if (!g_pGameRules->IsMultiplayer())
	{
		Killed(pev, GIB_NEVER);
	}

	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time;// this will get changed below if the bolt is allowed to stick in what it hit.

}

void CTeslaOrb::OrbThink(void)
{
	// If at any point, it's underwater, so underwater stuff
	if (FALSE)
	{

	}

	// If charge depletes, remove
	chargecheck:
	if (GetCharge() <= 0)
	{
		pev->nextthink = gpGlobals->time;
		SetThink(NULL);
		SetTouch(NULL);
		UTIL_Remove(this);
		return;
	}

	// Occasionally zap


	// Run timer
	if (GetDrainTime() <= 0)
	{
		SetCharge(GetCharge() - GetDrainRate());
		if (GetCharge() <= 0)
			goto chargecheck;
		SetDrainTime(GetDrainInterval());
	}
	else
	{
		SetDrainTime(max(GetDrainTime() - 0.01, 0.0f));
	}

	// Next think
	pev->nextthink = gpGlobals->time + 0.01;
}

void CTeslaOrb ::ExplodeThink(void)
{
	int iContents = UTIL_PointContents(pev->origin);
	int iScale;

	pev->dmg = 40;
	iScale = 10;

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
	WRITE_BYTE(TE_EXPLOSION);
	WRITE_COORD(pev->origin.x);
	WRITE_COORD(pev->origin.y);
	WRITE_COORD(pev->origin.z);
	if (iContents != CONTENTS_WATER)
	{
		WRITE_SHORT(g_sModelIndexFireball);
	}
	else
	{
		WRITE_SHORT(g_sModelIndexWExplosion);
	}
	WRITE_BYTE(iScale); // scale * 10
	WRITE_BYTE(15); // framerate
	WRITE_BYTE(TE_EXPLFLAG_NONE);
	MESSAGE_END();

	entvars_t* pevOwner;

	if (pev->owner)
		pevOwner = VARS(pev->owner);
	else
		pevOwner = NULL;

	pev->owner = NULL; // can't traceline attack owner if this is set

//	::RadiusDamage(pev->origin, pev, pevOwner, pev->dmg, 128, CLASS_NONE, DMG_BLAST | DMG_ALWAYSGIB, ID_DMG_CROSSBOW_BOLT_BLAST);

	UTIL_Remove(this);
}
#endif

LINK_ENTITY_TO_CLASS(weapon_dmc_light, CLightningGun);

#define DMC_LIGHT_STF_ALT		WEAPON_STF_CUSTOM5
#define DMC_LIGHT_STF_CHAIN		WEAPON_STF_CUSTOM6
#define DMC_LIGHT_STF_TRI		WEAPON_STF_CUSTOM7
#define DMC_LIGHT_STF_CHARGING	WEAPON_STF_CUSTOM8
#define DMC_LIGHT_STF_ATTACKING	WEAPON_STF_CUSTOM9

#ifndef CLIENT_DLL

TYPEDESCRIPTION	CLightningGun::m_SaveData[] =
{
	DEFINE_ARRAY(CLightningGun, m_iAmmoIndices, FIELD_INTEGER, 2),
	DEFINE_ARRAY(CLightningGun, m_iTargetAmmoIndex, FIELD_INTEGER, 2),
	DEFINE_ARRAY(CLightningGun, pTargetOne, FIELD_EHANDLE, 3),
	DEFINE_ARRAY(CLightningGun, pTargetTwo, FIELD_EHANDLE, 3),
	DEFINE_ARRAY(CLightningGun, pTargetThree, FIELD_EHANDLE, 3),
	DEFINE_FIELD(CLightningGun, m_flBeamsTime, FIELD_FLOAT),
};

IMPLEMENT_SAVERESTORE(CLightningGun, CBasePlayerWeapon);

#endif

weaponInfo CLightningGun::m_weaponInfo = {

	{ 0, { "ecells","ocecells","opecells" } },
	{ 0, { "pcells","ocpcells","oppcells" } },
};

legalAmmoTypes CLightningGun::m_legalAmmoIndicies = GenerateLegalAmmoIndicies(CLightningGun::m_weaponInfo);

CLightningGun::CLightningGun(void)
{
	m_usLight1 = 0;
	m_usLight2 = 0;
	m_fWeaponFlags = 0;

	// Max clips defaults are defined here
	m_iAmmoIndices[0] = 0;
	m_iAmmoIndices[1] = 0;

	m_iTargetAmmoIndex[0] = -1;
	m_iTargetAmmoIndex[1] = -1;

	// Init all beam stuff
	for (int i = 0; i < 9; i++)
	{
		if (i < 3) pTargetOne[i % 3] = NULL;
		if (i < 6) pTargetTwo[i % 3] = NULL;
		if (i < 9) pTargetThree[i % 3] = NULL;
		m_pBeams[i] = NULL;
	}

	m_flBeamsTime = 0.0f;
	m_flNextAnimReset = 0.0f;
	m_flNextSoundReset = 0.0f;
}

//=========================================================

int CLightningGun::HUDIcon(void)
{
	return 43;
}

int CLightningGun::HUDActiveIcon(void)
{
	return 44;
}

int CLightningGun::ModeIcon(void)
{
	return -1;
}

int CLightningGun::ModeIcon2(void)
{
	return -1;
}

int CLightningGun::ModeIcon3(void)
{
	return -1;
}

int CLightningGun::SmallIcon(void)
{
	return 26;

}

// To determine which firing mode we're using, we need some bit math fuckery
// Blueprint for weapon functions is as follows
// CONTINUOUS MODE:
//	-Primary Fire: Straight line aka DMC/Quake 1 Lightning Gun
//	-Secondary Fire: Three homing bolts aka RTCW Tesla Gun
//	-Tertiary Fire: Toggle between chaining and non-chaining
// ALTERNATE MODE:
//	-Primary Fire: Charge up to fire a straight bolt that zaps the enemy. Fires automatically when fully charged. Damage poportional to distance
//	-Secondary Fire: Same as primary, can be charged
//	-Tertiary Fire: Fire a projectile that zaps nearby enemies and that can be detonated by firing the primary on it aka Unreal 1 ASMD projectile.
// RELOAD: Switch between alternative and

void CLightningGun::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_dmc_light"); // hack to allow for old names
	Precache();
	SET_MODEL(ENT(pev), "models/w_light.mdl");
	m_iId = WEAPON_M4;
	m_iDefaultAmmo = MP5_MAX_CLIP;
	FallInit();// get ready to fall down.
	//m_iAmmoIndices;
}

void CLightningGun::Precache(void)
{
	PRECACHE_MODEL("models/v_light.mdl");
	PRECACHE_MODEL("models/w_light.mdl");
	PRECACHE_MODEL("models/p_light.mdl");

	PRECACHE_MODEL("sprites/lgtning.spr");

	PRECACHE_SOUND("weapons/dmc/light/fire.wav");
	PRECACHE_SOUND("weapons/dmc/light/firechargepent.wav");

	m_usLight1 = PRECACHE_EVENT(1, "events/light1.sc");
	m_usLight2 = PRECACHE_EVENT(1, "events/light2.sc");
}

int CLightningGun::GetItemInfo(ItemInfo* p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "ecells";
	p->iMaxAmmo1 = _9MMH_MAX_CARRY;
	p->pszAmmo2 = "pcells";
	p->iMaxAmmo2 = _40MM_MAX_CARRY;
	p->iSlot = WEAPON_BUCKET_AUTOMATIC;
	p->iPosition = WEAPON_M4_SLOT;
	p->iFlags = ITEM_FLAG_DUPLICATION;
	p->iId = m_iId = WEAPON_M4;
	p->iWeight = MP5_WEIGHT;
	return 1;
}

void CLightningGun::ItemPostFrame(void)
{
	// Timer and ticks for beam
	BeamLogic();
	UpdateBodygroup();
	CBasePlayerWeapon::ItemPostFrame();
}

void CLightningGun::UpdateBodygroup(void)
{
	if (m_pPlayer)
	{
		m_pPlayer->pev->viewmodelbody = m_pPlayer->pev->playmodelbody = 0;
		m_pPlayer->pev->viewmodelskin = m_pPlayer->pev->playmodelskin = 0;
	}

	pev->body = 0;
	pev->skin = 0;
}

void CLightningGun::PickupSound(void)
{
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/mp5/pickup.wav", 1, ATTN_NORM);
}

void CLightningGun::DropSound(void)
{
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/mp5/drop.wav", 1, ATTN_NORM);
}

BOOL CLightningGun::CanDeploy(void)
{
	return TRUE;
}

BOOL CLightningGun::Deploy(void)
{
	UpdateBodygroup();
	UnsetIdle();
	return DefaultDeploy("models/v_light.mdl", "models/p_light.mdl", LIGHT_IDLE, "mp5");
}

void CLightningGun::Holster(int skiplocal)
{
	UnsetIdle();
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = m_flNextReload = UTIL_WeaponTimeBase() + 1.0;
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
}

void CLightningGun::BeamLogic(void)
{
	if (m_pPlayer)
	{
		UpdateBeamPosition();
		if (!HasWeaponStatusFlags(DMC_LIGHT_STF_ATTACKING))
		{
			m_flNextAnimReset = 0.0f;
			m_flNextSoundReset = 0.0f;
			ClearBeams(-1);
		}
		else
		{
			if (m_flNextAnimReset > 0.0f)
			{
				m_flNextAnimReset = max(m_flNextAnimReset - gpGlobals->frametime, 0.0f);
			}

			if (m_flNextSoundReset > 0.0f)
			{
				m_flNextSoundReset = max(m_flNextSoundReset - gpGlobals->frametime, 0.0f);
			}
		}
	}
	else
	{
		m_flNextAnimReset = 0.0f;
		m_flNextSoundReset = 0.0f;
	}

	// Beam Timers
	//if (m_flBeamsTime <= 0)
	//	ClearBeams(-1);
	//else
	//	m_flBeamsTime = max(m_flBeamsTime - gpGlobals->frametime, 0.0f);
}

// WaterDischarge: If you do anything with shock based damage or abilities whilst underwater, discharge
// all the bolts. If bolts were charged, further amplify damage and radius.
//=============================================================================================================
BOOL CLightningGun::WaterDischarge(void)
{
	// If in water, discharge depending on how much you've got in reserve
	if (m_pPlayer->pev->waterlevel != 0)
	{
		// Get all ammo loaded in the weapon, ignore the rest
		float flCellsBurnt = GetCurrentAmmoType(0) + GetCurrentAmmoType(1);

		m_pPlayer->TakeDamage(pev, m_pPlayer->pev, 100 * flCellsBurnt, ID_DMG_SHOCKROACH_WATERSHOCK);
		m_pPlayer->RadiusDamage2(pev, m_pPlayer->pev, 100 * flCellsBurnt, CLASS_NONE, 100 * flCellsBurnt, ID_DMG_SHOCKROACH_WATERSHOCK);

		// Clean up animations and timers to avoid spam or desynched idles.
		m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = m_flNextReload = UTIL_WeaponTimeBase() + 0.2f;

		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/dmc/firechargepent.wav", 1, ATTN_NORM, 0, PITCH_NORM);

		return TRUE;
	}

	return FALSE;
}

//===========================================================================================================
// ClearBeams
// Arguments: <32-bit integer> iBeam, which specific beam
// Returns: Nothing
// Clears a specific beam (based on index) from memory.
// Negative numbers clear all beams.
// Any number over maximum will cause function to return early.
//===========================================================================================================
void CLightningGun::ClearBeams(int iBeam)
{
	// Do not do anything if beam index excedes maximum
	if (iBeam > 8)
		return;

	// If count is negative clear all beams, otherwise, clear only the specific beam
	int iMin = iBeam;
	int iMax = iBeam + 1;
	if (iBeam < 0) { iMin = 0; iMax = 9; }

	// Using a loop for both specific beam clear and global beam clear
	for (int i = iMin; i < iMax; i++)
	{
		if (m_pBeams[i])
		{
			UTIL_Remove(m_pBeams[i]);
			m_pBeams[i] = NULL;
		}
	}
}

//===========================================================================================================
// ClearTargets
// Arguments: <32-bit integer> iTarget, which target beam
// Returns: Nothing
// Clears a specific target (based on index) from memory.
// Negative numbers clear all targets.
// Any number over maximum will cause function to return early.
//===========================================================================================================
void CLightningGun::ClearTargets(int iTarget)
{
	// Do not do anything if beam index excedes maximum
	if (iTarget > 8)
		return;

	// If count is negative clear all beams, otherwise, clear only the specific beam
	int iMin = iTarget;
	int iMax = iTarget + 1;
	if (iTarget < 0) { iMin = 0; iMax = 9; }

	// Using a loop for both specific beam clear and global beam clear
	for (int i = iMin; i < iMax; i++)
	{
		if (i >= 0 && i < 3)
			pTargetOne[i] = NULL;

		if (i >= 3 && i < 6)
			pTargetTwo[i - 3] = NULL;

		if (i >= 6 && i < 9)
			pTargetThree[i - 6] = NULL;
	}

	m_iNumTargets = 0;
}

//===========================================================================================================
// ValidTarget
// Arguments: <EHANDLE> hTarget, the target we're checking
// Returns: <Boolean> True or False
// Checks whether the target is valid or not for latching or chaining
// Target validity depends on the following factors:
//	-If the target in question does exist
//	-If the weapon is currently owned by an entity
//	-If the target can be shocked, this depends on the CanBeShocked boolean function off of individual
//	 CBaseEntity(s)
//	-If the target is within owner LOS and can be reached by the beam
//===========================================================================================================
BOOL CLightningGun::ValidTarget(CBaseEntity *pTarget)
{
	if (pTarget != NULL)
	{
		if (m_pPlayer)
		{
			if (pTarget->CanBeShocked())
			{
				if (m_pPlayer->FVisible(pTarget))
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

BOOL CLightningGun::TargetExists(EHANDLE phTargetArray)
{
	if ((CBaseEntity*)phTargetArray)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CLightningGun::InTarget(CBaseEntity* pTarget)
{
	if (pTarget)
	{
		for (int i = 0; i < 3; i++)
		{
			if (TargetExists(pTargetOne[i]) && (pTargetOne[i] == pTarget))
				return TRUE;
		}
	}
	return FALSE;
}

BOOL CLightningGun::InChain(CBaseEntity* pTarget)
{
	if (pTarget)
	{
		for (int i = 0; i < 3; i++)
		{
			if (TargetExists(pTargetTwo[i]) && pTargetTwo[i] == pTarget)
				return TRUE;

			if (TargetExists(pTargetThree[i]) && pTargetThree[i] == pTarget)
				return TRUE;
		}
	}
	return FALSE;
}

//===========================================================================================================
// AcquireTargets
// Arguments: Nothing
// Returns: <Boolean> TRUE or FALSE, whether we have acquired a positive number of targets
// Function in charge of acquiring targets for the lightning gun depending on the mode.
// Notes:
//  -Function will default to returning false if it has no owner
//	-It is recommended to clear targets before calling this function again
//===========================================================================================================
BOOL CLightningGun::AcquireTargets(void)
{
	if (m_pPlayer)
	{
		// Sphere search
		CBaseEntity* pEntity = NULL;

		// Acquire target directly in front of you
		Vector vecSrc = m_pPlayer->GetGunPosition() - gpGlobals->v_up * 2;
		TraceResult tr;
		CBaseEntity* pTraceEntity = NULL;
		Vector anglesAim = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
		UTIL_MakeVectors(anglesAim);
		anglesAim.x = -anglesAim.x;
		Vector vecDir = gpGlobals->v_forward;
		float flDist = 8192;
		UTIL_TraceLine(vecSrc, vecSrc + vecDir * flDist, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
		
		// If we're not tri-targeting, we're single targeting
		if (HasWeaponStatusFlags(DMC_LIGHT_STF_TRI))
		{
			// We look for visible, valid targets up to a maximum of three
			while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, flDist)) != NULL)
			{
				//ALERT(at_console, "Found: %s\n", STRING(pEntity->pev->classname));
				if (pEntity == this || pEntity == m_pPlayer)
				{
					continue;
				}

				if (ValidTarget(pEntity))
				{
					pTargetOne[m_iNumTargets % 3] = pEntity; // Don't decrement one since we start at zero targets for this
					m_iNumTargets++;

					// We found three targets break
					if (m_iNumTargets >= 3) break;
				}
			}
		}
		else
		{
			// Single targeting gets immediately assigned to sphere search in case of chaining
			pTraceEntity = CBaseEntity::Instance(tr.pHit);
			pTargetOne[0] = pTraceEntity;
			pEntity = pTraceEntity; // Set in case of chaining
			m_iNumTargets++;
		}


		// Chaining requires checking whether we have a single or multiple targets
		if (!HasWeaponStatusFlags(DMC_LIGHT_STF_TRI) && !ValidTarget(pTargetOne[0]))
		{
			goto cancel;
		}
		else
		{
			if (HasWeaponStatusFlags(DMC_LIGHT_STF_CHAIN) && m_iNumTargets > 0)
			{
				// We look for visible, valid targets up to a maximum of three
				while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, flDist)) != NULL)
				{
					// Do not include this entity, the player or chained and targeted entities
					if (pEntity == this || pEntity == m_pPlayer || InChain(pEntity) || InTarget(pEntity))
					{
						continue;
					}

					if (ValidTarget(pEntity))
					{
						if (HasWeaponStatusFlags(DMC_LIGHT_STF_TRI))
						{
							// Chains go
							if (m_iNumTargets > 3 && m_iNumTargets < 7) pTargetTwo[m_iNumTargets % 3] = pEntity;
							if (m_iNumTargets > 6) pTargetThree[m_iNumTargets % 3] = pEntity;
							m_iNumTargets++;

							// Do not go over 9 targets
							if (m_iNumTargets >= 9) break;
						}
						else
						{
							// Chains go
							if (m_iNumTargets == 1) pTargetTwo[0] = pEntity;
							if (m_iNumTargets == 2) pTargetThree[0] = pEntity;
							m_iNumTargets++;

							// Do not go over 3 targets
							if (m_iNumTargets >= 3) break;
						}

					}
				}
			}
		}
	}

	cancel:
	// If by this call we have more than a single target, return TRUE
	return (m_iNumTargets > 0);
}

void CLightningGun::DamageTargets(void)
{
	float flDamage = gSkillData.plrDmgShockTase;

	if (HasWeaponStatusFlags(DMC_LIGHT_STF_TRI))
	{
		int numOnes = 0;

		for (int i = 0; i < 3; i++)
		{
			if (TargetExists(pTargetOne[i]))
			{
				numOnes++;
			}
		}

		for (int i = 0; i < numOnes; i++)
		{
			if (TargetExists(pTargetOne[i]))
			{
				if (pTargetOne[i]->pev->takedamage)
				{
					pTargetOne[i]->TakeDamage(m_pPlayer->pev, pTargetOne[i]->pev, flDamage * 1.0 + 0.33 * (3 - numOnes) * 0.5, ID_DMG_MP5);
				}
			}
		}

		if (HasWeaponStatusFlags(DMC_LIGHT_STF_CHAIN))
		{
			int numTwos = 0;
			int numThrees = 0;

			for (int i = 0; i < 3; i++)
			{
				if (TargetExists(pTargetTwo[i]))
				{
					numTwos++;
				}

				if (TargetExists(pTargetThree[i]))
				{
					numThrees++;
				}
			}

			for (int i = 0; i < numTwos; i++)
			{
				if (TargetExists(pTargetTwo[i]))
				{
					if (pTargetTwo[i]->pev->takedamage)
					{
						pTargetTwo[i]->TakeDamage(m_pPlayer->pev, pTargetTwo[i]->pev, flDamage * 1.0 + 0.33 * (3 - numTwos) * 0.25, ID_DMG_MP5);
					}
				}
			}

			for (int i = 0; i < numThrees; i++)
			{
				if (TargetExists(pTargetThree[i]))
				{
					if (pTargetThree[i]->pev->takedamage)
					{
						pTargetThree[i]->TakeDamage(m_pPlayer->pev, pTargetThree[i]->pev, flDamage * 1.0 + 0.33 * (3 - numThrees) * 0.125, ID_DMG_MP5);
					}
				}
			}
		}
	}
	else
	{
		if (HasWeaponStatusFlags(DMC_LIGHT_STF_CHAIN))
		{
			int numChain = 0;
			numChain += (TargetExists(pTargetOne[0])) ? 1 : 0;
			numChain += (TargetExists(pTargetTwo[0])) ? 1 : 0;
			numChain += (TargetExists(pTargetThree[0])) ? 1 : 0;

			if (TargetExists(pTargetOne[0]))
			{
				if (pTargetOne[0]->pev->takedamage)
				{
					pTargetOne[0]->TakeDamage(m_pPlayer->pev, pTargetOne[0]->pev, flDamage * 0.5, ID_DMG_MP5);
				}

				if (TargetExists(pTargetTwo[0]))
				{
					if (pTargetTwo[0]->pev->takedamage)
					{
						pTargetTwo[0]->TakeDamage(m_pPlayer->pev, pTargetTwo[0]->pev, flDamage * 0.25, ID_DMG_MP5);
					}

					if (TargetExists(pTargetThree[0]))
					{
						if (pTargetThree[0]->pev->takedamage)
						{
							pTargetThree[0]->TakeDamage(m_pPlayer->pev, pTargetThree[0]->pev, flDamage * 0.125, ID_DMG_MP5);
						}
					}
				}
			}
		}
		else
		{
			if (TargetExists(pTargetOne[0]))
			{
				if (pTargetOne[0]->pev->takedamage)
				{
					pTargetOne[0]->TakeDamage(m_pPlayer->pev, pTargetOne[0]->pev, flDamage, ID_DMG_MP5);
				}
			}
		}
	}
}

// Make the fucking beams
void CLightningGun::MakeBeams(void)
{
	if (m_pPlayer)
	{
		if (HasWeaponStatusFlags(DMC_LIGHT_STF_ATTACKING))
		{
			if (m_iNumTargets > 0)
			{
				// Main tri beams
				if (HasWeaponStatusFlags(DMC_LIGHT_STF_TRI))
				{
					for (int i = 0; i < 3; i++)
					{
						if (TargetExists(pTargetOne[i]))
						{
							// Draw the Beam
							if (!m_pBeams[i])
							{
								m_pBeams[i] = CBeam::BeamCreate("sprites/lgtning.spr", 50);
								m_pBeams[i]->PointsInit(m_pPlayer->GetGunPosition() - gpGlobals->v_up * 2, pTargetOne[i]->Center());
								m_pBeams[i]->SetColor(128, 128, 255);
								m_pBeams[i]->SetBrightness(255);
								m_pBeams[i]->SetNoise(20);
								m_pBeams[i]->LiveForTime(0.1);
								/*
								MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin, pev);
								WRITE_BYTE(TE_DLIGHT);
								WRITE_SHORT(0);	// entity to follow
								WRITE_COORD(pTargetOne[i]->Center().x); // x
								WRITE_COORD(pTargetOne[i]->Center().y); // y
								WRITE_COORD(pTargetOne[i]->Center().z); // z
								WRITE_COORD(1); // radius
								WRITE_BYTE(128); // r
								WRITE_BYTE(128); // g
								WRITE_BYTE(255); // b
								WRITE_BYTE(gpGlobals->time + 0.05); // life
								WRITE_BYTE(1); // decay rate
								MESSAGE_END();
								*/
							}
						}
					}
				}

				// Chain beams
				if (HasWeaponStatusFlags(DMC_LIGHT_STF_CHAIN))
				{
					for (int i = 0; i < 3; i++)
					{
						if (TargetExists(pTargetOne[i]))
						{
							if (TargetExists(pTargetTwo[i]))
							{
								if (!m_pBeams[i + 3])
								{
									m_pBeams[i + 3] = CBeam::BeamCreate("sprites/lgtning.spr", 50);
									m_pBeams[i + 3]->PointsInit(pTargetOne[i]->Center(), pTargetTwo[i]->Center());
									m_pBeams[i + 3]->SetColor(128, 128, 255);
									m_pBeams[i + 3]->SetBrightness(255);
									m_pBeams[i + 3]->SetNoise(20);
									m_pBeams[i + 3]->LiveForTime(0.1);

									if (TargetExists(pTargetThree[i]))
									{
										if (!m_pBeams[i + 6])
										{
											m_pBeams[i + 6] = CBeam::BeamCreate("sprites/lgtning.spr", 50);
											m_pBeams[i + 6]->PointsInit(pTargetTwo[i]->Center(), pTargetThree[i]->Center());
											m_pBeams[i + 6]->SetColor(128, 128, 255);
											m_pBeams[i + 6]->SetBrightness(255);
											m_pBeams[i + 6]->SetNoise(20);
											m_pBeams[i + 6]->LiveForTime(0.1);
										}
									}
								}
							}
						}
					}
				}
			}

			// If we're doing neither targeting types
			if (!HasWeaponStatusFlags(DMC_LIGHT_STF_TRI))
			{
				// Draw the Beam
				if (!m_pBeams[0])
				{
					Vector vecSrc = m_pPlayer->GetGunPosition() - gpGlobals->v_up * 2;
					TraceResult tr;
					Vector anglesAim = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
					UTIL_MakeVectors(anglesAim);
					anglesAim.x = -anglesAim.x;
					Vector vecDir = gpGlobals->v_forward;
					float flDist = 8192;
					UTIL_TraceLine(vecSrc, vecSrc + vecDir * flDist, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
					m_pBeams[0] = CBeam::BeamCreate("sprites/lgtning.spr", 50);
					m_pBeams[0]->PointEntInit(tr.vecEndPos, m_pPlayer->entindex());
					m_pBeams[0]->SetEndAttachment(1);
					m_pBeams[0]->SetColor(128, 128, 255);
					m_pBeams[0]->SetBrightness(255);
					m_pBeams[0]->SetNoise(20);
					m_pBeams[0]->LiveForTime(0.1);
				}
			}
		}
	}
}

void CLightningGun::UpdateBeamPosition(void)
{
	if (m_pPlayer)
	{
		ClearBeams(-1);
		MakeBeams();
		return;
	}
}

void CLightningGun::RegularAttack(void)
{
	// Die if you use this weapon in the water
	if (WaterDischarge()) return;

	UpdateBodygroup();
	
	// Most of the weapon functions are done here
	if (!HasWeaponStatusFlags(DMC_LIGHT_STF_ATTACKING))
		SetWeaponStatusFlags(DMC_LIGHT_STF_ATTACKING, TRUE);
	ClearBeams(-1);
	ClearTargets(-1);
	BOOL bProceed = AcquireTargets();
	if (bProceed || !HasWeaponStatusFlags(DMC_LIGHT_STF_TRI))
	{
		MakeBeams();
	}
	else
	{
		SetWeaponStatusFlags(DMC_LIGHT_STF_ATTACKING | DMC_LIGHT_STF_TRI, FALSE);
		return;
	}

	DamageTargets();

	// Create light on the weapon itself
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin, pev);
	WRITE_BYTE(TE_DLIGHT);
	WRITE_SHORT(0);	// entity to follow
	WRITE_COORD(pev->origin.x); // x
	WRITE_COORD(pev->origin.y); // y
	WRITE_COORD(pev->origin.z); // z
	WRITE_COORD(1); // radius
	WRITE_BYTE(128); // r
	WRITE_BYTE(128); // g
	WRITE_BYTE(255); // b
	WRITE_BYTE(gpGlobals->time + 0.1); // life
	WRITE_BYTE(1); // decay rate
	MESSAGE_END();

	int iAnim = m_pPlayer->pev->savedvanim;
	float flFramerate = m_pPlayer->pev->savedvframerate;
	byte byFrame = m_pPlayer->pev->savedvframe;

	BOOL bUpdateSound = FALSE;
	BOOL bUpdateAnimation = FALSE;

	if (m_flNextSoundReset <= 0.0f)
	{
		bUpdateSound = TRUE;
		m_flNextSoundReset = 0.60f;
	}

	if (m_flNextAnimReset <= 0.0f)
	{
		bUpdateAnimation = TRUE;
		m_flNextAnimReset = 0.16f;
		iAnim = m_pPlayer->pev->savedvanim = LIGHT_FIRE;
		flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
		byFrame = m_pPlayer->pev->savedvframe = (byte)0;
	}

	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usLight1, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0, 0, 0,
		bUpdateSound, bUpdateAnimation,
		(float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);

	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextReload = UTIL_WeaponTimeBase() + 1.53;
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.53;// idle pretty soon after shooting.

	UnsetIdle();
}

// PrimaryAttack
// On continuous mode: Continuously shoots a single bolt of light forward in a straight line (cells)
// On charged mode: Charge up an attack that produces a single powerful bolt (plasma cells)
void CLightningGun::PrimaryAttack(void)
{
	SetWeaponStatusFlags(DMC_LIGHT_STF_TRI, FALSE);
	RegularAttack();
}

//===========================================================================================================
// SecondaryAttack
// Arguments: None
// Returns: Nothing
// On continuous mode: Generate three bolts of lightning that prioritize latching onto
// a single target each. Multiple bolts can attack the same target, but the bonus for
// doing so won't be a 1-to-1. (cells)
// On charged mode: Straight projectile attack that has an energy pool. Zaps passing targets
// and explodes in an electric shockwave on contact with a surface or fluid. Distance
// and zaps reduce the projectile's energy pool. Continuous attacks can recharge and over the energy pool.
// A charged primary attack will detonate the projectile, dealing electric and EMP damage
// in a small radius. Two projectiles can zap each other and explode at their midpoint for
// increased damage and radius. Can destroy most projectiles.
//===========================================================================================================
void CLightningGun::SecondaryAttack(void)
{
	SetWeaponStatusFlags(DMC_LIGHT_STF_TRI, TRUE);
	RegularAttack();
}

void CLightningGun::ProjectileAttack(void)
{
	return;

	// Die if you use this weapon in the water
	if (WaterDischarge()) return;

	TraceResult tr;

	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;

	int flags = 0;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#endif

	UpdateBodygroup();

	int iAnim = m_pPlayer->pev->savedvanim = LIGHT_FIRE;
	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;

//	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usLight2, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0, 0, 0,
//		bUpdateSound, bUpdateAnimation,
//		(float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);

	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	Vector anglesAim = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
	UTIL_MakeVectors(anglesAim);

	anglesAim.x = -anglesAim.x;
	Vector vecSrc = m_pPlayer->GetGunPosition() - gpGlobals->v_up * 2;
	Vector vecDir = gpGlobals->v_forward;

	UTIL_TraceLine(vecSrc, vecSrc + gpGlobals->v_forward * 8192, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);

#ifndef CLIENT_DLL
//	CCrossbowBolt* pBolt = CCrossbowBolt::BoltCreate(m_bLoaded);
//
//	if (m_iTorque >= 100)
//		pBolt->pev->origin = tr.vecEndPos;
//	else
//		pBolt->pev->origin = vecSrc;
//	pBolt->pev->angles = anglesAim;
//	pBolt->pev->owner = m_pPlayer->edict();
//
//	float flTorqueVelocity = BOLT_AIR_VELOCITY;
//
//	if (m_pPlayer->pev->waterlevel == 3)
//		flTorqueVelocity = (float)((float)BOLT_WATER_VELOCITY + ((float)(BOLT_WATER_VELOCITY_MAX - BOLT_WATER_VELOCITY) * (float)m_iTorque / (float)100));
//	else
//		flTorqueVelocity = (float)((float)BOLT_AIR_VELOCITY + ((float)(BOLT_AIR_VELOCITY_MAX - BOLT_AIR_VELOCITY) * (float)m_iTorque / (float)100));
//
//	pBolt->pev->velocity = vecDir * flTorqueVelocity;
//	pBolt->pev->speed = flTorqueVelocity;
//	pBolt->pev->avelocity.z = 10;
//	pBolt->pev->dmg = m_iTorque;
//
//	m_iTorque = 0;
//	m_flNextTorque = -1.0f;
//	m_bTorquing = FALSE;

#endif


	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.47;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.47;
	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.47;
	m_flNextReload = UTIL_WeaponTimeBase() + 0.47;
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.5;

	UnsetIdle();
}

// TertiaryAttack
// Toggle chaining
void CLightningGun::TertiaryAttack(void)
{
	if (HasWeaponStatusFlags(DMC_LIGHT_STF_ALT))
	{
		// Fire plasma ball
		ProjectileAttack();
	}
	else
	{
		SetWeaponStatusFlags(DMC_LIGHT_STF_CHAIN, !HasWeaponStatusFlags(DMC_LIGHT_STF_CHAIN));
		ALERT(at_console, "DMC_LIGHT_STF_CHAIN: %d\n", HasWeaponStatusFlags(DMC_LIGHT_STF_CHAIN));
		if (HasWeaponStatusFlags(DMC_LIGHT_STF_TRI | DMC_LIGHT_STF_ATTACKING, FC_ANY))
		{
			ClearTargets(-1);
			ClearBeams(-1);
			SetWeaponStatusFlags(DMC_LIGHT_STF_TRI | DMC_LIGHT_STF_ATTACKING, FALSE);
		}
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.5;
	}
}


// Melee swing
void CLightningGun::QuaternaryAttack(void)
{

}

// Melee block
void CLightningGun::QuinaryAttack(void)
{

}

// ShouldReload
// Arguments: <32-bit integer> iClipIndex (UNNEEDED)
// Returns: <boolean> Should this weapon reload as of now?
// Reload is used to switch modes, you should always be able to do that
BOOL CLightningGun::ShouldReload(int iClipIndex)
{
	//return TRUE;
	return FALSE;
}

// Reload
// Arguments: None
// Returns: Nothing
// Switches between continous and charged. Because of the vital function
// performed by Reload, fidgeting when fully loaded is not possible
// FIXED: Hold R to fidget, consistancy wise it's not great, but heh.
void CLightningGun::Reload(void)
{
	// For now don't do anything
	return;

	// Can't reload if already reloading. This may change in the future
	if (InReload())
		return;

	if (ShouldReload(0))
	{
		if (HasWeaponStatusFlags(DMC_LIGHT_STF_TRI | DMC_LIGHT_STF_ATTACKING, FC_ANY))
		{
			ClearTargets(-1);
			ClearBeams(-1);
			SetWeaponStatusFlags(DMC_LIGHT_STF_TRI | DMC_LIGHT_STF_ATTACKING, FALSE);
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.43;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.43;
			m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.43;
		}
		SetReloadStart();
	}
	else
	{
		// SetReloadCheck();
	}

	// If we were idling to begin with, unset the idle.
	UnsetIdle();
}


void CLightningGun::WeaponIdle(void)
{
	// If we're in any of these states, clear beams and targets
	if (HasWeaponStatusFlags(DMC_LIGHT_STF_TRI | DMC_LIGHT_STF_ATTACKING, FC_ANY))
	{
		ClearTargets(-1);
		ClearBeams(-1);
		SetWeaponStatusFlags(DMC_LIGHT_STF_TRI | DMC_LIGHT_STF_ATTACKING, FALSE);
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.43;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.43;
		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.43;
	}

	return;

	ResetEmptySound();

	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase())
		return;

	// For now, don't re-idle if idle
	if (IsIdle()) return;

	UpdateBodygroup();
	SendWeaponAnim(LIGHT_IDLE);
	//m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.125 * 2;
	SetIdle();
}