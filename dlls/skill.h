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
//=========================================================
// skill.h - skill level concerns
//=========================================================

#if !defined(ENGINE_DLL) 
struct skilldata_t
{
	// game skill level
	int iSkillLevel;

	// =========================== //
	//           MONSTERS           //
	// =========================== //

	// Alien Grunt
	float agruntHealth;
	float agruntDmgPunch;
	float agruntDmgBite;
	float agruntDmgHeadButt;
	float agruntDmgKick;

	// Apache 
	float apacheHealth;
	float apacheDmgChaingun;
	float apacheDmgHVR;

	// Barney
	float barneyHealth;
	float barneyDmgKick;
	float barneyDmgPunch;
	float barneyDmgGunWhip;

	// Bullsquid
	float bullsquidHealth;
	float bullsquidDmgBite;
	float bullsquidDmgWhip;
	float bullsquidDmgSpit;

	// Big momma
	float bigmommaHealth;
	float bigmommaHealthFactor;
	float bigmommaDmgSlash;
	float bigmommaDmgBlast;
	float bigmommaRadiusBlast;
	float bigmommaDmgRam;

	// Gargantua
	float gargantuaHealth;
	float gargantuaDmgSlash;
	float gargantuaDmgFire;
	float gargantuaDmgStomp;

	// Hassassin
	float hassassinHealth;
	float hassassinDmgKick;
	float hassassinDmgPunch;
	float hassassinDmgGunWhip;

	// Headcrab
	float headcrabHealth;
	float headcrabDmgBite;

	// Human Grunt
	float hgruntHealth;
	float hgruntDmgKick;
	float hgruntDmgPunch;
	float hgruntDmgGunWhip;

	// Houndeye
	float houndeyeHealth;
	float houndeyeDmgBlast;
	float houndeyeDmgBark;

	// Alien Slave
	float slaveHealth;
	float slaveDmgClaw;
	float slaveDmgClawrake;
	float slaveDmgZap;
	float slaveDmgZapStomp;
	float slaveHeal;
	float slavePower;

	// Icthyosaur
	float ichthyosaurHealth;
	float ichthyosaurDmgChomp;

	// Leech
	float leechHealth;
	float leechDmgBite;

	// Controller
	float controllerHealth;
	float controllerDmgZap;
	float controllerSpeedBall;
	float controllerDmgBall;
	float controllerDmgSlash;

	// Nihilanth
	float nihilanthHealth;
	float nihilanthDmgZap;
	float nihilanthSpeedBall;
	float nihilanthDmgBall;
	float nihilanthDmgSlash;

	// Scientist
	float scientistHealth;
	float scientistDmgPunch;
	float scientistDmgKick;
	float scientistHeal;

	// Zombie
	float zombieHealth;
	float zombieDmgOneSlash;
	float zombieDmgBothSlash;

	// Gonome
	float gonomeHealth;
	float gonomeHeadcrabHealth;
	float gonomeDmgSlash;
	float gonomeDmgChomp;
	float gonomeDmgLeap;
	float gonomeDmgAcid;

	//Turret
	float turretHealth;

	// MiniTurret
	float miniturretHealth;

	// Sentry Turret
	float sentryHealth;

	// Shock Trooper

	float strooperHealth;
	float strooperDmgSlap;
	float strooperDmgBite;
	float strooperDmgPalm;

	// =========================== //
	//           WEAPONS           //
	// =========================== //

	// === 1 - MELEE === //

	// Fists
	float plrDmgFistPunch;
	float plrDmgFistUppercut;
	float plrDmgFistKick;
	float plrDmgFistCounter;

	// Spanner
	float plrDmgSpannerLight;
	float plrDmgSpannerHeavy;
	float plrDmgSpannerThrown;
	float plrDmgSpannerCounter;

	// Knife
	float plrDmgKnifeLight;
	float plrDmgKnifeHeavy;
	float plrDmgKnifeThrown;
	float plrDmgKnifeCounter;

	// Crowbar
	float plrDmgCrowbarLight;
	float plrDmgCrowbarHeavy;
	float plrDmgCrowbarThrown;
	float plrDmgCrowbarCounter;

	// Pipewrench
	float plrDmgPipewrenchLight;
	float plrDmgPipewrenchHeavy;
	float plrDmgPipewrenchThrown;
	float plrDmgPipewrenchCounter;

	// === 2 - PISTOLS === //

	// 9mm Round (Glock-17)
	float plrDmg9mm;

	// 38 SW (M9 Beretta)
	float plrDmg38sw;

	// .357 Magnum Round
	float plrDmg357mag;

	// .44 SW Round (Desert Eagle)
	float plrDmg44sw;

	// === 3 - SHOTGUNS & MACHINE-GUNS === //

	// Automatic Shotgun
	float plrDmg12gauge;

	// Trench Gun
	float plrDmgExpGauge;
	float plrDmgFlameGauge;

	// Super Shotgun
	float plrDmg25gauge;

	// MP5
	float plrDmg9mmh;
	float plrDmg40mmBlast;
	float plrDmg40mmHeat;
	float plrDmg40mmShrapnel;
	float plrDmg40mmSmack;

	// M4
	float plrDmg556nato;
	float plrDmgSmokeGrenadeBlast;
	float plrDmgSmokeGrenadeHeat;
	float plrDmgSmokeGrenadeShrapnel;
	float plrDmgSmokeGrenadeSmack;

	// AK-47
	float plrDmg762r;
	float plrDmgHerBlast;
	float plrDmgHerHeat;
	float plrDmgHerShrapnel;

