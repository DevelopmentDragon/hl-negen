//========= Copyright © 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "weaponenum.h"

//========= Copyright © 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#pragma once

#ifndef CLIENT_DLL
// =========================== //
//           MELEE          //
// =========================== //

// Question
static const animinfo_t questionAnimInfo[QUESTION_LAST] =
{
	{ QUESTION_IDLE, 1, 30, true }
};

// Spanner
static const animinfo_t spannerAnimInfo[SPANNER_LAST] =
{
	{ SPANNER_IDLE1, 31, 15, true },
	{ SPANNER_ATTACK1, 16, 40, false },
	{ SPANNER_ATTACK2, 16, 40, false },
	{ SPANNER_USE, 16, 30, false },
	{ SPANNER_DRAW, 16, 30, false },
	{ SPANNER_HOLSTER, 16, 30, false }
};

// Knife
static const animinfo_t knifeAnimInfo[KNIFE_LAST] =
{
	{ KNIFE_IDLE1, 36, 13, true },
	{ KNIFE_IDLE2, 81, 15, true },
	{ KNIFE_IDLE3, 81, 15, true },
	{ KNIFE_ATTACK1MISS, 11, 22, false },
	{ KNIFE_ATTACK1HIT, 11, 22, false },
	{ KNIFE_ATTACK2MISS, 14, 22, false },
	{ KNIFE_ATTACK2HIT, 14, 22, false },
	{ KNIFE_ATTACK3MISS, 19, 24, false },
	{ KNIFE_ATTACK3HIT, 19, 24, false },
	{ KNIFE_CHARGE, 21, 30, false },
	{ KNIFE_STAB, 21, 30, false },
	{ KNIFE_DRAW, 13, 24, false },
	{ KNIFE_HOLSTER, 13, 24, false },
};

// Crowbar
static const animinfo_t crowbarAnimInfo[CROWBAR_LAST] =
{
	{ CROWBAR_IDLE1, 81, 15, true },
	{ CROWBAR_FIDGET1, 36, 13, false },
	{ CROWBAR_FIDGET2, 81, 15, false },
	{ CROWBAR_ATTACK1MISS, 11, 22, false },
	{ CROWBAR_ATTACK1HIT, 11, 22, false },
	{ CROWBAR_ATTACK2MISS, 14, 22, false },
	{ CROWBAR_ATTACK2HIT, 14, 22, false },
	{ CROWBAR_ATTACK3MISS, 19, 24, false },
	{ CROWBAR_ATTACK3HIT, 19, 24, false },
	{ CROWBAR_BIGATTACKWINDUP, 36, 30, false },
	{ CROWBAR_BIGATTACKMISS, 19, 30, false },
	{ CROWBAR_BIGATTACKHIT, 19, 25, false },
	{ CROWBAR_THROWWINDUP, 13, 20, false },
	{ CROWBAR_THROW, 13, 20, false },
	{ CROWBAR_BLOCKSTART, 17, 25, false },
	{ CROWBAR_BLOCKCOUNTER, 17, 25, false },
	{ CROWBAR_BLOCKCOUNTERHIT, 14, 20, false },
	{ CROWBAR_BLOCKEND, 17, 25, false },
	{ CROWBAR_BLOCKBREAK, 28, 30, false },
	{ CROWBAR_TOOLSTART, 11, 20, false },
	{ CROWBAR_TOOLLOOP, 11, 20, true },
	{ CROWBAR_TOOLEND, 11, 20, false },
	{ CROWBAR_DRAW, 13, 24, false },
	{ CROWBAR_HOLSTER, 13, 24, false },
};

// Pipewrench
static const animinfo_t pipewrenchAnimInfo[PIPEWRENCH_LAST] =
{
	{ PIPEWRENCH_IDLE1, 91, 30, true },
	{ PIPEWRENCH_FIDGET1, 61, 30, false },
	{ PIPEWRENCH_FIDGET2, 91, 30, false },
	{ PIPEWRENCH_ATTACK1MISS, 28, 30, false },
	{ PIPEWRENCH_ATTACK1HIT, 23, 30, false },
	{ PIPEWRENCH_ATTACK2MISS, 23, 30, false },
	{ PIPEWRENCH_ATTACK2HIT, 23, 30, false },
	{ PIPEWRENCH_ATTACK3MISS, 23, 30, false },
	{ PIPEWRENCH_ATTACK3HIT, 18, 30, false },
	{ PIPEWRENCH_ATTACKBIGWIND, 27, 30, false },
	{ PIPEWRENCH_ATTACKBIGMISS, 30, 30, false },
	{ PIPEWRENCH_ATTACKBIGHIT, 29, 30, false },
	{ PIPEWRENCH_DRAW, 21, 30, false },
	{ PIPEWRENCH_HOLSTER, 21, 30, false },
};

// =========================== //
//           HANDGUNS          //
// =========================== //

