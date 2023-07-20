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

LINK_ENTITY_TO_CLASS(weapon_mp5, CMP5);
LINK_ENTITY_TO_CLASS(weapon_9mmAR, CMP5); // Added for compatibility

// Firing modes are handled by weapon status flags
// MP5_BURST3 = 3 round burst
// MP5_BURST2 = 2 round burst
// MP5_BURST3 + MP5_BURST2 = Semi Auto
#define MP5_STF_SWITCH_DIR	WEAPON_STF_CUSTOM5
#define MP5_STF_BURST3	WEAPON_STF_CUSTOM6
#define MP5_STF_BURST2	WEAPON_STF_CUSTOM7

#define MP5_MAX_CLIP	30
#define MP5_ALT_MAX_CLIP 1

#ifndef CLIENT_DLL

	TYPEDESCRIPTION	CMP5::m_SaveData[] =
	{
		DEFINE_ARRAY(CMP5, m_iClips, FIELD_INTEGER, 2),
		DEFINE_ARRAY(CMP5, m_iMaxClips, FIELD_INTEGER, 2),
		DEFINE_ARRAY(CMP5, m_iChamberedRounds, FIELD_INTEGER, 2),
		DEFINE_ARRAY(CMP5, m_iMaxChamberedRounds, FIELD_INTEGER, 2),
		DEFINE_ARRAY(CMP5, m_iAmmoIndices, FIELD_INTEGER, 2),
		DEFINE_ARRAY(CMP5, m_iPreReloadClips, FIELD_INTEGER, 2),
		DEFINE_ARRAY(CMP5, m_iTargetAmmoIndex, FIELD_INTEGER, 2),
	};

	IMPLEMENT_SAVERESTORE(CMP5, CBasePlayerWeapon);

#endif

//=========================================================

weaponInfo CMP5::m_weaponInfo = {

	{ 1, { "9mm","9mmI","9mmE","9mmIE","9mmAP","9mmAPI","9mmAPE","9amAPEI","9mmHP","9mmHPI","9mmHPE","9amHPIE" } },
	{ 1, { "40mm","40mmHE","40mmF","40mmI","40mmB","40mmS","40mmG","40mm+" } },
};

legalAmmoTypes CMP5::m_legalAmmoIndicies = GenerateLegalAmmoIndicies(CMP5::m_weaponInfo);

CMP5::CMP5(void)
{
	m_usMP5 = 0;
	m_usMP52 = 0;
	m_iShell = 0;
	m_fWeaponFlags = WEAPON_FLAG_CHAMBER_ROUND;

	// Max clips defaults are defined here
	m_iClips[0] = m_iMaxClips[0] = MP5_MAX_CLIP;
	m_iClips[1] = m_iMaxClips[1] = MP5_ALT_MAX_CLIP;

	// Chambered rounds default set here
	m_iChamberedRounds[0] = m_iMaxChamberedRounds[0] = 1;
	m_iChamberedRounds[1] = m_iMaxChamberedRounds[1] = 1;

	m_iAmmoIndices[0] = 0;
	m_iAmmoIndices[1] = 0;

	m_iPreReloadClips[0] = -1;
	m_iPreReloadClips[1] = -1;

	m_iTargetAmmoIndex[0] = -1;
	m_iTargetAmmoIndex[1] = -1;
}

//=========================================================

int CMP5::HUDIcon(void)
{
	return 43 + HasWeaponUpgrades(UPGRADE_MP5_SUPRESSOR) * 2
		+ HasWeaponUpgrades(UPGRADE_MP5_CHASSIS) * 4
		+ HasWeaponUpgrades(UPGRADE_MP5_BARREL) * 8
		+ HasWeaponUpgrades(UPGRADE_MP5_SYSTEMS) * 16;
}

int CMP5::HUDActiveIcon(void)
{
	return 44 + HasWeaponUpgrades(UPGRADE_MP5_SUPRESSOR) * 2
		+ HasWeaponUpgrades(UPGRADE_MP5_CHASSIS) * 4
		+ HasWeaponUpgrades(UPGRADE_MP5_BARREL) * 8
		+ HasWeaponUpgrades(UPGRADE_MP5_SYSTEMS) * 16;
}

int CMP5::ModeIcon(void)
{
	return -1;
}

