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
//#ifndef CLIENT_DLL
//
//LINK_ENTITY_TO_CLASS(monster_satchel, CSatchelCharge);
//
////=========================================================
//// Deactivate - do whatever it is we do to an orphaned 
//// satchel when we don't want it in the world anymore.
////=========================================================
//void CSatchelCharge::Deactivate(void)
//{
//	pev->solid = SOLID_NOT;
//	UTIL_Remove(this);
//}
//
//void CSatchelCharge::Spawn(void)
//{
//	if (m_iSatchelType == SATCHEL_SET)
//	{
//		Precache();
//		// motor
//		pev->movetype = MOVETYPE_FLY;
//		pev->solid = SOLID_BBOX;
//		EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/satchel/arm_plant.wav", 1, ATTN_NORM);
//
//		SET_MODEL(ENT(pev), "models/w_satchel.mdl");
//
//		UTIL_SetSize(pev, Vector(-4, -4, -4), Vector(4, 4, 4));	// Uses point-sized, and can be stepped over
//		UTIL_SetOrigin(pev, pev->origin);
//
//		SetThink(&CSatchelCharge::PlantedSatchelThink);
//		SetUse(&CSatchelCharge::SatchelUse);
//		pev->nextthink = gpGlobals->time + 0.1;
//
//		pev->dmg = gSkillData.plrDmgTripmineBlast;
//		pev->sequence = 0;
//	}
//	else
//	{
//		Precache();
//		// motor
//		pev->movetype = MOVETYPE_BOUNCE;
//		pev->solid = SOLID_BBOX;
//
//		SET_MODEL(ENT(pev), "models/w_satchel.mdl");
//		EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/satchel/arm_throw.wav", 1, ATTN_NORM);
//		//UTIL_SetSize(pev, Vector( -16, -16, -4), Vector(16, 16, 32));	// Old box -- size of headcrab monsters/players get blocked by this
//		UTIL_SetSize(pev, Vector(-4, -4, -4), Vector(4, 4, 4));	// Uses point-sized, and can be stepped over
//		UTIL_SetOrigin(pev, pev->origin);
//
//		if (m_iSatchelType == SATCHEL_STICKY)
//		{
//			SetTouch(&CSatchelCharge::SatchelStick);
//			SetUse(&CSatchelCharge::SatchelUse);
//			SetThink(&CSatchelCharge::SatchelThink);
//			pev->nextthink = gpGlobals->time + 0.1;
//
//			pev->gravity = 0.5;
//			pev->friction = 0.8;
//
//			pev->dmg = gSkillData.plrDmgSatchelBlast;
//			// ResetSequenceInfo( );
//			pev->sequence = 0;
//		}
//		else
//		{
//			SetTouch(&CSatchelCharge::SatchelSlide);
//			SetUse(&CSatchelCharge::SatchelUse);
//			SetThink(&CSatchelCharge::SatchelThink);
//			pev->nextthink = gpGlobals->time + 0.1;
//
//			pev->gravity = 0.5;
//			pev->friction = 0.8;
//
//			pev->dmg = gSkillData.plrDmgSatchelBlast;
//			// ResetSequenceInfo( );
//			pev->sequence = 1;
//		}
//	}
//}
//
//
//void CSatchelCharge::SatchelSlide(CBaseEntity* pOther)
//{
//	entvars_t* pevOther = pOther->pev;
//
//	// don't hit the guy that launched this grenade
//	if (pOther->edict() == pev->owner)
//		return;
//
//	// pev->avelocity = Vector (300, 300, 300);
//	pev->gravity = 1;// normal gravity now
//
//	// HACKHACK - On ground isn't always set, so look for ground underneath
//	TraceResult tr;
//	UTIL_TraceLine(pev->origin, pev->origin - Vector(0, 0, 10), ignore_monsters, edict(), &tr);
//
//	if (tr.flFraction < 1.0)
//	{
//		// add a bit of static friction
//		pev->velocity = pev->velocity * 0.95;
//		pev->avelocity = pev->avelocity * 0.9;
//		// play sliding sound, volume based on velocity
//	}
//	if (!(pev->flags & FL_ONGROUND) && pev->velocity.Length2D() > 10)
//	{
//		BounceSound();
//	}
//	StudioFrameAdvance();
//}
//
//void CSatchelCharge::SatchelStick(CBaseEntity* pOther)
//{
//	entvars_t* pevOther = pOther->pev;
//
//	// don't hit the guy that launched this grenade
//	if (pOther->edict() == pev->owner)
//		return;
//
//	// pev->avelocity = Vector (300, 300, 300);
//	pev->gravity = 1;// normal gravity now
//
//					 // HACKHACK - On ground isn't always set, so look for ground underneath
//	TraceResult tr;
//	UTIL_TraceLine(pev->origin, pev->origin - Vector(0, 0, 10), ignore_monsters, edict(), &tr);
//
//	if (!pOther->IsBSPModel())
//	{
//		if (tr.flFraction < 1.0)
//		{
//			// add a bit of static friction
//			pev->velocity = pev->velocity * 0.95;
//			pev->avelocity = pev->avelocity * 0.9;
//			// play sliding sound, volume based on velocity
//		}
//		if (!(pev->flags & FL_ONGROUND) && pev->velocity.Length2D() > 10)
//		{
//			BounceSound();
//		}
//	}
//	else
//	{
//		if ((pOther->pev->flags & FL_CONVEYOR))
//		{
//			BounceSound();
//			SetTouch(&CSatchelCharge::SatchelSlide);
//			SetUse(&CSatchelCharge::SatchelUse);
//			SetThink(&CSatchelCharge::SatchelThink);
//			pev->nextthink = gpGlobals->time + 0.1;
//			pev->gravity = 0.5;
//			pev->friction = 0.8;
//		}
//		else
//		{
//			pev->aiment = pOther->edict();
//			pev->movetype = MOVETYPE_COMPOUND;
//			//ALERT(at_console, "aiment %s\n", STRING(pOther->pev->classname));
//			pev->solid = SOLID_BBOX;
//			EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/satchel/plant.wav", 1, ATTN_NORM);
//			pev->velocity = g_vecZero;
//			SetTouch(NULL);
//			SetThink(&CSatchelCharge::PlantedSatchelThink);
//			SetUse(&CSatchelCharge::SatchelUse);
//		}
//	}
//
//	StudioFrameAdvance();
//}
//
//
//
//void CSatchelCharge::SatchelThink(void)
//{
//	StudioFrameAdvance();
//	pev->nextthink = gpGlobals->time + 0.1;
//
//	if (!IsInWorld())
//	{
//		UTIL_Remove(this);
//		return;
//	}
//
//	if (pev->waterlevel == 3)
//	{
//		pev->movetype = MOVETYPE_FLY;
//		pev->velocity = pev->velocity * 0.8;
//		pev->avelocity = pev->avelocity * 0.9;
//		pev->velocity.z += 8;
//	}
//	else if (pev->waterlevel == 0)
//	{
//		pev->movetype = MOVETYPE_BOUNCE;
//	}
//	else
//	{
//		pev->velocity.z -= 8;
//	}
//}
//
//void CSatchelCharge::PlantedSatchelThink(void)
//{
//	StudioFrameAdvance();
//	pev->nextthink = gpGlobals->time + 0.1;
//
//	if (pev->aiment)
//	{
//		if (!CBaseEntity::Instance(pev->aiment))
//		{
//			pev->movetype = MOVETYPE_BOUNCE;
//			pev->aiment = NULL;
//			pev->nextthink = gpGlobals->time + 0.01;
//			pev->velocity = g_vecDummy;
//			g_vecZero;
//			pev->avelocity.z = 1;
//
//			ResetSequenceInfo();
//			pev->sequence = 1;
//			ResetSequenceInfo();
//			pev->sequence = 1;
//
//			SetTouch(&CSatchelCharge::SatchelSlide);
//			SetUse(&CSatchelCharge::SatchelUse);
//			SetThink(&CSatchelCharge::SatchelThink);
//			pev->nextthink = gpGlobals->time + 0.1;
//
//			pev->gravity = 0.5;
//			pev->friction = 0.8;
//
//			return;
//		}
//	}
//
//	if (!IsInWorld())
//	{
//		UTIL_Remove(this);
//		return;
//	}
//}
//
//void CSatchelCharge::SatchelUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
//{
//	/*
//	if (!pActivator)
//		return;
//
//	if (!pActivator->IsPlayer())
//		return;
//
//	if (useType == USE_SET)
//	{
//		CBasePlayer* pPlayer = (CBasePlayer*)pActivator;
//
//		// Play defuse sound
//		if (pPlayer->m_iDefuseMeter == 0)
//		{
//			EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/defuse.wav", 1.0, ATTN_NORM);
//		}
//
//		CBaseEntity* pCompare = CBaseEntity::Instance(pev->owner);
//
//		if (pCompare)
//		{
//			if (pCompare == pActivator)
//				pPlayer->m_iDefuseMeter += 250;
//		}
//
//		pPlayer->m_iDefuseMeter++;
//
//		pPlayer->m_flNextDefuse = 0.1f;
//
//		// Defuse and set appropriate logics
//		if (pPlayer->m_iDefuseMeter >= 250)
//		{
//			STOP_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/defuse.wav");
//			EMIT_SOUND(ENT(pev), CHAN_ITEM, "weapons/satchel/defuse.wav", 1.0, ATTN_NORM);
//			CBaseEntity* pCharge = Create("weapon_satchel", pev->origin, pev->angles);
//			//pCharge->DisplacerAdjustment();
//			pCharge->pev->spawnflags |= SF_NORESPAWN;
//			pCharge->pev->skin = pev->skin;
//			pCharge->pev->origin = pev->origin;
//			pCharge->pev->angles = pev->angles;
//
//			SetThink(&CBaseEntity::SUB_Remove);
//			SetUse(NULL);
//			pev->nextthink = gpGlobals->time + 0.01;
//
//			if (pCompare && (pCompare == pActivator))
//			{
//				pPlayer->m_iDefuseMeter = -50;
//				pPlayer->m_flNextDefuse = 0.5f;
//			}
//			else
//			{
//				pPlayer->m_iDefuseMeter = 0;
//			}
//			return;
//		}
//	}
//
//	if (useType == USE_ON)
//	{
//		SetUse(NULL);
//		CGrenade::DetonateUse(pActivator, pCaller, useType, value);
//	}
//	*/
//}
//
//void CSatchelCharge::Precache(void)
//{
//	PRECACHE_MODEL("models/w_satchel.mdl");
//	PRECACHE_SOUND("weapons/satchel/bounce1.wav");
//	PRECACHE_SOUND("weapons/satchel/bounce2.wav");
//	PRECACHE_SOUND("weapons/satchel/bounce3.wav");
//	PRECACHE_SOUND("weapons/satchel/bounce4.wav");
//	PRECACHE_SOUND("weapons/satchel/bounce5.wav");
//	PRECACHE_SOUND("weapons/satchel/arm_plant.wav");
//	PRECACHE_SOUND("weapons/satchel/arm_throw.wav");
//	PRECACHE_SOUND("weapons/satchel/defuse.wav");
//}
//
//void CSatchelCharge::BounceSound(void)
//{
//	switch (RANDOM_LONG(0, 4))
//	{
//	default:EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/satchel/bounce1.wav", 1, ATTN_NORM);	break;
//	case 1:	EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/satchel/bounce2.wav", 1, ATTN_NORM);	break;
//	case 2:	EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/satchel/bounce3.wav", 1, ATTN_NORM);	break;
//	case 3:	EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/satchel/bounce4.wav", 1, ATTN_NORM);	break;
//	case 4:	EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/satchel/bounce5.wav", 1, ATTN_NORM);	break;
//	}
//}
//
//TYPEDESCRIPTION	CSatchelCharge::m_SaveData[] =
//{
//	DEFINE_FIELD(CSatchelCharge, m_iSatchelType, FIELD_INTEGER),
//};
//IMPLEMENT_SAVERESTORE(CSatchelCharge, CGrenade);
//
//#endif
//
////=========================================================
////=========================================================
//
//LINK_ENTITY_TO_CLASS(weapon_satchel, CSatchel);
//
//void CSatchel::Spawn()
//{
//	Precache();
//	m_iId = WEAPON_SATCHEL;
//	SET_MODEL(ENT(pev), "models/w_satchel.mdl");
//	m_iDefaultAmmo = SATCHEL_DEFAULT_GIVE;
//	FallInit();// get ready to fall down.
//}
//
//
//void CSatchel::Precache(void)
//{
//	PRECACHE_MODEL("models/v_satchel.mdl");
//	PRECACHE_MODEL("models/w_satchel.mdl");
//	PRECACHE_MODEL("models/p_satchel.mdl");
//
//	PRECACHE_SOUND("weapons/satchel/detonate.wav");
//	PRECACHE_SOUND("weapons/satchel/magnetise.wav");
//	PRECACHE_SOUND("weapons/satchel/demagnetise.wav");
//	PRECACHE_SOUND("weapons/satchel/throw.wav");
//	PRECACHE_SOUND("weapons/satchel/plant.wav");
//	PRECACHE_SOUND("weapons/satchel/pickup.wav");
//	PRECACHE_SOUND("weapons/satchel/arm_plant.wav");
//	PRECACHE_SOUND("weapons/satchel/arm_throw.wav");
//	PRECACHE_SOUND("weapons/satchel/exp.wav");
//
//	UTIL_PrecacheOther("monster_satchel");
//}
//
//
//int CSatchel::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "satchel";
//	p->iMaxAmmo1 = SATCHEL_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = WEAPON_NOCLIP_RELOAD;
//	p->iSlot = WEAPON_BUCKET_TRAPS;
//	p->iPosition = WEAPON_SATCHEL_SLOT;
//	p->iFlags = ITEM_FLAG_NOAUTORELOAD | ITEM_FLAG_SELECTONEMPTY | ITEM_FLAG_LIMITINWORLD | ITEM_FLAG_EXHAUSTIBLE;
//	p->iId = m_iId = WEAPON_SATCHEL;
//	p->iWeight = SATCHEL_WEIGHT;
//
//	return 1;
//}
//
//int CSatchel::HUDIcon(void)
//{
//	return 101;
//}
//
//int CSatchel::HUDActiveIcon(void)
//{
//	return 102;
//}
//
//int CSatchel::ModeIcon(void)
//{
//	if (m_bSticky)
//		return 61;
//
//	return -1;
//}
//
//int CSatchel::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CSatchel::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CSatchel::SmallIcon(void)
//{
//	return 57;
//}
//
//BOOL CSatchel::ShouldDisplayThrowForce(void)
//{
//	return (BOOL)(m_fArmed && m_iForce >= 10);
//}
//
//int CSatchel::GetThrowForce(void)
//{
//	return m_iForce;
//}
//
//int CSatchel::GetMaxThrowForce(void)
//{
//	return 100;
//}
//
//void CSatchel::ItemPostFrame(void)
//{
//	UpdateBodygroup();
//	SatchelLogic();
//	CBasePlayerWeapon::ItemPostFrame();
//}
//
//BOOL CSatchel::HasAmmo(void)
//{
//	if (m_iDefaultAmmo > 0)
//		return TRUE;
//
//	if (m_pPlayer)
//	{
//		if (HasPrimaryAmmo(TRUE))
//			return TRUE;
//	}
//
//	return FALSE;
//}
//
//void CSatchel::ClearSatchel(void)
//{
//	// Clear all values to prevent abnormal behavior, call when throwing grenade or changing weapons
//	m_fArmed = FALSE;
//	m_iForce = 0;
//}
//
//void CSatchel::UpdateBodygroup(void)
//{
//	// Viewmodel
//	if (m_pPlayer)
//	{
//		m_pPlayer->pev->viewmodelbody = 0;
//		m_pPlayer->pev->viewmodelskin = 0;
//
//		if (HasAmmo() && m_flRedraw < 0)
//			m_pPlayer->pev->playmodelbody = 1;
//		else
//			m_pPlayer->pev->playmodelbody = 0;
//
//		m_pPlayer->pev->playmodelskin = 0;
//	}
//
//	pev->body = 0;
//	pev->skin = 0;
//}
//
//void CSatchel::SatchelLogic(void)
//{
//	if (m_flRedraw > 0)
//	{
//		m_flRedraw -= gpGlobals->frametime;
//		if (m_flRedraw <= 0)
//		{
//			if (HasAmmo() == TRUE)
//			{
//				// Increment if you have infinite ammo as to avoid animation glitches
//				if (m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()] <= 0)
//					m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()]++;
//
//				SendWeaponAnim(SATCHEL_REDRAW);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//				UnsetIdle();
//				m_flRedraw = -1;
//			}
//			else
//			{
//				m_flRedraw = 0.1;
//				// Don't set the m_flNextWeaponIdle here because the radio can still idle on its own
//			}
//		}
//	}
//
//	// If satchel is not armed, do not call anything
//	if (m_fArmed == FALSE)
//		return;
//
//	if (m_pPlayer->pev->button & IN_ATTACK && m_iForce < 100)
//		m_iForce += 2;
//	else
//		Throw();
//}
//
//void CSatchel::PickupSound(void)
//{
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/satchel/pickup.wav", 1, ATTN_NORM);
//}
//
////=========================================================
////=========================================================
//BOOL CSatchel::IsUseable(void)
//{
//	return TRUE;
//}
//
//BOOL CSatchel::CanDeploy(void)
//{
//	return TRUE;
//}
//
//BOOL CSatchel::Deploy(void)
//{
//	UpdateBodygroup();
//	ClearSatchel();
//
//	int result = 0;
//
//	if (HasAmmo())
//	{
//		result = DefaultDeploy("models/v_satchel.mdl", "models/p_satchel.mdl", SATCHEL_DRAW, "trip");
//		m_flRedraw = -1;
//		m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.45;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//	}
//	else
//	{
//		result = DefaultDeploy("models/v_satchel.mdl", "models/p_satchel.mdl", SATCHEL_RADIO_DRAW, "trip");
//		m_flRedraw = 0.50;
//		m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.50;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//	}
//
//	UnsetIdle();
//	return (BOOL)result;
//}
//
//void CSatchel::Holster(int skiplocal /* = 0 */)
//{
//	UpdateBodygroup();
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.0;
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//
//	if (HasAmmo() == TRUE && m_flRedraw < 0 && m_fArmed == FALSE)
//		SendWeaponAnim(SATCHEL_HOLSTER);
//	else
//		SendWeaponAnim(SATCHEL_RADIO_HOLSTER);
//
//	ClearSatchel();
//	UnsetIdle();
//	m_flRedraw = -1;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//}
//
//
//// Primary Attack only initiates the throw, everything else is handled within SatchelLogic
//void CSatchel::PrimaryAttack(void)
//{
//	if (m_fArmed || !HasAmmo())
//		return;
//
//	SendWeaponAnim(SATCHEL_PREPTHROW);
//	m_fArmed = TRUE;
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 5.0;
//
//	UnsetIdle();
//}
//
//// Secondary Attack detonates
//void CSatchel::SecondaryAttack(void)
//{
//	Detonate();
//}
//
//// Stick it on the wall if possible
//void CSatchel::TertiaryAttack(void)
//{
//	Plant();
//}
//
//// Swap to sticky mode, 
//void CSatchel::Reload(void)
//{
//	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase() || m_flNextSecondaryAttack > UTIL_WeaponTimeBase() || m_flNextTertiaryAttack > UTIL_WeaponTimeBase())
//		return;
//
//	if (m_bSticky)
//	{
//		m_bSticky = FALSE;
//		EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/satchel/demagnetise.wav", 1, ATTN_NORM);
//	}
//	else
//	{
//		m_bSticky = TRUE;
//		EMIT_SOUND(ENT(pev), CHAN_WEAPON2, "weapons/satchel/magnetise.wav", 1, ATTN_NORM);
//	}
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.40;
//}
//
//// Pressing the button to detonate
//void CSatchel::Detonate(void)
//{
//	if (m_fArmed)
//		return;
//
//	if (HasAmmo())
//		SendWeaponAnim(SATCHEL_FIRE);
//	else
//		SendWeaponAnim(SATCHEL_RADIO_FIRE);
//
//	if (m_chargeReady == 1)
//	{
//		edict_t* pPlayer = m_pPlayer->edict();
//
//		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/satchel/detonate.wav", 1, ATTN_NORM);
//
//		CBaseEntity* pSatchel = NULL;
//
//		while ((pSatchel = UTIL_FindEntityInSphere(pSatchel, m_pPlayer->pev->origin, 4096)) != NULL)
//		{
//			if (FClassnameIs(pSatchel->pev, "monster_satchel"))
//			{
//				if (pSatchel->pev->owner == pPlayer)
//				{
//					pSatchel->Use(m_pPlayer, m_pPlayer, USE_ON, 0);
//				}
//			}
//		}
//		m_chargeReady = 0;
//	}
//
//	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.0;
//	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.0;
//	m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.0;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
//
//	UnsetIdle();
//}
//
//void CSatchel::Throw(void)
//{
//	if (HasAmmo())
//	{
//		// + m_pPlayer->pev->view_ofs
//		Vector vecSrc = m_pPlayer->pev->origin + gpGlobals->v_forward * 16;
//		Vector angThrow = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
//		float flVel = 100 + 500 * ((float)m_iForce / 100); // originally 800
//		UTIL_MakeVectors(angThrow);
//		Vector vecThrow = gpGlobals->v_forward * flVel + m_pPlayer->pev->velocity;
//
//#ifndef CLIENT_DLL
//		CSatchelCharge* pSatchel = GetClassPtr((CSatchelCharge*)NULL);
//		UTIL_SetOrigin(pSatchel->pev, vecSrc);
//		pSatchel->pev->classname = MAKE_STRING("monster_satchel");	// g-cont. enable save\restore
//		pSatchel->pev->owner = m_pPlayer->edict();
//		pSatchel->m_iGrenadeType = pSatchel->TYPE_SATCHEL;
//		if (m_bSticky)
//			pSatchel->m_iSatchelType = pSatchel->SATCHEL_STICKY;
//		else
//			pSatchel->m_iSatchelType = pSatchel->SATCHEL_THROWN;
//		pSatchel->Spawn();
//		pSatchel->pev->velocity = vecThrow;
//
//		if (!m_bSticky)
//		{
//			pSatchel->pev->avelocity.y = 400;
//		}
//		else
//		{
//			// Yes
//			pSatchel->pev->angles.x -= 180;
//			pSatchel->pev->angles.y = m_pPlayer->pev->angles.y - 180;
//			pSatchel->pev->angles.z -= 180;
//
//		}
//#endif
//
//		EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/satchel/throw.wav", 1, ATTN_NORM);
//
//		m_chargeReady = 1;
//
//		if (!HasInfinitePrimaryAmmo())
//			--m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType];
//
//		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.53;
//		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.53;
//		m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.53;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//
//		m_flRedraw = 0.53f;
//
//		ClearSatchel();
//
//		SendWeaponAnim(SATCHEL_THROW);
//
//		UnsetIdle();
//	}
//}
//
//void CSatchel::Plant(void)
//{
//	if (!HasAmmo())
//		return;
//
//	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//	Vector vecAiming = gpGlobals->v_forward;
//
//	TraceResult tr;
//
//	UTIL_TraceLine(vecSrc, vecSrc + vecAiming * 128, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);
//
//	int flags;
//#ifdef CLIENT_WEAPONS
//	flags = FEV_NOTHOST;
//#else
//	flags = 0;
//#endif
//	if (tr.flFraction < 1.0)
//	{
//		CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);
//		if (pEntity)
//		{
//			if (pEntity->IsBSPModel() && !(pEntity->pev->flags & FL_CONVEYOR))
//			{
//				SendWeaponAnim(SATCHEL_SET);
//
//				Vector angles = UTIL_VecToAngles(tr.vecPlaneNormal);
//#ifndef CLIENT_DLL
//				CSatchelCharge* pSatchel = GetClassPtr((CSatchelCharge*)NULL);
//				UTIL_SetOrigin(pSatchel->pev, tr.vecEndPos + tr.vecPlaneNormal * 4);
//				pSatchel->pev->angles = angles;
//				pSatchel->pev->classname = MAKE_STRING("monster_satchel");	// g-cont. enable save\restore
//				pSatchel->pev->owner = m_pPlayer->edict();
//				pSatchel->m_iGrenadeType = pSatchel->TYPE_SATCHEL;
//				pSatchel->m_iSatchelType = pSatchel->SATCHEL_SET;
//				pSatchel->Spawn();
//				pSatchel->pev->movetype = MOVETYPE_COMPOUND;
//				pSatchel->pev->aiment = pEntity->edict();
//
//				//ALERT(at_console, "aiment %s\n", STRING(pEntity->pev->classname));
//
//				// Yes
//				pSatchel->pev->angles.x -= 180;
//				pSatchel->pev->angles.y = m_pPlayer->pev->angles.y - 180;
//				pSatchel->pev->angles.z -= 180;
//
//#endif
//				EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/satchel/plant.wav", 1, ATTN_NORM);
//
//				m_chargeReady = 1;
//
//				if (!HasInfinitePrimaryAmmo())
//					m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;
//
//				// player "shoot" animation
//				m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//				m_flNextTertiaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.36;
//				m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.26;
//				m_flRedraw = 0.36;
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
//
//				UnsetIdle();
//			}
//		}
//	}
//
//}
//
//void CSatchel::WeaponIdle(void)
//{
//	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase())
//		return;
//
//	// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//	if (RANDOM_LONG(0, 99) <= 5)
//	{
//		UpdateBodygroup();
//		if (HasAmmo())
//			SendWeaponAnim(SATCHEL_FIDGET);
//		else
//			SendWeaponAnim(SATCHEL_RADIO_FIDGET);
//		UnsetIdle();
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.7;
//	}
//	else
//	{
//		// Ensure at least two successful loops
//		if (!IsIdle())
//		{
//			UpdateBodygroup();
//			if (HasAmmo())
//			{
//				SendWeaponAnim(SATCHEL_IDLE);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 4.05 * 2;
//			}
//			else
//			{
//				SendWeaponAnim(SATCHEL_RADIO_IDLE);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.7 * 2;
//			}
//			SetIdle();
//		}
//		else
//		{
//			// Only perform a single loop in this case
//			if (HasAmmo())
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 4.05;
//			else
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.7;
//		}
//	}
//}
////=========================================================
//// DeactivateSatchels - removes all satchels owned by
//// the provided player. Should only be used upon death.
////
//// Made this global on purpose.
////=========================================================
//void DeactivateSatchels(CBasePlayer* pOwner)
//{
//	edict_t* pFind;
//
//	pFind = FIND_ENTITY_BY_CLASSNAME(NULL, "monster_satchel");
//
//	while (!FNullEnt(pFind))
//	{
//		CBaseEntity* pEnt = CBaseEntity::Instance(pFind);
//		CSatchelCharge* pSatchel = (CSatchelCharge*)pEnt;
//
//		if (pSatchel)
//		{
//			if (pSatchel->pev->owner == pOwner->edict())
//			{
//#ifndef CLIENT_DLL
//				pSatchel->Deactivate();
//#endif
//			}
//		}
//
//		pFind = FIND_ENTITY_BY_CLASSNAME(pFind, "monster_satchel");
//	}
//}