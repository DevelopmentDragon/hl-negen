#pragma once

#define DMG_IMAGE_LIFE		2	// seconds that image is up

// All Damage IDs for greater control of effects
enum dmg_ids
{

	ID_DMG_GENERIC = 0,

	// Weapons for Player and NPCs
	ID_DMG_CROWBAR_LIGHT, // Secondary fast attack for crowbar
	ID_DMG_CROWBAR_MEDIUM,
	ID_DMG_CROWBAR_HEAVY, // Primary slow attack for crowbar
	ID_DMG_CROWBAR_COUNTER,
	ID_DMG_CROWBAR_THROWN,

	ID_DMG_PIPEWRENCH_LIGHT,
	ID_DMG_PIPEWRENCH_MEDIUM,
	ID_DMG_PIPEWRENCH_HEAVY,
	ID_DMG_PIPEWRENCH_COUNTER,
	ID_DMG_PIPEWRENCH_THROWN,

	ID_DMG_KNIFE_LIGHT,
	ID_DMG_KNIFE_MEDIUM,
	ID_DMG_KNIFE_HEAVY,
	ID_DMG_KNIFE_COUNTER,
	ID_DMG_KNIFE_THROWN,

	ID_DMG_SPANNER_LIGHT,
	ID_DMG_SPANNER_MEDIUM,
	ID_DMG_SPANNER_HEAVY,
	ID_DMG_SPANNER_COUNTER,
	ID_DMG_SPANNER_THROWN,

	ID_DMG_GLOCK,
	ID_DMG_GLOCK_SILENCED,
	ID_DMG_M9,
	ID_DMG_PYTHON,
	ID_DMG_DEAGLE,

	ID_DMG_MP5,
	ID_DMG_MP5_GRENADE_HEAT,
	ID_DMG_MP5_GRENADE_BLAST,
	ID_DMG_MP5_GRENADE_SHRAPNEL,
	ID_DMG_M4, // M4 Round
	ID_DMG_M4_GRENADE_BLAST,
	ID_DMG_M4_GRENADE_IMPACT,
	ID_DMG_NAIL,
	ID_DMG_FIRENAIL,
	ID_DMG_SHOTGUN, // Standard Half-Life Shotgun Pellet
	ID_DMG_AUTOSHOTGUN,
	ID_DMG_SUPERSHOTGUN,

	ID_DMG_M249,
	ID_DMG_M60,
	ID_DMG_CHAINGUN,
	ID_DMG_MINIGUN,
	ID_DMG_GLAUNCHER_BLAST,
	ID_DMG_GLAUNCHER_IMPACT,
	ID_DMG_RPG_BLAST,
	ID_DMG_RPG_IMPACT,
	ID_DMG_ROCKETRIFLE_BLAST,
	ID_DMG_ROCKETRIFLE_SMALLBLAST,
	ID_DMG_ROCKETRIFLE_HEAT,
	ID_DMG_ROCKETRIFLE_SHRAPNEL,
	ID_DMG_QUAKE_BLAST,

	ID_DMG_FRAG_IMPACT,
	ID_DMG_FRAG_BLAST,
	ID_DMG_FRAG_HEAT,
	ID_DMG_FRAG_SHRAPNEL,
	ID_DMG_HE_IMPACT,
	ID_DMG_HE_BLAST,
	ID_DMG_HE_HEAT,
	ID_DMG_HE_SHRAPNEL,
	ID_DMG_FLASH_IMPACT,
	ID_DMG_FLASH_BLAST,
	ID_DMG_STUN_IMPACT,
	ID_DMG_STUN_BLAST,
	ID_DMG_FLARE_HIT,
	ID_DMG_FLARE_BURN,
	ID_DMG_TRIPMINE_BLAST,
	ID_DMG_TRIPMINE_SHRAPNEL,
	ID_DMG_TRIPMINE_GAS,
	ID_DMG_SATCHEL_BLAST,
	ID_DMG_SATCHEL_AP,