int CMP5::ModeIcon2(void)
{
	return -1;
}

int CMP5::ModeIcon3(void)
{
	return -1;
}

int CMP5::SmallIcon(void)
{
	return 26 + HasWeaponUpgrades(UPGRADE_MP5_SUPRESSOR)
		+ HasWeaponUpgrades(UPGRADE_MP5_CHASSIS) * 2
		+ HasWeaponUpgrades(UPGRADE_MP5_BARREL) * 4
		+ HasWeaponUpgrades(UPGRADE_MP5_SYSTEMS) * 8;
}

void CMP5::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_mp5"); // hack to allow for old names
	Precache();
	SET_MODEL(ENT(pev), "models/w_mp5.mdl");
	m_iId = WEAPON_MP5;
	m_iDefaultAmmo = MP5_MAX_CLIP;
	FallInit();// get ready to fall down.
	m_iAmmoIndices;
}

void CMP5::Precache(void)
{
	m_iShell = PRECACHE_MODEL("models/shells/9mmh.mdl");// brass shellTE_MODEL

	PRECACHE_MODEL("models/proj_40mm.mdl");	// grenade

	PRECACHE_MODEL("models/v_mp5.mdl");
	PRECACHE_MODEL("models/w_mp5.mdl");
	PRECACHE_MODEL("models/p_mp5.mdl");

	PRECACHE_SOUND("weapons/mp5/fire.wav");// H to the K
	//PRECACHE_SOUND("weapons/mp5/firepent.wav");// H to the K
	//PRECACHE_SOUND("weapons/mp5/firesil.wav");// H to the K
	//PRECACHE_SOUND("weapons/mp5/firesilpent.wav");// H to the K
	//PRECACHE_SOUND("weapons/mp5/firesuper.wav");// H to the K
	//PRECACHE_SOUND("weapons/mp5/firesuperpent.wav");// H to the K
	//PRECACHE_SOUND("weapons/mp5/firesupersil.wav");// H to the K
	//PRECACHE_SOUND("weapons/mp5/firesupersilpent.wav");// H to the K
	PRECACHE_SOUND("weapons/mp5/dry.wav");
	PRECACHE_SOUND("weapons/mp5/alt_fire.wav");
	PRECACHE_SOUND("weapons/mp5/switchback.wav");
	PRECACHE_SOUND("weapons/mp5/switchforward.wav");
	PRECACHE_SOUND("weapons/mp5/swing.wav");
	PRECACHE_SOUND("weapons/mp5/swinghitflesh.wav");
	PRECACHE_SOUND("weapons/mp5/swinghit.wav");
	//PRECACHE_SOUND("weapons/mp5/alt_firepent.wav");
	//PRECACHE_SOUND("weapons/mp5/alt_dry.wav");
	//PRECACHE_SOUND("weapons/mp5/pickup.wav");// H to the K

	m_usMP5 = PRECACHE_EVENT(1, "events/mp5.sc");
	m_usMP52 = PRECACHE_EVENT(1, "events/mp52.sc");
}

int CMP5::GetItemInfo(ItemInfo* p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "9mmh";
	p->iMaxAmmo1 = _9MMH_MAX_CARRY;
	p->pszAmmo2 = "40mm";
	p->iMaxAmmo2 = _40MM_MAX_CARRY;
	p->iSlot = WEAPON_BUCKET_AUTOMATIC;
	p->iPosition = WEAPON_MP5_SLOT;
	p->iFlags = ITEM_FLAG_DUPLICATION;
	p->iId = m_iId = WEAPON_MP5;
	p->iWeight = MP5_WEIGHT;
	return 1;
}

void CMP5::ItemPostFrame(void)
{
	UpdateBodygroup();
	if (m_pPlayer)
		m_pPlayer->GetAutoaimVector(0.5);
	CBasePlayerWeapon::ItemPostFrame();
}

void CMP5::UpdateBodygroup(void)
{
	if (m_pPlayer)
	{
		m_pPlayer->pev->viewmodelbody = m_pPlayer->pev->playmodelbody
			= HasWeaponUpgrades(UPGRADE_MP5_SUPRESSOR) + HasWeaponUpgrades(UPGRADE_MP5_CHASSIS) * 2;
		m_pPlayer->pev->viewmodelskin = m_pPlayer->pev->playmodelskin = m_iWeaponLooks;
	}

	pev->body = HasWeaponUpgrades(UPGRADE_MP5_SUPRESSOR) + HasWeaponUpgrades(UPGRADE_MP5_CHASSIS) * 2;
	pev->skin = m_iWeaponLooks;
}

