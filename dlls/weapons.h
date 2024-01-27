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
#ifndef WEAPONS_H
#define WEAPONS_H

//#pragma once

#include "effects.h"
#include "schedule.h"
#include "weaponenum.h"
#include "player.h"

BOOL CanAttack(float attack_time, float curtime, BOOL isPredicted);

class CBasePlayer;
extern int gmsgWeapPickup;
extern int gmsgItemPickup;

extern int gEvilImpulse101;
extern int g_iAmmoCheat;

// Moved here because we want the base weapon class to inherit this
class CLaserSpot : public CBaseEntity
{
public:
	void Spawn(void);
	void Precache(void);
	int	ObjectCaps(void);

	void Suspend(float flSuspendTime);
	void EXPORT Revive(void);
	void SetPowerUp(void);
	void EXPORT PowerUp(void); // Think function for when powering up the spot
	void SetPowerDown(void);
	void EXPORT PowerDown(void); // Think function for when powering down the spot

	void SetPowerTime(float flTime); // Set up the time it takes to fully power up as well as the increment

	float m_flPowerTime;
	int m_iPowerIncrement;

	void Update(Vector vecSpotOrigin, Vector vecTrailOrigin); // Update origin
	// Trail for the laser, the dot is the ending
	int m_iTrail; // Index
	int m_szTrailModel; // Model string
	CBeam* m_pTrail;
	Vector m_vecTrailOrigin; // Origin of spot is different than pev->origin. In this case, 
	Vector m_vecTrailColor;

	// Color
	Vector m_vecColor; // Color of the spot, we use the same for both it and the trail, because it would be nonesense otherwise
	int m_iStartingVisibility; // Alpha of both the beam and dot, note, we use this to change the opacity of both the spot and the trail
	int m_iVisibilityMin; // Min visibility
	int m_iVisibilityMax; // Max visibility

	void SetMinVisibility(int iVisibility); // Set minimum visibility and modify power increment
	void SetMaxVisibility(int iVisibility); // Set maximum visibility and modify power increment
	void SetStartingVisibility(int iVisibility); // Set minimum visibility and modify power decrement

	int m_fSpotFlags;

	void Killed(entvars_t* pevAttacker, int iGib);
	static CLaserSpot* CreateSpot(edict_t* pOwner);
	CLaserSpot(void); // Creation of a CLaserSpot with default varriables
	~CLaserSpot(void); // Removal of CLaserSpot made to also get rid of the beam entity that follows
};

class CBaseProjectile : public CBaseMonster
{

};

//void DeactivateSatchels(CBasePlayer* pOwner);
//void DeactivateLauncherNades(CBasePlayer* pOwner);

// Contact Grenade / Timed grenade / Satchel Charge
class CGrenade : public CBaseMonster
{
public:
	void Spawn(void);

	typedef enum { SATCHEL_DETONATE = 0, SATCHEL_RELEASE } SATCHELCODE;

	typedef enum
	{
		TYPE_HANDGRENADE = 0,
		TYPE_MP5GRENADE,
		TYPE_SATCHEL,
		TYPE_TRIPMINE,
		TYPE_RPGROCKET,
		TYPE_HEGRENADE,
		TYPE_M4GRENADE,
		TYPE_RIFLEROCKET,
		TYPE_LAWROCKET,
		TYPE_LAUNCHERGRENADE,
	} GRENADETYPE;

	static CGrenade* ShootTimed(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time);
	static CGrenade* ShootHE(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time);
	static CGrenade* ShootContact(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity);
	static CGrenade* ShootSoftContact(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time);
	static CGrenade* ShootSatchelCharge(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity);
	static CGrenade* ShootLauncherGrenade(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time, BOOL remote);
	static CGrenade* ShootSmoke(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity);
	static CGrenade* ShootSoftSmoke(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time);
	static void StartSmoking(void);
	static void UseSatchelCharges(entvars_t* pevOwner, SATCHELCODE code);


	void Explode(Vector vecSrc, Vector vecAim);
	void Explode(TraceResult* pTrace, int bitsDamageType);
	void EXPORT Smoke(void);

	void EXPORT BounceTouch(CBaseEntity* pOther);
	void EXPORT SlideTouch(CBaseEntity* pOther);
	void EXPORT ExplodeTouch(CBaseEntity* pOther);
	void EXPORT QuakeTouch(CBaseEntity* pOther);
	void EXPORT PseudoQuakeTouch(CBaseEntity* pOther);
	void EXPORT DangerSoundThink(void);
	void EXPORT PreDetonate(void);
	void EXPORT Detonate(void);
	void EXPORT DetonateUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);
	void EXPORT TumbleThink(void);

	void Precache(void); // Needed for trail and other ressources

	// Smoke Grenade smoke emission
	void EXPORT SmokeGrenade(void);
	float m_flSmokeLife;
	int m_iTrail;

	virtual void BounceSound(void);
	virtual int	BloodColor(void) { return DONT_BLEED; }
	virtual void Killed(entvars_t* pevAttacker, int iGib);

	float SmokeScale(void);
	float ExplosionScale(void);
	float PullUpScale(void);
	int ExplosionSpriteIndex(void);
	int ScorchSprite(void);


	BOOL m_fRegisteredSound;// whether or not this grenade has issued its DANGER sound to the world sound list yet.

	int m_iGrenadeType;
	BOOL m_bRemote;

#ifndef CLIENT_DLL
	int		Save(CSave& save);
	int		Restore(CRestore& restore);
	static	TYPEDESCRIPTION m_SaveData[];
#endif
};

// Straight out of Deathmatch: Classic
class CQuakeRocket : public CBaseMonster
{
public:
	void Spawn(void);
	void Precache(void);

	//void Explode( void );
	void Explode(Vector vecSrc, Vector vecAim);
	void Explode(TraceResult* pTrace, int bitsDamageType);

	// Rocket funcs
	static CQuakeRocket* CreateRocket(Vector vecOrigin, Vector vecAngles, CBaseEntity* pOwner);
	void EXPORT RocketTouch(CBaseEntity* pOther);

	// Grenade funcs
	static CQuakeRocket* CreateGrenade(Vector vecOrigin, Vector vecAngles, CBaseEntity* pOwner, BOOL isLong);
	void EXPORT GrenadeTouch(CBaseEntity* pOther);
	void EXPORT GrenadeExplode(void);
	void EXPORT TumbleThink(void);
	void EXPORT PreDetonate(void);
	void EXPORT Detonate(void);

	int		m_iTrail;
	float	m_flAttackFinished;

	void EXPORT Smoke(void);

	//	virtual void BounceSound( void );
	virtual int	BloodColor(void) { return DONT_BLEED; }
	//	virtual void Killed( entvars_t *pevAttacker, int iGib );

	BOOL m_fRegisteredSound;// whether or not this grenade has issued its DANGER sound to the world sound list yet.
};

// constant items
/*
 * Little Badis: Special values for maxclip
 * -1: No clip at all, cannot reload
 *  0: No clip at all, but the reload key is used for another purpose
 */
#define WEAPON_NOCLIP			-1
#define WEAPON_NOCLIP_RELOAD	0

#define WEAPON_CLIP_INVALID		-2
#define WEAPON_CLIP_INFINITE	-1

#define WEAPON_MAX_NUM 128

// These weapon flags have been written to reduce the amount of boolean varriables used
/// All of these flags are handled by the m_fWeaponFlags varriable
#define WEAPON_STF_NONE					0
#define WEAPON_STF_IDLE					BIT64(0)
#define WEAPON_STF_IDLE_SPECIAL			BIT64(1)
#define WEAPON_STF_RELOAD_START			BIT64(2)
#define WEAPON_STF_RELOAD_MID			BIT64(3)
#define WEAPON_STF_RELOAD_END			BIT64(4)
#define WEAPON_STF_UNPUMPED				BIT64(5)
#define WEAPON_STF_SEMIFIRED			BIT64(6)
#define WEAPON_STF_BLOCK_START			BIT64(7)
#define WEAPON_STF_BLOCK_MID			BIT64(8)
#define WEAPON_STF_BLOCK_END			BIT64(9)
#define WEAPON_STF_TOOL_START			BIT64(10)
#define WEAPON_STF_TOOL_MID				BIT64(11)
#define WEAPON_STF_TOOL_END				BIT64(12)
#define WEAPON_STF_CHARGE_START			BIT64(13)
#define WEAPON_STF_CHARGE_MID			BIT64(14)
#define WEAPON_STF_CHARGE_END			BIT64(15)
#define WEAPON_STF_SWITCH_START			BIT64(16)
#define WEAPON_STF_SWITCH_MID			BIT64(17)
#define WEAPON_STF_SWITCH_END			BIT64(18)
#define WEAPON_STF_THROW_START			BIT64(19)
#define WEAPON_STF_THROW_MID			BIT64(20)
#define WEAPON_STF_THROW_END			BIT64(21)
#define WEAPON_STF_HOLSTERED			BIT64(22)
#define WEAPON_STF_CLIP_SECONDARY		BIT64(23)
#define WEAPON_STF_RELOAD_SECONDARY		BIT64(24)
#define WEAPON_STF_RELOAD_SHOTGUN		BIT64(25)
#define WEAPON_STF_LASER				BIT64(26)
#define WEAPON_STF_SAFETY_ON			BIT64(27)
#define WEAPON_STF_SWING_LOCK			BIT64(28)
#define WEAPON_STF_SWITCH_AMMO			BIT64(29)
#define WEAPON_STF_CUSTOM5				BIT64(30)
#define WEAPON_STF_CUSTOM6				BIT64(31)
#define WEAPON_STF_CUSTOM7				BIT64(32)
#define WEAPON_STF_CUSTOM8				BIT64(33)
#define WEAPON_STF_CUSTOM9				BIT64(34)
#define WEAPON_STF_CUSTOM10				BIT64(35)
#define WEAPON_STF_CUSTOM11				BIT64(36)
#define WEAPON_STF_CUSTOM12				BIT64(37)
#define WEAPON_STF_CUSTOM13				BIT64(38)
#define WEAPON_STF_CUSTOM14				BIT64(39)
#define WEAPON_STF_CUSTOM15				BIT64(40)
#define WEAPON_STF_CUSTOM16				BIT64(41)
#define WEAPON_STF_CUSTOM17				BIT64(42)
#define WEAPON_STF_CUSTOM18				BIT64(43)
#define WEAPON_STF_CUSTOM19				BIT64(44)
#define WEAPON_STF_CUSTOM20				BIT64(45)
#define WEAPON_STF_CUSTOM21				BIT64(46)
#define WEAPON_STF_CUSTOM22				BIT64(47)
#define WEAPON_STF_CUSTOM23				BIT64(48)
#define WEAPON_STF_CUSTOM24				BIT64(49)
#define WEAPON_STF_CUSTOM25				BIT64(50)
#define WEAPON_STF_CUSTOM26				BIT64(51)
#define WEAPON_STF_CUSTOM27				BIT64(52)
#define WEAPON_STF_CUSTOM28				BIT64(53)
#define WEAPON_STF_CUSTOM29				BIT64(54)
#define WEAPON_STF_CUSTOM30				BIT64(55)
#define WEAPON_STF_CUSTOM31				BIT64(56)
#define WEAPON_STF_CUSTOM32				BIT64(57)
#define WEAPON_STF_CUSTOM33				BIT64(58)
#define WEAPON_STF_CUSTOM34				BIT64(59)
#define WEAPON_STF_CUSTOM35				BIT64(60)
#define WEAPON_STF_CUSTOM36				BIT64(61)
#define WEAPON_STF_CUSTOM37				BIT64(62)
#define WEAPON_STF_CUSTOM38				BIT64(63)

