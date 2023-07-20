/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
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
#include "gamerules.h"

LINK_ENTITY_TO_CLASS(weapon_question, CQuestion);

void CQuestion::Spawn()
{
	pev->classname = MAKE_STRING("weapon_question"); // hack to allow for old names
	Precache();
	SET_MODEL(ENT(pev), "models/v_question.mdl");
	m_iId = WEAPON_QUESTION;

	m_iDefaultAmmo = SOCIAL_MAX_CARRY;
	FallInit();// get ready to fall down.
}

void CQuestion::Precache(void)
{
	PRECACHE_MODEL("models/v_question.mdl");
}

int CQuestion::GetItemInfo(ItemInfo* p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "social";
	p->iMaxAmmo1 = SOCIAL_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = WEAPON_BUCKET_MELEE;
	p->iPosition = WEAPON_QUESTION_SLOT;
	p->iFlags = ITEM_FLAG_SELECTONEMPTY | ITEM_FLAG_CANSELECT;
	p->iId = m_iId = WEAPON_QUESTION;
	p->iWeight = QUESTION_WEIGHT;
	return 1;
}

BOOL CQuestion::IsUseable(void)
{
	return TRUE;
}

int CQuestion::HUDIcon(void)
{
	return 3;
}

int CQuestion::HUDActiveIcon(void)
{
	return 4;
}

int CQuestion::ModeIcon(void)
{
	return -1;
}

int CQuestion::ModeIcon2(void)
{
	return -1;
}

int CQuestion::ModeIcon3(void)
{
	return -1;
}

int CQuestion::SmallIcon(void)
{
	return 1;
}

void CQuestion::ItemPostFrame(void)
{

	//ALERT(at_console, "Question classname is %s\n", STRING(pev->classname));
	return CBasePlayerWeapon::ItemPostFrame();
}

int CQuestion::AddToPlayer(CBasePlayer* pPlayer)
{
	if (CBasePlayerWeapon::AddToPlayer(pPlayer))
	{
		// Little Badis: No messages for this one
		/*
		MESSAGE_BEGIN(MSG_ONE, gmsgWeapPickup, NULL, pPlayer->pev);
		WRITE_BYTE(m_iId);
		MESSAGE_END();
		*/
		return TRUE;
	}
	return FALSE;
}

BOOL CQuestion::Deploy()
{
	return DefaultDeploy("models/v_question.mdl", "models/v_question.mdl", QUESTION_IDLE, "crowbar");
}

void CQuestion::Holster(int skiplocal) {
	SendWeaponAnim(QUESTION_IDLE);
}

void CQuestion::PrimaryAttack(void)
{
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);
	return;
}

void CQuestion::SecondaryAttack(void)
{
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);
	return;
}

void CQuestion::Reload(void)
{
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);
	return;
}

void CQuestion::WeaponIdle(void)
{
	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase())
		return;

}