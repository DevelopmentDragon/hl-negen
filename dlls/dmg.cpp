
#include "dmg.h"

bool UseMultiDamage( int dmg )
{
	if ( dmg == ID_DMG_SHOTGUN || dmg == ID_DMG_AUTOSHOTGUN || dmg == ID_DMG_SUPERSHOTGUN )
		return true;
	return false;
}

bool IsBullet( int bullet )
{
	switch(bullet)
	{
	case BULLET_9MM:
	case BULLET_9MMS:
	case BULLET_38SW:
	case BULLET_357:
	case BULLET_44SW:
	case BULLET_12G_SMALL:
	case BULLET_12G:
	case BULLET_25G:
	case BULLET_EXP:
	case BULLET_EXP_SMALL:
	case BULLET_EXP_INC:
	case BULLET_EXP_SMALL_INC:
	case BULLET_9MMH:
	case BULLET_9MMHS:
	case BULLET_9MMHE:
	case BULLET_9MMHES:
	case BULLET_22MM:
	case BULLET_5MM:
	case BULLET_556NATO:
	case BULLET_556NATOH:
	case BULLET_762NATOH:
	case BULLET_10MM:
	case BULLET_127MM:
	case BULLET_50C:
	case BULLET_762NATO:
	case BULLET_308:
	case BULLET_338:
	case BULLET_SENTRYTURRET:
	case BULLET_MINITURRET:
	case BULLET_TURRET:
		return true;
		break;
	default:
		return false;
		break;
	};
}

bool IsMeleeBullet( int bullet )
{
	switch(bullet)
	{
		case BULLET_MELEE_CROWBAR_NORM:
		case BULLET_MELEE_CROWBAR_CHARGED:
		case BULLET_MELEE_KNIFE_SLASH:
		case BULLET_MELEE_KNIFE_STAB:
		case BULLET_MELEE_PIPEWRENCH:
		case BULLET_MELEE_SPANNER:
		case BULLET_MELEE_SPORELAUNCHER_BITE:
		case BULLET_MELEE_SHOCKROACH_BITE:
			return true;
			break;
	}

	return false;
}

bool SupressTracer( int bullet )
{
	if ( IsBullet( bullet ) == false )
		return true;

	switch(bullet)
	{
	case BULLET_9MMS:
	case BULLET_9MMH:
	case BULLET_9MMHS:
	case BULLET_9MMHE:
	case BULLET_9MMHES:
	case BULLET_22MM:
	case BULLET_12G:
	case BULLET_25G:
	case BULLET_12G_SMALL:
	case BULLET_EXP:
	case BULLET_EXP_SMALL:
	case BULLET_EXP_INC:
	case BULLET_EXP_SMALL_INC:
		return true;
		break;
	default:
		return false;
		break;
	};
}

bool UsesPellets( int bullet )
{
	switch (bullet)
	{
	case BULLET_12G_SMALL:
	case BULLET_12G:
	case BULLET_25G:
	case BULLET_EXP:
	case BULLET_EXP_SMALL:
	case BULLET_EXP_INC:
	case BULLET_EXP_SMALL_INC:
		return true;
		break;
	default:
		return false;
		break;
	};
}

bool IsPowered(int armortype)
{
	if (armortype == ARMOR_NONE || armortype == ARMOR_BARN)
		return false;
	else
		return true;
}