// Permanent flags for weapons that should be changed once placed on the weapon in question
#define WEAPON_FLAG_NONE			0			
#define WEAPON_FLAG_SHOTGUN_RELOAD	BIT(0)
#define WEAPON_FLAG_REQUIRES_PUMP	BIT(1)
#define WEAPON_FLAG_CHAMBER_ROUND	BIT(2)
#define WEAPON_FLAG_DESYNCH_CHAMBER	BIT(3)	// This flag synchs decrementation of a clip's chambered rounds and the ones you can fire

// Enum for clean-up routines
// The CleanUp function is used to force weapons variables
// to certain values when performing certain actions as to
// avoid unwanted behavior when interrupting them
// Example: Holstering a grenade after the pin was pulled
enum weapon_cleanup_e 
{
	WEAPON_CLEAN_DRAW,
	WEAPON_CLEAN_HOLSTER,
	WEAPON_CLEAN_PRE_RELOAD,
	WEAPON_CLEAN_POST_RELOAD,
	WEAPON_CLEAN_PICKUP,
	WEAPON_CLEAN_DROP,
	WEAPON_CLEAN_INTERRUPT,
};

enum weaponId_e
{
	WEAPON_QUESTION = 0,
	WEAPON_SPANNER,
	WEAPON_KNIFE,
	WEAPON_CROWBAR,
	WEAPON_PIPEWRENCH,
	WEAPON_AXE,
	WEAPON_SWORD,

	WEAPON_GLOCK,
	WEAPON_M9,
	WEAPON_PYTHON,
	WEAPON_DEAGLE,
	WEAPON_FLAREGUN,

	WEAPON_SHOTGUN,
	WEAPON_AUTOSHOTGUN,
	WEAPON_COMBATSHOTGUN, // Not yet implemented
	WEAPON_HUNTINGSHOTGUN,
	WEAPON_SUPERSHOTGUN,

	WEAPON_MICROSMG,
	WEAPON_MP5,
	WEAPON_M4,
	WEAPON_AK47, // Not yet implemented
	WEAPON_NAILGUN,

	WEAPON_M249,
	WEAPON_CHAINGUN,
	WEAPON_M60,
	WEAPON_MINIGUN,
	WEAPON_SPIKEGUN,

	WEAPON_TRANQGUN,
	WEAPON_CROSSBOW,
	WEAPON_TORQUEBOW,
	WEAPON_M40A1,
	WEAPON_AUTOSNIPER,

	WEAPON_GLAUNCHER,
	WEAPON_RPG,
	WEAPON_LAW,
	WEAPON_ROCKETRIFLE,
	WEAPON_FLAMETHROWER,

	WEAPON_RAILGUN,
	WEAPON_GAUSS,
	WEAPON_EGON,
	WEAPON_PLASMARIFLE,
	WEAPON_DISPLACER,

	WEAPON_CHUBTOAD,
	WEAPON_SNARK,
	WEAPON_BARNACLE,
	WEAPON_ALIENCHAINSAW,
	WEAPON_ALIENSPRAYER,
	WEAPON_HORNETGUN,
	WEAPON_SHOCKROACH,
	WEAPON_SPORELAUNCHER,
	WEAPON_PENGUIN,

	WEAPON_HANDGRENADE,
	WEAPON_HEGRENADE,
	WEAPON_INCGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DYNAMITE,
	WEAPON_CONCGRENADE,
	WEAPON_GASGRENADE,
	WEAPON_FLASHBANG,
	WEAPON_FRREZEGRENADE,
	WEAPON_EMPGRENADE,

	WEAPON_TRIPMINE,
	WEAPON_SATCHEL,
	WEAPON_TIMEBOMB,
	WEAPON_PROXBOMB,
	WEAPON_LANDMINE,
	WEAPON_NAILMINE,
	WEAPON_MIRV,
	WEAPON_CALTROP,
	WEAPON_DETPACK,

	WEAPON_FLASHLIGHT,
	WEAPON_FLARE,
	WEAPON_EXTINGUISHER,
	WEAPON_MEDKIT,
	WEAPON_CHARGER,
	WEAPON_EMPTOOL,

	WEAPON_CURRENTMAX,
};

// BUCKET CATEGORIES
enum weaponBucket_e
{
	WEAPON_BUCKET_MELEE = 0,  // 1
	WEAPON_BUCKET_HANDGUNS, // 2
	WEAPON_BUCKET_SHOTGUNS, // 3
	WEAPON_BUCKET_AUTOMATIC, // 4
	WEAPON_BUCKET_HEAVY, // 5
	WEAPON_BUCKET_RANGED, // 6
	WEAPON_BUCKET_LAUNCHERS, // 7
	WEAPON_BUCKET_ENERGY, // 8
	WEAPON_BUCKET_BIO, // 9
	WEAPON_BUCKET_GRENADES, // 0
	WEAPON_BUCKET_TRAPS, // -
	WEAPON_BUCKET_MINES, // +
	WEAPON_BUCKET_UTILITY, // <-

	WEAPON_BUCKET_MAX
};

// SLOTS WHERE THE WEAPONS BELONG
enum meleeSlot_e
{
	WEAPON_QUESTION_SLOT = 0,
	WEAPON_SPANNER_SLOT,
	WEAPON_KNIFE_SLOT,
	WEAPON_CROWBAR_SLOT,
	WEAPON_PIPEWRENCH_SLOT,
	WEAPON_AXE_SLOT,
	WEAPON_SWORD_SLOT,
};

enum handgunsSlot_e
{
	WEAPON_GLOCK_SLOT = 0,
	WEAPON_M9_SLOT,
	WEAPON_PYTHON_SLOT,
	WEAPON_DEAGLE_SLOT,
	WEAPON_FLAREGUN_SLOT,
};

enum shotgunsSlot_e
{
	WEAPON_SHOTGUN_SLOT = 0,
	WEAPON_AUTOSHOTGUN_SLOT,
	WEAPON_COMBATSHOTGUN_SLOT, // Not yet implemented
	WEAPON_HUNTINGSHOTGUN_SLOT,
	WEAPON_SUPERSHOTGUN_SLOT,
};

enum automaticSlot_e
{
	WEAPON_MICROSMG_SLOT = 0,
	WEAPON_MP5_SLOT,
	WEAPON_M4_SLOT,
	WEAPON_AK47_SLOT, // Not yet implemented
	WEAPON_NAILGUN_SLOT,
};

enum heavySlot_e
{
	WEAPON_M249_SLOT = 0,
	WEAPON_CHAINGUN_SLOT,
	WEAPON_M60_SLOT,
	WEAPON_MINIGUN_SLOT,
	WEAPON_SPIKEGUN_SLOT,
};

enum rangedSlot_e
{
	WEAPON_TRANQGUN_SLOT = 0,
	WEAPON_CROSSBOW_SLOT,
	WEAPON_TORQUEBOW_SLOT,
	WEAPON_M40A1_SLOT,
	WEAPON_AUTOSNIPER_SLOT,
};

enum launchersSlot_e
{
	WEAPON_GLAUNCHER_SLOT = 0,
	WEAPON_RPG_SLOT,
	WEAPON_LAW_SLOT,
	WEAPON_ROCKETRIFLE_SLOT,
	WEAPON_FLAMETHROWER_SLOT,
};

enum energySlot_e
{
	WEAPON_RAILGUN_SLOT = 0,
	WEAPON_GAUSS_SLOT,
	WEAPON_EGON_SLOT,
	WEAPON_PLASMARIFLE_SLOT,
	WEAPON_DISPLACER_SLOT,
};

enum bioSlot_e
{
	WEAPON_CHUBTOAD_SLOT = 0,
	WEAPON_SNARK_SLOT,
	WEAPON_BARNACLE_SLOT,
	WEAPON_ALIENCHAINSAW_SLOT,
	WEAPON_ALIENSPRAYER_SLOT,
	WEAPON_HORNETGUN_SLOT,
	WEAPON_SHOCKROACH_SLOT,
	WEAPON_SPORELAUNCHER_SLOT,
	WEAPON_PENGUIN_SLOT,
};

enum grenadeSlot_e
{
	WEAPON_HANDGRENADE_SLOT = 0,
	WEAPON_HEGRENADE_SLOT,
	WEAPON_INCGRENADE_SLOT,
	WEAPON_MOLOTOV_SLOT,
	WEAPON_DYNAMITE_SLOT,
	WEAPON_CONCGRENADE_SLOT,
	WEAPON_GASGRENADE_SLOT,
	WEAPON_FLASHBANG_SLOT,
	WEAPON_FRREZEGRENADE_SLOT,
	WEAPON_EMPGRENADE_SLOT,
};

enum trapsSlot_e
{
	WEAPON_TRIPMINE_SLOT = 0,
	WEAPON_SATCHEL_SLOT,
	WEAPON_TIMEBOMB_SLOT,
	WEAPON_PROXBOMB_SLOT,
	WEAPON_LANDMINE_SLOT,
	WEAPON_NAILMINE_SLOT,
	WEAPON_MIRV_SLOT,
	WEAPON_CALTROP_SLOT,
	WEAPON_DETPACK_SLOT,
};

enum utlitySlot_e
{
	WEAPON_FLASHLIGHT_SLOT = 0,
	WEAPON_FLARE_SLOT,
	WEAPON_EXTINGUISHER_SLOT,
	WEAPON_MEDKIT_SLOT,
	WEAPON_CHARGER_SLOT,
	WEAPON_EMPTOOL_SLOT,
};

// Crowbar Defaults

#define CROWBAR_WEIGHT		2

// Glock Defaults
#define GLOCK_WEIGHT			10
#define GLOCK_MAX_CLIP			17
#define GLOCK_DEFAULT_GIVE		GLOCK_MAX_CLIP // Little Badis: Was >17
#define AMMO_GLOCKCLIP_GIVE		GLOCK_MAX_CLIP
#define	_9MM_MAX_CARRY			85	// Little Badis: Was 250
#define UPGRADE_GLOCKS			0 // Silencer Upgrade

// Colt Python Defaults
#define PYTHON_WEIGHT			25
#define PYTHON_DEFAULT_GIVE		6
#define PYTHON_MAX_CLIP			6
#define AMMO_357BOX_GIVE		PYTHON_MAX_CLIP
#define _357_MAX_CARRY			36
#define UPGRADE_PYTHONS			0 // Scope Upgrade

// MP5 Defaults

#define MP5_WEIGHT				15
#define MP5_MAX_CLIP			30
#define _9MMH_MAX_CARRY			300
#define MP5_GRENADE_CLIP		1
#define _40MM_MAX_CARRY			10

#define UPGRADE_MP5_SUPRESSOR	BIT(0)	// Increases accuracy, damage and quiets the weapon a bit
#define UPGRADE_MP5_CHASSIS		BIT(1)	// Increase grenade velocity and weapon damage
#define UPGRADE_MP5_BARREL		BIT(2)	// Reduces recoil by 50%
#define UPGRADE_MP5_SYSTEMS		BIT(3)	// Increases firing speed by 25%
#define UPGRADE_MP5_MAG			BIT(4) // Increase Magazine capacity

// Chaingun Defaults
#define _10G_MAX_CARRY			200
#define CHAINGUN_WEIGHT			35
#define CHAINGUN_MAX_CLIP		WEAPON_NOCLIP_RELOAD
#define CHAINGUN_DEFAULT_GIVE	200
#define AMMO_CHAINBOX_GIVE		200

// Crossbow Defaults
#define CROSSBOW_WEIGHT			10
#define CROSSBOW_MAX_CLIP		5
#define BOLT_MAX_CARRY			50
#define BOLTPOISON_MAX_CARRY	55
#define UPGRADE_CROSSBOW		0

// Shotgun Defaults
#define SHOTGUN_WEIGHT			15
#define SHOTGUN_MAX_CLIP		8
#define SHOTGUN_DEFAULT_GIVE	SHOTGUN_MAX_CLIP
#define AMMO_BUCKSHOT_GIVE		3
#define AMMO_BUCKSHOTBOX_GIVE	12
#define BUCKSHOT_MAX_CARRY		128