	ID_DMG_CROSSBOW_BOLT,
	ID_DMG_CROSSBOW_BOLT_ELITE,
	ID_DMG_CROSSBOW_BOLT_BLAST,
	ID_DMG_CROSSBOW_BOLT_ELITE_BLAST,
	ID_DMG_CROSSBOW_NEUROTOXIN,
	ID_DMG_M40A1,
	ID_DMG_AUTOSNIPER,
	ID_DMG_AUTOSNIPER_SUPER,

	ID_DMG_BARNACLE_BITE,
	ID_DMG_BARNACLE_CHOMP,
	ID_DMG_SHOCKROACH_HIT,
	ID_DMG_SHOCKROACH_BITE,
	ID_DMG_SHOCKROACH_BITESHOCK,
	ID_DMG_SHOCKROACH_TASER,
	ID_DMG_SHOCKROACH_WATERSHOCK,
	ID_DMG_HIVEHAND_HIT_NORMAL,
	ID_DMG_HIVEHAND_HIT_FAST,
	ID_DMG_HIVEHAND_CHOMP,
	ID_DMG_SNARK_BITE,
	ID_DMG_SNARK_BITE_ELITE,
	ID_DMG_SNARK_BLAST,
	ID_DMG_SPORE_DIRECTHIT,
	ID_DMG_SPORE_RADIUS,
	ID_DMG_SPORELAUNCHER_BITE,

	ID_DMG_RAIL,
	ID_DMG_RAIL_RADIUS,
	ID_DMG_RAIL_CHARGE,
	ID_DMG_RAIL_CHARGE_RADIUS,
	ID_DMG_RAIL_SUPER,
	ID_DMG_RAIL_RADIUS_SUPER,
	ID_DMG_RAIL_CHARGE_SUPER,
	ID_DMG_RAIL_CHARGE_RADIUS_SUPER,
	ID_DMG_FLAMETHROWER_STREAM,
	ID_DMG_FLAMETHROWER_FIREBALL,
	ID_DMG_GAUSS,
	ID_DMG_GAUSS_CHARGED,
	ID_DMG_GAUSS_RECOIL_CHARGED,
	ID_DMG_GAUSS_SELFSHOCK,
	ID_DMG_GAUSS_BLAST,
	ID_DMG_EGON_NARROW,
	ID_DMG_EGON_WIDE,
	ID_DMG_EGON_WIDE_RADIUS,
	ID_DMG_EGON_RELEASE,
	ID_DMG_DISPLACER_ZAP,
	ID_DMG_DISPLACER_BLAST,

	// NPCs
	ID_DMG_ZOMBIE_CLAW,
	ID_DMG_ZOMBIE_CLAWRAKE,

	ID_DMG_HEADCRAB_LUNGE,
	ID_DMG_HEADCRAB_BITE,
	ID_DMG_HEADCRAB_POISON,

	ID_DMG_GONOME_SLASH,
	ID_DMG_GONOME_CHOMP,
	ID_DMG_GONOME_LEAP,
	ID_DMG_GONOME_ACID,

	ID_DMG_GONARCH_CLAW,
	ID_DMG_GONARCH_MORTAR,

	ID_DMG_ISLAVE_CLAWSWIPE,
	ID_DMG_ISLAVE_CLAWRAKE,
	ID_DMG_ISLAVE_ZAP,

	ID_DMG_HGRUNT_KICK,
	ID_DMG_HGRUNT_KNIFE,
	ID_DMG_HGRUNT_PUNCH,

	ID_DMG_FASSN_KICK_SPARTA,
	ID_DMG_FASSN_KICK_STUN,
	ID_DMG_FASSN_KICK_DMG,

	ID_DMG_HOUNDEYE_SONICBLAST,

	ID_DMG_BULLSQUID_SPIT,
	ID_DMG_BULLSQUID_BITE,
	ID_DMG_BULLSQUID_WHIP,
	ID_DMG_BULLSQUID_THROW,

	ID_DMG_TENTACLE_HEAD_TOUCH,
	ID_DMG_TENTACLE_BODY_TOUCH,

	ID_DMG_LEECH_BITE,

	ID_DMG_ICKY_BITE,
	ID_DMG_ICKY_BITE_BABY,
	ID_DMG_ICKY_FATAL_CHOMP,