void CMP5::PickupSound(void)
{
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/mp5/pickup.wav", 1, ATTN_NORM);
}

void CMP5::DropSound(void)
{
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/mp5/drop.wav", 1, ATTN_NORM);
}

BOOL CMP5::Deploy(void)
{
	UpdateBodygroup();
	UnsetIdle();
	return DefaultDeploy("models/v_mp5.mdl", "models/p_mp5.mdl", MP5_DRAW, "mp5");
}

void CMP5::Holster(int skiplocal)
{
	UnsetIdle();
	SendWeaponAnim(MP5_HOLSTER);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = m_flNextReload = UTIL_WeaponTimeBase() + 1.0;
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
}

void CMP5::PrimaryAttack(void)
{
	// Burst fire logic, what the hell is this
	if (HasSemiFired())
	{
		if (GetBurstMax() > 0)
		{
			if (GetBurst() < 1)
			{
				return;
			}
			else
			{
				// Empty and Infinite ammo cases as well as underwater cases
				if (!HasClipAmmoIndex(0,AMMO_CHECK_DEFAULT_PARAMS) || m_pPlayer->pev->waterlevel == 3)
				{
					EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/mp5/dry.wav", 1, ATTN_NORM);
					m_flNextPrimaryAttack = 0.15;
					SetBurst(GetBurst() - 1);
					return;
				}
			}
		}
		else
		{
			// Leave this, don't do it again
			return;
		}
	}
	else
	{
		if (!HasClipAmmoIndex(0, AMMO_CHECK_DEFAULT_PARAMS) || m_pPlayer->pev->waterlevel == 3)
		{
			EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/mp5/dry.wav", 1, ATTN_NORM);
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.15;
			SetSemiFired();
			SetBursts(0, 0);
			return;
		}

		if (HasWeaponStatusFlags(MP5_STF_BURST2 | MP5_STF_BURST3, FC_ALL))
		{
			SetBursts(0, 0);
			SetSemiFired();
		}
		else if (HasWeaponStatusFlags(MP5_STF_BURST3))
		{
			SetBursts(3, 3);
			SetSemiFired();
		}
		else if (HasWeaponStatusFlags(MP5_STF_BURST2))
		{
			SetBursts(2, 2);
			SetSemiFired();
		}
		else
		{
			// Empty and Infinite ammo cases as well as underwater cases
			SetBursts(0, 0);
		}
	}

	m_pPlayer->pev->effects = (int)(m_pPlayer->pev->effects) | EF_MUZZLEFLASH;
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecAiming = m_pPlayer->GetAutoaimVector(0.5);
	Vector vecDir;

	// Little Badis: Control Bullet Damage

	Vector vecRecoil = VECTOR_CONE_4DEGREES;
	if (HasWeaponUpgrades(UPGRADE_MP5_BARREL))
		vecRecoil = VECTOR_CONE_2DEGREES;

	int iBulletType = BULLET_9MMH + (HasWeaponUpgrades(UPGRADE_MP5_SUPRESSOR) * 1) + (HasWeaponUpgrades(UPGRADE_MP5_CHASSIS) * 2);

	vecDir = m_pPlayer->FireBullets(1, vecSrc, vecAiming, vecRecoil, 8192, iBulletType, 2, 0, m_pPlayer->pev, m_pPlayer->random_seed);

#ifndef CLIENT_DLL
	if (m_pPlayer)
	{
		m_pPlayer->SendWeaponRecoilTest(10);
	}
#endif

	int iAnim = m_pPlayer->pev->savedvanim = RANDOM_LONG(MP5_FIRE1, MP5_FIRE3)
		+ HasWeaponUpgrades(UPGRADE_MP5_SUPRESSOR) * (MP5_FIRE_SD1 - MP5_FIRE1)
		+ HasWeaponUpgrades(UPGRADE_MP5_CHASSIS) * (MP5_FIRE_ELITE1 - MP5_FIRE1);
	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;

	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usMP5, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, vecDir.x, vecDir.y, 0, 0,
		HasWeaponUpgrades(UPGRADE_MP5_SUPRESSOR), HasWeaponUpgrades(UPGRADE_MP5_CHASSIS),
		(float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);

	// Infinite ammo case
	if (!HasInfiniteClipAmmo(AMMO_CHECK_DEFAULT_PARAMS))
		DecrementClip(0, 1);

	if (!HasClipAmmoIndex(0,AMMO_CHECK_DEFAULT_PARAMS) && !HasAmmoIndex(GetClipAmmoIndex(0), AMMO_CHECK_DEFAULT_PARAMS))
		// HEV suit - indicate out of ammo condition
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);

	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);

	UnsetIdle();

	BOOL bBurst = BOOL(HasWeaponStatusFlags(MP5_STF_BURST2 | MP5_STF_BURST3, FC_ANY) && !HasWeaponStatusFlags(MP5_STF_BURST2 | MP5_STF_BURST3, FC_ALL));
	if (bBurst)
	{
		SetBurst(GetBurst() - 1);
	}
	else
	{
		SetBursts(0, 0);
	}

	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.085 + 0.015 * bBurst;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.085 + 0.015 * bBurst;
	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.085 + 0.015 * bBurst;
	m_flNextReload = UTIL_WeaponTimeBase() + 0.7 + 0.015 * bBurst;
	if (HasWeaponUpgrades(UPGRADE_MP5_SYSTEMS))
	{
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.065 + 0.015 * bBurst;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.065 + 0.015 * bBurst;
		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.065 + 0.015 * bBurst;
		m_flNextReload = UTIL_WeaponTimeBase() + 0.7 + 0.015 * bBurst;
	}

	ALERT(at_console, "m_iClips[0]: %d\n", m_iClips[0]);
}

