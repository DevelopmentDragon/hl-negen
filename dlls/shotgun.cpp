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
//#include "monsters.h"
//#include "weapons.h"
//#include "nodes.h"
//#include "player.h"
//#include "gamerules.h"
//
//// special deathmatch shotgun spreads
//#define VECTOR_CONE_DM_SHOTGUN	Vector( 0.08716, 0.04362, 0.00  )// 10 degrees by 5 degrees
//#define VECTOR_CONE_DM_DOUBLESHOTGUN Vector( 0.17365, 0.04362, 0.00 ) // 20 degrees by 5 degrees
//
//LINK_ENTITY_TO_CLASS(weapon_shotgun, CShotgun);
//
////=========================================================
////=========================================================
//
//int CShotgun::PrimaryAmmoIndex(void)
//{
//	return m_iPrimaryAmmoType;
//}
//
//void CShotgun::Spawn()
//{
//	Precache();
//	m_iId = WEAPON_SHOTGUN;
//	SET_MODEL(ENT(pev), "models/w_shotgun.mdl");
//	pev->classname = MAKE_STRING("weapon_shotgun"); // hack to allow for old names
//	m_iClip = SHOTGUN_MAX_CLIP;
//	m_iDefaultAmmo = 0;
//	m_iDefaultAmmoSecondary = 0;
//	m_fHasPumped = TRUE;
//	m_fDoubleFire = FALSE;
//	FallInit();// get ready to fall
//}
//
//
//void CShotgun::Precache(void)
//{
//	PRECACHE_MODEL("models/v_shotgun.mdl");
//	PRECACHE_MODEL("models/w_shotgun.mdl");
//	PRECACHE_MODEL("models/p_shotgun.mdl");
//
//	m_iShell = PRECACHE_MODEL("models/shell_buckshot.mdl");// shotgun shell     
//
//	PRECACHE_SOUND("weapons/shotgun/fire_dbl.wav");//shotgun
//	PRECACHE_SOUND("weapons/shotgun/fire.wav");//shotgun
//	PRECACHE_SOUND("weapons/shotgun/pickup.wav"); // pickup
//	PRECACHE_SOUND("weapons/shotgun/drop.wav"); // pickup
//	PRECACHE_SOUND("weapons/shotgun/insert.wav");	// shotgun reload
//	PRECACHE_SOUND("weapons/shotgun/dry.wav"); // gun empty sound
//	PRECACHE_SOUND("weapons/shotgun/rapidon.wav"); // gun empty sound
//	PRECACHE_SOUND("weapons/shotgun/rapidoff.wav"); // gun empty sound
//
//	m_usSingleFire = PRECACHE_EVENT(1, "events/shotgun1.sc");
//	m_usDoubleFire = PRECACHE_EVENT(1, "events/shotgun2.sc");
//}
//
//// This function is not used for spread, but rather shooting vector director offset for rapid fire shots
//Vector CShotgun::ConeRecoil(void)
//{
//	// This how deviation is calculated for shooting vector director
//	return Vector(0.0f, VECTOR_CONE_5DEGREES.y, 0.0f);
//}
//
//void CShotgun::RecoilLogic(void)
//{
//	// Recoil Timer
//	if (m_flNextRecoil > 0.0f)
//	{
//		m_flNextRecoil -= gpGlobals->frametime;
//		if (m_flNextRecoil <= 0.0f)
//		{
//			m_flNextRecoil = -1.0f;
//		}
//	}
//	else
//	{
//		if (m_iRecoil > 0)
//		{
//			--m_iRecoil;
//			if (m_iRecoil > 0)
//				m_flNextRecoil = m_flIncrementalRecoilCooldown;
//		}
//	}
//}
//
//void CShotgun::ItemPostFrame(void)
//{
//	RecoilLogic();
//
//	UpdateBodygroup();
//
//	// Turn off rapid if player isn't holding the button
//	if (m_pPlayer)
//	{
//		if (!(m_pPlayer->pev->button & IN_ATTACK3) && m_bRapidFire)
//		{
//			m_bRapidFire = FALSE;
//			EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/shotgun/rapidoff.wav", 1, ATTN_NORM, 0, RANDOM_LONG(PITCH_NORM, PITCH_LOW));
//		}
//	}
//
//	if (CanPump() && HasWeaponStatusFlags(WEAPON_STF_UNPUMPED))
//	{
//		int flags;
//#if defined( CLIENT_WEAPONS )
//		flags = FEV_NOTHOST;
//#else
//		flags = 0;
//#endif
//		PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usDoubleFire, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0,
//			m_bRapidFire, (m_fDoubleFire == TRUE) ? 2 : 1, 0, 0, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0.0f, (byte)0);
//		// play pumping sound
//		SetWeaponStatusFlags(WEAPON_STF_UNPUMPED, FALSE);
//	}
//
//	// Reload Timer
//	if (m_flNextReload > 0.0)
//	{
//		m_flNextReload -= gpGlobals->frametime;
//		if (m_flNextReload <= 0.0)
//			m_flNextReload = -1;
//	}
//
//	CBasePlayerWeapon::ItemPostFrame();
//}
//
//void CShotgun::UpdateBodygroup(void)
//{
//	// Viewmodel
//	if (m_pPlayer)
//	{
//		m_pPlayer->pev->viewmodelbody = 0;
//		m_pPlayer->pev->viewmodelskin = m_iWeaponLooks;
//		m_pPlayer->pev->playmodelbody = 0;
//		m_pPlayer->pev->playmodelskin = m_iWeaponLooks;
//	}
//
//	pev->body = 0;
//	pev->skin = m_iWeaponLooks;
//}
//
//void CShotgun::PickupSound(void)
//{
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/shotgun/pickup.wav", 1, ATTN_NORM);
//}
//
//int CShotgun::HUDIcon(void)
//{
//	return 33;
//}
//
//int CShotgun::HUDActiveIcon(void)
//{
//	return 34;
//}
//
//int CShotgun::ModeIcon(void)
//{
//	if (m_bRapidFire)
//		return 14;
//
//	return -1;
//}
//
//int CShotgun::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CShotgun::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CShotgun::SmallIcon(void)
//{
//	return 21;
//}
//
//int CShotgun::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "buckshot";
//	p->iMaxAmmo1 = BUCKSHOT_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = SHOTGUN_MAX_CLIP;
//	p->iSlot = WEAPON_BUCKET_SHOTGUNS;
//	p->iPosition = WEAPON_SHOTGUN_SLOT;
//	p->iFlags = 0;
//	p->iId = m_iId = WEAPON_SHOTGUN;
//	p->iWeight = SHOTGUN_WEIGHT;
//
//	return 1;
//}
//
//BOOL CShotgun::CanHolster(void)
//{
//	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase() || m_flNextSecondaryAttack > UTIL_WeaponTimeBase())
//		return FALSE;
//	return TRUE;
//}
//
//BOOL CShotgun::Deploy()
//{
//	UnsetReload();
//	m_flNextReload = 0.6;
//
//	UpdateBodygroup();
//	BOOL result = DefaultDeploy("models/v_shotgun.mdl", "models/p_shotgun.mdl", SHOTGUN_DRAW, "shotgun");
//	UnsetIdle();
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//	return result;
//}
//
//void CShotgun::Holster(int skiplocal)
//{
//	UnsetReload();
//	m_flNextReload = 1.0;
//	UnsetIdle();
//	SendWeaponAnim(SHOTGUN_HOLSTER);
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//}
//
//void CShotgun::PrimaryAttack(void)
//{
//
//	// Semi-automatic shots
//	if (HasSemiFired())
//	{
//		return;
//	}
//
//	// don't fire underwater
//	if (m_pPlayer->pev->waterlevel == 3)
//	{
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/shotgun/dry.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.15;
//		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.15;
//		return;
//	}
//
//	if (!HasClipAmmo(TRUE))
//	{
//		Reload();
//		if (GetClip() == 0)
//		{
//			EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/shotgun/dry.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.15;
//			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.15;
//		}
//		return;
//	}
//
//	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
//	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;
//
//	if (!HasInfiniteClipAmmo())
//		m_iClip--;
//
//	int flags;
//#if defined( CLIENT_WEAPONS )
//	flags = FEV_NOTHOST;
//#else
//	flags = 0;
//#endif
//
//	m_pPlayer->pev->effects = (int)(m_pPlayer->pev->effects) | EF_MUZZLEFLASH;
//
//	// player "shoot" animation
//	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//	Vector vecAiming = m_pPlayer->GetAutoaimVector(AUTOAIM_5DEGREES);
//	Vector vecSpread = VECTOR_CONE_8DEGREES;
//
//	if (m_bRapidFire)
//		vecAiming = DeviateShootingVectorDirector(vecAiming, ConeRecoil(), 1.5f * (float)((float)max(1, m_iRecoil) / (float)SHOTGUN_MAX_CLIP));
//
//	Vector vecDir = m_pPlayer->FireBullets(8, vecSrc, vecAiming, vecSpread, 2048, BULLET_12G_SMALL,
//		0, 0, m_pPlayer->pev, m_pPlayer->random_seed);
//
//	int iAnim = m_pPlayer->pev->savedvanim = (m_bRapidFire ? SHOTGUN_FIRE_RAPID : SHOTGUN_FIRE);
//	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
//	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//
//	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usSingleFire, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, vecSpread.x, vecSpread.y,
//		m_iRecoil, 1, m_bRapidFire, 0, (float*)&vecAiming, (float*)&g_vecZero, iAnim, flFramerate, byFrame);
//	m_fDoubleFire = FALSE;
//
//	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
//		// HEV suit - indicate out of ammo condition
//		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
//
//	if (!m_bRapidFire)
//	{
//		m_flNextSecondaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.78;
//		m_flNextReload = 0.91;
//		m_flNextPump = UTIL_WeaponTimeBase() + 0.56;
//	}
//	else
//	{
//		m_flNextSecondaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.51; //0.60;
//		m_flNextReload = 0.78;
//		m_flNextPump = UTIL_WeaponTimeBase() + 0.43;
//		m_iRecoil = min(m_iRecoil + 1, SHOTGUN_MAX_CLIP);
//		m_flNextRecoil = m_flInitialRecoilCooldown;
//	}
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//
//	SetSemiFired();
//
//	UnsetIdle();
//}
//
//
//void CShotgun::SecondaryAttack(void)
//{
//	// Semi-automatic shots
//	if (HasSemiFired())
//		return;
//
//	// don't fire underwater
//	if (m_pPlayer->pev->waterlevel == 3)
//	{
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/shotgun/dry.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.15;
//		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.15;
//		return;
//	}
//
//	if (m_iClip == 1 && HasInfiniteClipAmmo())
//	{
//		PrimaryAttack();
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/shotgun/dry.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//		return;
//	}
//	else if (m_iClip < 1 && HasInfiniteClipAmmo())
//	{
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/shotgun/dry.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.15;
//		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.15;
//		return;
//	}
//
//	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
//	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;
//
//	if (HasInfiniteClipAmmo())
//		m_iClip -= 2;
//
//
//	int flags;
//#if defined( CLIENT_WEAPONS )
//	flags = FEV_NOTHOST;
//#else
//	flags = 0;
//#endif
//
//	m_pPlayer->pev->effects = (int)(m_pPlayer->pev->effects) | EF_MUZZLEFLASH;
//
//	// player "shoot" animation
//	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//	Vector vecAiming = m_pPlayer->GetAutoaimVector(AUTOAIM_5DEGREES);
//
//	Vector vecSpread = VECTOR_CONE_10DEGREES;
//
//	if (m_bRapidFire)
//		vecAiming = DeviateShootingVectorDirector(vecAiming, ConeRecoil(), 3.0f * (float)((float)max(1, m_iRecoil) / (float)SHOTGUN_MAX_CLIP));
//
//	Vector vecDir = m_pPlayer->FireBullets(16, vecSrc, vecAiming, vecSpread, 2048, BULLET_12G_SMALL, 0, 0, m_pPlayer->pev, m_pPlayer->random_seed);
//
//	int iAnim = m_pPlayer->pev->savedvanim = (m_bRapidFire ? SHOTGUN_FIRE_DOUBLE_RAPID : SHOTGUN_FIRE_DOUBLE);
//	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
//	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//
//	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usSingleFire, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, vecSpread.x, vecSpread.y,
//		m_iRecoil, 2, m_bRapidFire, 0, (float*)&vecAiming, (float*)&g_vecZero, iAnim, flFramerate, byFrame);
//	m_fDoubleFire = TRUE;
//
//	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
//		// HEV suit - indicate out of ammo condition
//		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
//
//	if (!m_bRapidFire)
//	{
//		m_flNextSecondaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.0625;
//		m_flNextReload = 1.3125;
//		m_flNextPump = UTIL_WeaponTimeBase() + 0.875;
//	}
//	else
//	{
//		m_flNextSecondaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.65;
//		m_flNextReload = 0.87;
//		m_flNextPump = UTIL_WeaponTimeBase() + 0.52;
//		m_iRecoil = min(m_iRecoil + 2, SHOTGUN_MAX_CLIP);
//		m_flNextRecoil = m_flInitialRecoilCooldown;
//	}
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.4;
//
//	UnsetReload();
//
//	SetSemiFired();
//	UnsetIdle();
//
//}
//
//void CShotgun::TertiaryAttack(void)
//{
//	if (!m_bRapidFire)
//	{
//		m_bRapidFire = TRUE;
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/shotgun/rapidon.wav", 1, ATTN_NORM, 0, RANDOM_LONG(PITCH_NORM, PITCH_LOW));
//	}
//
//	// Check for player
//	if (m_pPlayer)
//	{
//		if (m_pPlayer->pev->button & IN_ATTACK2 && m_flNextSecondaryAttack <= UTIL_WeaponTimeBase())
//		{
//			SecondaryAttack();
//			return;
//		}
//		else if (m_pPlayer->pev->button & IN_ATTACK && m_flNextPrimaryAttack <= UTIL_WeaponTimeBase())
//		{
//			PrimaryAttack();
//			return;
//
//		}
//		else
//		{
//			if (HasSemiFired() && !(m_pPlayer->pev->button & (IN_ATTACK | IN_ATTACK2)))
//			{
//				//m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.10;
//				UnsetSemiFired();
//			}
//			return;
//		}
//	}
//}
//
//
//void CShotgun::Reload(void)
//{
//	if (HasPrimaryAmmo(TRUE) || m_iClip >= GetMaxClip())
//		return;
//
//	// check to see if we're ready to reload
//	if (!InReload())
//	{
//		SendWeaponAnim(SHOTGUN_RELOAD_START);
//
//		if (m_iClip <= 0)
//			m_fHasPumped = FALSE;
//
//		m_fInReload = 1;
//		m_flNextReload = 0.45;
//
//		UnsetIdle();
//	}
//	else
//	{
//		return;
//	}
//}
//
//
//void CShotgun::WeaponIdle(void)
//{
//	// Semi-auto firing
//	UnsetSemiFired();
//
//	ResetEmptySound();
//
//	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
//
//	// If reloading, do not call anything beyond this point
//	if (InReload())
//		return;
//
//	if (m_flNextWeaponIdle < UTIL_WeaponTimeBase())
//	{
//		long rand = RANDOM_LONG(0, 99);
//		// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//		if (rand <= 5)
//		{
//			UpdateBodygroup();
//
//			long rareRand = RANDOM_LONG(0, 99);
//			// 25% chance of playing the rare shell bounce fidget
//			if (rareRand <= 25 && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] > 0)
//			{
//				SendWeaponAnim(SHOTGUN_FIDGET2);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.08;
//			}
//			else
//			{
//				SendWeaponAnim(SHOTGUN_FIDGET1);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.33;
//			}
//
//			UnsetIdle();
//		}
//		else
//		{
//			// Ensure at least two successful loops
//			if (!IsIdle())
//			{
//				UpdateBodygroup();
//
//				long rand = RANDOM_LONG(0, 1);
//				if (rand)
//				{
//					SendWeaponAnim(SHOTGUN_IDLE1);
//					m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.33 * 2;
//					m_bAltIdle = FALSE;
//				}
//				else
//				{
//					SendWeaponAnim(SHOTGUN_IDLE2);
//					m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.08 * 2;
//					m_bAltIdle = TRUE;
//				}
//
//				SetIdle();
//			}
//			else
//			{
//				// Only perform a single loop in this case
//				if (m_bAltIdle)
//					m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.08;
//				else
//					m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.33;
//			}
//		}
//	}
//}
//
////===========================================================
//// Shotgun Ammo Entities
////===========================================================
//class CShotgunAmmo : public CBasePlayerAmmo
//{
//public:
//	CShotgunAmmo(void)
//	{
//		m_szAmmoType = MAKE_STRING("buckshot");
//		m_szModel = MAKE_STRING("models/ammo_buckshot.mdl");
//		m_szPickupSound = MAKE_STRING("weapons/shotgun/ammo.wav");
//		m_iAmmoAmount = AMMO_BUCKSHOTBOX_GIVE; //AMMO_BUCKSHOT_GIVE;
//	};
//};
//LINK_ENTITY_TO_CLASS(ammo_buckshot, CShotgunAmmo);