// Glock-17
static const animinfo_t glockAnimInfo[GLOCK_LAST] =
{
	{ GLOCK_IDLE1, 50, 14, true },
	{ GLOCK_IDLE1_EMPTY, 50, 14, true },
	{ GLOCK_FIDGET1, 61, 14, false },
	{ GLOCK_FIDGET1_EMPTY, 61, 14, false },
	{ GLOCK_SHOOT, 15, 30, false },
	{ GLOCK_SHOOT_EMPTY, 15, 25, false },
	{ GLOCK_SHOOT2, 15, 25, false },
	{ GLOCK_SHOOT_EMPTY2, 15, 25, false },
	{ GLOCK_HOLSTER_FROM_SILENCER, 11, 18, false },
	{ GLOCK_HOLSTER_FROM_SILENCER_EMPTY, 11, 18, false },
	{ GLOCK_ADD_SILENCER, 51, 18, false },
	{ GLOCK_ADD_SILENCER_EMPTY, 51, 18, false },
	{ GLOCK_REMOVE_SILENCER, 51, 18, false },
	{ GLOCK_REMOVE_SILENCER_EMPTY, 51, 18, false },
	{ GLOCK_DRAW_FROM_SILENCER, 11, 18, false },
	{ GLOCK_DRAW_FROM_SILENCER_EMPTY, 11, 18, false },
	{ GLOCK_RELOAD, 25, 18, false },
	{ GLOCK_RELOAD_EMPTY, 36, 18, false },
	{ GLOCK_RELOAD2, 42, 30, false },
	{ GLOCK_RELOAD_EMPTY2, 42, 30, false },
	{ GLOCK_SWITCH, 41, 28, false },
	{ GLOCK_SWITCH_EMPTY, 41, 28, false },
	{ GLOCK_DRAW, 16, 16, false },
	{ GLOCK_DRAW_EMPTY, 16, 16, false },
	{ GLOCK_HOLSTER, 16, 16, false },
	{ GLOCK_HOLSTER_EMPTY, 16, 16, false },
	{ GLOCK_DRAW2, 16, 16, false },
	{ GLOCK_DRAW_EMPTY2, 16, 16, false },
	{ GLOCK_HOLSTER2, 16, 16, false },
	{ GLOCK_HOLSTER_EMPTY2, 16, 16, false },
};

// Beretta
static const animinfo_t m9AnimInfo[M9_LAST] =
{
	{ M9_IDLE, 48, 14, true },
	{ M9_IDLE_EMPTY, 48, 14, true },
	{ M9_SHOOT, 20, 28, false },
	{ M9_SHOOT_EMPTY, 20, 28, false },
	{ M9_RELOAD, 42, 25, false },
	{ M9_RELOAD_EMPTY, 42, 25, false },
	{ M9_SWITCH, 41, 41, false },
	{ M9_SWITCH_EMPTY, 41, 41, false },
	{ M9_DRAW, 16, 20, false },
	{ M9_DRAW_EMPTY, 16, 20, false },
	{ M9_HOLSTER, 16, 20, false },
	{ M9_HOLSTER_EMPTY, 16, 20, false },
};

// Colt Python
static const animinfo_t pythonAnimInfo[PYTHON_LAST] =
{
	{ PYTHON_IDLE1, 71, 30, true },
	{ PYTHON_IDLE2, 16, 20, true },
	{ PYTHON_FIDGET, 171, 30, false },
	{ PYTHON_FIRE1, 30, 30, false },
	{ PYTHON_FIRE2, 31, 30, false },
	{ PYTHON_RELOAD, 111, 36, false },
	{ PYTHON_SIGHT, 61, 30, false },
	{ PYTHON_DRAW, 16, 30, false },
	{ PYTHON_HOLSTER, 16, 30, false },
};

// Desert Eagle
static const animinfo_t deagleAnimInfo[DEAGLE_LAST] =
{
	{ DEAGLE_IDLE, 50, 30, true },
	{ DEAGLE_SPECIAL_IDLE1, 76, 30, false },
	{ DEAGLE_SPECIAL_IDLE2, 75, 30, false },
	{ DEAGLE_SPECIAL_IDLE3, 61, 30, false },
	{ DEAGLE_SHOOT, 20, 30, false },
	{ DEAGLE_SHOOT_LAST, 20, 27, false },
	{ DEAGLE_RELOAD, 42, 25, false },
	{ DEAGLE_RELOAD_EMPTY, 42, 25, false },
	{ DEAGLE_SIGHT, 61, 48, false },
	{ DEAGLE_DRAW, 16, 18, false },
	{ DEAGLE_HOLSTER, 16, 22, false },
};

// =========================== //
// AUTOMATICS & SHOTGUNS       //
// =========================== //

// MP5-SD
static const animinfo_t mp5AnimInfo[MP5_LAST] = 
{
	{ MP5_IDLE, 41, 8, true },
	{ MP5_FIDGET, 111, 35, false },
	{ MP5_FIRE1, 7, 10, false },
	{ MP5_FIRE2, 7, 10, false },
	{ MP5_FIRE3, 7, 10, false },
	{ MP5_FIRE_SD1, 7, 10, false },
	{ MP5_FIRE_SD2, 7, 10, false },
	{ MP5_FIRE_SD3, 7, 10, false },
	{ MP5_FIRE_ELITE1, 7, 10, false },
	{ MP5_FIRE_ELITE2, 7, 10, false },
	{ MP5_FIRE_ELITE3, 7, 10, false },
	{ MP5_FIRE_ELITE_SD1, 7, 10, false },
	{ MP5_FIRE_ELITE_SD2, 7, 10, false },
	{ MP5_FIRE_ELITE_SD3, 7, 10, false },
	{ MP5_GRENADE, 34, 30, false },
	{ MP5_SWING, 11, 15, false },
	{ MP5_RELOAD, 47, 25, false },
	{ MP5_RELOAD_EMPTY, 63, 25, false },
	{ MP5_RELOAD_EMPTY_COCK, 69, 25, false },
	{ MP5_SWITCH_UP, 11, 25, false },
	{ MP5_SWITCH_DOWN, 11, 25, false },
	{ MP5_DRAW, 12, 12, false },
	{ MP5_HOLSTER, 12, 12, false },
};