void CMP5::SecondaryAttack(void)
{
	// don't fire underwater or when out of ammo
	if (!HasClipAmmo(1) || m_pPlayer->pev->waterlevel == 3)
	{
		EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/mp5/alt_dry.wav", 1, ATTN_NORM);
		m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.15;
		return;
	}

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	m_pPlayer->m_iExtraSoundTypes = bits_SOUND_DANGER;
	m_pPlayer->m_flStopExtraSoundTime = UTIL_WeaponTimeBase() + 0.2;

	if (HasClipAmmo(1))
		m_iClips[1]--;

	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	// we don't add in player velocity anymore.
	CGrenade* pGrenade = CGrenade::ShootContact(m_pPlayer->pev,
		m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_forward * 16,
		gpGlobals->v_forward * 800 * (float)(1.0 + 0.5 * (float)HasWeaponUpgrades(UPGRADE_MP5_CHASSIS)));

	// Little Badis: Always plays
	//PLAYBACK_EVENT( FEV_NOTHOST, m_pPlayer->edict(), m_usMP52 );

	int iAnim = m_pPlayer->pev->savedvanim = MP5_GRENADE;
	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;

	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usMP52, 0.0, NULL, NULL, 0.0, 0.0,
		m_pPlayer->pev->viewmodelbody, 0, 0, 0, (float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);

	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.13;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.13;
	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.13;
	m_flNextReload = UTIL_WeaponTimeBase() + 1.13;
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5;// idle pretty soon after shooting.

	UnsetIdle();

	if (HasAmmoIndex(GetClipAmmoIndex(1), AMMO_CHECK_DEFAULT_PARAMS))
		// HEV suit - indicate out of ammo condition
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
}

