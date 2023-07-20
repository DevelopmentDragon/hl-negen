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
//
//extern int g_iAmmoCheat;
//
//LINK_ENTITY_TO_CLASS(weapon_glock, CGlock);
//LINK_ENTITY_TO_CLASS(weapon_9mmhandgun, CGlock); // Compatibility
//
////=========================================================
////=========================================================
//
//#ifndef CLIENT_DLL
//
//TYPEDESCRIPTION	CGlock::m_SaveData[] =
//{
//	DEFINE_FIELD(CGlock,m_fAutofire,FIELD_BOOLEAN),
//	DEFINE_FIELD(CGlock,m_fSilenced,FIELD_BOOLEAN),
//	DEFINE_FIELD(CGlock,m_fSilencing,FIELD_BOOLEAN),
//	DEFINE_FIELD(CGlock,m_flSilencing,FIELD_FLOAT),
//
//};
//IMPLEMENT_SAVERESTORE(CGlock, CBasePlayerWeapon);
//
//#endif
//
////=========================================================
////=========================================================
//
//weaponInfo CGlock::m_weaponInfo = {
//	{ 1, { "9mm","9mmI","9mmE","9mmH","9mmAP","9mmAPI","9mmAPE","9mmAPIE","9mmHP","9mmHPI","9mmHPE","9mmHPIE" } },
//};
//
//legalAmmoTypes CMP5::m_legalAmmoIndicies = GenerateLegalAmmoIndicies(CMP5::m_weaponInfo);
//
//
//CGlock::CGlock(void)
//{
//	m_usGlock1 = 0;
//	m_usGlock2 = 0;
//	m_iShell = 0;
//	m_fWeaponFlags = WEAPON_FLAG_CHAMBER_ROUND;
//}
//
//void CGlock::Spawn(void)
//{
//	pev->classname = MAKE_STRING("weapon_glock"); // hack to allow for compatibility
//	Precache();
//	m_iId = WEAPON_GLOCK;
//	SET_MODEL(ENT(pev), "models/w_glock.mdl");
//	m_iDefaultAmmo = GLOCK_DEFAULT_GIVE;
//
//	FallInit();// get ready to fall down.
//}
//
//void CGlock::ItemPostFrame(void)
//{
//	UpdateBodygroup();
//	CBasePlayerWeapon::ItemPostFrame();
//
//	if (m_fSilencing)
//	{
//		m_flSilencing = max((float)0.0f, m_flSilencing - gpGlobals->frametime);
//		if (m_flSilencing <= gpGlobals->frametime)
//		{
//			SwitchSilencer(GLOCK_SILENCE_LAST);
//		}
//	}
//
//}
//
//void CGlock::UpdateBodygroup(void)
//{
//	// Viewmodel
//	if (m_pPlayer)
//		m_pPlayer->pev->viewmodelbody = m_pPlayer->pev->playmodelbody = m_fSilenced;
//
//	// Worldmodel
//	pev->body = m_fSilenced;
//
//}
//
//void CGlock::PickupSound(void)
//{
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/glock/pickup.wav", 1, ATTN_NORM);
//}
//
//// Return HUD icon frame
//int CGlock::HUDIcon(void)
//{
//	if (HasWeaponUpgrades(UPGRADE_GLOCKS))
//		return 23;
//	else
//		return 21;
//}
//
//int CGlock::HUDActiveIcon(void)
//{
//	if (HasWeaponUpgrades(UPGRADE_GLOCKS))
//		return 24;
//	else
//		return 22;
//}
//
//int CGlock::ModeIcon(void)
//{
//	if (m_fAutofire == TRUE)
//		return 5;
//	else
//		return 4;
//}
//
//int CGlock::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CGlock::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CGlock::SmallIcon(void)
//{
//	if (HasWeaponUpgrades(UPGRADE_GLOCKS))
//		return 16;
//	else
//		return 15;
//}
//
//void CGlock::Precache(void)
//{
//	PRECACHE_MODEL("models/v_glock.mdl");
//	PRECACHE_MODEL("models/w_glock.mdl");
//	PRECACHE_MODEL("models/p_glock.mdl");
//
//	m_iShell = PRECACHE_MODEL("models/shell_9mm.mdl");
//
//	PRECACHE_SOUND("weapons/glock/fire.wav");
//	PRECACHE_SOUND("weapons/glock/fire_silencer.wav");
//	PRECACHE_SOUND("weapons/glock/dry.wav");
//	PRECACHE_SOUND("weapons/glock/pickup.wav");
//	PRECACHE_SOUND("weapons/glock/switch.wav");
//
//	m_usFireGlock1 = PRECACHE_EVENT(1, "events/glock1.sc");
//	m_usFireGlock2 = PRECACHE_EVENT(1, "events/glock2.sc");
//}
//
//int CGlock::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "9mm";
//	p->iMaxAmmo1 = _9MM_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = GLOCK_MAX_CLIP;
//	p->iSlot = WEAPON_BUCKET_HANDGUNS;
//	p->iPosition = WEAPON_GLOCK_SLOT;
//	p->iFlags = ITEM_FLAG_DUPLICATION;
//	p->iId = m_iId = WEAPON_GLOCK;
//	p->iWeight = GLOCK_WEIGHT;
//
//	return 1;
//}
//
//BOOL CGlock::NewDeploy(char* szViewModel, char* szWeaponModel, int iAnim, char* szAnimExt)
//{
//	m_pPlayer->pev->viewmodel = MAKE_STRING(szViewModel);
//	m_pPlayer->pev->weaponmodel = MAKE_STRING(szWeaponModel);
//	SendWeaponAnim(iAnim);
//	pev->frame = 0;
//	strcpy(m_pPlayer->m_szAnimExtention, szAnimExt);
//	return TRUE;
//}
//
//BOOL CGlock::Deploy(void)
//{
//	UpdateBodygroup();
//	m_fSilencing = FALSE;
//	m_flSilencing = 0.0;
//
//	int iDrawAnim = ((m_fSilenced) ? GLOCK_DRAW2 : GLOCK_DRAW) + ((m_iClip <= 0) ? 1 : 0);
//
//	return DefaultDeploy("models/v_glock.mdl", "models/p_glock.mdl", iDrawAnim, "onehanded", pev->body);
//
//}
//void CGlock::Holster(int skiplocal)
//{
//	// Reset special weapon mechanics
//	UnsetSemiFired();
//
//	UnsetReload();// cancel any reload in progress.
//	m_fSilencing = FALSE;// FAREAST: cancel any silencing in progress
//	m_flSilencing = 0.0;
//	SendWeaponAnim(GLOCK_HOLSTER);
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//	UnsetIdle();
//}
//
//void CGlock::TertiaryAttack(void)
//{
//	if (!HasWeaponUpgrades(UPGRADE_GLOCKS))
//		return;
//
//	// Do not call when silencing
//	if (m_fSilencing == TRUE)
//		return;
//
//	m_fSilencing = TRUE;
//	SwitchSilencer(GLOCK_SILENCE_FIRST);
//}
//
//void CGlock::SecondaryAttack(void)
//{
//	SendWeaponAnim((m_iClip <= 0) ? GLOCK_SWITCH_EMPTY : GLOCK_SWITCH, 2.0f);
//
//	if (m_fAutofire)
//		m_fAutofire = FALSE;
//	else
//		m_fAutofire = TRUE;
//
//	EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/glock/switch.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//
//	// FAREAST: We want a delay between switches and firing.
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.78;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.78;
//	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.78;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 0.98;
//	UnsetIdle();
//}
//
//void CGlock::PrimaryAttack(void)
//{
//	if (m_fAutofire == FALSE)
//		GlockFire(0.01 - (m_fSilenced == TRUE ? 0.005 : 0), 0.0, m_fAutofire);
//	else if (m_fAutofire == TRUE)
//		GlockFire(0.1 - (m_fSilenced == TRUE ? 0.05 : 0), 0.10, m_fAutofire);
//}
//
//void CGlock::GlockFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
//{
//	if (HasSemiFired())
//		return;
//
//	if (m_fSilenced == FALSE) {
//		m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
//		m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;
//	}
//	else {
//		m_pPlayer->m_iWeaponVolume = SILENT_GUN_VOLUME;
//		m_pPlayer->m_iWeaponFlash = NULL_GUN_FLASH;
//	}
//
//	if (m_pPlayer->pev->waterlevel == 3 && m_fSilenced == FALSE)
//	{
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/glock/dry.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.15;
//		return;
//	}
//
//	if (HasClipAmmo(TRUE))
//	{
//		if (m_fFireOnEmpty)
//		{
//			EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/glock/dry.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.2;
//		}
//
//		return;
//	}
//
//	if (HasInfiniteClipAmmo())
//		m_iClip--;
//
//	m_pPlayer->pev->effects = (int)(m_pPlayer->pev->effects);
//
//	int flags = FEV_NOTHOST;
//
//	/*
//#if defined( CLIENT_WEAPONS )
//	flags = FEV_NOTHOST;
//#else
//	flags = 0;
//#endif
//	*/
//
//	// player "shoot" animation
//	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//	Vector vecAiming;
//
//	if (fUseAutoAim)
//	{
//		vecAiming = m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
//	}
//	else
//	{
//		vecAiming = gpGlobals->v_forward;
//	}
//
//	Vector vecDir;
//	int shared_rand = m_pPlayer->random_seed;
//
//	UpdateBodygroup();
//	vecDir = m_pPlayer->FireBullets(1, vecSrc, vecAiming, Vector(flSpread, flSpread, flSpread), 8192, m_fSilenced == TRUE ? BULLET_9MMS : BULLET_9MM, 0, 0, m_pPlayer->pev, shared_rand);
//
//	int iAnim = m_pPlayer->pev->savedvanim = (m_fSilenced) ? ((m_iClip == 0) ? GLOCK_SHOOT_EMPTY2 : GLOCK_SHOOT2) : ((m_iClip == 0) ? GLOCK_SHOOT_EMPTY : GLOCK_SHOOT);
//	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
//	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//
//	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_fSilenced == TRUE ? m_usFireGlock2 : m_usFireGlock1, 0.0, (float*)&g_vecZero, (float*)&g_vecZero,
//		vecDir.x, vecDir.y, m_pPlayer->pev->viewmodelbody, 0, (m_iClip == 0) ? 1 : 0, 0, (float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//
//	UnsetIdle();
//
//	if (fUseAutoAim == FALSE)
//		SetSemiFired();
//
//
//	if (!HasClipAmmo(TRUE) && !HasPrimaryAmmo(TRUE))
//		// HEV suit - indicate out of ammo condition
//		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
//
//}
//
//
//void CGlock::Reload(void)
//{
//	if (HasAmmo())
//		return;
//
//	if (HasSemiFired())
//		UnsetSemiFired();
//
//	int iResult;
//
//	float flReloadTime = 1.38;
//	int iReloadAnim = GLOCK_RELOAD;
//
//	if (m_fSilenced)
//	{
//		if (m_iClip <= 0)
//			iReloadAnim = GLOCK_RELOAD_EMPTY2;
//		else
//			iReloadAnim = GLOCK_RELOAD2;
//
//		flReloadTime = 1.4;
//	}
//	else
//	{
//		if (m_iClip <= 0)
//		{
//			iReloadAnim = GLOCK_RELOAD_EMPTY;
//			flReloadTime = 2.0;
//		}
//	}
//
//
//	//iResult = DefaultReload(iReloadAnim, 1.0f, (byte)0, flReloadTime, flReloadTime + 1.5, flReloadTime + 1.5, flReloadTime + 1.5, flReloadTime + 1.5);
//
//	m_pPlayer->SetAnimation(PLAYER_RELOAD);
//
//}
//
//void CGlock::SwitchSilencer(int mode)
//{
//	if (mode)
//	{
//		if (m_fSilenced == FALSE)
//		{
//			m_fSilenced = TRUE;
//			UpdateBodygroup();
//			SendWeaponAnim((m_iClip <= 0) ? GLOCK_ADD_SILENCER_EMPTY : GLOCK_ADD_SILENCER);
//			m_fSilencing = FALSE;
//
//		}
//		else if (m_fSilenced == TRUE)
//		{
//			m_fSilenced = FALSE;
//			UpdateBodygroup();
//			SendWeaponAnim((m_iClip <= 0) ? GLOCK_DRAW_FROM_SILENCER_EMPTY : GLOCK_DRAW_FROM_SILENCER);
//			m_fSilencing = FALSE;
//		}
//	}
//	else
//	{
//		if (m_fSilenced == TRUE)
//		{
//			UpdateBodygroup();
//			SendWeaponAnim((m_iClip <= 0) ? GLOCK_REMOVE_SILENCER_EMPTY : GLOCK_REMOVE_SILENCER);
//			m_fSilencing = TRUE;
//			m_flSilencing = 2.83;
//		}
//		else
//		{
//			UpdateBodygroup();
//			SendWeaponAnim((m_iClip <= 0) ? GLOCK_HOLSTER_FROM_SILENCER_EMPTY : GLOCK_HOLSTER_FROM_SILENCER);
//			m_fSilencing = TRUE;
//			m_flSilencing = 0.55;
//		}
//
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 3.40;
//		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 3.40;
//		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 3.40;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.40; //2.65;
//		UnsetIdle();
//	}
//}
//
//
//void CGlock::WeaponIdle(void)
//{
//	if (HasSemiFired() && m_flNextPrimaryAttack <= UTIL_WeaponTimeBase())
//	{
//		m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.10;
//		UnsetSemiFired();
//	}
//
//	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
//
//	if (m_flNextWeaponIdle <= UTIL_WeaponTimeBase() && !m_fSilencing)
//	{
//		// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//		if (RANDOM_LONG(0, 99) <= 5)
//		{
//			UpdateBodygroup();
//			SendWeaponAnim((m_iClip <= 0) ? GLOCK_FIDGET1_EMPTY : GLOCK_FIDGET1);
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 4.35;
//			UnsetIdle();
//		}
//		else
//		{
//			// Ensure at least two successful loops
//			if (!IsIdle())
//			{
//				UpdateBodygroup();
//				SendWeaponAnim((m_iClip <= 0) ? GLOCK_IDLE1_EMPTY : GLOCK_IDLE1);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.57 * 2;
//				SetIdle();
//			}
//			else
//			{
//				// Only perform a single loop in this case
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.57;
//			}
//		}
//	}
//}
//
//class CGlockAmmo : public CBasePlayerAmmo
//{
//public:
//	CGlockAmmo(void)
//	{
//		m_szPickupSound = MAKE_STRING("weapons/glock/ammo.wav");
//		m_szAmmoType = MAKE_STRING("9mm");
//		m_szModel = MAKE_STRING("models/ammo_9mm.mdl");
//		m_iAmmoAmount = GLOCK_MAX_CLIP;
//	}
//	void Spawn(void)
//	{
//		CBasePlayerAmmo::Spawn();
//		pev->classname = MAKE_STRING("ammo_9mm"); // Added for compatiblity
//	}
//};
//LINK_ENTITY_TO_CLASS(ammo_9mm, CGlockAmmo);
//LINK_ENTITY_TO_CLASS(ammo_glockclip, CGlockAmmo); // Added for compatiblity
//LINK_ENTITY_TO_CLASS(ammo_9mmclip, CGlockAmmo); // Added for compatibility
//
//// Little Badis: Silencer upgrade for the Glock
//class CGlockSilencer : public CGlock
//{
//	void Spawn(void)
//	{
//		CGlock::Spawn();
//		pev->body = 1;
//		m_fWeaponUpgrades |= (1 << UPGRADE_GLOCKS);
//		m_fSilenced = TRUE;
//	}
//};
//LINK_ENTITY_TO_CLASS(weapon_glocksilencer, CGlockSilencer);