// M4
static const animinfo_t m4AnimInfo[M4_LAST] =
{
	{ M4_IDLE, 41, 8, true },
	{ M4_FIDGET, 111, 35, false },
	{ M4_FIRE1, 7, 10, false },
	{ M4_FIRE2, 7, 10, false },
	{ M4_FIRE3, 7, 10, false },
	{ M4_GRENADE, 34, 30, false },
	{ M4_RELOAD, 47, 30, false },
	{ M4_RELOAD_EMPTY, 61, 30, false },
	{ M4_DRAW, 12, 30, false },
	{ M4_HOLSTER, 12, 30, false },
};

// Nailgun
static const animinfo_t nailgunAnimInfo[NAILGUN_LAST] =
{
	{ NAILGUN_IDLE, 36, 8, true },
	{ NAILGUN_FIDGET, 59, 20, false },
	{ NAILGUN_FIRE1, 16, 60, false },
	{ NAILGUN_FIRE2, 16, 45, false },
	{ NAILGUN_FIRE3, 16, 50, false },
	{ NAILGUN_RELOAD, 51, 30, false },
	{ NAILGUN_RELOAD_EMPTY, 66, 30, false },
	{ NAILGUN_DRAW, 16, 30, false },
	{ NAILGUN_HOLSTER, 16, 30, false },
	{ SUPERNAILGUN_IDLE, 36, 8, true },
	{ SUPERNAILGUN_FIDGET, 59, 20, false },
	{ SUPERNAILGUN_FIRE1, 16, 60, false },
	{ SUPERNAILGUN_FIRE2, 16, 45, false },
	{ SUPERNAILGUN_FIRE3, 16, 50, false },
	{ SUPERNAILGUN_RELOAD, 51, 30, false },
	{ SUPERNAILGUN_RELOAD_EMPTY, 66, 30, false },
	{ SUPERNAILGUN_DRAW, 16, 30, false },
	{ SUPERNAILGUN_HOLSTER, 16, 30, false },
};

// Shotgun
static const animinfo_t shotgunAnimInfo[SHOTGUN_LAST] =
{
	{ SHOTGUN_IDLE1, 21, 9, true },
	{ SHOTGUN_IDLE2, 61, 12, true },
	{ SHOTGUN_FIDGET1, 21, 9, false },
	{ SHOTGUN_FIDGET2, 61, 12, false },
	{ SHOTGUN_FIRE, 21, 23, false },
	{ SHOTGUN_FIRE_RAPID, 18, 23, false },
	{ SHOTGUN_FIRE_DOUBLE, 21, 16, false },
	{ SHOTGUN_FIRE_DOUBLE_RAPID, 20, 23, false },
	{ SHOTGUN_RELOAD_START, 9, 20, false },
	{ SHOTGUN_RELOAD_MID, 11, 23, false },
	{ SHOTGUN_RELOAD_END, 9, 20, false },
	{ SHOTGUN_RELOAD_PUMP, 11, 16, false },
	{ SHOTGUN_DRAW, 13, 24, false },
	{ SHOTGUN_HOLSTER, 13, 24, false },
};

// SPAS-12
static const animinfo_t autoshotgunAnimInfo[AUTOSHOTGUN_LAST] =
{
	{ AUTOSHOTGUN_IDLE, 21, 9, true },
	{ AUTOSHOTGUN_FIDGET, 21, 9, false },
	{ AUTOSHOTGUN_PUMPSHOOT, 28, 42, false },
	{ AUTOSHOTGUN_SEMISHOOT, 7, 15, false },
	{ AUTOSHOTGUN_AUTOSHOOT, 7, 15, false },
	{ AUTOSHOTGUN_SWITCH, 21, 44, false },
	{ AUTOSHOTGUN_RELOAD_START, 9, 27, false },
	{ AUTOSHOTGUN_RELOAD_MID, 10, 27, false },
	{ AUTOSHOTGUN_RELOAD_END, 9, 27, false },
	{ AUTOSHOTGUN_RELOAD_PUMP, 30, 44, false },
	{ AUTOSHOTGUN_DRAW, 13, 24, false },
	{ AUTOSHOTGUN_HOLSTER, 13, 24, false },
};

// Doubled Barreled Shotgun
static const animinfo_t supershotgunAnimInfo[SUPERSHOTGUN_LAST] =
{
	{ SUPERSHOTGUN_IDLE, 11, 30, true },
	{ SUPERSHOTGUN_FIRERIGHT, 11, 25, false },
	{ SUPERSHOTGUN_FIRERIGHTRELOAD, 31, 25, false },
	{ SUPERSHOTGUN_FIRELEFT, 11, 25, false },
	{ SUPERSHOTGUN_FIRELEFTRELOAD, 31, 25, false },
	{ SUPERSHOTGUN_FIREDOUBLE, 11, 25, false },
	{ SUPERSHOTGUN_FIREDOUBLERELOAD, 31, 25, false },
	{ SUPERSHOTGUN_RELOAD, 21, 25, false },
	{ SUPERSHOTGUN_DRAW, 11, 15, false },
	{ SUPERSHOTGUN_HOLSTER, 11, 15, false },
};