void CMP5::TertiaryAttack(void)
{
	if (!(m_pPlayer->pev->button & (IN_ATTACK | IN_ATTACK2)))
		return;

	BOOL bSuccess = FALSE;

	if (m_pPlayer->pev->button & IN_ATTACK)
	{
		if (!HasWeaponStatusFlags(MP5_STF_BURST2 | MP5_STF_BURST3, FC_NONE))
		{
			if (HasWeaponStatusFlags(MP5_STF_BURST3))
			{
				SetWeaponStatusFlags(MP5_STF_BURST3, FALSE);
			}
			else
			{
				SetWeaponStatusFlags(MP5_STF_BURST2, FALSE);
				SetWeaponStatusFlags(MP5_STF_BURST3, TRUE);
			}
			bSuccess = TRUE;
			SendWeaponAnim(MP5_SWITCH_UP);
			EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/mp5/switchback.wav", 1, ATTN_NORM);
		}
	}
	else
	{
		if (!(HasWeaponStatusFlags(MP5_STF_BURST2 | MP5_STF_BURST3, FC_ALL)))
		{
			if (!HasWeaponStatusFlags(MP5_STF_BURST3))
			{
				SetWeaponStatusFlags(MP5_STF_BURST3, TRUE);
			}
			else
			{
				SetWeaponStatusFlags(MP5_STF_BURST2, TRUE);
				SetWeaponStatusFlags(MP5_STF_BURST3, FALSE);
			}
			bSuccess = TRUE;
			SendWeaponAnim(MP5_SWITCH_DOWN);
			EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/mp5/switchforward.wav", 1, ATTN_NORM);
		}
	}

	// Only do these if we are successful
	if (bSuccess)
	{
		ALERT(at_console, "Mode: %d\n", HasWeaponStatusFlags(MP5_STF_BURST3) + HasWeaponStatusFlags(MP5_STF_BURST2) * 2);
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.44;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.44;
		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.44;
		m_flNextReload = UTIL_WeaponTimeBase() + 0.44;
		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;// idle pretty soon after shooting.
	}
}

void CMP5::QuaternaryAttack(void)
{
	/*
	int fDidHit = FALSE;

	TraceResult tr;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecEnd = vecSrc + gpGlobals->v_forward * 32;

	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);

#ifndef CLIENT_DLL
	if (tr.flFraction >= 1.0)
	{
		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, ENT(m_pPlayer->pev), &tr);
		if (tr.flFraction < 1.0)
		{
			// Calculate the point of intersection of the line (or hull) and the object we hit
			// This is and approximation of the "best" intersection
			CBaseEntity* pHit = CBaseEntity::Instance(tr.pHit);
			if (!pHit || pHit->IsBSPModel())
				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
			vecEnd = tr.vecEndPos;	// This is the point on the actual surface (the hull could have hit space)
		}
	}
#endif

	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/mp5/swing.wav", 1, ATTN_NORM);
	SendWeaponAnim(MP5_SWING);
	// miss
	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.72;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.72;
	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.72;
	m_flNextQuaternaryAttack = UTIL_WeaponTimeBase() + 0.72;
	m_flNextQuinaryAttack = UTIL_WeaponTimeBase() + 0.72;

	ALERT(at_console, "long long is %d bytes wide!\n", sizeof(long long));
	ALERT(at_console, "Max long long is %llu!\n", (unsigned long long)((long long)1 << (long long)63));

	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	if (tr.flFraction < 1.0)
	{
#ifndef CLIENT_DLL

		// hit
		fDidHit = TRUE;
		CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);

		float flVol = 1.0;
		int fHitWorld = TRUE;

		if (pEntity)
		{
			pEntity->TakeDamage(m_pPlayer->pev, m_pPlayer->pev, gSkillData.plrDmgCrowbarHeavy, ID_DMG_CROWBAR_HEAVY);

			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
			{
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON3, "weapons/mp5/swinghitflesh.wav", 1, ATTN_NORM);
				// play thwack or smack sound
				m_pPlayer->m_iWeaponVolume = 10;

				fHitWorld = FALSE;
			}
			else
			{
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON3, "weapons/mp5/swinghit.wav", 1, ATTN_NORM);
			}
		}

		m_pPlayer->m_iWeaponVolume = flVol * 10;
#endif

	}
	*/
}

void CMP5::QuinaryAttack(void)
{
	if (InReload())
		return;

	BOOL bGoThrough = FALSE;

	// don't fire underwater or when out of ammo
	if (GetCurrentAmmoType(0) == 0)
	{
		if (HasAmmoIndex(1, AMMO_CHECK_DEFAULT_PARAMS))
			bGoThrough = TRUE;

		if (bGoThrough)
			SetTargetAmmoIndex(0, 1);
	}
	else
	{
		if (HasAmmoIndex(0, AMMO_CHECK_DEFAULT_PARAMS))
			bGoThrough = TRUE;

		if (bGoThrough)
			SetTargetAmmoIndex(0, 0);
	}


	if (bGoThrough)
	{
		ALERT(at_console, "Legal ammo index: %d\n", GetClipAmmoLegalIndex(0));
		SetAmmoSwitch();
		SetReloadStart();
		UnsetIdle();
	}

	return;
}

