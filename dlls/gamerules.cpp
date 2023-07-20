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
// GameRules.cpp
//=========================================================

#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"player.h"
#include	"weapons.h"
#include	"gamerules.h"
#include	"teamplay_gamerules.h"
#include	"skill.h"
#include	"game.h"

extern edict_t *EntSelectSpawnPoint( CBaseEntity *pPlayer );

DLL_GLOBAL CGameRules*	g_pGameRules = NULL;
extern DLL_GLOBAL BOOL	g_fGameOver;
extern int gmsgDeathMsg;	// client dll messages
extern int gmsgMOTD;

int g_teamplay = 0;

//=========================================================
//=========================================================
BOOL CGameRules::CanHaveAmmo( CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry )
{
	int iAmmoIndex;

	if ( pszAmmoName )
	{
		iAmmoIndex = GetAmmoIndex( pszAmmoName );

		if ( iAmmoIndex > -1 )
		{
			if ( pPlayer->AmmoInventory( iAmmoIndex ) < iMaxCarry )
			{
				// player has room for more of this type of ammo
				return TRUE;
			}
		}
	}

	return FALSE;
}

//=========================================================
//=========================================================
edict_t *CGameRules :: GetPlayerSpawnSpot( CBasePlayer *pPlayer )
{
	edict_t *pentSpawnSpot = EntSelectSpawnPoint( pPlayer );

	pPlayer->pev->origin = VARS(pentSpawnSpot)->origin + Vector(0,0,1);
	pPlayer->pev->v_angle  = g_vecZero;
	pPlayer->pev->velocity = g_vecZero;
	pPlayer->pev->angles = VARS(pentSpawnSpot)->angles;
	pPlayer->pev->punchangle = g_vecZero;
	pPlayer->pev->fixangle = TRUE;
	
	return pentSpawnSpot;
}

//=========================================================
//=========================================================
BOOL CGameRules::CanHavePlayerItem( CBasePlayer *pPlayer, CBasePlayerItem *pWeapon )
{
	// only living players can have items
	if ( pPlayer->pev->deadflag != DEAD_NO )
		return FALSE;

	if ( pWeapon->UsesAmmo() )
	{
		// Disabled until we can figure out how to pull this off
		//if ( !CanHaveAmmo( pPlayer, pWeapon->pszAmmo1(), pWeapon->iMaxAmmo1() ) )
		//{
			// we can't carry anymore ammo for this gun. We can only 
			// have the gun if we aren't already carrying one of this type
			if ( pPlayer->HasPlayerItem( pWeapon ) )
			{
				return FALSE;
			}
		//}
	}
	else
	{
		// weapon doesn't use ammo, don't take another if you already have it.
		if ( pPlayer->HasPlayerItem( pWeapon ) )
		{
			return FALSE;
		}
	}

	// note: will fall through to here if GetItemInfo doesn't fill the struct!
	return TRUE;
}