static const animinfo_t huntingshotgunAnimInfo[HUNTINGSHOTGUN_LAST] =
{
	{ HUNTINGSHOTGUN_IDLE, 21, 11, true },
	{ HUNTINGSHOTGUN_FIDGET, 21, 8, false },
	{ HUNTINGSHOTGUN_FIRE, 31, 30, false },
	{ HUNTINGSHOTGUN_FIRE2, 27, 27, false },
	{ HUNTINGSHOTGUN_FIRE3, 39, 39, false },
	{ HUNTINGSHOTGUN_RELOAD_START, 11, 24, false },
	{ HUNTINGSHOTGUN_RELOAD_MID, 9, 24, false },
	{ HUNTINGSHOTGUN_RELOAD_END, 11, 24, false },
	{ HUNTINGSHOTGUN_RELOAD_PUMP, 20, 24, false },
	{ HUNTINGSHOTGUN_DRAW, 13, 24, false },
	{ HUNTINGSHOTGUN_HOLSTER, 13, 24, false },
};

// =========================== //
//         HEAVY WEAPONS       //
// =========================== //

// Grenade Launcher
static const animinfo_t glauncherAnimInfo[GLAUNCHER_LAST] =
{
	{ GLAUNCHER_IDLE, 41, 8, true },
	{ GLAUNCHER_FIDGET, 25, 10, false },
	{ GLAUNCHER_FIRE, 12, 20, false },
	{ GLAUNCHER_FIRE_ARM, 16, 20, false },
	{ GLAUNCHER_DETONATE, 12, 20, false },
	{ GLAUNCHER_SWITCH, 16, 20, false },
	{ GLAUNCHER_RELOAD, 47, 25, false },
	{ GLAUNCHER_RELOAD_EMPTY, 67, 25, false },
	{ GLAUNCHER_DRAW, 16, 15, false },
	{ GLAUNCHER_HOLSTER, 16, 15, false },
};

// RPG
static const animinfo_t rpgAnimInfo[RPG_LAST] =
{
	{ RPG_IDLE, 91, 15, true },
	{ RPG_IDLE2, 91, 15, true },
	{ RPG_FIDGET, 91, 15, false },
	{ RPG_FIDGET2, 91, 15, false },
	{ RPG_FIRE, 25, 30, false },
	{ RPG_RELOAD, 61, 30, false },
	{ RPG_DRAW, 16, 30, false },
	{ RPG_DRAW2, 16, 30, false },
	{ RPG_HOLSTER, 16, 30, false },
	{ RPG_HOLSTER2,	16, 30, false },
};

// Rocket Rifle
static const animinfo_t rocketrifleAnimInfo[ROCKETRIFLE_LAST] =
{
	{ ROCKETRIFLE_IDLE, 25, 5, true },
	{ ROCKETRIFLE_IDLE_EMPTY, 25, 5, true },
	{ ROCKETRIFLE_FIDGET, 35, 10, false },
	{ ROCKETRIFLE_FIDGET_EMPTY, 35, 10, false },
	{ ROCKETRIFLE_FIRE, 13, 15, false },
	{ ROCKETRIFLE_FIRE_EMPTY, 13, 15, false },
	{ ROCKETRIFLE_JUMP, 13, 15, false },
	{ ROCKETRIFLE_JUMP_EMPTY, 13, 15, false },
	{ ROCKETRIFLE_RELOAD_START, 19, 20, false },
	{ ROCKETRIFLE_RELOAD_START_EMPTY, 19, 20, false },
	{ ROCKETRIFLE_RELOAD_INSERT, 21, 20, false },
	{ ROCKETRIFLE_RELOAD_INSERT_LAST, 25, 20, false },
	{ ROCKETRIFLE_RELOAD_INTERUPT, 19, 20, false },
	{ ROCKETRIFLE_RELOAD_INTERUPT_EMPTY, 19, 20, false },
	{ ROCKETRIFLE_DRAW, 16, 15, false },
	{ ROCKETRIFLE_DRAW_EMPTY, 16, 15, false },
	{ ROCKETRIFLE_HOLSTER, 16, 20, false },
	{ ROCKETRIFLE_HOLSTER_EMPTY, 16, 20, false },
	{ ROCKETRIFLE_ZOOM, 2, 1, true },
};

// M249 SAW
static const animinfo_t m249AnimInfo[M249_LAST] =
{
	{ M249_IDLE, 101, 20, true },
	{ M249_FIDGET, 155, 25, false },
	{ M249_FIRE_LOW, 7, 30, false },
	{ M249_FIRE_MED, 7, 30, false },
	{ M249_FIRE_HIGH, 7, 30, false },
	{ M249_BOXOUT, 61, 40, false },
	{ M249_BOXIN, 111, 45, false },
	{ M249_DRAW, 31, 30, false },
	{ M249_HOLSTER, 29, 30, false },
};

// M60
static const animinfo_t m60AnimInfo[M60_LAST] =
{
	{ M60_IDLE, 31, 15, true },
	{ M60_FIRE, 5, 30, false },
	{ M60_DRAW, 16, 30, false },
	{ M60_HOLSTER, 16, 30, false },
};