// ShouldReload: Should we reload this weapon?
// If amount in clip is lesser than max clip or max clip + one if we're allowing over 1 cap
// If we have primary ammo
BOOL CMP5::ShouldReload(int iClipIndex)
{
	return ((GetClip(iClipIndex) < GetMaxClip(iClipIndex) + GetMaxChamberedRounds(iClipIndex)) && (HasAmmoIndex(GetClipAmmoIndex(iClipIndex), AMMO_CHECK_DEFAULT_PARAMS)));
}

// Reload: This is the function that either checks if we can reload. If so, reload, otherwise, perform a reload fidget.
// Reload durations: 1.84f on empty, 1.48f en non-empty (SUBJECT TO CHANGE)
void CMP5::Reload(void)
{
	// Can't reload if already reloading. This may change in the future
	if (InReload())
		return;

	if (ShouldReload(0))
	{
		SetReloadStart();
	}
	else
	{
		// SetReloadCheck();
	}

	// If we were idling to begin with, unset the idle.
	UnsetIdle();
}

// ReloadStart: Start reload animation, set timers
// Reload durations: 1.84f on empty, 0.36f on non-empty (SUBJECT TO CHANGE)
void CMP5::ReloadStart(void)
{
	if (CanReload())
	{
		if (InAmmoSwitch() && HasClipAmmoIndex(0, AMMO_CHECK_DEFAULT_PARAMS))
		{
			SendWeaponAnim(MP5_RELOAD_EMPTY);
			//m_pPlayer->SetAnimation(PLAYER_RELOAD);
			SetReload(0.23f);
			SetWeaponIdle(3.0f);
			SetPrimaryAttack(2.5f);
			SetSecondaryAttack(2.5f);
			SetTertiaryAttack(2.5f);
		}
		else
		{
			SendWeaponAnim(HasClipAmmoIndex(0, AMMO_CHECK_DEFAULT_PARAMS) ? MP5_RELOAD : MP5_RELOAD_EMPTY_COCK);
			//m_pPlayer->SetAnimation(PLAYER_RELOAD);
			SetReload(HasClipAmmoIndex(0, AMMO_CHECK_DEFAULT_PARAMS) ? 0.16f : 0.36f);
			SetWeaponIdle(HasClipAmmoIndex(0, AMMO_CHECK_DEFAULT_PARAMS) ? 2.56f : 3.06f);
			SetPrimaryAttack(HasClipAmmoIndex(0, AMMO_CHECK_DEFAULT_PARAMS) ? 1.9f : 2.5f);
			SetSecondaryAttack(HasClipAmmoIndex(0, AMMO_CHECK_DEFAULT_PARAMS) ? 1.9f : 2.5f);
			SetTertiaryAttack(HasClipAmmoIndex(0, AMMO_CHECK_DEFAULT_PARAMS) ? 1.9f : 2.5f);
		}

		UnsetReloadStart();
		SetReloadStartToMid();
	}
}

// ReloadStartToMid: If the gun needs to be unpumped or uncocked before loading, do so here,
// otherwise skip instantly to ReloadMid
void CMP5::ReloadStartToMid(void)
{
	if (HasClipAmmoIndex(0,AMMO_CHECK_DEFAULT_PARAMS))
	{
		if (InAmmoSwitch())
		{
			SetReload(0.47);
			SetUnpumped();
			SetChamberedRounds(0,0);
		}

		UnsetReloadStartToMid();
		SetReloadMid();
	}
	else
	{
		if (CanReload())
		{
			SetReload(0.56f);
			SetUnpumped();
			UnsetReloadStartToMid();
			SetReloadMid();
		}
	}
}


// ReloadMid: Clipout the weapon, depending on cvars, clip is removed and added to ammo pool or not
// Durations are still determined by HasClipAmmo
void CMP5::ReloadMid(void)
{
	if (CanReload())
	{
		DefaultReloadClipOut(0);
		if (InAmmoSwitch())
		{
			SetCurrentAmmoType(0, GetTargetAmmoIndex(0));
			SetTargetAmmoIndex(0, -1);
		}
		SetReload(1.12f);
		UnsetReloadMid();
		SetReloadMidToEnd();
	}
}