//=========================================================
// load the SkillData struct with the proper values based on the skill level.
//=========================================================
void CGameRules::RefreshSkillData ( void )
{
	int	iSkill;

	iSkill = (int)CVAR_GET_FLOAT("skill");
	g_iSkillLevel = iSkill;

	if (iSkill < SKILL_MIN)
	{
		iSkill = SKILL_MIN;
	}
	else if (iSkill > SKILL_MAX)
	{
		iSkill = SKILL_MAX;
	}

	gSkillData.iSkillLevel = iSkill;

	ALERT(at_console, "\nGAME SKILL LEVEL:%d\n", iSkill);

	// =========================== //
	//           MONSTERS           //
	// =========================== //

	// Alien Grunt
	gSkillData.agruntHealth = GetSkillCvar("sk_agrunt_health");
	gSkillData.agruntDmgPunch = GetSkillCvar("sk_agrunt_dmg_punch");
	gSkillData.agruntDmgBite = GetSkillCvar("sk_agrunt_dmg_bite");
	gSkillData.agruntDmgHeadButt = GetSkillCvar("sk_agrunt_dmg_headbutt");
	gSkillData.agruntDmgKick = GetSkillCvar("sk_agrunt_dmg_kick");

	// Apache 
	gSkillData.apacheHealth = GetSkillCvar("sk_apache_health");
	gSkillData.apacheDmgChaingun = GetSkillCvar("sk_apache_dmg_chaingun");
	gSkillData.apacheDmgHVR = GetSkillCvar("sk_apache_dmg_hvr");

	// Barney
	gSkillData.barneyHealth = GetSkillCvar("sk_barney_health");
	gSkillData.barneyDmgKick = GetSkillCvar("sk_barney_dmg_kick");
	gSkillData.barneyDmgPunch = GetSkillCvar("sk_barney_dmg_punch");
	gSkillData.barneyDmgGunWhip = GetSkillCvar("sk_barney_dmg_gunwhip");

	// Bullsquid
	gSkillData.bullsquidHealth = GetSkillCvar("sk_bullsquid_health");
	gSkillData.bullsquidDmgBite = GetSkillCvar("sk_bullsquid_dmg_bite");
	gSkillData.bullsquidDmgWhip = GetSkillCvar("sk_bullsquid_dmg_whip");
	gSkillData.bullsquidDmgSpit = GetSkillCvar("sk_bullsquid_dmg_spit");

	// Big momma
	gSkillData.bigmommaHealth = GetSkillCvar("sk_bigmomma_health");
	gSkillData.bigmommaHealthFactor = GetSkillCvar("sk_bigmomma_health_factor");
	gSkillData.bigmommaDmgSlash = GetSkillCvar("sk_bigmomma_dmg_slash");
	gSkillData.bigmommaDmgBlast = GetSkillCvar("sk_bigmomma_dmg_blast");
	gSkillData.bigmommaRadiusBlast = GetSkillCvar("sk_bigmomma_radius_blast");
	gSkillData.bigmommaDmgRam = GetSkillCvar("sk_bigmomma_dmg_ram");

	// Gargantua
	gSkillData.gargantuaHealth = GetSkillCvar("sk_gargantua_health");
	gSkillData.gargantuaDmgSlash = GetSkillCvar("sk_gargantua_dmg_slash");
	gSkillData.gargantuaDmgFire = GetSkillCvar("sk_gargantua_dmg_fire");
	gSkillData.gargantuaDmgStomp = GetSkillCvar("sk_gargantua_dmg_stomp");

	// Hassassin
	gSkillData.hassassinHealth = GetSkillCvar("sk_hassassin_health");
	gSkillData.hassassinDmgKick = GetSkillCvar("sk_hassassin_dmg_kick");
	gSkillData.hassassinDmgPunch = GetSkillCvar("sk_hassassin_dmg_punch");
	gSkillData.hassassinDmgGunWhip = GetSkillCvar("sk_hassassin_dmg_gunwhip");

	// Headcrab
	gSkillData.headcrabHealth = GetSkillCvar("sk_headcrab_health");
	gSkillData.headcrabDmgBite = GetSkillCvar("sk_headcrab_dmg_bite");

	// Human Grunt
	gSkillData.hgruntHealth = GetSkillCvar("sk_hgrunt_health");
	gSkillData.hgruntDmgKick = GetSkillCvar("sk_hgrunt_dmg_kick");
	gSkillData.hgruntDmgPunch = GetSkillCvar("sk_hgrunt_dmg_punch");
	gSkillData.hgruntDmgGunWhip = GetSkillCvar("sk_hgrunt_dmg_gunwhip");

	// Houndeye
	gSkillData.houndeyeHealth = GetSkillCvar("sk_houndeye_health");
	gSkillData.houndeyeDmgBlast = GetSkillCvar("sk_houndeye_dmg_blast");
	gSkillData.houndeyeDmgBark = GetSkillCvar("sk_houndeye_dmg_bark");

	// Alien Slave
	gSkillData.slaveHealth = GetSkillCvar("sk_islave_health");
	gSkillData.slaveDmgClaw = GetSkillCvar("sk_islave_dmg_claw");
	gSkillData.slaveDmgClawrake = GetSkillCvar("sk_islave_dmg_clawrake");
	gSkillData.slaveDmgZap = GetSkillCvar("sk_islave_dmg_zap");
	gSkillData.slaveDmgZapStomp = GetSkillCvar("sk_islave_dmg_zapstomp");
	gSkillData.slaveHeal = GetSkillCvar("sk_islave_heal");
	gSkillData.slavePower = GetSkillCvar("sk_islave_power");

	// Icthyosaur
	gSkillData.ichthyosaurHealth = GetSkillCvar("sk_ichthyosaur_health");
	gSkillData.ichthyosaurDmgChomp = GetSkillCvar("sk_ichthyosaur_dmg_chomp");

	// Leech
	gSkillData.leechHealth = GetSkillCvar("sk_leech_health");
	gSkillData.leechDmgBite = GetSkillCvar("sk_leech_dmg_bite");

	// Controller
	gSkillData.controllerHealth = GetSkillCvar("sk_controller_health");
	gSkillData.controllerDmgZap = GetSkillCvar("sk_controller_dmg_zap");
	gSkillData.controllerSpeedBall = GetSkillCvar("sk_controller_speed_ball");
	gSkillData.controllerDmgBall = GetSkillCvar("sk_controller_dmg_ball");
	gSkillData.controllerDmgSlash = GetSkillCvar("sk_controller_dmg_slash");

	// Nihilanth
	gSkillData.nihilanthHealth = GetSkillCvar("sk_nihilanth_health");
	gSkillData.nihilanthDmgZap = GetSkillCvar("sk_nihilanth_dmg_zap");
	gSkillData.nihilanthSpeedBall = GetSkillCvar("sk_nihilanth_speed_ball");
	gSkillData.nihilanthDmgBall = GetSkillCvar("sk_nihilanth_dmg_ball");
	gSkillData.nihilanthDmgSlash = GetSkillCvar("sk_nihilanth_dmg_slash");

	// Scientist
	gSkillData.scientistHealth = GetSkillCvar("sk_scientist_health");
	gSkillData.scientistDmgPunch = GetSkillCvar("sk_scientist_dmg_punch");
	gSkillData.scientistDmgKick = GetSkillCvar("sk_scientist_dmg_kick");
	gSkillData.scientistHeal = GetSkillCvar("sk_scientist_heal");

	// Zombie
	gSkillData.zombieHealth = GetSkillCvar("sk_zombie_health");
	gSkillData.zombieDmgOneSlash = GetSkillCvar("sk_zombie_dmg_one_slash");
	gSkillData.zombieDmgBothSlash = GetSkillCvar("sk_zombie_dmg_both_slash");

	// Gonome
	gSkillData.gonomeHealth = GetSkillCvar("sk_gonome_health");
	gSkillData.gonomeHeadcrabHealth = GetSkillCvar("sk_gonome_headcrab_health");
	gSkillData.gonomeDmgSlash = GetSkillCvar("sk_gonome_dmg_slash");
	gSkillData.gonomeDmgChomp = GetSkillCvar("sk_gonome_dmg_chomp");
	gSkillData.gonomeDmgLeap = GetSkillCvar("sk_gonome_dmg_leap");
	gSkillData.gonomeDmgAcid = GetSkillCvar("sk_gonome_dmg_acid");

	//Turret
	gSkillData.turretHealth = GetSkillCvar("sk_turret_health");

	// MiniTurret
	gSkillData.miniturretHealth = GetSkillCvar("sk_miniturret_health");

	// Sentry Turret
	gSkillData.sentryHealth = GetSkillCvar("sk_sentry_health");

	// Shock Trooper
	gSkillData.strooperHealth = GetSkillCvar("sk_strooper_health");
	gSkillData.strooperDmgBite = GetSkillCvar("sk_strooper_dmg_bite");
	gSkillData.strooperDmgSlap = GetSkillCvar("sk_strooper_dmg_slap");
	gSkillData.strooperDmgPalm = GetSkillCvar("sk_strooper_dmg_palm");

	// =========================== //
	//           WEAPONS           //
	// =========================== //

	// === 1 - MELEE === //

	// Fists
	gSkillData.plrDmgFistPunch = GetSkillCvar("sk_plr_punch");
	gSkillData.plrDmgFistUppercut = GetSkillCvar("sk_plr_uppercut");
	gSkillData.plrDmgFistKick = GetSkillCvar("sk_plr_kick");
	gSkillData.plrDmgFistCounter = GetSkillCvar("sk_plr_counter");

	// Spanner
	gSkillData.plrDmgSpannerLight = GetSkillCvar("sk_plr_span_light");
	gSkillData.plrDmgSpannerHeavy = GetSkillCvar("sk_plr_span_heavy");
	gSkillData.plrDmgSpannerThrown = GetSkillCvar("sk_plr_span_thrown");
	gSkillData.plrDmgSpannerCounter = GetSkillCvar("sk_plr_span_counter");

	// Knife
	gSkillData.plrDmgKnifeLight = GetSkillCvar("sk_plr_knife_light");
	gSkillData.plrDmgKnifeHeavy = GetSkillCvar("sk_plr_knife_heavy");
	gSkillData.plrDmgKnifeThrown = GetSkillCvar("sk_plr_knife_thrown");
	gSkillData.plrDmgKnifeCounter = GetSkillCvar("sk_plr_knife_counter");

	// Crowbar
	gSkillData.plrDmgCrowbarLight = GetSkillCvar("sk_plr_cbar_light");
	gSkillData.plrDmgCrowbarHeavy = GetSkillCvar("sk_plr_cbar_heavy");
	gSkillData.plrDmgCrowbarThrown = GetSkillCvar("sk_plr_cbar_thrown");
	gSkillData.plrDmgCrowbarCounter = GetSkillCvar("sk_plr_cbar_counter");

	// Pipewrench
	gSkillData.plrDmgPipewrenchLight = GetSkillCvar("sk_plr_cbar_light");
	gSkillData.plrDmgPipewrenchHeavy = GetSkillCvar("sk_plr_cbar_heavy");
	gSkillData.plrDmgPipewrenchThrown = GetSkillCvar("sk_plr_cbar_thrown");
	gSkillData.plrDmgPipewrenchCounter = GetSkillCvar("sk_plr_cbar_counter");

	// === 2 - PISTOLS === //

	// 9mm Round (Glock-17)
	gSkillData.plrDmg9mm = GetSkillCvar("sk_plr_9mm");

	// 38 SW (M9 Beretta)
	gSkillData.plrDmg38sw = GetSkillCvar("sk_plr_38sw");

	// .357 Magnum Round
	gSkillData.plrDmg357mag = GetSkillCvar("sk_plr_357mag");

	// .44 SW Round (Desert Eagle)
	gSkillData.plrDmg44sw = GetSkillCvar("sk_plr_44sw");

	// === 3 - SHOTGUNS & MACHINE-GUNS === //

	// Automatic Shotgun
	gSkillData.plrDmg12gauge = GetSkillCvar("sk_plr_12gauge");

	// Trench Gun
	gSkillData.plrDmgExpGauge = GetSkillCvar("sk_plr_expgauge");
	gSkillData.plrDmgFlameGauge = GetSkillCvar("sk_plr_flamegauge");

	// Super Shotgun
	gSkillData.plrDmg25gauge = GetSkillCvar("sk_plr_25gauge");

	// MP5
	gSkillData.plrDmg9mmh = GetSkillCvar("sk_plr_9mmh");
	gSkillData.plrDmg40mmBlast = GetSkillCvar("sk_plr_40mm_blast");
	gSkillData.plrDmg40mmHeat = GetSkillCvar("sk_plr_40mm_heat");
	gSkillData.plrDmg40mmShrapnel = GetSkillCvar("sk_plr_40mm_shrap");
	gSkillData.plrDmg40mmSmack = GetSkillCvar("sk_plr_40mm_smack");

	// M4
	gSkillData.plrDmg556nato = GetSkillCvar("sk_plr_556nato");
	gSkillData.plrDmgSmokeGrenadeBlast = GetSkillCvar("sk_plr_smokegrenade_blast");
	gSkillData.plrDmgSmokeGrenadeHeat = GetSkillCvar("sk_plr_smokegrenade_heat");
	gSkillData.plrDmgSmokeGrenadeShrapnel = GetSkillCvar("sk_plr_smokegrenade_shrap");
	gSkillData.plrDmgSmokeGrenadeSmack = GetSkillCvar("sk_plr_smokegrenade_smack");

	// AK-47
	gSkillData.plrDmg762r = GetSkillCvar("sk_plr_762r");
	gSkillData.plrDmgHerBlast = GetSkillCvar("sk_plr_her_blast");
	gSkillData.plrDmgHerHeat = GetSkillCvar("sk_plr_her_heat");
	gSkillData.plrDmgHerShrapnel = GetSkillCvar("sk_plr_her_shrap");

	// Nailgun
	gSkillData.plrDmgNail = GetSkillCvar("sk_plr_nail");
	gSkillData.plrDmgHeatnail = GetSkillCvar("sk_plr_heatnail");
	gSkillData.plrDmgNailBombBlast = GetSkillCvar("sk_plr_nailbomb_blast");
	gSkillData.plrDmgNailBombHeat = GetSkillCvar("sk_plr_nailbomb_heat");
	gSkillData.plrDmgNailBombShrapnel = GetSkillCvar("sk_plr_nailbomb_shrap");

	// === 4 - HEAVY WEAPONS === //

	// Grenade Launcher
	gSkillData.plrDmg50mmgBlast = GetSkillCvar("sk_plr_50mmg_blast");
	gSkillData.plrDmg50mmgHeat = GetSkillCvar("sk_plr_50mmg_heat");
	gSkillData.plrDmg50mmgShrapnel = GetSkillCvar("sk_plr_50mmg_shrap");

	// RPG
	gSkillData.plrDmgRpgBlast = GetSkillCvar("sk_plr_rpg_blast");
	gSkillData.plrDmgRpgHeat = GetSkillCvar("sk_plr_rpg_heat");
	gSkillData.plrDmgRpgShrapnel = GetSkillCvar("sk_plr_rpg_shrap");

	// LAW
	gSkillData.plrDmg66mmBlast = GetSkillCvar("sk_plr_66mm_blast");
	gSkillData.plrDmg66mmHeat = GetSkillCvar("sk_plr_66mm_heat");
	gSkillData.plrDmg66mmShrapnel = GetSkillCvar("sk_plr_66mm_shrap");

	// 50mm Rocket (Rocket Rifle)
	gSkillData.plrDmg50mmrBlast = GetSkillCvar("sk_plr_50mmr_blast");
	gSkillData.plrDmg50mmrHeat = GetSkillCvar("sk_plr_50mmr_heat");
	gSkillData.plrDmg50mmrShrapnel = GetSkillCvar("sk_plr_50mmr_shrap");

	// Flamethrower
	gSkillData.plrDmgFlameTouch = GetSkillCvar("sk_plr_flametouch");
	gSkillData.plrDmgFlameRadius = GetSkillCvar("sk_plr_flamerad");
	gSkillData.plrDmgNapalmBombBlast = GetSkillCvar("sk_plr_nbomb_blast");
	gSkillData.plrDmgNapalmBombHeat = GetSkillCvar("sk_plr_nbomb_heat");
	gSkillData.plrDmgNapalmBombBlast = GetSkillCvar("sk_plr_nbomb_shrap");

	// M249
	gSkillData.plrDmg556natoh = GetSkillCvar("sk_plr_556natoh");

	// M60
	gSkillData.plrDmg762natoh = GetSkillCvar("sk_plr_762natoh");

	// Chaingun
	gSkillData.plrDmg10mm = GetSkillCvar("sk_plr_10mm");

	// Minigun
	gSkillData.plrDmg127mm = GetSkillCvar("sk_plr_127mm");

	// === 5 - RANGED WEAPONS === //

	// Autocrossbow
	gSkillData.plrDmgCrossbowBolt = GetSkillCvar("sk_plr_bolt");
	gSkillData.plrDmgCrossbowBoltToxin = GetSkillCvar("sk_plr_bolt_toxin");

	// Torque Crossbow
	gSkillData.plrDmgTorqueBolt = GetSkillCvar("sk_plr_tbolt");
	gSkillData.plrDmgTorqueBoltBlast = GetSkillCvar("sk_plr_tbolt_blast");
	gSkillData.plrDmgTorqueBoltHeat = GetSkillCvar("sk_plr_tbolt_heat");
	gSkillData.plrDmgTorqueBoltShrap = GetSkillCvar("sk_plr_tbolt_shrap");

	// M40A1
	gSkillData.plrDmg762nato = GetSkillCvar("sk_plr_762nato");

	// Autosniper
	gSkillData.plrDmg308 = GetSkillCvar("sk_plr_308");
	gSkillData.plrDmg338 = GetSkillCvar("sk_plr_338");

	// === 6 - ENERGY WEAPONS === //

	// Railgun
	gSkillData.plrDmgRailBolt = GetSkillCvar("sk_plr_railbolt");
	gSkillData.plrDmgRailBoltRadius = GetSkillCvar("sk_plr_railbolt_radius");

	// Plasma Gun
	gSkillData.plrDmgPlasma = GetSkillCvar("sk_plr_plasma");
	gSkillData.plrDmgPlasmaSpray = GetSkillCvar("sk_plr_plasma_spray");
	gSkillData.plrDmgPlasmaBlast = GetSkillCvar("sk_plr_plasma_blast");

	// Gauss Gun
	gSkillData.plrDmgGaussLaser = GetSkillCvar("sk_plr_gauss_laser");
	gSkillData.plrDmgGaussRail = GetSkillCvar("sk_plr_gauss_rail");

	// Egon Gun
	gSkillData.plrDmgEgonNarrow = GetSkillCvar("sk_plr_egon_narrow");
	gSkillData.plrDmgEgonWide = GetSkillCvar("sk_plr_egon_wide");
	gSkillData.plrDmgEgonWideRadius = GetSkillCvar("sk_plr_egon_wide_rad");
	gSkillData.plrDmgEgonWideBlast = GetSkillCvar("sk_plr_egon_blast");

	// Displacer Gun/Cannon
	gSkillData.plrDmgDisplacerBlast = GetSkillCvar("sk_plr_disp_blast");
	gSkillData.plrDmgDisplacerArc = GetSkillCvar("sk_plr_disp_arc");
	gSkillData.plrDmgDisplacerDirect = GetSkillCvar("sk_plr_disp_dir");


	// === 7 - THROWABLE AND TRAPS === //

	// High-Explosive Grenade
	gSkillData.plrDmgHighExplosiveBlast = GetSkillCvar("sk_plr_he_blast");
	gSkillData.plrDmgHighExplosiveHeat = GetSkillCvar("sk_plr_he_heat");
	gSkillData.plrDmgHighExplosiveShrapnel = GetSkillCvar("sk_plr_he_shrap");
	gSkillData.plrDmgHighExplosiveSmack = GetSkillCvar("sk_plr_he_smack");

	// Fragmentation Grenade
	gSkillData.plrDmgFragmentationBlast = GetSkillCvar("sk_plr_frag_blast");
	gSkillData.plrDmgFragmentationHeat = GetSkillCvar("sk_plr_frag_heat");
	gSkillData.plrDmgFragmentationShrapnel = GetSkillCvar("sk_plr_frag_shrap");
	gSkillData.plrDmgFragmentationSmack = GetSkillCvar("sk_plr_frag_smack");

	// Satchel Charge
	gSkillData.plrDmgSatchelBlast = GetSkillCvar("sk_plr_satchel_blast");
	gSkillData.plrDmgSatchelHeat = GetSkillCvar("sk_plr_satchel_heat");
	gSkillData.plrDmgSatchelShrapnel = GetSkillCvar("sk_plr_satchel_shrap");

	// Tripmine
	gSkillData.plrDmgTripmineBlast = GetSkillCvar("sk_plr_tripmine_blast");
	gSkillData.plrDmgTripmineHeat = GetSkillCvar("sk_plr_tripmine_heat");
	gSkillData.plrDmgTripmineShrapnel = GetSkillCvar("sk_plr_tripmine_shrap");

	// === 8 - ALIEN WEAPONS === //

	// Hivehand
	gSkillData.hornetHealth = GetSkillCvar("sk_hornet_health");
	gSkillData.plrDmgHornet = GetSkillCvar("sk_plr_hornet");
	gSkillData.plrDmgPheromoneMissile = GetSkillCvar("sk_plr_phero_missile");
	gSkillData.plrDmgBlackHole = GetSkillCvar("sk_plr_black_hole");
	gSkillData.plrDmgChainsaw = GetSkillCvar("sk_plr_chainsaw");

	// Snark
	gSkillData.snarkHealth = GetSkillCvar("sk_snark_health");
	gSkillData.snarkDmgBite = GetSkillCvar("sk_snark_dmg_bite");
	gSkillData.snarkDmgPop = GetSkillCvar("sk_snark_dmg_pop");

	// Spore Launcher
	gSkillData.plrDmgSporeRadius = GetSkillCvar("sk_plr_spore_radius");
	gSkillData.plrDmgSporeDirect = GetSkillCvar("sk_plr_spore_direct");
	gSkillData.plrDmgSporeBite = GetSkillCvar("sk_plr_spore_bite");

	// Shock Roach
	gSkillData.plrDmgShockBolt = GetSkillCvar("sk_plr_shockbolt");
	gSkillData.plrDmgShockTase = GetSkillCvar("sk_plr_shocktase");
	gSkillData.plrDmgShockBite = GetSkillCvar("sk_plr_shockbite");

	// Barnacle
	gSkillData.barnacleHealth = GetSkillCvar("sk_barnacle_health");
	gSkillData.plrDmgBarnacleBite = GetSkillCvar("sk_plr_barnacle_bite");

	// Chumtoad
	//? ? ?

	// === 9 - SUPPORT WEAPONS === //

	// Automatic Medkit
	gSkillData.plrHealMedkit = GetSkillCvar("sk_plr_medkit_heal");
	gSkillData.plrDmgMedkit = GetSkillCvar("sk_plr_medkit_poison");

	// EMP Tool
	//? ? ?

	// Syringe
	//? ? ?

	// Flare
	gSkillData.plrDmgFlareBurn = GetSkillCvar("sk_plr_flare_burn");
	gSkillData.plrDmgFlareHit = GetSkillCvar("sk_plr_flare_hit");
	gSkillData.plrDmgFlareBlast = GetSkillCvar("sk_plr_flare_blast");
	gSkillData.plrDmgFlareHeat = GetSkillCvar("sk_plr_flare_heat");
	gSkillData.plrDmgFlareShrapnel = GetSkillCvar("sk_plr_flare_shrap");

	// HEALTH/SUIT CHARGE DISTRIBUTION
	gSkillData.chargerCapacity = GetSkillCvar("sk_charger");
	gSkillData.batteryCapacity = GetSkillCvar("sk_battery");
	gSkillData.healthkitCapacity = GetSkillCvar("sk_healthkit");

	// damage adjusters
	gSkillData.dmgAdjustHead = GetSkillCvar("sk_dmgadjust_head");
	gSkillData.dmgAdjustChest = GetSkillCvar("sk_dmgadjust_chest");
	gSkillData.dmgAdjustStomach = GetSkillCvar("sk_dmgadjust_stomach");
	gSkillData.dmgAdjustLeg = GetSkillCvar("sk_dmgadjust_arm");
	gSkillData.dmgAdjustArm = GetSkillCvar("sk_dmgadjust_leg");
}

//=========================================================
// instantiate the proper game rules object
//=========================================================

CGameRules *InstallGameRules( void )
{
	SERVER_COMMAND( "exec game.cfg\n" );
	SERVER_EXECUTE( );

	if ( !gpGlobals->deathmatch )
	{
		// generic half-life
		g_teamplay = 0;
		return new CHalfLifeRules;
	}
	else
	{
		if ( teamplay.value > 0 )
		{
			// teamplay

			g_teamplay = 1;
			return new CHalfLifeTeamplay;
		}
		if ((int)gpGlobals->deathmatch == 1)
		{
			// vanilla deathmatch
			g_teamplay = 0;
			return new CHalfLifeMultiplay;
		}
		else
		{
			// vanilla deathmatch??
			g_teamplay = 0;
			return new CHalfLifeMultiplay;
		}
	}
}