// RPG Defaults
#define RPG_MAX_CLIP			1
#define ROCKET_MAX_CARRY		5
#define RPG_WEIGHT				20
#define AMMO_RPGCLIP_GIVE		RPG_MAX_CLIP
#define RPG_DEFAULT_GIVE		1

// Gauss Defaults
#define GAUSS_WEIGHT			20
#define GAUSS_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define CELLS_MAX_CARRY			300
#define AMMO_GAUSSCLIP_GIVE		60
#define AMMO_GAUSS_GIVE			100
#define AMMO_CELLSBOX_GIVE		CELLS_MAX_CARRY
#define GAUSS_DEFAULT_GIVE		AMMO_GAUSS_GIVE

#define UPGRADE_GAUSS_CHASSIS	0 // Increased firepower
#define UPGRADE_GAUSS_SYSTEM	1 // Cell Efficency, No Overload, Increased charging speed
#define UPGRADE_GAUSS_HANDLE	2 // Increased Firing Speed, zero recoil on charge if gauss jumping disabled

// Egon Defaults
#define EGON_WEIGHT				20
#define EGON_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define EGON_DEFAULT_GIVE		200
#define AMMO_URANIUMBOX_GIVE	20
#define URANIUM_MAX_CARRY		200
#define URANIUMW_MAX_CARRY		100
#define UPGRADE_EGONP			0 // Power Upgrade
#define UPGRADE_EGONE			1 // Efficency Upgrade

// Hivehand Defaults
#define HORNET_MAX_CARRY		24	// Little Badis: Was 8
#define HORNETGUN_WEIGHT	10
#define HORNETGUN_MAX_CLIP		WEAPON_NOCLIP
#define HIVEHAND_DEFAULT_GIVE		24 // Little Badis: Was 8

// Handgrenade Defaults
#define HANDGRENADE_MAX_CARRY	5
#define HANDGRENADE_WEIGHT	5
#define HANDGRENADE_MAX_CLIP	WEAPON_NOCLIP
#define HANDGRENADE_DEFAULT_GIVE	1

// Tripmine Defaults
#define TRIPMINE_MAX_CARRY		5
#define TRIPMINE_WEIGHT		2
#define TRIPMINE_MAX_CLIP		WEAPON_NOCLIP_RELOAD
#define TRIPMINE_DEFAULT_GIVE		1

 // Satchel Defaults
#define SATCHEL_MAX_CARRY		5
#define SATCHEL_WEIGHT		2
#define SATCHEL_MAX_CLIP		WEAPON_NOCLIP_RELOAD
#define SATCHEL_DEFAULT_GIVE		1

// Snark Defaults
#define SNARK_MAX_CARRY			5	// Little Badis: Was 15
#define SUPERSNARK_MAX_CARRY	5
#define SNARK_WEIGHT			5
#define SNARK_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define SNARK_DEFAULT_GIVE		1
#define SNARK_NEST_DEFAULT_GIVE 5

// Medkit Defaults
#define AMMO_MEDICAL_GIVE		50
#define AMMO_VIRUS_GIVE			50
#define MEDICAL_MAX_CARRY		200
#define VIRUS_MAX_CARRY			200
#define MEDKIT_WEIGHT			2
#define UPGRADE_MEDKIT			0

// M4 Defaults
#define M4_WEIGHT				20
#define M4_MAX_CLIP				40
#define _556NATO_MAX_CARRY		360
#define SMOKEGRENADE_MAX_CARRY	10

// Autoshotgun Defaults
#define AUTOSHOTGUN_WEIGHT					20
#define AUTOSHOTGUN_MAX_CLIP				16
#define AUTOSHOTGUN_DEFAULT_GIVE			AUTOSHOTGUN_MAX_CLIP
#define UPGRADE_AUTOSHOTS					0	// Stock Upgrade

// M9 Defaults
#define M9_WEIGHT				17
#define M9_MAX_CLIP				12
#define M9_DEFAULT_GIVE			M9_MAX_CLIP
#define AMMO_M9CLIP_GIVE		M9_MAX_CLIP
#define _38_MAX_CARRY			144

// Rocket Rifle Defaults
#define ROCKETRIFLE_MAX_CLIP		4
#define ROCKETRIFLE_WEIGHT			25
#define RIFLEROCKET_MAX_CARRY		52


// Desert Eagle Defaults
#define DEAGLE_WEIGHT			20
#define DEAGLE_MAX_CLIP			8
#define AMMO_DEAGLECLIP_GIVE	DEAGLE_MAX_CLIP
#define _44SW_MAX_CARRY			32
#define DEAGLE_DEFAULT_GIVE		DEAGLE_MAX_CLIP

// M249 Defaults
#define M249_WEIGHT			50
#define M249_MAX_CLIP		100
#define M249_DEFAULT_GIVE	M249_MAX_CLIP
#define M249_AMMO			M249_MAX_CLIP
#define _556H_MAX_CARRY		(2 * M249_MAX_CLIP)

// Shockroach defaults
#define SHOCKBOLT_MAX_CARRY		10
#define SHOCKROACH_WEIGHT	50
#define SHOCKROACH_DEFAULT_GIVE		20

// Knife Default

#define KNIFE_WEIGHT			5
#define KNIFE_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define KNIFE_COMBAT			0
#define KNIFE_BAYONET			1

// M40A1 Defaults
#define M40A1_WEIGHT					40
#define	M40A1_MAX_CLIP					5
#define M40A1_DEFAULT_GIVE				M40A1_MAX_CLIP
#define AMMO_762_GIVE					M40A1_MAX_CLIP
#define _762_MAX_CARRY					30

// Pipewrench Defaults
#define PIPEWRENCH_WEIGHT		4
#define PIPEWRENCH_MAX_CLIP		WEAPON_NOCLIP_RELOAD

// Grenade Launcher Defaults
#define GLAUNCHER_WEIGHT			40
#define GLAUNCHER_MAX_CLIP			3
#define GLAUNCHER_DEFAULT_GIVE		GLAUNCHER_MAX_CLIP
#define AMMO_50MM_GIVE				GLAUNCHER_MAX_CLIP
#define _50MM_MAX_CARRY				27

// M60 Defauls
#define	M60_WEIGHT					100
#define M60_MAX_CLIP				150
#define M60_DEFAULT_GIVE			M60_MAX_CLIP
#define AMMO_762H_GIVE				M60_MAX_CLIP
#define _762H_MAX_CARRY				M60_MAX_CLIP

// Autosniper Defaults
#define AUTOSNIPER_MAX_CLIP_AUTO			25
#define AUTOSNIPER_MAX_CLIP_BOLT			1
#define AUTOSNIPER_WEIGHT					75
#define _308_MAX_CARRY						75
#define _338_MAX_CARRY						25

// Spanner Defaults
#define SPANNER_WEIGHT				6
#define SPANNER_MAX_CLIP			WEAPON_NOCLIP_RELOAD

// Displacer Defaults
#define DISPLACER_WEIGHT			30
#define DISPLACER_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define HYDROGEN_MAX_CARRY			500
#define HYDROGEN_DEFAULT_AMMO		100

// High-Explosive Grenade
#define HEGRENADE_MAX_CARRY			10
#define HEGRENADE_WEIGHT			6
#define HEGRENADE_DEFAULT_AMMO		1

// AK-47
#define AK47_MAX_CLIP				30
#define AK47_WEIGHT					25
#define	HER_MAX_CARRY				10
#define _762R_MAX_CARRY				120

// Supershotgun
#define SUPERSHOTGUN_WEIGHT			25
#define SUPERSHOTGUN_MAX_CLIP		2
#define _20G_MAX_CARRY				58
#define _20G_AMMO_BOX				12

// Hunting Shotgun
#define HUNTINGSHOTGUN_WEIGHT		26
#define HUNTINGSHOTGUN_MAX_CLIP		5
#define _25G_MAX_CARRY				60
#define _25G_AMMO_GIVE				5

// Flaregun
#define FLAREGUN_WEIGHT				7
#define FLAREGUN_MAX_CLIP			5
#define MINIFLARE_MAX_CARRY			45

// Nailgun
#define NAILGUN_WEIGHT				12
#define NAILGUN_MAX_CLIP			32
#define SUPERNAILGUN_MAX_CLIP		64
#define NAILS_MAX_CARRY				256
#define UPGRADE_SUPERNAILGUN		0

// Railgun
#define RAILGUN_WEIGHT				25
#define RAILGUN_MAX_CLIP			20
#define MFCELLS_MAX_CARRY			100

// Tranquilizer Gun
#define TRANQGUN_WEIGHT				10
#define TRANQGUN_MAX_CLIP			1
#define TRANQ_DART_MAX_CARRY		40
#define POISON_DART_MAX_CARRY		40

// Minigun
#define MINIGUN_WEIGHT				50
#define MINIGUN_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define _12MM_MAX_CARRY				250
#define SPIKE_MAX_CARRY				150
#define AMMO_SPIKE_DEFAULT			50
#define AMMO_12MM_DEFAULT			100

// Flamethrower
#define FLAMETHROWER_WEIGHT			55
#define FLAMETHROWER_MAX_CLIP		WEAPON_NOCLIP_RELOAD
#define FUEL_MAX_CARRY				200
#define HELL_MAX_CARRY				20

// LAW Rocket
#define LAWS_WEIGHT					35
#define LAWS_MAX_CLIP				1
#define _66MM_MAX_CARRY				5

// Torque Bow
#define TORQUEBOW_WEIGHT			24
#define TORQUEBOW_MAX_CLIP			1
#define ARROW_MAX_CARRY				12
#define ARROWEXP_MAX_CARRY			12

// Chumtoad
#define CHUBTOAD_WEIGHT				8
#define CHUBTOAD_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define CHUB_MAX_CARRY				5

// Penguin
#define PENGUIN_WEIGHT				666
#define PENGUIN_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define PENGUIN_MAX_CARRY			3

// Charger
#define CHARGER_WEIGHT				12
#define CHARGER_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define CHARGEJUICE_MAX_CARRY		100

// Flare
#define FLARE_WEIGHT	7
#define FLARE_MAX_CLIP	WEAPON_NOCLIP_RELOAD
#define FLARE_MAX_CARRY	5

// Incendiary Grenade
#define INCGRENADE_WEIGHT		30
#define INCGRENADE_MAX_CLIP		WEAPON_NOCLIP_RELOAD
#define INCGRENADE_MAX_CARRY	5

// Molotov Cocktail
#define MOLTOVO_WEIGHT		29
#define MOLOTOV_MAX_CLIP	WEAPON_NOCLIP_RELOAD
#define MOLOTOV_MAX_CARRY	5

// Dynamite
#define DYNAMITE_WEIGHT		25
#define DYNMAITE_MAX_CLIP	WEAPON_NOCLIP_RELOAD
#define DYNAMITE_MAX_CARRY	60

// Concussion Grenade
#define CONCGRENADE_WEIGHT		30
#define CONCGRENADE_MAX_CLIP	WEAPON_NOCLIP_RELOAD
#define CONCGRENADE_MAX_CARRY	5

// Gas Grenade
#define GASGRENADE_WEIGHT		35
#define GASGRENADE_MAX_CLIP		WEAPON_NOCLIP_RELOAD
#define GASGRENADE_MAX_CARRY	5

// Spore Launcher
#define SPORELAUNCHER_WEIGHT		27
#define SPORELAUNCHER_MAX_CLIP		5
#define SPORE_MAX_CARRY				35
#define SPORE_PICKUP				1

// Plasma Rifle
#define PLASMARIFLE_WEIGHT			36
#define PLASMARIFLE_MAX_CLIP		40
#define PLUTONIUM_MAX_CARRY			160
#define STF_PLASMARIFLE_FIRING		64
#define PLASMABOLT_TYPE_NORMAL		0
#define PLASMABOLT_TYPE_PELLET		1
#define PLASMABOLT_TYPE_SUPER		2