void CMP5::ReloadMidToEnd(void)
{
	if (CanReload())
	{
		DefaultReloadClipIn(0);

		if (IsUnpumped())
		{
			if (InAmmoSwitch())
				SetReload(0.31f);
			else
				SetReload(0.36f);
		}

		UnsetReloadMidToEnd();
		SetReloadEnd();
	}
}

void CMP5::ReloadEnd(void)
{
	if (!IsUnpumped())
	{
		UnsetReloadEnd();
		SetReloadEndToStart();
	}
	else
	{
		if (CanReload())
		{
			UnsetUnpumped();
			UnsetReloadEnd();
			SetReloadEndToStart();
		}
	}

	if (InAmmoSwitch())
		UnsetAmmoSwitch();
}

// Usually used for interrupts
void CMP5::ReloadEndToStart(void)
{
	if (CanReload())
	{
		UnsetReload();
	}
}


void CMP5::WeaponIdle(void)
{
	if (HasSemiFired())
		UnsetSemiFired();

	ResetEmptySound();

	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase())
		return;

	// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
	if (RANDOM_LONG(0, 99) <= 5)
	{
		UpdateBodygroup();
		SendWeaponAnim(MP5_FIDGET);
		UnsetIdle();
		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.17;
	}
	else
	{
		// Ensure at least two successful loops
		if (!IsIdle())
		{
			UpdateBodygroup();
			SendWeaponAnim(MP5_IDLE);
			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.125 * 2;
			SetIdle();
		}
		else
		{
			// Only perform a single loop in this case
			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.125;
		}
	}
}

class CMP5AmmoClip : public CBasePlayerAmmo
{
public:
	CMP5AmmoClip(void)
	{
		m_szPickupSound = MAKE_STRING("items/ammo/mp5clip.wav");
		m_szAmmoType = MAKE_STRING("9mmH");
		m_szModel = MAKE_STRING("models/ammo_9mmH.mdl");
		m_iAmmoAmount = MP5_MAX_CLIP;
	}
	void Spawn(void)
	{
		CBasePlayerAmmo::Spawn();
		pev->classname = MAKE_STRING("ammo_9mmh"); // Added for compatiblity
	}
};
LINK_ENTITY_TO_CLASS(ammo_9mmh, CMP5AmmoClip);
LINK_ENTITY_TO_CLASS(ammo_mp5clip, CMP5AmmoClip); // Added for compatiblity
LINK_ENTITY_TO_CLASS(ammo_9mmAR, CMP5AmmoClip); // Added for compatiblity

class CMP5AmmoBox : public CMP5AmmoClip
{
public:
	CMP5AmmoBox(void)
	{
		m_szPickupSound = MAKE_STRING("items/ammo/mp5clipmulti.wav");
		m_szAmmoType = MAKE_STRING("9mmH");
		m_szModel = MAKE_STRING("models/ammo_9mmH.mdl");
		m_iAmmoAmount = MP5_MAX_CLIP * 5;
	}
	void Spawn(void)
	{
		CBasePlayerAmmo::Spawn();
		pev->body = 4;
		pev->classname = MAKE_STRING("ammo_9mmh"); // Added for compatiblity
	}
};
LINK_ENTITY_TO_CLASS(ammo_9mmbox, CMP5AmmoBox); // Added for compatiblity, chainbox entity doesn't exist anymore

class CMP5AmmoGrenade : public CBasePlayerAmmo
{
public:
	CMP5AmmoGrenade(void)
	{
		m_szPickupSound = MAKE_STRING("items/ammo/mp5grenademulti.wav");
		m_szAmmoType = MAKE_STRING("40mm");
		m_szModel = MAKE_STRING("models/ammo_40mm.mdl");
		m_iAmmoAmount = 2;
	}
	void Spawn(void)
	{
		CBasePlayerAmmo::Spawn();
		pev->classname = MAKE_STRING("ammo_40mm"); // Added for compatiblity
	}
};
LINK_ENTITY_TO_CLASS(ammo_40mm, CMP5AmmoGrenade);
LINK_ENTITY_TO_CLASS(ammo_mp5grenades, CMP5AmmoGrenade); // Added for compatiblity
LINK_ENTITY_TO_CLASS(ammo_ARgrenades, CMP5AmmoGrenade); // Added for compatiblity















