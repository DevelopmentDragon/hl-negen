///***
//*
//*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
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
//#if !defined( OEM_BUILD )
//
//#include "extdll.h"
//#include "util.h"
//#include "cbase.h"
//#include "monsters.h"
//#include "weapons.h"
//#include "nodes.h"
//#include "player.h"
//#include "gamerules.h"
//
//LINK_ENTITY_TO_CLASS(weapon_rpg, CRpg);
//
//#ifndef CLIENT_DLL
//
//LINK_ENTITY_TO_CLASS(rpg_rocket, CRpgRocket);
//
////=========================================================
////=========================================================
//CRpgRocket* CRpgRocket::CreateRpgRocket(Vector vecOrigin, Vector vecAngles, CBaseEntity* pOwner, CRpg* pLauncher)
//{
//	CRpgRocket* pRocket = GetClassPtr((CRpgRocket*)NULL);
//
//	UTIL_SetOrigin(pRocket->pev, vecOrigin);
//	pRocket->pev->angles = vecAngles;
//	pRocket->Spawn();
//	pRocket->SetTouch(&CRpgRocket::RocketTouch);
//	pRocket->m_pLauncher = pLauncher;// remember what RPG fired me. 
//	if (pLauncher->SpotEnabled())
//	{
//		pRocket->m_pLauncher->m_cActiveRockets++;// register this missile as active for the launcher
//	}
//
//	if (pLauncher)
//		pRocket->m_pLauncher->m_pRocket = (CBaseEntity*)pRocket;
//
//	pRocket->pev->owner = pOwner->edict();
//
//	return pRocket;
//}
//
////=========================================================
////=========================================================
//void CRpgRocket::Spawn(void)
//{
//	Precache();
//	// motor
//	pev->movetype = MOVETYPE_BOUNCE;
//	pev->solid = SOLID_BBOX;
//
//	SET_MODEL(ENT(pev), "models/rpgrocket.mdl");
//	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
//	UTIL_SetOrigin(pev, pev->origin);
//
//	pev->classname = MAKE_STRING("rpg_rocket");
//
//	SetThink(&CRpgRocket::IgniteThink);
//	SetTouch(&CRpgRocket::ExplodeTouch);
//
//	pev->angles.x -= 30;
//	UTIL_MakeVectors(pev->angles);
//	pev->angles.x = -(pev->angles.x + 30);
//
//	pev->velocity = gpGlobals->v_forward * 250;
//	pev->gravity = 0.5;
//
//	pev->nextthink = gpGlobals->time + 0.4;
//
//	pev->dmg = gSkillData.plrDmgRpgBlast;
//	m_iGrenadeType = TYPE_RPGROCKET;
//}
//
////=========================================================
////=========================================================
//void CRpgRocket::RocketTouch(CBaseEntity* pOther)
//{
//	if (m_pLauncher)
//	{
//		// my launcher is still around, tell it I'm dead.
//		m_pLauncher->m_cActiveRockets--;
//		m_pLauncher->m_pRocket = NULL;
//	}
//
//	STOP_SOUND(edict(), CHAN_VOICE, "weapons/rpg/fly.wav");
//	ExplodeTouch(pOther);
//}
//
////=========================================================
////=========================================================
//
//void CRpgRocket::Precache(void)
//{
//	PRECACHE_MODEL("models/rpgrocket.mdl");
//	m_iTrail = PRECACHE_MODEL("sprites/smoke.spr");
//	PRECACHE_SOUND("weapons/rpg/fly.wav");
//	PRECACHE_SOUND("weapons/rpg/explode.wav");
//	PRECACHE_SOUND("weapons/rpg/ignite.wav");
//}
//
//
//void CRpgRocket::IgniteThink(void)
//{
//	// pev->movetype = MOVETYPE_TOSS;
//
//	pev->movetype = MOVETYPE_FLY;
//	pev->effects |= EF_LIGHT;
//
//	// make rocket sound
//	EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/rpg/ignite.wav", 1, 0.5);
//	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/rpg/fly.wav", 1, 0.5);
//
//	// rocket trail
//	MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
//
//	WRITE_BYTE(TE_BEAMFOLLOW);
//	WRITE_SHORT(entindex());	// entity
//	WRITE_SHORT(m_iTrail);	// model
//	WRITE_BYTE(40); // life
//	WRITE_BYTE(5);  // width
//	WRITE_BYTE(224);   // r, g, b
//	WRITE_BYTE(224);   // r, g, b
//	WRITE_BYTE(255);   // r, g, b
//	WRITE_BYTE(255);	// brightness
//
//	MESSAGE_END();  // move PHS/PVS data sending into here (SEND_ALL, SEND_PVS, SEND_PHS)
//
//	m_flIgniteTime = gpGlobals->time;
//
//	// set to follow laser spot
//	SetThink(&CRpgRocket::FollowThink);
//	pev->nextthink = gpGlobals->time + 0.01;
//}
//
//
//void CRpgRocket::FollowThink(void)
//{
//	CBaseEntity* pOther = NULL;
//	Vector vecTarget;
//	Vector vecDir;
//	float flDist, flMax, flDot;
//	TraceResult tr;
//
//	UTIL_MakeAimVectors(pev->angles);
//
//	vecTarget = gpGlobals->v_forward;
//	flMax = 4096;
//
//	// Examine all entities within a reasonable radius
//	while ((pOther = UTIL_FindEntityByClassname(pOther, "laser_spot")) != NULL)
//	{
//		UTIL_TraceLine(pev->origin, pOther->pev->origin, dont_ignore_monsters, ENT(pev), &tr);
//		// ALERT( at_console, "%f\n", tr.flFraction );
//		if (tr.flFraction >= 0.90)
//		{
//			vecDir = pOther->pev->origin - pev->origin;
//			flDist = vecDir.Length();
//			vecDir = vecDir.Normalize();
//			flDot = DotProduct(gpGlobals->v_forward, vecDir);
//			if ((flDot > 0) && (flDist * (1 - flDot) < flMax))
//			{
//				flMax = flDist * (1 - flDot);
//				vecTarget = vecDir;
//			}
//		}
//	}
//
//	pev->angles = UTIL_VecToAngles(vecTarget);
//
//	// this acceleration and turning math is totally wrong, but it seems to respond well so don't change it.
//	float flSpeed = pev->velocity.Length();
//	if (gpGlobals->time - m_flIgniteTime < 1.0)
//	{
//		pev->velocity = pev->velocity * 0.2 + vecTarget * (flSpeed * 0.8 + 400);
//		if (pev->waterlevel == 3)
//		{
//			// go slow underwater
//			if (pev->velocity.Length() > 300)
//			{
//				pev->velocity = pev->velocity.Normalize() * 300;
//			}
//			UTIL_BubbleTrail(pev->origin - pev->velocity * 0.1, pev->origin, 4);
//		}
//		else
//		{
//			if (pev->velocity.Length() > 2000)
//			{
//				pev->velocity = pev->velocity.Normalize() * 2000;
//			}
//		}
//	}
//	else
//	{
//		if (pev->effects & EF_LIGHT)
//		{
//			pev->effects = 0;
//			STOP_SOUND(ENT(pev), CHAN_VOICE, "weapons/rpg/fly.wav");
//		}
//		pev->velocity = pev->velocity * 0.2 + vecTarget * flSpeed * 0.798;
//		if (pev->waterlevel == 0 && pev->velocity.Length() < 1500)
//		{
//			Detonate();
//		}
//	}
//	// ALERT( at_console, "%.0f\n", flSpeed );
//
//	pev->nextthink = gpGlobals->time + 0.01;
//}
//#endif
//
//void CRpg::UpdateBodygroup(void)
//{
//
//}
//
//void CRpg::ItemPostFrame(void)
//{
//	UpdateBodygroup();
//
//	if (m_pPlayer)
//	{
//		if (m_pPlayer->pev->button & IN_ATTACK3)
//			TertiaryAttack();
//	}
//
//	CBasePlayerWeapon::ItemPostFrame();
//	//ALERT( at_console, "%s\n", STRING(pev->model) );
//}
//
//
//void CRpg::Reload(void)
//{
//	int iResult;
//
//	if (m_iClip == 1)
//	{
//		// don't bother with any of this if don't need to reload.
//		return;
//	}
//
//	if (!HasPrimaryAmmo(TRUE))
//		return;
//
//	// because the RPG waits to autoreload when no missiles are active while  the LTD is on, the
//	// weapons code is constantly calling into this function, but is often denied because 
//	// a) missiles are in flight, but the LTD is on
//	// or
//	// b) player is totally out of ammo and has nothing to switch to, and should be allowed to
//	//    shine the designator around
//	//
//	// Set the next attack time into the future so that WeaponIdle will get called more often
//	// than reload, allowing the RPG LTD to be updated
//
//	if (SpotEnabled())
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
//	else
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.20;
//
//	if (m_cActiveRockets && SpotEnabled())
//	{
//		// no reloading when there are active missiles tracking the designator.
//		// ward off future autoreload attempts by setting next attack time into the future for a bit. 
//		return;
//	}
//
//	UnsetIdle();
//
//#ifndef CLIENT_DLL
//	if (m_pSpot && SpotEnabled())
//	{
//		m_pSpot->Suspend(2.1);
//	}
//#endif
//
//	UpdateBodygroup();
//	if (m_iClip == 0)
//		iResult = DefaultReload(RPG_MAX_CLIP, RPG_RELOAD, 2, 3.0, 2, 2.1, 0.0f);
//
//	m_pPlayer->SetAnimation(PLAYER_RELOAD);
//
//}
//
//void CRpg::Spawn()
//{
//	Precache();
//	m_iId = WEAPON_RPG;
//	SET_MODEL(ENT(pev), "models/w_rpg.mdl");
//	m_iDefaultAmmo = RPG_DEFAULT_GIVE;
//	FallInit();// get ready to fall down.
//}
//
//
//void CRpg::Precache(void)
//{
//	PRECACHE_MODEL("models/w_rpg.mdl");
//	PRECACHE_MODEL("models/v_rpg.mdl");
//	PRECACHE_MODEL("models/p_rpg.mdl");
//
//	UTIL_PrecacheOther("laser_spot");
//	UTIL_PrecacheOther("rpg_rocket");
//
//	PRECACHE_SOUND("weapons/rpg/fire.wav");
//	PRECACHE_SOUND("weapons/rpg/fly.wav");
//	PRECACHE_SOUND("weapons/rpg/dry.wav");
//	PRECACHE_SOUND("weapons/rpg/draw.wav");
//	PRECACHE_SOUND("weapons/rpg/holster.wav");
//	PRECACHE_SOUND("weapons/rpg/grabrocket.wav");
//	PRECACHE_SOUND("weapons/rpg/reload.wav");
//	PRECACHE_SOUND("weapons/rpg/laseroff.wav");
//	PRECACHE_SOUND("weapons/rpg/laseron.wav");
//	PRECACHE_SOUND("weapons/rpg/detonate.wav");
//
//	m_usRpg = PRECACHE_EVENT(1, "events/rpg.sc");
//}
//
//
//int CRpg::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "rockets";
//	p->iMaxAmmo1 = ROCKET_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = RPG_MAX_CLIP;
//	p->iSlot = WEAPON_BUCKET_LAUNCHERS;
//	p->iPosition = WEAPON_RPG_SLOT;
//	p->iId = m_iId = WEAPON_RPG;
//	//p->iFlags = ITEM_FLAG_NOAUTORELOAD;
//	p->iFlags = 0;
//	p->iWeight = RPG_WEIGHT;
//
//	return 1;
//}
//
//int CRpg::HUDIcon(void)
//{
//	return 81;
//}
//
//int CRpg::HUDActiveIcon(void)
//{
//	return 82;
//}
//
//int CRpg::ModeIcon(void)
//{
//	if (SpotEnabled())
//		return 18;
//
//	return 7;
//}
//
//int CRpg::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CRpg::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CRpg::SmallIcon(void)
//{
//	return 47;
//}
//
//BOOL CRpg::Deploy(void)
//{
//	UpdateBodygroup();
//	UnsetIdle();
//
//	if (m_iClip == 0)
//	{
//		return DefaultDeploy("models/v_rpg.mdl", "models/p_rpg.mdl", RPG_DRAW2, "rpg");
//	}
//
//	return DefaultDeploy("models/v_rpg.mdl", "models/p_rpg.mdl", RPG_DRAW, "rpg");
//}
//
//
//BOOL CRpg::CanHolster(void)
//{
//	if (SpotEnabled() && m_cActiveRockets)
//	{
//		// can't put away while guiding a missile.
//		return FALSE;
//	}
//	return TRUE;
//}
//
//void CRpg::Holster(int skiplocal /* = 0 */)
//{
//	if (CanHolster())
//	{
//		UnsetIdle();
//
//		UnsetReload();
//		m_flNextReload = -1.0f;
//
//		UpdateBodygroup();
//		if (m_iClip == 0)
//			SendWeaponAnim(RPG_HOLSTER2);
//		else
//			SendWeaponAnim(RPG_HOLSTER);
//
//#ifndef CLIENT_DLL
//		if (m_pSpot)
//		{
//			m_pSpot->Killed(NULL, GIB_NEVER);
//			m_pSpot = NULL;
//		}
//#endif
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//	}
//}
//
//void CRpg::PrimaryAttack()
//{
//	if (HasClipAmmo(TRUE))
//	{
//		m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
//		m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;
//
//#ifndef CLIENT_DLL
//		// player "shoot" animation
//		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//		UTIL_MakeVectors(m_pPlayer->pev->v_angle);
//		Vector vecSrc = m_pPlayer->GetGunPosition() + gpGlobals->v_forward * 16 + gpGlobals->v_right * 8 + gpGlobals->v_up * -8;
//
//		CRpgRocket* pRocket = CRpgRocket::CreateRpgRocket(vecSrc, m_pPlayer->pev->v_angle, m_pPlayer, this);
//
//		UTIL_MakeVectors(m_pPlayer->pev->v_angle);// RpgRocket::Create stomps on globals, so remake.
//		pRocket->pev->velocity = pRocket->pev->velocity + gpGlobals->v_forward * DotProduct(m_pPlayer->pev->velocity, gpGlobals->v_forward);
//#endif
//
//		// firing RPG no longer turns on the designator. ALT fire is a toggle switch for the LTD.
//		// Ken signed up for this as a global change (sjb)
//
//		int flags;
//#if defined( CLIENT_WEAPONS )
//		flags = FEV_NOTHOST;
//#else
//		flags = 0;
//#endif
//
//		int iAnim = m_pPlayer->pev->savedvanim = RPG_FIRE;
//		float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
//		byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//
//		PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usRpg, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0, m_pPlayer->pev->viewmodelbody, 0, 0, 0, (float*)&g_vecZero, (float*)&g_vecZero,
//			iAnim, flFramerate, byFrame);
//
//		if (HasInfiniteClipAmmo())
//			m_iClip--;
//
//		UnsetIdle();
//		//m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.5;
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
//	}
//	else
//	{
//		PlayEmptySound();
//	}
//	UpdateSpot();
//}
//
//
//void CRpg::SecondaryAttack()
//{
//	UpdateBodygroup();
//
//	if (SpotEnabled())
//	{
//		ActivateSpot();
//		EMIT_SOUND(ENT(pev), CHAN_WEAPON3, "weapons/rpg/laseroff.wav", 1, ATTN_NORM);
//	}
//	else
//	{
//		DeactivateSpot();
//		EMIT_SOUND(ENT(pev), CHAN_WEAPON3, "weapons/rpg/laseron.wav", 1, ATTN_NORM);
//	}
//
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.5;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.5;
//
//	if (m_pRocket)
//	{
//#ifndef CLIENT_DLL
//		CRpgRocket* pRocket = (CRpgRocket*)m_pRocket;
//		pRocket->Detonate();
//		m_pRocket = NULL;
//
//		if (m_cActiveRockets)
//			m_cActiveRockets--;
//
//		m_pRocket = NULL;
//#endif
//		EMIT_SOUND(ENT(pev), CHAN_WEAPON3, "weapons/rpg/detonate.wav", 1, ATTN_NORM);
//	}
//}
//
//void CRpg::WeaponIdle(void)
//{
//	UpdateSpot();
//
//	ResetEmptySound();
//
//	m_pPlayer->GetAutoaimVector(AUTOAIM_5DEGREES + AUTOAIM_2DEGREES);
//
//	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase())
//		return;
//
//	// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//	if (RANDOM_LONG(0, 99) <= 5)
//	{
//		UpdateBodygroup();
//		UnsetIdle();
//
//		if (m_iClip)
//			SendWeaponAnim(RPG_FIDGET);
//		else
//			SendWeaponAnim(RPG_FIDGET2);
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 6.06;
//	}
//	else
//	{
//		// Ensure at least two successful loops
//		if (!IsIdle())
//		{
//			UpdateBodygroup();
//			if (m_iClip)
//				SendWeaponAnim(RPG_IDLE);
//			else
//				SendWeaponAnim(RPG_IDLE2);
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 6.06 * 2;
//			SetIdle();
//		}
//		else
//		{
//			// Only perform a single loop in this case
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 6.06;
//		}
//	}
//}
//
//
///*
//void CRpg::UpdateSpot(void)
//{
//
//#ifndef CLIENT_DLL
//	if (m_fSpotActive)
//	{
//		if (!m_pSpot)
//		{
//			m_pSpot = CLaserSpot::CreateSpot();
//		}
//
//		UTIL_MakeVectors(m_pPlayer->pev->v_angle);
//		Vector vecSrc = m_pPlayer->GetGunPosition();;
//		Vector vecAiming = gpGlobals->v_forward;
//
//		TraceResult tr;
//		UTIL_TraceLine(vecSrc, vecSrc + vecAiming * 8192, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
//
//		UTIL_SetOrigin(m_pSpot->pev, tr.vecEndPos);
//	}
//#endif
//
//}
//*/
//
//
//class CRpgAmmo : public CBasePlayerAmmo
//{
//public:
//	CRpgAmmo(void)
//	{
//		m_szPickupSound = MAKE_STRING("weapons/rpg/ammo.wav");
//		m_szAmmoType = MAKE_STRING("rockets");
//		m_szModel = MAKE_STRING("models/ammo_rockets.mdl");
//		m_iAmmoAmount = RPG_MAX_CLIP;
//	}
//	void Spawn(void)
//	{
//		CBasePlayerAmmo::Spawn();
//		pev->classname = MAKE_STRING("ammo_rockets"); // Added for compatiblity
//	}
//};
//LINK_ENTITY_TO_CLASS(ammo_rockets, CRpgAmmo);
//LINK_ENTITY_TO_CLASS(ammo_rpgclip, CRpgAmmo);
//
//#endif