// Question (Defacto Null Weapon) Yes/No/Question for the three attacks, R switches to fisticuffs mode
#define SOCIAL_MAX_CARRY			100
#define QUESTION_WEIGHT				1

// Flashbang
#define FLASHBANG_WEIGHT			15
#define FLASHBANG_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define FLASHBANG_MAX_CARRY			5

// Freeze Grenade
#define FRREZEGRENADE_WEIGHT		17
#define FRREZEGRENADE_MAX_CLIP		WEAPON_NOCLIP_RELOAD
#define FRREZEGRENADE_MAX_CARRY		5

// EMP Grenade
#define EMPGRENADE_WEIGHT			17
#define EMPGRENADE_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define EMPGRENADE_MAX_CARRY		5

// Timebomb
#define TIMEBOMB_MAX_CARRY			5
#define TIMEBOMB_WEIGHT				17
#define TIMEBOMB_MAX_CLIP			WEAPON_NOCLIP_RELOAD

// Proximity Mine
#define PROXBOMB_WEIGHT				17
#define PROXBOMB_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define PROXBOMB_MAX_CARRY			5

// Landmine
#define LANDMINE_WEIGHT				17
#define LANDMINE_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define LANDMINE_MAX_CARRY			3

// Nailmine
#define NAILMINE_WEIGHT				17
#define NAILMINE_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define NAILMINE_MAX_CARRY			3

// MIRV
#define MIRV_WEIGHT					17
#define MIRV_MAX_CLIP				WEAPON_NOCLIP_RELOAD
#define MIRV_MAX_CARRY				3

// Caltrop
#define CALTROP_WEIGHT				17
#define CALTROP_MAX_CLIP			WEAPON_NOCLIP_RELOAD
#define CALTROP_MAX_CARRY			100

// Detpack
#define DETPACK_MAX_CARRY			1
#define DETPACK_WEIGHT				1
#define DETPACK_MAX_CLIP			WEAPON_NOCLIP_RELOAD

// Extinguisher

#define ITEM_FLAG_SELECTONEMPTY		1
#define ITEM_FLAG_NOAUTORELOAD		2
#define ITEM_FLAG_NOAUTOSWITCHEMPTY	4
#define ITEM_FLAG_LIMITINWORLD		8
#define ITEM_FLAG_EXHAUSTIBLE		16 // A player can totally exhaust their ammo supply and lose this weapon
#define ITEM_FLAG_SECONDARYNOTAMMO	32	// Secondary ammo is not actual ammo
#define ITEM_FLAG_CANSELECT			64	// Always selectable, no matter what
#define ITEM_FLAG_NOAMMODISPLAY		128	// Do not display any ammo related HUD features.
#define ITEM_FLAG_DUPLICATION		256	// Allow duplicates to be picked up

#define WEAPON_IS_ONTARGET 0x40

typedef struct
{
	int		iSlot;
	int		iPosition;
	const char	*pszAmmo1;	// ammo 1 type
	int		iMaxAmmo1;		// max ammo 1
	const char	*pszAmmo2;	// ammo 2 type
	int		iMaxAmmo2;		// max ammo 2
	const char	*pszName;
	int		iMaxClip;
	int		iId;
	int		iFlags;
	int		iWeight;// this value used to determine this weapon's importance in autoselection.
} ItemInfo;

typedef struct
{
	const char *pszName;
	int iId;
} AmmoInfo;

// Items that the player has in their inventory that they can use
class CBasePlayerItem : public CBaseAnimating
{
public:
	virtual void SetObjectCollisionBox( void );

	virtual int		Save( CSave &save );
	virtual int		Restore( CRestore &restore );
	
	static	TYPEDESCRIPTION m_SaveData[];

	virtual int AddToPlayer( CBasePlayer *pPlayer );	// return TRUE if the item you want the item added to the player inventory
	virtual int AddDuplicate( CBasePlayerItem *pItem ) { return FALSE; }	// return TRUE if you want your duplicate removed from world
	void EXPORT DestroyItem( void );
	void EXPORT DestroyItemAlt(void);
	void EXPORT DefaultTouch( CBaseEntity *pOther );	// default weapon touch
	void EXPORT FallThink ( void );// when an item is first spawned, this think is run to determine when the object has hit the ground.
	void EXPORT Materialize( void );// make a weapon visible and tangible
	void EXPORT AttemptToMaterialize( void );  // the weapon desires to become visible and tangible, if the game rules allow for it
	CBaseEntity* Respawn ( void );// copy a weapon
	void FallInit( void );
	void CheckRespawn( void );
	virtual int GetItemInfo(ItemInfo *p) { return 0; };	// returns 0 if struct not filled out
	virtual BOOL CanDeploy( void ) { return TRUE; };
	virtual BOOL Deploy( )								// returns is deploy was successful
		 { return TRUE; };

	virtual BOOL CanHolster( void ) { return TRUE; };// can this weapon be put away right now?
	virtual void Holster( int skiplocal = 0 );
	virtual void UpdateItemInfo( void ) { return; };

	virtual void ItemPreFrame( void )	{ return; }		// called each frame by the player PreThink
	virtual void ItemPostFrame( void ) { return; }		// called each frame by the player PostThink

	virtual void Drop( void );
	virtual void Kill( void );
	virtual void AttachToPlayer ( CBasePlayer *pPlayer );

	virtual int UpdateClientData( CBasePlayer *pPlayer ) { return 0; }

	virtual CBasePlayerItem *GetWeaponPtr( void ) { return NULL; };

	virtual float GetHolsterTime(void) { return 0.0; }; // Get Deploy time for weapon
	virtual float GetDeployTime(void) { return 0.0; }; // Get Holster time for weapon

	static ItemInfo ItemInfoArray[128];
	static AmmoInfo AmmoInfoArray[MAX_AMMO_SLOTS];

	CBasePlayer	*m_pPlayer;
	CBasePlayerItem *m_pNext;
	int		m_iId;												// WEAPON_???

	BOOL IsWeapon(void) { return TRUE; }

	// 	Looks section
	int	m_iWeaponLooks; // This for additional appearance customization

	// Flag section
	int m_fWeaponFlags;
	virtual BOOL HasWeaponFlags(int fWeaponFlags, int fFlagCheck = FC_ALL) { return HasFlags(m_fWeaponFlags, fWeaponFlags, fFlagCheck); };
	virtual void SetWeaponFlags(int fWeaponFlags, BOOL bSign) { SetFlags(m_fWeaponFlags, fWeaponFlags, bSign); };

	// Status flag section
	flag m_fWeaponStatusFlags;
	virtual BOOL HasWeaponStatusFlags(flag fWeaponStatusFlags, int fFlagCheck = FC_ALL) { return HasFlags64(m_fWeaponStatusFlags, fWeaponStatusFlags, fFlagCheck); };
	virtual void SetWeaponStatusFlags(flag fWeaponStatusFlags, BOOL bSign) { SetFlags64(m_fWeaponStatusFlags, fWeaponStatusFlags, bSign); };

	// Upgrade section
	int m_fWeaponUpgrades; // Flag int keeping track of upgrades. One bit per upgrade
	virtual BOOL HasWeaponUpgrades(int fUpgrades, int fFlagCheck = FC_ALL) { return HasFlags(m_fWeaponUpgrades, fUpgrades, fFlagCheck); };
	virtual void SetWeaponUpgrades(int fWeaponUpgrades, BOOL bSign) { SetFlags(m_fWeaponUpgrades, fWeaponUpgrades, bSign); };
	virtual BOOL IsUpgradeable(CBasePlayerItem* pOriginal) { if (pOriginal) { return !HasWeaponUpgrades(pOriginal->m_fWeaponUpgrades, FC_ALL); } return FALSE; };
	void Upgrade(CBasePlayerItem* pOriginal);

	virtual void UpdateBodygroup(void) { return; };
	void KeyValue(KeyValueData* pkvd)
	{
		if (FStrEq(pkvd->szKeyName, "m_fWeaponUpgrades"))
		{
			m_fWeaponUpgrades = atoi(pkvd->szValue);
			pkvd->fHandled = TRUE;
			UpdateBodygroup();
		}
		else
			CBaseAnimating::KeyValue(pkvd);
	}

	// Icon handling stuff
	virtual int HUDIcon(void) { return 1; }; // Return index of icon that should be used
	virtual int HUDActiveIcon(void) { return 2; } // Return index of active icon that should be used
	virtual int ModeIcon(void) { return -1; }; // What mode icon should I use? // -1 means this isn't displayed at all
	virtual int ModeIcon2(void) { return -1; }; // What mode icon should I use? // -1 means this isn't displayed at all
	virtual int ModeIcon3(void) { return -1; }; // What mode icon should I use? // -1 means this isn't displayed at all
	virtual int SmallIcon(void) { return -1; }; // Small icons that are used for previous weapon and kill icon

	virtual BOOL ShouldDisplayThrowForce(void) { return FALSE; }; // Should this display throw force
	virtual int GetThrowForce(void) { return 0; }; //What throw force do we display
	virtual int GetMaxThrowForce(void) { return 100; }; // Maximum throw force
	virtual BOOL HasChamberRound(void) { return HasWeaponFlags(WEAPON_FLAG_CHAMBER_ROUND); };
	virtual BOOL ShouldRedeploy(CBasePlayerItem* pOriginal); // Should this weapon redeploy after upgrading?
	virtual BOOL CanDuplicate(CBasePlayerItem* pOriginal); // What conditions allow this weapon to be picked up if we already have a copy?
	virtual void PickupSound(void) { return; }; // What sound should this weapon play when picked up?
	virtual void DropSound(void) { return; }; // What sound should this weapon play when dropped?
	virtual void PreSpecialDuplicate(CBasePlayerItem* pOriginal) { return; }; // Perform special -actions relating to adding duplicates
	virtual void PostSpecialDuplicate(CBasePlayerItem* pOriginal) { return; }; // Perform special actions relating to adding duplicates

	virtual int iItemSlot( void ) { return 0; }			// return 0 to MAX_ITEMS_SLOTS, used in hud

	int			iItemPosition( void ) { return ItemInfoArray[ m_iId ].iPosition; }
	const char	*pszName( void )	{ return ItemInfoArray[ m_iId ].pszName; }
	int			iWeight( void )		{ return ItemInfoArray[ m_iId ].iWeight; }
	int			iFlags( void )		{ return ItemInfoArray[ m_iId ].iFlags; }

	int m_iszDropMonster; // Entity name for monster to drop if this is released, this goes for Chumtoads, Shock Roaches, Snarks
	int m_iszPickupSound;
	int m_iszDropSound;

	// Blocking mechanic
	BOOL m_bBlocking;
	float m_flBlockAmount;
	float m_flBlockCooldown;
	float m_flBlockRegen;
	virtual float GetBlockRegen(void) { return -1.0f; };
	virtual float GetBlockAmount(void) { return -1.0f; };
	virtual float GetBlockDot(void) { return -1.0f; };
	virtual float GetBlockCooldown(void) { return -1.0f; };
	virtual void Block(float flDamage) { return; };
	virtual void BlockBreak(float flDamage) { return; };
	virtual void BlockStop(void) { return; };

	// Tool mechanic
	int m_fToolFlags; // 0 for not, 1 for start, 2 for looping, 3 for ending
	float m_flToolTime;
	virtual void ToolStart(void) { return; };
	virtual void ToolLoop(void) { return; };
	virtual void ToolEnd(void) { return; };

	float m_flWeaponAnimTime;