// Chaingun
static const animinfo_t chaingunAnimInfo[CHAINGUN_LAST] =
{
	{ CHAINGUN_IDLE, 41, 10, true },
	{ CHAINGUN_IDLE2, 51, 16, true },
	{ CHAINGUN_SPINUP, 17, 18, false },
	{ CHAINGUN_SPINDOWN, 33, 32, false },
	{ CHAINGUN_FIRE, 33, 33, false },
	{ CHAINGUN_DRAW, 17, 32, false },
	{ CHAINGUN_HOLSTER, 17, 32, false },
};

// =========================== //
//         RANGED WEAPONS      //
// =========================== //

// Auto-Crossbow
static const animinfo_t crossbowAnimInfo[CROSSBOW_LAST] =
{
	{ CROSSBOW_IDLE, 91, 30, true },
	{ CROSSBOW_IDLE_EMPTY, 91, 30, true },
	{ CROSSBOW_FIDGET, 81, 30, false },
	{ CROSSBOW_FIDGET_EMPTY, 81, 30, false },
	{ CROSSBOW_FIRE, 91, 60, false },
	{ CROSSBOW_FIRE_EMPTY, 16, 30, false },
	{ CROSSBOW_FIRE_RAPID, 16, 30, false },
	{ CROSSBOW_TORQUE, 91, 45, false },
	{ CROSSBOW_RELOAD, 61, 30, false },	// from non-empty
	{ CROSSBOW_RELOAD_EMPTY, 136, 30, false },	// from empty
	{ CROSSBOW_DRAW, 16, 30, false }, // full
	{ CROSSBOW_DRAW_EMPTY, 16, 30, false },	// empty
	{ CROSSBOW_HOLSTER, 16, 30, false },	// full
	{ CROSSBOW_HOLSTER_EMPTY, 16, 30, false },	// empty
};

// M40A1 Sniper Rifle
static const animinfo_t m40a1AnimInfo[M40A1_LAST] =
{
	{ M40A1_IDLE, 101, 33, true },
	{ M40A1_IDLE_EMPTY, 101, 33, true },
	{ M40A1_FIRE, 68, 48, false },
	{ M40A1_FIRE_EMPTY, 68, 48, false },
	{ M40A1_RELOAD, 80, 40, false },
	{ M40A1_RELOAD_EMPTY, 129, 40, false },
	{ M40A1_DRAW, 31, 30, false },
	{ M40A1_DRAW_EMPTY, 31, 30, false },
	{ M40A1_HOLSTER, 31, 30, false },
	{ M40A1_HOLSTER_EMPTY, 31, 30, false },
};

// Autosniper
static const animinfo_t autosniperAnimInfo[AUTOSNIPER_LAST] =
{
	{ AUTOSNIPER_AUTO_IDLE, 41, 15, true },
	{ AUTOSNIPER_AUTO_FIDGET, 41, 15, false },
	{ AUTOSNIPER_AUTO_FIRE, 11, 20, false },
	{ AUTOSNIPER_AUTO_RELOAD, 45, 20, false },
	{ AUTOSNIPER_AUTO_RELOAD_EMPTY, 61, 20, false },
	{ AUTOSNIPER_AUTO_SWITCH, 49, 20, false },
	{ AUTOSNIPER_AUTO_SWITCH_EMPTY, 35, 20, false },
	{ AUTOSNIPER_AUTO_DRAW, 13, 15, false },
	{ AUTOSNIPER_AUTO_HOLSTER, 13, 15, false },
	{ AUTOSNIPER_BOLT_IDLE, 41, 15, true },
	{ AUTOSNIPER_BOLT_FIDGET, 41, 15, false },
	{ AUTOSNIPER_BOLT_FIRE, 11, 20, false },
	{ AUTOSNIPER_BOLT_RELOAD, 61, 25, false },
	{ AUTOSNIPER_BOLT_SWITCH, 48, 20, false },
	{ AUTOSNIPER_BOLT_SWITCH_EMPTY, 25, 20, false },
	{ AUTOSNIPER_BOLT_DRAW, 13, 15, false },
	{ AUTOSNIPER_BOLT_HOLSTER, 13, 15, false },
	{ AUTOSNIPER_ZOOM, 1, 1, true },
};

// =========================== //
//    THROWABLE/EXPLOSIVES      //
// =========================== //

// Hand Grenades
static const animinfo_t handgrenadeAnimInfo[HANDGRENADE_LAST] =
{
	{ HANDGRENADE_IDLE, 91, 30, true },
	{ HANDGRENADE_FIDGET, 91, 30, false },
	{ HANDGRENADE_PINPULL, 25, 45, false },
	{ HANDGRENADE_THROW_SOFT, 12, 24, false },
	{ HANDGRENADE_THROW_NORMAL,	16, 24, false },
	{ HANDGRENADE_THROW_HARD, 19, 30, false },
	{ HANDGRENADE_HOLSTER, 16, 30, false },
	{ HANDGRENADE_DRAW, 16, 30, false },
	{ HANDGRENADE_NULL, 1, 1, true },
};