// Generic damage
dmginfo_t dmgGeneric =
{
		ID_DMG_GENERIC, // id

		{0.0f,0.0f}, // critchance
		{1.0f,1.0f}, // critmult

		{0.0f,0.0f,0.0f,0.0f}, // penpower
		{1.0f,1.0f,1.0f,1.0f}, // penreduction
		{1.0f,1.0f,1.0f,1.0f}, // pendmgreduction
		{0.0f,0.0f,0.0f,0.0f}, // armorpen
		{0.0f,0.0f,0.0f,0.0f}, // armorshred
		{0.0f,0.0f,0.0f,0.0f}, // shieldpen
		{0.0f,0.0f,0.0f,0.0f}, // shieldshred

		{0.0f,0.0f,0.0f,0.0f}, // gibchance
		{0.0f,0.0f,0.0f,0.0f}, // gibthresh
		{0.0f,0.0f,0.0f,0.0f}, // gibmindist
		{0.0f,0.0f,0.0f,0.0f}, // gibmaxdist
		{0.0f,0.0f,0.0f,0.0f}, // gibultrachance
		{0.0f,0.0f,0.0f,0.0f}, // gibultrathresh
		{0.0f,0.0f,0.0f,0.0f}, // gibultramindist
		{0.0f,0.0f,0.0f,0.0f}, // gibultramaxdist
		{0.0f,0.0f,0.0f,0.0f}, // gibheadchance
		{0.0f,0.0f,0.0f,0.0f}, // gibheadthresh
		{0.0f,0.0f,0.0f,0.0f}, // gibheadmaxdist
		{0.0f,0.0f,0.0f,0.0f}, // gibheadultrachance
		{0.0f,0.0f,0.0f,0.0f}, // gibheadultrathresh
		{0.0f,0.0f,0.0f,0.0f}, // gibheadultramindist
		{0.0f,0.0f,0.0f,0.0f}, // gibheadultramaxdist
		{GIB_NEVER, GIB_NEVER, GIB_NORMAL, GIB_NORMAL}, // gibflags

		// Falloff and multishot stuff
		{0.0f, 0.0f, 0.0f, 0.0f}, // falloffmid
		{0.0f, 0.0f, 0.0f, 0.0f}, // falloffpos
		{0.0f, 0.0f, 0.0f, 0.0f}, // falloffneg
		{0.0f, 0.0f, 0.0f, 0.0f}, // multishotmult

		{ DOT_NONE, DOT_NONE, DOT_NONE, DOT_NONE }, // dotid
		{ 0.0f, 0.0f, 0.0f, 0.0f }, // dotchance
};

dmginfo_t dmgTelefrag =
{
	ID_DMG_TELEFRAG, // id

	{ 0.0f,0.0f }, // critchance
	{ 1.0f,1.0f }, // critmult

	{ 0.0f,0.0f,0.0f,0.0f }, // penpower
	{ 1.0f,1.0f,1.0f,1.0f }, // penreduction
	{ 1.0f,1.0f,1.0f,1.0f }, // pendmgreduction
	{ 0.0f,0.0f,0.0f,0.0f }, // armorpen
	{ 0.0f,0.0f,0.0f,0.0f }, // armorshred
	{ 0.0f,0.0f,0.0f,0.0f }, // shieldpen
	{ 0.0f,0.0f,0.0f,0.0f }, // shieldshred

	{ 100.0f,100.0f,100.0f,100.0f }, // gibchance
	{ 0.0f,0.0f,0.0f,0.0f }, // gibthresh
	{ 0.0f,0.0f,0.0f,0.0f }, // gibmindist
	{ 0.0f,0.0f,0.0f,0.0f }, // gibmaxdist
	{ 0.0f,0.0f,0.0f,0.0f }, // gibultrachance
	{ 0.0f,0.0f,0.0f,0.0f }, // gibultrathresh
	{ 0.0f,0.0f,0.0f,0.0f }, // gibultramindist
	{ 0.0f,0.0f,0.0f,0.0f }, // gibultramaxdist
	{ 0.0f,0.0f,0.0f,0.0f }, // gibheadchance
	{ 0.0f,0.0f,0.0f,0.0f }, // gibheadthresh
	{ 0.0f,0.0f,0.0f,0.0f }, // gibheadmaxdist
	{ 0.0f,0.0f,0.0f,0.0f }, // gibheadultrachance
	{ 0.0f,0.0f,0.0f,0.0f }, // gibheadultrathresh
	{ 0.0f,0.0f,0.0f,0.0f }, // gibheadultramindist
	{ 0.0f,0.0f,0.0f,0.0f }, // gibheadultramaxdist
	{ (GIB_NORMAL | GIB_ALWAYS | GIB_INSTANT), (GIB_NORMAL | GIB_ALWAYS | GIB_INSTANT), (GIB_NORMAL | GIB_ALWAYS | GIB_INSTANT), (GIB_NORMAL | GIB_ALWAYS | GIB_INSTANT) }, // gibflags

	// Falloff and multishot stuff
	{ 0.0f, 0.0f, 0.0f, 0.0f }, // falloffmid
	{ 0.0f, 0.0f, 0.0f, 0.0f }, // falloffpos
	{ 0.0f, 0.0f, 0.0f, 0.0f }, // falloffneg
	{ 0.0f, 0.0f, 0.0f, 0.0f }, // multishotmult

	{ DOT_NONE, DOT_NONE, DOT_NONE, DOT_NONE }, // dotid
	{ 0.0f, 0.0f, 0.0f, 0.0f }, // dotchance
};

dmginfo_t DmgInfo[ID_DMG_MAX];