	ID_DMG_AGRUNT_SMASH,

	ID_DMG_CONTROLLER_ENERGYBOLT,
	ID_DMG_CONTROLLER_ENERGYBLAST,

	ID_DMG_NIHILANTH_BALLZAP,

	ID_DMG_APACHE_CRASH,

	ID_DMG_OSPREY_CRASH,

	ID_DMG_GARGANTUA_FLAMES,
	ID_DMG_GARGANTUA_STOMP,
	ID_DMG_GARGANTUA_SMASH,

	ID_DMG_AGRUNT_BHOLE,
	ID_DMG_AGRUNT_BRADIUS,

	// Func
	ID_DMG_FUNC_ROTATE_TOUCH,
	ID_DMG_FUNC_ROTATE_BLOCK,
	ID_DMG_FUNC_PENDULUM_TOUCH,
	ID_DMG_FUNC_TRACKTRAIN_BLOCK,
	ID_DMG_FUNC_TRAIN_BLOCK,
	ID_DMG_FUNC_PLAT_BLOCK,
	ID_DMG_FUNC_DOOR_BLOCK,
	ID_DMG_FUNC_BREAK_GLASS,

	ID_DMG_MORTAR_BLAST,
	ID_DMG_MORTAR_FRAG,

	ID_DMG_ENV_EXPLOSION,
	ID_DMG_ENV_ROPE_SHOCK,
	ID_DMG_ENV_BEAM_BURN,

	ID_DMG_LANDMINE,

	ID_DMG_TELEFRAG,

	ID_DMG_MAX,
};

enum heal_ids
{
	ID_HEAL_GENERIC = 0,

	ID_HEAL_SCIENTIST,
	ID_HEAL_AUTOMEDKIT,
	ID_HEAL_WALLMEDKIT,
	ID_HEAL_HEALTHBONUS,
	ID_HEAL_FUNC_DOOR,
	ID_HEAL_HEALTHKIT,
	ID_HEAL_HEALTHSPRAY,
	ID_HEAL_HEALTHBOX,
	ID_HEAL_HGRUNT,
	ID_HEAL_SODACAN,
	ID_HEAL_ISLAVE,
};

// bullet types
typedef	enum
{
	// GENERIC
	BULLET_NONE = 0, // no bullets
	BULLET_GENERIC, // generic for things that may require an impact

	// Crowbar
	BULLET_MELEE_CROWBAR_NORM,
	BULLET_MELEE_CROWBAR_CHARGED,

	BULLET_MELEE_KNIFE_SLASH,
	BULLET_MELEE_KNIFE_STAB,

	BULLET_MELEE_PIPEWRENCH,

	BULLET_MELEE_SPANNER,

	BULLET_MELEE_SPORELAUNCHER_BITE,

	BULLET_MELEE_SHOCKROACH_BITE,

	// HANDGUNS
	BULLET_9MM, // glock
	BULLET_9MMS, // glock silenced
	BULLET_38SW, // m9
	BULLET_357, // colt python
	BULLET_44SW, // desert eagle

	// SHOTGUNS
	BULLET_12G_SMALL, // shotgun
	BULLET_12G, // autoshotgun
	BULLET_25G, // double-barreled and hunting shotguns
	BULLET_EXP,
	BULLET_EXP_SMALL,
	BULLET_EXP_INC,
	BULLET_EXP_SMALL_INC,

	// SMGS
	BULLET_9MMH, // mp5
	BULLET_9MMHS,
	BULLET_9MMHE,
	BULLET_9MMHES,
	BULLET_22MM, // stealthgun
	BULLET_5MM, // assmg

	// RIFLES
	BULLET_556NATO, // m4

	// HEAVY
	BULLET_556NATOH, // m249
	BULLET_762NATOH, // m60
	BULLET_10MM, // chaingun
	BULLET_127MM, // minigun, apache gun
	BULLET_50C, // .50 cal

	// SNIPER RIFLES
	BULLET_762NATO, // m40a1
	BULLET_308,
	BULLET_338,

	// SPECIAL
	BULLET_SENTRYTURRET,
	BULLET_MINITURRET,
	BULLET_TURRET,
	
	// MELEE ATTACKS FOR NPCS
} Bullet;