// Tripmine
static const animinfo_t tripmineAnimInfo[TRIPMINE_LAST] =
{
	{ TRIPMINE_IDLE1, 91, 30, true },
	{ TRIPMINE_IDLE2, 61, 30, true },
	{ TRIPMINE_FIDGET, 101, 30, false },
	{ TRIPMINE_PLACE, 11, 30, false },
	{ TRIPMINE_PLACE2, 24, 60, false },
	{ TRIPMINE_TIMER, 65, 60, false },
	{ TRIPMINE_DRAW, 16, 30, false },
	{ TRIPMINE_HOLSTER, 16, 30, false },
	{ TRIPMINE_NULL, 1, 1, false },
};

// Satchel Charge
static const animinfo_t satchelAnimInfo[SATCHEL_LAST] =
{
	{ SATCHEL_IDLE, 81, 20, true },
	{ SATCHEL_FIDGET, 111, 30, false },
	{ SATCHEL_PREPTHROW, 16, 40, false },
	{ SATCHEL_THROW, 16, 30, false },
	{ SATCHEL_SET, 11, 30, false },
	{ SATCHEL_FIRE, 31, 30, false },
	{ SATCHEL_REDRAW, 61, 40, false },
	{ SATCHEL_DRAW, 61, 40, false },
	{ SATCHEL_HOLSTER, 61, 40, false },
	{ SATCHEL_RADIO_IDLE, 81, 30, false },
	{ SATCHEL_RADIO_FIDGET, 111, 30, false },
	{ SATCHEL_RADIO_FIRE, 31, 30, false },
	{ SATCHEL_RADIO_DRAW, 31, 30, false },
	{ SATCHEL_RADIO_HOLSTER, 16, 30, false },
};

// =========================== //
//    ALIEN WEAPONS			 //
// =========================== //

// Hivehand
static const animinfo_t hgunAnimInfo[HGUN_LAST] =
{
	{ HGUN_IDLE1, 31, 16, true },
	{ HGUN_FIDGETSWAY, 41, 16, false },
	{ HGUN_FIDGETSHAKE, 36, 16, false },
	{ HGUN_DOWN, 19, 16, false },
	{ HGUN_UP, 31, 30, false },
	{ HGUN_SHOOT, 11, 24, false },
};

// Shock Roach
static const animinfo_t shockroachAnimInfo[SHOCKROACH_LAST] =
{
	{ SHOCKROACH_IDLE, 51, 15, true },
	{ SHOCKROACH_FIDGET, 101, 30, false },
	{ SHOCKROACH_FIRE, 11, 30, false },
	{ SHOCKROACH_FIRESUPER, 11, 30, false },
	{ SHOCKROACH_FIRESUPERLAST, 11, 30, false },
	{ SHOCKROACH_BITE, 11, 30, false },
	{ SHOCKROACH_BITESUPER, 13, 30, false },
	{ SHOCKROACH_BITESUPERLAST, 13, 30, false },
	{ SHOCKROACH_START, 7, 30, false },
	{ SHOCKROACH_LOOP, 21, 30, true },
	{ SHOCKROACH_END, 4, 30, false },
	{ SHOCKROACH_DRAW, 31, 30, false },
	{ SHOCKROACH_DRAWSUPER, 38, 30, false },
	{ SHOCKROACH_HOLSTER, 26, 30, false },
	{ SHOCKROACH_HOLSTERSUPER, 30, 30, false },
};

// Spore Launcher
static const animinfo_t sporelauncherAnimInfo[SPORELAUNCHER_LAST] =
{
	{ SPORELAUNCHER_IDLE1, 61, 30, true },
	{ SPORELAUNCHER_FIDGET1, 121, 30, false },
	{ SPORELAUNCHER_FIDGET2, 121, 30, false },
	{ SPORELAUNCHER_FIRE, 16, 30, false },
	{ SPORELAUNCHER_ALTFIRE, 16, 30, false },
	{ SPORELAUNCHER_BITE, 16, 20, false },
	{ SPORELAUNCHER_START_RELOAD, 21, 30, false },
	{ SPORELAUNCHER_MID_RELOAD, 31, 30, false },
	{ SPORELAUNCHER_END_RELOAD, 26, 30, false },
	{ SPORELAUNCHER_DRAW, 31, 30, false },
	{ SPORELAUNCHER_HOLSTER, 31, 30, false },
};



// Snark
static const animinfo_t squeakAnimInfo[SQUEAK_LAST] =
{
	{ SQUEAK_IDLE1, 31, 16, true },
	{ SQUEAK_FIDGETFIT, 71, 16, false },
	{ SQUEAK_FIDGETNIP, 81, 16, false },
	{ SQUEAK_DOWN, 21, 16, false },
	{ SQUEAK_UP, 51, 30, false },
	{ SQUEAK_THROW, 14, 24, false },
};



// =========================== //
//    ENERGY WEAPONS			//
// =========================== //

static const animinfo_t railgunAnimInfo[RAILGUN_LAST] =
{
	{ RAILGUN_IDLE, 31, 10, true },
	{ RAILGUN_FIDGET, 31, 20, false },
	{ RAILGUN_FIRE, 13, 30, false },
	{ RAILGUN_FIRE2, 9, 20, false },
	{ RAILGUN_FIREALT, 17, 30, false },
	{ RAILGUN_FIREALT2, 17, 30, false },
	{ RAILGUN_RELOAD, 41, 20, false },
	{ RAILGUN_RELOAD_EMPTY, 41, 20, false },
	{ RAILGUN_CHARGE, 51, 30, false },
	{ RAILGUN_CHARGE2, 51, 28, false },
	{ RAILGUN_SWITCH, 21, 20, false },
	{ RAILGUN_DRAW, 16, 20, false },
	{ RAILGUN_HOLSTER, 16, 20, false },
};

