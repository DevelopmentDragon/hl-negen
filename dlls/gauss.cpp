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
//#include "soundent.h"
//#include "shake.h"
//#include "gamerules.h"
//
//
//#define	GAUSS_PRIMARY_CHARGE_VOLUME	256// how loud gauss is while charging
//#define GAUSS_PRIMARY_FIRE_VOLUME	450// how loud gauss is when discharged
//
//LINK_ENTITY_TO_CLASS(weapon_gauss, CGauss);
//LINK_ENTITY_TO_CLASS(weapon_gaussgun, CGauss);
//LINK_ENTITY_TO_CLASS(weapon_tau, CGauss);
//LINK_ENTITY_TO_CLASS(weapon_taucannon, CGauss);
//
//void CGauss::UpdateBodygroup(void)
//{
//	if (m_pPlayer)
//	{
//		m_pPlayer->pev->viewmodelbody = HasWeaponUpgrades(UPGRADE_GAUSS_CHASSIS)
//			+ HasWeaponUpgrades(UPGRADE_GAUSS_SYSTEM) * 2
//			+ HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 4
//			+ m_pPlayer->pev->armor_type * 8;
//		m_pPlayer->pev->viewmodelskin = 0;
//
//		m_pPlayer->pev->playmodelbody = HasWeaponUpgrades(UPGRADE_GAUSS_CHASSIS) + HasWeaponUpgrades(UPGRADE_GAUSS_SYSTEM) * 2
//			+ HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 4;
//		m_pPlayer->pev->playmodelskin = 0;
//	}
//
//	pev->body = HasWeaponUpgrades(UPGRADE_GAUSS_CHASSIS) + HasWeaponUpgrades(UPGRADE_GAUSS_SYSTEM) * 2
//		+ HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 4;
//	pev->skin = 0;
//}
//
//void CGauss::ItemPostFrame(void)
//{
//	UpdateBodygroup();
//	CBasePlayerWeapon::ItemPostFrame();
//}
//
//#ifdef CLIENT_DLL
//extern int g_irunninggausspred;
//#endif
//
//void CGauss::Spawn()
//{
//	Precache();
//	m_iId = WEAPON_GAUSS;
//	pev->classname = MAKE_STRING("weapon_gauss"); // hack to allow for old names
//	SET_MODEL(ENT(pev), "models/w_gauss.mdl");
//	m_iDefaultAmmo = GAUSS_DEFAULT_GIVE;
//
//	FallInit();// get ready to fall down.
//}
//
//
//void CGauss::Precache(void)
//{
//	PRECACHE_MODEL("models/w_gauss.mdl");
//	PRECACHE_MODEL("models/v_gauss.mdl");
//	PRECACHE_MODEL("models/p_gauss.mdl");
//
//	PRECACHE_SOUND("items/9mmclip1.wav");
//
//	PRECACHE_SOUND("weapons/gauss/fire.wav");
//	PRECACHE_SOUND("weapons/gauss/firecharge.wav");
//	PRECACHE_SOUND("weapons/gauss/charge.wav");
//
//	m_iGlow = PRECACHE_MODEL("sprites/hotglow.spr");
//	m_iBalls = PRECACHE_MODEL("sprites/hotglow.spr");
//	m_iBeam = PRECACHE_MODEL("sprites/smoke.spr");
//
//	m_usGaussFire = PRECACHE_EVENT(1, "events/gauss.sc");
//	m_usGaussSpin = PRECACHE_EVENT(1, "events/gaussspin.sc");
//}
//
//int CGauss::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "cells";
//	p->iMaxAmmo1 = CELLS_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = WEAPON_NOCLIP_RELOAD;
//	p->iSlot = WEAPON_BUCKET_ENERGY;
//	p->iPosition = WEAPON_GAUSS_SLOT;
//	p->iId = m_iId = WEAPON_GAUSS;
//	p->iFlags = 0;
//	p->iWeight = GAUSS_WEIGHT;
//
//	return 1;
//}
//
//int CGauss::HUDIcon(void)
//{
//	return 135 + HasWeaponUpgrades(UPGRADE_GAUSS_CHASSIS) * 2
//		+ HasWeaponUpgrades(UPGRADE_GAUSS_SYSTEM) * 4
//		+ HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 8;
//}
//
//int CGauss::HUDActiveIcon(void)
//{
//	return 136 + HasWeaponUpgrades(UPGRADE_GAUSS_CHASSIS) * 2
//		+ HasWeaponUpgrades(UPGRADE_GAUSS_SYSTEM) * 4
//		+ HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 8;
//}
//
//int CGauss::ModeIcon(void)
//{
//	return -1;
//}
//
//int CGauss::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CGauss::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CGauss::SmallIcon(void)
//{
//	return 77 + +HasWeaponUpgrades(UPGRADE_GAUSS_CHASSIS) * 1
//		+ HasWeaponUpgrades(UPGRADE_GAUSS_SYSTEM) * 2
//		+ HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 4;
//}
//
//float CGauss::GetFullChargeTime(void)
//{
//	if (HasWeaponUpgrades(UPGRADE_GAUSS_SYSTEM))
//	{
//		return 2;
//	}
//
//	return 4;
//}
//
//int CGauss::GetIdealAmmoConsumption(BOOL bPrimary)
//{
//	int result = 1;
//
//	if (bPrimary)
//		result *= 2;
//
//	if (m_bVerticalVelocity)
//		result *= 2;
//
//	return result;
//}
//
//int CGauss::GetAmmoConsumption(BOOL bPrimary)
//{
//	int result = min(m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType], GetIdealAmmoConsumption(bPrimary));
//
//	return result;
//}
//
//BOOL CGauss::Deploy(void)
//{
//	UpdateBodygroup();
//	m_pPlayer->m_flPlayAftershock = 0.0;
//	UnsetIdle();
//	if (HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE))
//		return DefaultDeploy("models/v_gauss.mdl", "models/p_gauss.mdl", GAUSS_DRAW + 9, "AC");
//	else
//		return DefaultDeploy("models/v_gauss.mdl", "models/p_gauss.mdl", GAUSS_DRAW, "gauss");
//}
//
//void CGauss::Holster(int skiplocal /* = 0 */)
//{
//	PLAYBACK_EVENT_FULL(FEV_RELIABLE | FEV_GLOBAL, m_pPlayer->edict(), m_usGaussFire, 0.01, (float*)&m_pPlayer->pev->origin, (float*)&m_pPlayer->pev->angles, 0.0, 0.0,
//		0, m_fWeaponUpgrades, 0, 1, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0.0f, (byte)0);
//
//	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
//
//	SendWeaponAnim(GAUSS_HOLSTER + HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 9);
//	m_fInAttack = 0;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//	UnsetIdle();
//}
//
//void CGauss::Reload(void)
//{
//	if (m_flNextPrimaryAttack >= UTIL_WeaponTimeBase() || m_flNextSecondaryAttack >= UTIL_WeaponTimeBase())
//		return;
//
//	if (m_bVerticalVelocity)
//		m_bVerticalVelocity = FALSE;
//	else
//		m_bVerticalVelocity = TRUE;
//
//	SendWeaponAnim(GAUSS_SWITCH + HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 9);
//
//	UnsetIdle();
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.0;
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//}
//
//void CGauss::PrimaryAttack(void)
//{
//	// don't fire underwater
//	if (m_pPlayer->pev->waterlevel == 3)
//	{
//		PlayEmptySound();
//		m_flNextSecondaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.15;
//		return;
//	}
//
//	if (!HasPrimaryAmmo(TRUE))
//	{
//		PlayEmptySound();
//		m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
//		return;
//	}
//
//	m_pPlayer->m_iWeaponVolume = GAUSS_PRIMARY_FIRE_VOLUME;
//	m_fPrimaryFire = TRUE;
//
//	if (m_pPlayer->m_flInfiniteAmmo < 1)
//		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] -= GetAmmoConsumption(TRUE);
//
//	StartFire();
//	m_fInAttack = 0;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.2 - 0.1 * HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE);
//	UnsetIdle();
//}
//
//void CGauss::SecondaryAttack(void)
//{
//	// don't fire underwater
//	if (m_pPlayer->pev->waterlevel == 3)
//	{
//		if (m_fInAttack != 0)
//		{
//			SendWeaponAnim(GAUSS_IDLE + HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 9);
//			m_fInAttack = 0;
//		}
//		else
//		{
//			PlayEmptySound();
//		}
//
//		m_flNextSecondaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
//		return;
//	}
//
//	UnsetIdle();
//
//	if (m_fInAttack == 0)
//	{
//		if (!HasPrimaryAmmo(TRUE))
//		{
//			EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/357_cock1.wav", 0.8, ATTN_NORM);
//			m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
//			return;
//		}
//
//		m_fPrimaryFire = FALSE;
//
//		if (!HasInfinitePrimaryAmmo())
//			m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;// take one ammo just to start the spin
//
//		m_pPlayer->m_flNextAmmoBurn = UTIL_WeaponTimeBase();
//
//		// spin up
//		m_pPlayer->m_iWeaponVolume = GAUSS_PRIMARY_CHARGE_VOLUME;
//
//		SendWeaponAnim(GAUSS_SPINUP + HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 9);
//		m_fInAttack = 1;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 0.5;
//		m_pPlayer->m_flStartCharge = gpGlobals->time;
//		m_pPlayer->m_flAmmoStartCharge = UTIL_WeaponTimeBase() + GetFullChargeTime();
//
//		PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usGaussSpin, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0,
//			110, m_fWeaponUpgrades, 0, 0, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0.0f, (byte)0);
//
//		m_iSoundState = SND_CHANGE_PITCH;
//	}
//	else if (m_fInAttack == 1)
//	{
//		if (m_flNextWeaponIdle < UTIL_WeaponTimeBase())
//		{
//			SendWeaponAnim(GAUSS_SPIN + HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 9);
//			m_fInAttack = 2;
//		}
//	}
//	else
//	{
//		// during the charging process, eat one bit of ammo every once in a while
//		if (UTIL_WeaponTimeBase() >= m_pPlayer->m_flNextAmmoBurn && m_pPlayer->m_flNextAmmoBurn != 1000)
//		{
//			if (m_pPlayer->m_flInfiniteAmmo < 1)
//				m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] -= GetAmmoConsumption(FALSE);
//
//			m_pPlayer->m_flNextAmmoBurn = UTIL_WeaponTimeBase() + 0.15;
//		}
//
//		if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 && m_pPlayer->m_flInfiniteAmmo < 1)
//		{
//			// out of ammo! force the gun to fire
//			StartFire();
//			m_fInAttack = 0;
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//			m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 1;
//			return;
//		}
//
//		if (UTIL_WeaponTimeBase() >= m_pPlayer->m_flAmmoStartCharge)
//		{
//			// don't eat any more ammo after gun is fully charged.
//			m_pPlayer->m_flNextAmmoBurn = 1000;
//		}
//
//		int pitch = (gpGlobals->time - m_pPlayer->m_flStartCharge) * (150 / GetFullChargeTime()) + 100;
//		if (pitch > 250)
//			pitch = 250;
//
//		// ALERT( at_console, "%d %d %d\n", m_fInAttack, m_iSoundState, pitch );
//
//		if (m_iSoundState == 0)
//			ALERT(at_console, "sound state %d\n", m_iSoundState);
//
//		PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usGaussSpin, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0,
//			pitch, m_fWeaponUpgrades, (m_iSoundState == SND_CHANGE_PITCH) ? 1 : 0, 0, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0.0f, (byte)0);
//
//		m_iSoundState = SND_CHANGE_PITCH; // hack for going through level transitions
//
//		m_pPlayer->m_iWeaponVolume = GAUSS_PRIMARY_CHARGE_VOLUME;
//
//		// m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 0.1;
//		if (m_pPlayer->m_flStartCharge < gpGlobals->time - 10)
//		{
//			// Player charged up too long. Zap him.
//
//			m_fInAttack = 0;
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//			m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 1.0;
//
//#ifndef CLIENT_DLL
//			m_pPlayer->TakeDamage(VARS(eoNullEntity), VARS(eoNullEntity), 50, DMG_SHOCK, ID_DMG_GAUSS_SELFSHOCK);
//			UTIL_ScreenFade(m_pPlayer, Vector(255, 128, 0), 2, 0.5, 128, FFADE_IN);
//#endif
//			SendWeaponAnim(GAUSS_IDLE + HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 9);
//
//			// Player may have been killed and this weapon dropped, don't execute any more code after this!
//			return;
//		}
//
//	}
//}
//
////=========================================================
//// StartFire- since all of this code has to run and then 
//// call Fire(), it was easier at this point to rip it out 
//// of weaponidle() and make its own function then to try to
//// merge this into Fire(), which has some identical variable names 
////=========================================================
//void CGauss::StartFire(void)
//{
//	float flDamage = gSkillData.plrDmgGaussRail;
//
//	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
//	Vector vecAiming = gpGlobals->v_forward;
//	Vector vecSrc = m_pPlayer->GetGunPosition(); // + gpGlobals->v_up * -8 + gpGlobals->v_right * 8;
//
//	if (!m_fPrimaryFire)
//	{
//		if (gpGlobals->time - m_pPlayer->m_flStartCharge > GetFullChargeTime())
//		{
//			flDamage = 200;
//		}
//		else
//		{
//			flDamage = 200 * ((gpGlobals->time - m_pPlayer->m_flStartCharge) / GetFullChargeTime());
//		}
//	}
//
//	flDamage *= (1.0 + 0.25 * m_bVerticalVelocity + 0.5 * HasWeaponUpgrades(UPGRADE_GAUSS_CHASSIS));
//
//#ifndef CLIENT_DLL
//	Vector vecPlayer = m_pPlayer->pev->velocity;
//
//	if (!m_bVerticalVelocity)
//	{
//		m_pPlayer->pev->velocity = vecPlayer;
//	}
//	else
//	{
//		if (m_fPrimaryFire)
//		{
//			m_pPlayer->pev->velocity = m_pPlayer->pev->velocity - gpGlobals->v_forward * flDamage * 5
//				* (1.0 + 0.5 * (HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE)));
//			m_pPlayer->pev->velocity.z = vecPlayer.z; // Primary fire only controls x and y velocity.
//		}
//		else
//		{
//			m_pPlayer->pev->velocity = -gpGlobals->v_forward * flDamage * (2.5 + 2.5 * (HasWeaponUpgrades(UPGRADE_GAUSS_CHASSIS)))
//				* (1.0 + 0.5 * (HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE))) * ((gpGlobals->time - m_pPlayer->m_flStartCharge) / GetFullChargeTime());
//		}
//	}
//
//#endif
//	// player "shoot" animation
//	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//	//}
//
//	// time until aftershock 'static discharge' sound
//	m_pPlayer->m_flPlayAftershock = gpGlobals->time + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 0.3, 0.8);
//
//	Fire(vecSrc, vecAiming, flDamage);
//}
//
//void CGauss::Fire(Vector vecOrigSrc, Vector vecDir, float flDamage)
//{
//	m_pPlayer->m_iWeaponVolume = GAUSS_PRIMARY_FIRE_VOLUME;
//
//	Vector vecSrc = vecOrigSrc;
//	Vector vecDest = vecSrc + vecDir * 8192;
//	edict_t* pentIgnore;
//	TraceResult tr, beam_tr;
//	float flMaxFrac = 1.0;
//	int	nTotal = 0;
//	int fHasPunched = 0;
//	int fFirstBeam = 1;
//	int	nMaxHits = 10;
//
//	pentIgnore = ENT(m_pPlayer->pev);
//
//#ifdef CLIENT_DLL
//	if (m_fPrimaryFire == false)
//		g_irunninggausspred = true;
//#endif
//
//	// The main firing event is sent unreliably so it won't be delayed.
//	int iAnim = m_pPlayer->pev->savedvanim = (m_fPrimaryFire ? GAUSS_FIRE : GAUSS_FIRE2) + HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * GAUSS_IDLE_HANDLE;
//	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
//	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//
//	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usGaussFire, 0.0, (float*)&m_pPlayer->pev->origin, (float*)&m_pPlayer->pev->angles, flDamage, 0.0,
//		0, m_fWeaponUpgrades, m_fPrimaryFire ? 1 : 0, 0, (float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);
//
//	// This reliable event is used to stop the spinning sound
//	// It's delayed by a fraction of second to make sure it is delayed by 1 frame on the client
//	// It's sent reliably anyway, which could lead to other delays
//
//	PLAYBACK_EVENT_FULL(FEV_NOTHOST | FEV_RELIABLE, m_pPlayer->edict(), m_usGaussFire, 0.01, (float*)&m_pPlayer->pev->origin, (float*)&m_pPlayer->pev->angles, 0.0,
//		0.0, 0, m_fWeaponUpgrades, 0, 1, (float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);
//
//
//	/*ALERT( at_console, "%f %f %f\n%f %f %f\n",
//		vecSrc.x, vecSrc.y, vecSrc.z,
//		vecDest.x, vecDest.y, vecDest.z );*/
//
//
//		//	ALERT( at_console, "%f %f\n", tr.flFraction, flMaxFrac );
//
//#ifndef CLIENT_DLL
//	while (flDamage > 10 && nMaxHits > 0)
//	{
//		nMaxHits--;
//
//		// ALERT( at_console, "." );
//		UTIL_TraceLine(vecSrc, vecDest, dont_ignore_monsters, pentIgnore, &tr);
//
//		if (tr.fAllSolid)
//			break;
//
//		CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);
//
//		if (pEntity == NULL)
//			break;
//
//		if (fFirstBeam)
//		{
//			m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
//			fFirstBeam = 0;
//
//			nTotal += 26;
//		}
//
//		if (pEntity->pev->takedamage)
//		{
//			//ClearMultiDamage();
//			pEntity->TraceAttack(m_pPlayer->pev, flDamage, vecDir, &tr, DMG_BULLET, ID_DMG_GAUSS);
//			//ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev, ID_DMG_GENERIC);
//		}
//
//		if (pEntity->ReflectGauss())
//		{
//			float n;
//
//			pentIgnore = NULL;
//
//			n = -DotProduct(tr.vecPlaneNormal, vecDir);
//
//			if (n < 0.5) // 60 degrees
//			{
//				// ALERT( at_console, "reflect %f\n", n );
//				// reflect
//				Vector r;
//
//				r = 2.0 * tr.vecPlaneNormal * n + vecDir;
//				flMaxFrac = flMaxFrac - tr.flFraction;
//				vecDir = r;
//				vecSrc = tr.vecEndPos + vecDir * 8;
//				vecDest = vecSrc + vecDir * 8192;
//
//				// explode a bit
//				m_pPlayer->RadiusDamage(tr.vecEndPos, pev, m_pPlayer->pev, flDamage * n, CLASS_NONE, DMG_BLAST, ID_DMG_GAUSS_BLAST);
//
//				nTotal += 34;
//
//				// lose energy
//				if (n == 0) n = 0.1;
//				flDamage = flDamage * (1 - n);
//			}
//			else
//			{
//				nTotal += 13;
//
//				// limit it to one hole punch
//				if (fHasPunched)
//					break;
//				fHasPunched = 1;
//
//				// try punching through wall if secondary attack (primary is incapable of breaking through)
//				if (!m_fPrimaryFire)
//				{
//					UTIL_TraceLine(tr.vecEndPos + vecDir * 8, vecDest, dont_ignore_monsters, pentIgnore, &beam_tr);
//					if (!beam_tr.fAllSolid)
//					{
//						// trace backwards to find exit point
//						UTIL_TraceLine(beam_tr.vecEndPos, tr.vecEndPos, dont_ignore_monsters, pentIgnore, &beam_tr);
//
//						float n = (beam_tr.vecEndPos - tr.vecEndPos).Length();
//
//						if (n < flDamage)
//						{
//							if (n == 0) n = 1;
//							flDamage -= n;
//
//							// ALERT( at_console, "punch %f\n", n );
//							nTotal += 21;
//
//							float damage_radius;
//
//
//							if (!HasWeaponUpgrades(UPGRADE_GAUSS_CHASSIS))
//							{
//								damage_radius = flDamage * 1.75;  // Old code == 2.5
//							}
//							else
//							{
//								damage_radius = flDamage * 2.5;
//							}
//
//							::RadiusDamage(beam_tr.vecEndPos + vecDir * 8, pev, m_pPlayer->pev, flDamage, damage_radius, CLASS_NONE, DMG_BLAST, ID_DMG_GAUSS_BLAST);
//
//							CSoundEnt::InsertSound(bits_SOUND_COMBAT, pev->origin, NORMAL_EXPLOSION_VOLUME, 3.0);
//
//							nTotal += 53;
//
//							vecSrc = beam_tr.vecEndPos + vecDir;
//						}
//					}
//					else
//					{
//						//ALERT( at_console, "blocked %f\n", n );
//						flDamage = 0;
//					}
//				}
//				else
//				{
//					//ALERT( at_console, "blocked solid\n" );
//
//					flDamage = 0;
//				}
//
//			}
//		}
//		else
//		{
//			vecSrc = tr.vecEndPos + vecDir;
//			pentIgnore = ENT(pEntity->pev);
//		}
//	}
//#endif
//	// ALERT( at_console, "%d bytes\n", nTotal );
//}
//
//
//
//
//void CGauss::WeaponIdle(void)
//{
//	ResetEmptySound();
//
//	// play aftershock static discharge
//	if (m_pPlayer->m_flPlayAftershock && m_pPlayer->m_flPlayAftershock < gpGlobals->time)
//	{
//		m_pPlayer->m_flPlayAftershock = 0.0;
//	}
//
//	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase())
//		return;
//
//	if (m_fInAttack != 0)
//	{
//		StartFire();
//		m_fInAttack = 0;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//	}
//	else
//	{
//		// 4.067 - 3.03 - 4.067 - 2.367
//		// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//		if (RANDOM_LONG(0, 99) <= 5)
//		{
//			SendWeaponAnim(GAUSS_FIDGET + HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 9);
//			UnsetIdle();
//			if (HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE))
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.367;
//			else
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.03;
//		}
//		else
//		{
//			// Ensure at least two successful loops
//			if (!IsIdle())
//			{
//				UpdateBodygroup();
//				SendWeaponAnim(GAUSS_IDLE + HasWeaponUpgrades(UPGRADE_GAUSS_HANDLE) * 9);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 4.067 * 2;
//				SetIdle();
//			}
//			else
//			{
//				// Only perform a single loop in this case
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 4.067;
//			}
//		}
//	}
//}
//
//class CGaussAmmo : public CBasePlayerAmmo
//{
//public:
//	CGaussAmmo(void)
//	{
//		m_szModel = MAKE_STRING("models/ammo_isotope.mdl");
//		m_szAmmoType = MAKE_STRING("cells");
//		m_szPickupSound = MAKE_STRING("weapons/gauss/ammo.wav");
//		m_iAmmoAmount = AMMO_GAUSS_GIVE;
//	}
//	void Spawn(void)
//	{
//		CBasePlayerAmmo::Spawn();
//		pev->classname = MAKE_STRING("ammo_cells"); // Added for compatiblity
//	}
//};
//LINK_ENTITY_TO_CLASS(ammo_cells, CGaussAmmo);
//LINK_ENTITY_TO_CLASS(ammo_gaussclip, CGaussAmmo);
