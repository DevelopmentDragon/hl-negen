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
//#if !defined( OEM_BUILD ) && !defined( HLDEMO_BUILD )
//
//#include "extdll.h"
//#include "util.h"
//#include "cbase.h"
//#include "player.h"
//#include "monsters.h"
//#include "weapons.h"
//#include "nodes.h"
//#include "effects.h"
//#include "customentity.h"
//#include "gamerules.h"
//
//#define	EGON_PRIMARY_VOLUME		450
//#define EGON_BEAM_SPRITE		"sprites/xbeam1.spr"
//#define EGON_FLARE_SPRITE		"sprites/XSpark1.spr"
//#define EGON_FLARE_SPRITE2		"sprites/XSpark5.spr"
//#define EGON_SHOCKWAVE_SPRITE	"sprites/shockwave.spr"
//#define EGON_SOUND_OFF			"weapons/egon/end.wav"
//#define EGON_SOUND_RUN			"weapons/egon/loop.wav"
//#define EGON_SOUND_STARTUP		"weapons/egon/start.wav"
//
//#define EGON_SWITCH_NARROW_TIME			0.75			// Time it takes to switch fire modes
//#define EGON_SWITCH_WIDE_TIME			1.5
//
//LINK_ENTITY_TO_CLASS(weapon_egon, CEgon);
//
//void CEgon::PickupSound(void)
//{
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/egon/pickup.wav", 1, ATTN_NORM);
//}
//
//int CEgon::HUDIcon(void)
//{
//	return 127 + HasWeaponUpgrades(UPGRADE_EGONP) * 2 + HasWeaponUpgrades(UPGRADE_EGONE) * 4;
//}
//
//int CEgon::HUDActiveIcon(void)
//{
//	return 128 + HasWeaponUpgrades(UPGRADE_EGONP) * 2 + HasWeaponUpgrades(UPGRADE_EGONE) * 4;;
//}
//
//int CEgon::ModeIcon(void)
//{
//	if (m_fireMode)
//		return 73;
//
//	return 75;
//}
//
//int CEgon::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CEgon::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CEgon::SmallIcon(void)
//{
//	return 73
//		+ HasWeaponUpgrades(UPGRADE_EGONP) * 2
//		+ HasWeaponUpgrades(UPGRADE_EGONE) * 4;
//}
//
//void CEgon::Spawn(void)
//{
//	pev->classname = MAKE_STRING("weapon_egon");
//	Precache();
//	m_iId = WEAPON_EGON;
//	SET_MODEL(ENT(pev), "models/w_egon.mdl");
//	m_iDefaultAmmo = EGON_DEFAULT_GIVE;
//
//	FallInit();// get ready to fall down.
//}
//
//
//void CEgon::Precache(void)
//{
//	PRECACHE_MODEL("models/w_egon.mdl");
//	PRECACHE_MODEL("models/v_egon.mdl");
//	PRECACHE_MODEL("models/p_egon.mdl");
//
//	PRECACHE_MODEL("models/w_9mmclip.mdl");
//	PRECACHE_SOUND("items/9mmclip1.wav");
//
//	PRECACHE_SOUND(EGON_SOUND_OFF);
//	PRECACHE_SOUND(EGON_SOUND_RUN);
//	PRECACHE_SOUND(EGON_SOUND_STARTUP);
//	PRECACHE_SOUND("weapons/egon/blast.wav");
//	PRECACHE_SOUND("weapons/egon/pickup.wav");
//
//	PRECACHE_MODEL(EGON_BEAM_SPRITE);
//	PRECACHE_MODEL(EGON_FLARE_SPRITE);
//	PRECACHE_MODEL(EGON_FLARE_SPRITE2);
//	m_iSpriteIndex = PRECACHE_MODEL(EGON_SHOCKWAVE_SPRITE);
//	// "sprites/shockwave.spr"
//
//	m_usEgonFire = PRECACHE_EVENT(1, "events/egon_fire.sc");
//	m_usEgonStop = PRECACHE_EVENT(1, "events/egon_stop.sc");
//}
//
//
//BOOL CEgon::Deploy(void)
//{
//	m_deployed = FALSE;
//	m_fireState = FIRE_OFF;
//
//	UpdateBodygroup();
//	return DefaultDeploy("models/v_egon.mdl", "models/p_egon.mdl", (m_fireMode == FIRE_WIDE) ? EGON_DRAW : EGON_ALTDRAW, "egon");
//}
//
//void CEgon::UpdateBodygroup(void)
//{
//	if (m_pPlayer)
//	{
//		m_pPlayer->pev->viewmodelbody = HasWeaponUpgrades(UPGRADE_EGONP) * 1 + HasWeaponUpgrades(UPGRADE_EGONE) * 2 + 4 * m_pPlayer->pev->armortype;
//		m_pPlayer->pev->playmodelbody = HasWeaponUpgrades(UPGRADE_EGONP) * 1 + HasWeaponUpgrades(UPGRADE_EGONE) * 2;
//	}
//
//	pev->body = HasWeaponUpgrades(UPGRADE_EGONP) * 1 + HasWeaponUpgrades(UPGRADE_EGONE) * 2;
//}
//
//void CEgon::ItemPostFrame(void)
//{
//	UpdateBodygroup();
//	//ALERT( at_console, "Name is: %s\n", STRING(pev->classname) );
//	CBasePlayerWeapon::ItemPostFrame();
//}
//
//void CEgon::Holster(int skiplocal /* = 0 */)
//{
//	UpdateBodygroup();
//	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
//	EndAttack();
//	SendWeaponAnim((m_fireMode == FIRE_WIDE) ? EGON_HOLSTER : EGON_ALTHOLSTER);
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//}
//
//int CEgon::SecondaryAmmoIndex(void)
//{
//	return m_iSecondaryAmmoType;
//}
//
//int CEgon::PrimaryAmmoIndex(void)
//{
//	return m_iPrimaryAmmoType;
//}
//
//int CEgon::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "uranium";
//	p->iMaxAmmo1 = URANIUM_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = WEAPON_NOCLIP_RELOAD;
//	p->iSlot = WEAPON_BUCKET_ENERGY;
//	p->iPosition = WEAPON_DISPLACER_SLOT;
//	p->iId = m_iId = WEAPON_EGON;
//	p->iFlags = 0;
//	p->iWeight = EGON_WEIGHT;
//
//	return 1;
//}
//
//#define EGON_PULSE_INTERVAL			0.1
//#define EGON_DISCHARGE_INTERVAL		0.1
//
//float CEgon::GetPulseInterval(void)
//{
//	return EGON_PULSE_INTERVAL;
//}
//
//float CEgon::GetDischargeInterval(void)
//{
//	return EGON_DISCHARGE_INTERVAL;
//}
//
//BOOL CEgon::HasAmmo(void)
//{
//	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 && m_pPlayer->m_flInfiniteAmmo < 1)
//		return FALSE;
//
//	return TRUE;
//}
//
//void CEgon::UseAmmo(int count)
//{
//	if (m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] < URANIUMW_MAX_CARRY)
//		m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] = min(URANIUMW_MAX_CARRY, count + m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType]);
//
//	if (m_pPlayer->m_flInfiniteAmmo > 0)
//		return;
//
//	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] >= count)
//		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] -= count;
//	else
//		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] = 0;
//}
//
//void CEgon::Attack(void)
//{
//	// don't fire underwater
//	if (m_pPlayer->pev->waterlevel == 3)
//	{
//
//		if (m_fireState != FIRE_OFF || m_pBeam)
//		{
//			EndAttack();
//		}
//		else
//		{
//			PlayEmptySound();
//		}
//		return;
//	}
//
//	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
//	Vector vecAiming = gpGlobals->v_forward;
//	Vector vecSrc = m_pPlayer->GetGunPosition();
//
//	int flags;
//#if defined( CLIENT_WEAPONS )
//	flags = FEV_NOTHOST;
//#else
//	flags = 0;
//#endif
//
//	switch (m_fireState)
//	{
//	case FIRE_OFF:
//	{
//		if (!HasAmmo())
//		{
//			m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.25;
//			PlayEmptySound();
//			return;
//		}
//
//		m_flAmmoUseTime = gpGlobals->time;// start using ammo ASAP.
//
//		UpdateBodygroup();
//		int iAnim = m_pPlayer->pev->savedvanim = (m_fireMode ? RANDOM_LONG(EGON_ALTFIRE1, EGON_ALTFIRE5) : RANDOM_LONG(EGON_FIRE1, EGON_FIRE5));
//		float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
//		byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//		PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usEgonFire, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0,
//			1, m_pPlayer->pev->viewmodelbody, m_fireState, m_fireMode, (float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);
//
//		m_shakeTime = 0;
//
//		m_pPlayer->m_iWeaponVolume = EGON_PRIMARY_VOLUME;
//		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 0.1;
//		UnsetIdle();
//		pev->fuser1 = UTIL_WeaponTimeBase() + 0.65;
//
//		pev->dmgtime = gpGlobals->time + GetPulseInterval();
//		m_fireState = FIRE_CHARGE;
//	}
//	break;
//
//	case FIRE_CHARGE:
//	{
//		Fire(vecSrc, vecAiming);
//		m_pPlayer->m_iWeaponVolume = EGON_PRIMARY_VOLUME;
//
//		if (pev->fuser1 <= UTIL_WeaponTimeBase())
//		{
//			UpdateBodygroup();
//			int iAnim = m_pPlayer->pev->savedvanim = (m_fireMode ? RANDOM_LONG(EGON_ALTFIRE1, EGON_ALTFIRE5) : RANDOM_LONG(EGON_FIRE1, EGON_FIRE5));
//			float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
//			byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;
//			PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usEgonFire, 0, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0,
//				0, m_pPlayer->pev->viewmodelbody, m_fireState, m_fireMode, (float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);
//			pev->fuser1 = 1000;
//		}
//
//		if (!HasAmmo())
//		{
//			EndAttack();
//			m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.0;
//		}
//
//	}
//	break;
//	}
//}
//
//void CEgon::PrimaryAttack(void)
//{
//	Attack();
//}
//
//void CEgon::SecondaryAttack(void)
//{
//	EndAttack();
//
//	UpdateBodygroup();
//	if (m_fireMode == FIRE_WIDE)
//	{
//		SendWeaponAnim(EGON_SWITCH);
//		m_fireMode = FIRE_NARROW;
//	}
//	else
//	{
//		SendWeaponAnim(EGON_ALTSWITCH);
//		m_fireMode = FIRE_WIDE;
//	}
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.0;
//}
//
//void CEgon::Reload(void)
//{
//	// Return
//	return;
//
//	// Check time
//	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase())
//		return;
//
//	// Check ammo
//	if (m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] <= 0)
//		return;
//
//	float		flAdjustedDamage;
//	float		flDist;
//
//	BYTE		red;
//	BYTE		green;
//	BYTE		blue;
//
//	if (HasWeaponUpgrades(UPGRADE_EGONP))
//	{
//		red = 255;
//		green = 0;
//		blue = 0;
//	}
//	else
//	{
//		red = 30;
//		green = 30;
//		blue = 144;
//	}
//
//	UpdateBodygroup();
//	SendWeaponAnim((m_fireMode == FIRE_WIDE) ? EGON_FIDGET1 : EGON_ALTFIDGET1);
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/egon/blast.wav", 1, ATTN_NORM);
//
//	// blast circles
//	MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, m_pPlayer->pev->origin);
//	WRITE_BYTE(TE_BEAMCYLINDER);
//	WRITE_COORD(m_pPlayer->pev->origin.x);
//	WRITE_COORD(m_pPlayer->pev->origin.y);
//	WRITE_COORD(m_pPlayer->pev->origin.z + 16);
//	WRITE_COORD(m_pPlayer->pev->origin.x);
//	WRITE_COORD(m_pPlayer->pev->origin.y);
//	WRITE_COORD(m_pPlayer->pev->origin.z + 16 + 150 / .2); // reach damage radius over .3 seconds
//	WRITE_SHORT(m_iSpriteIndex);
//	WRITE_BYTE(0); // startframe
//	WRITE_BYTE(0); // framerate
//	WRITE_BYTE(2); // life
//	WRITE_BYTE(16);  // width
//	WRITE_BYTE(0);   // noise
//
//	WRITE_BYTE(red);
//	WRITE_BYTE(green);
//	WRITE_BYTE(blue);
//
//	WRITE_BYTE(255); //brightness
//	WRITE_BYTE(0);		// speed
//	MESSAGE_END();
//
//	MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, m_pPlayer->pev->origin);
//	WRITE_BYTE(TE_BEAMCYLINDER);
//	WRITE_COORD(m_pPlayer->pev->origin.x);
//	WRITE_COORD(m_pPlayer->pev->origin.y);
//	WRITE_COORD(m_pPlayer->pev->origin.z + 16);
//	WRITE_COORD(m_pPlayer->pev->origin.x);
//	WRITE_COORD(m_pPlayer->pev->origin.y);
//	WRITE_COORD(m_pPlayer->pev->origin.z + 16 + (150 / 2) / .2); // reach damage radius over .3 seconds
//	WRITE_SHORT(m_iSpriteIndex);
//	WRITE_BYTE(0); // startframe
//	WRITE_BYTE(0); // framerate
//	WRITE_BYTE(2); // life
//	WRITE_BYTE(16);  // width
//	WRITE_BYTE(0);   // noise
//
//	WRITE_BYTE(red);
//	WRITE_BYTE(green);
//	WRITE_BYTE(blue);
//
//	WRITE_BYTE(255); //brightness
//	WRITE_BYTE(0);		// speed
//	MESSAGE_END();
//
//	CBaseEntity* pEntity = NULL;
//	// iterate on all entities in the vicinity.
//	while ((pEntity = UTIL_FindEntityInSphere(pEntity, m_pPlayer->pev->origin, 150)) != NULL)
//	{
//		if (pEntity->pev->takedamage != DAMAGE_NO)
//		{
//			if (pEntity != (CBaseEntity*)m_pPlayer)
//			{// houndeyes don't hurt other houndeyes with their attack
//
//				// houndeyes do FULL damage if the ent in question is visible. Half damage otherwise.
//				// This means that you must get out of the houndeye's attack range entirely to avoid damage.
//				// Calculate full damage first
//
//				flAdjustedDamage = gSkillData.plrDmgEgonWide * m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType];
//
//				if (HasWeaponUpgrades(UPGRADE_EGONP))
//					flAdjustedDamage *= 1.25;
//
//				flDist = (pEntity->Center() - m_pPlayer->pev->origin).Length();
//
//				flAdjustedDamage -= (flDist / 150) * flAdjustedDamage;
//
//				if (!FVisible(pEntity))
//				{
//					if (pEntity->IsPlayer())
//					{
//						// if this entity is a client, and is not in full view, inflict half damage. We do this so that players still 
//						// take the residual damage if they don't totally leave the houndeye's effective radius. We restrict it to clients
//						// so that monsters in other parts of the level don't take the damage and get pissed.
//						flAdjustedDamage *= 0.5;
//					}
//					else if (!FClassnameIs(pEntity->pev, "func_breakable") && !FClassnameIs(pEntity->pev, "func_pushable"))
//					{
//						// do not hurt nonclients through walls, but allow damage to be done to breakables
//						flAdjustedDamage = 0;
//					}
//				}
//
//				//ALERT ( at_aiconsole, "Damage: %f\n", flAdjustedDamage );
//
//				if (flAdjustedDamage > 0)
//				{
//					pEntity->TakeDamage(m_pPlayer->pev, m_pPlayer->pev, flAdjustedDamage, DMG_BLAST | DMG_RADIATION, ID_DMG_EGON_RELEASE);
//				}
//			}
//		}
//	}
//
//	m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] = 0;
//	UnsetIdle();
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.5;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//}
//
//void CEgon::Fire(const Vector& vecOrigSrc, const Vector& vecDir)
//{
//	Vector vecDest = vecOrigSrc + vecDir * 8192; //2048;
//	edict_t* pentIgnore;
//	TraceResult tr;
//
//	pentIgnore = m_pPlayer->edict();
//	Vector tmpSrc = vecOrigSrc + gpGlobals->v_up * -8 + gpGlobals->v_right * 3;
//
//	// ALERT( at_console, "." );
//
//	UTIL_TraceLine(vecOrigSrc, vecDest, dont_ignore_monsters, pentIgnore, &tr);
//
//	if (tr.fAllSolid)
//		return;
//
//#ifndef CLIENT_DLL
//	CBaseEntity* pEntity = CBaseEntity::Instance(tr.pHit);
//
//	if (pEntity == NULL)
//		return;
//
//	if (g_pGameRules->IsMultiplayer())
//	{
//		if (m_pSprite && pEntity->pev->takedamage)
//		{
//			m_pSprite->pev->effects &= ~EF_NODRAW;
//		}
//		else if (m_pSprite)
//		{
//			m_pSprite->pev->effects |= EF_NODRAW;
//		}
//	}
//
//
//#endif
//
//	float timedist;
//
//	switch (m_fireMode)
//	{
//	case FIRE_NARROW:
//#ifndef CLIENT_DLL
//		if (pev->dmgtime < gpGlobals->time)
//		{
//			// Narrow mode only does damage to the entity it hits
//			//ClearMultiDamage();
//			if (pEntity->pev->takedamage)
//			{
//				float calcDamage = gSkillData.plrDmgEgonNarrow;
//				if (HasWeaponUpgrades(UPGRADE_EGONP))
//					calcDamage *= 1.25;
//				pEntity->TraceAttack(m_pPlayer->pev, calcDamage, vecDir, &tr, DMG_ENERGYBEAM, ID_DMG_EGON_NARROW);
//			}
//			//ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev, ID_DMG_GENERIC);
//
//
//			// single player, use 3 ammo/second
//			if (gpGlobals->time >= m_flAmmoUseTime)
//			{
//				UseAmmo(1);
//				if (HasWeaponUpgrades(UPGRADE_EGONE))
//					m_flAmmoUseTime = gpGlobals->time + 0.332;
//				else
//					m_flAmmoUseTime = gpGlobals->time + 0.166;
//			}
//
//			pev->dmgtime = gpGlobals->time + GetPulseInterval();
//		}
//#endif
//		timedist = (pev->dmgtime - gpGlobals->time) / GetPulseInterval();
//		break;
//
//	case FIRE_WIDE:
//#ifndef CLIENT_DLL
//		if (pev->dmgtime < gpGlobals->time)
//		{
//			float calcDamage = gSkillData.plrDmgEgonWide;
//			if (HasWeaponUpgrades(UPGRADE_EGONP))
//				calcDamage *= 1.25;
//
//			// wide mode does damage to the ent, and radius damage
//			//ClearMultiDamage();
//			if (pEntity->pev->takedamage)
//			{
//				pEntity->TraceAttack(m_pPlayer->pev, calcDamage, vecDir, &tr, DMG_ENERGYBEAM | DMG_ALWAYSGIB, ID_DMG_EGON_WIDE);
//			}
//			// radius damage used to be four times less, then half now it's full.
//			::RadiusDamage(tr.vecEndPos, pev, m_pPlayer->pev, calcDamage, 150, CLASS_NONE, DMG_ENERGYBEAM | DMG_BLAST | DMG_ALWAYSGIB, ID_DMG_EGON_WIDE_RADIUS);
//
//			if (!m_pPlayer->IsAlive())
//				return;
//
//			// Wide mode uses 10 charges per second in single player
//			if (gpGlobals->time >= m_flAmmoUseTime)
//			{
//				UseAmmo(1);
//				if (HasWeaponUpgrades(UPGRADE_EGONE))
//					m_flAmmoUseTime = gpGlobals->time + 0.18;
//				else
//					m_flAmmoUseTime = gpGlobals->time + 0.09;
//			}
//
//			pev->dmgtime = gpGlobals->time + GetDischargeInterval();
//			if (m_shakeTime < gpGlobals->time)
//			{
//				UTIL_ScreenShake(tr.vecEndPos, 5.0, 150.0, 0.75, 250.0);
//				m_shakeTime = gpGlobals->time + 1.5;
//			}
//		}
//#endif
//		timedist = (pev->dmgtime - gpGlobals->time) / GetDischargeInterval();
//		break;
//	}
//
//	if (timedist < 0)
//		timedist = 0;
//	else if (timedist > 1)
//		timedist = 1;
//	timedist = 1 - timedist;
//
//	UpdateEffect(tmpSrc, tr.vecEndPos, timedist);
//}
//
//
//void CEgon::UpdateEffect(const Vector& startPoint, const Vector& endPoint, float timeBlend)
//{
//#ifndef CLIENT_DLL
//	if (!m_pBeam)
//	{
//		CreateEffect();
//	}
//
//	m_pBeam->SetStartPos(endPoint);
//	m_pBeam->SetBrightness(255 - (timeBlend * 180));
//	m_pBeam->SetWidth(40 - (timeBlend * 20));
//
//	if (!HasWeaponUpgrades(UPGRADE_EGONP))
//	{
//		if (m_fireMode == FIRE_WIDE)
//			m_pBeam->SetColor(30 + (25 * timeBlend), 30 + (30 * timeBlend), 64 + 80 * fabs(sin(gpGlobals->time * 10)));
//		else
//			m_pBeam->SetColor(60 + (25 * timeBlend), 120 + (30 * timeBlend), 64 + 80 * fabs(sin(gpGlobals->time * 10)));
//	}
//	else
//	{
//		if (m_fireMode == FIRE_WIDE)
//			m_pBeam->SetColor(255, (30 * timeBlend), fabs(sin(gpGlobals->time * 10)));
//		else
//			m_pBeam->SetColor(204, (30 * timeBlend), fabs(sin(gpGlobals->time * 10)));
//	}
//
//
//	UTIL_SetOrigin(m_pSprite->pev, endPoint);
//	m_pSprite->pev->frame += 8 * gpGlobals->frametime;
//	if (m_pSprite->pev->frame > m_pSprite->Frames())
//		m_pSprite->pev->frame = 0;
//
//	m_pNoise->SetStartPos(endPoint);
//
//#endif
//
//}
//
//void CEgon::CreateEffect(void)
//{
//
//#ifndef CLIENT_DLL
//	DestroyEffect();
//
//	m_pBeam = CBeam::BeamCreate(EGON_BEAM_SPRITE, 40);
//	m_pBeam->PointEntInit(pev->origin, m_pPlayer->entindex());
//	m_pBeam->SetFlags(BEAM_FSINE);
//	m_pBeam->SetEndAttachment(1);
//	m_pBeam->pev->spawnflags |= SF_BEAM_TEMPORARY;	// Flag these to be destroyed on save/restore or level transition
//	m_pBeam->pev->flags |= FL_SKIPLOCALHOST;
//	m_pBeam->pev->owner = m_pPlayer->edict();
//
//	m_pNoise = CBeam::BeamCreate(EGON_BEAM_SPRITE, 55);
//	m_pNoise->PointEntInit(pev->origin, m_pPlayer->entindex());
//	m_pNoise->SetScrollRate(25);
//	m_pNoise->SetBrightness(100);
//	m_pNoise->SetEndAttachment(1);
//	m_pNoise->pev->spawnflags |= SF_BEAM_TEMPORARY;
//	m_pNoise->pev->flags |= FL_SKIPLOCALHOST;
//	m_pNoise->pev->owner = m_pPlayer->edict();
//
//	if (HasWeaponUpgrades(UPGRADE_EGONP))
//		m_pSprite = CSprite::SpriteCreate(EGON_FLARE_SPRITE2, pev->origin, FALSE);
//	else
//		m_pSprite = CSprite::SpriteCreate(EGON_FLARE_SPRITE, pev->origin, FALSE);
//	m_pSprite->pev->scale = 1.0;
//	m_pSprite->SetTransparency(kRenderGlow, 255, 255, 255, 255, kRenderFxNoDissipation);
//	m_pSprite->pev->spawnflags |= SF_SPRITE_TEMPORARY;
//	m_pSprite->pev->flags |= FL_SKIPLOCALHOST;
//	m_pSprite->pev->owner = m_pPlayer->edict();
//
//	if (m_fireMode == FIRE_WIDE)
//	{
//		m_pSprite->pev->scale = 4.0;
//		m_pBeam->SetScrollRate(50);
//		m_pBeam->SetNoise(20);
//		if (HasWeaponUpgrades(UPGRADE_EGONP))
//			m_pNoise->SetColor(255, 0, 0);
//		else
//			m_pNoise->SetColor(50, 50, 255);
//		m_pNoise->SetNoise(8);
//	}
//	else
//	{
//		m_pSprite->pev->scale = 1.0;
//		m_pBeam->SetScrollRate(110);
//		m_pBeam->SetNoise(5);
//		if (HasWeaponUpgrades(UPGRADE_EGONP))
//			m_pNoise->SetColor(204, 0, 0);
//		else
//			m_pNoise->SetColor(80, 120, 255);
//		m_pNoise->SetNoise(2);
//	}
//#endif
//
//}
//
//
//void CEgon::DestroyEffect(void)
//{
//
//#ifndef CLIENT_DLL
//	if (m_pBeam)
//	{
//		UTIL_Remove(m_pBeam);
//		m_pBeam = NULL;
//	}
//	if (m_pNoise)
//	{
//		UTIL_Remove(m_pNoise);
//		m_pNoise = NULL;
//	}
//	if (m_pSprite)
//	{
//		if (m_fireMode == FIRE_WIDE)
//			m_pSprite->Expand(10, 500);
//		else
//			UTIL_Remove(m_pSprite);
//		m_pSprite = NULL;
//	}
//#endif
//
//}
//
//
//
//void CEgon::WeaponIdle(void)
//{
//	ResetEmptySound();
//
//	if (m_fireState != FIRE_OFF)
//		EndAttack();
//
//	if (m_flNextWeaponIdle <= UTIL_WeaponTimeBase())
//	{
//		// Ensure at least two successful loops
//		if (!IsIdle())
//		{
//			UpdateBodygroup();
//			SendWeaponAnim((m_fireMode == FIRE_WIDE) ? EGON_IDLE1 : EGON_ALTIDLE1);
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0 * 2;
//			SetIdle();
//			m_deployed = TRUE;
//		}
//		else
//		{
//			// Only perform a single loop in this case
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//		}
//	}
//}
//
//
//
//void CEgon::EndAttack(void)
//{
//	bool bMakeNoise = false;
//
//	if (m_fireState != FIRE_OFF) //Checking the button just in case!.
//		bMakeNoise = true;
//
//	UpdateBodygroup();
//	PLAYBACK_EVENT_FULL(FEV_GLOBAL | FEV_RELIABLE, m_pPlayer->edict(), m_usEgonStop, 0, (float*)&m_pPlayer->pev->origin, (float*)&m_pPlayer->pev->angles, 0.0, 0.0,
//		bMakeNoise, 0, 0, m_pPlayer->pev->viewmodelbody, (float*)&g_vecZero, (float*)&g_vecZero, 0, 0.0f, (byte)0);
//
//	SendWeaponAnim((m_fireMode == FIRE_WIDE) ? EGON_FIDGET1 : EGON_ALTFIDGET1);
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
//	UnsetIdle();
//	m_fireState = FIRE_OFF;
//
//	DestroyEffect();
//}
//
//class CEgonAmmo : public CBasePlayerAmmo
//{
//public:
//	CEgonAmmo(void)
//	{
//		m_szModel = MAKE_STRING("models/ammo_uranium.mdl");
//		m_szAmmoType = MAKE_STRING("uranium");
//		m_szPickupSound = MAKE_STRING("weapons/egon/ammo.wav");
//		m_iAmmoAmount = AMMO_URANIUMBOX_GIVE;
//	}
//};
//LINK_ENTITY_TO_CLASS(ammo_uranium, CEgonAmmo);
//
//#endif
//
//// Little Badis: Nose Upgrade for the Egon
//class CEgonNose : public CEgon
//{
//	void Spawn(void)
//	{
//		CEgon::Spawn();
//		pev->body = 1;
//		m_fWeaponUpgrades |= (1 << UPGRADE_EGONP);
//	}
//};
//LINK_ENTITY_TO_CLASS(weapon_egonnose, CEgonNose);
//
//// Little Badis: Controls Upgrade for the Egon
//class CEgonControls : public CEgon
//{
//	void Spawn(void)
//	{
//		CEgon::Spawn();
//		pev->body = 2;
//		m_fWeaponUpgrades |= (1 << UPGRADE_EGONE);
//	}
//};
//LINK_ENTITY_TO_CLASS(weapon_egoncontrols, CEgonControls);
//
//// Little Badis: Full Upgrades for the Egon
//class CEgonFull : public CEgon
//{
//	void Spawn(void)
//	{
//		CEgon::Spawn();
//		pev->body = 3;
//		m_fWeaponUpgrades |= (1 << UPGRADE_EGONP) | (1 << UPGRADE_EGONE);
//	}
//};
//LINK_ENTITY_TO_CLASS(weapon_egonfull, CEgonFull);
