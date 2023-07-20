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
/*

===== generic grenade.cpp ========================================================

*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "soundent.h"
#include "decals.h"


//===================grenade


LINK_ENTITY_TO_CLASS(grenade, CGrenade);

// Grenades flagged with this will be triggered when the owner calls detonateSatchelCharges
#define SF_DETONATE		0x0001

//
// Grenade Explode
//
void CGrenade::Explode(Vector vecSrc, Vector vecAim)
{
	TraceResult tr = UTIL_GetGlobalTrace();
	//UTIL_TraceLine ( pev->origin, pev->origin + Vector ( 0, 0, -32 ),  ignore_monsters, ENT(pev), & tr);

	Explode(&tr, 0);
}

// UNDONE: temporary scorching for PreAlpha - find a less sleazy permenant solution.
void CGrenade::Explode(TraceResult* pTrace, int bitsDamageType)
{
	float		flRndSound;// sound randomizer

	int dmgID = 0;

	pev->model = iStringNull;//invisible
	pev->solid = SOLID_NOT;// intangible

	pev->takedamage = DAMAGE_NO;

	Vector previousOrigin = pev->origin;

	// Pull out of the wall a bit
	if (pTrace->flFraction != 1.0)
	{
		pev->origin = pTrace->vecEndPos + (pTrace->vecPlaneNormal * PullUpScale());
	}

	int iContents = UTIL_PointContents(pev->origin);

	MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, pev->origin);
	WRITE_BYTE(TE_EXPLOSION);		// This makes a dynamic light and the explosion sprites/sound
	WRITE_COORD(pev->origin.x);	// Send to PAS because of the sound
	WRITE_COORD(pev->origin.y);
	WRITE_COORD(pev->origin.z);
	if (iContents != CONTENTS_WATER)
	{
		WRITE_SHORT(g_sModelIndexFireball);
	}
	else
	{
		WRITE_SHORT(g_sModelIndexWExplosion);
	}
	WRITE_BYTE(ExplosionScale()); // scale * 10
	WRITE_BYTE(15); // framerate
	WRITE_BYTE(TE_EXPLFLAG_NOSOUND);
	MESSAGE_END();

	CSoundEnt::InsertSound(bits_SOUND_COMBAT, pev->origin, NORMAL_EXPLOSION_VOLUME, 3.0);
	entvars_t* pevOwner;
	if (pev->owner)
		pevOwner = VARS(pev->owner);
	else
		pevOwner = NULL;

	pev->owner = NULL; // can't traceline attack owner if this is set

	switch (m_iGrenadeType)
	{
	case TYPE_MP5GRENADE:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/mp5/alt_exp.wav", VOL_NORM, 0.3f);
		RadiusDamage2(pev, pevOwner, gSkillData.plrDmg40mmHeat, CLASS_NONE, 100, ID_DMG_MP5_GRENADE_HEAT);
		RadiusDamage2(pev, pevOwner, gSkillData.plrDmg40mmBlast, CLASS_NONE, 200, ID_DMG_MP5_GRENADE_BLAST);
		RadiusDamage2(pev, pevOwner, gSkillData.plrDmg40mmShrapnel, CLASS_NONE, 250, ID_DMG_MP5_GRENADE_SHRAPNEL);
		UTIL_ScreenShake(pev->origin, 2.0, 2.0, 1.0, 200);
		break;
	case TYPE_TRIPMINE:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/tripmine/explode.wav", VOL_NORM, 0.3f);
		RadiusDamage2(pev, pevOwner, pev->dmg, CLASS_NONE, 300, ID_DMG_TRIPMINE_BLAST);
		RadiusDamage2(pev, pevOwner, pev->dmg / 4, CLASS_NONE, 300, ID_DMG_TRIPMINE_BLAST);
		UTIL_ScreenShake(pev->origin, 2.0, 2.0, 1.0, 300);
		break;
	case TYPE_RPGROCKET:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/rpg/explode.wav", VOL_NORM, 0.3f);
		RadiusDamage2(pev, pevOwner, pev->dmg, CLASS_NONE, 250, ID_DMG_RPG_BLAST);
		RadiusDamage2(pev, pevOwner, pev->dmg / 5, CLASS_NONE, 250, ID_DMG_RPG_IMPACT);
		UTIL_ScreenShake(pev->origin, 2.0, 2.0, 1.0, 250);
		break;
	case TYPE_HEGRENADE:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/handgrenade/he_exp.wav", VOL_NORM, 0.3f);
		RadiusDamage2(pev, pevOwner, gSkillData.plrDmgHighExplosiveBlast, CLASS_NONE, 250, ID_DMG_HE_BLAST);
		RadiusDamage2(pev, pevOwner, gSkillData.plrDmgHighExplosiveHeat, CLASS_NONE, 150, ID_DMG_HE_HEAT);
		RadiusDamage2(pev, pevOwner, gSkillData.plrDmgHighExplosiveShrapnel, CLASS_NONE, 350, ID_DMG_HE_SHRAPNEL);
		UTIL_ScreenShake(pev->origin, 2.0, 2.0, 1.0, 250);
		break;
	case TYPE_M4GRENADE:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/m4/alt_exp.wav", VOL_NORM, 0.3f);
		RadiusDamage2(pev, pevOwner, gSkillData.plrDmgSmokeGrenadeBlast, CLASS_NONE, 250, ID_DMG_HE_BLAST);
		RadiusDamage2(pev, pevOwner, gSkillData.plrDmgSmokeGrenadeHeat, CLASS_NONE, 150, ID_DMG_HE_HEAT);
		RadiusDamage2(pev, pevOwner, gSkillData.plrDmgSmokeGrenadeShrapnel, CLASS_NONE, 350, ID_DMG_HE_SHRAPNEL);
		UTIL_ScreenShake(pev->origin, 2.0, 2.0, 2.0, 400);
		break;
	case TYPE_RIFLEROCKET:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/rocketrifle/exp.wav", VOL_NORM, 0.3f);
		RadiusDamage2(pev, pevOwner, pev->dmg * 1.5, CLASS_NONE, 128, ID_DMG_HE_BLAST);
		RadiusDamage2(pev, pevOwner, pev->dmg * 0.25, CLASS_NONE, 128, ID_DMG_HE_HEAT);
		RadiusDamage2(pev, pevOwner, pev->dmg * 0.25, CLASS_NONE, 128, ID_DMG_HE_SHRAPNEL);
		UTIL_ScreenShake(pev->origin, 2.0, 2.0, 1.0, 128);
		break;
	case TYPE_SATCHEL:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/satchel/exp.wav", VOL_NORM * 2, 0.3f);
		RadiusDamage2(pev, pevOwner, pev->dmg / 4, CLASS_NONE, 256, ID_DMG_HE_SHRAPNEL);
		RadiusDamage2(pev, pevOwner, pev->dmg / 2, CLASS_NONE, 100, ID_DMG_HE_HEAT);
		RadiusDamage2(pev, pevOwner, pev->dmg, CLASS_NONE, 256, ID_DMG_HE_BLAST);
		UTIL_ScreenShake(pev->origin, 4.0, 2.0, 1.0, 256);
		break;
	case TYPE_LAUNCHERGRENADE:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/glauncher/explode.wav", VOL_NORM, 0.3f);
		RadiusDamage2(pev, pevOwner, pev->dmg / 4, CLASS_NONE, 256, ID_DMG_HE_SHRAPNEL);
		RadiusDamage2(pev, pevOwner, pev->dmg / 2, CLASS_NONE,  100, ID_DMG_HE_HEAT);
		RadiusDamage2(pev, pevOwner, pev->dmg, CLASS_NONE, 256, ID_DMG_HE_BLAST);
		UTIL_ScreenShake(pev->origin, 4.0, 2.0, 1.0, 256);
		break;
	default:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/handgrenade/frag_exp.wav", VOL_NORM, 0.3f);
		RadiusDamage(pev, pevOwner, pev->dmg, CLASS_NONE, ID_DMG_FRAG_BLAST);
		RadiusDamage(pev, pevOwner, pev->dmg, CLASS_NONE, ID_DMG_FRAG_SHRAPNEL);
		break;
	}

	// replace pTrace
	//TraceResult newTr = UTIL_GetGlobalTrace();

	UTIL_DecalTrace(pTrace, ScorchSprite());

	flRndSound = RANDOM_FLOAT(0, 1);

	switch (RANDOM_LONG(0, 2))
	{
	case 0:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/debris1.wav", 0.55, ATTN_NORM);	break;
	case 1:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/debris2.wav", 0.55, ATTN_NORM);	break;
	case 2:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/debris3.wav", 0.55, ATTN_NORM);	break;
	}

	pev->effects |= EF_NODRAW;

	if (m_iGrenadeType == TYPE_M4GRENADE)
	{
		pev->origin = previousOrigin;
		m_flSmokeLife = 5.0f; // Five seconds of smoke only?
		SetThink(&CGrenade::SmokeGrenade);
		pev->nextthink = gpGlobals->time + 0.1;
		pev->solid = SOLID_NOT;
		pev->movetype = MOVETYPE_NONE;
		pev->effects |= EF_NODRAW;
		EMIT_SOUND(ENT(pev), CHAN_WEAPON3, "weapons/m4/alt_smoke.wav", VOL_NORM, ATTN_NORM);
	}
	else
	{
		SetThink(&CGrenade::Smoke);
		pev->nextthink = gpGlobals->time + 0.3;
	}
	pev->velocity = g_vecZero;

	if (iContents != CONTENTS_WATER)
	{
		int sparkCount = RANDOM_LONG(0, 3);
		for (int i = 0; i < sparkCount; i++)
			Create("spark_shower", pev->origin, pTrace->vecPlaneNormal, NULL);
	}
}


void CGrenade::Smoke(void)
{
	if (UTIL_PointContents(pev->origin) == CONTENTS_WATER)
	{
		UTIL_Bubbles(pev->origin - Vector(64, 64, 64), pev->origin + Vector(64, 64, 64), 100);
	}
	else
	{
		MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
		WRITE_BYTE(TE_SMOKE);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z);
		WRITE_SHORT(g_sModelIndexSmoke);
		WRITE_BYTE(SmokeScale()); // scale * 10
		WRITE_BYTE(12); // framerate
		MESSAGE_END();
	}
	UTIL_Remove(this);
}

void CGrenade::SmokeGrenade(void)
{
	// Timer is controlled here
	m_flSmokeLife -= 0.1;

	if (m_flSmokeLife > (float)0)
	{
		// Make some smoke
		MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
		WRITE_BYTE(TE_SMOKE);
		WRITE_COORD(pev->origin.x + RANDOM_FLOAT(-100, 100));
		WRITE_COORD(pev->origin.y + RANDOM_FLOAT(-100, 100));
		WRITE_COORD(pev->origin.z + RANDOM_FLOAT(-100, 100));
		WRITE_SHORT(g_sModelIndexSmoke);
		WRITE_BYTE(100); // a nice big cloud
		WRITE_BYTE(12); // framerate
		MESSAGE_END();
	}
	else
	{
		// Out of time? Remove it
		UTIL_Remove(this);
		return;
	}

	pev->nextthink = gpGlobals->time + 0.1;
}

void CGrenade::Killed(entvars_t* pevAttacker, int iGib)
{
	Detonate();
}


// Timed grenade, this think is called when time runs out.
void CGrenade::DetonateUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	SetThink(&CGrenade::Detonate);
	pev->nextthink = gpGlobals->time;
}

void CGrenade::PreDetonate(void)
{
	CSoundEnt::InsertSound(bits_SOUND_DANGER, pev->origin, 400, 0.3);

	SetThink(&CGrenade::Detonate);
	pev->nextthink = gpGlobals->time + 1;
}


void CGrenade::Detonate(void)
{
	TraceResult tr;
	Vector		vecSpot;// trace starts here!

	vecSpot = pev->origin + Vector(0, 0, 8);
	UTIL_TraceLine(vecSpot, vecSpot + Vector(0, 0, -40), ignore_monsters, ENT(pev), &tr);

	Explode(&tr, 0);

}


//
// Contact grenade, explode when it touches something
// 
void CGrenade::ExplodeTouch(CBaseEntity* pOther)
{
	TraceResult tr;
	Vector		vecSpot;// trace starts here!

	pev->enemy = pOther->edict();

	vecSpot = pev->origin - pev->velocity.Normalize() * 32;
	UTIL_TraceLine(vecSpot, vecSpot + pev->velocity.Normalize() * 64, ignore_monsters, ENT(pev), &tr);

	Explode(&tr, 0);
}

//=========================================================
void CGrenade::QuakeTouch(CBaseEntity* pOther)
{
	// don't hit the guy that launched this grenade
	// if ( pOther->edict() == pev->owner )
	//	return;

	if (pOther->pev->takedamage == DAMAGE_AIM && !(m_iGrenadeType == TYPE_LAUNCHERGRENADE && m_bRemote))
	{
		// Do touch damage
		float flDmg = RANDOM_FLOAT(100, 120);
		CBaseEntity* pOwner = CBaseEntity::Instance(pev->owner);
		if (pOther->pev->health)
			pOther->TakeDamage(pev, pOwner->pev, flDmg, ID_DMG_QUAKE_BLAST);


		TraceResult tr;
		Vector		vecSpot;// trace starts here!

		pev->enemy = pOther->edict();

		vecSpot = pev->origin - pev->velocity.Normalize() * 32;
		UTIL_TraceLine(vecSpot, vecSpot + pev->velocity.Normalize() * 64, ignore_monsters, ENT(pev), &tr);

		Explode(&tr, 0);
		return;
	}

	// Special call for this
	BounceTouch(pOther);
}

void CGrenade::PseudoQuakeTouch(CBaseEntity* pOther)
{
	// Special call for this
	BounceTouch(pOther);
}

void CGrenade::DangerSoundThink(void)
{
	if (!IsInWorld())
	{
		UTIL_Remove(this);
		return;
	}

	CSoundEnt::InsertSound(bits_SOUND_DANGER, pev->origin + pev->velocity * 0.5, pev->velocity.Length(), 0.2);
	pev->nextthink = gpGlobals->time + 0.2;

	if (pev->waterlevel != 0)
	{
		pev->velocity = pev->velocity * 0.5;
	}
}


void CGrenade::BounceTouch(CBaseEntity* pOther)
{
	// don't hit the guy that launched this grenade
	if (pOther->edict() == pev->owner)
		return;

	if (m_iGrenadeType != TYPE_LAUNCHERGRENADE)
	{
		// only do damage if we're moving fairly fast
		if (m_flNextAttack < gpGlobals->time && pev->velocity.Length() > 100)
		{
			entvars_t* pevOwner = VARS(pev->owner);
			if (pevOwner)
			{
				TraceResult tr = UTIL_GetGlobalTrace();
				//ClearMultiDamage( );
				pOther->TraceAttack(pevOwner, 1, gpGlobals->v_forward, &tr, ID_DMG_HE_IMPACT);
				//ApplyMultiDamage( pev, pevOwner, ID_DMG_GENERIC);
			}
			m_flNextAttack = gpGlobals->time + 1.0; // debounce
		}
	}

	Vector vecTestVelocity;
	// pev->avelocity = Vector (300, 300, 300);

	// this is my heuristic for modulating the grenade velocity because grenades dropped purely vertical
	// or thrown very far tend to slow down too quickly for me to always catch just by testing velocity. 
	// trimming the Z velocity a bit seems to help quite a bit.
	vecTestVelocity = pev->velocity;
	vecTestVelocity.z *= 0.45;

	if (!m_fRegisteredSound && vecTestVelocity.Length() <= 60)
	{
		//ALERT( at_console, "Grenade Registered!: %f\n", vecTestVelocity.Length() );

		// grenade is moving really slow. It's probably very close to where it will ultimately stop moving. 
		// go ahead and emit the danger sound.

		// register a radius louder than the explosion, so we make sure everyone gets out of the way
		CSoundEnt::InsertSound(bits_SOUND_DANGER, pev->origin, pev->dmg / 0.4, 0.3);
		m_fRegisteredSound = TRUE;
	}

	if (pev->flags & FL_ONGROUND)
	{
		// add a bit of static friction
		pev->velocity = pev->velocity * 0.8;

		pev->sequence = RANDOM_LONG(1, 1);
	}
	else
	{
		// play bounce sound
		BounceSound();
	}
	pev->framerate = pev->velocity.Length() / 200.0;
	if (pev->framerate > 1.0)
		pev->framerate = 1;
	else if (pev->framerate < 0.5)
		pev->framerate = 0;

}



void CGrenade::SlideTouch(CBaseEntity* pOther)
{
	// don't hit the guy that launched this grenade
	if (pOther->edict() == pev->owner)
		return;

	// pev->avelocity = Vector (300, 300, 300);

	if (pev->flags & FL_ONGROUND)
	{
		// add a bit of static friction
		pev->velocity = pev->velocity * 0.95;

		if (pev->velocity.x != 0 || pev->velocity.y != 0)
		{
			// maintain sliding sound
		}
	}
	else
	{
		BounceSound();
	}
}

void CGrenade::BounceSound(void)
{
	switch (m_iGrenadeType)
	{
	case TYPE_MP5GRENADE:
	{
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/mp5/alt_bounce.wav", VOL_NORM, ATTN_NORM);
		break;
	}
	case TYPE_M4GRENADE:
	{
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/m4/alt_bounce.wav", VOL_NORM, ATTN_NORM);
		break;
	}
	case TYPE_LAUNCHERGRENADE:
	{
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/glauncher/bounce.wav", VOL_NORM, ATTN_NORM);
		break;
	}
	default:
	{
		switch (RANDOM_LONG(0, 2))
		{
		case 1:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/handgrenade/hit2.wav", VOL_NORM, ATTN_NORM);	break;
		case 2:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/handgrenade/hit3.wav", VOL_NORM, ATTN_NORM);	break;
		default: EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/handgrenade/hit1.wav", VOL_NORM, ATTN_NORM);	break;
		}
		break;
	}
	}
}

void CGrenade::TumbleThink(void)
{
	if (!IsInWorld())
	{
		UTIL_Remove(this);
		return;
	}

	StudioFrameAdvance();

	pev->nextthink = gpGlobals->time + 0.1;

	if (!(m_iGrenadeType == TYPE_LAUNCHERGRENADE && m_bRemote))
	{
		if (pev->dmgtime - 1 < gpGlobals->time)
		{
			CSoundEnt::InsertSound(bits_SOUND_DANGER, pev->origin + pev->velocity * (pev->dmgtime - gpGlobals->time), 400, 0.1);
		}

		if (pev->dmgtime <= gpGlobals->time)
		{
			SetThink(&CGrenade::Detonate);
		}
	}

	if (pev->waterlevel != 0)
	{
		pev->velocity = pev->velocity * 0.5;
		pev->framerate = 0.2;
	}
}


void CGrenade::Spawn(void)
{
	pev->movetype = MOVETYPE_BOUNCE;
	pev->classname = MAKE_STRING("grenade");

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/proj_40mm.mdl");
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
	UTIL_SetOrigin(pev, pev->origin);

	pev->dmg = 100;
	m_fRegisteredSound = FALSE;

	m_bRemote = FALSE;
}


CGrenade* CGrenade::ShootContact(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity)
{
	CGrenade* pGrenade = GetClassPtr((CGrenade*)NULL);
	pGrenade->Spawn();
	// contact grenades arc lower
	pGrenade->pev->gravity = 0.5;// lower gravity since grenade is aerodynamic and engine doesn't know it.
	UTIL_SetOrigin(pGrenade->pev, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = UTIL_VecToAngles(pGrenade->pev->velocity);
	pGrenade->pev->owner = ENT(pevOwner);

	// make monsters afaid of it while in the air
	pGrenade->SetThink(&CGrenade::DangerSoundThink);
	pGrenade->pev->nextthink = gpGlobals->time;

	// Tumble in air
	pGrenade->pev->avelocity.x = RANDOM_FLOAT(-100, -500);

	// Explode on contact
	pGrenade->SetTouch(&CGrenade::ExplodeTouch);

	pGrenade->pev->dmg = gSkillData.plrDmg40mmBlast;

	pGrenade->m_iGrenadeType = TYPE_MP5GRENADE;

	return pGrenade;
}

CGrenade* CGrenade::ShootSoftContact(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time)
{
	CGrenade* pGrenade = GetClassPtr((CGrenade*)NULL);
	pGrenade->Spawn();
	// contact grenades arc lower
	pGrenade->pev->gravity = 0.5;// lower gravity since grenade is aerodynamic and engine doesn't know it.
	pGrenade->pev->friction = 0.8;
	UTIL_SetOrigin(pGrenade->pev, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = UTIL_VecToAngles(pGrenade->pev->velocity);
	pGrenade->pev->owner = ENT(pevOwner);

	// make monsters afaid of it while in the air
	pGrenade->SetThink(&CGrenade::DangerSoundThink);
	pGrenade->pev->nextthink = gpGlobals->time + time;

	// Tumble in air
	pGrenade->pev->avelocity.x = RANDOM_FLOAT(-100, -500);

	// Explode on contact
	pGrenade->SetTouch(&CGrenade::QuakeTouch);

	pGrenade->pev->dmg = gSkillData.plrDmg40mmBlast;

	pGrenade->m_iGrenadeType = TYPE_MP5GRENADE;
	pGrenade->SetThink(&CGrenade::TumbleThink);

	return pGrenade;
}

CGrenade* CGrenade::ShootSmoke(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity)
{
	CGrenade* pGrenade = GetClassPtr((CGrenade*)NULL);
	pGrenade->Spawn();
	// contact grenades arc lower
	pGrenade->pev->gravity = 0.5;// lower gravity since grenade is aerodynamic and engine doesn't know it.
	UTIL_SetOrigin(pGrenade->pev, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = UTIL_VecToAngles(pGrenade->pev->velocity);
	pGrenade->pev->owner = ENT(pevOwner);

	// make monsters afaid of it while in the air
	pGrenade->SetThink(&CGrenade::DangerSoundThink);
	pGrenade->pev->nextthink = gpGlobals->time;

	// Tumble in air
	pGrenade->pev->avelocity.x = RANDOM_FLOAT(-100, -500);

	// Explode on contact
	pGrenade->SetTouch(&CGrenade::ExplodeTouch);

	SET_MODEL(ENT(pGrenade->pev), "models/proj_smokegrenade.mdl");
	UTIL_SetOrigin(pGrenade->pev, pGrenade->pev->origin);
	UTIL_SetSize(pGrenade->pev, Vector(0, 0, 0), Vector(0, 0, 0));
	pGrenade->pev->dmg = gSkillData.plrDmgSmokeGrenadeBlast;

	pGrenade->m_iGrenadeType = TYPE_M4GRENADE;

	return pGrenade;
}

CGrenade* CGrenade::ShootSoftSmoke(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time)
{
	CGrenade* pGrenade = GetClassPtr((CGrenade*)NULL);
	pGrenade->Spawn();
	// contact grenades arc lower
	pGrenade->pev->gravity = 0.5;// lower gravity since grenade is aerodynamic and engine doesn't know it.
	pGrenade->pev->friction = 0.8;
	UTIL_SetOrigin(pGrenade->pev, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = UTIL_VecToAngles(pGrenade->pev->velocity);
	pGrenade->pev->owner = ENT(pevOwner);

	// make monsters afaid of it while in the air
	pGrenade->SetThink(&CGrenade::DangerSoundThink);
	pGrenade->pev->nextthink = gpGlobals->time + time;

	// Tumble in air
	pGrenade->pev->avelocity.x = RANDOM_FLOAT(-100, -500);

	// Explode on contact
	pGrenade->SetTouch(&CGrenade::QuakeTouch);

	SET_MODEL(ENT(pGrenade->pev), "models/proj_smokegrenade.mdl");
	UTIL_SetOrigin(pGrenade->pev, pGrenade->pev->origin);
	UTIL_SetSize(pGrenade->pev, Vector(0, 0, 0), Vector(0, 0, 0));
	pGrenade->pev->dmg = gSkillData.plrDmgSmokeGrenadeBlast;

	pGrenade->m_iGrenadeType = TYPE_M4GRENADE;
	pGrenade->SetThink(&CGrenade::TumbleThink);

	return pGrenade;
}

CGrenade* CGrenade::ShootTimed(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time)
{
	CGrenade* pGrenade = GetClassPtr((CGrenade*)NULL);
	pGrenade->Spawn();
	UTIL_SetOrigin(pGrenade->pev, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = UTIL_VecToAngles(pGrenade->pev->velocity);
	pGrenade->pev->owner = ENT(pevOwner);

	pGrenade->SetTouch(&CGrenade::BounceTouch);	// Bounce if touched

	// Take one second off of the desired detonation time and set the think to PreDetonate. PreDetonate
	// will insert a DANGER sound into the world sound list and delay detonation for one second so that 
	// the grenade explodes after the exact amount of time specified in the call to ShootTimed(). 

	pGrenade->pev->dmgtime = gpGlobals->time + time;
	pGrenade->SetThink(&CGrenade::TumbleThink);
	pGrenade->pev->nextthink = gpGlobals->time + 0.1;
	if (time < 0.1)
	{
		pGrenade->pev->nextthink = gpGlobals->time;
		pGrenade->pev->velocity = Vector(0, 0, 0);
	}

	pGrenade->pev->sequence = RANDOM_LONG(3, 6);
	pGrenade->pev->framerate = 1.0;

	// Tumble through the air
	// pGrenade->pev->avelocity.x = -400;

	pGrenade->pev->gravity = 0.5;
	pGrenade->pev->friction = 0.8;

	SET_MODEL(ENT(pGrenade->pev), "models/w_handgrenade.mdl");
	pGrenade->pev->dmg = 100;

	pGrenade->m_iGrenadeType = TYPE_HANDGRENADE;

	return pGrenade;
}

CGrenade* CGrenade::ShootHE(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time)
{
	CGrenade* pGrenade = GetClassPtr((CGrenade*)NULL);
	pGrenade->Spawn();
	UTIL_SetOrigin(pGrenade->pev, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = UTIL_VecToAngles(pGrenade->pev->velocity);
	pGrenade->pev->owner = ENT(pevOwner);

	pGrenade->SetTouch(&CGrenade::BounceTouch);	// Bounce if touched

	// Take one second off of the desired detonation time and set the think to PreDetonate. PreDetonate
	// will insert a DANGER sound into the world sound list and delay detonation for one second so that 
	// the grenade explodes after the exact amount of time specified in the call to ShootTimed(). 

	pGrenade->pev->dmgtime = gpGlobals->time + time;
	pGrenade->SetThink(&CGrenade::TumbleThink);
	pGrenade->pev->nextthink = gpGlobals->time + 0.1;
	if (time < 0.1)
	{
		pGrenade->pev->nextthink = gpGlobals->time;
		pGrenade->pev->velocity = Vector(0, 0, 0);
	}

	pGrenade->pev->sequence = RANDOM_LONG(3, 6);
	pGrenade->pev->framerate = 1.0;

	// Tumble through the air
	// pGrenade->pev->avelocity.x = -400;

	pGrenade->pev->gravity = 0.5;
	pGrenade->pev->friction = 0.8;

	SET_MODEL(ENT(pGrenade->pev), "models/w_hegrenade.mdl");
	pGrenade->pev->dmg = 250;

	pGrenade->m_iGrenadeType = TYPE_HEGRENADE;

	return pGrenade;
}


CGrenade* CGrenade::ShootSatchelCharge(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity)
{
	CGrenade* pGrenade = GetClassPtr((CGrenade*)NULL);
	pGrenade->pev->movetype = MOVETYPE_BOUNCE;
	pGrenade->pev->classname = MAKE_STRING("grenade");

	pGrenade->pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pGrenade->pev), "models/w_handgrenade.mdl");	// Change this to satchel charge model

	UTIL_SetSize(pGrenade->pev, Vector(0, 0, 0), Vector(0, 0, 0));

	pGrenade->pev->dmg = 200;
	UTIL_SetOrigin(pGrenade->pev, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = g_vecZero;
	pGrenade->pev->owner = ENT(pevOwner);

	// Detonate in "time" seconds
	pGrenade->SetThink(&CBaseEntity::SUB_DoNothing);
	pGrenade->SetUse(&CGrenade::DetonateUse);
	pGrenade->SetTouch(&CGrenade::SlideTouch);
	pGrenade->pev->spawnflags = SF_DETONATE;

	pGrenade->pev->friction = 0.9;

	pGrenade->m_iGrenadeType = TYPE_SATCHEL;

	return pGrenade;
}

CGrenade* CGrenade::ShootLauncherGrenade(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time, BOOL remote)
{
	CGrenade* pGrenade = GetClassPtr((CGrenade*)NULL);
	pGrenade->Spawn();

	SET_MODEL(ENT(pGrenade->pev), "models/proj_50mm.mdl");


	//UTIL_SetSize(pGrenade->pev, Vector(-4.0f, -4.0f, -4.0f), Vector(4.0f, 4.0f, 4.0f));
	pGrenade->pev->absmin = pGrenade->pev->origin + Vector(-4.0f, -4.0f, -4.0f);
	pGrenade->pev->absmax = pGrenade->pev->origin + Vector(4.0f, 4.0f, 4.0f);

	// contact grenades arc lower
	pGrenade->pev->gravity = 0.5;// lower gravity since grenade is aerodynamic and engine doesn't know it.
	pGrenade->pev->friction = 0.8;
	UTIL_SetOrigin(pGrenade->pev, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = UTIL_VecToAngles(pGrenade->pev->velocity);
	pGrenade->pev->owner = ENT(pevOwner);

	// make monsters afaid of it while in the air
	pGrenade->SetThink(&CGrenade::DangerSoundThink);
	pGrenade->pev->nextthink = gpGlobals->time + time;

	// Tumble in air
	pGrenade->pev->avelocity.x = RANDOM_FLOAT(-100, -500);

	// Explode on contact
	if (!remote)
		pGrenade->SetTouch(&CGrenade::QuakeTouch);
	else
		pGrenade->SetTouch(&CGrenade::PseudoQuakeTouch);

	pGrenade->pev->dmg = gSkillData.plrDmg40mmBlast;

	pGrenade->m_iGrenadeType = TYPE_LAUNCHERGRENADE;
	pGrenade->SetThink(&CGrenade::TumbleThink);
	pGrenade->m_bRemote = remote;
	pGrenade->SetUse(&CGrenade::DetonateUse);

	return pGrenade;
}


void CGrenade::UseSatchelCharges(entvars_t* pevOwner, SATCHELCODE code)
{
	edict_t* pentFind;
	edict_t* pentOwner;

	if (!pevOwner)
		return;

	CBaseEntity* pOwner = CBaseEntity::Instance(pevOwner);

	pentOwner = pOwner->edict();

	pentFind = FIND_ENTITY_BY_CLASSNAME(NULL, "grenade");
	while (!FNullEnt(pentFind))
	{
		CBaseEntity* pEnt = Instance(pentFind);
		if (pEnt)
		{
			if (FBitSet(pEnt->pev->spawnflags, SF_DETONATE) && pEnt->pev->owner == pentOwner)
			{
				if (code == SATCHEL_DETONATE)
					pEnt->Use(pOwner, pOwner, USE_ON, 0);
				else	// SATCHEL_RELEASE
					pEnt->pev->owner = NULL;
			}
		}
		pentFind = FIND_ENTITY_BY_CLASSNAME(pentFind, "grenade");
	}
}

float CGrenade::SmokeScale(void)
{
	if (m_iGrenadeType == TYPE_RIFLEROCKET)
		return 10;

	return (min(100, pev->dmg) - 50) * 0.80;
}

float CGrenade::ExplosionScale(void)
{
	if (m_iGrenadeType == TYPE_RIFLEROCKET)
		return 10;

	return ((100 - 50) * .60);
}

float CGrenade::PullUpScale(void)
{
	if (m_iGrenadeType == TYPE_RIFLEROCKET)
		return 10;

	return (100 - 24) * 0.6;
}

int CGrenade::ExplosionSpriteIndex(void)
{
	return 0;
}

int CGrenade::ScorchSprite(void)
{
	if (m_iGrenadeType == TYPE_RIFLEROCKET)
		return RANDOM_LONG(DECAL_OFSCORCH1, DECAL_OFSCORCH3);

	return RANDOM_LONG(DECAL_SCORCH1, DECAL_SCORCH2);
}

TYPEDESCRIPTION	CGrenade::m_SaveData[] =
{
	DEFINE_FIELD(CGrenade, m_iGrenadeType, FIELD_INTEGER),
	DEFINE_FIELD(CGrenade, m_fRegisteredSound, FIELD_BOOLEAN),
	DEFINE_FIELD(CGrenade, m_bRemote, FIELD_BOOLEAN),
	DEFINE_FIELD(CGrenade, m_flSmokeLife, FIELD_FLOAT),
};
IMPLEMENT_SAVERESTORE(CGrenade, CBaseMonster);

void CGrenade::Precache(void)
{
	PRECACHE_MODEL("models/proj_40mm.mdl");

	// MP5 40mm Grenade
	PRECACHE_MODEL("models/proj_40mm.mdl");
	PRECACHE_SOUND("weapons/mp5/alt_bounce.wav");
	PRECACHE_SOUND("weapons/mp5/alt_bouncepent.wav");
	PRECACHE_SOUND("weapons/mp5/alt_exp.wav");
	PRECACHE_SOUND("weapons/mp5/alt_exppent.wav");

	// M4 Smoke Grenade
	PRECACHE_MODEL("models/proj_smokegrenade.mdl");
	PRECACHE_SOUND("weapons/m4/alt_bounce.wav");
	PRECACHE_SOUND("weapons/m4/alt_bouncepent.wav");
	PRECACHE_SOUND("weapons/m4/alt_exp.wav");
	PRECACHE_SOUND("weapons/m4/alt_exppent.wav");
	PRECACHE_SOUND("weapons/m4/alt_smoke.wav");
	PRECACHE_SOUND("weapons/m4/alt_smokepent.wav");

	// Rocket Rifle
	PRECACHE_SOUND("weapons/rocketrifle/exp.wav");
	PRECACHE_SOUND("weapons/rocketrifle/exppent.wav");
	PRECACHE_MODEL("models/proj_riflerocket.mdl");

	m_iTrail = PRECACHE_MODEL("sprites/smoke.spr");
}

//======================end grenade

