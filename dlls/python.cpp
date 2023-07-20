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
//
//#include "extdll.h"
//#include "util.h"
//#include "cbase.h"
//#include "weapons.h"
//#include "monsters.h"
//#include "player.h"
//#include "gamerules.h"
//
//LINK_ENTITY_TO_CLASS(weapon_python, CPython);
//LINK_ENTITY_TO_CLASS(weapon_357, CPython); // Added for compatibility
//
//int CPython::PrimaryAmmoIndex(void)
//{
//	return m_iPrimaryAmmoType;
//}
//
//void CPython::ItemPostFrame(void)
//{
//	UpdateSpot();
//	UpdateBodygroup();
//
//	if (m_iRecoil > 0)
//	{
//		if (m_flNextRecoil <= gpGlobals->time)
//		{
//			--m_iRecoil;
//		}
//
//		if (m_iRecoil == 0)
//		{
//			m_flNextRecoil = -1;
//		}
//	}
//
//	CBasePlayerWeapon::ItemPostFrame();
//}
//
//void CPython::UpdateBodygroup(void)
//{
//	if (m_pPlayer)
//		m_pPlayer->pev->viewmodelbody = m_pPlayer->pev->playmodelbody = HasWeaponUpgrades(UPGRADE_PYTHONS);
//
//	pev->body = HasWeaponUpgrades(UPGRADE_PYTHONS);
//}
//
//BOOL CPython::IsUseable(void)
//{
//	if (m_iClip > 0 || m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] > 0 || m_pPlayer->m_flInfiniteAmmo > 0)
//		return TRUE;
//	else
//		return FALSE;
//}
//
//int CPython::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "357";
//	p->iMaxAmmo1 = _357_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = PYTHON_MAX_CLIP;
//	p->iFlags = ITEM_FLAG_DUPLICATION;
//	p->iSlot = WEAPON_BUCKET_HANDGUNS;
//	p->iPosition = WEAPON_PYTHON_SLOT;
//	p->iId = m_iId = WEAPON_PYTHON;
//	p->iWeight = PYTHON_WEIGHT;
//
//	return 1;
//}
//
//void CPython::PickupSound(void)
//{
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/python/pickup.wav", 1, ATTN_NORM);
//}
//
//int CPython::HUDIcon(void)
//{
//	if (HasWeaponUpgrades(UPGRADE_PYTHONS))
//		return 27;
//
//	return 25;
//}
//
//int CPython::HUDActiveIcon(void)
//{
//	if (HasWeaponUpgrades(UPGRADE_PYTHONS))
//		return 28;
//
//	return 26;
//}
//
//int CPython::ModeIcon(void)
//{
//	// Check for scope upgrade first
//	if (HasWeaponUpgrades(UPGRADE_PYTHONS))
//	{
//		if (m_fSpotActive)
//			return 8;
//	}
//
//	return 17;
//}
//
//int CPython::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CPython::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CPython::SmallIcon(void)
//{
//	if (HasWeaponUpgrades(UPGRADE_PYTHONS))
//		return 18;
//
//	return 16;
//}
//
//void CPython::Spawn(void)
//{
//	pev->classname = MAKE_STRING("weapon_python"); // hack to allow for old names
//	Precache();
//	m_iId = WEAPON_PYTHON;
//	SET_MODEL(ENT(pev), "models/w_python.mdl");
//	m_iDefaultAmmo = PYTHON_DEFAULT_GIVE;
//	FallInit();// get ready to fall down.
//}
//
//BOOL CPython::IsZoomActive()
//{
//	return m_pPlayer && (m_pPlayer->pev->fov != 0.0f);
//}
//
//void CPython::Precache(void)
//{
//	PRECACHE_MODEL("models/v_python.mdl");
//	PRECACHE_MODEL("models/w_python.mdl");
//	PRECACHE_MODEL("models/p_python.mdl");
//
//	PRECACHE_SOUND("weapons/python/fire.wav");
//	PRECACHE_SOUND("weapons/python/dry.wav");
//	PRECACHE_SOUND("weapons/python/laseroff.wav");
//	PRECACHE_SOUND("weapons/python/laseron.wav");
//	PRECACHE_SOUND("weapons/python/pickup.wav");
//
//	UTIL_PrecacheOther("laser_spot");
//
//	m_usFirePython = PRECACHE_EVENT(1, "events/python.sc");
//}
//
//BOOL CPython::Deploy(void)
//{
//	UpdateBodygroup();
//	UnsetIdle();
//	UnsetSemiFired();
//	BOOL deployResult = DefaultDeploy("models/v_python.mdl", "models/p_python.mdl", PYTHON_DRAW, "python");
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = m_flNextReload = UTIL_WeaponTimeBase() + 0.54;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 0.7;
//	return deployResult;
//}
//
//void CPython::Holster(int skiplocal)
//{
//	UpdateBodygroup();
//	SendWeaponAnim(PYTHON_HOLSTER);
//
//#ifndef CLIENT_DLL
//	if (m_pSpot)
//	{
//		m_pSpot->Suspend(2.0);
//		m_pSpot->Killed(NULL, GIB_NORMAL);
//		m_pSpot = NULL;
//	}
//#endif
//
//	UnsetSemiFired();
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 0.7;
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = m_flNextReload = UTIL_WeaponTimeBase() + 1.5;
//
//	m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 0;
//
//	UnsetIdle();
//}
//
//void CPython::UpdateSpot(void)
//{
//	if (m_pPlayer)
//	{
//		if (m_pPlayer->m_fWeaponDeployDelay > 0)
//			return;
//	}
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
//}
//
//Vector CPython::ConeRecoil(int shots)
//{
//	if (shots <= 0)
//		return VECTOR_CONE_0DEGREES;
//	else if (shots >= 1 && shots < 4)
//		return VECTOR_CONE_1DEGREES;
//	else if (shots >= 4 && shots < 8)
//		return VECTOR_CONE_2DEGREES;
//	else if (shots >= 8 && shots < 16)
//		return VECTOR_CONE_4DEGREES;
//	else
//		return VECTOR_CONE_8DEGREES;
//}
//
//void CPython::PrimaryAttack(void)
//{
//	if (HasSemiFired())
//		return;
//
//	if (HasWeaponUpgrades(UPGRADE_PYTHONS))
//	{
//		if (m_fSpotActive)
//			ShootIt(ConeRecoil(max(0, m_iRecoil - 5)), 0.60, FALSE, 0);
//		else
//			ShootIt(ConeRecoil(m_iRecoil + 1), 0.60, FALSE, 1);
//	}
//	else
//	{
//		ShootIt(ConeRecoil(m_iRecoil), 0.60, FALSE, 1);
//	}
//
//	if (m_iRecoil < 18)
//		m_iRecoil++;
//}
//
//void CPython::SecondaryAttack(void)
//{
//	if (HasSemiFired())
//		return;
//
//	if (HasWeaponUpgrades(UPGRADE_PYTHONS))
//	{
//		if (m_fSpotActive)
//			ShootIt(ConeRecoil(max(0, m_iRecoil - 5)), 0.30, TRUE, 2);
//		else
//			ShootIt(ConeRecoil(m_iRecoil + 1), 0.20, TRUE, 3);
//	}
//	else
//	{
//		ShootIt(ConeRecoil(m_iRecoil), 0.20, TRUE, 3);
//	}
//
//	if (m_iRecoil < 18)
//		m_iRecoil += 3;
//}
//
//void CPython::TertiaryAttack(void)
//{
//	if (HasWeaponUpgrades(UPGRADE_PYTHONS))
//	{
//#ifndef CLIENT_DLL
//		ActivateLaser();
//#endif
//	}
//}
//
//void CPython::ActivateLaser(void)
//{
//	if (m_fSpotActive)
//	{
//		EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/python/laseroff.wav", 1, ATTN_NORM);
//		m_fSpotActive = FALSE;
//	}
//	else
//	{
//		EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/python/laseron.wav", 1, ATTN_NORM);
//		m_fSpotActive = TRUE;
//	}
//
//	SendWeaponAnim(PYTHON_SIGHT);
//
//#ifndef CLIENT_DLL
//	if (!m_fSpotActive && m_pSpot)
//	{
//		m_pSpot->Killed(NULL, GIB_NORMAL);
//		m_pSpot = NULL;
//	}
//#endif
//
//	m_pPlayer->pev->fov = m_pPlayer->m_iFOV = IsZoomActive() ? 0 : 20;
//
//	// Used to be 1.25
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.75;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.75;
//	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.75;
//	m_flNextReload = UTIL_WeaponTimeBase() + 0.75;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.04;
//	UnsetIdle();
//	UnsetSemiFired();
//}
//
//void CPython::ShootIt(Vector vecShootCone, float flCycle, BOOL fFastAnim, int iPunchAngle)
//{
//	// don't fire underwater
//	if (m_pPlayer->pev->waterlevel == 3 || (m_iClip <= 0 && m_pPlayer->m_flInfiniteAmmo < 2))
//	{
//		EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/python/dry.wav", 0.8, ATTN_NORM);
//		m_flNextPrimaryAttack = 0.15;
//		m_flNextSecondaryAttack = 0.15;
//		m_flNextTertiaryAttack = 0.15;
//		return;
//	}
//
//	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
//	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;
//
//	if (m_pPlayer->m_flInfiniteAmmo < 2)
//		m_iClip--;
//
//	m_pPlayer->pev->effects = (int)(m_pPlayer->pev->effects) | EF_MUZZLEFLASH;
//
//	// player "shoot" animation
//	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//
//	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
//
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//	Vector vecAiming;
//	if (HasWeaponUpgrades(UPGRADE_PYTHONS))
//		vecAiming = m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
//	else
//		vecAiming = m_pPlayer->GetAutoaimVector(AUTOAIM_5DEGREES);
//
//	Vector vecDir;
//	vecDir = m_pPlayer->FireBullets(1, vecSrc, vecAiming, vecShootCone, 8192, BULLET_357, 0, 0, m_pPlayer->pev, m_pPlayer->random_seed);
//
//	int flags;
//
//#if defined( CLIENT_WEAPONS )
//	flags = FEV_NOTHOST;
//#else
//	flags = 0;
//#endif
//
//	int iAnim = m_pPlayer->pev->savedvanim = (fFastAnim ? PYTHON_FIRE2 : PYTHON_FIRE1);
//	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
//	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//
//	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usFirePython, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, vecDir.x, vecDir.y, m_pPlayer->pev->viewmodelbody, iPunchAngle, 0, FALSE, (float*)&g_vecZero, (float*)&g_vecZero,
//		iAnim, flFramerate, byFrame);
//
//	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 && m_pPlayer->m_flInfiniteAmmo < 1)
//		// HEV suit - indicate out of ammo condition
//		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
//
//#ifndef CLIENT_DLL
//	if (m_pSpot)
//	{
//		m_pSpot->Suspend(flCycle);
//	}
//#endif
//
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + flCycle;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycle;
//	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + flCycle;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + flCycle;
//
//	if (fFastAnim)
//		m_flNextReload = UTIL_WeaponTimeBase() + 1.03;
//	else
//		m_flNextReload = UTIL_WeaponTimeBase() + 1.0;
//	UnsetIdle();
//	SetSemiFired();
//
//	m_flNextRecoil = gpGlobals->time + 0.8;
//}
//
//void CPython::Reload(void)
//{
//	UpdateBodygroup();
//	if (HasPrimaryAmmo(TRUE))
//		return;
//
//#ifndef CLIENT_DLL
//	if (m_fSpotActive && m_pSpot)
//		ActivateLaser();
//#endif
//	m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 0;
//
//	m_pPlayer->SetAnimation(PLAYER_RELOAD);
//	DefaultReload(6, PYTHON_RELOAD, 3, 4.0);
//
//	UnsetSemiFire();
//}
//
//
//void CPython::WeaponIdle(void)
//{
//	UpdateBodygroup();
//	UpdateSpot();
//
//	if (HasSemiFired() && m_flNextPrimaryAttack <= UTIL_WeaponTimeBase())
//	{
//		UnsetSemiFired();
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//	}
//
//	ResetEmptySound();
//
//	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
//
//	if (m_flNextWeaponIdle <= UTIL_WeaponTimeBase())
//	{
//		// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//		if (RANDOM_LONG(0, 99) <= 5)
//		{
//			UpdateBodygroup();
//			SendWeaponAnim(PYTHON_FIDGET);
//			UnsetIdle();
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.7;
//		}
//		else
//		{
//			// Ensure at least two successful loops
//			if (!IsIdle())
//			{
//				int rAnim = RANDOM_LONG(PYTHON_IDLE1, PYTHON_IDLE2);
//				UpdateBodygroup();
//				SendWeaponAnim(rAnim);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.67 * 2; // Minimum plus half of difference
//				SetIdle();
//			}
//			else
//			{
//				// Only perform a single loop in this case
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.67; // Minimum plus half of difference
//			}
//		}
//	}
//}
//
//class CPythonAmmo : public CBasePlayerAmmo
//{
//public:
//	CPythonAmmo(void)
//	{
//		m_szPickupSound = MAKE_STRING("weapons/python/ammo.wav");
//		m_szAmmoType = MAKE_STRING("357");
//		m_szModel = MAKE_STRING("models/ammo_357.mdl");
//		m_iAmmoAmount = PYTHON_MAX_CLIP;
//	}
//};
//LINK_ENTITY_TO_CLASS(ammo_357, CPythonAmmo);
//
//// Little Badis: Scope Upgrade for the Python
//class CPythonScope : public CPython
//{
//	void Spawn(void)
//	{
//		CPython::Spawn();
//		pev->body = 1;
//		m_fWeaponUpgrades |= (1 << UPGRADE_PYTHONS);
//		pev->classname = MAKE_STRING("weapon_python");
//	}
//};
//LINK_ENTITY_TO_CLASS(weapon_pythonscope, CPythonScope);