// Is this damage type that of a bullet
bool DmgIsBullet( int dmg );

// Determines whether or not damage uses MultiDamage system (shotguns)
bool UseMultiDamage( int dmg );

// Is this bullet an actual hitscan bullet
bool IsBullet( int bullet );

// This is purely for decals, not using actual bullets
bool IsMeleeBullet( int bullet );

// Determines which bullet types suppress tracers
bool SupressTracer( int bullet );

// Determines whether or not this thing uses pellets
bool UsesPellets( int bullet );


// Gibbing here essentially means that all members of a monster or player will seperate or fly in a gory mess
// Ultra Gibbing is the same, albeit the chunks are more numerous and much smaller
// Headshots are for special cases with monsters that have heads can be decapitated or blown off (hyper gibbing)
// 

#define	GIB_NEVER					( 0 << 0 )  // Damage dealt will never gib or contribute to gibbing - N/A

#define GIB_NORMAL					( 1 << 0 )  // Gibbing is enabled, this flag is needed for any general gib - 0
#define GIB_ULTRA					( 1 << 1 ) // Ultra gib is enabled, this flag is needed for ultra gib - 1
#define	GIB_CONTRIBUTE				( 1 << 2 )  // Damage dealt will contribute to gibbing, but not gib - 2
#define GIB_THRESHOLD				( 1 << 3 )  // Damage dealt will only gib if damage threshold is passed - 3
#define GIB_THRESHOLD_ULTRA			( 1 << 4 )  // Damage dealt will only ultra gib  when threshold for ultra is passed - 4
#define GIB_RANDOM					( 1 << 5 ) // Whether gibbing is chance based - 5
#define GIB_RANDOM_ULTRA			( 1 << 6 ) // Whether ultra gibbing is chance based - 6
#define GIB_ALWAYS					( 1 << 7 )	// Always gibs on death - 7
#define GIB_INSTANT					( 1 << 8 ) // Override: this damage type will instantly gib - 8
#define GIB_SHARE_HEAD				( 1 << 9 ) // Whether damage dealt will be shared with head or not - 9

#define GIB_HEAD					( 1 << 10 )  // Damage type will chop or blow the victim's head right off - 10
#define GIB_HEAD_ULTRA				( 1 << 11 )
#define GIB_HEAD_CONTRIBUTE			( 1 << 12 )  // Damage type will contribute to head damage, but not blow it - 9
#define GIB_HEAD_THRESHOLD			( 1 << 13 )  // Damage type will blow head only with damage threshold - 10
#define GIB_HEAD_THRESHOLD_ULTRA	( 1 << 14 )
#define GIB_HEAD_RANDOM				( 1 << 15 )
#define GIB_HEAD_RANDOM_ULTRA		( 1 << 16 )
#define GIB_HEAD_ALWAYS				( 1 << 17 )  // Damage type will instantly gib head upon death - 11
#define GIB_HEAD_INSTANT			( 1 << 18 )  // Override: Damage type will instantly headshot no matter what - 12
#define GIB_HEAD_SHARE_BODY			( 1 << 19 )  // Any damage dealt with to head will be shared with body - 13

typedef enum
{
	DMG_INDEX_NORMAL = 0,
	DMG_INDEX_CRIT,
	DMG_INDEX_PENTAGRAM,
	DMG_INDEX_PENTRAGRAM_CRIT,
} dmgIndex_e;