	// Laser sight related stuff
	CLaserSpot* m_pSpot; // Set to null when created, not saved but rather recreated
	virtual void UpdateSpot(void); // Update Spot Position
	virtual void ActivateSpot(void); // Activate Spot
	virtual void DeactivateSpot(void); // Deactivate Spot
	virtual void SuspendSpot(float flTime); // Suspend spot for x amount of time
	virtual float GetSpotRender(void); // Get how how much of the spot is rendered
	virtual float SetDotRenderTime(float flTime); // Set the amount of time it takes for the dot to go from 0 to 255 or 255 to 0
	virtual BOOL SpotEnabled(void); // Determines whether or not we have a spot

	// More stuff
	// --------------------------------------------------------------------------------------------
	// Although defined here, these must be defined on every weapon to ensure smooth generalizing
	// Non-static, can be called and initialized from parent class

	//============================================================================
	// AMMO
	// Ammo stuff, goes as follows, clip, reserve ammo, all ammo
	// The ammo system having been reworked it's imperative to keep track of what the values mean
	// Positive value represent the ammo available
	// 0 means no ammo at this index
	// -1 means infinite ammo
	// -2 and below means illegal, cannot be had, etc.
	//============================================================================

	// Functions controling the new ammo system
	virtual weaponInfo* GetWeaponInfo(void) { return NULL; }; // Get Weapon Information, this is null by default
	virtual legalAmmoTypes* GetLegalAmmoTypes(void) { return NULL; } // Get all the legal ammo indices for this weapon
	virtual int GetNumAmmoTypes(void);
	virtual BOOL ValidAmmoTypeIndex(int iAmmoTypeIndex);
	virtual int GetNumAltAmmoTypes(int iAmmoTypeIndex);
	virtual BOOL ValidAltAmmoTypeIndex(int iAmmoTypeIndex, int iAmmoAltTypeIndex);
	virtual int GetTotalNumAmmoTypes(void);
	virtual int GetAmmoTypeMinBound(int iAmmoTypeIndex); // Get minimum bound for 
	virtual int GetAmmoTypeMaxBound(int iAmmoTypeIndex);
	virtual int* GetAmmoIndexArray(void) { return NULL; }; // Return array containing the ammo indices for each ammo slot
	virtual int* GetClipArray(void) { return NULL; }; // Return array containing the amount of ammo in each clip
	virtual int* GetPreReloadClipArray(void) { return NULL; };
	virtual int* GetMaxClipArray(void) { return NULL; }; // Return array containing the max amount of ammo allowed in each clip
	virtual int* GetChamberedArray(void) { return NULL; }; // Return array containing the number of chambered rounds per clip
	virtual int* GetMaxChamberedArray(void) { return NULL; }; // Return array containig the maximum of chambered rounds per clip
	virtual int* GetTargetAmmoIndexArray(void) { return NULL; }; // Return array containig the maximum of chambered rounds per clip
	virtual int GetNumClips(void); // Return the number of clips this weapon has
	virtual BOOL ValidClipIndex(int iClipIndex);
	virtual int GetClipAmmoType(int iClipIndex); // Return ammo type index (not ammo index) from clip by reverse searching
	virtual int GetClipAmmoLegalIndex(int iClipIndex);
	virtual int GetClipAmmoIndex(int iClipIndex); // Get Ammo Index from Clip
	virtual int GetCurrentAmmoType(int iAmmoTypeIndex);
	virtual void SetCurrentAmmoType(int iAmmoTypeIndex, int iSetTo);
	virtual int GetClip(int iClipIndex); // Get number of rounds in clip
	virtual int GetMaxClip(int iClipIndex); // Not static since upgrades may affect
	virtual int GetChamberedRounds(int iClipIndex); // IMPLEMENT THIS
	virtual int GetMaxChamberedRounds(int iClipIndex); // IMPLEMENT THIS
	virtual int GetTargetAmmoIndex(int iAmmoTypeIndex);
	virtual void SetTargetAmmoIndex(int iAmmoTypeIndex, int iTargetAmmoTypeIndex);
	virtual BOOL UsesAmmo(void);
	virtual BOOL UsesAmmoIndex(int iAmmoIndex);
	virtual int UsesAmmoName(const char* szAmmoName);
	virtual BOOL HasInfiniteReserveAmmoCheat(flag fCheckFlags); // Checks if we have the cheat for infinite reserve ammo
	virtual BOOL HasInfiniteReserveAmmo(flag fCheckFlags);
	virtual BOOL HasReserveAmmo(flag fCheckFlags); // Do we have any type of reserve ammo at all?
	virtual BOOL HasInfiniteReserveAmmoIndex(int iAmmoIndex, flag fCheckFlags); // Do we have this specific reserve ammo?
	virtual BOOL HasReserveAmmoIndex(int iAmmoIndex, flag fCheckFlags); // Do we have this specific reserve ammo?
	virtual BOOL HasInfiniteReserveAmmoType(int iAmmoTypeIndex, flag fCheckFlags);
	virtual BOOL HasReserveAmmoType(int iAmmoTypeIndex, flag fCheckFlags);
	virtual BOOL HasInfiniteReserveAmmoName(const char* szAmmoName, flag fCheckFlags);
	virtual BOOL HasReserveAmmoName(const char* szAmmoName, flag fCheckFlags);
	virtual BOOL HasInfiniteClipAmmoCheat(flag fCheckFlags); // Infinite Cheat Ammo
	virtual BOOL HasInfiniteClipAmmoIndex(int iClipIndex, flag fCheckFlags); // Do we have infinite clip ammo at this index? Do we take ammo cheats into consideration?
	virtual BOOL HasInfiniteClipAmmoTypeIndex(int iAmmoTypeIndex, flag fCheckFlags);
	virtual BOOL HasInfiniteClipAmmo(flag fCheckFlags);
	virtual BOOL HasClipAmmo(flag fCheckFlags); // Does this thing have any clip ammo
	virtual BOOL HasClipAmmoIndex(int iClipIndex, flag fCheckFlags); // Whether or not this
	virtual BOOL HasClipAmmoTypeIndex(int iClipIndex, flag fCheckFlags); // Whether or not this

	// These two functions are needed in the case the ammo that was already in the clip is returned to the reserve
	virtual int GetPreReloadClip(int iClipIndex);
	virtual void SetPreReloadClip(int iClipIndex, int iAmount);

	virtual BOOL HasInfiniteClipAmmoIndexSpecific(int iClipIndex, int iAmmoIndex, flag fCheckFlags);
	virtual BOOL HasClipAmmoIndexSpecific(int iClipIndex, int iAmmoIndex, flag fCheckFlags);
	virtual BOOL HasInfiniteClipAmmoIndexArray(int iAmmoIndex, flag fCheckFlags);
	virtual BOOL HasClipAmmoIndexArray(int iAmmoIndex, flag fCheckFlags);

	virtual void SetClip(int iClipIndex, int iAmount); // 
	virtual void SetMaxClip(int iClipIndex, int iAmount);
	virtual void IncrementClip(int iClipIndex, int iAmount);
	virtual void DecrementClip(int iClipIndex, int iAmount);
	virtual void SetChamberedRounds(int iClipIndex, int iAmount);
	virtual void IncrementChamberedRounds(int iClipIndex, int iAmount);
	virtual void DecrementChamberedRounds(int iClipIndex, int iAmount);
	virtual void SetMaxChamberedRounds(int iClipIndex, int iAmount);
	virtual BOOL HasAmmo(flag fCheckFlags); // Does this weapon have any ammo type?
	virtual BOOL HasAmmoType(int iAmmoTypeIndex, flag fCheckFlags); // Does this weapon have ammo of this type? (eg: 9mm and alts, 40mm and alt, etc.)
	virtual BOOL HasAmmoIndex(int iAmmoIndex, flag fCheckFlags); // Does this weapon have this amom?
	virtual BOOL HasAmmoName(const char* szAmmoName, flag fCheckFlags); // Does this weapon have ammo of this name?

	CBasePlayerItem(void)
	{
		m_fWeaponUpgrades = 0;
		m_iWeaponLooks = 0;
		m_fWeaponFlags = 0;

		m_iszDropMonster = iStringNull;
		m_iszPickupSound = iStringNull;
		m_iszDropSound = iStringNull;

		m_flBlockAmount = -1.0f;
		m_flBlockCooldown = -1.0f;
		m_flBlockRegen = -1.0f;
		m_flToolTime = -1.0f;

		m_flWeaponAnimTime = 0.0f;
		m_pSpot = NULL;
	}
};


// inventory items that 
class CBasePlayerWeapon : public CBasePlayerItem
{
public:
	virtual int		Save( CSave &save );
	virtual int		Restore( CRestore &restore );
	
	static	TYPEDESCRIPTION m_SaveData[];

	// Timer stuff
	float	m_flNextPrimaryAttack;								// soonest time ItemPostFrame will call PrimaryAttack
	float	m_flNextSecondaryAttack;							// soonest time ItemPostFrame will call SecondaryAttack
	float	m_flNextTertiaryAttack;								// soonest time ItemPostFrame will call TertiaryAttack
	float	m_flNextQuaternaryAttack;							// soonest time ItemPostFrame will call QuarternaryAttack
	float	m_flNextQuinaryAttack;								// soonest time ItemPostFrame will call QuinaryAttack
	float	m_flNextReload;										// soonest time ItemPostFrame will call Reload
	float	m_flNextWeaponIdle;									// soonest time ItemPostFrame will call WeaponIdle
	float	m_flNextRecoil;										// soonest time ItemPostFrame will call Recoil
	float	m_flNextCharge;										// soonest time ItemPostFrame will call Charge
	float	m_flNextPump;										// soonest time ItemPostFrame will cal Pump
	float	m_flNextSwitch;										// soonest time ItemPostFrame will call Switch

	// Some meters that may be helpful
	int m_iCharge;	// Amount of charge weapon has
	int m_iMaxCharge;
	int m_iRecoil; // Amount of recoil weapon has
	int m_iMaxRecoil; // Max ammount of recoil weapons has
	float m_flInitialRecoilCooldown;
	float m_flIncrementalRecoilCooldown;						// After recoil is called, increment timer by this amount if not done artificially

	// All burst fire stuff
	int m_iBurst;
	int m_iBurstMax;
	void SetBurst(int iNum) { m_iBurst = iNum; };
	int GetBurst(void) { return m_iBurst; };
	void SetBurstMax(int iNum) { m_iBurstMax = iNum; };
	int GetBurstMax(void) { return m_iBurstMax; };
	void SetBursts(int iNum, int iNumMax) { m_iBurst = iNum; m_iBurstMax = iNum; };

	int		m_iClientClip;										// the last version of m_iClip sent to hud dll
	int		m_iClientWeaponState;								// the last version of the weapon state sent to hud dll (is current weapon, is on target)

	int		m_iDefaultAmmo;// how much ammo you get when you pick up this weapon as placed by a level designer.
	int		m_iDefaultAmmoSecondary; // How much secondary ammo do you get when picking this up

	// generic weapon versions of CBasePlayerItem calls
	virtual int AddToPlayer( CBasePlayer *pPlayer );
	virtual int AddDuplicate( CBasePlayerItem *pItem );

	// Changed to include clip
	virtual int AddWeapon(void) { ExtractAmmo(this); return TRUE; };	// Return TRUE if you want to add yourself to the player
	virtual int ExtractAmmo( CBasePlayerWeapon *pWeapon ); //{ return TRUE; };			// Return TRUE if you can add ammo to yourself when picked up
	//virtual int ExtractClipAmmo( CBasePlayerWeapon *pWeapon );// { return TRUE; };			// Return TRUE if you can add ammo to yourself when picked up

	virtual void UpdateItemInfo( void ) {};	// updates HUD state

	int m_iPlayEmptySound;
	int m_fFireOnEmpty;		// True when the gun is empty and the player is still holding down the
							// attack key(s)
	virtual BOOL PlayEmptySound( void );
	virtual void ResetEmptySound( void );

	virtual void SendWeaponAnim( int iAnim, float flFramerate = 1.0f, byte byFrame = (byte)0, int skiplocal = 1 );  // skiplocal is 1 if client is predicting weapon animations

