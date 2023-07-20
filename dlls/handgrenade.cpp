////=============================================================//
////	Half-Life: Negentropy
////	
////	This product contains software technology licensed from:
////	Valve LLC.
////	Id Software, Inc. ("Id Technology")
////
////	Before using any parts of this code, read licence.txt file 
////=============================================================//
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
//#define	HANDGRENADE_PRIMARY_VOLUME		450
//
//LINK_ENTITY_TO_CLASS(weapon_handgrenade, CHandGrenade);
//
////=========================================================
////=========================================================
//
//int CHandGrenade::PrimaryAmmoIndex(void)
//{
//	return m_iPrimaryAmmoType;
//}
//
//void CHandGrenade::Spawn(void)
//{
//	Precache();
//	m_iId = WEAPON_HANDGRENADE;
//	SET_MODEL(ENT(pev), "models/w_handgrenade.mdl");
//
//	pev->classname = MAKE_STRING("weapon_handgrenade");
//#ifndef CLIENT_DLL
//	pev->dmg = gSkillData.plrDmgFragmentationBlast;
//#endif
//	// Init all data
//	ClearGrenade();
//	m_iDefaultAmmo = HANDGRENADE_DEFAULT_GIVE;
//	FallInit();// get ready to fall down.
//}
//
//void CHandGrenade::Precache(void)
//{
//	PRECACHE_MODEL("models/w_handgrenade.mdl");
//	PRECACHE_MODEL("models/v_handgrenade.mdl");
//	PRECACHE_MODEL("models/p_handgrenade.mdl");
//	PRECACHE_SOUND("weapons/handgrenade/pulse.wav");
//	PRECACHE_SOUND("weapons/handgrenade/hit1.wav");
//	PRECACHE_SOUND("weapons/handgrenade/hit2.wav");
//	PRECACHE_SOUND("weapons/handgrenade/hit3.wav");
//	PRECACHE_SOUND("weapons/handgrenade/tlight.wav");
//	PRECACHE_SOUND("weapons/handgrenade/tmed.wav");
//	PRECACHE_SOUND("weapons/handgrenade/thard.wav");
//	PRECACHE_SOUND("weapons/handgrenade/frag_exp.wav");
//	PRECACHE_SOUND("weapons/handgrenade/spoon.wav");
//	PRECACHE_SOUND("weapons/handgrenade/swap.wav");
//	PRECACHE_SOUND("items/he.wav");
//}
//
//int CHandGrenade::GetItemInfo(ItemInfo* p)
//{
//	p->pszName = STRING(pev->classname);
//	p->pszAmmo1 = "handgrenade";
//	p->iMaxAmmo1 = HANDGRENADE_MAX_CARRY;
//	p->pszAmmo2 = NULL;
//	p->iMaxAmmo2 = -1;
//	p->iMaxClip = 0; // Allowing reloading without displaying two digits
//	p->iSlot = WEAPON_BUCKET_GRENADES;
//	p->iPosition = WEAPON_HANDGRENADE_SLOT;
//	p->iId = m_iId = WEAPON_HANDGRENADE;
//	p->iWeight = HANDGRENADE_WEIGHT;
//	p->iFlags = ITEM_FLAG_DUPLICATION;
//
//	return 1;
//}
//
//BOOL CHandGrenade::ShouldDisplayThrowForce(void)
//{
//	return m_fArmed;
//}
//
//int CHandGrenade::GetThrowForce(void)
//{
//	return m_iForce;
//}
//
//int CHandGrenade::GetMaxThrowForce(void)
//{
//	return 100;
//}
//
//void CHandGrenade::ItemPostFrame(void)
//{
//	UpdateBodygroup();
//	TickGrenade();
//	CBasePlayerWeapon::ItemPostFrame();
//}
//
//int CHandGrenade::HUDIcon(void)
//{
//	return 95;
//}
//
//int CHandGrenade::HUDActiveIcon(void)
//{
//	return 96;
//}
//
//int CHandGrenade::ModeIcon(void)
//{
//	if (m_fTimed)
//		return 67;
//	else
//		return 68;
//}
//
//int CHandGrenade::ModeIcon2(void)
//{
//	return -1;
//}
//
//int CHandGrenade::ModeIcon3(void)
//{
//	return -1;
//}
//
//int CHandGrenade::SmallIcon(void)
//{
//	return 55;
//}
//
//BOOL CHandGrenade::HasAmmo(void)
//{
//	return HasPrimaryAmmo();
//}
//
//void CHandGrenade::UpdateBodygroup(void)
//{
//	// Viewmodel
//	if (m_pPlayer)
//	{
//		m_pPlayer->pev->viewmodelbody = m_pPlayer->pev->viewmodelbody = m_pPlayer->pev->armortype;
//
//		if (HasAmmo() == FALSE)
//		{
//			if (m_flNextPrimaryAttack <= UTIL_WeaponTimeBase() || m_flNextSecondaryAttack <= UTIL_WeaponTimeBase() || m_flNextTertiaryAttack <= UTIL_WeaponTimeBase())
//			{
//				m_pPlayer->pev->playmodelbody = 1;
//				pev->body = 1;
//			}
//		}
//		else
//		{
//			m_pPlayer->pev->playmodelbody = 0;
//			pev->body = 0;
//		}
//	}
//
//}
//
//void CHandGrenade::PullPin(BOOL m_fTimedGrenade)
//{
//	m_fArmed = TRUE; // You arm it, get ready to throw
//	m_fPrimed = TRUE; // Since you pressed button keep it that way
//	//m_fTimed = m_fTimedGrenade; // Depends on where it's called
//	m_flThrowTime = UTIL_WeaponTimeBase() + (25.0 / 45.0); // When can you throw this
//	m_flPulseTime = gpGlobals->time + (16.0 / 45.0); // Pulse time
//	m_flTime = UTIL_WeaponTimeBase() + 3.0 + (16.0 / 45.0); // Add three seconds to pulse time
//	m_flSpoonSound = 0.35;
//}
//
//void CHandGrenade::ClearGrenade(void)
//{
//	// Clear all values to prevent abnormal behavior, call when throwing grenade or changing weapons
//	m_fArmed = FALSE;
//	m_fPrimed = FALSE;
//	m_flPulseTime = -1;
//	m_flTime = -1;
//	m_flThrowTime = -1;
//	m_iForce = 0;
//	m_bSpoonSound = FALSE;
//	m_flSpoonSound = -1;
//	if (m_bMidSpoon)
//	{
//		m_bMidSpoon = FALSE;
//		m_fTimed = FALSE;
//	}
//}
//
//void CHandGrenade::ThrowGrenade(void)
//{
//	// Calcuate angle and velocity
//	Vector angThrow = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
//
//	/*
//	if ( angThrow.x < 0 )
//		angThrow.x = -10 + angThrow.x * ( ( 90 - 10 ) / 90.0 );
//	else
//		angThrow.x = -10 + angThrow.x * ( ( 90 + 10 ) / 90.0 );
//
//	float flVel = ( 90 - angThrow.x ) * m_iForce * (m_iForce / 100); //4;
//	*/
//
//	float flVel = 1000 * ((float)m_iForce / 100); // originally 800
//
//	UTIL_MakeVectors(angThrow);
//	Vector vecSrc = m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_forward * 16;
//	Vector vecThrow = gpGlobals->v_forward * flVel + m_pPlayer->pev->velocity;
//
//	if (m_flTime < 0)
//		m_flTime = 0;
//
//	// Throwing animations depending on force
//	if (m_iForce < 40)
//	{
//		SendWeaponAnim(HANDGRENADE_THROW_SOFT);
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/handgrenade/tlight.wav", VOL_NORM, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//		m_flRedraw = 0.45;
//	}
//	else if (m_iForce < 70)
//	{
//		SendWeaponAnim(HANDGRENADE_THROW_NORMAL);
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/handgrenade/tmed.wav", VOL_NORM, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//		m_flRedraw = 0.58;
//	}
//	else
//	{
//		SendWeaponAnim(HANDGRENADE_THROW_HARD);
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON2, "weapons/handgrenade/thard.wav", VOL_NORM, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//		m_flRedraw = 0.26;
//	}
//
//	// Throw Grenade	
//	if (HasInfinitePrimaryAmmo())
//		--m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()];
//
//	if (!m_fTimed)
//		EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON3, "weapons/handgrenade/spoon.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//
//	CGrenade::ShootTimed(m_pPlayer->pev, vecSrc, vecThrow, m_flTime - UTIL_WeaponTimeBase());
//
//	// player "shoot" animation
//	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + m_flRedraw + 0.53;
//}
//
//void CHandGrenade::TickGrenade(void)
//{
//	if (m_flNextReload > UTIL_WeaponTimeBase())
//		m_flNextReload -= gpGlobals->frametime;
//
//	if (m_flRedraw > 0)
//	{
//		//ALERT( at_console, "m_flRedraw = %.2f\n", m_flRedraw );
//		m_flRedraw -= gpGlobals->frametime;
//		if (m_flRedraw <= 0)
//		{
//			m_flRedraw = -1;
//			if (HasAmmo() == TRUE)
//			{
//				SendWeaponAnim(HANDGRENADE_DRAW);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 0.75;
//			}
//			else
//			{
//				m_flRedraw = 0.1;
//				SendWeaponAnim(HANDGRENADE_NULL);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.00;
//			}
//		}
//	}
//
//	// If grenade is not armed, do not call anything
//	if (m_fArmed == FALSE)
//		return;
//
//	if (m_flSpoonSound > 0.0f)
//	{
//		m_flSpoonSound -= gpGlobals->frametime;
//	}
//
//	if (m_fTimed && m_bSpoonSound == FALSE)
//	{
//		if (m_flSpoonSound < 0.0f)
//		{
//			EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON3, "weapons/handgrenade/spoon.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//			m_bSpoonSound = TRUE;
//		}
//	}
//
//	if ((m_pPlayer->pev->button & IN_RELOAD) == IN_RELOAD && !m_fTimed && m_bSpoonSound == FALSE)
//	{
//		if (m_flSpoonSound < 0.0f)
//		{
//			m_fTimed = TRUE;
//			EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON3, "weapons/handgrenade/spoon.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//			m_bSpoonSound = TRUE;
//			m_bMidSpoon = TRUE;
//		}
//	}
//
//
//	if ((m_pPlayer->pev->button & (IN_ATTACK | IN_ATTACK2)) == (IN_ATTACK | IN_ATTACK2))
//	{
//		if (m_iForce != 50)
//		{
//			if (m_iForce > 50)
//			{
//				m_iForce -= 2;
//			}
//			else if (m_iForce < 50)
//			{
//				m_iForce += 2;
//			}
//
//		}
//	}
//	else if ((m_pPlayer->pev->button & IN_ATTACK) == IN_ATTACK)
//	{
//		if (m_iForce < 100)
//			m_iForce += 2;
//	}
//	else if ((m_pPlayer->pev->button & IN_ATTACK2) == IN_ATTACK2)
//	{
//		if (m_iForce > 0)
//			m_iForce -= 2;
//	}
//
//	// ALERT( at_console, "Force: %d\n", m_iForce );
//
//	// Not the time to throw or count yet, but decrement time to actually throw grenade (for the animation)
//	if (m_flThrowTime > 0)
//	{
//		m_flThrowTime -= gpGlobals->frametime;
//		m_flNextReload = UTIL_WeaponTimeBase() + 1.0;
//	}
//
//	if (m_flTime <= 0 && m_fTimed == TRUE && m_fPrimed == TRUE)
//	{
//		// Time's up, toss grenade with zero seconds left
//		ThrowGrenade();
//		ClearGrenade();
//		return;
//	}
//
//	// Not holding a fire button anymore, toss grenade with remaining time if timed, otherwise, default throwing stuff
//	if (m_fPrimed == FALSE && m_flThrowTime <= 0)
//	{
//		ThrowGrenade();
//		ClearGrenade();
//		if (HasAmmo() == FALSE)
//			m_flNextReload = UTIL_WeaponTimeBase() + 0.2;
//		else
//			m_flNextReload = UTIL_WeaponTimeBase() + 1.0;
//		return;
//	}
//
//	// If timed, count down and play the pulsing sound
//	if (m_fTimed == TRUE)
//	{
//		if (gpGlobals->time > m_flPulseTime)
//		{
//			EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/handgrenade/pulse.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//			m_flPulseTime = gpGlobals->time + 1.0;
//		}
//
//		if (m_flTime > 0)
//			m_flTime -= gpGlobals->frametime;
//
//		return;
//	}
//}
//
//void CHandGrenade::PickupSound(int mode)
//{
//	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "items/he.wav", 1, ATTN_NORM);
//}
//
//BOOL CHandGrenade::IsUseable(void)
//{
//	if (m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()] > 0 || m_pPlayer->m_flInfiniteAmmo > 0)
//		return TRUE;
//	return TRUE;
//}
//
//BOOL CHandGrenade::Deploy(void)
//{
//	UpdateBodygroup();
//	ClearGrenade();
//	m_flNextReload = UTIL_WeaponTimeBase() + 0.5;
//
//	int result;
//	//SET_MODEL(ENT(pev), "models/w_handgrenade.mdl");
//	result = DefaultDeploy("models/v_handgrenade.mdl", "models/p_handgrenade.mdl", (HasAmmo() == TRUE) ? HANDGRENADE_DRAW : HANDGRENADE_NULL, "crowbar");
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.53;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//	UnsetIdle();
//	m_flRedraw = -1;
//	return result;
//}
//
//BOOL CHandGrenade::CanHolster(void)
//{
//	if (m_fPrimed == TRUE || m_fReloading == TRUE)
//		return FALSE;
//
//	return TRUE;
//}
//
//void CHandGrenade::Holster(int skiplocal /* = 0 */)
//{
//	UpdateBodygroup();
//
//	if (!CanHolster()) {
//		return;
//	}
//
//	ClearGrenade();
//
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 1.0;
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//
//	if (HasAmmo() == TRUE)
//		SendWeaponAnim(HANDGRENADE_HOLSTER);
//	else
//		SendWeaponAnim(HANDGRENADE_NULL);
//
//	UnsetIdle();
//	m_flRedraw = -1;
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//}
//
//void CHandGrenade::PrimaryAttack(void)
//{
//	UpdateBodygroup();
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//
//	if (m_fArmed == TRUE)
//		return;
//
//	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase())
//		return;
//
//	if (HasAmmo() == TRUE)
//	{
//		m_iForce = 2;
//		PullPin(m_fTimed);
//		SendWeaponAnim(HANDGRENADE_PINPULL);
//		UnsetIdle();
//	}
//	else
//	{
//		return;
//	}
//
//}
//
//void CHandGrenade::SecondaryAttack(void)
//{
//	UpdateBodygroup();
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//
//	if (m_fArmed == TRUE)
//		return;
//
//	if (m_flNextSecondaryAttack > UTIL_WeaponTimeBase())
//		return;
//
//	if (HasAmmo() == TRUE)
//	{
//		m_iForce = 2;
//		PullPin(m_fTimed);
//		SendWeaponAnim(HANDGRENADE_PINPULL);
//	}
//	else
//	{
//		return;
//	}
//}
//
//
//void CHandGrenade::TertiaryAttack(void)
//{
//	UpdateBodygroup();
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.0;
//
//	if (m_fArmed == TRUE)
//		return;
//
//	if (m_flNextTertiaryAttack > UTIL_WeaponTimeBase())
//		return;
//
//	if (HasAmmo() == TRUE)
//	{
//		m_iForce = 2;
//		PullPin(m_fTimed);
//		SendWeaponAnim(HANDGRENADE_PINPULL);
//	}
//	else
//	{
//		return;
//	}
//}
//
//BOOL CHandGrenade::CanReload(void)
//{
//	if (m_fArmed == TRUE && m_fTimed == FALSE || m_flNextReload > UTIL_WeaponTimeBase())
//		return FALSE;
//
//	return TRUE;
//}
//
//void CHandGrenade::Reload(void)
//{
//	if (CanReload() == FALSE)
//		return;
//
//	if (m_fTimed == TRUE)
//		m_fTimed = FALSE;
//	else
//		m_fTimed = TRUE;
//
//	EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON3, "weapons/handgrenade/swap.wav", 1, ATTN_NORM, 0, 95 + RANDOM_LONG(0, 0x1f));
//
//	m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
//	m_flNextReload = UTIL_WeaponTimeBase() + 1.0;
//	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + 0.25;
//
//}
//
//void CHandGrenade::WeaponIdle(void)
//{
//	if (m_fPrimed == TRUE)
//		m_fPrimed = FALSE;
//
//	if (m_flNextWeaponIdle > UTIL_WeaponTimeBase())
//		return;
//
//	// Idle section
//	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] == 0)
//	{
//		return;
//	}
//	else
//	{
//		// 5% chance of playing the special animations instead. Do not set idle as we still need to set it afterwards
//		if (RANDOM_LONG(0, 99) <= 5)
//		{
//			UpdateBodygroup();
//			SendWeaponAnim(HANDGRENADE_FIDGET);
//			UnsetIdle();
//			m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.03;
//		}
//		else
//		{
//			// Ensure at least two successful loops
//			if (!IsIdle())
//			{
//				UpdateBodygroup();
//				SendWeaponAnim(HANDGRENADE_IDLE);
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.03 * 2;
//				SetIdle();
//			}
//			else
//			{
//				// Only perform a single loop in this case
//				m_flNextWeaponIdle = UTIL_WeaponTimeBase() + 3.03;
//			}
//		}
//	}
//}
