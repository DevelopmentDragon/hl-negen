//=============================================================//
//	Half-Life Update MOD
//	https://github.com/Fograin/hl-subsmod-ex
//	
//	This product contains software technology licensed from:
//	Valve LLC.
//	Id Software, Inc. ("Id Technology")
//
//	Before using any parts of this code, read licence.txt file 
//=============================================================//

/*
#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "hornet.h"
#include "gamerules.h"
#include "agrunt.h"

//=========================================================
// Assault Rocket Definition, server side only
//=========================================================

#ifndef CLIENT_DLL

LINK_ENTITY_TO_CLASS(phero_missile, CPheromone);

CPheromone* CPheromone::CreatePheromone(void)
{
	CPheromone* pPheromone = GetClassPtr((CPheromone*)NULL);
	pPheromone->pev->classname = MAKE_STRING("phero_missile");
	pPheromone->Spawn();

	return pPheromone;
}

void CPheromone::Spawn(void)
{
	Precache();
	pev->movetype = MOVETYPE_FLY;
	pev->solid = SOLID_BBOX;

	pev->gravity = 0.5;
	SET_MODEL(ENT(pev), "models/proj_phero.mdl");

	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0)); // Vector(-2.6, -3.46, -2.51), Vector(20.8338, 3.17, 4.12)

	SetTouch(&CPheromone::ExplodeThink);
	SetThink(&CPheromone::BubbleThink);
	pev->nextthink = gpGlobals->time + 0.2;
}


void CPheromone::Precache(void)
{
	PRECACHE_MODEL("models/proj_phero.mdl");
	PRECACHE_SOUND("weapons/hivehand/pfire.wav");
	PRECACHE_SOUND("weapons/hivehand/phit.wav");
	m_iImpactIndex = PRECACHE_MODEL("sprites/bm2.spr");
}

int	CPheromone::Classify(void)
{
	return	CLASS_NONE;
}

void CPheromone::BubbleThink(void)
{
	pev->nextthink = gpGlobals->time + 0.1;

	if (pev->waterlevel > 0)
	{
		UTIL_Remove(this);
		return;
	}

}

void CPheromone::ExplodeThink(CBaseEntity* pOther)
{
	int iContents = UTIL_PointContents(pev->origin);
	int iScale = 10;
	pev->dmg = 50;

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
	WRITE_BYTE(TE_EXPLOSION);
	WRITE_COORD(pev->origin.x);
	WRITE_COORD(pev->origin.y);
	WRITE_COORD(pev->origin.z);
	WRITE_SHORT(m_iImpactIndex);
	WRITE_BYTE(iScale); // scale * 10
	WRITE_BYTE(15); // framerate
	WRITE_BYTE(TE_EXPLFLAG_NOSOUND);
	MESSAGE_END();

	EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/hivehand/phit.wav", VOL_NORM, 0.3f);

	entvars_t* pevOwner = NULL;
	CBaseEntity* pTracker = NULL;

	if (pev->owner)
	{
		pevOwner = VARS(pev->owner);
		pTracker = CBaseEntity::Instance(pevOwner);

	}
	else
	{
		pevOwner = NULL;
	}

	if (pTracker)
	{
		if (pTracker->IsAlive())
		{
			if (FClassnameIs(pTracker->pev, "monster_alien_grunt"))
			{
				CAGrunt* pAGrunt = (CAGrunt*)pTracker;
				if (pOther)
				{
					if (pOther->IsAlive())
					{
						pAGrunt->m_hHeatSeek = pOther;
					}
				}
			}
		}
	}

	pev->owner = NULL; // can't traceline attack owner if this is set

	TraceResult tr = UTIL_GetGlobalTrace();

	pOther->TraceAttack(pevOwner, pev->dmg, pev->velocity.Normalize(), &tr, DMG_GENERIC, ID_DMG_GENERIC);

	UTIL_Remove(this);
}

#endif

/*
//=========================================================
// Hivehand or Hornet Gun
//=========================================================

enum firemode_e
{
	FIREMODE_TRACK = 0,
	FIREMODE_FAST
};

LINK_ENTITY_TO_CLASS(weapon_hornetgun, CHgun);

int CHgun::HUDIcon(void)
{
	return 117;
}

int CHgun::HUDActiveIcon(void)
{
	return 118;
}

int CHgun::ModeIcon(void)
{
	return -1;
}

int CHgun::ModeIcon2(void)
{
	return -1;
}

int CHgun::ModeIcon3(void)
{
	return -1;
}

int CHgun::SmallIcon(void)
{
	return 66;
}

BOOL CHgun::IsUseable(void)
{
	return TRUE;
}



void CHgun::Spawn()
{
	Precache();
	m_iId = WEAPON_HORNETGUN;
	SET_MODEL(ENT(pev), "models/w_hgun.mdl");

	m_iDefaultAmmo = HIVEHAND_DEFAULT_GIVE;
	m_iFirePhase = 0;

	FallInit();// get ready to fall down.
}


void CHgun::Precache(void)
{
	PRECACHE_MODEL("models/v_hgun.mdl");
	PRECACHE_MODEL("models/w_hgun.mdl");
	PRECACHE_MODEL("models/p_hgun.mdl");

	PRECACHE_SOUND("weapons/hivehand/fire.wav");
	PRECACHE_SOUND("weapons/hivehand/reload.wav");

	m_usHornetFire = PRECACHE_EVENT(1, "events/firehornet.sc");

	UTIL_PrecacheOther("hornet");
}

int CHgun::AddToPlayer(CBasePlayer* pPlayer)
{
	if (CBasePlayerWeapon::AddToPlayer(pPlayer))
	{

#ifndef CLIENT_DLL
		if (g_pGameRules->IsMultiplayer())
		{
			// in multiplayer, all hivehands come full. 
			pPlayer->m_rgAmmo[PrimaryAmmoIndex()] = HORNET_MAX_CARRY;
		}
#endif

		MESSAGE_BEGIN(MSG_ONE, gmsgWeapPickup, NULL, pPlayer->pev);
		WRITE_BYTE(m_iId);
		MESSAGE_END();
		return TRUE;
	}
	return FALSE;
}

int CHgun::GetItemInfo(ItemInfo* p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "hornets";
	p->iMaxAmmo1 = HORNET_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = WEAPON_BUCKET_BIO;
	p->iPosition = WEAPON_HORNETGUN_SLOT;
	p->iId = m_iId = WEAPON_HORNETGUN;
	p->iFlags = ITEM_FLAG_NOAUTOSWITCHEMPTY | ITEM_FLAG_NOAUTORELOAD;
	p->iWeight = HORNETGUN_WEIGHT;

	return 1;
}


BOOL CHgun::Deploy()
{
	return DefaultDeploy("models/v_hgun.mdl", "models/p_hgun.mdl", HGUN_UP, "hive");
}

void CHgun::Holster(int skiplocal )
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 1.1;
	SendWeaponAnim(HGUN_DOWN);

	//!!!HACKHACK - can't select hornetgun if it's empty! no way to get ammo for it, either.
	if (!m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()])
	{
		m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()] = 1;
	}
}


void CHgun::PrimaryAttack()
{
	Reload();

	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 && m_pPlayer->m_flInfiniteAmmo < 1)
	{
		return;
	}

#ifndef CLIENT_DLL
	UTIL_MakeVectors(m_pPlayer->pev->v_angle);

	CHornet* pHornet = CHornet::Create(0, m_pPlayer->GetGunPosition() + gpGlobals->v_forward * 16 + gpGlobals->v_right * 8 + gpGlobals->v_up * -12, m_pPlayer->pev->v_angle, m_pPlayer->edict());
	//CBaseEntity::Create( "hornet", m_pPlayer->GetGunPosition( ) + gpGlobals->v_forward * 16 + gpGlobals->v_right * 8 + gpGlobals->v_up * -12, m_pPlayer->pev->v_angle, m_pPlayer->edict() );
	pHornet->pev->velocity = gpGlobals->v_forward * 300;

	m_flRechargeTime = gpGlobals->time + 0.5;
#endif

	if (m_pPlayer->m_flInfiniteAmmo < 1)
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;


	m_pPlayer->m_iWeaponVolume = QUIET_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	int flags;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif
	int iAnim = m_pPlayer->pev->savedvanim = HGUN_SHOOT;
	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usHornetFire, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0,
		FIREMODE_TRACK, 0, 0, 0, (float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);

	// Fograin92: Server side sound
	EMIT_SOUND(ENT(pev), CHAN_WEAPON, "hivehand/fire.wav", 0.80, ATTN_NORM);

	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	m_flNextPrimaryAttack = m_flNextPrimaryAttack + 0.25;

	if (m_flNextPrimaryAttack < UTIL_WeaponTimeBase())
	{
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.25;
	}

	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);
}



void CHgun::SecondaryAttack(void)
{
	Reload();

	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 && m_pPlayer->m_flInfiniteAmmo < 1)
	{
		return;
	}

	//Wouldn't be a bad idea to completely predict these, since they fly so fast...
#ifndef CLIENT_DLL
	CHornet* pHornet;
	Vector vecSrc;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle);

	vecSrc = m_pPlayer->GetGunPosition() + gpGlobals->v_forward * 16 + gpGlobals->v_right * 8 + gpGlobals->v_up * -12;

	m_iFirePhase++;
	switch (m_iFirePhase)
	{
	case 1:
		vecSrc = vecSrc + gpGlobals->v_up * 8;
		break;
	case 2:
		vecSrc = vecSrc + gpGlobals->v_up * 8;
		vecSrc = vecSrc + gpGlobals->v_right * 8;
		break;
	case 3:
		vecSrc = vecSrc + gpGlobals->v_right * 8;
		break;
	case 4:
		vecSrc = vecSrc + gpGlobals->v_up * -8;
		vecSrc = vecSrc + gpGlobals->v_right * 8;
		break;
	case 5:
		vecSrc = vecSrc + gpGlobals->v_up * -8;
		break;
	case 6:
		vecSrc = vecSrc + gpGlobals->v_up * -8;
		vecSrc = vecSrc + gpGlobals->v_right * -8;
		break;
	case 7:
		vecSrc = vecSrc + gpGlobals->v_right * -8;
		break;
	case 8:
		vecSrc = vecSrc + gpGlobals->v_up * 8;
		vecSrc = vecSrc + gpGlobals->v_right * -8;
		m_iFirePhase = 0;
		break;
	}

	pHornet = CHornet::Create(0, vecSrc, m_pPlayer->pev->v_angle, m_pPlayer->edict());
	//CBaseEntity::Create( "hornet", vecSrc, m_pPlayer->pev->v_angle, m_pPlayer->edict() );
	pHornet->pev->velocity = gpGlobals->v_forward * 1200;
	pHornet->pev->angles = UTIL_VecToAngles(pHornet->pev->velocity);

	pHornet->SetThink(&CHornet::StartDart);

	m_flRechargeTime = gpGlobals->time + 0.5;
#endif

	int flags;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	int iAnim = m_pPlayer->pev->savedvanim = HGUN_SHOOT;
	float flFramerate = m_pPlayer->pev->savedvframerate = 1.0f;
	byte byFrame = m_pPlayer->pev->savedvframe = (byte)0;

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usHornetFire, 0.0, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0,
		FIREMODE_FAST, 0, 0, 0, (float*)&g_vecZero, (float*)&g_vecZero, iAnim, flFramerate, byFrame);

	// Fograin92: Server side sound
	EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/hivehand/fire.wav", 0.80, ATTN_NORM);

	if (m_pPlayer->m_flInfiniteAmmo < 1)
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;
	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);
}


void CHgun::Reload(void)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] >= HORNET_MAX_CARRY)
		return;

	while (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] < HORNET_MAX_CARRY && m_flRechargeTime < gpGlobals->time)
	{
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]++;
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/hivehand/reload.wav", 0.80, ATTN_NORM);
		m_flRechargeTime += 0.25; // Little Badis: Was 0.5
	}
}


void CHgun::WeaponIdle(void)
{
	Reload();

	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase())
		return;

	int iAnim;
	float flRand = UTIL_SharedRandomFloat(m_pPlayer->random_seed, 0, 1);
	if (flRand <= 0.75)
	{
		iAnim = HGUN_IDLE1;
		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 30.0 / 16 * (2);
	}
	else if (flRand <= 0.875)
	{
		iAnim = HGUN_FIDGETSWAY;
		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 40.0 / 16.0;
	}
	else
	{
		iAnim = HGUN_FIDGETSHAKE;
		m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 35.0 / 16.0;
	}
	SendWeaponAnim(iAnim);
}
*/