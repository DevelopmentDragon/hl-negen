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

LINK_ENTITY_TO_CLASS(weapon_dmc_light, CLightningGun);

#ifndef CLIENT_DLL

TYPEDESCRIPTION	CLightningGun::m_SaveData[] =
{
	DEFINE_ARRAY(CLightningGun, m_iAmmoIndices, FIELD_INTEGER, 2),
	DEFINE_ARRAY(CLightningGun, m_iTargetAmmoIndex, FIELD_INTEGER, 2),
	DEFINE_ARRAY(CLightningGun, pTargetOne, FIELD_EHANDLE, 3),
	DEFINE_ARRAY(CLightningGun, pTargetTwo, FIELD_EHANDLE, 3),
	DEFINE_ARRAY(CLightningGun, pTargetThree, FIELD_EHANDLE, 3),
	DEFINE_ARRAY(CLightningGun, m_flBeamsEnd, FIELD_FLOAT, 9),
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
		m_flBeamsEnd[i] = 0.0f;
	}

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
//	-Primary and secondary: Focus three bolts at once in a straight line.
//	-Tertiary Fire: Hold for chaining mode. Primary becomes cut Chain Lightning Gun, Secondary becomes the same with each beam
// ALTERNATIVE MODE:
//	-Primary Fire: Charge up to fire a straight bolt that zaps the enemy. Fires automatically when fully charged. Damage poportional to distance
//	-Secondary Fire: Fire a projectile that zaps nearby enemies and that can be detonated by firing the primary on it aka Unreal 1 ASMD projectile.
//	-Tertiary Fire: Toggle chaining
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
	UpdateBeamPosition();

	if (m_pPlayer)
	{
		if (!(m_pPlayer->pev->button & (IN_ATTACK | IN_ATTACK2)))
		{
			m_flNextAnimReset = 0.0f;
			m_flNextSoundReset = 0.0f;
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
	for (int i = 0; i < 9; i++)
	{
		if (m_pBeams[i])
		{
			if (m_flBeamsEnd[i] <= 0)
				ClearBeams(i);
			else
				m_flBeamsEnd[i] = max(m_flBeamsEnd[i] - gpGlobals->frametime, 0.0f);
		}
	}
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
			m_flBeamsEnd[i] = 0.0f;
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
		EHANDLE* phTarget = (i % 3 == 0) ? pTargetOne : ((i % 3 == 1) ? pTargetTwo : pTargetThree);
		if (phTarget[i % 3])
		{
			phTarget[i % 3] = NULL;
		}
	}
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
BOOL CLightningGun::ValidTarget(EHANDLE hTarget)
{
	if (hTarget != NULL)
	{
		if (m_pPlayer)
		{
			if (hTarget->CanBeShocked())
			{
				if (m_pPlayer->FVisible(hTarget))
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

void CLightningGun::UpdateBeamPosition(void)
{
	if (m_pPlayer)
	{
		if (pTargetOne[0] != NULL || pTargetOne[1] != NULL || pTargetOne[2] != NULL)
		{
			for (int i = 0; i < 3; i++)
			{
				if (m_pBeams[i])
				{
					if (pTargetOne[i] != NULL)
					{
						m_pBeams[i]->PointEntInit(pTargetOne[i]->Center(), m_pPlayer->entindex());
						m_pBeams[i]->SetEndAttachment(1);
					}
				}
			}
		}
		else
		{
			if (m_pBeams[0])
			{
				TraceResult tr;
				Vector vecSrc = m_pPlayer->GetGunPosition() - gpGlobals->v_up * 2;
				Vector vecDir = gpGlobals->v_forward;
				float flDist = 8192;
				UTIL_TraceLine(vecSrc, vecSrc + vecDir * flDist, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
				m_pBeams[0]->PointEntInit(tr.vecEndPos, m_pPlayer->entindex());
				m_pBeams[0]->SetEndAttachment(1);
			}
		}
	}
}

// PrimaryAttack
// On continuous mode: Continuously shoots a single bolt of light forward in a straight line (cells)
// On charged mode: Charge up an attack that produces a single powerful bolt (plasma cells)
void CLightningGun::PrimaryAttack(void)
{
	// Die if you use this weapon in the water
	if (WaterDischarge()) return;

	// Vector computations and trace attack
	TraceResult tr;
	CBaseEntity* pEntity;
	Vector anglesAim = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
	UTIL_MakeVectors(anglesAim);

	anglesAim.x = -anglesAim.x;
	Vector vecSrc = m_pPlayer->GetGunPosition() - gpGlobals->v_up * 2;
	Vector vecDir = gpGlobals->v_forward;

	float flDist = 8192;
	UTIL_TraceLine(vecSrc, vecSrc + vecDir * flDist, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
	pEntity = CBaseEntity::Instance(tr.pHit);

	float flDamage = gSkillData.plrDmgShockTase;
	if (pEntity)
	{
		if (pEntity->pev->takedamage)
		{
			pEntity->TakeDamage(m_pPlayer->pev, pEntity->pev, 100, ID_DMG_MP5);
		}
	}

	// Draw the Beam
	if (!m_pBeams[0])
	{
		m_pBeams[0] = CBeam::BeamCreate("sprites/lgtning.spr", 50);
		m_pBeams[0]->PointEntInit(tr.vecEndPos, m_pPlayer->entindex());
		m_pBeams[0]->SetEndAttachment(1);
		m_pBeams[0]->SetColor(128, 128, 255);
		m_pBeams[0]->SetBrightness(255);
		m_pBeams[0]->SetNoise(20);
		m_flBeamsEnd[0] = 0.1;

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
		WRITE_BYTE(gpGlobals->time + 0.05); // life
		WRITE_BYTE(1); // decay rate
		MESSAGE_END();

		MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin, pev);
		WRITE_BYTE(TE_DLIGHT);
		WRITE_SHORT(0);	// entity to follow
		WRITE_COORD(tr.vecEndPos.x); // x
		WRITE_COORD(tr.vecEndPos.y); // y
		WRITE_COORD(tr.vecEndPos.z); // z
		WRITE_COORD(1); // radius
		WRITE_BYTE(128); // r
		WRITE_BYTE(128); // g
		WRITE_BYTE(255); // b
		WRITE_BYTE(gpGlobals->time + 0.05); // life
		WRITE_BYTE(1); // decay rate
		MESSAGE_END();
	}
	else
	{
		// Extend life of beam otherwise, let functions update position
		m_flBeamsEnd[0] = 0.1;
	}

#ifndef CLIENT_DLL
	if (UTIL_PointContents(tr.vecEndPos) != CONTENTS_WATER)
	{
		UTIL_Sparks(tr.vecEndPos);
		/*
		//if (m_iBoltsStored > GetMaxAmmo1() / 2)
			UTIL_DecalTrace(&tr, DECAL_OFSCORCH4 + RANDOM_LONG(0, 2));
		else
			UTIL_DecalTrace(&tr, DECAL_OFSMSCORCH1 + RANDOM_LONG(0, 2));\
		*/
	}
#endif

	UpdateBodygroup();

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

	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usLight1, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, vecDir.x, vecDir.y, 0, 0,
		bUpdateSound, bUpdateAnimation,
		(float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);

	/*
	if (m_pPlayer->m_flInfiniteAmmo > 0)
	{
		m_flNextRoachAnim = 0.23f;
		m_iRoachAnimState = RAS_STARTTOLOOP;
	}
	else
	{
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] -= m_iBoltsStored;
		m_iBoltsStored = 0;
		m_iRoachAnimState = RAS_NONE;
		m_flNextRoachAnim = -1.0f;
	}
	*/

	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextReload = UTIL_WeaponTimeBase() + 1.53;
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.53;// idle pretty soon after shooting.
	UnsetIdle();
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
	// Die if you use this weapon in the water
	if (WaterDischarge()) return;

	TraceResult tr;
	CBaseEntity* pEntity;
	Vector anglesAim = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
	UTIL_MakeVectors(anglesAim);

	anglesAim.x = -anglesAim.x;
	Vector vecSrc = m_pPlayer->GetGunPosition() - gpGlobals->v_up * 2;
	Vector vecDir = gpGlobals->v_forward;

	int numTargets = 0; // Use this to keep track of how many targets we've acquired

	pEntity = NULL;
	while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, 8192)) != NULL)
	{
		//ALERT(at_console, "Found: %s\n", STRING(pEntity->pev->classname));
		if (pEntity == this || pEntity == m_pPlayer)
		{
			continue;
		}
		
		const char* pStr = STRING(pEntity->pev->classname);
		if (m_pPlayer->FVisible(pEntity))
		{
			if (pEntity->CanBeShocked())
			{
				if (pEntity->IsAlive())
				{
					//ALERT(at_console, "Got: %s\n", STRING(pEntity->pev->classname));
#ifndef CLIENT_DLL
					pTargetOne[numTargets] = pEntity;
					numTargets++;
#endif
				}
			}
		}

	}

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
	WRITE_BYTE(gpGlobals->time + 0.05); // life
	WRITE_BYTE(1); // decay rate
	MESSAGE_END();

	if (numTargets > 0)
	{
		for (int i = 0; i < numTargets; i++)
		{
			if (pTargetOne[i])
			{
				// The goal here is simple
				float flDamage = gSkillData.plrDmgShockTase * 1.0 + 0.33 * (3 - numTargets);
				if (pTargetOne[i]->pev->takedamage)
				{
					pTargetOne[i]->TakeDamage(m_pPlayer->pev, pTargetOne[i]->pev, 5, ID_DMG_MP5);
				}
				// Draw the Beam
				if (!m_pBeams[i])
				{
					m_pBeams[i] = CBeam::BeamCreate("sprites/lgtning.spr", 50);
					m_pBeams[i]->PointEntInit(pTargetOne[i]->Center(), m_pPlayer->entindex());
					m_pBeams[i]->SetEndAttachment(1);
					m_pBeams[i]->SetColor(128, 128, 255);
					m_pBeams[i]->SetBrightness(255);
					m_pBeams[i]->SetNoise(20);
					m_flBeamsEnd[i] = 0.1;

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
				}
				else
				{
					m_flBeamsEnd[i] = 0.1;
				}
			}
		}
	}
	else
	{
		// Randomly shoot beams and waste cells
	}

	UpdateBodygroup();

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

	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usLight1, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, vecDir.x, vecDir.y, 0, 0,
		bUpdateSound, bUpdateAnimation,
		(float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);

	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextReload = UTIL_WeaponTimeBase() + 1.53;
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.53;// idle pretty soon after shooting.

	UnsetIdle();
}

// TertiaryAttack
// If held, enable chaining when applicable
void CLightningGun::TertiaryAttack(void)
{

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