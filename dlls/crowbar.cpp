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
//#include "extdll.h"
//#include "util.h"
//#include "cbase.h"
//#include "monsters.h"
//#include "weapons.h"
//#include "nodes.h"
//#include "player.h"
//#include "gamerules.h"
//#include "soundent.h"
//
//#ifndef CLIENT_DLL
//#define CROWBAR_AIR_VELOCITY	1000
//#define CROWBAR_WATER_VELOCITY	500
//
//// UNDONE: Save/restore this?  Don't forget to set classname and LINK_ENTITY_TO_CLASS()
//// 
//// OVERLOADS SOME ENTVARS:
////
//// speed - the ideal magnitude of my velocity
//class CThrownCrowbar : public CBaseEntity
//{
//	void Spawn(void);
//	void Precache(void);
//	int  Classify(void);
//	void EXPORT SpinThink(void);
//	void EXPORT CrowbarTouch(CBaseEntity* pOther);
//	BOOL m_fStays;
//	float m_flNextFlySound;
//	float m_flFallTime;
//
//	int	Save(CSave& save);
//	int Restore(CRestore& restore);
//	static TYPEDESCRIPTION m_SaveData[];
//
//public:
//	static CThrownCrowbar* CbarCreate(int iLooks, BOOL m_fInfiniteAmmo);
//};
//LINK_ENTITY_TO_CLASS(thrown_crowbar, CThrownCrowbar);
//
//TYPEDESCRIPTION	CThrownCrowbar::m_SaveData[] =
//{
//	DEFINE_FIELD(CThrownCrowbar, m_fStays, FIELD_BOOLEAN),
//	DEFINE_FIELD(CThrownCrowbar, m_flNextFlySound, FIELD_FLOAT),
//	DEFINE_FIELD(CThrownCrowbar, m_flFallTime, FIELD_FLOAT),
//};
//
//IMPLEMENT_SAVERESTORE(CThrownCrowbar, CBaseEntity);
//
//CThrownCrowbar* CThrownCrowbar::CbarCreate(int iLooks, BOOL m_fInfiniteAmmo)
//{
//	// Create a new entity with CThrownCrowbar private data
//	CThrownCrowbar* pCbar = GetClassPtr((CThrownCrowbar*)NULL);
//	pCbar->pev->classname = MAKE_STRING("thrown_crowbar");	// g-cont. enable save\restore
//	pCbar->Spawn();
//	pCbar->m_fStays = m_fInfiniteAmmo;
//	pCbar->pev->body = iLooks;
//	return pCbar;
//}
//
//void CThrownCrowbar::Spawn()
//{
//	Precache();
//	pev->movetype = MOVETYPE_BOUNCE;
//	pev->solid = SOLID_BBOX;
//
//	pev->gravity = 1.0;
//	m_flFallTime = 0.1;
//
//	SET_MODEL(ENT(pev), "models/w_crowbar.mdl");
//
//	UTIL_SetOrigin(pev, pev->origin);
//	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
//
//	SetTouch(&CThrownCrowbar::CrowbarTouch);
//	SetThink(&CThrownCrowbar::SpinThink);
//	pev->nextthink = gpGlobals->time + 0.01;
//	m_flNextFlySound = gpGlobals->time;
//}
//
//
//void CThrownCrowbar::Precache()
//{
//	PRECACHE_MODEL("models/w_crowbar.mdl");
//
//	PRECACHE_SOUND("weapons/crowbar/throwhit01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throwhitflesh01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throw01.wav");
//}
//
//
//int	CThrownCrowbar::Classify(void)
//{
//	return	CLASS_NONE;
//}
//
//void CThrownCrowbar::CrowbarTouch(CBaseEntity* pOther)
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
//
//		pOther->TraceAttack(pevOwner, gSkillData.plrDmgCrowbarThrown, pev->velocity.Normalize(), &tr, ID_DMG_CROWBAR_THROWN);
//
//		pev->velocity = Vector(0, 0, 0);
//
//		EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/crowbar/throwhitflesh01.wav", 1, ATTN_NORM);
//
//	}
//	else
//	{
//		EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/crowbar/throwhit01.wav", 1, ATTN_NORM);
//	}
//
//	if (m_fStays == TRUE)
//	{
//		CBaseEntity* pOld = Create("weapon_crowbar", pev->origin, pev->angles);
//		CCrowbar* pNew = (CCrowbar*)pOld;
//		pNew->pev->body = pev->body;
//		pNew->m_iWeaponLooks = pev->body;
//		pNew->pev->solid = SOLID_NOT;
//		UTIL_SetSize(pNew->pev, Vector(-2.5, -2.5, -2.5), Vector(2.5, 2.5, 2.5));
//	}
//
//	if (UTIL_PointContents(pev->origin) != CONTENTS_WATER)
//	{
//		UTIL_Sparks(pev->origin);
//	}
//
//	pev->nextthink = gpGlobals->time;// this will get changed below if the bolt is allowed to stick in what it hit.
//
//	UTIL_Remove(this);
//}
//
//void CThrownCrowbar::SpinThink(void)
//{
//	pev->nextthink = gpGlobals->time + 0.01;
//
//	if (m_flFallTime > 0.0f)
//	{
//		m_flFallTime -= 0.01;
//		if (m_flFallTime <= 0.0)
//		{
//			m_flFallTime = -1.0;
//			//pev->velocity = g_vecDummy;
//			pev->gravity = 2.0;
//		}
//	}
//
//	if (pev->waterlevel != 0)
//		return;
//
//	// Play the sound
//	if (m_flNextFlySound <= gpGlobals->time)
//	{
//		m_flNextFlySound = gpGlobals->time + 0.34;
//		EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/crowbar/throw01.wav", 1, ATTN_NORM);
//	}
//
//	pev->angles.x = pev->angles.x - 7.2; //3.6;
//}
//
//#endif
//
//#define	CROWBAR_BODYHIT_VOLUME 128
//#define	CROWBAR_WALLHIT_VOLUME 512
//
//LINK_ENTITY_TO_CLASS(weapon_crowbar, CCrowbar);
//
//#ifndef CLIENT_DLL
//
//TYPEDESCRIPTION	CCrowbar::m_SaveData[] =
//{
//	DEFINE_FIELD(CCrowbar, m_bSwingLock, FIELD_BOOLEAN),
//	DEFINE_FIELD(CCrowbar, m_iSwing, FIELD_INTEGER),
//	DEFINE_FIELD(CCrowbar, m_iThrowing, FIELD_INTEGER),
//	DEFINE_FIELD(CCrowbar, m_flThrowTime, FIELD_FLOAT),
//};
//IMPLEMENT_SAVERESTORE(CCrowbar, CBasePlayerWeapon);
//
//#endif
//
//void CCrowbar::ItemPostFrame(void)
//{
//	UpdateBodygroup();
//
//	// Sanity Check
//	if (m_pPlayer)
//	{
//		// Tool logic
//		if (m_flToolTime > 0.0f)
//		{
//			m_flToolTime -= gpGlobals->frametime;
//		}
//		else if (m_flToolTime != -1.0f)
//		{
//			m_flToolTime = -1.0f;
//		}
//
//		// Throw Logic
//		if (m_iThrowing)
//		{
//			if (m_flThrowTime > 0.0f)
//			{
//				m_flThrowTime -= gpGlobals->frametime;
//			}
//			else if (m_flThrowTime != -1.0f)
//			{
//				switch (m_iThrowing)
//				{
//				case 1:
//				{
//					if ((m_pPlayer->pev->button & IN_ATTACK3) != IN_ATTACK3)
//						ThrowCrowbar();
//				}
//				break;
//
//				default:
//				{
//					if (HasInfiniteReserveAmmo())
//						RedrawCrowbar();
//					else
//						DestroyCrowbar();
//				}
//				break;
//				}
//			}
//		}
//
//		// Block cooldown logic
//		if (m_flBlockCooldown > 0.0f)
//		{
//			m_flBlockCooldown -= gpGlobals->frametime;
//		}
//		else if (m_flBlockCooldown != -1.0f)
//		{
//			m_flBlockCooldown = -1.0f;
//		}
//
//		// Block regeneration logic
//		if (m_flBlockRegen > 0.0f)
//		{
//			m_flBlockRegen -= gpGlobals->frametime;
//		}
//		else
//		{
//			if (m_flBlockAmount < GetBlockAmount())
//			{
//				m_flBlockAmount += 1.0f;
//			}
//			m_flBlockRegen += GetBlockRegen();
//		}
//
//		// Big Swing timed logic
//		if (m_flSwingTime > 0)
//			m_flSwingTime -= gpGlobals->frametime;
//		else if (m_flSwingTime != -1)
//			m_flSwingTime = 0;
//
//		// Big Swing timed logic
//		if (m_flNextReload > 0.0f)
//			m_flNextReload -= gpGlobals->frametime;
//		else
//			m_flNextReload = UTIL_WeaponTimeBase();
//
//		// Stop the block
//		if (m_bBlocking == TRUE && m_flNextReload <= UTIL_WeaponTimeBase() && !FBitSet(m_pPlayer->pev->button, IN_RELOAD))
//		{
//			BlockStop();
//		}
//
//		// Swing the charged crowbar
//		if (m_bBigSwing == TRUE && m_flSwingTime <= 0 && !FBitSet(m_pPlayer->pev->button, IN_ATTACK2))
//		{
//			if (!BigSwing(1))
//			{
//				SetThink(&CCrowbar::BigSwingAgain);
//				pev->nextthink = gpGlobals->time + 0.1;
//			}
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.0;
//			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.0;
//			m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.0;
//			m_bBigSwing = FALSE;
//			m_flSwingTime = -1;
//		}
//
//		// Be sure to fix issue with lock
//		if (m_flNextPrimaryAttack <= UTIL_WeaponTimeBase())
//			m_bSwingLock = FALSE;
//	}
//
//	CBasePlayerWeapon::ItemPostFrame();
//}
//
//BOOL CCrowbar::ShouldDisplayThrowForce(void)
//{
//	if (m_bBlocking)
//		return TRUE;
//
//	return FALSE;
//}
//
//int CCrowbar::GetThrowForce(void)
//{
//	return (int)m_flBlockAmount;
//}
//
//int CCrowbar::GetMaxThrowForce(void)
//{
//	return (int)GetBlockAmount();
//}
//
//void CCrowbar::UpdateBodygroup(void)
//{
//	if (m_pPlayer)
//	{
//		if (m_iThrowing == 2)
//			m_pPlayer->pev->viewmodelbody = 4;
//		else
//			m_pPlayer->pev->viewmodelbody = m_iWeaponLooks + 5;
//
//		m_pPlayer->pev->playmodelbody = m_iWeaponLooks;
//	}
//
//	pev->body = m_iWeaponLooks;
//}
//
//void CCrowbar::PickupSound(void)
//{
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/crowbar/pickup.wav", 1, ATTN_NORM);
//}
//
////BOOL CCrowbar::IsUseable(void)
////{
////	return TRUE; // To be able to use the scope
////}
//
//int CCrowbar::HUDIcon(void)
//{
//	if (m_iWeaponLooks == 3)
//		return 7;
//	else
//		return 5;
//}
//
//int CCrowbar::HUDActiveIcon(void)
//{
//	if (m_iWeaponLooks == 3)
//		return 8;
//	else
//		return 6;
//}
//
//int CCrowbar::ModeIcon(void)
//{
//	return -1;
//}
//
//int CCrowbar::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CCrowbar::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CCrowbar::SmallIcon(void)
//{
//	if (m_iWeaponLooks == 3)
//		return 8;
//	else
//		return 7;
//}
//
//void CCrowbar::Spawn()
//{
//	Precache();
//	m_iId = WEAPON_CROWBAR;
//	SET_MODEL(ENT(pev), "models/w_crowbar.mdl");
//	m_iClip = -1;
//	pev->classname = MAKE_STRING("weapon_crowbar");
//
//	m_flBlockAmount = GetBlockAmount();
//	m_flBlockRegen = GetBlockRegen();
//
//	FallInit();// get ready to fall down.
//}
//
//
//void CCrowbar::Precache(void)
//{
//	PRECACHE_SOUND("weapons/crowbar/althipent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/althit01.wav");
//	PRECACHE_SOUND("weapons/crowbar/althitflesh01.wav");
//	PRECACHE_SOUND("weapons/crowbar/althitflesh02.wav");
//	PRECACHE_SOUND("weapons/crowbar/althitflesh03.wav");
//	PRECACHE_SOUND("weapons/crowbar/althitfleshpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/althitfleshpent02.wav");
//	PRECACHE_SOUND("weapons/crowbar/althitfleshpent03.wav");
//	PRECACHE_SOUND("weapons/crowbar/altprep.wav");
//	PRECACHE_SOUND("weapons/crowbar/altpreppent.wav");
//	PRECACHE_SOUND("weapons/crowbar/altswing01.wav");
//	PRECACHE_SOUND("weapons/crowbar/altswingpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/block01.wav");
//	PRECACHE_SOUND("weapons/crowbar/block02.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockbreak.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockbreakpent.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockhit01.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockhitflesh01.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockhitfleshpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockhitpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockpent02.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockprep.wav");
//	PRECACHE_SOUND("weapons/crowbar/lockpreppent.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockstop.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockstoppent.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockswing01.wav");
//	PRECACHE_SOUND("weapons/crowbar/blockswingpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/draw.wav");
//	PRECACHE_SOUND("weapons/crowbar/drop.wav");
//	PRECACHE_SOUND("weapons/crowbar/holster.wav");
//	PRECACHE_SOUND("weapons/crowbar/pickup.wav");
//	PRECACHE_SOUND("weapons/crowbar/swing01.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghit01.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghit02.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghitflesh01.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghitflesh02.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghitflesh03.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghitfleshpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghitfleshpent02.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghitfleshpent03.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghitpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/swinghitpent02.wav");
//	PRECACHE_SOUND("weapons/crowbar/swingpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throw01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throwhit01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throwhitflesh01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throwhitfleshpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throwhitpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throwpent01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throwprep01.wav");
//	PRECACHE_SOUND("weapons/crowbar/throwpreppent01.wav");
//
//	PRECACHE_MODEL("models/v_crowbar.mdl");
//	PRECACHE_MODEL("models/p_crowbar.mdl");
//	PRECACHE_MODEL("models/w_crowbar.mdl");
//
//	m_usCrowbar = PRECACHE_EVENT(1, "events/crowbar.sc");
//}
//
//int CCrowbar::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = NULL;
//	p->iMaxAmmo1 = -1;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = WEAPON_NOCLIP_RELOAD; //-1;
//	p->iSlot = WEAPON_BUCKET_MELEE;
//	p->iPosition = WEAPON_CROWBAR_SLOT;
//	p->iFlags = ITEM_FLAG_CANSELECT | ITEM_FLAG_NOAMMODISPLAY | ITEM_FLAG_DUPLICATION | ITEM_FLAG_NOAUTORELOAD;
//	p->iId = m_iId = WEAPON_CROWBAR;
//	p->iWeight = CROWBAR_WEIGHT;
//	return 1;
//}
//
//// Fograin92: The correct model will be deployed
//BOOL CCrowbar::Deploy()
//{
//	UpdateBodygroup();
//	return DefaultDeploy("models/v_crowbar.mdl", "models/p_crowbar.mdl", CROWBAR_DRAW, "crowbar");
//}
//
//
//void CCrowbar::Holster(int skiplocal /* = 0 */)
//{
//	BlockStop();
//	SendWeaponAnim(CROWBAR_HOLSTER, 1, (byte)128);
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//}
//
//void CCrowbar::PrimaryAttack()
//{
//	// Don't initiate this if we're throwing a big swing or blocking
//	if (m_bBigSwing || m_bBlocking || m_fToolFlags != 0 || m_iThrowing != 0)
//		return;
//
//	if (!Swing(1))
//	{
//		SetThink(&CCrowbar::SwingAgain);
//		pev->nextthink = gpGlobals->time + 0.1;
//	}
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//}
//
//void CCrowbar::SecondaryAttack()
//{
//	if (m_bBigSwing == FALSE && m_bBlocking == FALSE && m_fToolFlags == 0 && m_iThrowing == 0)
//	{
//		m_bBigSwing = TRUE;
//		m_flSwingTime = 0.9;
//		SendWeaponAnim(CROWBAR_BIGATTACKWINDUP);
//		UnsetIdle();
//	}
//}
//
//void CCrowbar::TertiaryAttack(void)
//{
//	// Don't initiate this if we're throwing a big swing or blocking
//	if (m_bBigSwing || m_bBlocking || m_fToolFlags != 0 || m_iThrowing)
//		return;
//
//	// Initiate the throwing here
//	m_iThrowing = 1;
//	SendWeaponAnim(CROWBAR_THROWWINDUP);
//	m_flThrowTime = 0.65;
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.0;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//	m_flNextReload = UTIL_WeaponTimeBase() + 1.0;
//}
//
//void CCrowbar::ThrowCrowbar(void)
//{
//	TraceResult tr;
//
//	m_pPlayer->m_iWeaponVolume = QUIET_GUN_VOLUME;
//
//	m_iThrowing = 2;
//	UpdateBodygroup();
//	SendWeaponAnim(CROWBAR_THROW, 1.0f, 0.0f, 1);
//
//	m_flThrowTime = 0.65;
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
//#ifndef CLIENT_DLL
//	CThrownCrowbar* pCbar = CThrownCrowbar::CbarCreate(m_iWeaponLooks, !HasInfiniteReserveAmmo() ? TRUE : FALSE);
//	pCbar->pev->origin = vecSrc;
//	pCbar->pev->angles = anglesAim;
//	pCbar->pev->owner = m_pPlayer->edict();
//
//	if (m_pPlayer->pev->waterlevel == 3)
//	{
//		pCbar->pev->velocity = vecDir * CROWBAR_WATER_VELOCITY;
//		pCbar->pev->speed = CROWBAR_WATER_VELOCITY;
//	}
//	else
//	{
//		pCbar->pev->velocity = vecDir * CROWBAR_AIR_VELOCITY;
//		pCbar->pev->speed = CROWBAR_AIR_VELOCITY;
//	}
//	pCbar->pev->avelocity.z = 10;
//#endif
//
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.00;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.00;
//	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.00;
//	m_flNextReload = UTIL_WeaponTimeBase() + 1.00;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.00;
//
//	if (!HasInfiniteReserveAmmo())
//	{
//		if ((&m_pPlayer->m_rgpPlayerItems[0][0]))
//		{
//			m_pPlayer->SwitchWeaponAlt(&m_pPlayer->m_rgpPlayerItems[0][0]);
//			m_pPlayer->m_flNextDeploy = 0.65;
//		}
//
//		m_pPlayer->pev->weaponmodel = 0;
//		m_pPlayer->pev->weapons &= ~(1 << (WEAPON_CROWBAR % 32)); // [WEAPON_CROWBAR / 32] &= ~(1 << (WEAPON_CROWBAR % 32));
//		SetThink(&CBasePlayerItem::DestroyItemAlt);
//		pev->nextthink = gpGlobals->time + 0.01;
//	}
//}
//
//// Do we still need this?
//void CCrowbar::DestroyCrowbar(void)
//{
//	return;
//}
//
//void CCrowbar::RedrawCrowbar(void)
//{
//	Deploy();
//	m_iThrowing = 0;
//}
//
//void CCrowbar::Reload(void)
//{
//	//ALERT(at_console, "Attempting to block.\n");
//
//	if (m_flBlockCooldown > 0.0f)
//		return;
//
//	if (!m_bBlocking)
//	{
//		SendWeaponAnim(CROWBAR_BLOCKSTART);
//		UnsetIdle();
//		m_bBlocking = TRUE;
//		m_flNextReload = UTIL_WeaponTimeBase() + 0.68;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//	}
//	else
//	{
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//	}
//}
//
//void CCrowbar::Smack(void)
//{
//	m_bSwingLock = FALSE;
//}
//
//void CCrowbar::SwingAgain(void)
//{
//	Swing(0);
//}
//
//void CCrowbar::BigSwingAgain(void)
//{
//	BigSwing(0);
//}
//
//void CCrowbar::BigSmack(void)
//{
//	return;
//}
//
//int CCrowbar::Swing(int fFirst)
//{
//	int fDidHit = FALSE;
//
//	TraceResult tr;
//
//	UTIL_MakeVectors(m_pPlayer->pev->v_angle);
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//	Vector vecEnd = vecSrc + gpGlobals->v_forward * 32;
//
//	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
//
//#ifndef CLIENT_DLL
//	if (tr.flFraction >= 1.0)
//	{
//		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, ENT(m_pPlayer->pev), &tr);
//		if (tr.flFraction < 1.0)
//		{
//			// Calculate the point of intersection of the line (or hull) and the object we hit
//			// This is and approximation of the "best" intersection
//			CBaseEntity* pHit = CBaseEntity::Instance(tr.pHit);
//			if (!pHit || pHit->IsBSPModel())
//				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
//			vecEnd = tr.vecEndPos;	// This is the point on the actual surface (the hull could have hit space)
//		}
//	}
//#endif
//
//	// Perform the swing
//	if (m_bSwingLock == FALSE)
//	{
//		m_iSwing++;
//		if (m_iSwing > 2)
//			m_iSwing = 0;
//	}
//
//	// Fograin92: Crowbar swing missed
//	if (tr.flFraction >= 1.0)
//	{
//		if (fFirst)
//		{
//			EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/swing01.wav", 1, ATTN_NORM);
//
//			SendWeaponAnim(CROWBAR_ATTACK1MISS + (2 * m_iSwing));
//
//			// miss
//			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.36;
//			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.36;
//			m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.36;
//
//			// player "shoot" animation
//			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//			m_bSwingLock = TRUE;
//		}
//	}
//	else
//	{
//		SendWeaponAnim(CROWBAR_ATTACK1HIT + (2 * m_iSwing));
//
//		//ALERT( at_console, "m_iSwing: %d\n", m_iSwing );
//
//		// player "shoot" animation
//		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//#ifndef CLIENT_DLL
//
//		// hit
//		fDidHit = TRUE;
//		CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);
//
//		//ClearMultiDamage( );
//
//		if (!m_iSwing)
//		{
//			// first swing does full damage
//			pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgCrowbarHeavy, gpGlobals->v_forward, &tr, ID_DMG_CROWBAR_HEAVY);
//		}
//		else
//		{
//			// subsequent swings do half
//			pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgCrowbarLight, gpGlobals->v_forward, &tr, ID_DMG_CROWBAR_LIGHT);
//		}
//		//ApplyMultiDamage( m_pPlayer->pev, m_pPlayer->pev, ID_DMG_GENERIC );
//
//		// play thwack, smack, or dong sound
//		float flVol = 1.0;
//		int fHitWorld = TRUE;
//
//		if (pEntity)
//		{
//			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
//			{
//				switch (RANDOM_LONG(0, 2))
//				{
//				case 0: EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/swinghitflesh01.wav", 1, ATTN_NORM); break;
//				case 1:	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/swinghitflesh02.wav", 1, ATTN_NORM); break;
//				case 2:	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/swinghitflesh03.wav", 1, ATTN_NORM); break;
//				}
//				// play thwack or smack sound
//				m_pPlayer->m_iWeaponVolume = CROWBAR_BODYHIT_VOLUME;
//
//				if (!pEntity->IsAlive())
//				{
//					m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.36;	// Vit_amiN: fixed the 'rapid crowbar'
//					m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.36;	// Vit_amiN: fixed the 'rapid crowbar'
//					m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.36;
//					return TRUE;
//				}
//				else
//					flVol = 0.1;
//
//				fHitWorld = FALSE;
//			}
//		}
//
//		// play texture hit sound
//		// UNDONE: Calculate the correct point of intersection when we hit with the hull instead of the line
//
//		if (fHitWorld)
//		{
//			if (!(pEntity && FClassnameIs(pEntity->pev, "func_breakable")))
//			{
//				Vector vecDir2 = m_pPlayer->FireBullets(1, vecSrc, gpGlobals->v_forward, Vector(0, 0, 0), 32, BULLET_MELEE_CROWBAR_NORM, 0, 0, m_pPlayer->pev, m_pPlayer->random_seed);
//				PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usCrowbar, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, vecDir2.x, vecDir2.y, 0, 0, FALSE, 0, (float*)&g_vecZero, (float*)&g_vecZero,
//					0, 0.0f, (byte)0);
//			}
//
//			// delay the decal a bit
//			m_trHit = tr;
//		}
//
//		m_pPlayer->m_iWeaponVolume = flVol * CROWBAR_WALLHIT_VOLUME;
//#endif
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.36;
//		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.36;
//		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.36;
//
//		SetThink(&CCrowbar::Smack);
//		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
//
//
//	}
//	return fDidHit;
//}
//
//int CCrowbar::BigSwing(int fFirst)
//{
//	int fDidHit = FALSE;
//
//	TraceResult tr;
//
//	UTIL_MakeVectors(m_pPlayer->pev->v_angle);
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//	Vector vecEnd = vecSrc + gpGlobals->v_forward * 32;
//
//	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
//
//#ifndef CLIENT_DLL
//	if (tr.flFraction >= 1.0)
//	{
//		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, ENT(m_pPlayer->pev), &tr);
//		if (tr.flFraction < 1.0)
//		{
//			// Calculate the point of intersection of the line (or hull) and the object we hit
//			// This is and approximation of the "best" intersection
//			CBaseEntity* pHit = CBaseEntity::Instance(tr.pHit);
//			if (!pHit || pHit->IsBSPModel())
//				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
//			vecEnd = tr.vecEndPos;	// This is the point on the actual surface (the hull could have hit space)
//		}
//	}
//#endif
//
//
//	// Fograin92: Crowbar swing missed
//	if (tr.flFraction >= 1.0)
//	{
//		if (fFirst)
//		{
//			EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/altswing01.wav", 1, ATTN_NORM);
//
//			SendWeaponAnim(CROWBAR_BIGATTACKMISS);
//
//			// miss
//			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
//			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
//			m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.5;
//
//			// player "shoot" animation
//			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//		}
//	}
//	else
//	{
//		SendWeaponAnim(CROWBAR_BIGATTACKHIT);
//
//		// player "shoot" animation
//		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//#ifndef CLIENT_DLL
//
//		// hit
//		fDidHit = TRUE;
//		CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);
//
//		//ClearMultiDamage( );
//
//		pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgCrowbarHeavy, gpGlobals->v_forward, &tr, ID_DMG_CROWBAR_HEAVY);
//		//ApplyMultiDamage( m_pPlayer->pev, m_pPlayer->pev, ID_DMG_GENERIC );
//
//		// play thwack, smack, or dong sound
//		float flVol = 1.0;
//		int fHitWorld = TRUE;
//
//		if (pEntity)
//		{
//			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
//			{
//				switch (RANDOM_LONG(0, 2))
//				{
//				case 1: EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/althitflesh01.wav", 1, ATTN_NORM); break;
//				case 2: EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/althitflesh02.wav", 1, ATTN_NORM); break;
//				default: EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/althitflesh03.wav", 1, ATTN_NORM); break;
//				}
//				// play thwack or smack sound
//				m_pPlayer->m_iWeaponVolume = CROWBAR_BODYHIT_VOLUME;
//
//				if (!pEntity->IsAlive())
//				{
//					m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;	// Vit_amiN: fixed the 'rapid crowbar'
//					m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;	// Vit_amiN: fixed the 'rapid crowbar'
//					m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.5;
//					return TRUE;
//				}
//				else
//					flVol = 0.1;
//
//				fHitWorld = FALSE;
//			}
//		}
//
//		// play texture hit sound
//		// UNDONE: Calculate the correct point of intersection when we hit with the hull instead of the line
//
//		if (fHitWorld)
//		{
//			if (!(pEntity && FClassnameIs(pEntity->pev, "func_breakable")))
//			{
//				Vector vecDir2 = m_pPlayer->FireBullets(1, vecSrc, gpGlobals->v_forward, Vector(0, 0, 0), 32, BULLET_MELEE_CROWBAR_NORM, 0, 0, m_pPlayer->pev, m_pPlayer->random_seed);
//				PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usCrowbar, 0.0, (float*)&g_vecZero, (float*)&g_vecZero,
//					vecDir2.x, vecDir2.y, 0, 0, TRUE, 0, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0.0f, (byte)0);
//			}
//
//			// delay the decal a bit
//			m_trHit = tr;
//		}
//
//		m_pPlayer->m_iWeaponVolume = flVol * CROWBAR_WALLHIT_VOLUME;
//#endif
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
//		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
//		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.5;
//
//		SetThink(&CCrowbar::BigSmack);
//		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
//
//
//	}
//	return fDidHit;
//}
//
//float CCrowbar::GetBlockRegen(void)
//{
//	if (m_bBlocking)
//		return 0.1f;
//
//	return 0.05f;
//}
//
//float CCrowbar::GetBlockAmount(void)
//{
//	return 100.0f;
//}
//
//float CCrowbar::GetBlockDot(void)
//{
//	return -0.74f;
//}
//
//float CCrowbar::GetBlockCooldown(void)
//{
//	return 1.26f;
//}
//
//void CCrowbar::Block(float flDamage)
//{
//	// Play audio and cause vertical punch
//	m_flBlockRegen = GetBlockCooldown();
//
//	// Is this sanity check necessary?
//	if (m_pPlayer)
//	{
//		if (FBitSet(m_pPlayer->pev->button, IN_ATTACK | IN_ATTACK2 | IN_ATTACK3))
//		{
//			if (!CounterSwing(1))
//			{
//				SetThink(&CCrowbar::CounterSwingAgain);
//				pev->nextthink = gpGlobals->time + 0.1;
//			}
//
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//		}
//	}
//
//	return;
//}
//
//void CCrowbar::BlockBreak(float flDamage)
//{
//	// Play audio and cause vertical punch
//	SendWeaponAnim(CROWBAR_BLOCKBREAK);
//	m_flBlockCooldown = GetBlockCooldown() - 0.33f;
//	m_bBlocking = FALSE;
//	m_flBlockAmount = 0.0f;
//	m_flBlockRegen = GetBlockRegen() * 3.0f;
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.9;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.9;
//	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.9;
//}
//
//void CCrowbar::BlockStop(void)
//{
//	SendWeaponAnim(CROWBAR_BLOCKEND);
//	m_flBlockCooldown = GetBlockCooldown() / 2;
//	m_bBlocking = FALSE;
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.68;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.68;
//	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.68;
//}
//
//void CCrowbar::CounterSmack(void)
//{
//	return;
//}
//
//void CCrowbar::CounterSwingAgain(void)
//{
//	CounterSwing(0);
//}
//
//int CCrowbar::CounterSwing(int fFirst)
//{
//	if (fFirst)
//	{
//		m_flBlockAmount = 0.0f;
//		m_bBlocking = FALSE;
//		m_flBlockCooldown = GetBlockCooldown() / 2;
//		m_flBlockRegen = 1.0f;
//	}
//
//	int fDidHit = FALSE;
//
//	TraceResult tr;
//
//	UTIL_MakeVectors(m_pPlayer->pev->v_angle);
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//	Vector vecEnd = vecSrc + gpGlobals->v_forward * 32;
//
//	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
//
//#ifndef CLIENT_DLL
//	if (tr.flFraction >= 1.0)
//	{
//		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, ENT(m_pPlayer->pev), &tr);
//		if (tr.flFraction < 1.0)
//		{
//			// Calculate the point of intersection of the line (or hull) and the object we hit
//			// This is and approximation of the "best" intersection
//			CBaseEntity* pHit = CBaseEntity::Instance(tr.pHit);
//			if (!pHit || pHit->IsBSPModel())
//				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
//			vecEnd = tr.vecEndPos;	// This is the point on the actual surface (the hull could have hit space)
//		}
//	}
//#endif
//
//
//	// Fograin92: Crowbar swing missed
//	if (tr.flFraction >= 1.0)
//	{
//		if (fFirst)
//		{
//			EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/blockswing01.wav", 1, ATTN_NORM);
//
//			SendWeaponAnim(CROWBAR_BLOCKCOUNTER);
//
//			// miss
//			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
//			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
//			m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.5;
//
//			// player "shoot" animation
//			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//		}
//	}
//	else
//	{
//		SendWeaponAnim(CROWBAR_BLOCKCOUNTERHIT);
//
//		// player "shoot" animation
//		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//#ifndef CLIENT_DLL
//
//		// hit
//		fDidHit = TRUE;
//		CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);
//
//		//ClearMultiDamage( );
//
//		pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgCrowbarHeavy, gpGlobals->v_forward, &tr, ID_DMG_CROWBAR_HEAVY);
//		//ApplyMultiDamage( m_pPlayer->pev, m_pPlayer->pev, ID_DMG_GENERIC );
//
//		// play thwack, smack, or dong sound
//		float flVol = 1.0;
//		int fHitWorld = TRUE;
//
//		if (pEntity)
//		{
//			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
//			{
//				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/crowbar/blockhitflesh01.wav", 1, ATTN_NORM);
//				// play thwack or smack sound
//				m_pPlayer->m_iWeaponVolume = CROWBAR_BODYHIT_VOLUME;
//
//				if (!pEntity->IsAlive())
//				{
//					m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;	// Vit_amiN: fixed the 'rapid crowbar'
//					m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;	// Vit_amiN: fixed the 'rapid crowbar'
//					m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.5;
//					return TRUE;
//				}
//				else
//					flVol = 0.1;
//
//				fHitWorld = FALSE;
//			}
//		}
//
//		// play texture hit sound
//		// UNDONE: Calculate the correct point of intersection when we hit with the hull instead of the line
//
//		if (fHitWorld)
//		{
//			if (!(pEntity && FClassnameIs(pEntity->pev, "func_breakable")))
//			{
//				Vector vecDir2 = m_pPlayer->FireBullets(1, vecSrc, gpGlobals->v_forward, Vector(0, 0, 0), 32, BULLET_MELEE_CROWBAR_NORM, 0, 0, m_pPlayer->pev, m_pPlayer->random_seed);
//				PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usCrowbar, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, vecDir2.x, vecDir2.y,
//					0, 0, TRUE, 0, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0.0f, (byte)0);
//			}
//
//			// delay the decal a bit
//			m_trHit = tr;
//		}
//
//		m_pPlayer->m_iWeaponVolume = flVol * CROWBAR_WALLHIT_VOLUME;
//#endif
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
//		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
//		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.5;
//
//		SetThink(&CCrowbar::CounterSmack);
//		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
//
//
//	}
//	return fDidHit;
//}
//
//// Start using the tool
//void CCrowbar::ToolStart(void)
//{
//	if (m_fToolFlags == 0)
//	{
//		m_flToolTime = 0.55f;
//		SendWeaponAnim(CROWBAR_TOOLSTART);
//		m_fToolFlags = 1;
//	}
//}
//
//// Loop it away until you're not using the toolable object
//void CCrowbar::ToolLoop(void)
//{
//	if (m_fToolFlags == 1)
//	{
//		m_fToolFlags = 2;
//		SendWeaponAnim(CROWBAR_TOOLLOOP);
//	}
//}
//
//// End the tooling process and add a delay to when you can normally use this
//void CCrowbar::ToolEnd(void)
//{
//	if (m_fToolFlags != 0)
//	{
//		SendWeaponAnim(CROWBAR_TOOLEND);
//		m_fToolFlags = 0;
//		m_flToolTime = 0.55f;
//		m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 0.55f;
//	}
//}
//
//void CCrowbar::WeaponIdle(void)
//{
//	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase() || m_bBigSwing == TRUE || m_bBlocking == TRUE || m_iThrowing != 0 || m_fToolFlags != 0)
//		return;
//
//	// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//	if (RANDOM_LONG(0, 99) <= 5)
//	{
//		UpdateBodygroup();
//		UnsetIdle();
//
//		if (RANDOM_LONG(0, 1))
//		{
//			SendWeaponAnim(CROWBAR_FIDGET1);
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.77;
//		}
//		else
//		{
//			SendWeaponAnim(CROWBAR_FIDGET2);
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.4;
//		}
//	}
//	else
//	{
//		// Ensure at least two successful loops
//		if (!IsIdle())
//		{
//			UpdateBodygroup();
//			SendWeaponAnim(CROWBAR_IDLE1);
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.4 * 2;
//			SetIdle();
//		}
//		else
//		{
//			// Only perform a single loop in this case
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.4;
//		}
//	}
//}