// Each damage has its own set of information vital to the new damage system
// If the varriable in question is an array of size, the indices are FALSE and TRUE
// with that being whether or not we're going with the critical varriation or not.
// If absent, there is no possible critical varriation for that.
// If a varriable is to stay the same on either critical or non-critical,
// assign identical values at both indices
typedef struct dmginfo_s
{
	unsigned int id; // The id of the damage, this helps it uniquely identify it

	float critchance[2]; // Critical Damage Chance, chance for the damage type to be critical
	float critmult[2]; // Critical Damage Multiplier, damage multiplier for the critital strike

	float penpower[4]; // Penetration Power, unit compared to penetration resistance of entities and surfaces to see if the shot passes through to the next
	float penreduction[4]; // Penetration reduction per hammer unit
	float pendmgreduction[4]; // Penetration damage reduction, the amount the damage is reduced by with each hammer unit penetrated

	float armorpen[4]; // Armor penetration or how much of the armor is ignored. Note this means ignoring the armor's damage absorbtion
	float armorshred[4]; // Armor shred, percentage of the damage that is dealt exclusively to the armor, stacks atop of the split with the normal damage
	float shieldpen[4]; // Shield penetration, how much of the shield is ignored
	float shieldshred[4]; // Shield shred, percentage of the damage that is dealt exclusively to the shield, stacks atop of the split with the normal damage

	// Gib Stuff
	float gibchance[4];
	float gibthresh[4];
	float gibmindist[4];
	float gibmaxdist[4];
	float gibultrachance[4];
	float gibultrathresh[4];
	float gibultramindist[4];
	float gibultramaxdist[4];
	float gibheadchance[4];
	float gibheadthresh[4];
	float gibheadmaxdist[4];
	float gibheadultrachance[4];
	float gibheadultrathresh[4];
	float gibheadultramindist[4];
	float gibheadultramaxdist[4];
	unsigned int gibflags[4];

	// Falloff and multishot stuff
	float falloffmid[4];
	float falloffpos[4];
	float falloffneg[4];
	float multishotmult[4];

	unsigned int dotid[4];
	float dotchance[4];

} dmginfo_t;

extern dmginfo_t DmgInfo[ID_DMG_MAX];
void DAMAGE_Init(void);

// Armors
enum armors_e
{
	ARMOR_NONE = 0,
	ARMOR_HAZM,
	ARMOR_BARN,
	ARMOR_PCV,
	ARMOR_BOPS,
	ARMOR_HEV,
	ARMOR_HEV2,

	MAX_ARMOR_TYPE,
};

enum healths_e
{
	HEALTH_NONE = 0,
	HEALTH_HUMAN,
};

typedef struct healthinfo_s
{
	unsigned int id; // This is the id of the health, helps uniquely identity it
	int iconid; // Id for the icon to be used when representing it in the HUD
	int bloodcolor;

	float healthdefault;
	float healthmaxdefault;

} healthinfo_t;

typedef struct armorinfo_s
{
	unsigned int id; // The id of the armor, helps uniquely identifiy it
	int iconid; // Id for the icon to be used when representing it in the HUD

	float armordefault;
	float armordefaultmax;
	float armortempdefault;
	float armortempdefaultmax;

	float damagereduction; // Amount of damage reduced by the armor, reduction is applied before absorption
	float damageabsorption; // Percentage of the damage absorbed by the armor. Armor penetration affects this
	float thickness; // How much penetration power is required to pierce through the armor. This is added to a unit's base

} armorinfo_t;

enum shields_e
{
	SHIELD_NONE = 0,
	SHIELD_STANDARD, // Simply tank damage
	SHIELD_ABSORB, // Restore health, shields or armor based on damage recieved
	SHIELD_BOUNCE, // Bounce projectiles and hitscan back at enemy
	SHIELD_REFLECT, // Return damage to source and absorb
	SHIELD_SPELL, // Negates the effects of crowd control

};

typedef struct shieldinfo_s
{
	unsigned int id; // This is the id of the health, helps uniquely identity it
	float thickness;
} shieldinfo_t;

bool IsPowered(int armortype);

enum dot_ids
{
	DOT_NONE = 0,
	DOT_IGNITE_TEST,

	DOT_MAX_ID,
};

typedef enum
{
	DOT_ATTACK_ID = 0,
	DOT_DAMAGE_TYPE,

	DOT_INT_INFO_MAX,
} DotInfoInt;

typedef enum
{
	DOT_DAMAGE = 0,
	DOT_TIME,
	DOT_TICK,
	DOT_TICKTIMER,

	DOT_FLOAT_INFO_MAX,
} DotInfoFloat;
