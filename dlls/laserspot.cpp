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
#include "gamerules.h"
#include "soundent.h"
#include "decals.h"

LINK_ENTITY_TO_CLASS(laser_spot, CLaserSpot);

//=========================================================
//=========================================================
void CLaserSpot::Precache(void)
{
	PRECACHE_MODEL("sprites/laserdot.spr");
};

int CLaserSpot::ObjectCaps(void)
{ 
	return FCAP_DONT_SAVE; 
}

void CLaserSpot::Spawn(void)
{
	Precache();
	pev->movetype = MOVETYPE_NONE;
	pev->solid = SOLID_NOT;

	pev->rendermode = kRenderGlow;
	pev->renderfx = kRenderFxNoDissipation;
	pev->renderamt = 255;

	SET_MODEL(ENT(pev), "sprites/laserdot.spr");
	UTIL_SetOrigin(pev, pev->origin);
};

//=========================================================
// Suspend- make the laser sight invisible. 
//=========================================================
void CLaserSpot::Suspend(float flSuspendTime)
{
	pev->effects |= EF_NODRAW;

	SetThink(&CLaserSpot::Revive);
	pev->nextthink = gpGlobals->time + flSuspendTime;
}

//=========================================================
// Revive - bring a suspended laser sight back.
//=========================================================
void CLaserSpot::Revive(void)
{
	pev->effects &= ~EF_NODRAW;

	SetThink(NULL);
}

//=============================================================================
// Perform all actions required to set a power up routine for the lasert spot
//=============================================================================
void CLaserSpot::SetPowerUp(void)
{
	pev->nextthink = gpGlobals->time;
	SetThink(&CLaserSpot::PowerUp);
}

void CLaserSpot::PowerUp(void)
{
	if (pev->renderamt < m_iVisibilityMax)
		m_iVisibilityMax++;

	pev->nextthink = gpGlobals->frametime;
}

void CLaserSpot::SetPowerDown(void)
{
	pev->nextthink = gpGlobals->time;
	SetThink(&CLaserSpot::PowerDown);
}

void CLaserSpot::PowerDown(void)
{
	pev->nextthink = gpGlobals->frametime;
}

//=========================================================
// Create a laser spot and return pointer
//=========================================================
CLaserSpot::CLaserSpot(void)
{

}

CLaserSpot::~CLaserSpot(void)
{
	// Remove the trail apropriately
	if (m_pTrail)
	{
		UTIL_Remove(m_pTrail);
		m_pTrail = NULL;
	}
}

void CLaserSpot::Killed(entvars_t* pevAttacker, int iGib)
{
	UTIL_Remove(this);
}

CLaserSpot* CLaserSpot::CreateSpot(edict_t* pOwner)
{
	CLaserSpot* pSpot = GetClassPtr((CLaserSpot*)NULL);
	pSpot->Spawn();

	pSpot->pev->classname = MAKE_STRING("laser_spot");
	pSpot->pev->owner = pOwner;

	return pSpot;
}

//=========================================================
// Create a laser spot and return pointer
//=========================================================

void CLaserSpot::SetPowerTime(float flTime)
{

}

void CLaserSpot::SetStartingVisibility(int iVisibility)
{

}

void CLaserSpot::SetMaxVisibility(int iVisibility)
{

}

void CLaserSpot::SetMinVisibility(int iVisibility)
{

}

void CLaserSpot::Update(Vector vecSpotOrigin, Vector vecTrailOrigin)
{

}