// Plasma Gun
static const animinfo_t plasmarifleAnimInfo[PLASMARIFLE_LAST] =
{
	{ PLASMARIFLE_IDLE, 41, 8, true },
	{ PLASMARIFLE_FIDGET, 111, 35, false },
	{ PLASMARIFLE_FIRE1, 7, 10, false },
	{ PLASMARIFLE_FIRE2, 7, 10, false },
	{ PLASMARIFLE_FIRE3, 7, 10, false },
	{ PLASMARIFLE_GRENADE, 34, 30, false },
	{ PLASMARIFLE_RELOAD, 47, 30, false },
	{ PLASMARIFLE_RELOAD_EMPTY, 61, 30, false },
	{ PLASMARIFLE_DRAW, 12, 30, false },
	{ PLASMARIFLE_HOLSTER, 12, 30, false },
};

// Gauss Gun - Tau Cannon
static const animinfo_t gaussAnimInfo[GAUSS_LAST] =
{
	{ GAUSS_IDLE, 61, 15, true },
	{ GAUSS_FIDGET, 91, 30, false },
	{ GAUSS_FIRE, 31, 41, false },
	{ GAUSS_FIRE2, 41, 30, false },
	{ GAUSS_SPINUP, 31, 30, false },
	{ GAUSS_SPIN, 16, 30, true },
	{ GAUSS_SWITCH, 61, 61, false },
	{ GAUSS_DRAW, 36, 60, false },
	{ GAUSS_HOLSTER, 31, 45, false },
	{ GAUSS_IDLE_HANDLE, 61, 15, true },
	{ GAUSS_FIDGET_HANDLE, 71, 30, false },
	{ GAUSS_FIRE_HANDLE, 31, 41, false },
	{ GAUSS_FIRE2_HANDLE, 31, 30, false },
	{ GAUSS_SPINUP_HANDLE, 31, 30, false },
	{ GAUSS_SPIN_HANDLE, 16, 30, true },
	{ GAUSS_SWITCH_HANDLE, 46, 46, false },
	{ GAUSS_DRAW_HANDLE, 36, 64, false },
	{ GAUSS_HOLSTER_HANDLE, 31, 60, false },
};

// Gluon Gun
static const animinfo_t egonAnimInfo[EGON_LAST] =
{
	{ EGON_IDLE1, 61, 30, true },
	{ EGON_FIDGET1, 81, 30, false },
	{ EGON_FIRE1, 16, 30, true },
	{ EGON_FIRE2, 16, 30, true },
	{ EGON_FIRE3, 16, 30, true },
	{ EGON_FIRE4, 16, 30, true },
	{ EGON_FIRE5, 16, 30, true },
	{ EGON_SWITCH, 16, 30, false },
	{ EGON_DRAW, 16, 30, false },
	{ EGON_HOLSTER, 16, 30, false },
	{ EGON_ALTIDLE1, 61, 30, true },
	{ EGON_ALTFIDGET1, 11, 20, false },
	{ EGON_ALTFIRE1, 16, 30, true },
	{ EGON_ALTFIRE2, 16, 30, true },
	{ EGON_ALTFIRE3, 16, 30, true },
	{ EGON_ALTFIRE4, 16, 30, true },
	{ EGON_ALTFIRE5, 16, 30, true },
	{ EGON_ALTSWITCH, 21, 30, false },
	{ EGON_ALTDRAW, 16, 30, false },
	{ EGON_ALTHOLSTER, 16, 30, false },
};

// Displacer Gun
static const animinfo_t displacerAnimInfo[DISPLACER_LAST] =
{
	{ DISPLACER_IDLE1, 91, 30, true },
	{ DISPLACER_FIDGET, 91, 30, false },
	{ DISPLACER_FIRE, 30, 31, false },
	{ DISPLACER_SPINUP, 31, 27, false },
	{ DISPLACER_SPINDOWN, 30, 27, false },
	{ DISPLACER_SPIN, 31, 31, true },
	{ DISPLACER_DRAW, 16, 15, false },
	{ DISPLACER_HOLSTER, 16, 15, false },
};



// =========================== //
//    SUPPORT					//
// =========================== //

// Automatic Medkit
static const animinfo_t medkitAnimInfo[MEDKIT_LAST] =
{
	{ MEDKIT_IDLE, 36, 30, true },
	{ MEDKIT_LONGIDLE, 72, 30, true },
	{ MEDKIT_LONGUSE, 72, 30, false },
	{ MEDKIT_SHORTUSE, 36, 30, false },
	{ MEDKIT_HOLSTER, 16, 30, false },
	{ MEDKIT_DRAW, 16, 30, false },
};