	// Nailgun
	float plrDmgNail;
	float plrDmgHeatnail;
	float plrDmgNailBombBlast;
	float plrDmgNailBombHeat;
	float plrDmgNailBombShrapnel;

	// === 4 - HEAVY WEAPONS === //

	// Grenade Launcher
	float plrDmg50mmgBlast;
	float plrDmg50mmgHeat;
	float plrDmg50mmgShrapnel;

	// RPG
	float plrDmgRpgBlast;
	float plrDmgRpgHeat;
	float plrDmgRpgShrapnel;

	// LAW
	float plrDmg66mmBlast;
	float plrDmg66mmHeat;
	float plrDmg66mmShrapnel;

	// 50mm Rocket (Rocket Rifle)
	float plrDmg50mmrBlast;
	float plrDmg50mmrHeat;
	float plrDmg50mmrShrapnel;

	// Flamethrower
	float plrDmgFlameTouch;
	float plrDmgFlameRadius;
	float plrDmgNapalmBombBlast;
	float plrDmgNapalmBombHeat;
	float plrDmgNapalmBombShrapnel;

	// M249
	float plrDmg556natoh;

	// M60
	float plrDmg762natoh;

	// Chaingun
	float plrDmg10mm;

	// Minigun
	float plrDmg127mm;

	// === 5 - RANGED WEAPONS === //

	// Autocrossbow
	float plrDmgCrossbowBolt;
	float plrDmgCrossbowBoltToxin;

	// Torque Crossbow
	float plrDmgTorqueBolt;
	float plrDmgTorqueBoltBlast;
	float plrDmgTorqueBoltHeat;
	float plrDmgTorqueBoltShrap;

	// M40A1
	float plrDmg762nato;

	// Autosniper
	float plrDmg308;
	float plrDmg338;

	// === 6 - ENERGY WEAPONS === //

	// Railgun
	float plrDmgRailBolt;
	float plrDmgRailBoltRadius;

	// Plasma Gun
	float plrDmgPlasma;
	float plrDmgPlasmaSpray;
	float plrDmgPlasmaBlast;

	// Gauss Gun
	float plrDmgGaussLaser;
	float plrDmgGaussRail;

	// Egon Gun
	float plrDmgEgonNarrow;
	float plrDmgEgonWide;
	float plrDmgEgonWideRadius;
	float plrDmgEgonWideBlast;

	// Displacer Gun/Cannon
	float plrDmgDisplacerBlast;
	float plrDmgDisplacerArc;
	float plrDmgDisplacerDirect;


	// === 7 - THROWABLE AND TRAPS === //

	// High-Explosive Grenade
	float plrDmgHighExplosiveBlast;
	float plrDmgHighExplosiveHeat;
	float plrDmgHighExplosiveShrapnel;
	float plrDmgHighExplosiveSmack;

	// Fragmentation Grenade
	float plrDmgFragmentationBlast;
	float plrDmgFragmentationHeat;
	float plrDmgFragmentationShrapnel;
	float plrDmgFragmentationSmack;

	// Satchel Charge
	float plrDmgSatchelBlast;
	float plrDmgSatchelHeat;
	float plrDmgSatchelShrapnel;

	// Tripmine
	float plrDmgTripmineBlast;
	float plrDmgTripmineHeat;
	float plrDmgTripmineShrapnel;

	// === 8 - ALIEN WEAPONS === //

	// Hivehand
	float hornetHealth;
	float plrDmgHornet;
	float plrDmgPheromoneMissile;
	float plrDmgBlackHole;
	float plrDmgChainsaw;

	// Snark
	float snarkHealth;
	float snarkDmgBite;
	float snarkDmgPop;

	// Spore Launcher
	float plrDmgSporeRadius;
	float plrDmgSporeDirect;
	float plrDmgSporeBite;

	// Shock Roach
	float plrDmgShockBolt;
	float plrDmgShockTase;
	float plrDmgShockBite;

	// Barnacle
	float barnacleHealth;
	float plrDmgBarnacleBite;

	// Chumtoad
	//? ? ?

	// === 9 - SUPPORT WEAPONS === //

	// Automatic Medkit
	float plrHealMedkit;
	float plrDmgMedkit;

	// EMP Tool
	//? ? ?

	// Syringe
	//? ? ?

	// Flare
	float plrDmgFlareBurn;
	float plrDmgFlareHit;
	float plrDmgFlareBlast;
	float plrDmgFlareHeat;
	float plrDmgFlareShrapnel;

	// Items
	float chargerCapacity;
	float batteryCapacity;
	float healthkitCapacity;

	// damage adjusters
	float dmgAdjustHead;
	float dmgAdjustChest;
	float dmgAdjustStomach;
	float dmgAdjustLeg;
	float dmgAdjustArm;
};

extern	DLL_GLOBAL	skilldata_t	gSkillData;
float GetSkillCvar(char* pName);

extern DLL_GLOBAL int		g_iSkillLevel;
#endif

#define SKILL_NONE			0	// SKILL_NONE IS USED FOR CUSTOM DIFFICULTY
#define SKILL_EASY			1
#define SKILL_NORMAL		2
#define SKILL_MEDIUM		3
#define SKILL_DIFFICULT		4
#define SKILL_HARD			5
#define SKILL_EXTREME		6
#define SKILL_IMPOSSIBLE	7
#define SKILL_NIGHTMARE		8
#define SKILL_HELL			9

#define SKILL_MAX		SKILL_HELL
#define SKILL_MIN		SKILL_EASY