	virtual BOOL CanDeploy( void );
	virtual BOOL IsUseable( void );
	BOOL DefaultDeploy( char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal = 0, int body = 0 );


	virtual void ItemPostFrame( void );	// called each frame by the player PostThink
	// called by CBasePlayerWeapons ItemPostFrame()
	virtual void PrimaryAttack( void ) { return; }				// do "+ATTACK"
	virtual void SecondaryAttack( void ) { return; }			// do "+ATTACK2"
	virtual void TertiaryAttack(void) { return; }				// do "+ATTACK3"
	virtual void QuaternaryAttack(void) { return; }				// do "+ATTACK4"
	virtual void QuinaryAttack(void) { return; }				// do "+ATTACK5"
	virtual void Reload( void ) { return; }						// do "+RELOAD"
	virtual void WeaponIdle( void ) { return; }					// called when no buttons pressed
	virtual int UpdateClientData( CBasePlayer *pPlayer );		// sends hud info to client dll, if things have changed
	virtual void RetireWeapon( void );
	virtual BOOL ShouldWeaponIdle( void ) {return FALSE; };
	virtual void Holster( int skiplocal = 0 );
	virtual BOOL UseDecrement( void ) { return FALSE; };

	virtual void Recoil(void) { return; };
	virtual void Charge(void) { return; };
	virtual void Pump(void) { return; };
	virtual void Switch(void) { return; };

	// Reload related functions
	virtual void ReloadStart(void); // functions that allow for more customizability with reload
	virtual void ReloadStartToMid(void);
	virtual void ReloadMid(void); // functions that allow for more customizability with reload
	virtual void ReloadMidToEnd(void);;
	virtual void ReloadEnd(void); // functions that allow for more customizability with reload
	virtual void ReloadEndToStart(void);
	virtual void ReloadCheck(void); // Check for ammo or set/unset bolt/slide on empty
	
	virtual BOOL InReloadStart(void) { return HasWeaponStatusFlags(WEAPON_STF_RELOAD_START, FC_ALL); }; // Are we just starting the reload?
	virtual BOOL InReloadStartToMid(void) { return HasWeaponStatusFlags(WEAPON_STF_RELOAD_START | WEAPON_STF_RELOAD_MID, FC_ALL); }; // Are we going between the start and the mid?
	virtual BOOL InReloadMid(void) { return HasWeaponStatusFlags(WEAPON_STF_RELOAD_MID, FC_ALL); }; // Are we in the middle of reloading?
	virtual BOOL InReloadMidToEnd(void) { return HasWeaponStatusFlags(WEAPON_STF_RELOAD_MID | WEAPON_STF_RELOAD_END, FC_ALL); }; // Are we going between the middle and the end?
	virtual BOOL InReloadEnd(void) { return HasWeaponStatusFlags(WEAPON_STF_RELOAD_END, FC_ALL); }; // Are we ending reloading?
	virtual BOOL InReloadEndToStart(void) { return HasWeaponStatusFlags(WEAPON_STF_RELOAD_END | WEAPON_STF_RELOAD_START, FC_ALL); }; // Are we going back to start
	virtual BOOL InReloadCheck(void) { return HasWeaponStatusFlags(WEAPON_STF_RELOAD_START | WEAPON_STF_RELOAD_MID | WEAPON_STF_RELOAD_END, FC_ALL); }; // Are we trying to reload when we can't? Do something funny, cock the gun, spin it.
	virtual BOOL InReload(void) { return HasWeaponStatusFlags(WEAPON_STF_RELOAD_START | WEAPON_STF_RELOAD_MID | WEAPON_STF_RELOAD_END, FC_ANY); }; // Are we reloading in general
	virtual BOOL InAmmoSwitch(void) { return HasWeaponStatusFlags(WEAPON_STF_SWITCH_AMMO, FC_ANY); }
	virtual BOOL InTrueReload(void) { return (!InReloadCheck() && InReload()); }; // Any reload action that isn't a check

