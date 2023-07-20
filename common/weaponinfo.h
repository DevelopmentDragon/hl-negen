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

#ifndef WEAPONINFO_H
#define WEAPONINFO_H

// Info about weapons player might have in his/her possession
typedef struct weapon_data_s
{
	int		m_iId;
	int		m_iClip;

	float	m_flNextPrimaryAttack;								// soonest time ItemPostFrame will call PrimaryAttack
	float	m_flNextSecondaryAttack;							// soonest time ItemPostFrame will call SecondaryAttack
	float	m_flNextTertiaryAttack;								// soonest time ItemPostFrame will call TertiaryAttack
	float	m_flNextQuaternaryAttack;							// soonest time ItemPostFrame will call QuaternaryAttack
	float	m_flNextQuinaryAttack;								// soonest time ItemPostFrame will call QuinaryAttack
	float	m_flNextReload;										// soonest time ItemPostFrame will call Reload
	float	m_flNextWeaponIdle;									// soonest time ItemPostFrame will call WeaponIdle
	float	m_flNextRecoil;										// soonest time ItemPostFrame will call Recoil
	float	m_flNextCharge;										// soonest time ItemPostFrame will call Charge
	float	m_flNextPump;										// soonest time ItemPostFrame will cal Pump
	float	m_flNextSwitch;										// soonest time ItemPostFrame will call Switch

	int			m_fWeaponStatusFlags;
	float		m_fAimedDamage;
	float		m_fNextAimBonus;
	int		m_fInZoom;
	int		m_iWeaponState;

	int		iuser1;
	int		iuser2;
	int		iuser3;
	int		iuser4;
	float		fuser1;
	float		fuser2;
	float		fuser3;
	float		fuser4;
} weapon_data_t;

#endif//WEAPONINFO_H