///***
//*
//*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
//*
//*	This product contains software technology licensed from Id
//*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
//*	All Rights Reserved.
//*
//*   Use, distribution, and modification of this source code and/or resulting
//*   object code is restricted to non-commercial enhancements to products from
//*   Valve LLC.  All other use, distribution, or modification is prohibited
//*   without written permission from Valve LLC.
//*
//****/
//#include "extdll.h"
//#include "util.h"
//#include "cbase.h"
//#include "monsters.h"
//#include "weapons.h"
//#include "nodes.h"
//#include "player.h"
//#include "effects.h"
//#include "gamerules.h"
//
//#define	TRIPMINE_PRIMARY_VOLUME		450
//
//#ifndef CLIENT_DLL
//
//class CTripmineGrenade : public CGrenade
//{
//public:
//	void Spawn(void);
//	void Precache(void);
//
//	virtual int		Save(CSave& save);
//	virtual int		Restore(CRestore& restore);
//
//	static	TYPEDESCRIPTION m_SaveData[];
//
//	int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int iDamageId);
//
//	void EXPORT WarningThink(void);
//	void EXPORT PowerupThink(void);
//	void EXPORT BeamBreakThink(void);
//	void EXPORT DelayDeathThink(void);
//
//	void EXPORT ArmUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);
//	void EXPORT DefuseUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);
//
//
//	virtual int	ObjectCaps(void)
//	{
//		if (!m_bArmed)
//			return (CBaseEntity::ObjectCaps() | FCAP_IMPULSE_USE);
//		else
//			return (CBaseEntity::ObjectCaps() | FCAP_CONTINUOUS_USE);
//	};
//
//	void SetObjectCollisionBox(void)
//	{
//		//!!!BUGBUG - fix the model!
//		pev->absmin = pev->origin + Vector(-16, -16, -5);
//		pev->absmax = pev->origin + Vector(16, 16, 28);
//	}
//
//	void Killed(entvars_t* pevAttacker, int iGib);
//
//	void MakeBeam(void);
//	void KillBeam(void);
//
//	float		m_flPowerUp;
//	Vector		m_vecDir;
//	Vector		m_vecEnd;
//	float		m_flBeamLength;
//
//	BOOL		m_bArmed;
//	float		m_flArming;
//
//	EHANDLE		m_hOwner;
//	CBeam* m_pBeam;
//	Vector		m_posOwner;
//	Vector		m_angleOwner;
//	edict_t* m_pRealOwner;// tracelines don't hit PEV->OWNER, which means a player couldn't detonate his own trip mine, so we store the owner here.
//
//	static CTripmineGrenade* TripmineCreate(BOOL bArmed, Vector origin, Vector angles, edict_t* owner);
//
//	CTripmineGrenade(void)
//	{
//		m_flArming = 1.5;
//		m_bArmed = TRUE;
//	}
//};
//
//LINK_ENTITY_TO_CLASS(monster_tripmine, CTripmineGrenade);
//
//TYPEDESCRIPTION	CTripmineGrenade::m_SaveData[] =
//{
//	DEFINE_FIELD(CTripmineGrenade, m_flPowerUp, FIELD_TIME),
//	DEFINE_FIELD(CTripmineGrenade, m_vecDir, FIELD_VECTOR),
//	DEFINE_FIELD(CTripmineGrenade, m_vecEnd, FIELD_POSITION_VECTOR),
//	DEFINE_FIELD(CTripmineGrenade, m_flBeamLength, FIELD_FLOAT),
//	DEFINE_FIELD(CTripmineGrenade, m_hOwner, FIELD_EHANDLE),
//	DEFINE_FIELD(CTripmineGrenade, m_pBeam, FIELD_CLASSPTR),
//	DEFINE_FIELD(CTripmineGrenade, m_posOwner, FIELD_POSITION_VECTOR),
//	DEFINE_FIELD(CTripmineGrenade, m_angleOwner, FIELD_VECTOR),
//	DEFINE_FIELD(CTripmineGrenade, m_pRealOwner, FIELD_EDICT),
//	DEFINE_FIELD(CTripmineGrenade, m_bArmed, FIELD_BOOLEAN),
//	DEFINE_FIELD(CTripmineGrenade, m_flArming, FIELD_FLOAT),
//};
//
//IMPLEMENT_SAVERESTORE(CTripmineGrenade, CGrenade);
//
//CTripmineGrenade* CTripmineGrenade::TripmineCreate(BOOL bArmed, Vector origin, Vector angles, edict_t* owner)
//{
//	// Create a new entity with CCrossbowBolt private data
//	CTripmineGrenade* pMine = GetClassPtr((CTripmineGrenade*)NULL);
//	pMine->pev->classname = MAKE_STRING("monster_tripmine");	// g-cont. enable save\restore
//	pMine->m_bArmed = bArmed;
//	pMine->pev->origin = origin;
//	pMine->pev->angles = angles;
//
//	pMine->pev->owner = owner;
//	pMine->Spawn();
//	return pMine;
//}
//
//void CTripmineGrenade::Spawn(void)
//{
//	Precache();
//	// motor
//	pev->movetype = MOVETYPE_FLY;
//	pev->solid = SOLID_BBOX;
//
//	SET_MODEL(ENT(pev), "models/w_tripmine.mdl");
//	pev->frame = 0;
//	pev->sequence = 0;
//	ResetSequenceInfo();
//	pev->framerate = 0;
//
//	UTIL_SetOrigin(pev, pev->origin);
//	UTIL_SetSize(pev, Vector(-1, -1, -1), Vector(1, 1, 1));
//
//	if (pev->spawnflags & 1)
//	{
//		// power up quickly
//		m_flPowerUp = gpGlobals->time + 1.0;
//		m_flArming = 1.0;
//	}
//
//	SetThink(&CTripmineGrenade::PowerupThink);
//
//	if (!m_bArmed)
//		SetUse(&CTripmineGrenade::ArmUse);
//
//	pev->nextthink = gpGlobals->time + 0.2;
//
//	pev->takedamage = DAMAGE_YES;
//	pev->dmg = gSkillData.plrDmgTripmineBlast;
//	m_iGrenadeType = TYPE_TRIPMINE;
//	pev->health = 1; // don't let die normally
//
//	if (pev->owner != NULL)
//	{
//		// play deploy sound
//		EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/tripmine/plant.wav", 1.0, ATTN_NORM);
//		if (m_bArmed)
//			EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/tripmine/charge.wav", 1.0, ATTN_NORM); // chargeup
//
//		m_pRealOwner = pev->owner;// see CTripmineGrenade for why.
//		pev->owner = NULL;
//	}
//
//	UTIL_MakeAimVectors(pev->angles);
//
//	m_vecDir = gpGlobals->v_forward;
//	m_vecEnd = pev->origin + m_vecDir * 2048;
//}
//
//
//void CTripmineGrenade::Precache(void)
//{
//	PRECACHE_MODEL("models/w_tripmine.mdl");
//	PRECACHE_SOUND("weapons/tripmine/plant.wav");
//	PRECACHE_SOUND("weapons/tripmine/ready.wav");
//	PRECACHE_SOUND("weapons/tripmine/charge.wav");
//	PRECACHE_SOUND("weapons/tripmine/explode.wav");
//	PRECACHE_SOUND("weapons/tripmine/beep.wav");
//	PRECACHE_SOUND("items/defuse.wav");
//}
//
//void CTripmineGrenade::ArmUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
//{
//	if (!pActivator)
//		return;
//
//	if (!pActivator->IsPlayer())
//		return;
//
//	CBasePlayer* pPlayer = (CBasePlayer*)pActivator;
//
//	EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/tripmine/charge.wav", 1.0, ATTN_NORM);
//	m_bArmed = TRUE;
//
//	if (pev->skin > 5)
//		pev->skin -= 5;
//
//	SetUse(NULL);
//}
//
///*
//void CTripmineGrenade::DefuseUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
//{
//	if (!pActivator)
//		return;
//
//	if (!pActivator->IsPlayer())
//		return;
//
//	CBasePlayer* pPlayer = (CBasePlayer*)pActivator;
//
//	// Play defuse sound
//	if (pPlayer->m_iDefuseMeter == 0)
//	{
//		EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/defuse.wav", 1.0, ATTN_NORM);
//	}
//
//	CBaseEntity* pCompare = CBaseEntity::Instance(m_pRealOwner);
//
//	if (pCompare)
//	{
//		if (pCompare == pActivator)
//			pPlayer->m_iDefuseMeter += 250;
//	}
//
//	pPlayer->m_iDefuseMeter++;
//
//	pPlayer->m_flNextDefuse = 0.1f;
//
//	// Defuse and set appropriate logics
//	if (pPlayer->m_iDefuseMeter >= 250)
//	{
//		STOP_SOUND(ENT(pev), CHAN_ITEM, "items/defuse.wav");
//		EMIT_SOUND(ENT(pev), CHAN_ITEM, "weapons/tripmine/beep.wav", 1.0, ATTN_NORM);
//		CBaseEntity* pMine = Create("weapon_tripmine", pev->origin + m_vecDir * 8, pev->angles);
//		pMine->pev->spawnflags |= SF_NORESPAWN;
//		pMine->pev->skin = pev->skin;
//
//		SetThink(&CBaseEntity::SUB_Remove);
//		SetUse(NULL);
//		KillBeam();
//		pev->nextthink = gpGlobals->time + 0.01;
//
//		if (pCompare && (pCompare == pActivator))
//		{
//			pPlayer->m_iDefuseMeter = -50;
//			pPlayer->m_flNextDefuse = 0.5f;
//		}
//		else
//		{
//			pPlayer->m_iDefuseMeter = 0;
//		}
//		return;
//	}
//}
//*/
//
//void CTripmineGrenade::WarningThink(void)
//{
//	// play warning sound
//	// EMIT_SOUND( ENT(pev), CHAN_VOICE, "buttons/Blip2.wav", 1.0, ATTN_NORM );
//
//	// set to power up
//	SetThink(&CTripmineGrenade::PowerupThink);
//	pev->nextthink = gpGlobals->time + 1.0;
//}
//
//
//void CTripmineGrenade::PowerupThink(void)
//{
//	TraceResult tr;
//
//	if (m_hOwner == NULL)
//	{
//		// find an owner
//		edict_t* oldowner = pev->owner;
//		pev->owner = NULL;
//		UTIL_TraceLine(pev->origin + m_vecDir * 8, pev->origin - m_vecDir * 32, dont_ignore_monsters, ENT(pev), &tr);
//		/*
//		if (tr.fStartSolid || (oldowner && tr.pHit == oldowner))
//		{
//			pev->owner = oldowner;
//			m_flPowerUp += 0.1;
//			pev->nextthink = gpGlobals->time + 0.1;
//			return;
//		}
//		*/
//		if (tr.flFraction < 1.0)
//		{
//			pev->owner = tr.pHit;
//			m_hOwner = CBaseEntity::Instance(pev->owner);
//			m_posOwner = m_hOwner->pev->origin;
//			m_angleOwner = m_hOwner->pev->angles;
//		}
//		else
//		{
//			STOP_SOUND(ENT(pev), CHAN_VOICE, "weapons/tripmine/plant.wav");
//			STOP_SOUND(ENT(pev), CHAN_BODY, "weapons/tripmine/charge.wav");
//			SetThink(&CBaseEntity::SUB_Remove);
//			pev->nextthink = gpGlobals->time + 0.1;
//			ALERT(at_console, "WARNING:Tripmine at %.0f, %.0f, %.0f removed\n", pev->origin.x, pev->origin.y, pev->origin.z);
//			KillBeam();
//			return;
//		}
//	}
//
//	/*
//	else if (m_posOwner != m_hOwner->pev->origin || m_angleOwner != m_hOwner->pev->angles)
//	{
//		// disable
//		STOP_SOUND( ENT(pev), CHAN_VOICE, "weapons/tripmine/plant.wav" );
//		STOP_SOUND( ENT(pev), CHAN_BODY, "weapons/tripmine/charge.wav" );
//		CBaseEntity *pMine = Create( "weapon_tripmine", pev->origin + m_vecDir * 24, pev->angles );
//		pMine->pev->spawnflags |= SF_NORESPAWN;
//
//		SetThink(&CBaseEntity::SUB_Remove );
//		KillBeam();
//		pev->nextthink = gpGlobals->time + 0.1;
//		return;
//	}
//	// ALERT( at_console, "%d %.0f %.0f %0.f\n", pev->owner, m_pOwner->pev->origin.x, m_pOwner->pev->origin.y, m_pOwner->pev->origin.z );
//	*/
//
//	if (!m_bArmed)
//	{
//		m_flPowerUp = gpGlobals->time + m_flArming;
//		pev->nextthink = gpGlobals->time + 0.1;
//		return;
//	}
//
//	if (gpGlobals->time > m_flPowerUp)
//	{
//		// make solid
//		pev->solid = SOLID_BBOX;
//		UTIL_SetOrigin(pev, pev->origin);
//
//		MakeBeam();
//
//		// play enabled sound
//		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "weapons/tripmine/ready.wav", 0.5, ATTN_NORM, 1.0, 75);
//
//		SetUse(&CTripmineGrenade::DefuseUse);
//	}
//	pev->nextthink = gpGlobals->time + 0.1;
//}
//
//
//
//void CTripmineGrenade::KillBeam(void)
//{
//	if (m_pBeam)
//	{
//		UTIL_Remove(m_pBeam);
//		m_pBeam = NULL;
//	}
//}
//
//
//void CTripmineGrenade::MakeBeam(void)
//{
//	TraceResult tr;
//
//	// ALERT( at_console, "serverflags %f\n", gpGlobals->serverflags );
//
//	UTIL_TraceLine(pev->origin, m_vecEnd, dont_ignore_monsters, ENT(pev), &tr);
//
//	m_flBeamLength = tr.flFraction;
//
//	if (CBaseEntity::Instance(tr.pHit)->IsPlayer())
//	{
//		pev->owner = m_pRealOwner;
//		pev->health = 0;
//		Killed(VARS(pev->owner), GIB_NORMAL);
//		return;
//	}
//
//	// set to follow laser spot
//	if (m_pfnThink != &CTripmineGrenade::BeamBreakThink)
//	{
//		SetThink(&CTripmineGrenade::BeamBreakThink);
//		pev->nextthink = gpGlobals->time + 0.1;
//	}
//
//	Vector vecTmpEnd = EyePosition() + m_vecDir * 2048 * m_flBeamLength;
//
//	// Create beam if it doesn't exist
//	if (!m_pBeam)
//		m_pBeam = CBeam::BeamCreate(g_pModelNameLaser, 10);
//
//	m_pBeam->PointEntInit(vecTmpEnd, entindex());
//	//m_pBeam->HoseInit( pev->origin, vecTmpEnd );
//	m_pBeam->SetColor(255, 15, 0);
//	m_pBeam->SetScrollRate(255);
//	m_pBeam->SetBrightness(64);
//}
//
//
//void CTripmineGrenade::BeamBreakThink(void)
//{
//	if (m_pBeam)
//		MakeBeam();
//
//	BOOL bBlowup = FALSE;
//	TraceResult tr;
//
//	// HACKHACK Set simple box using this really nice global!
//	gpGlobals->trace_flags = FTRACE_SIMPLEBOX;
//	UTIL_TraceLine(pev->origin, m_vecEnd, dont_ignore_monsters, ENT(pev), &tr);
//
//	// ALERT( at_console, "%f : %f\n", tr.flFraction, m_flBeamLength );
//
//	// respawn detect. 
//	if (!m_pBeam)
//	{
//		MakeBeam();
//		if (tr.pHit)
//			m_hOwner = CBaseEntity::Instance(tr.pHit);	// reset owner too
//	}
//
//	if (fabs(m_flBeamLength - tr.flFraction) > 0.001 /*0.001*/)
//	{
//		bBlowup = TRUE;
//	}
//	else
//	{
//		if (m_hOwner == NULL)
//			bBlowup = TRUE;
//		else if (m_posOwner != m_hOwner->pev->origin)
//			bBlowup = TRUE;
//		else if (m_angleOwner != m_hOwner->pev->angles)
//			bBlowup = TRUE;
//	}
//
//	if (pev->aiment)
//	{
//		if (!CBaseEntity::Instance(pev->aiment))
//		{
//			pev->movetype = MOVETYPE_FLY;
//			pev->aiment = NULL;
//			bBlowup = TRUE;
//			return;
//		}
//	}
//
//	if (bBlowup)
//	{
//		// a bit of a hack, but all CGrenade code passes pev->owner along to make sure the proper player gets credit for the kill
//		// so we have to restore pev->owner from pRealOwner, because an entity's tracelines don't strike it's pev->owner which meant
//		// that a player couldn't trigger his own tripmine. Now that the mine is exploding, it's safe the restore the owner so the 
//		// CGrenade code knows who the explosive really belongs to.
//		pev->owner = m_pRealOwner;
//		pev->health = 0;
//		Killed(VARS(pev->owner), GIB_NORMAL);
//		return;
//	}
//
//	pev->nextthink = gpGlobals->time + 0.1;
//}
//
//int CTripmineGrenade::TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int iDamageId)
//{
//	if (gpGlobals->time < m_flPowerUp && flDamage < pev->health)
//	{
//		// disable
//		// Create( "weapon_tripmine", pev->origin + m_vecDir * 24, pev->angles );
//		SetThink(&CBaseEntity::SUB_Remove);
//		pev->nextthink = gpGlobals->time + 0.1;
//		KillBeam();
//		return FALSE;
//	}
//
//	return CGrenade::TakeDamage(pevInflictor, pevAttacker, flDamage, iDamageId);
//}
//
//void CTripmineGrenade::Killed(entvars_t* pevAttacker, int iGib)
//{
//	pev->takedamage = DAMAGE_NO;
//
//	if (pevAttacker && (pevAttacker->flags & FL_CLIENT))
//	{
//		// some client has destroyed this mine, he'll get credit for any kills
//		pev->owner = ENT(pevAttacker);
//	}
//
//	SetThink(&CTripmineGrenade::DelayDeathThink);
//	pev->nextthink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.3);
//
//	EMIT_SOUND(ENT(pev), CHAN_BODY, "common/null.wav", 0.5, ATTN_NORM); // shut off chargeup
//}
//
//
//void CTripmineGrenade::DelayDeathThink(void)
//{
//	KillBeam();
//	TraceResult tr;
//	UTIL_TraceLine(pev->origin + m_vecDir * 8, pev->origin - m_vecDir * 64, dont_ignore_monsters, ENT(pev), &tr);
//
//	Explode(&tr, ID_DMG_GENERIC);
//}
//#endif
//
//// Tripmine Weapon Code
//
//LINK_ENTITY_TO_CLASS(weapon_tripmine, CTripmine);
//
//BOOL CTripmine::HasAmmo(void)
//{
//	return HasPrimaryAmmo(TRUE);
//}
//
//void CTripmine::UpdateBodygroup(void)
//{
//	if (m_pPlayer)
//	{
//		m_pPlayer->pev->viewmodelbody = 0;
//		m_pPlayer->pev->viewmodelskin = m_iTimer + 5 - (int)m_bTimed * 5;
//		m_pPlayer->pev->playmodelbody = 0;
//		m_pPlayer->pev->playmodelskin = m_iTimer + 5 - (int)m_bTimed * 5;
//	}
//
//	if (m_pPlayer)
//		pev->body = (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] > 0) ? 0 : 1;
//	else
//		pev->body = 0;
//
//	pev->skin = m_iTimer + 5 - (int)m_bTimed * 5;
//}
//
//void CTripmine::ItemPostFrame(void)
//{
//	UpdateBodygroup();
//
//	// Redraw portion of the tripmine
//	if (m_flRedraw > 0)
//	{
//		//ALERT( at_console, "m_flRedraw = %.2f\n", m_flRedraw );
//		m_flRedraw -= gpGlobals->frametime;
//		if (m_flRedraw <= 0)
//		{
//			m_flRedraw = -1;
//			if (m_pPlayer && HasPrimaryAmmo(TRUE))
//			{
//				SendWeaponAnim(TRIPMINE_DRAW);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 0.70;
//			}
//			else
//			{
//				m_flRedraw = 0.1;
//				SendWeaponAnim(TRIPMINE_NULL);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.00;
//			}
//		}
//	}
//
//	CBasePlayerWeapon::ItemPostFrame();
//}
//
//int CTripmine::HUDIcon(void)
//{
//	return 99;
//}
//
//int CTripmine::HUDActiveIcon(void)
//{
//	return 100;
//}
//
//int CTripmine::ModeIcon(void)
//{
//	if (m_bTimed)
//		return 67;
//	else
//		return 68;
//}
//
//int CTripmine::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CTripmine::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CTripmine::SmallIcon(void)
//{
//	return 56;
//}
//
//void CTripmine::PickupSound(void)
//{
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/tripmine/pickup.wav", 1, ATTN_NORM);
//}
//
//void CTripmine::Spawn(void)
//{
//	Precache();
//	m_iId = WEAPON_TRIPMINE;
//	SET_MODEL(ENT(pev), "models/w_tripmine.mdl");
//	pev->frame = 0;
//	pev->sequence = 1;
//	//ResetSequenceInfo( );
//	pev->framerate = 0;
//
//	FallInit();// get ready to fall down
//
//	m_iDefaultAmmo = TRIPMINE_DEFAULT_GIVE;
//}
//
//void CTripmine::Precache(void)
//{
//	PRECACHE_MODEL("models/v_tripmine.mdl");
//	PRECACHE_MODEL("models/w_tripmine.mdl");
//	PRECACHE_MODEL("models/p_tripmine.mdl");
//	UTIL_PrecacheOther("monster_tripmine");
//	PRECACHE_SOUND("weapons/tripmine/pickup.wav");
//	PRECACHE_SOUND("weapons/tripmine/arm.wav");
//
//	m_usTripFire = PRECACHE_EVENT(1, "events/tripfire.sc");
//}
//
//int CTripmine::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "tripmine";
//	p->iMaxAmmo1 = TRIPMINE_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = WEAPON_NOCLIP_RELOAD;
//	p->iSlot = WEAPON_BUCKET_TRAPS;
//	p->iPosition = WEAPON_TRIPMINE_SLOT;
//	p->iId = m_iId = WEAPON_TRIPMINE;
//	p->iWeight = TRIPMINE_WEIGHT;
//	p->iFlags = ITEM_FLAG_NOAUTORELOAD;
//
//	return 1;
//}
//
//BOOL CTripmine::Deploy(void)
//{
//	UpdateBodygroup();
//	UnsetIdle();
//
//	if (!HasPrimaryAmmo(TRUE))
//	{
//		return DefaultDeploy("models/v_tripmine.mdl", "models/p_tripmine.mdl", TRIPMINE_NULL, "trip");
//	}
//	else
//	{
//		m_flRedraw = -1;
//		return DefaultDeploy("models/v_tripmine.mdl", "models/p_tripmine.mdl", TRIPMINE_DRAW, "trip");
//	}
//}
//
//
//void CTripmine::Holster(int skiplocal /* = 0 */)
//{
//	UnsetIdle();
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//
//	if (HasInfinitePrimaryAmmo())
//		SendWeaponAnim(TRIPMINE_NULL);
//	else
//		SendWeaponAnim(TRIPMINE_HOLSTER);
//
//}
//
//void CTripmine::PrimaryAttack(void)
//{
//	if (!HasPrimaryAmmo(TRUE))
//		return;
//
//	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//	Vector vecAiming = gpGlobals->v_forward;
//
//	TraceResult tr;
//
//	UTIL_TraceLine(vecSrc, vecSrc + vecAiming * 128, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
//
//	int flags;
//#ifdef CLIENT_WEAPONS
//	flags = FEV_NOTHOST;
//#else
//	flags = 0;
//#endif
//	if (tr.flFraction < 1.0)
//	{
//		CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);
//		if (pEntity && !(pEntity->pev->flags & FL_CONVEYOR))
//		{
//			// Needed for server side animation saving
//			int iAnim = m_pPlayer->pev->savedvanim = RANDOM_LONG(TRIPMINE_PLACE, TRIPMINE_PLACE2);
//			float flFrameRate = m_pPlayer->pev->savedvframerate = 1.0f;
//			byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//
//			PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usTripFire, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0, 0, 0, 0, 0, (float*)&g_vecZero, (float*)&g_vecZero,
//				iAnim, flFrameRate, byFrame);
//
//			Vector angles = UTIL_VecToAngles(tr.vecPlaneNormal);
//
//#ifndef CLIENT_DLL
//			CTripmineGrenade* pEnt = CTripmineGrenade::TripmineCreate(m_bTimed, tr.vecEndPos + tr.vecPlaneNormal * 8, angles, m_pPlayer->edict());
//			pEnt->m_flPowerUp = gpGlobals->time + GetArmingTime();
//			pEnt->m_flArming = GetArmingTime();
//			pEnt->pev->skin = m_pPlayer->pev->viewmodelskin;
//			pEnt->pev->aiment = tr.pHit;
//			pEnt->pev->movetype = MOVETYPE_COMPOUND;
//			// Adjust angle if the Tripmine is planted on either ceiling floor or floor, otherwise, keep to vector plane normal
//			if ((int)(pEnt->pev->angles).x - 90 == 0 || (int)(pEnt->pev->angles).x - 270 == 0)
//				pEnt->pev->angles.z = m_pPlayer->pev->angles.y - 180;
//#endif
//
//			if (!HasInfinitePrimaryAmmo())
//				m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;
//
//			// player "shoot" animation
//			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//			m_flNextTertiaryAttack = m_flNextSecondaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.38 + 0.53;
//			m_flRedraw = 0.38;
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);
//		}
//	}
//
//}
//
//void CTripmine::SecondaryAttack(void)
//{
//	SendWeaponAnim(TRIPMINE_TIMER);
//	if (m_iTimer >= 4)
//		m_iTimer = 0;
//	else
//		m_iTimer++;
//
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/tripmine/arm.wav", 1.0, ATTN_NORM);
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.08;
//
//	UnsetIdle();
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
//}
//
//void CTripmine::TertiaryAttack(void)
//{
//	SendWeaponAnim(TRIPMINE_TIMER);
//	if (m_iTimer <= 0)
//		m_iTimer = 4;
//	else
//		--m_iTimer;
//
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/tripmine/arm.wav", 1.0, ATTN_NORM);
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.08;
//
//	UnsetIdle();
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
//}
//
//void CTripmine::Reload(void)
//{
//	if (m_flNextPrimaryAttack >= UTIL_WeaponTimeBase() ||
//		m_flNextTertiaryAttack >= UTIL_WeaponTimeBase() ||
//		m_flNextSecondaryAttack >= UTIL_WeaponTimeBase())
//		return;
//
//	SendWeaponAnim(TRIPMINE_TIMER);
//
//	if (m_bTimed)
//		m_bTimed = FALSE;
//	else
//		m_bTimed = TRUE;
//
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/tripmine/arm.wav", 1.0, ATTN_NORM);
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.08;
//
//	UnsetIdle();
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
//}
//
//void CTripmine::WeaponIdle(void)
//{
//	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase())
//		return;
//
//	// Idle section
//	if (!HasPrimaryAmmo(TRUE) && !HasInfinitePrimaryAmmo())
//	{
//		return;
//	}
//	else
//	{
//		// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//		if (RANDOM_LONG(0, 99) <= 5)
//		{
//			UpdateBodygroup();
//			UnsetIdle();
//
//			if (RANDOM_LONG(0, 1))
//			{
//				SendWeaponAnim(TRIPMINE_FIDGET);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.36;
//			}
//			else
//			{
//				SendWeaponAnim(TRIPMINE_IDLE1);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.03;
//			}
//		}
//		else
//		{
//			// Ensure at least two successful loops
//			if (!IsIdle())
//			{
//				UpdateBodygroup();
//				SendWeaponAnim(TRIPMINE_IDLE2);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.03 * 2;
//				SetIdle();
//			}
//			else
//			{
//				// Only perform a single loop in this case
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.03;
//			}
//		}
//	}
//}