	virtual void SetReloadStart(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_START, TRUE); };
	virtual void SetReloadStartToMid(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_START | WEAPON_STF_RELOAD_MID, TRUE); };
	virtual void SetReloadMid(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_MID, TRUE); };
	virtual void SetReloadMidToEnd(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_MID | WEAPON_STF_RELOAD_END, TRUE); };
	virtual void SetReloadEnd(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_END, TRUE); };
	virtual void SetReloadEndToStart(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_START | WEAPON_STF_RELOAD_END, TRUE); };
	virtual void SetReloadCheck(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_START | WEAPON_STF_RELOAD_MID | WEAPON_STF_RELOAD_END, TRUE); };
	virtual void SetAmmoSwitch(void) { SetWeaponStatusFlags(WEAPON_STF_SWITCH_AMMO, TRUE); }

	virtual void UnsetReloadStart(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_START, FALSE); };
	virtual void UnsetReloadStartToMid(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_START | WEAPON_STF_RELOAD_MID, FALSE); };
	virtual void UnsetReloadMid(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_MID, FALSE); };
	virtual void UnsetReloadMidToEnd(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_MID | WEAPON_STF_RELOAD_END, FALSE); };
	virtual void UnsetReloadEnd(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_END, FALSE); };
	virtual void UnsetReloadEndToStart(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_START | WEAPON_STF_RELOAD_END, FALSE); };
	virtual void UnsetReloadCheck(void) { SetWeaponStatusFlags(WEAPON_STF_RELOAD_START | WEAPON_STF_RELOAD_MID | WEAPON_STF_RELOAD_END, FALSE); };
	virtual void UnsetReload(void) { UnsetReloadCheck(); }
	virtual void UnsetAmmoSwitch(void) { SetWeaponStatusFlags(WEAPON_STF_SWITCH_AMMO, FALSE); }

	virtual BOOL ShouldReload(int iClipIndex) { return TRUE; };
	virtual void ChangeClip(int iAmount, int iClipIndex, BOOL bSwap = FALSE) {  };
	virtual void DefaultReloadClipIn(int iClipIndex);
	virtual void DefaultReloadClipOut(int iClipIndex);

	// Semi-auto firing mechanic
	virtual BOOL HasSemiFired(void) { return HasWeaponStatusFlags(WEAPON_STF_SEMIFIRED, FC_ALL); };
	virtual void SetSemiFired(void) { SetWeaponStatusFlags(WEAPON_STF_SEMIFIRED, TRUE); };
	virtual void UnsetSemiFired(void) { SetWeaponStatusFlags(WEAPON_STF_SEMIFIRED, FALSE); };
	
	// Idle
	virtual void SetIdle(void) { SetWeaponStatusFlags(WEAPON_STF_IDLE, TRUE); }
	virtual void UnsetIdle(void) { SetWeaponStatusFlags(WEAPON_STF_IDLE, FALSE); }
	virtual BOOL IsIdle(void) { return HasWeaponStatusFlags(WEAPON_STF_IDLE); }
	virtual void SetSpecialIdle(void) { SetWeaponStatusFlags(WEAPON_STF_IDLE_SPECIAL, TRUE); }
	virtual void UnsetSpecialIdle(void) { SetWeaponStatusFlags(WEAPON_STF_IDLE_SPECIAL, FALSE); }
	virtual BOOL IsSpecialIdle(void) { return HasWeaponStatusFlags(WEAPON_STF_IDLE_SPECIAL); }
	virtual void UnsetAllIdle(void) { SetWeaponStatusFlags(WEAPON_STF_IDLE | WEAPON_STF_IDLE_SPECIAL, FALSE); }
	virtual BOOL IsAnyIdle(void) { return HasWeaponStatusFlags(WEAPON_STF_IDLE | WEAPON_STF_IDLE_SPECIAL, FC_ANY); }

	// Pumping/cocking
	virtual void SetUnpumped(void) { SetWeaponStatusFlags(WEAPON_STF_UNPUMPED, TRUE); };
	virtual void UnsetUnpumped(void) { SetWeaponStatusFlags(WEAPON_STF_UNPUMPED, FALSE); };
	virtual BOOL IsUnpumped(void) { return HasWeaponStatusFlags(WEAPON_STF_UNPUMPED, FC_ALL); }

	// Timer code
	virtual BOOL CanPrimaryAttack(void) { return CanAttack(m_flNextPrimaryAttack, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanSecondaryAttack(void) { return CanAttack(m_flNextSecondaryAttack, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanTertiaryAttack(void) { return CanAttack(m_flNextTertiaryAttack, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanQuaternaryAttack(void) { return CanAttack(m_flNextQuaternaryAttack, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanQuinaryAttack(void) { return CanAttack(m_flNextQuinaryAttack, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanReload(void) { return CanAttack(m_flNextReload, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanWeaponIdle(void) { return CanAttack(m_flNextWeaponIdle, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanRecoil(void) { return CanAttack(m_flNextRecoil, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanCharge(void) { return CanAttack(m_flNextCharge, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanPump(void) { return CanAttack(m_flNextPump, gpGlobals->time, UseDecrement()); }
	virtual BOOL CanSwitch(void) { return CanAttack(m_flNextSwitch, gpGlobals->time, UseDecrement()); }

	virtual void SetPrimaryAttack(float flTime) { m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + flTime; };
	virtual void SetSecondaryAttack(float flTime) { m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flTime; };
	virtual void SetTertiaryAttack(float flTime) { m_flNextTertiaryAttack = UTIL_WeaponTimeBase() + flTime; };
	virtual void SetQuaternaryAttack(float flTime) { m_flNextQuaternaryAttack = UTIL_WeaponTimeBase() + flTime; }
	virtual void SetQuinaryAttack(float flTime) { m_flNextQuinaryAttack = UTIL_WeaponTimeBase() + flTime; };
	virtual void SetReload(float flTime) { m_flNextReload = UTIL_WeaponTimeBase() + flTime; };
	virtual void SetWeaponIdle(float flTime) { m_flNextWeaponIdle = UTIL_WeaponTimeBase() + flTime; };
	virtual void SetRecoil(float flTime) { m_flNextRecoil = UTIL_WeaponTimeBase() + flTime; };
	virtual void SetCharge(float flTime) { m_flNextCharge = UTIL_WeaponTimeBase() + flTime; };
	virtual void SetPump(float flTime) { m_flNextPump = UTIL_WeaponTimeBase() + flTime; };
	virtual void SetSwitch(float flTime) { m_flNextSwitch = UTIL_WeaponTimeBase() + flTime; };

	int m_iSwing;
	virtual int Swing(bool bFirst, int iType) { return 0; };
	virtual void EXPORT SwingAgain(void) {};
	virtual void EXPORT SwingSmack(void) {};

	void PrintState( void );

	virtual CBasePlayerItem *GetWeaponPtr( void ) { return (CBasePlayerItem *)this; };

	virtual void UpdateAnimationInfo(void);
	// Some helper functions for status

	// Client vars go here, these are the varriables we use to check for HUD updates, they serve no other purpose

	// CALLBACK: This is mental gymnastics. Essentially, in order to make it so we can call the CBasePlayerItem
	// functions and keep virtual with default parameters, we have to declare them again in CBasePlayerWeapon
	// as virtuals and the same default params.
	//virtual int GetNumAmmoTypes(void) { return CBasePlayerItem::GetNumAmmoTypes(); };
	//virtual int GetNumAltAmmoTypes(int iAmmoTypeIndex) { return CBasePlayerItem::GetNumAltAmmoTypes(iAmmoTypeIndex); };
	//virtual int GetTotalNumAmmoTypes(void) { return CBasePlayerItem::GetTotalNumAmmoTypes(); };
	//virtual int GetCurrentAmmoType(int iAmmoTypeIndex) { return CBasePlayerItem::GetCurrentAmmoType(iAmmoTypeIndex); };

	//virtual BOOL ValidAmmoTypeIndex(int iAmmoTypeIndex) { return CBasePlayerItem::ValidAmmoTypeIndex(iAmmoTypeIndex); };
	//virtual BOOL ValidAmmoAltTypeIndex(int iAmmoTypeIndex, int iAmmoAltTypeIndex) { return CBasePlayerItem::ValidAltAmmoTypeIndex(iAmmoTypeIndex, iAmmoAltTypeIndex); };
	//virtual BOOL ValidClipIndex(int iClipIndex) { return CBasePlayerItem::ValidClipIndex(iClipIndex); };

	//virtual BOOL UsesAmmo(void) { return CBasePlayerItem::UsesAmmo(); };
	//virtual BOOL UsesAmmoIndex(int iAmmoIndex) { return CBasePlayerItem::UsesAmmoIndex(iAmmoIndex); };
	//virtual int UsesAmmoName(const char* szAmmoName) { return CBasePlayerItem::UsesAmmoName(szAmmoName); };

	//virtual BOOL HasInfiniteReserveAmmoCheat(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasInfiniteReserveAmmoCheat(fCheckFlags); };
	//virtual BOOL HasInfiniteReserveAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasInfiniteReserveAmmo(fCheckFlags); };
	//virtual BOOL HasReserveAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasReserveAmmo(fCheckFlags); };
	//virtual BOOL HasInfiniteReserveAmmoIndex(int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasInfiniteReserveAmmoIndex(iAmmoIndex, fCheckFlags); };
	//virtual BOOL HasReserveAmmoIndex(int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasReserveAmmoIndex(iAmmoIndex, fCheckFlags); };
	//virtual BOOL HasInfiniteReserveAmmoType(int iAmmoTypeIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasInfiniteReserveAmmoType(iAmmoTypeIndex, fCheckFlags); };
	//virtual BOOL HasReserveAmmoType(int iAmmoTypeIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasReserveAmmoType(iAmmoTypeIndex, fCheckFlags); };
	//virtual BOOL HasInfiniteReserveAmmoName(const char* szAmmoName, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasReserveAmmoName(szAmmoName, fCheckFlags); };
	//virtual BOOL HasReserveAmmoName(const char* szAmmoName, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasReserveAmmoName(szAmmoName, fCheckFlags); };

	//virtual int GetNumClips(void) { return CBasePlayerItem::GetNumClips(); };
	//virtual int GetClip(int iClipIndex) { return CBasePlayerItem::GetClip(iClipIndex); };
	//virtual int GetMaxClip(int iClipIndex) { return CBasePlayerItem::GetMaxClip(iClipIndex); };

	//virtual BOOL HasInfiniteClipAmmoCheat(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasInfiniteClipAmmoCheat(fCheckFlags); };
	//virtual BOOL HasInfiniteClipAmmoIndex(int iClipIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasInfiniteClipAmmoCheat(fCheckFlags); };
	//virtual BOOL HasInfiniteClipAmmoTypeIndex(int iAmmoTypeIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasInfiniteClipAmmoTypeIndex(iAmmoTypeIndex, fCheckFlags); };
	//virtual BOOL HasInfiniteClipAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasInfiniteClipAmmo(fCheckFlags); };
	//virtual BOOL HasClipAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasClipAmmo(fCheckFlags); };
	//virtual BOOL HasClipAmmoIndex(int iClipIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasClipAmmoIndex(iClipIndex, fCheckFlags); };
	//virtual BOOL HasClipAmmoTypeIndex(int iClipIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasClipAmmoTypeIndex(iClipIndex, fCheckFlags); };

	//virtual void SetClip(int iClipIndex, int iAmount) { return CBasePlayerItem::SetClip(iClipIndex, iAmount); };
	//virtual void SetMaxClip(int iClipIndex, int iAmount) { return CBasePlayerItem::SetMaxClip(iClipIndex, iAmount); };
	//virtual void IncrementClip(int iClipIndex, int iAmount = 1) { return CBasePlayerItem::IncrementClip(iClipIndex, iAmount); };
	//virtual void DecrementClip(int iClipIndex, int iAmount = 1) { return CBasePlayerItem::DecrementClip(iClipIndex, iAmount); };
	//virtual int GetMaxChamberedRounds(int iClipIndex) { return CBasePlayerItem::GetMaxChamberedRounds(iClipIndex); };
	//virtual int GetClipAmmoIndex(int iClipIndex) { return CBasePlayerItem::GetClipAmmoIndex(iClipIndex); };

	//virtual BOOL HasAmmo(flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasAmmo(fCheckFlags); };
	//virtual BOOL HasAmmoType(int iAmmoTypeIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasAmmoType(iAmmoTypeIndex, fCheckFlags); };
	//virtual BOOL HasAmmoIndex(int iAmmoIndex, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasAmmoIndex(iAmmoIndex, fCheckFlags); };
	//virtual BOOL HasAmmoName(const char* szAmmoName, flag fCheckFlags = AMMO_CHECK_DEFAULT_PARAMS) { return CBasePlayerItem::HasAmmoName(szAmmoName, fCheckFlags); };
};


class CBasePlayerAmmo : public CBaseEntity
{
public:
	virtual void Spawn( void );
	void EXPORT DefaultTouch( CBaseEntity *pOther ); // default weapon touch

	CBaseEntity* Respawn( void );
	void EXPORT Materialize( void );

	int m_szPickupSound;
	int m_szAmmoType;
	int m_szModel;
	int m_iAmmoAmount;

#ifndef CLIENT_DLL
	// Save restore because we now have additional data
	int		Save(CSave& save);
	int		Restore(CRestore& restore);
	static	TYPEDESCRIPTION m_SaveData[];

	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity* pOther);
	virtual void KeyValue(KeyValueData* pkvd);
	CBasePlayerAmmo(void);
#endif
};


extern DLL_GLOBAL	short	g_sModelIndexLaser;// holds the index for the laser beam
extern DLL_GLOBAL	const char *g_pModelNameLaser;

extern DLL_GLOBAL	short	g_sModelIndexLaserDot;// holds the index for the laser beam dot
extern DLL_GLOBAL	short	g_sModelIndexFireball;// holds the index for the fireball
extern DLL_GLOBAL	short	g_sModelIndexSmoke;// holds the index for the smoke cloud
extern DLL_GLOBAL	short	g_sModelIndexWExplosion;// holds the index for the underwater explosion
extern DLL_GLOBAL	short	g_sModelIndexBubbles;// holds the index for the bubbles model
extern DLL_GLOBAL	short	g_sModelIndexBloodDrop;// holds the sprite index for blood drops
extern DLL_GLOBAL	short	g_sModelIndexBloodSpray;// holds the sprite index for blood spray (bigger)

extern void ClearMultiDamage(void);
extern void ApplyMultiDamage(entvars_t* pevInflictor, entvars_t* pevAttacker );
extern void AddMultiDamage( entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int iDamageId);

extern void DecalGunshot( TraceResult *pTrace, int iBulletType );
extern void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage);
extern int DamageDecal( CBaseEntity *pEntity, int iDamageId );
extern void RadiusDamage( Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int iDamageId );

typedef struct 
{
	CBaseEntity		*pEntity;
	float			amount;
	int				type;
} MULTIDAMAGE;

extern MULTIDAMAGE gMultiDamage;


#define LOUD_GUN_VOLUME			1000
#define NORMAL_GUN_VOLUME		600
#define QUIET_GUN_VOLUME		200
#define SILENT_GUN_VOLUME		0

#define	BRIGHT_GUN_FLASH		512
#define NORMAL_GUN_FLASH		256
#define	DIM_GUN_FLASH			128
#define NULL_GUN_FLASH			0

#define BIG_EXPLOSION_VOLUME	2048
#define NORMAL_EXPLOSION_VOLUME	1024
#define SMALL_EXPLOSION_VOLUME	512

#define	WEAPON_ACTIVITY_VOLUME	64

#define VECTOR_CONE_1DEGREES	Vector( 0.00873, 0.00873, 0.00873 )
#define VECTOR_CONE_2DEGREES	Vector( 0.01745, 0.01745, 0.01745 )
#define VECTOR_CONE_3DEGREES	Vector( 0.02618, 0.02618, 0.02618 )
#define VECTOR_CONE_4DEGREES	Vector( 0.03490, 0.03490, 0.03490 )
#define VECTOR_CONE_5DEGREES	Vector( 0.04362, 0.04362, 0.04362 )
#define VECTOR_CONE_6DEGREES	Vector( 0.05234, 0.05234, 0.05234 )
#define VECTOR_CONE_7DEGREES	Vector( 0.06105, 0.06105, 0.06105 )
#define VECTOR_CONE_8DEGREES	Vector( 0.06976, 0.06976, 0.06976 )
#define VECTOR_CONE_9DEGREES	Vector( 0.07846, 0.07846, 0.07846 )
#define VECTOR_CONE_10DEGREES	Vector( 0.08716, 0.08716, 0.08716 )
#define VECTOR_CONE_15DEGREES	Vector( 0.13053, 0.13053, 0.13053 )
#define VECTOR_CONE_20DEGREES	Vector( 0.17365, 0.17365, 0.17365 )

//=========================================================
// CWeaponBox - a single entity that can store weapons
// and ammo. 
//=========================================================
class CWeaponBox : public CBaseEntity
{
	void Precache( void );
	void Spawn( void );
	void Touch( CBaseEntity *pOther );
	void KeyValue( KeyValueData *pkvd );
	BOOL IsEmpty( void );
	int  GiveAmmo( int iCount, char *szName, int iMax, int *pIndex = NULL );
	void SetObjectCollisionBox( void );

public:
	void EXPORT Kill ( void );
	int		Save( CSave &save );
	int		Restore( CRestore &restore );
	static	TYPEDESCRIPTION m_SaveData[];

	BOOL HasWeapon( CBasePlayerItem *pCheckItem );
	BOOL PackWeapon( CBasePlayerItem *pWeapon );
	BOOL PackAmmo( int iszName, int iCount );
	
	CBasePlayerItem	*m_rgpPlayerItems[MAX_ITEM_TYPES];// one slot for each 

	int m_rgiszAmmo[MAX_AMMO_SLOTS];// ammo names
	int	m_rgAmmo[MAX_AMMO_SLOTS];// ammo quantities

	int m_cAmmoTypes;// how many ammo types packed into this box (if packed by a level designer)
};

#ifdef CLIENT_DLL
bool bIsMultiplayer ( void );
void LoadVModel ( char *szViewModel, CBasePlayer *m_pPlayer );
#endif

// CWeaponTemplate: This is the base weapon template for all weapons and will feature all functions that should be systemically defined on each one
// Note: This class is intentionally commented out because as CBasePlayerItem and CBasePlayerWeapon already do
// This is basically a chunk of text for developers to copy, paste and uncomment whenever imeplementing a new weapon
//class CWeaponTemplate : public CBasePlayerWeapon
//{
//public:
//	void Precache(void);
//	void Spawn(void);
//};


// Question: The unarmed weapon, given by default to all players. Under no circumstance should this be removed.
// IDEA: Make it not occupy an actual weapon slot
class CQuestion : public CBasePlayerWeapon
{
public:
	void Spawn(void);
	void Precache(void);
	int iItemSlot() { return 0; }
	int GetItemInfo(ItemInfo* p);
	BOOL IsUseable(void);
	void PrimaryAttack(void);
	void SecondaryAttack(void);
	int AddToPlayer(CBasePlayer* pPlayer);
	BOOL Deploy();
	void Holster(int skiplocal = 0);
	void Reload(void);
	void WeaponIdle(void);
	void ItemPostFrame(void);

	int HUDIcon(void);
	int HUDActiveIcon(void);
	int ModeIcon(void);
	int ModeIcon2(void);
	int ModeIcon3(void);
	int SmallIcon(void);

	virtual BOOL UseDecrement(void)
	{
#if defined( CLIENT_WEAPONS )
		return TRUE;
#else
		return FALSE;
#endif
	}
};

//class CCrowbar : public CBasePlayerWeapon
//{
//
//#ifndef CLIENT_DLL
//	int		Save(CSave& save);
//	int		Restore(CRestore& restore);
//	static	TYPEDESCRIPTION m_SaveData[];
//#endif
//
//public:
//	void Spawn(void);
//	void Precache(void);
//	int iItemSlot(void) { return 1; }
//	void EXPORT SwingAgain(void);
//	void EXPORT Smack(void);
//	int GetItemInfo(ItemInfo* p);
//
//	void PrimaryAttack(void);
//	void SecondaryAttack(void);
//	void TertiaryAttack(void);
//	void Reload(void);
//	int Swing(int fFirst);
//	BOOL Deploy(void);
//	void Holster(int skiplocal = 0);
//	int m_iSwing;
//	TraceResult m_trHit;
//
//	void ItemPostFrame(void);
//	void UpdateBodygroup(void);
//
//	void PickupSound(void);
//
//	int HUDIcon(void);
//	int HUDActiveIcon(void);
//	int ModeIcon(void);
//	int ModeIcon2(void);
//	int ModeIcon3(void);
//	int SmallIcon(void);
//	//BOOL IsUseable(void);
//
//	void WeaponIdle(void);
//	BOOL m_bSwingLock;
//
//	int GetIdealIdleAnim(void);
//
//	BOOL m_bBigSwing;
//	float m_flSwingTime;
//	int BigSwing(int fFirst);
//	void EXPORT BigSwingAgain(void);
//	void EXPORT BigSmack(void);
//
//	int m_iThrowing;
//	float m_flThrowTime;
//	void ThrowCrowbar(void);
//	void RedrawCrowbar(void);
//	void DestroyCrowbar(void);
//
//	// Block
//	float GetBlockRegen(void);
//	float GetBlockAmount(void);
//	float GetBlockDot(void);
//	float GetBlockCooldown(void);
//	void Block(float flDamage);
//	void BlockBreak(float flDamage);
//	void BlockStop(void);
//
//	int CounterSwing(int fFirst);
//	void EXPORT CounterSwingAgain(void);
//	void EXPORT CounterSmack(void);
//
//	// Display block or throwing
//	BOOL ShouldDisplayThrowForce(void);
//	int GetThrowForce(void);
//	int GetMaxThrowForce(void);
//
//	// Tool
//	void ToolStart(void);
//	void ToolLoop(void);
//	void ToolEnd(void);
//
//	CCrowbar(void)
//	{
//		m_iSwing = 0;
//		m_bSwingLock = FALSE;
//		m_bBigSwing = FALSE;
//		m_flSwingTime = -1;
//	};
//
//
//	virtual BOOL UseDecrement(void)
//	{
//#if defined( CLIENT_WEAPONS )
//		return TRUE;
//#else
//		return FALSE;
//#endif
//}
//private:
//	unsigned short m_usCrowbar;
//};
//
//class CGlock : public CBasePlayerWeapon
//{
//
//#ifndef CLIENT_DLL
//	int		Save(CSave& save);
//	int		Restore(CRestore& restore);
//	static	TYPEDESCRIPTION m_SaveData[];
//#endif
//
//public:
//	void Spawn(void);
//	void Precache(void);
//	int iItemSlot(void) { return 2; }
//	int GetItemInfo(ItemInfo* p);
//	void PrimaryAttack(void);
//	void SecondaryAttack(void);
//	void TertiaryAttack(void);
//	void GlockFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);
//	BOOL Deploy(void);
//	void Holster(int skiplocal = 0);
//	void Reload(void);
//	void WeaponIdle(void);
//	int m_iShell;
//	//BOOL IsUseable(void);
//
//	// Fire modes and upgrades
//	void SwitchSilencer(int mode);
//	BOOL m_fAutofire;
//	BOOL m_fSilenced;
//	// Silencing is much more complex and requires a little bit of timing.
//	BOOL NewDeploy(char* szViewModel, char* szWeaponModel, int iAnim, char* szAnimExt);
//	BOOL m_fSilencing;
//	float m_flSilencing;
//
//	void ItemPostFrame(void);
//	void UpdateBodygroup(void);
//	void PickupSound(void);
//	int HUDIcon(void);
//	int HUDActiveIcon(void);
//	int ModeIcon(void);
//	int ModeIcon2(void);
//	int ModeIcon3(void);
//	int SmallIcon(void);
//
//	typedef enum
//	{
//		GLOCK_SILENCE_FIRST = 0,
//		GLOCK_SILENCE_LAST,
//	} GLOCK_SILENCER_STEP;
//
//	CGlock(void)
//	{
//		m_fAutofire = FALSE;
//		m_fSilenced = FALSE;
//		m_fSilencing = FALSE;
//		m_flSilencing = -1;
//	};
//
//	virtual BOOL UseDecrement(void)
//	{
//#if defined( CLIENT_WEAPONS )
//		return TRUE;
//#else
//		return FALSE;
//#endif
//	}
//
//private:
//	unsigned short m_usGlock1;
//	unsigned short m_usGlock2;
//};

class CMP5 : public CBasePlayerWeapon
{
public:

#ifndef CLIENT_DLL
	int		Save(CSave& save);
	int		Restore(CRestore& restore);
	static	TYPEDESCRIPTION m_SaveData[];
#endif

	void Spawn(void);
	void Precache(void);
	int iItemSlot(void) { return 3; }
	int GetItemInfo(ItemInfo* p);
	void Holster(int skiplocal = 0);
	void PrimaryAttack(void);
	void SecondaryAttack(void);
	void TertiaryAttack(void);
	void QuaternaryAttack(void);
	void QuinaryAttack(void);
	BOOL Deploy(void);

	BOOL ShouldReload(int iClipIndex);
	void Reload(void);
	void ReloadStart(void);
	void ReloadStartToMid(void);
	void ReloadMid(void);
	void ReloadMidToEnd(void);
	void ReloadEnd(void);
	void ReloadEndToStart(void);

	void WeaponIdle(void);
	int m_iShell;

	void ItemPostFrame(void);
	void UpdateBodygroup(void);
	void PickupSound(void);
	void DropSound(void);

	int HUDIcon(void);
	int HUDActiveIcon(void);
	int ModeIcon(void);
	int ModeIcon2(void);
	int ModeIcon3(void);
	int SmallIcon(void);

	// Needed on every one to ensure these stay constant
	static weaponInfo m_weaponInfo; // Ammo Types used by the weapon, STATIC and as such is never saved
	weaponInfo* GetWeaponInfo(void) { return &m_weaponInfo; };

	static legalAmmoTypes m_legalAmmoIndicies; // Indices of ammo types used by the weapon. Note that -1 means index invalid
	int m_iAmmoIndices[2]; // Ammo indices currently loaded, the size of this must be equal to number of ammo types (not total number of ammo types)
	int m_iClips[2];
	int m_iMaxClips[2];
	int m_iChamberedRounds[2];
	int m_iMaxChamberedRounds[2];
	int m_iPreReloadClips[2];
	int m_iTargetAmmoIndex[2];

	legalAmmoTypes* GetLegalAmmoTypes(void) { return &m_legalAmmoIndicies; }; // Get all the legal ammo indices for this weapon
	int* GetAmmoIndexArray(void) { return m_iAmmoIndices; }; // Return array containing the ammo indices for each ammo slot
	int* GetClipArray(void) { return m_iClips; }; // Return array containing the amount of ammo in each clip
	int* GetPreReloadClipArray(void) { return m_iPreReloadClips; };
	int* GetMaxClipArray(void) { return m_iMaxClips; }; // Return array containing the max amount of ammo allowed in each clip
	int* GetChamberedArray(void) { return m_iChamberedRounds; }; // Return array containing the number of chambered rounds per clip
	int* GetMaxChamberedArray(void) { return m_iMaxChamberedRounds; }; // Return array containig the maximum of chambered rounds per clip
	int* GetTargetAmmoIndexArray(void) { return m_iTargetAmmoIndex; };
	BOOL UsesAmmo(void) { return TRUE; };

	CMP5(void);

	virtual BOOL UseDecrement(void)
	{
#if defined( CLIENT_WEAPONS )
		return TRUE;
#else
		return FALSE;
#endif
	}
private:
	unsigned short m_usMP5;
	unsigned short m_usMP52;

};

class CLightningGun : public CBasePlayerWeapon
{
public:

#ifndef CLIENT_DLL
	int		Save(CSave& save);
	int		Restore(CRestore& restore);
	static	TYPEDESCRIPTION m_SaveData[];
#endif

	void Spawn(void);
	void Precache(void);
	int iItemSlot(void) { return 3; }
	int GetItemInfo(ItemInfo* p);
	void Holster(int skiplocal = 0);
	void PrimaryAttack(void);
	void SecondaryAttack(void);
	void TertiaryAttack(void);
	void QuaternaryAttack(void);
	void QuinaryAttack(void);
	BOOL Deploy(void);
	BOOL CanDeploy(void);

	BOOL ShouldReload(int iClipIndex);
	void Reload(void);

	void WeaponIdle(void);

	void ItemPostFrame(void);
	void UpdateBodygroup(void);
	void PickupSound(void);
	void DropSound(void);

	int HUDIcon(void);
	int HUDActiveIcon(void);
	int ModeIcon(void);
	int ModeIcon2(void);
	int ModeIcon3(void);
	int SmallIcon(void);

	// Needed on every one to ensure these stay constant
	static weaponInfo m_weaponInfo; // Ammo Types used by the weapon, STATIC and as such is never saved
	weaponInfo* GetWeaponInfo(void) { return &m_weaponInfo; };

	static legalAmmoTypes m_legalAmmoIndicies; // Indices of ammo types used by the weapon. Note that -1 means index invalid
	int m_iAmmoIndices[2]; // Ammo indices currently loaded, the size of this must be equal to number of ammo types (not total number of ammo types)
	int m_iTargetAmmoIndex[2];

	legalAmmoTypes* GetLegalAmmoTypes(void) { return &m_legalAmmoIndicies; }; // Get all the legal ammo indices for this weapon
	int* GetAmmoIndexArray(void) { return m_iAmmoIndices; }; // Return array containing the ammo indices for each ammo slot
	int* GetTargetAmmoIndexArray(void) { return m_iTargetAmmoIndex; };
	BOOL UsesAmmo(void) { return TRUE; };

	// Unique functions
	BOOL WaterDischarge(void);

	float m_flNextAnimReset;
	float m_flNextSoundReset;

	BOOL InTarget(CBaseEntity* pTarget); // Check whether or not we already have this target
	BOOL InChain(CBaseEntity* pTarget); // Check whether we're already chaining this target
	BOOL ValidTarget(CBaseEntity* hTarget); // Check whether or not target pointed is valid
	void ClearTargets(int iTarget);
	EHANDLE pTargetOne[3]; // Latch targets
	EHANDLE pTargetTwo[3]; // Chain first targets
	EHANDLE pTargetThree[3]; // Chain chain *targets
	BOOL TargetExists(EHANDLE phTargetArray);
	int m_iNumTargets; // Number of targets acquired
	BOOL AcquireTargets(void); // Function that scans and acquires targets
	void DamageTargets(void); // Proceed to deal damage to targets

	CBeam* m_pBeams[9];
	float m_flBeamsTime;
	void MakeBeams(void);
	void ClearBeams(int iBeam);
	void UpdateBeamPosition(void);
	void BeamLogic(void);

	void RegularAttack(void);

	CLightningGun(void);

	virtual BOOL UseDecrement(void)
	{
#if defined( CLIENT_WEAPONS )
		return TRUE;
#else
		return FALSE;
#endif
	}
private:
	unsigned short m_usLight1;
	unsigned short m_usLight2;

};

void FindHullIntersection(const Vector& vecSrc, TraceResult& tr, float* mins, float* maxs, edict_t* pEntity);

#endif // WEAPONS_H