// Final
const weaponaiminfo_t weaponAnimInfoArray[128] =
{
	{ &(questionAnimInfo[0]), QUESTION_LAST }, // WEAPON_QUESTION
	{ &(spannerAnimInfo[0]), SPANNER_LAST }, // WEAPON_SPANNER
	{ &(knifeAnimInfo[0]), KNIFE_LAST }, // WEAPON_KNIFE
	{ &(crowbarAnimInfo[0]), CROWBAR_LAST }, // WEAPON_CROWBAR
	{ &(pipewrenchAnimInfo[0]), PIPEWRENCH_LAST },// WEAPON_PIPEWRENCH
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_AXE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_SWORD, Not yet implemented

	{ &(glockAnimInfo[0]), GLOCK_LAST },//WEAPON_GLOCK,
	{ &(m9AnimInfo[0]), M9_LAST },//WEAPON_M9,
	{ &(pythonAnimInfo[0]), PYTHON_LAST },//WEAPON_PYTHON,
	{ &(deagleAnimInfo[0]), DEAGLE_LAST },//WEAPON_DEAGLE,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_FLAREGUN, Not yet implemented

	{ &(shotgunAnimInfo[0]), SHOTGUN_LAST },//WEAPON_SHOTGUN,
	{ &(autoshotgunAnimInfo[0]), AUTOSHOTGUN_LAST },//WEAPON_AUTOSHOTGUN,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_COMBATSHOTGUN, // Not yet implemented
	{ &(huntingshotgunAnimInfo[0]), HUNTINGSHOTGUN_LAST },//WEAPON_HUNTINGSHOTGUN,
	{ &(supershotgunAnimInfo[0]), SUPERSHOTGUN_LAST },//WEAPON_SUPERSHOTGUN,

	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_MICROSMG, // Not yet implemented
	{ &(mp5AnimInfo[0]), MP5_LAST },//WEAPON_MP5,
	{ &(m4AnimInfo[0]), M4_LAST },//WEAPON_M4,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_AK47, // Not yet implemented
	{ &(nailgunAnimInfo[0]), NAILGUN_LAST },//WEAPON_NAILGUN,

	{ &(m249AnimInfo[0]), M249_LAST },//WEAPON_M249,
	{ &(chaingunAnimInfo[0]), CHAINGUN_LAST },//WEAPON_CHAINGUN,
	{ &(m60AnimInfo[0]), M60_LAST },//WEAPON_M60,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_MINIGUN, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_SPIKEGUN, Not yet implemented

	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_TRANQGUN, Not yet implemented
	{ &(crossbowAnimInfo[0]), CROSSBOW_LAST },//WEAPON_CROSSBOW,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_TORQUEBOW, Not yet implemented
	{ &(m40a1AnimInfo[0]), M40A1_LAST },//WEAPON_M40A1,0
	{ &(autosniperAnimInfo[0]), AUTOSNIPER_LAST },//WEAPON_AUTOSNIPER,

	{ &(glauncherAnimInfo[0]), GLAUNCHER_LAST },//WEAPON_GLAUNCHER,
	{ &(rpgAnimInfo[0]), RPG_LAST },//WEAPON_RPG,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_LAW, Not yet implemented
	{ &(rocketrifleAnimInfo[0]), ROCKETRIFLE_LAST },//WEAPON_ROCKETRIFLE,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_FLAMETHROWER, Not yet implemented

	{ &(railgunAnimInfo[0]), RAILGUN_LAST },//WEAPON_RAILGUN,
	{ &(gaussAnimInfo[0]), GAUSS_LAST },//WEAPON_GAUSS,
	{ &(egonAnimInfo[0]), EGON_LAST },//WEAPON_EGON,
	{ &(plasmarifleAnimInfo[0]), PLASMARIFLE_LAST },//WEAPON_PLASMARIFLE,
	{ &(displacerAnimInfo[0]), DISPLACER_LAST },//WEAPON_DISPLACER,

	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_CHUBTOAD, Not yet implemented
	{ &(squeakAnimInfo[0]), SQUEAK_LAST },//WEAPON_SNARK,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_BARNACLE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_ALIENCHAINSAW, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_ALIENSPRAYER, Not yet implemented
	{ &(hgunAnimInfo[0]), HGUN_LAST },//WEAPON_HORNETGUN,
	{ &(shockroachAnimInfo[0]), SHOCKROACH_LAST },//WEAPON_SHOCKROACH,
	{ &(sporelauncherAnimInfo[0]), SPORELAUNCHER_LAST },//WEAPON_SPORELAUNCHER,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_PENGUIN, Not yet implemented

	{ &(handgrenadeAnimInfo[0]), HANDGRENADE_LAST },//WEAPON_HANDGRENADE,
	{ &(handgrenadeAnimInfo[0]), HANDGRENADE_LAST },//WEAPON_HEGRENADE,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_INCGRENADE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_MOLOTOV, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_DYNAMITE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_CONCGRENADE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_GASGRENADE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_FLASHBANG, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_FRREZEGRENADE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_EMPGRENADE, Not yet implemented

	{ &(tripmineAnimInfo[0]), TRIPMINE_LAST },//WEAPON_TRIPMINE,
	{ &(satchelAnimInfo[0]), SATCHEL_LAST },//WEAPON_SATCHEL,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_TIMEBOMB, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_PROXBOMB, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_LANDMINE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_NAILMINE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_MIRV, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_CALTROP, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_DETPACK, Not yet implemented

	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_FLASHLIGHT, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_FLARE, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_EXTINGUISHER, Not yet implemented
	{ &(medkitAnimInfo[0]), MEDKIT_LAST },//WEAPON_MEDKIT,
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_CHARGER, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_EMPTOOL, Not yet implemented

	// Unplanned indices
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
	{ &(questionAnimInfo[0]), QUESTION_LAST },//WEAPON_???, Not yet implemented
};

#endif