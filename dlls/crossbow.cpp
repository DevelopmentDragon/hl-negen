////=============================================================//
////	Half-Life Update MOD
////	https://github.com/Fograin/hl-subsmod-ex
////	
////	This product contains software technology licensed from:
////	Valve LLC.
////	Id Software, Inc. ("Id Technology")
////
////	Before using any parts of this code, read licence.txt file 
////=============================================================//
//
//#include "extdll.h"
//#include "util.h"
//#include "cbase.h"
//#include "monsters.h"
//#include "weapons.h"
//#include "nodes.h"
//#include "player.h"
//#include "gamerules.h"
//#include "soundent.h"
//#include "decals.h"
//
//#ifndef CLIENT_DLL
//#define BOLT_AIR_VELOCITY_MAX	2500
//#define BOLT_AIR_VELOCITY		1500
//#define BOLT_WATER_VELOCITY_MAX	1300
//#define BOLT_WATER_VELOCITY		800
//
//// UNDONE: Save/restore this?  Don't forget to set classname and LINK_ENTITY_TO_CLASS()
//// 
//// OVERLOADS SOME ENTVARS:
////
//// speed - the ideal magnitude of my velocity
//
//LINK_ENTITY_TO_CLASS(crossbow_bolt, CCrossbowBolt);
//
//CCrossbowBolt* CCrossbowBolt::BoltCreate(BOOL bExplode)
//{
//	// Create a new entity with CCrossbowBolt private data
//	CCrossbowBolt* pBolt = GetClassPtr((CCrossbowBolt*)NULL);
//	pBolt->pev->classname = MAKE_STRING("crossbow_bolt");	// g-cont. enable save\restore
//	pBolt->m_bExplodes = bExplode;
//	pBolt->Spawn();
//
//	return pBolt;
//}
//
//void CCrossbowBolt::Spawn()
//{
//	Precache();
//	pev->movetype = MOVETYPE_FLY;
//	pev->solid = SOLID_BBOX;
//
//	pev->gravity = 0.5;
//	SET_MODEL(ENT(pev), "models/crossbow_bolt.mdl");
//	if (m_bExplodes)
//		pev->body = 1;
//
//	UTIL_SetOrigin(pev, pev->origin);
//	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
//	pev->dmg = 40;
//
//	SetTouch(&CCrossbowBolt::BoltTouch);
//	SetThink(&CCrossbowBolt::BubbleThink);
//	pev->nextthink = gpGlobals->time + 0.2;
//}
//
//
//void CCrossbowBolt::Precache()
//{
//	PRECACHE_MODEL("models/crossbow_bolt.mdl");
//	PRECACHE_SOUND("weapons/crossbow/hitbod.wav");
//	PRECACHE_SOUND("weapons/crossbow/hit.wav");
//	PRECACHE_SOUND("weapons/crossbow/fly.wav");
//	PRECACHE_SOUND("weapons/crossbow/exp.wav");
//	PRECACHE_SOUND("fvox/beep.wav");
//	m_iTrail = PRECACHE_MODEL("sprites/streak.spr");
//}
//
//
//int	CCrossbowBolt::Classify(void)
//{
//	return	CLASS_NONE;
//}
//
//void CCrossbowBolt::BoltTouch(CBaseEntity* pOther)
//{
//	SetTouch(NULL);
//	SetThink(NULL);
//
//	if (pOther->pev->takedamage)
//	{
//		TraceResult tr = UTIL_GetGlobalTrace();
//		entvars_t* pevOwner;
//
//		pevOwner = VARS(pev->owner);
//
//		// UNDONE: this needs to call TraceAttack instead
//		//ClearMultiDamage( );
//		if (m_bExplodes)
//		{
//			int iContents = UTIL_PointContents(pev->origin);
//			int iScale = 10;
//
//			MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
//			WRITE_BYTE(TE_EXPLOSION);
//			WRITE_COORD(pev->origin.x);
//			WRITE_COORD(pev->origin.y);
//			WRITE_COORD(pev->origin.z);
//			if (iContents != CONTENTS_WATER)
//			{
//				WRITE_SHORT(g_sModelIndexFireball);
//			}
//			else
//			{
//				WRITE_SHORT(g_sModelIndexWExplosion);
//			}
//			WRITE_BYTE(iScale); // scale * 10
//			WRITE_BYTE(15); // framerate
//			WRITE_BYTE(TE_EXPLFLAG_NOSOUND);
//			MESSAGE_END();
//
//			EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/crossbow/exp.wav", VOL_NORM, 0.3f);
//
//			entvars_t* pevOwner;
//
//			if (pev->owner)
//				pevOwner = VARS(pev->owner);
//			else
//				pevOwner = NULL;
//
//			pev->owner = NULL; // can't traceline attack owner if this is set
//
//			pOther->TraceAttack(pevOwner, gSkillData.plrDmgCrossbowBolt + pev->dmg / 2, pev->velocity.Normalize(), &tr, DMG_BULLET | DMG_NEVERGIB, ID_DMG_CROSSBOW_BOLT);
//			::RadiusDamage(pev->origin, pev, pevOwner, gSkillData.plrDmgCrossbowBolt, 128, CLASS_NONE, DMG_BLAST | DMG_ALWAYSGIB, ID_DMG_CROSSBOW_BOLT);
//
//			UTIL_DecalTrace(&tr, DECAL_OFSMSCORCH1 + RANDOM_LONG(0, 2));
//		}
//		else
//		{
//			pOther->TraceAttack(pevOwner, gSkillData.plrDmgCrossbowBolt + pev->dmg / 2, pev->velocity.Normalize(), &tr, DMG_BULLET | DMG_NEVERGIB, ID_DMG_CROSSBOW_BOLT);
//			pOther->TraceAttack(pevOwner, gSkillData.plrDmgCrossbowBolt * 2, pev->velocity.Normalize(), &tr, DMG_PARALYZE, ID_DMG_CROSSBOW_NEUROTOXIN);
//		}
//
//		//ApplyMultiDamage( pev, pevOwner, ID_DMG_GENERIC );
//
//		pev->velocity = Vector(0, 0, 0);
//		// play body "thwack" sound
//
//		EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/crossbow/hitbod.wav", 1, ATTN_NORM);
//
//		if (!g_pGameRules->IsMultiplayer())
//		{
//			Killed(pev, GIB_NEVER);
//		}
//	}
//	else
//	{
//		TraceResult tr = UTIL_GetGlobalTrace();
//
//		EMIT_SOUND_DYN(ENT(pev), CHAN_BODY, "weapons/crossbow/hit.wav", RANDOM_FLOAT(0.95, 1.0), ATTN_NORM, 0, 98 + RANDOM_LONG(0, 7));
//
//		if (m_bExplodes)
//		{
//			int iContents = UTIL_PointContents(pev->origin);
//			int iScale = 10;
//
//			MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
//			WRITE_BYTE(TE_EXPLOSION);
//			WRITE_COORD(pev->origin.x);
//			WRITE_COORD(pev->origin.y);
//			WRITE_COORD(pev->origin.z);
//			if (iContents != CONTENTS_WATER)
//			{
//				WRITE_SHORT(g_sModelIndexFireball);
//			}
//			else
//			{
//				WRITE_SHORT(g_sModelIndexWExplosion);
//			}
//			WRITE_BYTE(iScale); // scale * 10
//			WRITE_BYTE(15); // framerate
//			WRITE_BYTE(TE_EXPLFLAG_NOSOUND);
//			MESSAGE_END();
//
//			EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/crossbow/exp.wav", VOL_NORM, 0.3f);
//
//			entvars_t* pevOwner;
//
//			if (pev->owner)
//				pevOwner = VARS(pev->owner);
//			else
//				pevOwner = NULL;
//
//			pev->owner = NULL; // can't traceline attack owner if this is set
//
//			::RadiusDamage(pev->origin, pev, pevOwner, gSkillData.plrDmgTorqueBoltBlast, 128, CLASS_NONE, DMG_BLAST | DMG_ALWAYSGIB, ID_DMG_CROSSBOW_BOLT);
//
//			UTIL_DecalTrace(&tr, DECAL_OFSMSCORCH1 + RANDOM_LONG(0, 2));
//		}
//
//		SetThink(&CBaseEntity::SUB_Remove);
//		pev->nextthink = gpGlobals->time;// this will get changed below if the bolt is allowed to stick in what it hit.
//
//		if (!m_bExplodes)
//		{
//			if (FClassnameIs(pOther->pev, "worldspawn"))
//			{
//				// if what we hit is static architecture, can stay around for a while.
//				Vector vecDir = pev->velocity.Normalize();
//				UTIL_SetOrigin(pev, pev->origin - vecDir * 6);
//				pev->angles = UTIL_VecToAngles(vecDir);
//				pev->solid = SOLID_NOT;
//				pev->movetype = MOVETYPE_FLY;
//				pev->velocity = Vector(0, 0, 0);
//				pev->avelocity.z = 0;
//				pev->angles.z = RANDOM_LONG(0, 360);
//				pev->nextthink = gpGlobals->time + 10.0;
//			}
//			// Fograin92: Stick it with prop_default
//			else if (FClassnameIs(pOther->pev, "prop_default"))
//			{
//				// if what we hit is static architecture, can stay around for a while.
//				Vector vecDir = pev->velocity.Normalize();
//				UTIL_SetOrigin(pev, pev->origin - vecDir * 6);
//				pev->angles = UTIL_VecToAngles(vecDir);
//				pev->solid = SOLID_NOT;
//				pev->movetype = MOVETYPE_FLY;
//				pev->velocity = Vector(0, 0, 0);
//				pev->avelocity.z = 0;
//				pev->angles.z = RANDOM_LONG(0, 360);
//				pev->nextthink = gpGlobals->time + 10.0;
//			}
//			else if (pOther->pev->movetype == MOVETYPE_PUSH || pOther->pev->movetype == MOVETYPE_PUSHSTEP)
//			{
//				Vector vecDir = pev->velocity.Normalize();
//				UTIL_SetOrigin(pev, pev->origin - vecDir * 6);
//				pev->angles = UTIL_VecToAngles(vecDir);
//				pev->solid = SOLID_NOT;
//				pev->velocity = Vector(0, 0, 0);
//				pev->avelocity.z = 0;
//				pev->angles.z = RANDOM_LONG(0, 360);
//				pev->nextthink = gpGlobals->time + 10.0;
//
//				// g-cont. Setup movewith feature
//				pev->movetype = MOVETYPE_COMPOUND;	// set movewith type
//				pev->aiment = ENT(pOther->pev);	// set parent
//			}
//
//			if (UTIL_PointContents(pev->origin) != CONTENTS_WATER)
//			{
//				UTIL_Sparks(pev->origin);
//			}
//		}
//	}
//
//	/*
//	if ( g_pGameRules->IsMultiplayer() )
//	{
//	SetThink( &CCrossbowBolt::ExplodeThink );
//	pev->nextthink = gpGlobals->time + 0.1;
//	}
//	*/
//}
//
//void CCrossbowBolt::BubbleThink(void)
//{
//	pev->nextthink = gpGlobals->time + 0.1;
//
//	if (pev->waterlevel == 0)
//		return;
//
//	UTIL_BubbleTrail(pev->origin - pev->velocity * 0.1, pev->origin, 1);
//}
//
//void CCrossbowBolt::ExplodeThink(void)
//{
//	int iContents = UTIL_PointContents(pev->origin);
//	int iScale;
//
//	pev->dmg = 40;
//	iScale = 10;
//
//	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
//	WRITE_BYTE(TE_EXPLOSION);
//	WRITE_COORD(pev->origin.x);
//	WRITE_COORD(pev->origin.y);
//	WRITE_COORD(pev->origin.z);
//	if (iContents != CONTENTS_WATER)
//	{
//		WRITE_SHORT(g_sModelIndexFireball);
//	}
//	else
//	{
//		WRITE_SHORT(g_sModelIndexWExplosion);
//	}
//	WRITE_BYTE(iScale); // scale * 10
//	WRITE_BYTE(15); // framerate
//	WRITE_BYTE(TE_EXPLFLAG_NONE);
//	MESSAGE_END();
//
//	entvars_t* pevOwner;
//
//	if (pev->owner)
//		pevOwner = VARS(pev->owner);
//	else
//		pevOwner = NULL;
//
//	pev->owner = NULL; // can't traceline attack owner if this is set
//
//	::RadiusDamage(pev->origin, pev, pevOwner, pev->dmg, 128, CLASS_NONE, DMG_BLAST | DMG_ALWAYSGIB, ID_DMG_CROSSBOW_BOLT_BLAST);
//
//	UTIL_Remove(this);
//}
//#endif
//
//LINK_ENTITY_TO_CLASS(weapon_crossbow, CCrossbow);
//
//void CCrossbow::ItemPostFrame(void)
//{
//	UpdateBodygroup();
//	Torque();
//	Insert();
//	CBasePlayerWeapon::ItemPostFrame();
//}
//
//BOOL CCrossbow::ShouldDisplayThrowForce(void)
//{
//	if (m_bTorquing && m_iTorque > 8)
//		return TRUE;
//
//	return FALSE;
//}
//
//int CCrossbow::GetThrowForce(void)
//{
//	return m_iTorque;
//}
//
//int CCrossbow::GetMaxThrowForce(void)
//{
//	return 100;
//}
//
//void CCrossbow::Torque(void)
//{
//	if (m_pPlayer)
//	{
//		if (m_bTorquing)
//		{
//			if (m_pPlayer->pev->button & IN_ATTACK)
//			{
//				if (m_flNextTorque > 0)
//				{
//					m_flNextTorque -= gpGlobals->frametime;
//				}
//				else
//				{
//					if (m_iTorque < 100)
//					{
//						if (HasWeaponUpgrades(UPGRADE_CROSSBOW))
//							m_iTorque += 4;
//						else
//							m_iTorque += 2;
//						m_flNextTorque = 0.01f;
//
//						if (m_iTorque >= 100)
//						{
//							FireBolt();
//						}
//					}
//				}
//				//ALERT(at_console, "%.2f %d \n", m_flNextTorque, m_iTorque);
//			}
//			else
//			{
//				FireBolt();
//			}
//		}
//	}
//}
//
//void CCrossbow::UpdateBodygroup(void)
//{
//	if (m_pPlayer)
//	{
//		m_pPlayer->pev->viewmodelbody = m_bLoaded + HasWeaponUpgrades(UPGRADE_CROSSBOW) * 2;
//		m_pPlayer->pev->playmodelbody = HasWeaponUpgrades(UPGRADE_CROSSBOW);
//	}
//
//	pev->body = HasWeaponUpgrades(UPGRADE_CROSSBOW);
//}
//
//void CCrossbow::Spawn()
//{
//	Precache();
//	m_iId = WEAPON_CROSSBOW;
//	SET_MODEL(ENT(pev), "models/w_crossbow.mdl");
//	m_iDefaultAmmo = CROSSBOW_MAX_CLIP;
//	pev->classname = MAKE_STRING("weapon_crossbow");
//	FallInit();// get ready to fall down.
//}
//
//int CCrossbow::PrimaryAmmoIndex(void)
//{
//	return m_iPrimaryAmmoType;
//}
//
//int CCrossbow::SecondaryAmmoIndex(void)
//{
//	return m_iSecondaryAmmoType;
//}
//
//BOOL CCrossbow::IsUseable(void)
//{
//	return TRUE; // To be able to use the scope
//}
//
//int CCrossbow::HUDIcon(void)
//{
//	if (!m_fWeaponUpgrades)
//		return 103;
//
//	return 105;
//}
//
//int CCrossbow::HUDActiveIcon(void)
//{
//	if (!m_fWeaponUpgrades)
//		return 104;
//
//	return 106;
//}
//
//int CCrossbow::ModeIcon(void)
//{
//	if (IsZoomActive())
//		return 6;
//
//	return 17;
//}
//
//int CCrossbow::ModeIcon2(void)
//{
//	if (m_bLoaded)
//		return 37;
//
//	return 47;
//}
//
//int CCrossbow::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CCrossbow::SmallIcon(void)
//{
//	if (!m_fWeaponUpgrades)
//		return 58;
//
//	return 59;
//}
//
//void CCrossbow::Precache(void)
//{
//	PRECACHE_MODEL("models/w_crossbow.mdl");
//	PRECACHE_MODEL("models/v_crossbow.mdl");
//	PRECACHE_MODEL("models/p_crossbow.mdl");
//
//	PRECACHE_SOUND("weapons/crossbow/fire.wav");
//	PRECACHE_SOUND("weapons/crossbow/exp_fire.wav");
//	PRECACHE_SOUND("weapons/crossbow/reload.wav");
//	PRECACHE_SOUND("weapons/crossbow/clipout.wav");
//	PRECACHE_SOUND("weapons/crossbow/clipin.wav");
//	PRECACHE_SOUND("weapons/crossbow/draw.wav");
//	PRECACHE_SOUND("weapons/crossbow/holster.wav");
//	PRECACHE_SOUND("weapons/crossbow/zoom.wav");
//	PRECACHE_SOUND("weapons/crossbow/dry.wav");
//	PRECACHE_SOUND("weapons/crossbow/pickup.wav");
//	PRECACHE_SOUND("weapons/crossbow/torque.wav");
//	PRECACHE_SOUND("weapons/crossbow/add.wav");
//	PRECACHE_SOUND("weapons/crossbow/remove.wav");
//
//	UTIL_PrecacheOther("crossbow_bolt");
//
//	m_usCrossbow = PRECACHE_EVENT(1, "events/crossbow1.sc");
//}
//
//
//int CCrossbow::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "bolts";
//	p->iMaxAmmo1 = BOLT_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = CROSSBOW_MAX_CLIP;
//	p->iSlot = WEAPON_BUCKET_RANGED;
//	p->iPosition = WEAPON_CROSSBOW_SLOT;
//	p->iId = m_iId = WEAPON_CROSSBOW;
//	p->iFlags = ITEM_FLAG_DUPLICATION;
//	p->iWeight = CROSSBOW_WEIGHT;
//	return 1;
//}
//
//BOOL CCrossbow::Deploy()
//{
//	UpdateBodygroup();
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
//	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.5;
//	m_flNextReload = UTIL_WeaponTimeBase() + 0.5;
//	return DefaultDeploy("models/v_crossbow.mdl", "models/p_crossbow.mdl", (m_iClip > 0 || m_bLoaded) ? CROSSBOW_DRAW : CROSSBOW_DRAW_EMPTY, "bow");
//}
//
//void CCrossbow::Holster(int skiplocal /* = 0 */)
//{
//	m_fInReload = FALSE;	// cancel any reload in progress.
//
//	if (IsZoomActive())	// Vit_amiN 
//	{
//		SecondaryAttack();
//	}
//
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
//	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.5;
//	m_flNextReload = UTIL_WeaponTimeBase() + 0.5;
//	UpdateBodygroup();
//
//	if (m_iClip > 0 || m_bLoaded)
//		SendWeaponAnim(CROSSBOW_HOLSTER);
//	else
//		SendWeaponAnim(CROSSBOW_HOLSTER_EMPTY);
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//}
//
//
//void CCrossbow::PrimaryAttack(void)
//{
//	if (m_bTorquing || m_iInsertState)
//		return;
//
//	if (!m_bLoaded && !HasAmmo(TRUE))
//	{
//		EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/crossbow/dry.wav", 0.80, ATTN_NORM);
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.25;
//		return;
//	}
//
//	SendWeaponAnim(CROSSBOW_TORQUE);
//	EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/crossbow/torque.wav", 0.80, ATTN_NORM);
//	m_bTorquing = TRUE;
//	m_flNextTorque = 0.01f;
//}
//
//void CCrossbow::SecondaryAttack(void)
//{
//	if (m_bTorquing || m_iInsertState)
//		return;
//
//	// 0 means reset to default fov; Vit_amiN: uses IsZoomActive() now
//	m_pPlayer->pev->fov = m_pPlayer->m_iFOV = IsZoomActive() ? 0 : 20;
//	EMIT_SOUND(ENT(pev), CHAN_WEAPON3, "weapons/crossbow/zoom.wav", 0.80, ATTN_NORM);
//	//pev->nextthink = UTIL_WeaponTimeBase() + 0.1;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.0;
//}
//
//void CCrossbow::TertiaryAttack(void)
//{
//	// Disallow this for now
//	return;
//
//	if (m_bTorquing || m_iInsertState || !m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType])
//		return;
//
//	if (m_iClip > 0 || m_bLoaded)
//		SendWeaponAnim(CROSSBOW_HOLSTER);
//	else
//		SendWeaponAnim(CROSSBOW_HOLSTER_EMPTY);
//
//	m_iInsertState = 1;
//	m_flNextInsert = 0.6;
//}
//
//void CCrossbow::FireBolt()
//{
//	TraceResult tr;
//
//	m_pPlayer->m_iWeaponVolume = QUIET_GUN_VOLUME;
//
//	if (!m_bLoaded)
//	{
//		if (!HasInfiniteClipAmmo())
//			m_iClip--;
//	}
//
//	int flags;
//#if defined( CLIENT_WEAPONS )
//	flags = FEV_NOTHOST;
//#else
//	flags = 0;
//#endif
//
//	UpdateBodygroup();
//	int iAnim = m_pPlayer->pev->savedvanim = (m_iClip <= 0 ? CROSSBOW_FIRE_EMPTY : (m_fWeaponUpgrades > 0 ? CROSSBOW_FIRE_RAPID : CROSSBOW_FIRE));
//	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
//	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usCrossbow, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0, m_iClip, 0, m_fWeaponUpgrades, m_bLoaded,
//		(float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);
//
//	// player "shoot" animation
//	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//	Vector anglesAim = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
//	UTIL_MakeVectors(anglesAim);
//
//	anglesAim.x = -anglesAim.x;
//	Vector vecSrc = m_pPlayer->GetGunPosition() - gpGlobals->v_up * 2;
//	Vector vecDir = gpGlobals->v_forward;
//
//	UTIL_TraceLine(vecSrc, vecSrc + gpGlobals->v_forward * 8192, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
//
//#ifndef CLIENT_DLL
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
//
//	if (!HasClipAmmo() && !HasPrimaryAmmo())
//	{
//		// HEV suit - indicate out of ammo condition
//		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
//	}
//#endif
//
//	if (m_iClip != 0)
//	{
//		if (HasWeaponUpgrades(UPGRADE_CROSSBOW))
//		{
//			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.33;
//			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.33;
//			m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.33;
//			m_flNextReload = UTIL_WeaponTimeBase() + 0.33;
//		}
//		else
//		{
//			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.17;
//			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.17;
//			m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.17;
//			m_flNextReload = UTIL_WeaponTimeBase() + 1.17;
//		}
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.5;
//	}
//	else
//	{
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.47;
//		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.47;
//		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.47;
//		m_flNextReload = UTIL_WeaponTimeBase() + 0.47;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
//	}
//
//	m_bLoaded = FALSE;
//	UnsetIdle();
//}
//
//void CCrossbow::Reload(void)
//{
//	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 && m_pPlayer->m_flInfiniteAmmo < 1)
//		return;
//
//	if (m_bTorquing || m_iInsertState)
//		return;
//
//	if (IsZoomActive())	// Vit_amiN
//		SecondaryAttack();
//
//	if (m_iClip > 0 || m_bLoaded)
//	{
//		if (DefaultReload(5, CROSSBOW_RELOAD, 2.0f, 4.0f))
//		{
//			UpdateBodygroup();
//			m_pPlayer->SetAnimation(PLAYER_RELOAD);
//		}
//	}
//	else
//	{
//		if (DefaultReload(5, CROSSBOW_RELOAD_EMPTY, 4.0f, 6.0f))
//		{
//			UpdateBodygroup();
//			m_pPlayer->SetAnimation(PLAYER_RELOAD);
//		}
//	}
//}
//
//BOOL CCrossbow::IsZoomActive()
//{
//	return m_pPlayer && (m_pPlayer->pev->fov != 0.0f);
//}
//
//
//void CCrossbow::WeaponIdle(void)
//{
//	m_pPlayer->GetAutoaimVector(AUTOAIM_2DEGREES);  // get the autoaim vector but ignore it;  used for autoaim crosshair in DM
//
//	ResetEmptySound();
//
//	if (m_bTorquing || m_iInsertState)
//		return;
//
//	if (m_flNextWeaponIdle < UTIL_WeaponTimeBase())
//	{
//		// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//		if (RANDOM_LONG(0, 99) <= 5)
//		{
//			UpdateBodygroup();
//			SendWeaponAnim((m_iClip <= 0 && !m_bLoaded) ? CROSSBOW_FIDGET_EMPTY : CROSSBOW_FIDGET);
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.7;
//			UnsetIdle();
//		}
//		else
//		{
//			// Ensure at least two successful loops
//			if (!IsIdle())
//			{
//				UpdateBodygroup();
//				SendWeaponAnim((m_iClip <= 0 && !m_bLoaded) ? CROSSBOW_IDLE_EMPTY : CROSSBOW_IDLE);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.03 * 2;
//				SetIdle();
//			}
//			else
//			{
//				// Only perform a single loop in this case
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.03;
//			}
//		}
//	}
//}
//
//class CCrossbowAmmo : public CBasePlayerAmmo
//{
//public:
//	CCrossbowAmmo(void)
//	{
//		m_szModel = MAKE_STRING("models/ammo_bolts.mdl");
//		m_szAmmoType = MAKE_STRING("bolts");
//		m_szPickupSound = MAKE_STRING("weapons/crossbow/ammo.wav");
//		m_iAmmoAmount = CROSSBOW_MAX_CLIP;
//	}
//	void Spawn(void)
//	{
//		CBasePlayerAmmo::Spawn();
//		pev->classname = MAKE_STRING("ammo_bolts"); // Added for compatiblity
//	}
//};
//LINK_ENTITY_TO_CLASS(ammo_bolts, CCrossbowAmmo);
//LINK_ENTITY_TO_CLASS(ammo_crossbow, CCrossbowAmmo); // Added for compatibility
//
///*
//class CCrossbowAmmo2 : public CBasePlayerAmmo
//{
//public:
//	void Spawn(void)
//	{
//		pev->body = 1;
//		CBasePlayerAmmo::Spawn();
//	};
//	CCrossbowAmmo2(void)
//	{
//		m_szModel = MAKE_STRING("models/crossbow_bolt.mdl");
//		m_szAmmoType = MAKE_STRING("exp_bolts");
//		m_szPickupSound = MAKE_STRING("weapons/crossbow/ammo2.wav");
//		m_iAmmoAmount = 1;
//	};
//};
//LINK_ENTITY_TO_CLASS(ammo_exp_bolts, CCrossbowAmmo2);
//*/