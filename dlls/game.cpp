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
#include "extdll.h"
#include "eiface.h"
#include "util.h"
#include "game.h"

cvar_t	displaysoundlist = {"displaysoundlist","0"};

// multiplayer server rules
cvar_t	fragsleft	= {"mp_fragsleft","0", FCVAR_SERVER | FCVAR_UNLOGGED };	  // Don't spam console/log files/users with this changing
cvar_t	timeleft	= {"mp_timeleft","0" , FCVAR_SERVER | FCVAR_UNLOGGED };	  // "      "

// multiplayer server rules
cvar_t	teamplay	= {"mp_teamplay","0", FCVAR_SERVER };
cvar_t	fraglimit	= {"mp_fraglimit","0", FCVAR_SERVER };
cvar_t	timelimit	= {"mp_timelimit","0", FCVAR_SERVER };
cvar_t	friendlyfire= {"mp_friendlyfire","0", FCVAR_SERVER };
cvar_t	falldamage	= {"mp_falldamage","0", FCVAR_SERVER };
cvar_t	weaponstay	= {"mp_weaponstay","0", FCVAR_SERVER };
cvar_t	forcerespawn= {"mp_forcerespawn","1", FCVAR_SERVER };
cvar_t	flashlight	= {"mp_flashlight","0", FCVAR_SERVER };
cvar_t	aimcrosshair= {"mp_autocrosshair","1", FCVAR_SERVER };
cvar_t	decalfrequency = {"decalfrequency","30", FCVAR_SERVER|FCVAR_ARCHIVE };
cvar_t	teamlist = {"mp_teamlist","hgrunt;scientist", FCVAR_SERVER };
cvar_t	teamoverride = {"mp_teamoverride","1" };
cvar_t	defaultteam = {"mp_defaultteam","0" };
cvar_t	allowmonsters={"mp_allowmonsters","0", FCVAR_SERVER };

cvar_t  mp_chattime = {"mp_chattime","10", FCVAR_SERVER };
cvar_t  saved1 = { "saved_cvar", "0", FCVAR_ARCHIVE };


// Engine Cvars
cvar_t 	*g_psv_gravity = NULL;
cvar_t	*g_psv_aim = NULL;
cvar_t	*g_footsteps = NULL;

// BEGIN: CVARS FOR SKILL LEVEL SETTINGS

// =========================== //
//           MONSTERS          //
// =========================== //

// Alien Grunt
cvar_t sk_agrunt_health1 = { "sk_agrunt_health1", "0" };
cvar_t sk_agrunt_health2 = { "sk_agrunt_health2", "0" };
cvar_t sk_agrunt_health3 = { "sk_agrunt_health3", "0" };
cvar_t sk_agrunt_health4 = { "sk_agrunt_health4", "0" };
cvar_t sk_agrunt_health5 = { "sk_agrunt_health5", "0" };
cvar_t sk_agrunt_health6 = { "sk_agrunt_health6", "0" };

cvar_t sk_agrunt_dmg_punch1 = { "sk_agrunt_dmg_punch1", "0" };
cvar_t sk_agrunt_dmg_punch2 = { "sk_agrunt_dmg_punch2", "0" };
cvar_t sk_agrunt_dmg_punch3 = { "sk_agrunt_dmg_punch3", "0" };
cvar_t sk_agrunt_dmg_punch4 = { "sk_agrunt_dmg_punch4", "0" };
cvar_t sk_agrunt_dmg_punch5 = { "sk_agrunt_dmg_punch5", "0" };
cvar_t sk_agrunt_dmg_punch6 = { "sk_agrunt_dmg_punch6", "0" };

cvar_t sk_agrunt_dmg_bite1 = { "sk_agrunt_dmg_bite1", "0" };
cvar_t sk_agrunt_dmg_bite2 = { "sk_agrunt_dmg_bite2", "0" };
cvar_t sk_agrunt_dmg_bite3 = { "sk_agrunt_dmg_bite3", "0" };
cvar_t sk_agrunt_dmg_bite4 = { "sk_agrunt_dmg_bite4", "0" };
cvar_t sk_agrunt_dmg_bite5 = { "sk_agrunt_dmg_bite5", "0" };
cvar_t sk_agrunt_dmg_bite6 = { "sk_agrunt_dmg_bite6", "0" };

cvar_t sk_agrunt_dmg_headbutt1 = { "sk_agrunt_dmg_headbutt1", "0" };
cvar_t sk_agrunt_dmg_headbutt2 = { "sk_agrunt_dmg_headbutt2", "0" };
cvar_t sk_agrunt_dmg_headbutt3 = { "sk_agrunt_dmg_headbutt3", "0" };
cvar_t sk_agrunt_dmg_headbutt4 = { "sk_agrunt_dmg_headbutt4", "0" };
cvar_t sk_agrunt_dmg_headbutt5 = { "sk_agrunt_dmg_headbutt5", "0" };
cvar_t sk_agrunt_dmg_headbutt6 = { "sk_agrunt_dmg_headbutt6", "0" };

cvar_t sk_agrunt_dmg_kick1 = { "sk_agrunt_dmg_kick1", "0" };
cvar_t sk_agrunt_dmg_kick2 = { "sk_agrunt_dmg_kick2", "0" };
cvar_t sk_agrunt_dmg_kick3 = { "sk_agrunt_dmg_kick3", "0" };
cvar_t sk_agrunt_dmg_kick4 = { "sk_agrunt_dmg_kick4", "0" };
cvar_t sk_agrunt_dmg_kick5 = { "sk_agrunt_dmg_kick5", "0" };
cvar_t sk_agrunt_dmg_kick6 = { "sk_agrunt_dmg_kick6", "0" };

// Apache 
cvar_t sk_apache_health1 = { "sk_apache_health1", "0" };
cvar_t sk_apache_health2 = { "sk_apache_health2", "0" };
cvar_t sk_apache_health3 = { "sk_apache_health3", "0" };
cvar_t sk_apache_health4 = { "sk_apache_health4", "0" };
cvar_t sk_apache_health5 = { "sk_apache_health5", "0" };
cvar_t sk_apache_health6 = { "sk_apache_health6", "0" };

cvar_t sk_apache_dmg_chaingun1 = { "sk_apache_dmg_chaingun1", "0" };
cvar_t sk_apache_dmg_chaingun2 = { "sk_apache_dmg_chaingun2", "0" };
cvar_t sk_apache_dmg_chaingun3 = { "sk_apache_dmg_chaingun3", "0" };
cvar_t sk_apache_dmg_chaingun4 = { "sk_apache_dmg_chaingun4", "0" };
cvar_t sk_apache_dmg_chaingun5 = { "sk_apache_dmg_chaingun5", "0" };
cvar_t sk_apache_dmg_chaingun6 = { "sk_apache_dmg_chaingun6", "0" };

cvar_t sk_apache_dmg_hvr1 = { "sk_apache_dmg_hvr1", "0" };
cvar_t sk_apache_dmg_hvr2 = { "sk_apache_dmg_hvr2", "0" };
cvar_t sk_apache_dmg_hvr3 = { "sk_apache_dmg_hvr3", "0" };
cvar_t sk_apache_dmg_hvr4 = { "sk_apache_dmg_hvr4", "0" };
cvar_t sk_apache_dmg_hvr5 = { "sk_apache_dmg_hvr5", "0" };
cvar_t sk_apache_dmg_hvr6 = { "sk_apache_dmg_hvr6", "0" };

// Barney
cvar_t sk_barney_health1 = { "sk_barney_health1", "0" };
cvar_t sk_barney_health2 = { "sk_barney_health2", "0" };
cvar_t sk_barney_health3 = { "sk_barney_health3", "0" };
cvar_t sk_barney_health4 = { "sk_barney_health4", "0" };
cvar_t sk_barney_health5 = { "sk_barney_health5", "0" };
cvar_t sk_barney_health6 = { "sk_barney_health6", "0" };

cvar_t sk_barney_dmg_kick1 = { "sk_barney_dmg_kick1", "0" };
cvar_t sk_barney_dmg_kick2 = { "sk_barney_dmg_kick2", "0" };
cvar_t sk_barney_dmg_kick3 = { "sk_barney_dmg_kick3", "0" };
cvar_t sk_barney_dmg_kick4 = { "sk_barney_dmg_kick4", "0" };
cvar_t sk_barney_dmg_kick5 = { "sk_barney_dmg_kick5", "0" };
cvar_t sk_barney_dmg_kick6 = { "sk_barney_dmg_kick6", "0" };

cvar_t sk_barney_dmg_punch1 = { "sk_barney_dmg_punch1", "0" };
cvar_t sk_barney_dmg_punch2 = { "sk_barney_dmg_punch2", "0" };
cvar_t sk_barney_dmg_punch3 = { "sk_barney_dmg_punch3", "0" };
cvar_t sk_barney_dmg_punch4 = { "sk_barney_dmg_punch4", "0" };
cvar_t sk_barney_dmg_punch5 = { "sk_barney_dmg_punch5", "0" };
cvar_t sk_barney_dmg_punch6 = { "sk_barney_dmg_punch6", "0" };

cvar_t sk_barney_dmg_gunwhip1 = { "sk_barney_dmg_gunwhip1", "0" };
cvar_t sk_barney_dmg_gunwhip2 = { "sk_barney_dmg_gunwhip2", "0" };
cvar_t sk_barney_dmg_gunwhip3 = { "sk_barney_dmg_gunwhip3", "0" };
cvar_t sk_barney_dmg_gunwhip4 = { "sk_barney_dmg_gunwhip4", "0" };
cvar_t sk_barney_dmg_gunwhip5 = { "sk_barney_dmg_gunwhip5", "0" };
cvar_t sk_barney_dmg_gunwhip6 = { "sk_barney_dmg_gunwhip6", "0" };

// Bullsquid
cvar_t sk_bullsquid_health1 = { "sk_bullsquid_health1", "0" };
cvar_t sk_bullsquid_health2 = { "sk_bullsquid_health2", "0" };
cvar_t sk_bullsquid_health3 = { "sk_bullsquid_health3", "0" };
cvar_t sk_bullsquid_health4 = { "sk_bullsquid_health4", "0" };
cvar_t sk_bullsquid_health5 = { "sk_bullsquid_health5", "0" };
cvar_t sk_bullsquid_health6 = { "sk_bullsquid_health6", "0" };

cvar_t sk_bullsquid_dmg_bite1 = { "sk_bullsquid_dmg_bite1", "0" };
cvar_t sk_bullsquid_dmg_bite2 = { "sk_bullsquid_dmg_bite2", "0" };
cvar_t sk_bullsquid_dmg_bite3 = { "sk_bullsquid_dmg_bite3", "0" };
cvar_t sk_bullsquid_dmg_bite4 = { "sk_bullsquid_dmg_bite4", "0" };
cvar_t sk_bullsquid_dmg_bite5 = { "sk_bullsquid_dmg_bite5", "0" };
cvar_t sk_bullsquid_dmg_bite6 = { "sk_bullsquid_dmg_bite6", "0" };

cvar_t sk_bullsquid_dmg_whip1 = { "sk_bullsquid_dmg_whip1", "0" };
cvar_t sk_bullsquid_dmg_whip2 = { "sk_bullsquid_dmg_whip2", "0" };
cvar_t sk_bullsquid_dmg_whip3 = { "sk_bullsquid_dmg_whip3", "0" };
cvar_t sk_bullsquid_dmg_whip4 = { "sk_bullsquid_dmg_whip4", "0" };
cvar_t sk_bullsquid_dmg_whip5 = { "sk_bullsquid_dmg_whip5", "0" };
cvar_t sk_bullsquid_dmg_whip6 = { "sk_bullsquid_dmg_whip6", "0" };

cvar_t sk_bullsquid_dmg_spit1 = { "sk_bullsquid_dmg_spit1", "0" };
cvar_t sk_bullsquid_dmg_spit2 = { "sk_bullsquid_dmg_spit2", "0" };
cvar_t sk_bullsquid_dmg_spit3 = { "sk_bullsquid_dmg_spit3", "0" };
cvar_t sk_bullsquid_dmg_spit4 = { "sk_bullsquid_dmg_spit4", "0" };
cvar_t sk_bullsquid_dmg_spit5 = { "sk_bullsquid_dmg_spit5", "0" };
cvar_t sk_bullsquid_dmg_spit6 = { "sk_bullsquid_dmg_spit6", "0" };

// Big momma
cvar_t sk_bigmomma_health1 = { "sk_bigmomma_health1", "0" };
cvar_t sk_bigmomma_health2 = { "sk_bigmomma_health2", "0" };
cvar_t sk_bigmomma_health3 = { "sk_bigmomma_health3", "0" };
cvar_t sk_bigmomma_health4 = { "sk_bigmomma_health4", "0" };
cvar_t sk_bigmomma_health5 = { "sk_bigmomma_health5", "0" };
cvar_t sk_bigmomma_health6 = { "sk_bigmomma_health6", "0" };

cvar_t sk_bigmomma_health_factor1 = { "sk_bigmomma_health_factor1", "1.0" };
cvar_t sk_bigmomma_health_factor2 = { "sk_bigmomma_health_factor2", "1.5" };
cvar_t sk_bigmomma_health_factor3 = { "sk_bigmomma_health_factor3", "2.0" };
cvar_t sk_bigmomma_health_factor4 = { "sk_bigmomma_health_factor4", "2.5" };
cvar_t sk_bigmomma_health_factor5 = { "sk_bigmomma_health_factor5", "3.0" };
cvar_t sk_bigmomma_health_factor6 = { "sk_bigmomma_health_factor6", "5.0" };

cvar_t sk_bigmomma_dmg_slash1 = { "sk_bigmomma_dmg_slash1", "50" };
cvar_t sk_bigmomma_dmg_slash2 = { "sk_bigmomma_dmg_slash2", "60" };
cvar_t sk_bigmomma_dmg_slash3 = { "sk_bigmomma_dmg_slash3", "70" };
cvar_t sk_bigmomma_dmg_slash4 = { "sk_bigmomma_dmg_slash4", "80" };
cvar_t sk_bigmomma_dmg_slash5 = { "sk_bigmomma_dmg_slash5", "90" };
cvar_t sk_bigmomma_dmg_slash6 = { "sk_bigmomma_dmg_slash6", "100" };

cvar_t sk_bigmomma_dmg_blast1 = { "sk_bigmomma_dmg_blast1", "100" };
cvar_t sk_bigmomma_dmg_blast2 = { "sk_bigmomma_dmg_blast2", "120" };
cvar_t sk_bigmomma_dmg_blast3 = { "sk_bigmomma_dmg_blast3", "150" };
cvar_t sk_bigmomma_dmg_blast4 = { "sk_bigmomma_dmg_blast4", "190" };
cvar_t sk_bigmomma_dmg_blast5 = { "sk_bigmomma_dmg_blast5", "240" };
cvar_t sk_bigmomma_dmg_blast6 = { "sk_bigmomma_dmg_blast6", "300" };

cvar_t sk_bigmomma_radius_blast1 = { "sk_bigmomma_radius_blast1", "250" };
cvar_t sk_bigmomma_radius_blast2 = { "sk_bigmomma_radius_blast2", "275" };
cvar_t sk_bigmomma_radius_blast3 = { "sk_bigmomma_radius_blast3", "300" };
cvar_t sk_bigmomma_radius_blast4 = { "sk_bigmomma_radius_blast4", "325" };
cvar_t sk_bigmomma_radius_blast5 = { "sk_bigmomma_radius_blast5", "350" };
cvar_t sk_bigmomma_radius_blast6 = { "sk_bigmomma_radius_blast6", "400" };

cvar_t sk_bigmomma_dmg_ram1 = { "sk_bigmomma_dmg_ram1", "0" };
cvar_t sk_bigmomma_dmg_ram2 = { "sk_bigmomma_dmg_ram2", "0" };
cvar_t sk_bigmomma_dmg_ram3 = { "sk_bigmomma_dmg_ram3", "0" };
cvar_t sk_bigmomma_dmg_ram4 = { "sk_bigmomma_dmg_ram4", "0" };
cvar_t sk_bigmomma_dmg_ram5 = { "sk_bigmomma_dmg_ram5", "0" };
cvar_t sk_bigmomma_dmg_ram6 = { "sk_bigmomma_dmg_ram6", "0" };

// Gargantua
cvar_t sk_gargantua_health1 = { "sk_gargantua_health1", "0" };
cvar_t sk_gargantua_health2 = { "sk_gargantua_health2", "0" };
cvar_t sk_gargantua_health3 = { "sk_gargantua_health3", "0" };
cvar_t sk_gargantua_health4 = { "sk_gargantua_health4", "0" };
cvar_t sk_gargantua_health5 = { "sk_gargantua_health5", "0" };
cvar_t sk_gargantua_health6 = { "sk_gargantua_health6", "0" };

cvar_t sk_gargantua_dmg_slash1 = { "sk_gargantua_dmg_slash1", "0" };
cvar_t sk_gargantua_dmg_slash2 = { "sk_gargantua_dmg_slash2", "0" };
cvar_t sk_gargantua_dmg_slash3 = { "sk_gargantua_dmg_slash3", "0" };
cvar_t sk_gargantua_dmg_slash4 = { "sk_gargantua_dmg_slash4", "0" };
cvar_t sk_gargantua_dmg_slash5 = { "sk_gargantua_dmg_slash5", "0" };
cvar_t sk_gargantua_dmg_slash6 = { "sk_gargantua_dmg_slash6", "0" };

cvar_t sk_gargantua_dmg_fire1 = { "sk_gargantua_dmg_fire1", "0" };
cvar_t sk_gargantua_dmg_fire2 = { "sk_gargantua_dmg_fire2", "0" };
cvar_t sk_gargantua_dmg_fire3 = { "sk_gargantua_dmg_fire3", "0" };
cvar_t sk_gargantua_dmg_fire4 = { "sk_gargantua_dmg_fire4", "0" };
cvar_t sk_gargantua_dmg_fire5 = { "sk_gargantua_dmg_fire5", "0" };
cvar_t sk_gargantua_dmg_fire6 = { "sk_gargantua_dmg_fire6", "0" };

cvar_t sk_gargantua_dmg_stomp1 = { "sk_gargantua_dmg_stomp1", "0" };
cvar_t sk_gargantua_dmg_stomp2 = { "sk_gargantua_dmg_stomp2", "0" };
cvar_t sk_gargantua_dmg_stomp3 = { "sk_gargantua_dmg_stomp3", "0" };
cvar_t sk_gargantua_dmg_stomp4 = { "sk_gargantua_dmg_stomp4", "0" };
cvar_t sk_gargantua_dmg_stomp5 = { "sk_gargantua_dmg_stomp5", "0" };
cvar_t sk_gargantua_dmg_stomp6 = { "sk_gargantua_dmg_stomp6", "0" };

// Hassassin
cvar_t sk_hassassin_health1 = { "sk_hassassin_health1", "0" };
cvar_t sk_hassassin_health2 = { "sk_hassassin_health2", "0" };
cvar_t sk_hassassin_health3 = { "sk_hassassin_health3", "0" };
cvar_t sk_hassassin_health4 = { "sk_hassassin_health4", "0" };
cvar_t sk_hassassin_health5 = { "sk_hassassin_health5", "0" };
cvar_t sk_hassassin_health6 = { "sk_hassassin_health6", "0" };

cvar_t sk_hassassin_dmg_kick1 = { "sk_hassassin_dmg_kick1", "0" };
cvar_t sk_hassassin_dmg_kick2 = { "sk_hassassin_dmg_kick2", "0" };
cvar_t sk_hassassin_dmg_kick3 = { "sk_hassassin_dmg_kick3", "0" };
cvar_t sk_hassassin_dmg_kick4 = { "sk_hassassin_dmg_kick4", "0" };
cvar_t sk_hassassin_dmg_kick5 = { "sk_hassassin_dmg_kick5", "0" };
cvar_t sk_hassassin_dmg_kick6 = { "sk_hassassin_dmg_kick6", "0" };

cvar_t sk_hassassin_dmg_punch1 = { "sk_hassassin_dmg_punch1", "0" };
cvar_t sk_hassassin_dmg_punch2 = { "sk_hassassin_dmg_punch2", "0" };
cvar_t sk_hassassin_dmg_punch3 = { "sk_hassassin_dmg_punch3", "0" };
cvar_t sk_hassassin_dmg_punch4 = { "sk_hassassin_dmg_punch4", "0" };
cvar_t sk_hassassin_dmg_punch5 = { "sk_hassassin_dmg_punch5", "0" };
cvar_t sk_hassassin_dmg_punch6 = { "sk_hassassin_dmg_punch6", "0" };

cvar_t sk_hassassin_dmg_gunwhip1 = { "sk_hassassin_dmg_gunwhip1", "0" };
cvar_t sk_hassassin_dmg_gunwhip2 = { "sk_hassassin_dmg_gunwhip2", "0" };
cvar_t sk_hassassin_dmg_gunwhip3 = { "sk_hassassin_dmg_gunwhip3", "0" };
cvar_t sk_hassassin_dmg_gunwhip4 = { "sk_hassassin_dmg_gunwhip4", "0" };
cvar_t sk_hassassin_dmg_gunwhip5 = { "sk_hassassin_dmg_gunwhip5", "0" };
cvar_t sk_hassassin_dmg_gunwhip6 = { "sk_hassassin_dmg_gunwhip6", "0" };

// Headcrab
cvar_t sk_headcrab_health1 = { "sk_headcrab_health1", "0" };
cvar_t sk_headcrab_health2 = { "sk_headcrab_health2", "0" };
cvar_t sk_headcrab_health3 = { "sk_headcrab_health3", "0" };
cvar_t sk_headcrab_health4 = { "sk_headcrab_health4", "0" };
cvar_t sk_headcrab_health5 = { "sk_headcrab_health5", "0" };
cvar_t sk_headcrab_health6 = { "sk_headcrab_health6", "0" };

cvar_t sk_headcrab_dmg_bite1 = { "sk_headcrab_dmg_bite1", "0" };
cvar_t sk_headcrab_dmg_bite2 = { "sk_headcrab_dmg_bite2", "0" };
cvar_t sk_headcrab_dmg_bite3 = { "sk_headcrab_dmg_bite3", "0" };
cvar_t sk_headcrab_dmg_bite4 = { "sk_headcrab_dmg_bite4", "0" };
cvar_t sk_headcrab_dmg_bite5 = { "sk_headcrab_dmg_bite5", "0" };
cvar_t sk_headcrab_dmg_bite6 = { "sk_headcrab_dmg_bite6", "0" };

// Human Grunt
cvar_t sk_hgrunt_health1 = { "sk_hgrunt_health1", "0" };
cvar_t sk_hgrunt_health2 = { "sk_hgrunt_health2", "0" };
cvar_t sk_hgrunt_health3 = { "sk_hgrunt_health3", "0" };
cvar_t sk_hgrunt_health4 = { "sk_hgrunt_health4", "0" };
cvar_t sk_hgrunt_health5 = { "sk_hgrunt_health5", "0" };
cvar_t sk_hgrunt_health6 = { "sk_hgrunt_health6", "0" };

cvar_t sk_hgrunt_dmg_kick1 = { "sk_hgrunt_dmg_kick1", "0" };
cvar_t sk_hgrunt_dmg_kick2 = { "sk_hgrunt_dmg_kick2", "0" };
cvar_t sk_hgrunt_dmg_kick3 = { "sk_hgrunt_dmg_kick3", "0" };
cvar_t sk_hgrunt_dmg_kick4 = { "sk_hgrunt_dmg_kick4", "0" };
cvar_t sk_hgrunt_dmg_kick5 = { "sk_hgrunt_dmg_kick5", "0" };
cvar_t sk_hgrunt_dmg_kick6 = { "sk_hgrunt_dmg_kick6", "0" };

cvar_t sk_hgrunt_dmg_punch1 = { "sk_hgrunt_dmg_punch1", "0" };
cvar_t sk_hgrunt_dmg_punch2 = { "sk_hgrunt_dmg_punch2", "0" };
cvar_t sk_hgrunt_dmg_punch3 = { "sk_hgrunt_dmg_punch3", "0" };
cvar_t sk_hgrunt_dmg_punch4 = { "sk_hgrunt_dmg_punch4", "0" };
cvar_t sk_hgrunt_dmg_punch5 = { "sk_hgrunt_dmg_punch5", "0" };
cvar_t sk_hgrunt_dmg_punch6 = { "sk_hgrunt_dmg_punch6", "0" };

cvar_t sk_hgrunt_dmg_gunwhip1 = { "sk_hgrunt_dmg_gunwhip1", "0" };
cvar_t sk_hgrunt_dmg_gunwhip2 = { "sk_hgrunt_dmg_gunwhip2", "0" };
cvar_t sk_hgrunt_dmg_gunwhip3 = { "sk_hgrunt_dmg_gunwhip3", "0" };
cvar_t sk_hgrunt_dmg_gunwhip4 = { "sk_hgrunt_dmg_gunwhip4", "0" };
cvar_t sk_hgrunt_dmg_gunwhip5 = { "sk_hgrunt_dmg_gunwhip5", "0" };
cvar_t sk_hgrunt_dmg_gunwhip6 = { "sk_hgrunt_dmg_gunwhip6", "0" };

// Houndeye
cvar_t sk_houndeye_health1 = { "sk_houndeye_health1", "0" };
cvar_t sk_houndeye_health2 = { "sk_houndeye_health2", "0" };
cvar_t sk_houndeye_health3 = { "sk_houndeye_health3", "0" };
cvar_t sk_houndeye_health4 = { "sk_houndeye_health4", "0" };
cvar_t sk_houndeye_health5 = { "sk_houndeye_health5", "0" };
cvar_t sk_houndeye_health6 = { "sk_houndeye_health6", "0" };

cvar_t sk_houndeye_dmg_blast1 = { "sk_houndeye_dmg_blast1", "0" };
cvar_t sk_houndeye_dmg_blast2 = { "sk_houndeye_dmg_blast2", "0" };
cvar_t sk_houndeye_dmg_blast3 = { "sk_houndeye_dmg_blast3", "0" };
cvar_t sk_houndeye_dmg_blast4 = { "sk_houndeye_dmg_blast4", "0" };
cvar_t sk_houndeye_dmg_blast5 = { "sk_houndeye_dmg_blast5", "0" };
cvar_t sk_houndeye_dmg_blast6 = { "sk_houndeye_dmg_blast6", "0" };

cvar_t sk_houndeye_dmg_bark1 = { "sk_houndeye_dmg_bark1", "0" };
cvar_t sk_houndeye_dmg_bark2 = { "sk_houndeye_dmg_bark2", "0" };
cvar_t sk_houndeye_dmg_bark3 = { "sk_houndeye_dmg_bark3", "0" };
cvar_t sk_houndeye_dmg_bark4 = { "sk_houndeye_dmg_bark4", "0" };
cvar_t sk_houndeye_dmg_bark5 = { "sk_houndeye_dmg_bark5", "0" };
cvar_t sk_houndeye_dmg_bark6 = { "sk_houndeye_dmg_bark6", "0" };

// ISlave
cvar_t sk_islave_health1 = { "sk_islave_health1", "0" };
cvar_t sk_islave_health2 = { "sk_islave_health2", "0" };
cvar_t sk_islave_health3 = { "sk_islave_health3", "0" };
cvar_t sk_islave_health4 = { "sk_islave_health4", "0" };
cvar_t sk_islave_health5 = { "sk_islave_health5", "0" };
cvar_t sk_islave_health6 = { "sk_islave_health6", "0" };

cvar_t sk_islave_dmg_claw1 = { "sk_islave_dmg_claw1", "0" };
cvar_t sk_islave_dmg_claw2 = { "sk_islave_dmg_claw2", "0" };
cvar_t sk_islave_dmg_claw3 = { "sk_islave_dmg_claw3", "0" };
cvar_t sk_islave_dmg_claw4 = { "sk_islave_dmg_claw4", "0" };
cvar_t sk_islave_dmg_claw5 = { "sk_islave_dmg_claw5", "0" };
cvar_t sk_islave_dmg_claw6 = { "sk_islave_dmg_claw6", "0" };

cvar_t sk_islave_dmg_clawrake1 = { "sk_islave_dmg_clawrake1", "0" };
cvar_t sk_islave_dmg_clawrake2 = { "sk_islave_dmg_clawrake2", "0" };
cvar_t sk_islave_dmg_clawrake3 = { "sk_islave_dmg_clawrake3", "0" };
cvar_t sk_islave_dmg_clawrake4 = { "sk_islave_dmg_clawrake4", "0" };
cvar_t sk_islave_dmg_clawrake5 = { "sk_islave_dmg_clawrake5", "0" };
cvar_t sk_islave_dmg_clawrake6 = { "sk_islave_dmg_clawrake6", "0" };

cvar_t sk_islave_dmg_zap1 = { "sk_islave_dmg_zap1", "0" };
cvar_t sk_islave_dmg_zap2 = { "sk_islave_dmg_zap2", "0" };
cvar_t sk_islave_dmg_zap3 = { "sk_islave_dmg_zap3", "0" };
cvar_t sk_islave_dmg_zap4 = { "sk_islave_dmg_zap4", "0" };
cvar_t sk_islave_dmg_zap5 = { "sk_islave_dmg_zap5", "0" };
cvar_t sk_islave_dmg_zap6 = { "sk_islave_dmg_zap6", "0" };

cvar_t sk_islave_dmg_zapstomp1 = { "sk_islave_dmg_zapstomp1", "0" };
cvar_t sk_islave_dmg_zapstomp2 = { "sk_islave_dmg_zapstomp2", "0" };
cvar_t sk_islave_dmg_zapstomp3 = { "sk_islave_dmg_zapstomp3", "0" };
cvar_t sk_islave_dmg_zapstomp4 = { "sk_islave_dmg_zapstomp4", "0" };
cvar_t sk_islave_dmg_zapstomp5 = { "sk_islave_dmg_zapstomp5", "0" };
cvar_t sk_islave_dmg_zapstomp6 = { "sk_islave_dmg_zapstomp6", "0" };

cvar_t sk_islave_heal1 = { "sk_islave_heal1", "0" };
cvar_t sk_islave_heal2 = { "sk_islave_heal2", "0" };
cvar_t sk_islave_heal3 = { "sk_islave_heal3", "0" };
cvar_t sk_islave_heal4 = { "sk_islave_heal4", "0" };
cvar_t sk_islave_heal5 = { "sk_islave_heal5", "0" };
cvar_t sk_islave_heal6 = { "sk_islave_heal6", "0" };

cvar_t sk_islave_power1 = { "sk_islave_power1", "0" };
cvar_t sk_islave_power2 = { "sk_islave_power2", "0" };
cvar_t sk_islave_power3 = { "sk_islave_power3", "0" };
cvar_t sk_islave_power4 = { "sk_islave_power4", "0" };
cvar_t sk_islave_power5 = { "sk_islave_power5", "0" };
cvar_t sk_islave_power6 = { "sk_islave_power6", "0" };

// Icthyosaur
cvar_t sk_ichthyosaur_health1 = { "sk_ichthyosaur_health1", "0" };
cvar_t sk_ichthyosaur_health2 = { "sk_ichthyosaur_health2", "0" };
cvar_t sk_ichthyosaur_health3 = { "sk_ichthyosaur_health3", "0" };
cvar_t sk_ichthyosaur_health4 = { "sk_ichthyosaur_health4", "0" };
cvar_t sk_ichthyosaur_health5 = { "sk_ichthyosaur_health5", "0" };
cvar_t sk_ichthyosaur_health6 = { "sk_ichthyosaur_health6", "0" };

cvar_t sk_ichthyosaur_dmg_chomp1 = { "sk_ichthyosaur_dmg_chomp1", "0" };
cvar_t sk_ichthyosaur_dmg_chomp2 = { "sk_ichthyosaur_dmg_chomp2", "0" };
cvar_t sk_ichthyosaur_dmg_chomp3 = { "sk_ichthyosaur_dmg_chomp3", "0" };
cvar_t sk_ichthyosaur_dmg_chomp4 = { "sk_ichthyosaur_dmg_chomp4", "0" };
cvar_t sk_ichthyosaur_dmg_chomp5 = { "sk_ichthyosaur_dmg_chomp5", "0" };
cvar_t sk_ichthyosaur_dmg_chomp6 = { "sk_ichthyosaur_dmg_chomp6", "0" };

// Leech
cvar_t sk_leech_health1 = { "sk_leech_health1", "0" };
cvar_t sk_leech_health2 = { "sk_leech_health2", "0" };
cvar_t sk_leech_health3 = { "sk_leech_health3", "0" };
cvar_t sk_leech_health4 = { "sk_leech_health4", "0" };
cvar_t sk_leech_health5 = { "sk_leech_health5", "0" };
cvar_t sk_leech_health6 = { "sk_leech_health6", "0" };

cvar_t sk_leech_dmg_bite1 = { "sk_leech_dmg_bite1", "0" };
cvar_t sk_leech_dmg_bite2 = { "sk_leech_dmg_bite2", "0" };
cvar_t sk_leech_dmg_bite3 = { "sk_leech_dmg_bite3", "0" };
cvar_t sk_leech_dmg_bite4 = { "sk_leech_dmg_bite4", "0" };
cvar_t sk_leech_dmg_bite5 = { "sk_leech_dmg_bite5", "0" };
cvar_t sk_leech_dmg_bite6 = { "sk_leech_dmg_bite6", "0" };

// Controller
cvar_t sk_controller_health1 = { "sk_controller_health1", "0" };
cvar_t sk_controller_health2 = { "sk_controller_health2", "0" };
cvar_t sk_controller_health3 = { "sk_controller_health3", "0" };
cvar_t sk_controller_health4 = { "sk_controller_health4", "0" };
cvar_t sk_controller_health5 = { "sk_controller_health5", "0" };
cvar_t sk_controller_health6 = { "sk_controller_health6", "0" };

cvar_t sk_controller_speed_ball1 = { "sk_controller_speed_ball1", "0" };
cvar_t sk_controller_speed_ball2 = { "sk_controller_speed_ball2", "0" };
cvar_t sk_controller_speed_ball3 = { "sk_controller_speed_ball3", "0" };
cvar_t sk_controller_speed_ball4 = { "sk_controller_speed_ball4", "0" };
cvar_t sk_controller_speed_ball5 = { "sk_controller_speed_ball5", "0" };
cvar_t sk_controller_speed_ball6 = { "sk_controller_speed_ball6", "0" };

cvar_t sk_controller_dmg_ball1 = { "sk_controller_dmg_ball1", "0" };
cvar_t sk_controller_dmg_ball2 = { "sk_controller_dmg_ball2", "0" };
cvar_t sk_controller_dmg_ball3 = { "sk_controller_dmg_ball3", "0" };
cvar_t sk_controller_dmg_ball4 = { "sk_controller_dmg_ball4", "0" };
cvar_t sk_controller_dmg_ball5 = { "sk_controller_dmg_ball5", "0" };
cvar_t sk_controller_dmg_ball6 = { "sk_controller_dmg_ball6", "0" };

cvar_t sk_controller_dmg_zap1 = { "sk_controller_dmg_zap1", "0" };
cvar_t sk_controller_dmg_zap2 = { "sk_controller_dmg_zap2", "0" };
cvar_t sk_controller_dmg_zap3 = { "sk_controller_dmg_zap3", "0" };
cvar_t sk_controller_dmg_zap4 = { "sk_controller_dmg_zap4", "0" };
cvar_t sk_controller_dmg_zap5 = { "sk_controller_dmg_zap5", "0" };
cvar_t sk_controller_dmg_zap6 = { "sk_controller_dmg_zap6", "0" };

cvar_t sk_controller_dmg_slash1 = { "sk_controller_dmg_slash1", "0" };
cvar_t sk_controller_dmg_slash2 = { "sk_controller_dmg_slash2", "0" };
cvar_t sk_controller_dmg_slash3 = { "sk_controller_dmg_slash3", "0" };
cvar_t sk_controller_dmg_slash4 = { "sk_controller_dmg_slash4", "0" };
cvar_t sk_controller_dmg_slash5 = { "sk_controller_dmg_slash5", "0" };
cvar_t sk_controller_dmg_slash6 = { "sk_controller_dmg_slash6", "0" };

// Nihilanth
cvar_t sk_nihilanth_health1 = { "sk_nihilanth_health1", "0" };
cvar_t sk_nihilanth_health2 = { "sk_nihilanth_health2", "0" };
cvar_t sk_nihilanth_health3 = { "sk_nihilanth_health3", "0" };
cvar_t sk_nihilanth_health4 = { "sk_nihilanth_health4", "0" };
cvar_t sk_nihilanth_health5 = { "sk_nihilanth_health5", "0" };
cvar_t sk_nihilanth_health6 = { "sk_nihilanth_health6", "0" };

cvar_t sk_nihilanth_speed_ball1 = { "sk_nihilanth_speed_ball1", "0" };
cvar_t sk_nihilanth_speed_ball2 = { "sk_nihilanth_speed_ball2", "0" };
cvar_t sk_nihilanth_speed_ball3 = { "sk_nihilanth_speed_ball3", "0" };
cvar_t sk_nihilanth_speed_ball4 = { "sk_nihilanth_speed_ball4", "0" };
cvar_t sk_nihilanth_speed_ball5 = { "sk_nihilanth_speed_ball5", "0" };
cvar_t sk_nihilanth_speed_ball6 = { "sk_nihilanth_speed_ball6", "0" };

cvar_t sk_nihilanth_dmg_ball1 = { "sk_nihilanth_dmg_ball1", "0" };
cvar_t sk_nihilanth_dmg_ball2 = { "sk_nihilanth_dmg_ball2", "0" };
cvar_t sk_nihilanth_dmg_ball3 = { "sk_nihilanth_dmg_ball3", "0" };
cvar_t sk_nihilanth_dmg_ball4 = { "sk_nihilanth_dmg_ball4", "0" };
cvar_t sk_nihilanth_dmg_ball5 = { "sk_nihilanth_dmg_ball5", "0" };
cvar_t sk_nihilanth_dmg_ball6 = { "sk_nihilanth_dmg_ball6", "0" };

cvar_t sk_nihilanth_dmg_zap1 = { "sk_nihilanth_dmg_zap1", "0" };
cvar_t sk_nihilanth_dmg_zap2 = { "sk_nihilanth_dmg_zap2", "0" };
cvar_t sk_nihilanth_dmg_zap3 = { "sk_nihilanth_dmg_zap3", "0" };
cvar_t sk_nihilanth_dmg_zap4 = { "sk_nihilanth_dmg_zap4", "0" };
cvar_t sk_nihilanth_dmg_zap5 = { "sk_nihilanth_dmg_zap5", "0" };
cvar_t sk_nihilanth_dmg_zap6 = { "sk_nihilanth_dmg_zap6", "0" };

cvar_t sk_nihilanth_dmg_slash1 = { "sk_nihilanth_dmg_slash1", "0" };
cvar_t sk_nihilanth_dmg_slash2 = { "sk_nihilanth_dmg_slash2", "0" };
cvar_t sk_nihilanth_dmg_slash3 = { "sk_nihilanth_dmg_slash3", "0" };
cvar_t sk_nihilanth_dmg_slash4 = { "sk_nihilanth_dmg_slash4", "0" };
cvar_t sk_nihilanth_dmg_slash5 = { "sk_nihilanth_dmg_slash5", "0" };
cvar_t sk_nihilanth_dmg_slash6 = { "sk_nihilanth_dmg_slash6", "0" };

// Scientist
cvar_t sk_scientist_health1 = { "sk_scientist_health1", "0" };
cvar_t sk_scientist_health2 = { "sk_scientist_health2", "0" };
cvar_t sk_scientist_health3 = { "sk_scientist_health3", "0" };
cvar_t sk_scientist_health4 = { "sk_scientist_health4", "0" };
cvar_t sk_scientist_health5 = { "sk_scientist_health5", "0" };
cvar_t sk_scientist_health6 = { "sk_scientist_health6", "0" };

cvar_t sk_scientist_dmg_punch1 = { "sk_scientist_dmg_punch1", "0" };
cvar_t sk_scientist_dmg_punch2 = { "sk_scientist_dmg_punch2", "0" };
cvar_t sk_scientist_dmg_punch3 = { "sk_scientist_dmg_punch3", "0" };
cvar_t sk_scientist_dmg_punch4 = { "sk_scientist_dmg_punch4", "0" };
cvar_t sk_scientist_dmg_punch5 = { "sk_scientist_dmg_punch5", "0" };
cvar_t sk_scientist_dmg_punch6 = { "sk_scientist_dmg_punch6", "0" };

cvar_t sk_scientist_dmg_kick1 = { "sk_scientist_dmg_kick1", "0" };
cvar_t sk_scientist_dmg_kick2 = { "sk_scientist_dmg_kick2", "0" };
cvar_t sk_scientist_dmg_kick3 = { "sk_scientist_dmg_kick3", "0" };
cvar_t sk_scientist_dmg_kick4 = { "sk_scientist_dmg_kick4", "0" };
cvar_t sk_scientist_dmg_kick5 = { "sk_scientist_dmg_kick5", "0" };
cvar_t sk_scientist_dmg_kick6 = { "sk_scientist_dmg_kick6", "0" };

cvar_t sk_scientist_heal1 = { "sk_scientist_heal1", "0" };
cvar_t sk_scientist_heal2 = { "sk_scientist_heal2", "0" };
cvar_t sk_scientist_heal3 = { "sk_scientist_heal3", "0" };
cvar_t sk_scientist_heal4 = { "sk_scientist_heal4", "0" };
cvar_t sk_scientist_heal5 = { "sk_scientist_heal5", "0" };
cvar_t sk_scientist_heal6 = { "sk_scientist_heal6", "0" };

// Zombie
cvar_t sk_zombie_health1 = { "sk_zombie_health1", "0" };
cvar_t sk_zombie_health2 = { "sk_zombie_health2", "0" };
cvar_t sk_zombie_health3 = { "sk_zombie_health3", "0" };
cvar_t sk_zombie_health4 = { "sk_zombie_health4", "0" };
cvar_t sk_zombie_health5 = { "sk_zombie_health5", "0" };
cvar_t sk_zombie_health6 = { "sk_zombie_health6", "0" };

cvar_t sk_zombie_dmg_one_slash1 = { "sk_zombie_dmg_one_slash1", "0" };
cvar_t sk_zombie_dmg_one_slash2 = { "sk_zombie_dmg_one_slash2", "0" };
cvar_t sk_zombie_dmg_one_slash3 = { "sk_zombie_dmg_one_slash3", "0" };
cvar_t sk_zombie_dmg_one_slash4 = { "sk_zombie_dmg_one_slash4", "0" };
cvar_t sk_zombie_dmg_one_slash5 = { "sk_zombie_dmg_one_slash5", "0" };
cvar_t sk_zombie_dmg_one_slash6 = { "sk_zombie_dmg_one_slash6", "0" };

cvar_t sk_zombie_dmg_both_slash1 = { "sk_zombie_dmg_both_slash1", "0" };
cvar_t sk_zombie_dmg_both_slash2 = { "sk_zombie_dmg_both_slash2", "0" };
cvar_t sk_zombie_dmg_both_slash3 = { "sk_zombie_dmg_both_slash3", "0" };
cvar_t sk_zombie_dmg_both_slash4 = { "sk_zombie_dmg_both_slash4", "0" };
cvar_t sk_zombie_dmg_both_slash5 = { "sk_zombie_dmg_both_slash5", "0" };
cvar_t sk_zombie_dmg_both_slash6 = { "sk_zombie_dmg_both_slash6", "0" };

// Gonome
cvar_t sk_gonome_health1 = { "sk_gonome_health1", "0" };
cvar_t sk_gonome_health2 = { "sk_gonome_health2", "0" };
cvar_t sk_gonome_health3 = { "sk_gonome_health3", "0" };
cvar_t sk_gonome_health4 = { "sk_gonome_health4", "0" };
cvar_t sk_gonome_health5 = { "sk_gonome_health5", "0" };
cvar_t sk_gonome_health6 = { "sk_gonome_health6", "0" };

cvar_t sk_gonome_headcrab_health1 = { "sk_gonome_headcrab_health1", "0" };
cvar_t sk_gonome_headcrab_health2 = { "sk_gonome_headcrab_health2", "0" };
cvar_t sk_gonome_headcrab_health3 = { "sk_gonome_headcrab_health3", "0" };
cvar_t sk_gonome_headcrab_health4 = { "sk_gonome_headcrab_health4", "0" };
cvar_t sk_gonome_headcrab_health5 = { "sk_gonome_headcrab_health5", "0" };
cvar_t sk_gonome_headcrab_health6 = { "sk_gonome_headcrab_health6", "0" };

cvar_t sk_gonome_dmg_slash1 = { "sk_gonome_dmg_slash1", "0" };
cvar_t sk_gonome_dmg_slash2 = { "sk_gonome_dmg_slash2", "0" };
cvar_t sk_gonome_dmg_slash3 = { "sk_gonome_dmg_slash3", "0" };
cvar_t sk_gonome_dmg_slash4 = { "sk_gonome_dmg_slash4", "0" };
cvar_t sk_gonome_dmg_slash5 = { "sk_gonome_dmg_slash5", "0" };
cvar_t sk_gonome_dmg_slash6 = { "sk_gonome_dmg_slash6", "0" };

cvar_t sk_gonome_dmg_chomp1 = { "sk_gonome_dmg_chomp1", "0" };
cvar_t sk_gonome_dmg_chomp2 = { "sk_gonome_dmg_chomp2", "0" };
cvar_t sk_gonome_dmg_chomp3 = { "sk_gonome_dmg_chomp3", "0" };
cvar_t sk_gonome_dmg_chomp4 = { "sk_gonome_dmg_chomp4", "0" };
cvar_t sk_gonome_dmg_chomp5 = { "sk_gonome_dmg_chomp5", "0" };
cvar_t sk_gonome_dmg_chomp6 = { "sk_gonome_dmg_chomp6", "0" };

cvar_t sk_gonome_dmg_leap1 = { "sk_gonome_dmg_leap1", "0" };
cvar_t sk_gonome_dmg_leap2 = { "sk_gonome_dmg_leap2", "0" };
cvar_t sk_gonome_dmg_leap3 = { "sk_gonome_dmg_leap3", "0" };
cvar_t sk_gonome_dmg_leap4 = { "sk_gonome_dmg_leap4", "0" };
cvar_t sk_gonome_dmg_leap5 = { "sk_gonome_dmg_leap5", "0" };
cvar_t sk_gonome_dmg_leap6 = { "sk_gonome_dmg_leap6", "0" };

cvar_t sk_gonome_dmg_acid1 = { "sk_gonome_dmg_acid1", "0" };
cvar_t sk_gonome_dmg_acid2 = { "sk_gonome_dmg_acid2", "0" };
cvar_t sk_gonome_dmg_acid3 = { "sk_gonome_dmg_acid3", "0" };
cvar_t sk_gonome_dmg_acid4 = { "sk_gonome_dmg_acid4", "0" };
cvar_t sk_gonome_dmg_acid5 = { "sk_gonome_dmg_acid5", "0" };
cvar_t sk_gonome_dmg_acid6 = { "sk_gonome_dmg_acid6", "0" };

//Turret
cvar_t sk_turret_health1 = { "sk_turret_health1", "0" };
cvar_t sk_turret_health2 = { "sk_turret_health2", "0" };
cvar_t sk_turret_health3 = { "sk_turret_health3", "0" };
cvar_t sk_turret_health4 = { "sk_turret_health4", "0" };
cvar_t sk_turret_health5 = { "sk_turret_health5", "0" };
cvar_t sk_turret_health6 = { "sk_turret_health6", "0" };

// MiniTurret
cvar_t sk_miniturret_health1 = { "sk_miniturret_health1", "0" };
cvar_t sk_miniturret_health2 = { "sk_miniturret_health2", "0" };
cvar_t sk_miniturret_health3 = { "sk_miniturret_health3", "0" };
cvar_t sk_miniturret_health4 = { "sk_miniturret_health4", "0" };
cvar_t sk_miniturret_health5 = { "sk_miniturret_health5", "0" };
cvar_t sk_miniturret_health6 = { "sk_miniturret_health6", "0" };

// Sentry Turret
cvar_t sk_sentry_health1 = { "sk_sentry_health1", "0" };
cvar_t sk_sentry_health2 = { "sk_sentry_health2", "0" };
cvar_t sk_sentry_health3 = { "sk_sentry_health3", "0" };
cvar_t sk_sentry_health4 = { "sk_sentry_health4", "0" };
cvar_t sk_sentry_health5 = { "sk_sentry_health5", "0" };
cvar_t sk_sentry_health6 = { "sk_sentry_health6", "0" };

// Shock Trooper
cvar_t sk_strooper_health1 = { "sk_strooper_health1", "0" };
cvar_t sk_strooper_health2 = { "sk_strooper_health2", "0" };
cvar_t sk_strooper_health3 = { "sk_strooper_health3", "0" };
cvar_t sk_strooper_health4 = { "sk_strooper_health4", "0" };
cvar_t sk_strooper_health5 = { "sk_strooper_health5", "0" };
cvar_t sk_strooper_health6 = { "sk_strooper_health6", "0" };

cvar_t sk_strooper_dmg_bite1 = { "sk_strooper_dmg_bite1", "0" };
cvar_t sk_strooper_dmg_bite2 = { "sk_strooper_dmg_bite2", "0" };
cvar_t sk_strooper_dmg_bite3 = { "sk_strooper_dmg_bite3", "0" };
cvar_t sk_strooper_dmg_bite4 = { "sk_strooper_dmg_bite4", "0" };
cvar_t sk_strooper_dmg_bite5 = { "sk_strooper_dmg_bite5", "0" };
cvar_t sk_strooper_dmg_bite6 = { "sk_strooper_dmg_bite6", "0" };

cvar_t sk_strooper_dmg_slap1 = { "sk_strooper_dmg_slap1", "0" };
cvar_t sk_strooper_dmg_slap2 = { "sk_strooper_dmg_slap2", "0" };
cvar_t sk_strooper_dmg_slap3 = { "sk_strooper_dmg_slap3", "0" };
cvar_t sk_strooper_dmg_slap4 = { "sk_strooper_dmg_slap4", "0" };
cvar_t sk_strooper_dmg_slap5 = { "sk_strooper_dmg_slap5", "0" };
cvar_t sk_strooper_dmg_slap6 = { "sk_strooper_dmg_slap6", "0" };

cvar_t sk_strooper_dmg_palm1 = { "sk_strooper_dmg_palm1", "0" };
cvar_t sk_strooper_dmg_palm2 = { "sk_strooper_dmg_palm2", "0" };
cvar_t sk_strooper_dmg_palm3 = { "sk_strooper_dmg_palm3", "0" };
cvar_t sk_strooper_dmg_palm4 = { "sk_strooper_dmg_palm4", "0" };
cvar_t sk_strooper_dmg_palm5 = { "sk_strooper_dmg_palm5", "0" };
cvar_t sk_strooper_dmg_palm6 = { "sk_strooper_dmg_palm6", "0" };

// =========================== //
//           WEAPONS           //
// =========================== //

// === 1 - MELEE === //

// Fists
cvar_t sk_plr_punch1 = { "sk_plr_punch1", "0" };
cvar_t sk_plr_punch2 = { "sk_plr_punch2", "0" };
cvar_t sk_plr_punch3 = { "sk_plr_punch3", "0" };
cvar_t sk_plr_punch4 = { "sk_plr_punch4", "0" };
cvar_t sk_plr_punch5 = { "sk_plr_punch5", "0" };
cvar_t sk_plr_punch6 = { "sk_plr_punch6", "0" };

cvar_t sk_plr_uppercut1 = { "sk_plr_uppercut1", "0" };
cvar_t sk_plr_uppercut2 = { "sk_plr_uppercut2", "0" };
cvar_t sk_plr_uppercut3 = { "sk_plr_uppercut3", "0" };
cvar_t sk_plr_uppercut4 = { "sk_plr_uppercut4", "0" };
cvar_t sk_plr_uppercut5 = { "sk_plr_uppercut5", "0" };
cvar_t sk_plr_uppercut6 = { "sk_plr_uppercut6", "0" };

cvar_t sk_plr_kick1 = { "sk_plr_kick1", "0" };
cvar_t sk_plr_kick2 = { "sk_plr_kick2", "0" };
cvar_t sk_plr_kick3 = { "sk_plr_kick3", "0" };
cvar_t sk_plr_kick4 = { "sk_plr_kick4", "0" };
cvar_t sk_plr_kick5 = { "sk_plr_kick5", "0" };
cvar_t sk_plr_kick6 = { "sk_plr_kick6", "0" };

cvar_t sk_plr_counter1 = { "sk_plr_counter1", "0" };
cvar_t sk_plr_counter2 = { "sk_plr_counter2", "0" };
cvar_t sk_plr_counter3 = { "sk_plr_counter3", "0" };
cvar_t sk_plr_counter4 = { "sk_plr_counter4", "0" };
cvar_t sk_plr_counter5 = { "sk_plr_counter5", "0" };
cvar_t sk_plr_counter6 = { "sk_plr_counter6", "0" };

// Spanner
cvar_t sk_plr_span_light1 = { "sk_plr_span_light1", "0" };
cvar_t sk_plr_span_light2 = { "sk_plr_span_light2", "0" };
cvar_t sk_plr_span_light3 = { "sk_plr_span_light3", "0" };
cvar_t sk_plr_span_light4 = { "sk_plr_span_light4", "0" };
cvar_t sk_plr_span_light5 = { "sk_plr_span_light5", "0" };
cvar_t sk_plr_span_light6 = { "sk_plr_span_light6", "0" };

cvar_t sk_plr_span_heavy1 = { "sk_plr_span_heavy1", "0" };
cvar_t sk_plr_span_heavy2 = { "sk_plr_span_heavy2", "0" };
cvar_t sk_plr_span_heavy3 = { "sk_plr_span_heavy3", "0" };
cvar_t sk_plr_span_heavy4 = { "sk_plr_span_heavy4", "0" };
cvar_t sk_plr_span_heavy5 = { "sk_plr_span_heavy5", "0" };
cvar_t sk_plr_span_heavy6 = { "sk_plr_span_heavy6", "0" };

cvar_t sk_plr_span_thrown1 = { "sk_plr_span_thrown1", "0" };
cvar_t sk_plr_span_thrown2 = { "sk_plr_span_thrown2", "0" };
cvar_t sk_plr_span_thrown3 = { "sk_plr_span_thrown3", "0" };
cvar_t sk_plr_span_thrown4 = { "sk_plr_span_thrown4", "0" };
cvar_t sk_plr_span_thrown5 = { "sk_plr_span_thrown5", "0" };
cvar_t sk_plr_span_thrown6 = { "sk_plr_span_thrown6", "0" };

cvar_t sk_plr_span_counter1 = { "sk_plr_span_counter1", "0" };
cvar_t sk_plr_span_counter2 = { "sk_plr_span_counter2", "0" };
cvar_t sk_plr_span_counter3 = { "sk_plr_span_counter3", "0" };
cvar_t sk_plr_span_counter4 = { "sk_plr_span_counter4", "0" };
cvar_t sk_plr_span_counter5 = { "sk_plr_span_counter5", "0" };
cvar_t sk_plr_span_counter6 = { "sk_plr_span_counter6", "0" };

// Knife
cvar_t sk_plr_knife_light1 = { "sk_plr_knife_light1", "0" };
cvar_t sk_plr_knife_light2 = { "sk_plr_knife_light2", "0" };
cvar_t sk_plr_knife_light3 = { "sk_plr_knife_light3", "0" };
cvar_t sk_plr_knife_light4 = { "sk_plr_knife_light4", "0" };
cvar_t sk_plr_knife_light5 = { "sk_plr_knife_light5", "0" };
cvar_t sk_plr_knife_light6 = { "sk_plr_knife_light6", "0" };

cvar_t sk_plr_knife_heavy1 = { "sk_plr_knife_heavy1", "0" };
cvar_t sk_plr_knife_heavy2 = { "sk_plr_knife_heavy2", "0" };
cvar_t sk_plr_knife_heavy3 = { "sk_plr_knife_heavy3", "0" };
cvar_t sk_plr_knife_heavy4 = { "sk_plr_knife_heavy4", "0" };
cvar_t sk_plr_knife_heavy5 = { "sk_plr_knife_heavy5", "0" };
cvar_t sk_plr_knife_heavy6 = { "sk_plr_knife_heavy6", "0" };

cvar_t sk_plr_knife_thrown1 = { "sk_plr_knife_thrown1", "0" };
cvar_t sk_plr_knife_thrown2 = { "sk_plr_knife_thrown2", "0" };
cvar_t sk_plr_knife_thrown3 = { "sk_plr_knife_thrown3", "0" };
cvar_t sk_plr_knife_thrown4 = { "sk_plr_knife_thrown4", "0" };
cvar_t sk_plr_knife_thrown5 = { "sk_plr_knife_thrown5", "0" };
cvar_t sk_plr_knife_thrown6 = { "sk_plr_knife_thrown6", "0" };

cvar_t sk_plr_knife_counter1 = { "sk_plr_knife_counter1", "0" };
cvar_t sk_plr_knife_counter2 = { "sk_plr_knife_counter2", "0" };
cvar_t sk_plr_knife_counter3 = { "sk_plr_knife_counter3", "0" };
cvar_t sk_plr_knife_counter4 = { "sk_plr_knife_counter4", "0" };
cvar_t sk_plr_knife_counter5 = { "sk_plr_knife_counter5", "0" };
cvar_t sk_plr_knife_counter6 = { "sk_plr_knife_counter6", "0" };

// Crowbar
cvar_t sk_plr_cbar_light1 = { "sk_plr_cbar_light1", "0" };
cvar_t sk_plr_cbar_light2 = { "sk_plr_cbar_light2", "0" };
cvar_t sk_plr_cbar_light3 = { "sk_plr_cbar_light3", "0" };
cvar_t sk_plr_cbar_light4 = { "sk_plr_cbar_light4", "0" };
cvar_t sk_plr_cbar_light5 = { "sk_plr_cbar_light5", "0" };
cvar_t sk_plr_cbar_light6 = { "sk_plr_cbar_light6", "0" };

cvar_t sk_plr_cbar_heavy1 = { "sk_plr_cbar_heavy1", "0" };
cvar_t sk_plr_cbar_heavy2 = { "sk_plr_cbar_heavy2", "0" };
cvar_t sk_plr_cbar_heavy3 = { "sk_plr_cbar_heavy3", "0" };
cvar_t sk_plr_cbar_heavy4 = { "sk_plr_cbar_heavy4", "0" };
cvar_t sk_plr_cbar_heavy5 = { "sk_plr_cbar_heavy5", "0" };
cvar_t sk_plr_cbar_heavy6 = { "sk_plr_cbar_heavy6", "0" };

cvar_t sk_plr_cbar_thrown1 = { "sk_plr_cbar_thrown1", "0" };
cvar_t sk_plr_cbar_thrown2 = { "sk_plr_cbar_thrown2", "0" };
cvar_t sk_plr_cbar_thrown3 = { "sk_plr_cbar_thrown3", "0" };
cvar_t sk_plr_cbar_thrown4 = { "sk_plr_cbar_thrown4", "0" };
cvar_t sk_plr_cbar_thrown5 = { "sk_plr_cbar_thrown5", "0" };
cvar_t sk_plr_cbar_thrown6 = { "sk_plr_cbar_thrown6", "0" };

cvar_t sk_plr_cbar_counter1 = { "sk_plr_cbar_counter1", "0" };
cvar_t sk_plr_cbar_counter2 = { "sk_plr_cbar_counter2", "0" };
cvar_t sk_plr_cbar_counter3 = { "sk_plr_cbar_counter3", "0" };
cvar_t sk_plr_cbar_counter4 = { "sk_plr_cbar_counter4", "0" };
cvar_t sk_plr_cbar_counter5 = { "sk_plr_cbar_counter5", "0" };
cvar_t sk_plr_cbar_counter6 = { "sk_plr_cbar_counter6", "0" };

// Pipewrench
cvar_t sk_plr_pwrench_light1 = { "sk_plr_pwrench_light1", "0" };
cvar_t sk_plr_pwrench_light2 = { "sk_plr_pwrench_light2", "0" };
cvar_t sk_plr_pwrench_light3 = { "sk_plr_pwrench_light3", "0" };
cvar_t sk_plr_pwrench_light4 = { "sk_plr_pwrench_light4", "0" };
cvar_t sk_plr_pwrench_light5 = { "sk_plr_pwrench_light5", "0" };
cvar_t sk_plr_pwrench_light6 = { "sk_plr_pwrench_light6", "0" };

cvar_t sk_plr_pwrench_heavy1 = { "sk_plr_pwrench_heavy1", "0" };
cvar_t sk_plr_pwrench_heavy2 = { "sk_plr_pwrench_heavy2", "0" };
cvar_t sk_plr_pwrench_heavy3 = { "sk_plr_pwrench_heavy3", "0" };
cvar_t sk_plr_pwrench_heavy4 = { "sk_plr_pwrench_heavy4", "0" };
cvar_t sk_plr_pwrench_heavy5 = { "sk_plr_pwrench_heavy5", "0" };
cvar_t sk_plr_pwrench_heavy6 = { "sk_plr_pwrench_heavy6", "0" };

cvar_t sk_plr_pwrench_thrown1 = { "sk_plr_pwrench_thrown1", "0" };
cvar_t sk_plr_pwrench_thrown2 = { "sk_plr_pwrench_thrown2", "0" };
cvar_t sk_plr_pwrench_thrown3 = { "sk_plr_pwrench_thrown3", "0" };
cvar_t sk_plr_pwrench_thrown4 = { "sk_plr_pwrench_thrown4", "0" };
cvar_t sk_plr_pwrench_thrown5 = { "sk_plr_pwrench_thrown5", "0" };
cvar_t sk_plr_pwrench_thrown6 = { "sk_plr_pwrench_thrown6", "0" };

cvar_t sk_plr_pwrench_counter1 = { "sk_plr_pwrench_counter1", "0" };
cvar_t sk_plr_pwrench_counter2 = { "sk_plr_pwrench_counter2", "0" };
cvar_t sk_plr_pwrench_counter3 = { "sk_plr_pwrench_counter3", "0" };
cvar_t sk_plr_pwrench_counter4 = { "sk_plr_pwrench_counter4", "0" };
cvar_t sk_plr_pwrench_counter5 = { "sk_plr_pwrench_counter5", "0" };
cvar_t sk_plr_pwrench_counter6 = { "sk_plr_pwrench_counter6", "0" };

// === 2 - PISTOLS === //

// 9mm Round (Glock-17)
cvar_t sk_plr_9mm1 = { "sk_plr_9mm1", "0" };
cvar_t sk_plr_9mm2 = { "sk_plr_9mm2", "0" };
cvar_t sk_plr_9mm3 = { "sk_plr_9mm3", "0" };
cvar_t sk_plr_9mm4 = { "sk_plr_9mm4", "0" };
cvar_t sk_plr_9mm5 = { "sk_plr_9mm5", "0" };
cvar_t sk_plr_9mm6 = { "sk_plr_9mm6", "0" };

// 38 SW (M9 Beretta)
cvar_t sk_plr_38sw1 = { "sk_plr_38sw1", "0" };
cvar_t sk_plr_38sw2 = { "sk_plr_38sw2", "0" };
cvar_t sk_plr_38sw3 = { "sk_plr_38sw3", "0" };
cvar_t sk_plr_38sw4 = { "sk_plr_38sw4", "0" };
cvar_t sk_plr_38sw5 = { "sk_plr_38sw5", "0" };
cvar_t sk_plr_38sw6 = { "sk_plr_38sw6", "0" };

// .357 Magnum Round
cvar_t sk_plr_357mag1 = { "sk_plr_357mag1", "0" };
cvar_t sk_plr_357mag2 = { "sk_plr_357mag2", "0" };
cvar_t sk_plr_357mag3 = { "sk_plr_357mag3", "0" };
cvar_t sk_plr_357mag4 = { "sk_plr_357mag4", "0" };
cvar_t sk_plr_357mag5 = { "sk_plr_357mag5", "0" };
cvar_t sk_plr_357mag6 = { "sk_plr_357mag6", "0" };

// .44 SW Round (Desert Eagle)
cvar_t sk_plr_44sw1 = { "sk_plr_44sw1", "0" };
cvar_t sk_plr_44sw2 = { "sk_plr_44sw2", "0" };
cvar_t sk_plr_44sw3 = { "sk_plr_44sw3", "0" };
cvar_t sk_plr_44sw4 = { "sk_plr_44sw4", "0" };
cvar_t sk_plr_44sw5 = { "sk_plr_44sw5", "0" };
cvar_t sk_plr_44sw6 = { "sk_plr_44sw6", "0" };

// === 3 - SHOTGUNS & MACHINE-GUNS === //

// 12 Gauge (Autoshotgun)
cvar_t sk_plr_12gauge1 = { "sk_plr_12gauge1", "0" };
cvar_t sk_plr_12gauge2 = { "sk_plr_12gauge2", "0" };
cvar_t sk_plr_12gauge3 = { "sk_plr_12gauge3", "0" };
cvar_t sk_plr_12gauge4 = { "sk_plr_12gauge4", "0" };
cvar_t sk_plr_12gauge5 = { "sk_plr_12gauge5", "0" };
cvar_t sk_plr_12gauge6 = { "sk_plr_12gauge6", "0" };

// Trench Gun
cvar_t sk_plr_expgauge1 = { "sk_plr_expgauge1", "0" };
cvar_t sk_plr_expgauge2 = { "sk_plr_expgauge2", "0" };
cvar_t sk_plr_expgauge3 = { "sk_plr_expgauge3", "0" };
cvar_t sk_plr_expgauge4 = { "sk_plr_expgauge4", "0" };
cvar_t sk_plr_expgauge5 = { "sk_plr_expgauge5", "0" };
cvar_t sk_plr_expgauge6 = { "sk_plr_expgauge6", "0" };

cvar_t sk_plr_flamegauge1 = { "sk_plr_flamegauge1", "0" };
cvar_t sk_plr_flamegauge2 = { "sk_plr_flamegauge2", "0" };
cvar_t sk_plr_flamegauge3 = { "sk_plr_flamegauge3", "0" };
cvar_t sk_plr_flamegauge4 = { "sk_plr_flamegauge4", "0" };
cvar_t sk_plr_flamegauge5 = { "sk_plr_flamegauge5", "0" };
cvar_t sk_plr_flamegauge6 = { "sk_plr_flamegauge6", "0" };

// 25 Gauge (Super Shotgun)
cvar_t sk_plr_25gauge1 = { "sk_plr_25gauge1", "0" };
cvar_t sk_plr_25gauge2 = { "sk_plr_25gauge2", "0" };
cvar_t sk_plr_25gauge3 = { "sk_plr_25gauge3", "0" };
cvar_t sk_plr_25gauge4 = { "sk_plr_25gauge4", "0" };
cvar_t sk_plr_25gauge5 = { "sk_plr_25gauge5", "0" };
cvar_t sk_plr_25gauge6 = { "sk_plr_25gauge6", "0" };

// MP5
cvar_t sk_plr_9mmh1 = { "sk_plr_9mmh1", "0" };
cvar_t sk_plr_9mmh2 = { "sk_plr_9mmh2", "0" };
cvar_t sk_plr_9mmh3 = { "sk_plr_9mmh3", "0" };
cvar_t sk_plr_9mmh4 = { "sk_plr_9mmh4", "0" };
cvar_t sk_plr_9mmh5 = { "sk_plr_9mmh5", "0" };
cvar_t sk_plr_9mmh6 = { "sk_plr_9mmh6", "0" };

cvar_t sk_plr_40mm_blast1 = { "sk_plr_40mm_blast1", "0" };
cvar_t sk_plr_40mm_blast2 = { "sk_plr_40mm_blast2", "0" };
cvar_t sk_plr_40mm_blast3 = { "sk_plr_40mm_blast3", "0" };
cvar_t sk_plr_40mm_blast4 = { "sk_plr_40mm_blast4", "0" };
cvar_t sk_plr_40mm_blast5 = { "sk_plr_40mm_blast5", "0" };
cvar_t sk_plr_40mm_blast6 = { "sk_plr_40mm_blast6", "0" };

cvar_t sk_plr_40mm_heat1 = { "sk_plr_40mm_heat1", "0" };
cvar_t sk_plr_40mm_heat2 = { "sk_plr_40mm_heat2", "0" };
cvar_t sk_plr_40mm_heat3 = { "sk_plr_40mm_heat3", "0" };
cvar_t sk_plr_40mm_heat4 = { "sk_plr_40mm_heat4", "0" };
cvar_t sk_plr_40mm_heat5 = { "sk_plr_40mm_heat5", "0" };
cvar_t sk_plr_40mm_heat6 = { "sk_plr_40mm_heat6", "0" };

cvar_t sk_plr_40mm_shrap1 = { "sk_plr_40mm_shrap1", "0" };
cvar_t sk_plr_40mm_shrap2 = { "sk_plr_40mm_shrap2", "0" };
cvar_t sk_plr_40mm_shrap3 = { "sk_plr_40mm_shrap3", "0" };
cvar_t sk_plr_40mm_shrap4 = { "sk_plr_40mm_shrap4", "0" };
cvar_t sk_plr_40mm_shrap5 = { "sk_plr_40mm_shrap5", "0" };
cvar_t sk_plr_40mm_shrap6 = { "sk_plr_40mm_shrap6", "0" };

cvar_t sk_plr_40mm_smack1 = { "sk_plr_40mm_smack1", "0" };
cvar_t sk_plr_40mm_smack2 = { "sk_plr_40mm_smack2", "0" };
cvar_t sk_plr_40mm_smack3 = { "sk_plr_40mm_smack3", "0" };
cvar_t sk_plr_40mm_smack4 = { "sk_plr_40mm_smack4", "0" };
cvar_t sk_plr_40mm_smack5 = { "sk_plr_40mm_smack5", "0" };
cvar_t sk_plr_40mm_smack6 = { "sk_plr_40mm_smack6", "0" };

// M4
cvar_t sk_plr_556nato1 = { "sk_plr_556nato1", "0" };
cvar_t sk_plr_556nato2 = { "sk_plr_556nato2", "0" };
cvar_t sk_plr_556nato3 = { "sk_plr_556nato3", "0" };
cvar_t sk_plr_556nato4 = { "sk_plr_556nato4", "0" };
cvar_t sk_plr_556nato5 = { "sk_plr_556nato5", "0" };
cvar_t sk_plr_556nato6 = { "sk_plr_556nato6", "0" };

cvar_t sk_plr_smokegrenade_blast1 = { "sk_plr_smokegrenade_blast1", "0" };
cvar_t sk_plr_smokegrenade_blast2 = { "sk_plr_smokegrenade_blast2", "0" };
cvar_t sk_plr_smokegrenade_blast3 = { "sk_plr_smokegrenade_blast3", "0" };
cvar_t sk_plr_smokegrenade_blast4 = { "sk_plr_smokegrenade_blast4", "0" };
cvar_t sk_plr_smokegrenade_blast5 = { "sk_plr_smokegrenade_blast5", "0" };
cvar_t sk_plr_smokegrenade_blast6 = { "sk_plr_smokegrenade_blast6", "0" };

cvar_t sk_plr_smokegrenade_heat1 = { "sk_plr_smokegrenade_heat1", "0" };
cvar_t sk_plr_smokegrenade_heat2 = { "sk_plr_smokegrenade_heat2", "0" };
cvar_t sk_plr_smokegrenade_heat3 = { "sk_plr_smokegrenade_heat3", "0" };
cvar_t sk_plr_smokegrenade_heat4 = { "sk_plr_smokegrenade_heat4", "0" };
cvar_t sk_plr_smokegrenade_heat5 = { "sk_plr_smokegrenade_heat5", "0" };
cvar_t sk_plr_smokegrenade_heat6 = { "sk_plr_smokegrenade_heat6", "0" };

cvar_t sk_plr_smokegrenade_shrap1 = { "sk_plr_smokegrenade_shrap1", "0" };
cvar_t sk_plr_smokegrenade_shrap2 = { "sk_plr_smokegrenade_shrap2", "0" };
cvar_t sk_plr_smokegrenade_shrap3 = { "sk_plr_smokegrenade_shrap3", "0" };
cvar_t sk_plr_smokegrenade_shrap4 = { "sk_plr_smokegrenade_shrap4", "0" };
cvar_t sk_plr_smokegrenade_shrap5 = { "sk_plr_smokegrenade_shrap5", "0" };
cvar_t sk_plr_smokegrenade_shrap6 = { "sk_plr_smokegrenade_shrap6", "0" };

cvar_t sk_plr_smokegrenade_smack1 = { "sk_plr_smokegrenade_smack1", "0" };
cvar_t sk_plr_smokegrenade_smack2 = { "sk_plr_smokegrenade_smack2", "0" };
cvar_t sk_plr_smokegrenade_smack3 = { "sk_plr_smokegrenade_smack3", "0" };
cvar_t sk_plr_smokegrenade_smack4 = { "sk_plr_smokegrenade_smack4", "0" };
cvar_t sk_plr_smokegrenade_smack5 = { "sk_plr_smokegrenade_smack5", "0" };
cvar_t sk_plr_smokegrenade_smack6 = { "sk_plr_smokegrenade_smack6", "0" };

// 7.62R (AK-47)
cvar_t sk_plr_762r1 = { "sk_plr_762r1", "0" };
cvar_t sk_plr_762r2 = { "sk_plr_762r2", "0" };
cvar_t sk_plr_762r3 = { "sk_plr_762r3", "0" };
cvar_t sk_plr_762r4 = { "sk_plr_762r4", "0" };
cvar_t sk_plr_762r5 = { "sk_plr_762r5", "0" };
cvar_t sk_plr_762r6 = { "sk_plr_762r6", "0" };

cvar_t sk_plr_her_blast1 = { "sk_plr_her_blast1", "0" };
cvar_t sk_plr_her_blast2 = { "sk_plr_her_blast2", "0" };
cvar_t sk_plr_her_blast3 = { "sk_plr_her_blast3", "0" };
cvar_t sk_plr_her_blast4 = { "sk_plr_her_blast4", "0" };
cvar_t sk_plr_her_blast5 = { "sk_plr_her_blast5", "0" };
cvar_t sk_plr_her_blast6 = { "sk_plr_her_blast6", "0" };

cvar_t sk_plr_her_heat1 = { "sk_plr_her_heat1", "0" };
cvar_t sk_plr_her_heat2 = { "sk_plr_her_heat2", "0" };
cvar_t sk_plr_her_heat3 = { "sk_plr_her_heat3", "0" };
cvar_t sk_plr_her_heat4 = { "sk_plr_her_heat4", "0" };
cvar_t sk_plr_her_heat5 = { "sk_plr_her_heat5", "0" };
cvar_t sk_plr_her_heat6 = { "sk_plr_her_heat6", "0" };

cvar_t sk_plr_her_shrap1 = { "sk_plr_her_shrap1", "0" };
cvar_t sk_plr_her_shrap2 = { "sk_plr_her_shrap2", "0" };
cvar_t sk_plr_her_shrap3 = { "sk_plr_her_shrap3", "0" };
cvar_t sk_plr_her_shrap4 = { "sk_plr_her_shrap4", "0" };
cvar_t sk_plr_her_shrap5 = { "sk_plr_her_shrap5", "0" };
cvar_t sk_plr_her_shrap6 = { "sk_plr_her_shrap6", "0" };

// Nailgun
cvar_t sk_plr_nail1 = { "sk_plr_nail1", "0" };
cvar_t sk_plr_nail2 = { "sk_plr_nail2", "0" };
cvar_t sk_plr_nail3 = { "sk_plr_nail3", "0" };
cvar_t sk_plr_nail4 = { "sk_plr_nail4", "0" };
cvar_t sk_plr_nail5 = { "sk_plr_nail5", "0" };
cvar_t sk_plr_nail6 = { "sk_plr_nail6", "0" };

cvar_t sk_plr_heatnail1 = { "sk_plr_heatnail1", "0" };
cvar_t sk_plr_heatnail2 = { "sk_plr_heatnail2", "0" };
cvar_t sk_plr_heatnail3 = { "sk_plr_heatnail3", "0" };
cvar_t sk_plr_heatnail4 = { "sk_plr_heatnail4", "0" };
cvar_t sk_plr_heatnail5 = { "sk_plr_heatnail5", "0" };
cvar_t sk_plr_heatnail6 = { "sk_plr_heatnail6", "0" };

cvar_t sk_plr_nailbomb_blast1 = { "sk_plr_nailbomb_blast1", "0" };
cvar_t sk_plr_nailbomb_blast2 = { "sk_plr_nailbomb_blast2", "0" };
cvar_t sk_plr_nailbomb_blast3 = { "sk_plr_nailbomb_blast3", "0" };
cvar_t sk_plr_nailbomb_blast4 = { "sk_plr_nailbomb_blast4", "0" };
cvar_t sk_plr_nailbomb_blast5 = { "sk_plr_nailbomb_blast5", "0" };
cvar_t sk_plr_nailbomb_blast6 = { "sk_plr_nailbomb_blast6", "0" };

cvar_t sk_plr_nailbomb_heat1 = { "sk_plr_nailbomb_heat1", "0" };
cvar_t sk_plr_nailbomb_heat2 = { "sk_plr_nailbomb_heat2", "0" };
cvar_t sk_plr_nailbomb_heat3 = { "sk_plr_nailbomb_heat3", "0" };
cvar_t sk_plr_nailbomb_heat4 = { "sk_plr_nailbomb_heat4", "0" };
cvar_t sk_plr_nailbomb_heat5 = { "sk_plr_nailbomb_heat5", "0" };
cvar_t sk_plr_nailbomb_heat6 = { "sk_plr_nailbomb_heat6", "0" };

cvar_t sk_plr_nailbomb_shrap1 = { "sk_plr_nailbomb_shrap1", "0" };
cvar_t sk_plr_nailbomb_shrap2 = { "sk_plr_nailbomb_shrap2", "0" };
cvar_t sk_plr_nailbomb_shrap3 = { "sk_plr_nailbomb_shrap3", "0" };
cvar_t sk_plr_nailbomb_shrap4 = { "sk_plr_nailbomb_shrap4", "0" };
cvar_t sk_plr_nailbomb_shrap5 = { "sk_plr_nailbomb_shrap5", "0" };
cvar_t sk_plr_nailbomb_shrap6 = { "sk_plr_nailbomb_shrap6", "0" };

// === 4 - HEAVY WEAPONS === //

// Grenade Launcher
cvar_t sk_plr_50mmg_blast1 = { "sk_plr_50mmg_blast1", "0" };
cvar_t sk_plr_50mmg_blast2 = { "sk_plr_50mmg_blast2", "0" };
cvar_t sk_plr_50mmg_blast3 = { "sk_plr_50mmg_blast3", "0" };
cvar_t sk_plr_50mmg_blast4 = { "sk_plr_50mmg_blast4", "0" };
cvar_t sk_plr_50mmg_blast5 = { "sk_plr_50mmg_blast5", "0" };
cvar_t sk_plr_50mmg_blast6 = { "sk_plr_50mmg_blast6", "0" };

cvar_t sk_plr_50mmg_heat1 = { "sk_plr_50mmg_heat1", "0" };
cvar_t sk_plr_50mmg_heat2 = { "sk_plr_50mmg_heat2", "0" };
cvar_t sk_plr_50mmg_heat3 = { "sk_plr_50mmg_heat3", "0" };
cvar_t sk_plr_50mmg_heat4 = { "sk_plr_50mmg_heat4", "0" };
cvar_t sk_plr_50mmg_heat5 = { "sk_plr_50mmg_heat5", "0" };
cvar_t sk_plr_50mmg_heat6 = { "sk_plr_50mmg_heat6", "0" };

cvar_t sk_plr_50mmg_shrap1 = { "sk_plr_50mmg_shrap1", "0" };
cvar_t sk_plr_50mmg_shrap2 = { "sk_plr_50mmg_shrap2", "0" };
cvar_t sk_plr_50mmg_shrap3 = { "sk_plr_50mmg_shrap3", "0" };
cvar_t sk_plr_50mmg_shrap4 = { "sk_plr_50mmg_shrap4", "0" };
cvar_t sk_plr_50mmg_shrap5 = { "sk_plr_50mmg_shrap5", "0" };
cvar_t sk_plr_50mmg_shrap6 = { "sk_plr_50mmg_shrap6", "0" };

// RPG
cvar_t sk_plr_rpg_blast1 = { "sk_plr_rpg_blast1", "0" };
cvar_t sk_plr_rpg_blast2 = { "sk_plr_rpg_blast2", "0" };
cvar_t sk_plr_rpg_blast3 = { "sk_plr_rpg_blast3", "0" };
cvar_t sk_plr_rpg_blast4 = { "sk_plr_rpg_blast4", "0" };
cvar_t sk_plr_rpg_blast5 = { "sk_plr_rpg_blast5", "0" };
cvar_t sk_plr_rpg_blast6 = { "sk_plr_rpg_blast6", "0" };

cvar_t sk_plr_rpg_heat1 = { "sk_plr_rpg_heat1", "0" };
cvar_t sk_plr_rpg_heat2 = { "sk_plr_rpg_heat2", "0" };
cvar_t sk_plr_rpg_heat3 = { "sk_plr_rpg_heat3", "0" };
cvar_t sk_plr_rpg_heat4 = { "sk_plr_rpg_heat4", "0" };
cvar_t sk_plr_rpg_heat5 = { "sk_plr_rpg_heat5", "0" };
cvar_t sk_plr_rpg_heat6 = { "sk_plr_rpg_heat6", "0" };

cvar_t sk_plr_rpg_shrap1 = { "sk_plr_rpg_shrap1", "0" };
cvar_t sk_plr_rpg_shrap2 = { "sk_plr_rpg_shrap2", "0" };
cvar_t sk_plr_rpg_shrap3 = { "sk_plr_rpg_shrap3", "0" };
cvar_t sk_plr_rpg_shrap4 = { "sk_plr_rpg_shrap4", "0" };
cvar_t sk_plr_rpg_shrap5 = { "sk_plr_rpg_shrap5", "0" };
cvar_t sk_plr_rpg_shrap6 = { "sk_plr_rpg_shrap6", "0" };

// 66mm Rocket (LAW)
cvar_t sk_plr_66mm_blast1 = { "sk_plr_66mm_blast1", "0" };
cvar_t sk_plr_66mm_blast2 = { "sk_plr_66mm_blast2", "0" };
cvar_t sk_plr_66mm_blast3 = { "sk_plr_66mm_blast3", "0" };
cvar_t sk_plr_66mm_blast4 = { "sk_plr_66mm_blast4", "0" };
cvar_t sk_plr_66mm_blast5 = { "sk_plr_66mm_blast5", "0" };
cvar_t sk_plr_66mm_blast6 = { "sk_plr_66mm_blast6", "0" };

cvar_t sk_plr_66mm_heat1 = { "sk_plr_66mm_heat1", "0" };
cvar_t sk_plr_66mm_heat2 = { "sk_plr_66mm_heat2", "0" };
cvar_t sk_plr_66mm_heat3 = { "sk_plr_66mm_heat3", "0" };
cvar_t sk_plr_66mm_heat4 = { "sk_plr_66mm_heat4", "0" };
cvar_t sk_plr_66mm_heat5 = { "sk_plr_66mm_heat5", "0" };
cvar_t sk_plr_66mm_heat6 = { "sk_plr_66mm_heat6", "0" };

cvar_t sk_plr_66mm_shrap1 = { "sk_plr_66mm_shrap1", "0" };
cvar_t sk_plr_66mm_shrap2 = { "sk_plr_66mm_shrap2", "0" };
cvar_t sk_plr_66mm_shrap3 = { "sk_plr_66mm_shrap3", "0" };
cvar_t sk_plr_66mm_shrap4 = { "sk_plr_66mm_shrap4", "0" };
cvar_t sk_plr_66mm_shrap5 = { "sk_plr_66mm_shrap5", "0" };
cvar_t sk_plr_66mm_shrap6 = { "sk_plr_66mm_shrap6", "0" };

// Rocket Rifle
cvar_t sk_plr_50mmr_blast1 = { "sk_plr_50mmr_blast1", "0" };
cvar_t sk_plr_50mmr_blast2 = { "sk_plr_50mmr_blast2", "0" };
cvar_t sk_plr_50mmr_blast3 = { "sk_plr_50mmr_blast3", "0" };
cvar_t sk_plr_50mmr_blast4 = { "sk_plr_50mmr_blast4", "0" };
cvar_t sk_plr_50mmr_blast5 = { "sk_plr_50mmr_blast5", "0" };
cvar_t sk_plr_50mmr_blast6 = { "sk_plr_50mmr_blast6", "0" };

cvar_t sk_plr_50mmr_heat1 = { "sk_plr_50mmr_heat1", "0" };
cvar_t sk_plr_50mmr_heat2 = { "sk_plr_50mmr_heat2", "0" };
cvar_t sk_plr_50mmr_heat3 = { "sk_plr_50mmr_heat3", "0" };
cvar_t sk_plr_50mmr_heat4 = { "sk_plr_50mmr_heat4", "0" };
cvar_t sk_plr_50mmr_heat5 = { "sk_plr_50mmr_heat5", "0" };
cvar_t sk_plr_50mmr_heat6 = { "sk_plr_50mmr_heat6", "0" };

cvar_t sk_plr_50mmr_shrap1 = { "sk_plr_50mmr_shrap1", "0" };
cvar_t sk_plr_50mmr_shrap2 = { "sk_plr_50mmr_shrap2", "0" };
cvar_t sk_plr_50mmr_shrap3 = { "sk_plr_50mmr_shrap3", "0" };
cvar_t sk_plr_50mmr_shrap4 = { "sk_plr_50mmr_shrap4", "0" };
cvar_t sk_plr_50mmr_shrap5 = { "sk_plr_50mmr_shrap5", "0" };
cvar_t sk_plr_50mmr_shrap6 = { "sk_plr_50mmr_shrap6", "0" };

// Flamethrower
cvar_t sk_plr_flametouch1 = { "sk_plr_flametouch1", "0" };
cvar_t sk_plr_flametouch2 = { "sk_plr_flametouch2", "0" };
cvar_t sk_plr_flametouch3 = { "sk_plr_flametouch3", "0" };
cvar_t sk_plr_flametouch4 = { "sk_plr_flametouch4", "0" };
cvar_t sk_plr_flametouch5 = { "sk_plr_flametouch5", "0" };
cvar_t sk_plr_flametouch6 = { "sk_plr_flametouch6", "0" };

cvar_t sk_plr_flamerad1 = { "sk_plr_flamerad1", "0" };
cvar_t sk_plr_flamerad2 = { "sk_plr_flamerad2", "0" };
cvar_t sk_plr_flamerad3 = { "sk_plr_flamerad3", "0" };
cvar_t sk_plr_flamerad4 = { "sk_plr_flamerad4", "0" };
cvar_t sk_plr_flamerad5 = { "sk_plr_flamerad5", "0" };
cvar_t sk_plr_flamerad6 = { "sk_plr_flamerad6", "0" };

cvar_t sk_plr_nbomb_blast1 = { "sk_plr_nbomb_blast1", "0" };
cvar_t sk_plr_nbomb_blast2 = { "sk_plr_nbomb_blast2", "0" };
cvar_t sk_plr_nbomb_blast3 = { "sk_plr_nbomb_blast3", "0" };
cvar_t sk_plr_nbomb_blast4 = { "sk_plr_nbomb_blast4", "0" };
cvar_t sk_plr_nbomb_blast5 = { "sk_plr_nbomb_blast5", "0" };
cvar_t sk_plr_nbomb_blast6 = { "sk_plr_nbomb_blast6", "0" };

cvar_t sk_plr_nbomb_heat1 = { "sk_plr_nbomb_heat1", "0" };
cvar_t sk_plr_nbomb_heat2 = { "sk_plr_nbomb_heat2", "0" };
cvar_t sk_plr_nbomb_heat3 = { "sk_plr_nbomb_heat3", "0" };
cvar_t sk_plr_nbomb_heat4 = { "sk_plr_nbomb_heat4", "0" };
cvar_t sk_plr_nbomb_heat5 = { "sk_plr_nbomb_heat5", "0" };
cvar_t sk_plr_nbomb_heat6 = { "sk_plr_nbomb_heat6", "0" };

cvar_t sk_plr_nbomb_shrap1 = { "sk_plr_nbomb_shrap1", "0" };
cvar_t sk_plr_nbomb_shrap2 = { "sk_plr_nbomb_shrap2", "0" };
cvar_t sk_plr_nbomb_shrap3 = { "sk_plr_nbomb_shrap3", "0" };
cvar_t sk_plr_nbomb_shrap4 = { "sk_plr_nbomb_shrap4", "0" };
cvar_t sk_plr_nbomb_shrap5 = { "sk_plr_nbomb_shrap5", "0" };
cvar_t sk_plr_nbomb_shrap6 = { "sk_plr_nbomb_shrap6", "0" };

// Heavy 5.56 Round (M249)
cvar_t sk_plr_556natoh1 = { "sk_plr_556natoh1", "0" };
cvar_t sk_plr_556natoh2 = { "sk_plr_556natoh2", "0" };
cvar_t sk_plr_556natoh3 = { "sk_plr_556natoh3", "0" };
cvar_t sk_plr_556natoh4 = { "sk_plr_556natoh4", "0" };
cvar_t sk_plr_556natoh5 = { "sk_plr_556natoh5", "0" };
cvar_t sk_plr_556natoh6 = { "sk_plr_556natoh6", "0" };

// Heavy 7.62 Round (M60)
cvar_t sk_plr_762natoh1 = { "sk_plr_762natoh1", "0" };
cvar_t sk_plr_762natoh2 = { "sk_plr_762natoh2", "0" };
cvar_t sk_plr_762natoh3 = { "sk_plr_762natoh3", "0" };
cvar_t sk_plr_762natoh4 = { "sk_plr_762natoh4", "0" };
cvar_t sk_plr_762natoh5 = { "sk_plr_762natoh5", "0" };
cvar_t sk_plr_762natoh6 = { "sk_plr_762natoh6", "0" };

// 10mm Round (Chaingun)
cvar_t sk_plr_10mm1 = { "sk_plr_10mm1", "0" };
cvar_t sk_plr_10mm2 = { "sk_plr_10mm2", "0" };
cvar_t sk_plr_10mm3 = { "sk_plr_10mm3", "0" };
cvar_t sk_plr_10mm4 = { "sk_plr_10mm4", "0" };
cvar_t sk_plr_10mm5 = { "sk_plr_10mm5", "0" };
cvar_t sk_plr_10mm6 = { "sk_plr_10mm6", "0" };

// 12.7mm Round (Minigun)
cvar_t sk_plr_127mm1 = { "sk_plr_127mm1", "0" };
cvar_t sk_plr_127mm2 = { "sk_plr_127mm2", "0" };
cvar_t sk_plr_127mm3 = { "sk_plr_127mm3", "0" };
cvar_t sk_plr_127mm4 = { "sk_plr_127mm4", "0" };
cvar_t sk_plr_127mm5 = { "sk_plr_127mm5", "0" };
cvar_t sk_plr_127mm6 = { "sk_plr_127mm6", "0" };

// === 5 - RANGED WEAPONS === //

// Autocrossbow
cvar_t sk_plr_bolt1 = { "sk_plr_bolt1", "0" };
cvar_t sk_plr_bolt2 = { "sk_plr_bolt2", "0" };
cvar_t sk_plr_bolt3 = { "sk_plr_bolt3", "0" };
cvar_t sk_plr_bolt4 = { "sk_plr_bolt4", "0" };
cvar_t sk_plr_bolt5 = { "sk_plr_bolt5", "0" };
cvar_t sk_plr_bolt6 = { "sk_plr_bolt6", "0" };

cvar_t sk_plr_bolt_toxin1 = { "sk_plr_bolt_toxin1", "0" };
cvar_t sk_plr_bolt_toxin2 = { "sk_plr_bolt_toxin2", "0" };
cvar_t sk_plr_bolt_toxin3 = { "sk_plr_bolt_toxin3", "0" };
cvar_t sk_plr_bolt_toxin4 = { "sk_plr_bolt_toxin4", "0" };
cvar_t sk_plr_bolt_toxin5 = { "sk_plr_bolt_toxin5", "0" };
cvar_t sk_plr_bolt_toxin6 = { "sk_plr_bolt_toxin6", "0" };

// Torque Crossbow
cvar_t sk_plr_tbolt1 = { "sk_plr_tbolt1", "0" };
cvar_t sk_plr_tbolt2 = { "sk_plr_tbolt2", "0" };
cvar_t sk_plr_tbolt3 = { "sk_plr_tbolt3", "0" };
cvar_t sk_plr_tbolt4 = { "sk_plr_tbolt4", "0" };
cvar_t sk_plr_tbolt5 = { "sk_plr_tbolt5", "0" };
cvar_t sk_plr_tbolt6 = { "sk_plr_tbolt6", "0" };

cvar_t sk_plr_tbolt_blast1 = { "sk_plr_tbolt_blast1", "0" };
cvar_t sk_plr_tbolt_blast2 = { "sk_plr_tbolt_blast2", "0" };
cvar_t sk_plr_tbolt_blast3 = { "sk_plr_tbolt_blast3", "0" };
cvar_t sk_plr_tbolt_blast4 = { "sk_plr_tbolt_blast4", "0" };
cvar_t sk_plr_tbolt_blast5 = { "sk_plr_tbolt_blast5", "0" };
cvar_t sk_plr_tbolt_blast6 = { "sk_plr_tbolt_blast6", "0" };

cvar_t sk_plr_tbolt_heat1 = { "sk_plr_tbolt_heat1", "0" };
cvar_t sk_plr_tbolt_heat2 = { "sk_plr_tbolt_heat2", "0" };
cvar_t sk_plr_tbolt_heat3 = { "sk_plr_tbolt_heat3", "0" };
cvar_t sk_plr_tbolt_heat4 = { "sk_plr_tbolt_heat4", "0" };
cvar_t sk_plr_tbolt_heat5 = { "sk_plr_tbolt_heat5", "0" };
cvar_t sk_plr_tbolt_heat6 = { "sk_plr_tbolt_heat6", "0" };

cvar_t sk_plr_tbolt_shrap1 = { "sk_plr_tbolt_shrap1", "0" };
cvar_t sk_plr_tbolt_shrap2 = { "sk_plr_tbolt_shrap2", "0" };
cvar_t sk_plr_tbolt_shrap3 = { "sk_plr_tbolt_shrap3", "0" };
cvar_t sk_plr_tbolt_shrap4 = { "sk_plr_tbolt_shrap4", "0" };
cvar_t sk_plr_tbolt_shrap5 = { "sk_plr_tbolt_shrap5", "0" };
cvar_t sk_plr_tbolt_shrap6 = { "sk_plr_tbolt_shrap6", "0" };

// 7.62 NATO (M40A1 Sniper Rifle)
cvar_t sk_plr_762nato1 = { "sk_plr_762nato1", "0" };
cvar_t sk_plr_762nato2 = { "sk_plr_762nato2", "0" };
cvar_t sk_plr_762nato3 = { "sk_plr_762nato3", "0" };
cvar_t sk_plr_762nato4 = { "sk_plr_762nato4", "0" };
cvar_t sk_plr_762nato5 = { "sk_plr_762nato5", "0" };
cvar_t sk_plr_762nato6 = { "sk_plr_762nato6", "0" };

// Autosniper
cvar_t sk_plr_3081 = { "sk_plr_3081", "0" };
cvar_t sk_plr_3082 = { "sk_plr_3082", "0" };
cvar_t sk_plr_3083 = { "sk_plr_3083", "0" };
cvar_t sk_plr_3084 = { "sk_plr_3084", "0" };
cvar_t sk_plr_3085 = { "sk_plr_3085", "0" };
cvar_t sk_plr_3086 = { "sk_plr_3086", "0" };

cvar_t sk_plr_3381 = { "sk_plr_3381", "0" };
cvar_t sk_plr_3382 = { "sk_plr_3382", "0" };
cvar_t sk_plr_3383 = { "sk_plr_3383", "0" };
cvar_t sk_plr_3384 = { "sk_plr_3384", "0" };
cvar_t sk_plr_3385 = { "sk_plr_3385", "0" };
cvar_t sk_plr_3386 = { "sk_plr_3386", "0" };

// === 6 - ENERGY WEAPONS === //

// Railgun
cvar_t sk_plr_railbolt1 = { "sk_plr_railbolt1", "0" };
cvar_t sk_plr_railbolt2 = { "sk_plr_railbolt2", "0" };
cvar_t sk_plr_railbolt3 = { "sk_plr_railbolt3", "0" };
cvar_t sk_plr_railbolt4 = { "sk_plr_railbolt4", "0" };
cvar_t sk_plr_railbolt5 = { "sk_plr_railbolt5", "0" };
cvar_t sk_plr_railbolt6 = { "sk_plr_railbolt6", "0" };

cvar_t sk_plr_railbolt_radius1 = { "sk_plr_railbolt_radius1", "0" };
cvar_t sk_plr_railbolt_radius2 = { "sk_plr_railbolt_radius2", "0" };
cvar_t sk_plr_railbolt_radius3 = { "sk_plr_railbolt_radius3", "0" };
cvar_t sk_plr_railbolt_radius4 = { "sk_plr_railbolt_radius4", "0" };
cvar_t sk_plr_railbolt_radius5 = { "sk_plr_railbolt_radius5", "0" };
cvar_t sk_plr_railbolt_radius6 = { "sk_plr_railbolt_radius6", "0" };

// Plasma Gun
cvar_t sk_plr_plasma1 = { "sk_plr_plasma1", "0" };
cvar_t sk_plr_plasma2 = { "sk_plr_plasma2", "0" };
cvar_t sk_plr_plasma3 = { "sk_plr_plasma3", "0" };
cvar_t sk_plr_plasma4 = { "sk_plr_plasma4", "0" };
cvar_t sk_plr_plasma5 = { "sk_plr_plasma5", "0" };
cvar_t sk_plr_plasma6 = { "sk_plr_plasma6", "0" };

cvar_t sk_plr_plasma_spray1 = { "sk_plr_plasma_spray1", "0" };
cvar_t sk_plr_plasma_spray2 = { "sk_plr_plasma_spray2", "0" };
cvar_t sk_plr_plasma_spray3 = { "sk_plr_plasma_spray3", "0" };
cvar_t sk_plr_plasma_spray4 = { "sk_plr_plasma_spray4", "0" };
cvar_t sk_plr_plasma_spray5 = { "sk_plr_plasma_spray5", "0" };
cvar_t sk_plr_plasma_spray6 = { "sk_plr_plasma_spray6", "0" };

cvar_t sk_plr_plasma_blast1 = { "sk_plr_plasma_blast1", "0" };
cvar_t sk_plr_plasma_blast2 = { "sk_plr_plasma_blast2", "0" };
cvar_t sk_plr_plasma_blast3 = { "sk_plr_plasma_blast3", "0" };
cvar_t sk_plr_plasma_blast4 = { "sk_plr_plasma_blast4", "0" };
cvar_t sk_plr_plasma_blast5 = { "sk_plr_plasma_blast5", "0" };
cvar_t sk_plr_plasma_blast6 = { "sk_plr_plasma_blast6", "0" };

// Gauss Gun
cvar_t sk_plr_gauss_laser1 = { "sk_plr_gauss_laser1", "0" };
cvar_t sk_plr_gauss_laser2 = { "sk_plr_gauss_laser2", "0" };
cvar_t sk_plr_gauss_laser3 = { "sk_plr_gauss_laser3", "0" };
cvar_t sk_plr_gauss_laser4 = { "sk_plr_gauss_laser4", "0" };
cvar_t sk_plr_gauss_laser5 = { "sk_plr_gauss_laser5", "0" };
cvar_t sk_plr_gauss_laser6 = { "sk_plr_gauss_laser6", "0" };

cvar_t sk_plr_gauss_rail1 = { "sk_plr_gauss_rail1", "0" };
cvar_t sk_plr_gauss_rail2 = { "sk_plr_gauss_rail2", "0" };
cvar_t sk_plr_gauss_rail3 = { "sk_plr_gauss_rail3", "0" };
cvar_t sk_plr_gauss_rail4 = { "sk_plr_gauss_rail4", "0" };
cvar_t sk_plr_gauss_rail5 = { "sk_plr_gauss_rail5", "0" };
cvar_t sk_plr_gauss_rail6 = { "sk_plr_gauss_rail6", "0" };

// Egon Gun
cvar_t sk_plr_egon_narrow1 = { "sk_plr_egon_narrow1", "0" };
cvar_t sk_plr_egon_narrow2 = { "sk_plr_egon_narrow2", "0" };
cvar_t sk_plr_egon_narrow3 = { "sk_plr_egon_narrow3", "0" };
cvar_t sk_plr_egon_narrow4 = { "sk_plr_egon_narrow4", "0" };
cvar_t sk_plr_egon_narrow5 = { "sk_plr_egon_narrow5", "0" };
cvar_t sk_plr_egon_narrow6 = { "sk_plr_egon_narrow6", "0" };

cvar_t sk_plr_egon_wide1 = { "sk_plr_egon_wide1", "0" };
cvar_t sk_plr_egon_wide2 = { "sk_plr_egon_wide2", "0" };
cvar_t sk_plr_egon_wide3 = { "sk_plr_egon_wide3", "0" };
cvar_t sk_plr_egon_wide4 = { "sk_plr_egon_wide4", "0" };
cvar_t sk_plr_egon_wide5 = { "sk_plr_egon_wide5", "0" };
cvar_t sk_plr_egon_wide6 = { "sk_plr_egon_wide6", "0" };

cvar_t sk_plr_egon_wide_rad1 = { "sk_plr_egon_wide_rad1", "0" };
cvar_t sk_plr_egon_wide_rad2 = { "sk_plr_egon_wide_rad2", "0" };
cvar_t sk_plr_egon_wide_rad3 = { "sk_plr_egon_wide_rad3", "0" };
cvar_t sk_plr_egon_wide_rad4 = { "sk_plr_egon_wide_rad4", "0" };
cvar_t sk_plr_egon_wide_rad5 = { "sk_plr_egon_wide_rad5", "0" };
cvar_t sk_plr_egon_wide_rad6 = { "sk_plr_egon_wide_rad6", "0" };

cvar_t sk_plr_egon_blast1 = { "sk_plr_egon_blast1", "0" };
cvar_t sk_plr_egon_blast2 = { "sk_plr_egon_blast2", "0" };
cvar_t sk_plr_egon_blast3 = { "sk_plr_egon_blast3", "0" };
cvar_t sk_plr_egon_blast4 = { "sk_plr_egon_blast4", "0" };
cvar_t sk_plr_egon_blast5 = { "sk_plr_egon_blast5", "0" };
cvar_t sk_plr_egon_blast6 = { "sk_plr_egon_blast6", "0" };

// Displacer Gun/Cannon
cvar_t sk_plr_disp_blast1 = { "sk_plr_disp_blast1", "0" };
cvar_t sk_plr_disp_blast2 = { "sk_plr_disp_blast2", "0" };
cvar_t sk_plr_disp_blast3 = { "sk_plr_disp_blast3", "0" };
cvar_t sk_plr_disp_blast4 = { "sk_plr_disp_blast4", "0" };
cvar_t sk_plr_disp_blast5 = { "sk_plr_disp_blast5", "0" };
cvar_t sk_plr_disp_blast6 = { "sk_plr_disp_blast6", "0" };

cvar_t sk_plr_disp_arc1 = { "sk_plr_disp_arc1", "0" };
cvar_t sk_plr_disp_arc2 = { "sk_plr_disp_arc2", "0" };
cvar_t sk_plr_disp_arc3 = { "sk_plr_disp_arc3", "0" };
cvar_t sk_plr_disp_arc4 = { "sk_plr_disp_arc4", "0" };
cvar_t sk_plr_disp_arc5 = { "sk_plr_disp_arc5", "0" };
cvar_t sk_plr_disp_arc6 = { "sk_plr_disp_arc6", "0" };

cvar_t sk_plr_disp_dir1 = { "sk_plr_disp_dir1", "0" };
cvar_t sk_plr_disp_dir2 = { "sk_plr_disp_dir2", "0" };
cvar_t sk_plr_disp_dir3 = { "sk_plr_disp_dir3", "0" };
cvar_t sk_plr_disp_dir4 = { "sk_plr_disp_dir4", "0" };
cvar_t sk_plr_disp_dir5 = { "sk_plr_disp_dir5", "0" };
cvar_t sk_plr_disp_dir6 = { "sk_plr_disp_dir6", "0" };

// === 7 - THROWABLE AND TRAPS === //

// High-Explosive Grenade
cvar_t sk_plr_he_blast1 = { "sk_plr_he_blast1", "0" };
cvar_t sk_plr_he_blast2 = { "sk_plr_he_blast2", "0" };
cvar_t sk_plr_he_blast3 = { "sk_plr_he_blast3", "0" };
cvar_t sk_plr_he_blast4 = { "sk_plr_he_blast4", "0" };
cvar_t sk_plr_he_blast5 = { "sk_plr_he_blast5", "0" };
cvar_t sk_plr_he_blast6 = { "sk_plr_he_blast6", "0" };

cvar_t sk_plr_he_heat1 = { "sk_plr_he_heat1", "0" };
cvar_t sk_plr_he_heat2 = { "sk_plr_he_heat2", "0" };
cvar_t sk_plr_he_heat3 = { "sk_plr_he_heat3", "0" };
cvar_t sk_plr_he_heat4 = { "sk_plr_he_heat4", "0" };
cvar_t sk_plr_he_heat5 = { "sk_plr_he_heat5", "0" };
cvar_t sk_plr_he_heat6 = { "sk_plr_he_heat6", "0" };

cvar_t sk_plr_he_shrap1 = { "sk_plr_he_shrap1", "0" };
cvar_t sk_plr_he_shrap2 = { "sk_plr_he_shrap2", "0" };
cvar_t sk_plr_he_shrap3 = { "sk_plr_he_shrap3", "0" };
cvar_t sk_plr_he_shrap4 = { "sk_plr_he_shrap4", "0" };
cvar_t sk_plr_he_shrap5 = { "sk_plr_he_shrap5", "0" };
cvar_t sk_plr_he_shrap6 = { "sk_plr_he_shrap6", "0" };

cvar_t sk_plr_he_smack1 = { "sk_plr_he_smack1", "0" };
cvar_t sk_plr_he_smack2 = { "sk_plr_he_smack2", "0" };
cvar_t sk_plr_he_smack3 = { "sk_plr_he_smack3", "0" };
cvar_t sk_plr_he_smack4 = { "sk_plr_he_smack4", "0" };
cvar_t sk_plr_he_smack5 = { "sk_plr_he_smack5", "0" };
cvar_t sk_plr_he_smack6 = { "sk_plr_he_smack6", "0" };

// Fragmentation Grenade
cvar_t sk_plr_frag_blast1 = { "sk_plr_frag_blast1", "0" };
cvar_t sk_plr_frag_blast2 = { "sk_plr_frag_blast2", "0" };
cvar_t sk_plr_frag_blast3 = { "sk_plr_frag_blast3", "0" };
cvar_t sk_plr_frag_blast4 = { "sk_plr_frag_blast4", "0" };
cvar_t sk_plr_frag_blast5 = { "sk_plr_frag_blast5", "0" };
cvar_t sk_plr_frag_blast6 = { "sk_plr_frag_blast6", "0" };

cvar_t sk_plr_frag_heat1 = { "sk_plr_frag_heat1", "0" };
cvar_t sk_plr_frag_heat2 = { "sk_plr_frag_heat2", "0" };
cvar_t sk_plr_frag_heat3 = { "sk_plr_frag_heat3", "0" };
cvar_t sk_plr_frag_heat4 = { "sk_plr_frag_heat4", "0" };
cvar_t sk_plr_frag_heat5 = { "sk_plr_frag_heat5", "0" };
cvar_t sk_plr_frag_heat6 = { "sk_plr_frag_heat6", "0" };

cvar_t sk_plr_frag_shrap1 = { "sk_plr_frag_shrap1", "0" };
cvar_t sk_plr_frag_shrap2 = { "sk_plr_frag_shrap2", "0" };
cvar_t sk_plr_frag_shrap3 = { "sk_plr_frag_shrap3", "0" };
cvar_t sk_plr_frag_shrap4 = { "sk_plr_frag_shrap4", "0" };
cvar_t sk_plr_frag_shrap5 = { "sk_plr_frag_shrap5", "0" };
cvar_t sk_plr_frag_shrap6 = { "sk_plr_frag_shrap6", "0" };

cvar_t sk_plr_frag_smack1 = { "sk_plr_frag_smack1", "0" };
cvar_t sk_plr_frag_smack2 = { "sk_plr_frag_smack2", "0" };
cvar_t sk_plr_frag_smack3 = { "sk_plr_frag_smack3", "0" };
cvar_t sk_plr_frag_smack4 = { "sk_plr_frag_smack4", "0" };
cvar_t sk_plr_frag_smack5 = { "sk_plr_frag_smack5", "0" };
cvar_t sk_plr_frag_smack6 = { "sk_plr_frag_smack6", "0" };

// Satchel Charge
cvar_t sk_plr_satchel_blast1 = { "sk_plr_satchel_blast1", "0" };
cvar_t sk_plr_satchel_blast2 = { "sk_plr_satchel_blast2", "0" };
cvar_t sk_plr_satchel_blast3 = { "sk_plr_satchel_blast3", "0" };
cvar_t sk_plr_satchel_blast4 = { "sk_plr_satchel_blast4", "0" };
cvar_t sk_plr_satchel_blast5 = { "sk_plr_satchel_blast5", "0" };
cvar_t sk_plr_satchel_blast6 = { "sk_plr_satchel_blast6", "0" };

cvar_t sk_plr_satchel_heat1 = { "sk_plr_satchel_heat1", "0" };
cvar_t sk_plr_satchel_heat2 = { "sk_plr_satchel_heat2", "0" };
cvar_t sk_plr_satchel_heat3 = { "sk_plr_satchel_heat3", "0" };
cvar_t sk_plr_satchel_heat4 = { "sk_plr_satchel_heat4", "0" };
cvar_t sk_plr_satchel_heat5 = { "sk_plr_satchel_heat5", "0" };
cvar_t sk_plr_satchel_heat6 = { "sk_plr_satchel_heat6", "0" };

cvar_t sk_plr_satchel_shrap1 = { "sk_plr_satchel_shrap1", "0" };
cvar_t sk_plr_satchel_shrap2 = { "sk_plr_satchel_shrap2", "0" };
cvar_t sk_plr_satchel_shrap3 = { "sk_plr_satchel_shrap3", "0" };
cvar_t sk_plr_satchel_shrap4 = { "sk_plr_satchel_shrap4", "0" };
cvar_t sk_plr_satchel_shrap5 = { "sk_plr_satchel_shrap5", "0" };
cvar_t sk_plr_satchel_shrap6 = { "sk_plr_satchel_shrap6", "0" };

// Tripmine
cvar_t sk_plr_tripmine_blast1 = { "sk_plr_tripmine_blast1", "0" };
cvar_t sk_plr_tripmine_blast2 = { "sk_plr_tripmine_blast2", "0" };
cvar_t sk_plr_tripmine_blast3 = { "sk_plr_tripmine_blast3", "0" };
cvar_t sk_plr_tripmine_blast4 = { "sk_plr_tripmine_blast4", "0" };
cvar_t sk_plr_tripmine_blast5 = { "sk_plr_tripmine_blast5", "0" };
cvar_t sk_plr_tripmine_blast6 = { "sk_plr_tripmine_blast6", "0" };

cvar_t sk_plr_tripmine_heat1 = { "sk_plr_tripmine_heat1", "0" };
cvar_t sk_plr_tripmine_heat2 = { "sk_plr_tripmine_heat2", "0" };
cvar_t sk_plr_tripmine_heat3 = { "sk_plr_tripmine_heat3", "0" };
cvar_t sk_plr_tripmine_heat4 = { "sk_plr_tripmine_heat4", "0" };
cvar_t sk_plr_tripmine_heat5 = { "sk_plr_tripmine_heat5", "0" };
cvar_t sk_plr_tripmine_heat6 = { "sk_plr_tripmine_heat6", "0" };

cvar_t sk_plr_tripmine_shrap1 = { "sk_plr_tripmine_shrap1", "0" };
cvar_t sk_plr_tripmine_shrap2 = { "sk_plr_tripmine_shrap2", "0" };
cvar_t sk_plr_tripmine_shrap3 = { "sk_plr_tripmine_shrap3", "0" };
cvar_t sk_plr_tripmine_shrap4 = { "sk_plr_tripmine_shrap4", "0" };
cvar_t sk_plr_tripmine_shrap5 = { "sk_plr_tripmine_shrap5", "0" };
cvar_t sk_plr_tripmine_shrap6 = { "sk_plr_tripmine_shrap6", "0" };

// === 8 - ALIEN WEAPONS === //

// Hivehand
cvar_t sk_plr_hornet1 = { "sk_plr_hornet1", "0" };
cvar_t sk_plr_hornet2 = { "sk_plr_hornet2", "0" };
cvar_t sk_plr_hornet3 = { "sk_plr_hornet3", "0" };
cvar_t sk_plr_hornet4 = { "sk_plr_hornet4", "0" };
cvar_t sk_plr_hornet5 = { "sk_plr_hornet5", "0" };
cvar_t sk_plr_hornet6 = { "sk_plr_hornet6", "0" };

cvar_t sk_hornet_health1 = { "sk_hornet_health1", "0" };
cvar_t sk_hornet_health2 = { "sk_hornet_health2", "0" };
cvar_t sk_hornet_health3 = { "sk_hornet_health3", "0" };
cvar_t sk_hornet_health4 = { "sk_hornet_health4", "0" };
cvar_t sk_hornet_health5 = { "sk_hornet_health5", "0" };
cvar_t sk_hornet_health6 = { "sk_hornet_health6", "0" };

cvar_t sk_plr_phero_missile1 = { "sk_plr_phero_missile1", "0" };
cvar_t sk_plr_phero_missile2 = { "sk_plr_phero_missile2", "0" };
cvar_t sk_plr_phero_missile3 = { "sk_plr_phero_missile3", "0" };
cvar_t sk_plr_phero_missile4 = { "sk_plr_phero_missile4", "0" };
cvar_t sk_plr_phero_missile5 = { "sk_plr_phero_missile5", "0" };
cvar_t sk_plr_phero_missile6 = { "sk_plr_phero_missile6", "0" };

cvar_t sk_plr_black_hole1 = { "sk_plr_black_hole1", "0" };
cvar_t sk_plr_black_hole2 = { "sk_plr_black_hole2", "0" };
cvar_t sk_plr_black_hole3 = { "sk_plr_black_hole3", "0" };
cvar_t sk_plr_black_hole4 = { "sk_plr_black_hole4", "0" };
cvar_t sk_plr_black_hole5 = { "sk_plr_black_hole5", "0" };
cvar_t sk_plr_black_hole6 = { "sk_plr_black_hole6", "0" };

cvar_t sk_plr_chainsaw1 = { "sk_plr_chainsaw1", "0" };
cvar_t sk_plr_chainsaw2 = { "sk_plr_chainsaw2", "0" };
cvar_t sk_plr_chainsaw3 = { "sk_plr_chainsaw3", "0" };
cvar_t sk_plr_chainsaw4 = { "sk_plr_chainsaw4", "0" };
cvar_t sk_plr_chainsaw5 = { "sk_plr_chainsaw5", "0" };
cvar_t sk_plr_chainsaw6 = { "sk_plr_chainsaw6", "0" };

// Snark
cvar_t sk_plr_snark_bite1 = { "sk_plr_snark_bite1", "0" };
cvar_t sk_plr_snark_bite2 = { "sk_plr_snark_bite2", "0" };
cvar_t sk_plr_snark_bite3 = { "sk_plr_snark_bite3", "0" };
cvar_t sk_plr_snark_bite4 = { "sk_plr_snark_bite4", "0" };
cvar_t sk_plr_snark_bite5 = { "sk_plr_snark_bite5", "0" };
cvar_t sk_plr_snark_bite6 = { "sk_plr_snark_bite6", "0" };

cvar_t sk_plr_snark_pop1 = { "sk_plr_snark_pop1", "0" };
cvar_t sk_plr_snark_pop2 = { "sk_plr_snark_pop2", "0" };
cvar_t sk_plr_snark_pop3 = { "sk_plr_snark_pop3", "0" };
cvar_t sk_plr_snark_pop4 = { "sk_plr_snark_pop4", "0" };
cvar_t sk_plr_snark_pop5 = { "sk_plr_snark_pop5", "0" };
cvar_t sk_plr_snark_pop6 = { "sk_plr_snark_pop6", "0" };

// Snark
cvar_t sk_snark_health1 = { "sk_snark_health1", "0" };
cvar_t sk_snark_health2 = { "sk_snark_health2", "0" };
cvar_t sk_snark_health3 = { "sk_snark_health3", "0" };
cvar_t sk_snark_health4 = { "sk_snark_health4", "0" };
cvar_t sk_snark_health5 = { "sk_snark_health5", "0" };
cvar_t sk_snark_health6 = { "sk_snark_health6", "0" };

cvar_t sk_snark_dmg_bite1 = { "sk_snark_dmg_bite1", "0" };
cvar_t sk_snark_dmg_bite2 = { "sk_snark_dmg_bite2", "0" };
cvar_t sk_snark_dmg_bite3 = { "sk_snark_dmg_bite3", "0" };
cvar_t sk_snark_dmg_bite4 = { "sk_snark_dmg_bite4", "0" };
cvar_t sk_snark_dmg_bite5 = { "sk_snark_dmg_bite5", "0" };
cvar_t sk_snark_dmg_bite6 = { "sk_snark_dmg_bite6", "0" };

cvar_t sk_snark_dmg_pop1 = { "sk_snark_dmg_pop1", "0" };
cvar_t sk_snark_dmg_pop2 = { "sk_snark_dmg_pop2", "0" };
cvar_t sk_snark_dmg_pop3 = { "sk_snark_dmg_pop3", "0" };
cvar_t sk_snark_dmg_pop4 = { "sk_snark_dmg_pop4", "0" };
cvar_t sk_snark_dmg_pop5 = { "sk_snark_dmg_pop5", "0" };
cvar_t sk_snark_dmg_pop6 = { "sk_snark_dmg_pop6", "0" };

// Spore Launcher
cvar_t sk_plr_spore_radius1 = { "sk_plr_spore_radius1", "0" };
cvar_t sk_plr_spore_radius2 = { "sk_plr_spore_radius2", "0" };
cvar_t sk_plr_spore_radius3 = { "sk_plr_spore_radius3", "0" };
cvar_t sk_plr_spore_radius4 = { "sk_plr_spore_radius4", "0" };
cvar_t sk_plr_spore_radius5 = { "sk_plr_spore_radius5", "0" };
cvar_t sk_plr_spore_radius6 = { "sk_plr_spore_radius6", "0" };

cvar_t sk_plr_spore_direct1 = { "sk_plr_spore_direct1", "0" };
cvar_t sk_plr_spore_direct2 = { "sk_plr_spore_direct2", "0" };
cvar_t sk_plr_spore_direct3 = { "sk_plr_spore_direct3", "0" };
cvar_t sk_plr_spore_direct4 = { "sk_plr_spore_direct4", "0" };
cvar_t sk_plr_spore_direct5 = { "sk_plr_spore_direct5", "0" };
cvar_t sk_plr_spore_direct6 = { "sk_plr_spore_direct6", "0" };

cvar_t sk_plr_spore_bite1 = { "sk_plr_spore_bite1", "0" };
cvar_t sk_plr_spore_bite2 = { "sk_plr_spore_bite2", "0" };
cvar_t sk_plr_spore_bite3 = { "sk_plr_spore_bite3", "0" };
cvar_t sk_plr_spore_bite4 = { "sk_plr_spore_bite4", "0" };
cvar_t sk_plr_spore_bite5 = { "sk_plr_spore_bite5", "0" };
cvar_t sk_plr_spore_bite6 = { "sk_plr_spore_bite6", "0" };

// Shock Roach
cvar_t sk_plr_shockbolt1 = { "sk_plr_shockbolt1", "0" };
cvar_t sk_plr_shockbolt2 = { "sk_plr_shockbolt2", "0" };
cvar_t sk_plr_shockbolt3 = { "sk_plr_shockbolt3", "0" };
cvar_t sk_plr_shockbolt4 = { "sk_plr_shockbolt4", "0" };
cvar_t sk_plr_shockbolt5 = { "sk_plr_shockbolt5", "0" };
cvar_t sk_plr_shockbolt6 = { "sk_plr_shockbolt6", "0" };

cvar_t sk_plr_shocktase1 = { "sk_plr_shocktase1", "0" };
cvar_t sk_plr_shocktase2 = { "sk_plr_shocktase2", "0" };
cvar_t sk_plr_shocktase3 = { "sk_plr_shocktase3", "0" };
cvar_t sk_plr_shocktase4 = { "sk_plr_shocktase4", "0" };
cvar_t sk_plr_shocktase5 = { "sk_plr_shocktase5", "0" };
cvar_t sk_plr_shocktase6 = { "sk_plr_shocktase6", "0" };

cvar_t sk_plr_shockbite1 = { "sk_plr_shockbite1", "0" };
cvar_t sk_plr_shockbite2 = { "sk_plr_shockbite2", "0" };
cvar_t sk_plr_shockbite3 = { "sk_plr_shockbite3", "0" };
cvar_t sk_plr_shockbite4 = { "sk_plr_shockbite4", "0" };
cvar_t sk_plr_shockbite5 = { "sk_plr_shockbite5", "0" };
cvar_t sk_plr_shockbite6 = { "sk_plr_shockbite6", "0" };

// Barnacle
cvar_t sk_barnacle_health1 = { "sk_barnacle_health1", "0" };
cvar_t sk_barnacle_health2 = { "sk_barnacle_health2", "0" };
cvar_t sk_barnacle_health3 = { "sk_barnacle_health3", "0" };
cvar_t sk_barnacle_health4 = { "sk_barnacle_health4", "0" };
cvar_t sk_barnacle_health5 = { "sk_barnacle_health5", "0" };
cvar_t sk_barnacle_health6 = { "sk_barnacle_health6", "0" };

cvar_t sk_plr_barnacle_bite1 = { "sk_plr_barnacle_bite1", "0" };
cvar_t sk_plr_barnacle_bite2 = { "sk_plr_barnacle_bite2", "0" };
cvar_t sk_plr_barnacle_bite3 = { "sk_plr_barnacle_bite3", "0" };
cvar_t sk_plr_barnacle_bite4 = { "sk_plr_barnacle_bite4", "0" };
cvar_t sk_plr_barnacle_bite5 = { "sk_plr_barnacle_bite5", "0" };
cvar_t sk_plr_barnacle_bite6 = { "sk_plr_barnacle_bite6", "0" };

// Chumtoad
//? ? ?

// === 9 - SUPPORT WEAPONS === //

// Automatic Medkit
cvar_t sk_plr_medkit_heal1 = { "sk_plr_medkit_heal1", "0" };
cvar_t sk_plr_medkit_heal2 = { "sk_plr_medkit_heal2", "0" };
cvar_t sk_plr_medkit_heal3 = { "sk_plr_medkit_heal3", "0" };
cvar_t sk_plr_medkit_heal4 = { "sk_plr_medkit_heal4", "0" };
cvar_t sk_plr_medkit_heal5 = { "sk_plr_medkit_heal5", "0" };
cvar_t sk_plr_medkit_heal6 = { "sk_plr_medkit_heal6", "0" };

cvar_t sk_plr_medkit_poison1 = { "sk_plr_medkit_poison1", "0" };
cvar_t sk_plr_medkit_poison2 = { "sk_plr_medkit_poison2", "0" };
cvar_t sk_plr_medkit_poison3 = { "sk_plr_medkit_poison3", "0" };
cvar_t sk_plr_medkit_poison4 = { "sk_plr_medkit_poison4", "0" };
cvar_t sk_plr_medkit_poison5 = { "sk_plr_medkit_poison5", "0" };
cvar_t sk_plr_medkit_poison6 = { "sk_plr_medkit_poison6", "0" };

// EMP Tool
//? ? ?

// Syringe
//? ? ?

// Flare
cvar_t sk_plr_flare_burn1 = { "sk_plr_flare_burn1", "0" };
cvar_t sk_plr_flare_burn2 = { "sk_plr_flare_burn2", "0" };
cvar_t sk_plr_flare_burn3 = { "sk_plr_flare_burn3", "0" };
cvar_t sk_plr_flare_burn4 = { "sk_plr_flare_burn4", "0" };
cvar_t sk_plr_flare_burn5 = { "sk_plr_flare_burn5", "0" };
cvar_t sk_plr_flare_burn6 = { "sk_plr_flare_burn6", "0" };

cvar_t sk_plr_flare_hit1 = { "sk_plr_flare_hit1", "0" };
cvar_t sk_plr_flare_hit2 = { "sk_plr_flare_hit2", "0" };
cvar_t sk_plr_flare_hit3 = { "sk_plr_flare_hit3", "0" };
cvar_t sk_plr_flare_hit4 = { "sk_plr_flare_hit4", "0" };
cvar_t sk_plr_flare_hit5 = { "sk_plr_flare_hit5", "0" };
cvar_t sk_plr_flare_hit6 = { "sk_plr_flare_hit6", "0" };

cvar_t sk_plr_flare_blast1 = { "sk_plr_flare_blast1", "0" };
cvar_t sk_plr_flare_blast2 = { "sk_plr_flare_blast2", "0" };
cvar_t sk_plr_flare_blast3 = { "sk_plr_flare_blast3", "0" };
cvar_t sk_plr_flare_blast4 = { "sk_plr_flare_blast4", "0" };
cvar_t sk_plr_flare_blast5 = { "sk_plr_flare_blast5", "0" };
cvar_t sk_plr_flare_blast6 = { "sk_plr_flare_blast6", "0" };

cvar_t sk_plr_flare_heat1 = { "sk_plr_flare_heat1", "0" };
cvar_t sk_plr_flare_heat2 = { "sk_plr_flare_heat2", "0" };
cvar_t sk_plr_flare_heat3 = { "sk_plr_flare_heat3", "0" };
cvar_t sk_plr_flare_heat4 = { "sk_plr_flare_heat4", "0" };
cvar_t sk_plr_flare_heat5 = { "sk_plr_flare_heat5", "0" };
cvar_t sk_plr_flare_heat6 = { "sk_plr_flare_heat6", "0" };

cvar_t sk_plr_flare_shrap1 = { "sk_plr_flare_shrap1", "0" };
cvar_t sk_plr_flare_shrap2 = { "sk_plr_flare_shrap2", "0" };
cvar_t sk_plr_flare_shrap3 = { "sk_plr_flare_shrap3", "0" };
cvar_t sk_plr_flare_shrap4 = { "sk_plr_flare_shrap4", "0" };
cvar_t sk_plr_flare_shrap5 = { "sk_plr_flare_shrap5", "0" };
cvar_t sk_plr_flare_shrap6 = { "sk_plr_flare_shrap6", "0" };

// HEALTH/SUIT CHARGE DISTRIBUTION
cvar_t sk_charger1 = { "sk_charger1", "0" };
cvar_t sk_charger2 = { "sk_charger2", "0" };
cvar_t sk_charger3 = { "sk_charger3", "0" };
cvar_t sk_charger4 = { "sk_charger4", "0" };
cvar_t sk_charger5 = { "sk_charger5", "0" };
cvar_t sk_charger6 = { "sk_charger6", "0" };

cvar_t sk_battery1 = { "sk_battery1", "0" };
cvar_t sk_battery2 = { "sk_battery2", "0" };
cvar_t sk_battery3 = { "sk_battery3", "0" };
cvar_t sk_battery4 = { "sk_battery4", "0" };
cvar_t sk_battery5 = { "sk_battery5", "0" };
cvar_t sk_battery6 = { "sk_battery6", "0" };

cvar_t sk_healthkit1 = { "sk_healthkit1", "0" };
cvar_t sk_healthkit2 = { "sk_healthkit2", "0" };
cvar_t sk_healthkit3 = { "sk_healthkit3", "0" };
cvar_t sk_healthkit4 = { "sk_healthkit4", "0" };
cvar_t sk_healthkit5 = { "sk_healthkit5", "0" };
cvar_t sk_healthkit6 = { "sk_healthkit6", "0" };

// damage adjusters
cvar_t sk_dmgadjust_head1 = { "sk_dmgadjust_head1", "3" };
cvar_t sk_dmgadjust_head2 = { "sk_dmgadjust_head2", "3" };
cvar_t sk_dmgadjust_head3 = { "sk_dmgadjust_head3", "3" };
cvar_t sk_dmgadjust_head4 = { "sk_dmgadjust_head4", "3" };
cvar_t sk_dmgadjust_head5 = { "sk_dmgadjust_head5", "3" };
cvar_t sk_dmgadjust_head6 = { "sk_dmgadjust_head6", "3" };

cvar_t sk_dmgadjust_chest1 = { "sk_dmgadjust_chest1", "1" };
cvar_t sk_dmgadjust_chest2 = { "sk_dmgadjust_chest2", "1" };
cvar_t sk_dmgadjust_chest3 = { "sk_dmgadjust_chest3", "1" };
cvar_t sk_dmgadjust_chest4 = { "sk_dmgadjust_chest4", "1" };
cvar_t sk_dmgadjust_chest5 = { "sk_dmgadjust_chest5", "1" };
cvar_t sk_dmgadjust_chest6 = { "sk_dmgadjust_chest6", "1" };

cvar_t sk_dmgadjust_stomach1 = { "sk_dmgadjust_stomach1", "1" };
cvar_t sk_dmgadjust_stomach2 = { "sk_dmgadjust_stomach2", "1" };
cvar_t sk_dmgadjust_stomach3 = { "sk_dmgadjust_stomach3", "1" };
cvar_t sk_dmgadjust_stomach4 = { "sk_dmgadjust_stomach4", "1" };
cvar_t sk_dmgadjust_stomach5 = { "sk_dmgadjust_stomach5", "1" };
cvar_t sk_dmgadjust_stomach6 = { "sk_dmgadjust_stomach6", "1" };

cvar_t sk_dmgadjust_arm1 = { "sk_dmgadjust_arm1", "1" };
cvar_t sk_dmgadjust_arm2 = { "sk_dmgadjust_arm2", "1" };
cvar_t sk_dmgadjust_arm3 = { "sk_dmgadjust_arm3", "1" };
cvar_t sk_dmgadjust_arm4 = { "sk_dmgadjust_arm4", "1" };
cvar_t sk_dmgadjust_arm5 = { "sk_dmgadjust_arm5", "1" };
cvar_t sk_dmgadjust_arm6 = { "sk_dmgadjust_arm6", "1" };

cvar_t sk_dmgadjust_leg1 = { "sk_dmgadjust_leg1", "1" };
cvar_t sk_dmgadjust_leg2 = { "sk_dmgadjust_leg2", "1" };
cvar_t sk_dmgadjust_leg3 = { "sk_dmgadjust_leg3", "1" };
cvar_t sk_dmgadjust_leg4 = { "sk_dmgadjust_leg4", "1" };
cvar_t sk_dmgadjust_leg5 = { "sk_dmgadjust_leg5", "1" };
cvar_t sk_dmgadjust_leg6 = { "sk_dmgadjust_leg6", "1" };

// END: CVARS FOR SKILL LEVEL SETTINGS

// Register your console variables here
// This gets called one time when the game is initialied
void GameDLLInit( void )
{
	// Register cvars here:

	g_psv_gravity = CVAR_GET_POINTER( "sv_gravity" );
	g_psv_aim = CVAR_GET_POINTER( "sv_aim" );
	g_footsteps = CVAR_GET_POINTER( "mp_footsteps" );

	CVAR_REGISTER (&displaysoundlist);

	CVAR_REGISTER (&teamplay);
	CVAR_REGISTER (&fraglimit);
	CVAR_REGISTER (&timelimit);

	CVAR_REGISTER (&fragsleft);
	CVAR_REGISTER (&timeleft);

	CVAR_REGISTER (&friendlyfire);
	CVAR_REGISTER (&falldamage);
	CVAR_REGISTER (&weaponstay);
	CVAR_REGISTER (&forcerespawn);
	CVAR_REGISTER (&flashlight);
	CVAR_REGISTER (&aimcrosshair);
	CVAR_REGISTER (&decalfrequency);
	CVAR_REGISTER (&teamlist);
	CVAR_REGISTER (&teamoverride);
	CVAR_REGISTER (&defaultteam);
	CVAR_REGISTER (&allowmonsters);

	CVAR_REGISTER (&mp_chattime);
	CVAR_REGISTER (&saved1);

	// BEGIN: REGISTER CVARS FOR SKILL LEVEL STUFF

	// =========================== //
	//           MONSTERS          //
	// =========================== //

	// Alien Grunt
	CVAR_REGISTER(&sk_agrunt_health1);
	CVAR_REGISTER(&sk_agrunt_health2);
	CVAR_REGISTER(&sk_agrunt_health3);
	CVAR_REGISTER(&sk_agrunt_health4);
	CVAR_REGISTER(&sk_agrunt_health5);
	CVAR_REGISTER(&sk_agrunt_health6);

	CVAR_REGISTER(&sk_agrunt_dmg_punch1);
	CVAR_REGISTER(&sk_agrunt_dmg_punch2);
	CVAR_REGISTER(&sk_agrunt_dmg_punch3);
	CVAR_REGISTER(&sk_agrunt_dmg_punch4);
	CVAR_REGISTER(&sk_agrunt_dmg_punch5);
	CVAR_REGISTER(&sk_agrunt_dmg_punch6);

	CVAR_REGISTER(&sk_agrunt_dmg_bite1);
	CVAR_REGISTER(&sk_agrunt_dmg_bite2);
	CVAR_REGISTER(&sk_agrunt_dmg_bite3);
	CVAR_REGISTER(&sk_agrunt_dmg_bite4);
	CVAR_REGISTER(&sk_agrunt_dmg_bite5);
	CVAR_REGISTER(&sk_agrunt_dmg_bite6);

	CVAR_REGISTER(&sk_agrunt_dmg_headbutt1);
	CVAR_REGISTER(&sk_agrunt_dmg_headbutt2);
	CVAR_REGISTER(&sk_agrunt_dmg_headbutt3);
	CVAR_REGISTER(&sk_agrunt_dmg_headbutt4);
	CVAR_REGISTER(&sk_agrunt_dmg_headbutt5);
	CVAR_REGISTER(&sk_agrunt_dmg_headbutt6);

	CVAR_REGISTER(&sk_agrunt_dmg_kick1);
	CVAR_REGISTER(&sk_agrunt_dmg_kick2);
	CVAR_REGISTER(&sk_agrunt_dmg_kick3);
	CVAR_REGISTER(&sk_agrunt_dmg_kick4);
	CVAR_REGISTER(&sk_agrunt_dmg_kick5);
	CVAR_REGISTER(&sk_agrunt_dmg_kick6);

	// Apache 
	CVAR_REGISTER(&sk_apache_health1);
	CVAR_REGISTER(&sk_apache_health2);
	CVAR_REGISTER(&sk_apache_health3);
	CVAR_REGISTER(&sk_apache_health4);
	CVAR_REGISTER(&sk_apache_health5);
	CVAR_REGISTER(&sk_apache_health6);

	CVAR_REGISTER(&sk_apache_dmg_chaingun1);
	CVAR_REGISTER(&sk_apache_dmg_chaingun2);
	CVAR_REGISTER(&sk_apache_dmg_chaingun3);
	CVAR_REGISTER(&sk_apache_dmg_chaingun4);
	CVAR_REGISTER(&sk_apache_dmg_chaingun5);
	CVAR_REGISTER(&sk_apache_dmg_chaingun6);

	CVAR_REGISTER(&sk_apache_dmg_hvr1);
	CVAR_REGISTER(&sk_apache_dmg_hvr2);
	CVAR_REGISTER(&sk_apache_dmg_hvr3);
	CVAR_REGISTER(&sk_apache_dmg_hvr4);
	CVAR_REGISTER(&sk_apache_dmg_hvr5);
	CVAR_REGISTER(&sk_apache_dmg_hvr6);

	CVAR_REGISTER(&sk_barney_health1);
	CVAR_REGISTER(&sk_barney_health2);
	CVAR_REGISTER(&sk_barney_health3);
	CVAR_REGISTER(&sk_barney_health4);
	CVAR_REGISTER(&sk_barney_health5);
	CVAR_REGISTER(&sk_barney_health6);

	CVAR_REGISTER(&sk_barney_dmg_kick1);
	CVAR_REGISTER(&sk_barney_dmg_kick2);
	CVAR_REGISTER(&sk_barney_dmg_kick3);
	CVAR_REGISTER(&sk_barney_dmg_kick4);
	CVAR_REGISTER(&sk_barney_dmg_kick5);
	CVAR_REGISTER(&sk_barney_dmg_kick6);

	CVAR_REGISTER(&sk_barney_dmg_punch1);
	CVAR_REGISTER(&sk_barney_dmg_punch2);
	CVAR_REGISTER(&sk_barney_dmg_punch3);
	CVAR_REGISTER(&sk_barney_dmg_punch4);
	CVAR_REGISTER(&sk_barney_dmg_punch5);
	CVAR_REGISTER(&sk_barney_dmg_punch6);

	CVAR_REGISTER(&sk_barney_dmg_gunwhip1);
	CVAR_REGISTER(&sk_barney_dmg_gunwhip2);
	CVAR_REGISTER(&sk_barney_dmg_gunwhip3);
	CVAR_REGISTER(&sk_barney_dmg_gunwhip4);
	CVAR_REGISTER(&sk_barney_dmg_gunwhip5);
	CVAR_REGISTER(&sk_barney_dmg_gunwhip6);

	// Bullsquid
	CVAR_REGISTER(&sk_bullsquid_health1);
	CVAR_REGISTER(&sk_bullsquid_health2);
	CVAR_REGISTER(&sk_bullsquid_health3);
	CVAR_REGISTER(&sk_bullsquid_health4);
	CVAR_REGISTER(&sk_bullsquid_health5);
	CVAR_REGISTER(&sk_bullsquid_health6);

	CVAR_REGISTER(&sk_bullsquid_dmg_bite1);
	CVAR_REGISTER(&sk_bullsquid_dmg_bite2);
	CVAR_REGISTER(&sk_bullsquid_dmg_bite3);
	CVAR_REGISTER(&sk_bullsquid_dmg_bite4);
	CVAR_REGISTER(&sk_bullsquid_dmg_bite5);
	CVAR_REGISTER(&sk_bullsquid_dmg_bite6);

	CVAR_REGISTER(&sk_bullsquid_dmg_whip1);
	CVAR_REGISTER(&sk_bullsquid_dmg_whip2);
	CVAR_REGISTER(&sk_bullsquid_dmg_whip3);
	CVAR_REGISTER(&sk_bullsquid_dmg_whip4);
	CVAR_REGISTER(&sk_bullsquid_dmg_whip5);
	CVAR_REGISTER(&sk_bullsquid_dmg_whip6);

	CVAR_REGISTER(&sk_bullsquid_dmg_spit1);
	CVAR_REGISTER(&sk_bullsquid_dmg_spit2);
	CVAR_REGISTER(&sk_bullsquid_dmg_spit3);
	CVAR_REGISTER(&sk_bullsquid_dmg_spit4);
	CVAR_REGISTER(&sk_bullsquid_dmg_spit5);
	CVAR_REGISTER(&sk_bullsquid_dmg_spit6);

	// Big momma
	CVAR_REGISTER(&sk_bigmomma_health1);
	CVAR_REGISTER(&sk_bigmomma_health2);
	CVAR_REGISTER(&sk_bigmomma_health3);
	CVAR_REGISTER(&sk_bigmomma_health4);
	CVAR_REGISTER(&sk_bigmomma_health5);
	CVAR_REGISTER(&sk_bigmomma_health6);

	CVAR_REGISTER(&sk_bigmomma_health_factor1);
	CVAR_REGISTER(&sk_bigmomma_health_factor2);
	CVAR_REGISTER(&sk_bigmomma_health_factor3);
	CVAR_REGISTER(&sk_bigmomma_health_factor4);
	CVAR_REGISTER(&sk_bigmomma_health_factor5);
	CVAR_REGISTER(&sk_bigmomma_health_factor6);

	CVAR_REGISTER(&sk_bigmomma_dmg_slash1);
	CVAR_REGISTER(&sk_bigmomma_dmg_slash2);
	CVAR_REGISTER(&sk_bigmomma_dmg_slash3);
	CVAR_REGISTER(&sk_bigmomma_dmg_slash4);
	CVAR_REGISTER(&sk_bigmomma_dmg_slash5);
	CVAR_REGISTER(&sk_bigmomma_dmg_slash6);

	CVAR_REGISTER(&sk_bigmomma_dmg_blast1);
	CVAR_REGISTER(&sk_bigmomma_dmg_blast2);
	CVAR_REGISTER(&sk_bigmomma_dmg_blast3);
	CVAR_REGISTER(&sk_bigmomma_dmg_blast4);
	CVAR_REGISTER(&sk_bigmomma_dmg_blast5);
	CVAR_REGISTER(&sk_bigmomma_dmg_blast6);

	CVAR_REGISTER(&sk_bigmomma_radius_blast1);
	CVAR_REGISTER(&sk_bigmomma_radius_blast2);
	CVAR_REGISTER(&sk_bigmomma_radius_blast3);
	CVAR_REGISTER(&sk_bigmomma_radius_blast4);
	CVAR_REGISTER(&sk_bigmomma_radius_blast5);
	CVAR_REGISTER(&sk_bigmomma_radius_blast6);

	CVAR_REGISTER(&sk_bigmomma_dmg_ram1);
	CVAR_REGISTER(&sk_bigmomma_dmg_ram2);
	CVAR_REGISTER(&sk_bigmomma_dmg_ram3);
	CVAR_REGISTER(&sk_bigmomma_dmg_ram4);
	CVAR_REGISTER(&sk_bigmomma_dmg_ram5);
	CVAR_REGISTER(&sk_bigmomma_dmg_ram6);

	// Gargantua
	CVAR_REGISTER(&sk_gargantua_health1);
	CVAR_REGISTER(&sk_gargantua_health2);
	CVAR_REGISTER(&sk_gargantua_health3);
	CVAR_REGISTER(&sk_gargantua_health4);
	CVAR_REGISTER(&sk_gargantua_health5);
	CVAR_REGISTER(&sk_gargantua_health6);

	CVAR_REGISTER(&sk_gargantua_dmg_slash1);
	CVAR_REGISTER(&sk_gargantua_dmg_slash2);
	CVAR_REGISTER(&sk_gargantua_dmg_slash3);
	CVAR_REGISTER(&sk_gargantua_dmg_slash4);
	CVAR_REGISTER(&sk_gargantua_dmg_slash5);
	CVAR_REGISTER(&sk_gargantua_dmg_slash6);

	CVAR_REGISTER(&sk_gargantua_dmg_fire1);
	CVAR_REGISTER(&sk_gargantua_dmg_fire2);
	CVAR_REGISTER(&sk_gargantua_dmg_fire3);
	CVAR_REGISTER(&sk_gargantua_dmg_fire4);
	CVAR_REGISTER(&sk_gargantua_dmg_fire5);
	CVAR_REGISTER(&sk_gargantua_dmg_fire6);

	CVAR_REGISTER(&sk_gargantua_dmg_stomp1);
	CVAR_REGISTER(&sk_gargantua_dmg_stomp2);
	CVAR_REGISTER(&sk_gargantua_dmg_stomp3);
	CVAR_REGISTER(&sk_gargantua_dmg_stomp4);
	CVAR_REGISTER(&sk_gargantua_dmg_stomp5);
	CVAR_REGISTER(&sk_gargantua_dmg_stomp6);

	// Hassassin
	CVAR_REGISTER(&sk_hassassin_health1);
	CVAR_REGISTER(&sk_hassassin_health2);
	CVAR_REGISTER(&sk_hassassin_health3);
	CVAR_REGISTER(&sk_hassassin_health4);
	CVAR_REGISTER(&sk_hassassin_health5);
	CVAR_REGISTER(&sk_hassassin_health6);

	CVAR_REGISTER(&sk_hassassin_dmg_kick1);
	CVAR_REGISTER(&sk_hassassin_dmg_kick2);
	CVAR_REGISTER(&sk_hassassin_dmg_kick3);
	CVAR_REGISTER(&sk_hassassin_dmg_kick4);
	CVAR_REGISTER(&sk_hassassin_dmg_kick5);
	CVAR_REGISTER(&sk_hassassin_dmg_kick6);

	CVAR_REGISTER(&sk_hassassin_dmg_punch1);
	CVAR_REGISTER(&sk_hassassin_dmg_punch2);
	CVAR_REGISTER(&sk_hassassin_dmg_punch3);
	CVAR_REGISTER(&sk_hassassin_dmg_punch4);
	CVAR_REGISTER(&sk_hassassin_dmg_punch5);
	CVAR_REGISTER(&sk_hassassin_dmg_punch6);

	CVAR_REGISTER(&sk_hassassin_dmg_gunwhip1);
	CVAR_REGISTER(&sk_hassassin_dmg_gunwhip2);
	CVAR_REGISTER(&sk_hassassin_dmg_gunwhip3);
	CVAR_REGISTER(&sk_hassassin_dmg_gunwhip4);
	CVAR_REGISTER(&sk_hassassin_dmg_gunwhip5);
	CVAR_REGISTER(&sk_hassassin_dmg_gunwhip6);

	// Headcrab
	CVAR_REGISTER(&sk_headcrab_health1);
	CVAR_REGISTER(&sk_headcrab_health2);
	CVAR_REGISTER(&sk_headcrab_health3);
	CVAR_REGISTER(&sk_headcrab_health4);
	CVAR_REGISTER(&sk_headcrab_health5);
	CVAR_REGISTER(&sk_headcrab_health6);

	CVAR_REGISTER(&sk_headcrab_dmg_bite1);
	CVAR_REGISTER(&sk_headcrab_dmg_bite2);
	CVAR_REGISTER(&sk_headcrab_dmg_bite3);
	CVAR_REGISTER(&sk_headcrab_dmg_bite4);
	CVAR_REGISTER(&sk_headcrab_dmg_bite5);
	CVAR_REGISTER(&sk_headcrab_dmg_bite6);

	// Human Grunt
	CVAR_REGISTER(&sk_hgrunt_health1);
	CVAR_REGISTER(&sk_hgrunt_health2);
	CVAR_REGISTER(&sk_hgrunt_health3);
	CVAR_REGISTER(&sk_hgrunt_health4);
	CVAR_REGISTER(&sk_hgrunt_health5);
	CVAR_REGISTER(&sk_hgrunt_health6);

	CVAR_REGISTER(&sk_hgrunt_dmg_kick1);
	CVAR_REGISTER(&sk_hgrunt_dmg_kick2);
	CVAR_REGISTER(&sk_hgrunt_dmg_kick3);
	CVAR_REGISTER(&sk_hgrunt_dmg_kick4);
	CVAR_REGISTER(&sk_hgrunt_dmg_kick5);
	CVAR_REGISTER(&sk_hgrunt_dmg_kick6);

	CVAR_REGISTER(&sk_hgrunt_dmg_punch1);
	CVAR_REGISTER(&sk_hgrunt_dmg_punch2);
	CVAR_REGISTER(&sk_hgrunt_dmg_punch3);
	CVAR_REGISTER(&sk_hgrunt_dmg_punch4);
	CVAR_REGISTER(&sk_hgrunt_dmg_punch5);
	CVAR_REGISTER(&sk_hgrunt_dmg_punch6);

	CVAR_REGISTER(&sk_hgrunt_dmg_gunwhip1);
	CVAR_REGISTER(&sk_hgrunt_dmg_gunwhip2);
	CVAR_REGISTER(&sk_hgrunt_dmg_gunwhip3);
	CVAR_REGISTER(&sk_hgrunt_dmg_gunwhip4);
	CVAR_REGISTER(&sk_hgrunt_dmg_gunwhip5);
	CVAR_REGISTER(&sk_hgrunt_dmg_gunwhip6);

	// Houndeye
	CVAR_REGISTER(&sk_houndeye_health1);
	CVAR_REGISTER(&sk_houndeye_health2);
	CVAR_REGISTER(&sk_houndeye_health3);
	CVAR_REGISTER(&sk_houndeye_health4);
	CVAR_REGISTER(&sk_houndeye_health5);
	CVAR_REGISTER(&sk_houndeye_health6);

	CVAR_REGISTER(&sk_houndeye_dmg_blast1);
	CVAR_REGISTER(&sk_houndeye_dmg_blast2);
	CVAR_REGISTER(&sk_houndeye_dmg_blast3);
	CVAR_REGISTER(&sk_houndeye_dmg_blast4);
	CVAR_REGISTER(&sk_houndeye_dmg_blast5);
	CVAR_REGISTER(&sk_houndeye_dmg_blast6);

	CVAR_REGISTER(&sk_houndeye_dmg_bark1);
	CVAR_REGISTER(&sk_houndeye_dmg_bark2);
	CVAR_REGISTER(&sk_houndeye_dmg_bark3);
	CVAR_REGISTER(&sk_houndeye_dmg_bark4);
	CVAR_REGISTER(&sk_houndeye_dmg_bark5);
	CVAR_REGISTER(&sk_houndeye_dmg_bark6);

	// ISlave
	CVAR_REGISTER(&sk_islave_health1);
	CVAR_REGISTER(&sk_islave_health2);
	CVAR_REGISTER(&sk_islave_health3);
	CVAR_REGISTER(&sk_islave_health4);
	CVAR_REGISTER(&sk_islave_health5);
	CVAR_REGISTER(&sk_islave_health6);

	CVAR_REGISTER(&sk_islave_dmg_claw1);
	CVAR_REGISTER(&sk_islave_dmg_claw2);
	CVAR_REGISTER(&sk_islave_dmg_claw3);
	CVAR_REGISTER(&sk_islave_dmg_claw4);
	CVAR_REGISTER(&sk_islave_dmg_claw5);
	CVAR_REGISTER(&sk_islave_dmg_claw6);

	CVAR_REGISTER(&sk_islave_dmg_clawrake1);
	CVAR_REGISTER(&sk_islave_dmg_clawrake2);
	CVAR_REGISTER(&sk_islave_dmg_clawrake3);
	CVAR_REGISTER(&sk_islave_dmg_clawrake4);
	CVAR_REGISTER(&sk_islave_dmg_clawrake5);
	CVAR_REGISTER(&sk_islave_dmg_clawrake6);

	CVAR_REGISTER(&sk_islave_dmg_zap1);
	CVAR_REGISTER(&sk_islave_dmg_zap2);
	CVAR_REGISTER(&sk_islave_dmg_zap3);
	CVAR_REGISTER(&sk_islave_dmg_zap4);
	CVAR_REGISTER(&sk_islave_dmg_zap5);
	CVAR_REGISTER(&sk_islave_dmg_zap6);

	CVAR_REGISTER(&sk_islave_dmg_zapstomp1);
	CVAR_REGISTER(&sk_islave_dmg_zapstomp2);
	CVAR_REGISTER(&sk_islave_dmg_zapstomp3);
	CVAR_REGISTER(&sk_islave_dmg_zapstomp4);
	CVAR_REGISTER(&sk_islave_dmg_zapstomp5);
	CVAR_REGISTER(&sk_islave_dmg_zapstomp6);

	CVAR_REGISTER(&sk_islave_heal1);
	CVAR_REGISTER(&sk_islave_heal2);
	CVAR_REGISTER(&sk_islave_heal3);
	CVAR_REGISTER(&sk_islave_heal4);
	CVAR_REGISTER(&sk_islave_heal5);
	CVAR_REGISTER(&sk_islave_heal6);

	CVAR_REGISTER(&sk_islave_power1);
	CVAR_REGISTER(&sk_islave_power2);
	CVAR_REGISTER(&sk_islave_power3);
	CVAR_REGISTER(&sk_islave_power4);
	CVAR_REGISTER(&sk_islave_power5);
	CVAR_REGISTER(&sk_islave_power6);

	// Icthyosaur
	CVAR_REGISTER(&sk_ichthyosaur_health1);
	CVAR_REGISTER(&sk_ichthyosaur_health2);
	CVAR_REGISTER(&sk_ichthyosaur_health3);
	CVAR_REGISTER(&sk_ichthyosaur_health4);
	CVAR_REGISTER(&sk_ichthyosaur_health5);
	CVAR_REGISTER(&sk_ichthyosaur_health6);

	CVAR_REGISTER(&sk_ichthyosaur_dmg_chomp1);
	CVAR_REGISTER(&sk_ichthyosaur_dmg_chomp2);
	CVAR_REGISTER(&sk_ichthyosaur_dmg_chomp3);
	CVAR_REGISTER(&sk_ichthyosaur_dmg_chomp4);
	CVAR_REGISTER(&sk_ichthyosaur_dmg_chomp5);
	CVAR_REGISTER(&sk_ichthyosaur_dmg_chomp6);

	// Leech
	CVAR_REGISTER(&sk_leech_health1);
	CVAR_REGISTER(&sk_leech_health2);
	CVAR_REGISTER(&sk_leech_health3);
	CVAR_REGISTER(&sk_leech_health4);
	CVAR_REGISTER(&sk_leech_health5);
	CVAR_REGISTER(&sk_leech_health6);

	CVAR_REGISTER(&sk_leech_dmg_bite1);
	CVAR_REGISTER(&sk_leech_dmg_bite2);
	CVAR_REGISTER(&sk_leech_dmg_bite3);
	CVAR_REGISTER(&sk_leech_dmg_bite4);
	CVAR_REGISTER(&sk_leech_dmg_bite5);
	CVAR_REGISTER(&sk_leech_dmg_bite6);

	// Controller
	CVAR_REGISTER(&sk_controller_health1);
	CVAR_REGISTER(&sk_controller_health2);
	CVAR_REGISTER(&sk_controller_health3);
	CVAR_REGISTER(&sk_controller_health4);
	CVAR_REGISTER(&sk_controller_health5);
	CVAR_REGISTER(&sk_controller_health6);

	CVAR_REGISTER(&sk_controller_speed_ball1);
	CVAR_REGISTER(&sk_controller_speed_ball2);
	CVAR_REGISTER(&sk_controller_speed_ball3);
	CVAR_REGISTER(&sk_controller_speed_ball4);
	CVAR_REGISTER(&sk_controller_speed_ball5);
	CVAR_REGISTER(&sk_controller_speed_ball6);

	CVAR_REGISTER(&sk_controller_dmg_ball1);
	CVAR_REGISTER(&sk_controller_dmg_ball2);
	CVAR_REGISTER(&sk_controller_dmg_ball3);
	CVAR_REGISTER(&sk_controller_dmg_ball4);
	CVAR_REGISTER(&sk_controller_dmg_ball5);
	CVAR_REGISTER(&sk_controller_dmg_ball6);

	CVAR_REGISTER(&sk_controller_dmg_zap1);
	CVAR_REGISTER(&sk_controller_dmg_zap2);
	CVAR_REGISTER(&sk_controller_dmg_zap3);
	CVAR_REGISTER(&sk_controller_dmg_zap4);
	CVAR_REGISTER(&sk_controller_dmg_zap5);
	CVAR_REGISTER(&sk_controller_dmg_zap6);

	CVAR_REGISTER(&sk_controller_dmg_slash1);
	CVAR_REGISTER(&sk_controller_dmg_slash2);
	CVAR_REGISTER(&sk_controller_dmg_slash3);
	CVAR_REGISTER(&sk_controller_dmg_slash4);
	CVAR_REGISTER(&sk_controller_dmg_slash5);
	CVAR_REGISTER(&sk_controller_dmg_slash6);

	// Nihilanth
	CVAR_REGISTER(&sk_nihilanth_health1);
	CVAR_REGISTER(&sk_nihilanth_health2);
	CVAR_REGISTER(&sk_nihilanth_health3);
	CVAR_REGISTER(&sk_nihilanth_health4);
	CVAR_REGISTER(&sk_nihilanth_health5);
	CVAR_REGISTER(&sk_nihilanth_health6);

	CVAR_REGISTER(&sk_nihilanth_speed_ball1);
	CVAR_REGISTER(&sk_nihilanth_speed_ball2);
	CVAR_REGISTER(&sk_nihilanth_speed_ball3);
	CVAR_REGISTER(&sk_nihilanth_speed_ball4);
	CVAR_REGISTER(&sk_nihilanth_speed_ball5);
	CVAR_REGISTER(&sk_nihilanth_speed_ball6);

	CVAR_REGISTER(&sk_nihilanth_dmg_ball1);
	CVAR_REGISTER(&sk_nihilanth_dmg_ball2);
	CVAR_REGISTER(&sk_nihilanth_dmg_ball3);
	CVAR_REGISTER(&sk_nihilanth_dmg_ball4);
	CVAR_REGISTER(&sk_nihilanth_dmg_ball5);
	CVAR_REGISTER(&sk_nihilanth_dmg_ball6);

	CVAR_REGISTER(&sk_nihilanth_dmg_zap1);
	CVAR_REGISTER(&sk_nihilanth_dmg_zap2);
	CVAR_REGISTER(&sk_nihilanth_dmg_zap3);
	CVAR_REGISTER(&sk_nihilanth_dmg_zap4);
	CVAR_REGISTER(&sk_nihilanth_dmg_zap5);
	CVAR_REGISTER(&sk_nihilanth_dmg_zap6);

	CVAR_REGISTER(&sk_nihilanth_dmg_slash1);
	CVAR_REGISTER(&sk_nihilanth_dmg_slash2);
	CVAR_REGISTER(&sk_nihilanth_dmg_slash3);
	CVAR_REGISTER(&sk_nihilanth_dmg_slash4);
	CVAR_REGISTER(&sk_nihilanth_dmg_slash5);
	CVAR_REGISTER(&sk_nihilanth_dmg_slash6);

	// Scientist
	CVAR_REGISTER(&sk_scientist_health1);
	CVAR_REGISTER(&sk_scientist_health2);
	CVAR_REGISTER(&sk_scientist_health3);
	CVAR_REGISTER(&sk_scientist_health4);
	CVAR_REGISTER(&sk_scientist_health5);
	CVAR_REGISTER(&sk_scientist_health6);

	CVAR_REGISTER(&sk_scientist_dmg_punch1);
	CVAR_REGISTER(&sk_scientist_dmg_punch2);
	CVAR_REGISTER(&sk_scientist_dmg_punch3);
	CVAR_REGISTER(&sk_scientist_dmg_punch4);
	CVAR_REGISTER(&sk_scientist_dmg_punch5);
	CVAR_REGISTER(&sk_scientist_dmg_punch6);

	CVAR_REGISTER(&sk_scientist_dmg_kick1);
	CVAR_REGISTER(&sk_scientist_dmg_kick2);
	CVAR_REGISTER(&sk_scientist_dmg_kick3);
	CVAR_REGISTER(&sk_scientist_dmg_kick4);
	CVAR_REGISTER(&sk_scientist_dmg_kick5);
	CVAR_REGISTER(&sk_scientist_dmg_kick6);

	CVAR_REGISTER(&sk_scientist_heal1);
	CVAR_REGISTER(&sk_scientist_heal2);
	CVAR_REGISTER(&sk_scientist_heal3);
	CVAR_REGISTER(&sk_scientist_heal4);
	CVAR_REGISTER(&sk_scientist_heal5);
	CVAR_REGISTER(&sk_scientist_heal6);

	// Zombie
	CVAR_REGISTER(&sk_zombie_health1);
	CVAR_REGISTER(&sk_zombie_health2);
	CVAR_REGISTER(&sk_zombie_health3);
	CVAR_REGISTER(&sk_zombie_health4);
	CVAR_REGISTER(&sk_zombie_health5);
	CVAR_REGISTER(&sk_zombie_health6);

	CVAR_REGISTER(&sk_zombie_dmg_one_slash1);
	CVAR_REGISTER(&sk_zombie_dmg_one_slash2);
	CVAR_REGISTER(&sk_zombie_dmg_one_slash3);
	CVAR_REGISTER(&sk_zombie_dmg_one_slash4);
	CVAR_REGISTER(&sk_zombie_dmg_one_slash5);
	CVAR_REGISTER(&sk_zombie_dmg_one_slash6);

	CVAR_REGISTER(&sk_zombie_dmg_both_slash1);
	CVAR_REGISTER(&sk_zombie_dmg_both_slash2);
	CVAR_REGISTER(&sk_zombie_dmg_both_slash3);
	CVAR_REGISTER(&sk_zombie_dmg_both_slash4);
	CVAR_REGISTER(&sk_zombie_dmg_both_slash5);
	CVAR_REGISTER(&sk_zombie_dmg_both_slash6);

	// Gonome
	CVAR_REGISTER(&sk_gonome_health1);
	CVAR_REGISTER(&sk_gonome_health2);
	CVAR_REGISTER(&sk_gonome_health3);
	CVAR_REGISTER(&sk_gonome_health4);
	CVAR_REGISTER(&sk_gonome_health5);
	CVAR_REGISTER(&sk_gonome_health6);

	CVAR_REGISTER(&sk_gonome_headcrab_health1);
	CVAR_REGISTER(&sk_gonome_headcrab_health2);
	CVAR_REGISTER(&sk_gonome_headcrab_health3);
	CVAR_REGISTER(&sk_gonome_headcrab_health4);
	CVAR_REGISTER(&sk_gonome_headcrab_health5);
	CVAR_REGISTER(&sk_gonome_headcrab_health6);

	CVAR_REGISTER(&sk_gonome_dmg_slash1);
	CVAR_REGISTER(&sk_gonome_dmg_slash2);
	CVAR_REGISTER(&sk_gonome_dmg_slash3);
	CVAR_REGISTER(&sk_gonome_dmg_slash4);
	CVAR_REGISTER(&sk_gonome_dmg_slash5);
	CVAR_REGISTER(&sk_gonome_dmg_slash6);

	CVAR_REGISTER(&sk_gonome_dmg_chomp1);
	CVAR_REGISTER(&sk_gonome_dmg_chomp2);
	CVAR_REGISTER(&sk_gonome_dmg_chomp3);
	CVAR_REGISTER(&sk_gonome_dmg_chomp4);
	CVAR_REGISTER(&sk_gonome_dmg_chomp5);
	CVAR_REGISTER(&sk_gonome_dmg_chomp6);

	CVAR_REGISTER(&sk_gonome_dmg_leap1);
	CVAR_REGISTER(&sk_gonome_dmg_leap2);
	CVAR_REGISTER(&sk_gonome_dmg_leap3);
	CVAR_REGISTER(&sk_gonome_dmg_leap4);
	CVAR_REGISTER(&sk_gonome_dmg_leap5);
	CVAR_REGISTER(&sk_gonome_dmg_leap6);

	CVAR_REGISTER(&sk_gonome_dmg_acid1);
	CVAR_REGISTER(&sk_gonome_dmg_acid2);
	CVAR_REGISTER(&sk_gonome_dmg_acid3);
	CVAR_REGISTER(&sk_gonome_dmg_acid4);
	CVAR_REGISTER(&sk_gonome_dmg_acid5);
	CVAR_REGISTER(&sk_gonome_dmg_acid6);

	//Turret
	CVAR_REGISTER(&sk_turret_health1);
	CVAR_REGISTER(&sk_turret_health2);
	CVAR_REGISTER(&sk_turret_health3);
	CVAR_REGISTER(&sk_turret_health4);
	CVAR_REGISTER(&sk_turret_health5);
	CVAR_REGISTER(&sk_turret_health6);

	// MiniTurret
	CVAR_REGISTER(&sk_miniturret_health1);
	CVAR_REGISTER(&sk_miniturret_health2);
	CVAR_REGISTER(&sk_miniturret_health3);
	CVAR_REGISTER(&sk_miniturret_health4);
	CVAR_REGISTER(&sk_miniturret_health5);
	CVAR_REGISTER(&sk_miniturret_health6);

	// Sentry Turret
	CVAR_REGISTER(&sk_sentry_health1);
	CVAR_REGISTER(&sk_sentry_health2);
	CVAR_REGISTER(&sk_sentry_health3);
	CVAR_REGISTER(&sk_sentry_health4);
	CVAR_REGISTER(&sk_sentry_health5);
	CVAR_REGISTER(&sk_sentry_health6);

	// Shock Trooper
	CVAR_REGISTER(&sk_strooper_health1);
	CVAR_REGISTER(&sk_strooper_health2);
	CVAR_REGISTER(&sk_strooper_health3);
	CVAR_REGISTER(&sk_strooper_health4);
	CVAR_REGISTER(&sk_strooper_health5);
	CVAR_REGISTER(&sk_strooper_health6);

	CVAR_REGISTER(&sk_strooper_dmg_bite1);
	CVAR_REGISTER(&sk_strooper_dmg_bite2);
	CVAR_REGISTER(&sk_strooper_dmg_bite3);
	CVAR_REGISTER(&sk_strooper_dmg_bite4);
	CVAR_REGISTER(&sk_strooper_dmg_bite5);
	CVAR_REGISTER(&sk_strooper_dmg_bite6);

	CVAR_REGISTER(&sk_strooper_dmg_slap1);
	CVAR_REGISTER(&sk_strooper_dmg_slap2);
	CVAR_REGISTER(&sk_strooper_dmg_slap3);
	CVAR_REGISTER(&sk_strooper_dmg_slap4);
	CVAR_REGISTER(&sk_strooper_dmg_slap5);
	CVAR_REGISTER(&sk_strooper_dmg_slap6);

	CVAR_REGISTER(&sk_strooper_dmg_palm1);
	CVAR_REGISTER(&sk_strooper_dmg_palm2);
	CVAR_REGISTER(&sk_strooper_dmg_palm3);
	CVAR_REGISTER(&sk_strooper_dmg_palm4);
	CVAR_REGISTER(&sk_strooper_dmg_palm5);
	CVAR_REGISTER(&sk_strooper_dmg_palm6);

	// =========================== //
	//           WEAPONS           //
	// =========================== //

	// === 1 - MELEE === //

	// Fists
	CVAR_REGISTER(&sk_plr_punch1);
	CVAR_REGISTER(&sk_plr_punch2);
	CVAR_REGISTER(&sk_plr_punch3);
	CVAR_REGISTER(&sk_plr_punch4);
	CVAR_REGISTER(&sk_plr_punch5);
	CVAR_REGISTER(&sk_plr_punch6);

	CVAR_REGISTER(&sk_plr_uppercut1);
	CVAR_REGISTER(&sk_plr_uppercut2);
	CVAR_REGISTER(&sk_plr_uppercut3);
	CVAR_REGISTER(&sk_plr_uppercut4);
	CVAR_REGISTER(&sk_plr_uppercut5);
	CVAR_REGISTER(&sk_plr_uppercut6);

	CVAR_REGISTER(&sk_plr_kick1);
	CVAR_REGISTER(&sk_plr_kick2);
	CVAR_REGISTER(&sk_plr_kick3);
	CVAR_REGISTER(&sk_plr_kick4);
	CVAR_REGISTER(&sk_plr_kick5);
	CVAR_REGISTER(&sk_plr_kick6);

	CVAR_REGISTER(&sk_plr_counter1);
	CVAR_REGISTER(&sk_plr_counter2);
	CVAR_REGISTER(&sk_plr_counter3);
	CVAR_REGISTER(&sk_plr_counter4);
	CVAR_REGISTER(&sk_plr_counter5);
	CVAR_REGISTER(&sk_plr_counter6);

	// Spanner
	CVAR_REGISTER(&sk_plr_span_light1);
	CVAR_REGISTER(&sk_plr_span_light2);
	CVAR_REGISTER(&sk_plr_span_light3);
	CVAR_REGISTER(&sk_plr_span_light4);
	CVAR_REGISTER(&sk_plr_span_light5);
	CVAR_REGISTER(&sk_plr_span_light6);

	CVAR_REGISTER(&sk_plr_span_heavy1);
	CVAR_REGISTER(&sk_plr_span_heavy2);
	CVAR_REGISTER(&sk_plr_span_heavy3);
	CVAR_REGISTER(&sk_plr_span_heavy4);
	CVAR_REGISTER(&sk_plr_span_heavy5);
	CVAR_REGISTER(&sk_plr_span_heavy6);

	CVAR_REGISTER(&sk_plr_span_thrown1);
	CVAR_REGISTER(&sk_plr_span_thrown2);
	CVAR_REGISTER(&sk_plr_span_thrown3);
	CVAR_REGISTER(&sk_plr_span_thrown4);
	CVAR_REGISTER(&sk_plr_span_thrown5);
	CVAR_REGISTER(&sk_plr_span_thrown6);

	CVAR_REGISTER(&sk_plr_span_counter1);
	CVAR_REGISTER(&sk_plr_span_counter2);
	CVAR_REGISTER(&sk_plr_span_counter3);
	CVAR_REGISTER(&sk_plr_span_counter4);
	CVAR_REGISTER(&sk_plr_span_counter5);
	CVAR_REGISTER(&sk_plr_span_counter6);

	// Knife
	CVAR_REGISTER(&sk_plr_knife_light1);
	CVAR_REGISTER(&sk_plr_knife_light2);
	CVAR_REGISTER(&sk_plr_knife_light3);
	CVAR_REGISTER(&sk_plr_knife_light4);
	CVAR_REGISTER(&sk_plr_knife_light5);
	CVAR_REGISTER(&sk_plr_knife_light6);

	CVAR_REGISTER(&sk_plr_knife_heavy1);
	CVAR_REGISTER(&sk_plr_knife_heavy2);
	CVAR_REGISTER(&sk_plr_knife_heavy3);
	CVAR_REGISTER(&sk_plr_knife_heavy4);
	CVAR_REGISTER(&sk_plr_knife_heavy5);
	CVAR_REGISTER(&sk_plr_knife_heavy6);

	CVAR_REGISTER(&sk_plr_knife_thrown1);
	CVAR_REGISTER(&sk_plr_knife_thrown2);
	CVAR_REGISTER(&sk_plr_knife_thrown3);
	CVAR_REGISTER(&sk_plr_knife_thrown4);
	CVAR_REGISTER(&sk_plr_knife_thrown5);
	CVAR_REGISTER(&sk_plr_knife_thrown6);

	CVAR_REGISTER(&sk_plr_knife_counter1);
	CVAR_REGISTER(&sk_plr_knife_counter2);
	CVAR_REGISTER(&sk_plr_knife_counter3);
	CVAR_REGISTER(&sk_plr_knife_counter4);
	CVAR_REGISTER(&sk_plr_knife_counter5);
	CVAR_REGISTER(&sk_plr_knife_counter6);

	// Crowbar
	CVAR_REGISTER(&sk_plr_cbar_light1);
	CVAR_REGISTER(&sk_plr_cbar_light2);
	CVAR_REGISTER(&sk_plr_cbar_light3);
	CVAR_REGISTER(&sk_plr_cbar_light4);
	CVAR_REGISTER(&sk_plr_cbar_light5);
	CVAR_REGISTER(&sk_plr_cbar_light6);

	CVAR_REGISTER(&sk_plr_cbar_heavy1);
	CVAR_REGISTER(&sk_plr_cbar_heavy2);
	CVAR_REGISTER(&sk_plr_cbar_heavy3);
	CVAR_REGISTER(&sk_plr_cbar_heavy4);
	CVAR_REGISTER(&sk_plr_cbar_heavy5);
	CVAR_REGISTER(&sk_plr_cbar_heavy6);

	CVAR_REGISTER(&sk_plr_cbar_thrown1);
	CVAR_REGISTER(&sk_plr_cbar_thrown2);
	CVAR_REGISTER(&sk_plr_cbar_thrown3);
	CVAR_REGISTER(&sk_plr_cbar_thrown4);
	CVAR_REGISTER(&sk_plr_cbar_thrown5);
	CVAR_REGISTER(&sk_plr_cbar_thrown6);

	CVAR_REGISTER(&sk_plr_cbar_counter1);
	CVAR_REGISTER(&sk_plr_cbar_counter2);
	CVAR_REGISTER(&sk_plr_cbar_counter3);
	CVAR_REGISTER(&sk_plr_cbar_counter4);
	CVAR_REGISTER(&sk_plr_cbar_counter5);
	CVAR_REGISTER(&sk_plr_cbar_counter6);

	// Pipewrench
	CVAR_REGISTER(&sk_plr_pwrench_light1);
	CVAR_REGISTER(&sk_plr_pwrench_light2);
	CVAR_REGISTER(&sk_plr_pwrench_light3);
	CVAR_REGISTER(&sk_plr_pwrench_light4);
	CVAR_REGISTER(&sk_plr_pwrench_light5);
	CVAR_REGISTER(&sk_plr_pwrench_light6);

	CVAR_REGISTER(&sk_plr_pwrench_heavy1);
	CVAR_REGISTER(&sk_plr_pwrench_heavy2);
	CVAR_REGISTER(&sk_plr_pwrench_heavy3);
	CVAR_REGISTER(&sk_plr_pwrench_heavy4);
	CVAR_REGISTER(&sk_plr_pwrench_heavy5);
	CVAR_REGISTER(&sk_plr_pwrench_heavy6);

	CVAR_REGISTER(&sk_plr_pwrench_thrown1);
	CVAR_REGISTER(&sk_plr_pwrench_thrown2);
	CVAR_REGISTER(&sk_plr_pwrench_thrown3);
	CVAR_REGISTER(&sk_plr_pwrench_thrown4);
	CVAR_REGISTER(&sk_plr_pwrench_thrown5);
	CVAR_REGISTER(&sk_plr_pwrench_thrown6);

	CVAR_REGISTER(&sk_plr_pwrench_counter1);
	CVAR_REGISTER(&sk_plr_pwrench_counter2);
	CVAR_REGISTER(&sk_plr_pwrench_counter3);
	CVAR_REGISTER(&sk_plr_pwrench_counter4);
	CVAR_REGISTER(&sk_plr_pwrench_counter5);
	CVAR_REGISTER(&sk_plr_pwrench_counter6);

	// === 2 - PISTOLS === //

	// 9mm Round (Glock-17)
	CVAR_REGISTER(&sk_plr_9mm1);
	CVAR_REGISTER(&sk_plr_9mm2);
	CVAR_REGISTER(&sk_plr_9mm3);
	CVAR_REGISTER(&sk_plr_9mm4);
	CVAR_REGISTER(&sk_plr_9mm5);
	CVAR_REGISTER(&sk_plr_9mm6);

	// 38 SW (M9 Beretta)
	CVAR_REGISTER(&sk_plr_38sw1);
	CVAR_REGISTER(&sk_plr_38sw2);
	CVAR_REGISTER(&sk_plr_38sw3);
	CVAR_REGISTER(&sk_plr_38sw4);
	CVAR_REGISTER(&sk_plr_38sw5);
	CVAR_REGISTER(&sk_plr_38sw6);

	// .357 Magnum Round
	CVAR_REGISTER(&sk_plr_357mag1);
	CVAR_REGISTER(&sk_plr_357mag2);
	CVAR_REGISTER(&sk_plr_357mag3);
	CVAR_REGISTER(&sk_plr_357mag4);
	CVAR_REGISTER(&sk_plr_357mag5);
	CVAR_REGISTER(&sk_plr_357mag6);

	// .44 SW Round (Desert Eagle)
	CVAR_REGISTER(&sk_plr_44sw1);
	CVAR_REGISTER(&sk_plr_44sw2);
	CVAR_REGISTER(&sk_plr_44sw3);
	CVAR_REGISTER(&sk_plr_44sw4);
	CVAR_REGISTER(&sk_plr_44sw5);
	CVAR_REGISTER(&sk_plr_44sw6);

	// === 3 - SHOTGUNS & MACHINE-GUNS === //

	// 12 Gauge (Autoshotgun)
	CVAR_REGISTER(&sk_plr_12gauge1);
	CVAR_REGISTER(&sk_plr_12gauge2);
	CVAR_REGISTER(&sk_plr_12gauge3);
	CVAR_REGISTER(&sk_plr_12gauge4);
	CVAR_REGISTER(&sk_plr_12gauge5);
	CVAR_REGISTER(&sk_plr_12gauge6);

	// Trench Gun
	CVAR_REGISTER(&sk_plr_expgauge1);
	CVAR_REGISTER(&sk_plr_expgauge2);
	CVAR_REGISTER(&sk_plr_expgauge3);
	CVAR_REGISTER(&sk_plr_expgauge4);
	CVAR_REGISTER(&sk_plr_expgauge5);
	CVAR_REGISTER(&sk_plr_expgauge6);

	CVAR_REGISTER(&sk_plr_flamegauge1);
	CVAR_REGISTER(&sk_plr_flamegauge2);
	CVAR_REGISTER(&sk_plr_flamegauge3);
	CVAR_REGISTER(&sk_plr_flamegauge4);
	CVAR_REGISTER(&sk_plr_flamegauge5);
	CVAR_REGISTER(&sk_plr_flamegauge6);

	// 25 Gauge (Super Shotgun)
	CVAR_REGISTER(&sk_plr_25gauge1);
	CVAR_REGISTER(&sk_plr_25gauge2);
	CVAR_REGISTER(&sk_plr_25gauge3);
	CVAR_REGISTER(&sk_plr_25gauge4);
	CVAR_REGISTER(&sk_plr_25gauge5);
	CVAR_REGISTER(&sk_plr_25gauge6);

	// MP5
	CVAR_REGISTER(&sk_plr_9mmh1);
	CVAR_REGISTER(&sk_plr_9mmh2);
	CVAR_REGISTER(&sk_plr_9mmh3);
	CVAR_REGISTER(&sk_plr_9mmh4);
	CVAR_REGISTER(&sk_plr_9mmh5);
	CVAR_REGISTER(&sk_plr_9mmh6);

	CVAR_REGISTER(&sk_plr_40mm_blast1);
	CVAR_REGISTER(&sk_plr_40mm_blast2);
	CVAR_REGISTER(&sk_plr_40mm_blast3);
	CVAR_REGISTER(&sk_plr_40mm_blast4);
	CVAR_REGISTER(&sk_plr_40mm_blast5);
	CVAR_REGISTER(&sk_plr_40mm_blast6);

	CVAR_REGISTER(&sk_plr_40mm_heat1);
	CVAR_REGISTER(&sk_plr_40mm_heat2);
	CVAR_REGISTER(&sk_plr_40mm_heat3);
	CVAR_REGISTER(&sk_plr_40mm_heat4);
	CVAR_REGISTER(&sk_plr_40mm_heat5);
	CVAR_REGISTER(&sk_plr_40mm_heat6);

	CVAR_REGISTER(&sk_plr_40mm_shrap1);
	CVAR_REGISTER(&sk_plr_40mm_shrap2);
	CVAR_REGISTER(&sk_plr_40mm_shrap3);
	CVAR_REGISTER(&sk_plr_40mm_shrap4);
	CVAR_REGISTER(&sk_plr_40mm_shrap5);
	CVAR_REGISTER(&sk_plr_40mm_shrap6);

	CVAR_REGISTER(&sk_plr_40mm_smack1);
	CVAR_REGISTER(&sk_plr_40mm_smack2);
	CVAR_REGISTER(&sk_plr_40mm_smack3);
	CVAR_REGISTER(&sk_plr_40mm_smack4);
	CVAR_REGISTER(&sk_plr_40mm_smack5);
	CVAR_REGISTER(&sk_plr_40mm_smack6);

	// M4
	CVAR_REGISTER(&sk_plr_556nato1);
	CVAR_REGISTER(&sk_plr_556nato2);
	CVAR_REGISTER(&sk_plr_556nato3);
	CVAR_REGISTER(&sk_plr_556nato4);
	CVAR_REGISTER(&sk_plr_556nato5);
	CVAR_REGISTER(&sk_plr_556nato6);

	CVAR_REGISTER(&sk_plr_smokegrenade_blast1);
	CVAR_REGISTER(&sk_plr_smokegrenade_blast2);
	CVAR_REGISTER(&sk_plr_smokegrenade_blast3);
	CVAR_REGISTER(&sk_plr_smokegrenade_blast4);
	CVAR_REGISTER(&sk_plr_smokegrenade_blast5);
	CVAR_REGISTER(&sk_plr_smokegrenade_blast6);

	CVAR_REGISTER(&sk_plr_smokegrenade_heat1);
	CVAR_REGISTER(&sk_plr_smokegrenade_heat2);
	CVAR_REGISTER(&sk_plr_smokegrenade_heat3);
	CVAR_REGISTER(&sk_plr_smokegrenade_heat4);
	CVAR_REGISTER(&sk_plr_smokegrenade_heat5);
	CVAR_REGISTER(&sk_plr_smokegrenade_heat6);

	CVAR_REGISTER(&sk_plr_smokegrenade_shrap1);
	CVAR_REGISTER(&sk_plr_smokegrenade_shrap2);
	CVAR_REGISTER(&sk_plr_smokegrenade_shrap3);
	CVAR_REGISTER(&sk_plr_smokegrenade_shrap4);
	CVAR_REGISTER(&sk_plr_smokegrenade_shrap5);
	CVAR_REGISTER(&sk_plr_smokegrenade_shrap6);

	CVAR_REGISTER(&sk_plr_smokegrenade_smack1);
	CVAR_REGISTER(&sk_plr_smokegrenade_smack2);
	CVAR_REGISTER(&sk_plr_smokegrenade_smack3);
	CVAR_REGISTER(&sk_plr_smokegrenade_smack4);
	CVAR_REGISTER(&sk_plr_smokegrenade_smack5);
	CVAR_REGISTER(&sk_plr_smokegrenade_smack6);

	// 7.62R (AK-47)
	CVAR_REGISTER(&sk_plr_762r1);
	CVAR_REGISTER(&sk_plr_762r2);
	CVAR_REGISTER(&sk_plr_762r3);
	CVAR_REGISTER(&sk_plr_762r4);
	CVAR_REGISTER(&sk_plr_762r5);
	CVAR_REGISTER(&sk_plr_762r6);

	CVAR_REGISTER(&sk_plr_her_blast1);
	CVAR_REGISTER(&sk_plr_her_blast2);
	CVAR_REGISTER(&sk_plr_her_blast3);
	CVAR_REGISTER(&sk_plr_her_blast4);
	CVAR_REGISTER(&sk_plr_her_blast5);
	CVAR_REGISTER(&sk_plr_her_blast6);

	CVAR_REGISTER(&sk_plr_her_heat1);
	CVAR_REGISTER(&sk_plr_her_heat2);
	CVAR_REGISTER(&sk_plr_her_heat3);
	CVAR_REGISTER(&sk_plr_her_heat4);
	CVAR_REGISTER(&sk_plr_her_heat5);
	CVAR_REGISTER(&sk_plr_her_heat6);

	CVAR_REGISTER(&sk_plr_her_shrap1);
	CVAR_REGISTER(&sk_plr_her_shrap2);
	CVAR_REGISTER(&sk_plr_her_shrap3);
	CVAR_REGISTER(&sk_plr_her_shrap4);
	CVAR_REGISTER(&sk_plr_her_shrap5);
	CVAR_REGISTER(&sk_plr_her_shrap6);

	// Nailgun
	CVAR_REGISTER(&sk_plr_nail1);
	CVAR_REGISTER(&sk_plr_nail2);
	CVAR_REGISTER(&sk_plr_nail3);
	CVAR_REGISTER(&sk_plr_nail4);
	CVAR_REGISTER(&sk_plr_nail5);
	CVAR_REGISTER(&sk_plr_nail6);

	CVAR_REGISTER(&sk_plr_heatnail1);
	CVAR_REGISTER(&sk_plr_heatnail2);
	CVAR_REGISTER(&sk_plr_heatnail3);
	CVAR_REGISTER(&sk_plr_heatnail4);
	CVAR_REGISTER(&sk_plr_heatnail5);
	CVAR_REGISTER(&sk_plr_heatnail6);

	CVAR_REGISTER(&sk_plr_nailbomb_blast1);
	CVAR_REGISTER(&sk_plr_nailbomb_blast2);
	CVAR_REGISTER(&sk_plr_nailbomb_blast3);
	CVAR_REGISTER(&sk_plr_nailbomb_blast4);
	CVAR_REGISTER(&sk_plr_nailbomb_blast5);
	CVAR_REGISTER(&sk_plr_nailbomb_blast6);

	CVAR_REGISTER(&sk_plr_nailbomb_heat1);
	CVAR_REGISTER(&sk_plr_nailbomb_heat2);
	CVAR_REGISTER(&sk_plr_nailbomb_heat3);
	CVAR_REGISTER(&sk_plr_nailbomb_heat4);
	CVAR_REGISTER(&sk_plr_nailbomb_heat5);
	CVAR_REGISTER(&sk_plr_nailbomb_heat6);

	CVAR_REGISTER(&sk_plr_nailbomb_shrap1);
	CVAR_REGISTER(&sk_plr_nailbomb_shrap2);
	CVAR_REGISTER(&sk_plr_nailbomb_shrap3);
	CVAR_REGISTER(&sk_plr_nailbomb_shrap4);
	CVAR_REGISTER(&sk_plr_nailbomb_shrap5);
	CVAR_REGISTER(&sk_plr_nailbomb_shrap6);

	// === 4 - HEAVY WEAPONS === //

	// Grenade Launcher
	CVAR_REGISTER(&sk_plr_50mmg_blast1);
	CVAR_REGISTER(&sk_plr_50mmg_blast2);
	CVAR_REGISTER(&sk_plr_50mmg_blast3);
	CVAR_REGISTER(&sk_plr_50mmg_blast4);
	CVAR_REGISTER(&sk_plr_50mmg_blast5);
	CVAR_REGISTER(&sk_plr_50mmg_blast6);

	CVAR_REGISTER(&sk_plr_50mmg_heat1);
	CVAR_REGISTER(&sk_plr_50mmg_heat2);
	CVAR_REGISTER(&sk_plr_50mmg_heat3);
	CVAR_REGISTER(&sk_plr_50mmg_heat4);
	CVAR_REGISTER(&sk_plr_50mmg_heat5);
	CVAR_REGISTER(&sk_plr_50mmg_heat6);

	CVAR_REGISTER(&sk_plr_50mmg_shrap1);
	CVAR_REGISTER(&sk_plr_50mmg_shrap2);
	CVAR_REGISTER(&sk_plr_50mmg_shrap3);
	CVAR_REGISTER(&sk_plr_50mmg_shrap4);
	CVAR_REGISTER(&sk_plr_50mmg_shrap5);
	CVAR_REGISTER(&sk_plr_50mmg_shrap6);

	// RPG
	CVAR_REGISTER(&sk_plr_rpg_blast1);
	CVAR_REGISTER(&sk_plr_rpg_blast2);
	CVAR_REGISTER(&sk_plr_rpg_blast3);
	CVAR_REGISTER(&sk_plr_rpg_blast4);
	CVAR_REGISTER(&sk_plr_rpg_blast5);
	CVAR_REGISTER(&sk_plr_rpg_blast6);

	CVAR_REGISTER(&sk_plr_rpg_heat1);
	CVAR_REGISTER(&sk_plr_rpg_heat2);
	CVAR_REGISTER(&sk_plr_rpg_heat3);
	CVAR_REGISTER(&sk_plr_rpg_heat4);
	CVAR_REGISTER(&sk_plr_rpg_heat5);
	CVAR_REGISTER(&sk_plr_rpg_heat6);

	CVAR_REGISTER(&sk_plr_rpg_shrap1);
	CVAR_REGISTER(&sk_plr_rpg_shrap2);
	CVAR_REGISTER(&sk_plr_rpg_shrap3);
	CVAR_REGISTER(&sk_plr_rpg_shrap4);
	CVAR_REGISTER(&sk_plr_rpg_shrap5);
	CVAR_REGISTER(&sk_plr_rpg_shrap6);

	// 66mm Rocket (LAW)
	CVAR_REGISTER(&sk_plr_66mm_blast1);
	CVAR_REGISTER(&sk_plr_66mm_blast2);
	CVAR_REGISTER(&sk_plr_66mm_blast3);
	CVAR_REGISTER(&sk_plr_66mm_blast4);
	CVAR_REGISTER(&sk_plr_66mm_blast5);
	CVAR_REGISTER(&sk_plr_66mm_blast6);

	CVAR_REGISTER(&sk_plr_66mm_heat1);
	CVAR_REGISTER(&sk_plr_66mm_heat2);
	CVAR_REGISTER(&sk_plr_66mm_heat3);
	CVAR_REGISTER(&sk_plr_66mm_heat4);
	CVAR_REGISTER(&sk_plr_66mm_heat5);
	CVAR_REGISTER(&sk_plr_66mm_heat6);

	CVAR_REGISTER(&sk_plr_66mm_shrap1);
	CVAR_REGISTER(&sk_plr_66mm_shrap2);
	CVAR_REGISTER(&sk_plr_66mm_shrap3);
	CVAR_REGISTER(&sk_plr_66mm_shrap4);
	CVAR_REGISTER(&sk_plr_66mm_shrap5);
	CVAR_REGISTER(&sk_plr_66mm_shrap6);

	// Rocket Rifle
	CVAR_REGISTER(&sk_plr_50mmr_blast1);
	CVAR_REGISTER(&sk_plr_50mmr_blast2);
	CVAR_REGISTER(&sk_plr_50mmr_blast3);
	CVAR_REGISTER(&sk_plr_50mmr_blast4);
	CVAR_REGISTER(&sk_plr_50mmr_blast5);
	CVAR_REGISTER(&sk_plr_50mmr_blast6);

	CVAR_REGISTER(&sk_plr_50mmr_heat1);
	CVAR_REGISTER(&sk_plr_50mmr_heat2);
	CVAR_REGISTER(&sk_plr_50mmr_heat3);
	CVAR_REGISTER(&sk_plr_50mmr_heat4);
	CVAR_REGISTER(&sk_plr_50mmr_heat5);
	CVAR_REGISTER(&sk_plr_50mmr_heat6);

	CVAR_REGISTER(&sk_plr_50mmr_shrap1);
	CVAR_REGISTER(&sk_plr_50mmr_shrap2);
	CVAR_REGISTER(&sk_plr_50mmr_shrap3);
	CVAR_REGISTER(&sk_plr_50mmr_shrap4);
	CVAR_REGISTER(&sk_plr_50mmr_shrap5);
	CVAR_REGISTER(&sk_plr_50mmr_shrap6);

	// Flamethrower
	CVAR_REGISTER(&sk_plr_flametouch1);
	CVAR_REGISTER(&sk_plr_flametouch2);
	CVAR_REGISTER(&sk_plr_flametouch3);
	CVAR_REGISTER(&sk_plr_flametouch4);
	CVAR_REGISTER(&sk_plr_flametouch5);
	CVAR_REGISTER(&sk_plr_flametouch6);

	CVAR_REGISTER(&sk_plr_flamerad1);
	CVAR_REGISTER(&sk_plr_flamerad2);
	CVAR_REGISTER(&sk_plr_flamerad3);
	CVAR_REGISTER(&sk_plr_flamerad4);
	CVAR_REGISTER(&sk_plr_flamerad5);
	CVAR_REGISTER(&sk_plr_flamerad6);

	CVAR_REGISTER(&sk_plr_nbomb_blast1);
	CVAR_REGISTER(&sk_plr_nbomb_blast2);
	CVAR_REGISTER(&sk_plr_nbomb_blast3);
	CVAR_REGISTER(&sk_plr_nbomb_blast4);
	CVAR_REGISTER(&sk_plr_nbomb_blast5);
	CVAR_REGISTER(&sk_plr_nbomb_blast6);

	CVAR_REGISTER(&sk_plr_nbomb_heat1);
	CVAR_REGISTER(&sk_plr_nbomb_heat2);
	CVAR_REGISTER(&sk_plr_nbomb_heat3);
	CVAR_REGISTER(&sk_plr_nbomb_heat4);
	CVAR_REGISTER(&sk_plr_nbomb_heat5);
	CVAR_REGISTER(&sk_plr_nbomb_heat6);

	CVAR_REGISTER(&sk_plr_nbomb_shrap1);
	CVAR_REGISTER(&sk_plr_nbomb_shrap2);
	CVAR_REGISTER(&sk_plr_nbomb_shrap3);
	CVAR_REGISTER(&sk_plr_nbomb_shrap4);
	CVAR_REGISTER(&sk_plr_nbomb_shrap5);
	CVAR_REGISTER(&sk_plr_nbomb_shrap6);

	// Heavy 5.56 Round (M249)
	CVAR_REGISTER(&sk_plr_556natoh1);
	CVAR_REGISTER(&sk_plr_556natoh2);
	CVAR_REGISTER(&sk_plr_556natoh3);
	CVAR_REGISTER(&sk_plr_556natoh4);
	CVAR_REGISTER(&sk_plr_556natoh5);
	CVAR_REGISTER(&sk_plr_556natoh6);

	// Heavy 7.62 Round (M60)
	CVAR_REGISTER(&sk_plr_762natoh1);
	CVAR_REGISTER(&sk_plr_762natoh2);
	CVAR_REGISTER(&sk_plr_762natoh3);
	CVAR_REGISTER(&sk_plr_762natoh4);
	CVAR_REGISTER(&sk_plr_762natoh5);
	CVAR_REGISTER(&sk_plr_762natoh6);

	// 10mm Round (Chaingun)
	CVAR_REGISTER(&sk_plr_10mm1);
	CVAR_REGISTER(&sk_plr_10mm2);
	CVAR_REGISTER(&sk_plr_10mm3);
	CVAR_REGISTER(&sk_plr_10mm4);
	CVAR_REGISTER(&sk_plr_10mm5);
	CVAR_REGISTER(&sk_plr_10mm6);

	// 12.7mm Round (Minigun)
	CVAR_REGISTER(&sk_plr_127mm1);
	CVAR_REGISTER(&sk_plr_127mm2);
	CVAR_REGISTER(&sk_plr_127mm3);
	CVAR_REGISTER(&sk_plr_127mm4);
	CVAR_REGISTER(&sk_plr_127mm5);
	CVAR_REGISTER(&sk_plr_127mm6);

	// === 5 - RANGED WEAPONS === //

	// Autocrossbow
	CVAR_REGISTER(&sk_plr_bolt1);
	CVAR_REGISTER(&sk_plr_bolt2);
	CVAR_REGISTER(&sk_plr_bolt3);
	CVAR_REGISTER(&sk_plr_bolt4);
	CVAR_REGISTER(&sk_plr_bolt5);
	CVAR_REGISTER(&sk_plr_bolt6);

	CVAR_REGISTER(&sk_plr_bolt_toxin1);
	CVAR_REGISTER(&sk_plr_bolt_toxin2);
	CVAR_REGISTER(&sk_plr_bolt_toxin3);
	CVAR_REGISTER(&sk_plr_bolt_toxin4);
	CVAR_REGISTER(&sk_plr_bolt_toxin5);
	CVAR_REGISTER(&sk_plr_bolt_toxin6);

	// Torque Crossbow
	CVAR_REGISTER(&sk_plr_tbolt1);
	CVAR_REGISTER(&sk_plr_tbolt2);
	CVAR_REGISTER(&sk_plr_tbolt3);
	CVAR_REGISTER(&sk_plr_tbolt4);
	CVAR_REGISTER(&sk_plr_tbolt5);
	CVAR_REGISTER(&sk_plr_tbolt6);

	CVAR_REGISTER(&sk_plr_tbolt_blast1);
	CVAR_REGISTER(&sk_plr_tbolt_blast2);
	CVAR_REGISTER(&sk_plr_tbolt_blast3);
	CVAR_REGISTER(&sk_plr_tbolt_blast4);
	CVAR_REGISTER(&sk_plr_tbolt_blast5);
	CVAR_REGISTER(&sk_plr_tbolt_blast6);

	CVAR_REGISTER(&sk_plr_tbolt_heat1);
	CVAR_REGISTER(&sk_plr_tbolt_heat2);
	CVAR_REGISTER(&sk_plr_tbolt_heat3);
	CVAR_REGISTER(&sk_plr_tbolt_heat4);
	CVAR_REGISTER(&sk_plr_tbolt_heat5);
	CVAR_REGISTER(&sk_plr_tbolt_heat6);

	CVAR_REGISTER(&sk_plr_tbolt_shrap1);
	CVAR_REGISTER(&sk_plr_tbolt_shrap2);
	CVAR_REGISTER(&sk_plr_tbolt_shrap3);
	CVAR_REGISTER(&sk_plr_tbolt_shrap4);
	CVAR_REGISTER(&sk_plr_tbolt_shrap5);
	CVAR_REGISTER(&sk_plr_tbolt_shrap6);

	// 7.62 NATO (M40A1 Sniper Rifle)
	CVAR_REGISTER(&sk_plr_762nato1);
	CVAR_REGISTER(&sk_plr_762nato2);
	CVAR_REGISTER(&sk_plr_762nato3);
	CVAR_REGISTER(&sk_plr_762nato4);
	CVAR_REGISTER(&sk_plr_762nato5);
	CVAR_REGISTER(&sk_plr_762nato6);

	// Autosniper
	CVAR_REGISTER(&sk_plr_3081);
	CVAR_REGISTER(&sk_plr_3082);
	CVAR_REGISTER(&sk_plr_3083);
	CVAR_REGISTER(&sk_plr_3084);
	CVAR_REGISTER(&sk_plr_3085);
	CVAR_REGISTER(&sk_plr_3086);

	CVAR_REGISTER(&sk_plr_3381);
	CVAR_REGISTER(&sk_plr_3382);
	CVAR_REGISTER(&sk_plr_3383);
	CVAR_REGISTER(&sk_plr_3384);
	CVAR_REGISTER(&sk_plr_3385);
	CVAR_REGISTER(&sk_plr_3386);

	// === 6 - ENERGY WEAPONS === //

	// Railgun
	CVAR_REGISTER(&sk_plr_railbolt1);
	CVAR_REGISTER(&sk_plr_railbolt2);
	CVAR_REGISTER(&sk_plr_railbolt3);
	CVAR_REGISTER(&sk_plr_railbolt4);
	CVAR_REGISTER(&sk_plr_railbolt5);
	CVAR_REGISTER(&sk_plr_railbolt6);

	CVAR_REGISTER(&sk_plr_railbolt_radius1);
	CVAR_REGISTER(&sk_plr_railbolt_radius2);
	CVAR_REGISTER(&sk_plr_railbolt_radius3);
	CVAR_REGISTER(&sk_plr_railbolt_radius4);
	CVAR_REGISTER(&sk_plr_railbolt_radius5);
	CVAR_REGISTER(&sk_plr_railbolt_radius6);

	// Plasma Gun
	CVAR_REGISTER(&sk_plr_plasma1);
	CVAR_REGISTER(&sk_plr_plasma2);
	CVAR_REGISTER(&sk_plr_plasma3);
	CVAR_REGISTER(&sk_plr_plasma4);
	CVAR_REGISTER(&sk_plr_plasma5);
	CVAR_REGISTER(&sk_plr_plasma6);

	CVAR_REGISTER(&sk_plr_plasma_spray1);
	CVAR_REGISTER(&sk_plr_plasma_spray2);
	CVAR_REGISTER(&sk_plr_plasma_spray3);
	CVAR_REGISTER(&sk_plr_plasma_spray4);
	CVAR_REGISTER(&sk_plr_plasma_spray5);
	CVAR_REGISTER(&sk_plr_plasma_spray6);

	CVAR_REGISTER(&sk_plr_plasma_blast1);
	CVAR_REGISTER(&sk_plr_plasma_blast2);
	CVAR_REGISTER(&sk_plr_plasma_blast3);
	CVAR_REGISTER(&sk_plr_plasma_blast4);
	CVAR_REGISTER(&sk_plr_plasma_blast5);
	CVAR_REGISTER(&sk_plr_plasma_blast6);

	// Gauss Gun
	CVAR_REGISTER(&sk_plr_gauss_laser1);
	CVAR_REGISTER(&sk_plr_gauss_laser2);
	CVAR_REGISTER(&sk_plr_gauss_laser3);
	CVAR_REGISTER(&sk_plr_gauss_laser4);
	CVAR_REGISTER(&sk_plr_gauss_laser5);
	CVAR_REGISTER(&sk_plr_gauss_laser6);

	CVAR_REGISTER(&sk_plr_gauss_rail1);
	CVAR_REGISTER(&sk_plr_gauss_rail2);
	CVAR_REGISTER(&sk_plr_gauss_rail3);
	CVAR_REGISTER(&sk_plr_gauss_rail4);
	CVAR_REGISTER(&sk_plr_gauss_rail5);
	CVAR_REGISTER(&sk_plr_gauss_rail6);

	// Egon Gun
	CVAR_REGISTER(&sk_plr_egon_narrow1);
	CVAR_REGISTER(&sk_plr_egon_narrow2);
	CVAR_REGISTER(&sk_plr_egon_narrow3);
	CVAR_REGISTER(&sk_plr_egon_narrow4);
	CVAR_REGISTER(&sk_plr_egon_narrow5);
	CVAR_REGISTER(&sk_plr_egon_narrow6);

	CVAR_REGISTER(&sk_plr_egon_wide1);
	CVAR_REGISTER(&sk_plr_egon_wide2);
	CVAR_REGISTER(&sk_plr_egon_wide3);
	CVAR_REGISTER(&sk_plr_egon_wide4);
	CVAR_REGISTER(&sk_plr_egon_wide5);
	CVAR_REGISTER(&sk_plr_egon_wide6);

	CVAR_REGISTER(&sk_plr_egon_wide_rad1);
	CVAR_REGISTER(&sk_plr_egon_wide_rad2);
	CVAR_REGISTER(&sk_plr_egon_wide_rad3);
	CVAR_REGISTER(&sk_plr_egon_wide_rad4);
	CVAR_REGISTER(&sk_plr_egon_wide_rad5);
	CVAR_REGISTER(&sk_plr_egon_wide_rad6);

	CVAR_REGISTER(&sk_plr_egon_blast1);
	CVAR_REGISTER(&sk_plr_egon_blast2);
	CVAR_REGISTER(&sk_plr_egon_blast3);
	CVAR_REGISTER(&sk_plr_egon_blast4);
	CVAR_REGISTER(&sk_plr_egon_blast5);
	CVAR_REGISTER(&sk_plr_egon_blast6);

	// Displacer Gun/Cannon
	CVAR_REGISTER(&sk_plr_disp_blast1);
	CVAR_REGISTER(&sk_plr_disp_blast2);
	CVAR_REGISTER(&sk_plr_disp_blast3);
	CVAR_REGISTER(&sk_plr_disp_blast4);
	CVAR_REGISTER(&sk_plr_disp_blast5);
	CVAR_REGISTER(&sk_plr_disp_blast6);

	CVAR_REGISTER(&sk_plr_disp_arc1);
	CVAR_REGISTER(&sk_plr_disp_arc2);
	CVAR_REGISTER(&sk_plr_disp_arc3);
	CVAR_REGISTER(&sk_plr_disp_arc4);
	CVAR_REGISTER(&sk_plr_disp_arc5);
	CVAR_REGISTER(&sk_plr_disp_arc6);

	CVAR_REGISTER(&sk_plr_disp_dir1);
	CVAR_REGISTER(&sk_plr_disp_dir2);
	CVAR_REGISTER(&sk_plr_disp_dir3);
	CVAR_REGISTER(&sk_plr_disp_dir4);
	CVAR_REGISTER(&sk_plr_disp_dir5);
	CVAR_REGISTER(&sk_plr_disp_dir6);

	// === 7 - THROWABLE AND TRAPS === //

	// High-Explosive Grenade
	CVAR_REGISTER(&sk_plr_he_blast1);
	CVAR_REGISTER(&sk_plr_he_blast2);
	CVAR_REGISTER(&sk_plr_he_blast3);
	CVAR_REGISTER(&sk_plr_he_blast4);
	CVAR_REGISTER(&sk_plr_he_blast5);
	CVAR_REGISTER(&sk_plr_he_blast6);

	CVAR_REGISTER(&sk_plr_he_heat1);
	CVAR_REGISTER(&sk_plr_he_heat2);
	CVAR_REGISTER(&sk_plr_he_heat3);
	CVAR_REGISTER(&sk_plr_he_heat4);
	CVAR_REGISTER(&sk_plr_he_heat5);
	CVAR_REGISTER(&sk_plr_he_heat6);

	CVAR_REGISTER(&sk_plr_he_shrap1);
	CVAR_REGISTER(&sk_plr_he_shrap2);
	CVAR_REGISTER(&sk_plr_he_shrap3);
	CVAR_REGISTER(&sk_plr_he_shrap4);
	CVAR_REGISTER(&sk_plr_he_shrap5);
	CVAR_REGISTER(&sk_plr_he_shrap6);

	CVAR_REGISTER(&sk_plr_he_smack1);
	CVAR_REGISTER(&sk_plr_he_smack2);
	CVAR_REGISTER(&sk_plr_he_smack3);
	CVAR_REGISTER(&sk_plr_he_smack4);
	CVAR_REGISTER(&sk_plr_he_smack5);
	CVAR_REGISTER(&sk_plr_he_smack6);

	// Fragmentation Grenade
	CVAR_REGISTER(&sk_plr_frag_blast1);
	CVAR_REGISTER(&sk_plr_frag_blast2);
	CVAR_REGISTER(&sk_plr_frag_blast3);
	CVAR_REGISTER(&sk_plr_frag_blast4);
	CVAR_REGISTER(&sk_plr_frag_blast5);
	CVAR_REGISTER(&sk_plr_frag_blast6);

	CVAR_REGISTER(&sk_plr_frag_heat1);
	CVAR_REGISTER(&sk_plr_frag_heat2);
	CVAR_REGISTER(&sk_plr_frag_heat3);
	CVAR_REGISTER(&sk_plr_frag_heat4);
	CVAR_REGISTER(&sk_plr_frag_heat5);
	CVAR_REGISTER(&sk_plr_frag_heat6);

	CVAR_REGISTER(&sk_plr_frag_shrap1);
	CVAR_REGISTER(&sk_plr_frag_shrap2);
	CVAR_REGISTER(&sk_plr_frag_shrap3);
	CVAR_REGISTER(&sk_plr_frag_shrap4);
	CVAR_REGISTER(&sk_plr_frag_shrap5);
	CVAR_REGISTER(&sk_plr_frag_shrap6);

	CVAR_REGISTER(&sk_plr_frag_smack1);
	CVAR_REGISTER(&sk_plr_frag_smack2);
	CVAR_REGISTER(&sk_plr_frag_smack3);
	CVAR_REGISTER(&sk_plr_frag_smack4);
	CVAR_REGISTER(&sk_plr_frag_smack5);
	CVAR_REGISTER(&sk_plr_frag_smack6);

	// Satchel Charge
	CVAR_REGISTER(&sk_plr_satchel_blast1);
	CVAR_REGISTER(&sk_plr_satchel_blast2);
	CVAR_REGISTER(&sk_plr_satchel_blast3);
	CVAR_REGISTER(&sk_plr_satchel_blast4);
	CVAR_REGISTER(&sk_plr_satchel_blast5);
	CVAR_REGISTER(&sk_plr_satchel_blast6);

	CVAR_REGISTER(&sk_plr_satchel_heat1);
	CVAR_REGISTER(&sk_plr_satchel_heat2);
	CVAR_REGISTER(&sk_plr_satchel_heat3);
	CVAR_REGISTER(&sk_plr_satchel_heat4);
	CVAR_REGISTER(&sk_plr_satchel_heat5);
	CVAR_REGISTER(&sk_plr_satchel_heat6);

	CVAR_REGISTER(&sk_plr_satchel_shrap1);
	CVAR_REGISTER(&sk_plr_satchel_shrap2);
	CVAR_REGISTER(&sk_plr_satchel_shrap3);
	CVAR_REGISTER(&sk_plr_satchel_shrap4);
	CVAR_REGISTER(&sk_plr_satchel_shrap5);
	CVAR_REGISTER(&sk_plr_satchel_shrap6);

	// Tripmine
	CVAR_REGISTER(&sk_plr_tripmine_blast1);
	CVAR_REGISTER(&sk_plr_tripmine_blast2);
	CVAR_REGISTER(&sk_plr_tripmine_blast3);
	CVAR_REGISTER(&sk_plr_tripmine_blast4);
	CVAR_REGISTER(&sk_plr_tripmine_blast5);
	CVAR_REGISTER(&sk_plr_tripmine_blast6);

	CVAR_REGISTER(&sk_plr_tripmine_heat1);
	CVAR_REGISTER(&sk_plr_tripmine_heat2);
	CVAR_REGISTER(&sk_plr_tripmine_heat3);
	CVAR_REGISTER(&sk_plr_tripmine_heat4);
	CVAR_REGISTER(&sk_plr_tripmine_heat5);
	CVAR_REGISTER(&sk_plr_tripmine_heat6);

	CVAR_REGISTER(&sk_plr_tripmine_shrap1);
	CVAR_REGISTER(&sk_plr_tripmine_shrap2);
	CVAR_REGISTER(&sk_plr_tripmine_shrap3);
	CVAR_REGISTER(&sk_plr_tripmine_shrap4);
	CVAR_REGISTER(&sk_plr_tripmine_shrap5);
	CVAR_REGISTER(&sk_plr_tripmine_shrap6);

	// === 8 - ALIEN WEAPONS === //

	// Hivehand
	CVAR_REGISTER(&sk_plr_hornet1);
	CVAR_REGISTER(&sk_plr_hornet2);
	CVAR_REGISTER(&sk_plr_hornet3);
	CVAR_REGISTER(&sk_plr_hornet4);
	CVAR_REGISTER(&sk_plr_hornet5);
	CVAR_REGISTER(&sk_plr_hornet6);

	CVAR_REGISTER(&sk_hornet_health1);
	CVAR_REGISTER(&sk_hornet_health2);
	CVAR_REGISTER(&sk_hornet_health3);
	CVAR_REGISTER(&sk_hornet_health4);
	CVAR_REGISTER(&sk_hornet_health5);
	CVAR_REGISTER(&sk_hornet_health6);

	CVAR_REGISTER(&sk_plr_phero_missile1);
	CVAR_REGISTER(&sk_plr_phero_missile2);
	CVAR_REGISTER(&sk_plr_phero_missile3);
	CVAR_REGISTER(&sk_plr_phero_missile4);
	CVAR_REGISTER(&sk_plr_phero_missile5);
	CVAR_REGISTER(&sk_plr_phero_missile6);

	CVAR_REGISTER(&sk_plr_black_hole1);
	CVAR_REGISTER(&sk_plr_black_hole2);
	CVAR_REGISTER(&sk_plr_black_hole3);
	CVAR_REGISTER(&sk_plr_black_hole4);
	CVAR_REGISTER(&sk_plr_black_hole5);
	CVAR_REGISTER(&sk_plr_black_hole6);

	CVAR_REGISTER(&sk_plr_chainsaw1);
	CVAR_REGISTER(&sk_plr_chainsaw2);
	CVAR_REGISTER(&sk_plr_chainsaw3);
	CVAR_REGISTER(&sk_plr_chainsaw4);
	CVAR_REGISTER(&sk_plr_chainsaw5);
	CVAR_REGISTER(&sk_plr_chainsaw6);

	// Snark
	CVAR_REGISTER(&sk_plr_snark_bite1);
	CVAR_REGISTER(&sk_plr_snark_bite2);
	CVAR_REGISTER(&sk_plr_snark_bite3);
	CVAR_REGISTER(&sk_plr_snark_bite4);
	CVAR_REGISTER(&sk_plr_snark_bite5);
	CVAR_REGISTER(&sk_plr_snark_bite6);

	CVAR_REGISTER(&sk_plr_snark_pop1);
	CVAR_REGISTER(&sk_plr_snark_pop2);
	CVAR_REGISTER(&sk_plr_snark_pop3);
	CVAR_REGISTER(&sk_plr_snark_pop4);
	CVAR_REGISTER(&sk_plr_snark_pop5);
	CVAR_REGISTER(&sk_plr_snark_pop6);

	// Snark
	CVAR_REGISTER(&sk_snark_health1);
	CVAR_REGISTER(&sk_snark_health2);
	CVAR_REGISTER(&sk_snark_health3);
	CVAR_REGISTER(&sk_snark_health4);
	CVAR_REGISTER(&sk_snark_health5);
	CVAR_REGISTER(&sk_snark_health6);

	CVAR_REGISTER(&sk_snark_dmg_bite1);
	CVAR_REGISTER(&sk_snark_dmg_bite2);
	CVAR_REGISTER(&sk_snark_dmg_bite3);
	CVAR_REGISTER(&sk_snark_dmg_bite4);
	CVAR_REGISTER(&sk_snark_dmg_bite5);
	CVAR_REGISTER(&sk_snark_dmg_bite6);

	CVAR_REGISTER(&sk_snark_dmg_pop1);
	CVAR_REGISTER(&sk_snark_dmg_pop2);
	CVAR_REGISTER(&sk_snark_dmg_pop3);
	CVAR_REGISTER(&sk_snark_dmg_pop4);
	CVAR_REGISTER(&sk_snark_dmg_pop5);
	CVAR_REGISTER(&sk_snark_dmg_pop6);

	// Spore Launcher
	CVAR_REGISTER(&sk_plr_spore_radius1);
	CVAR_REGISTER(&sk_plr_spore_radius2);
	CVAR_REGISTER(&sk_plr_spore_radius3);
	CVAR_REGISTER(&sk_plr_spore_radius4);
	CVAR_REGISTER(&sk_plr_spore_radius5);
	CVAR_REGISTER(&sk_plr_spore_radius6);

	CVAR_REGISTER(&sk_plr_spore_direct1);
	CVAR_REGISTER(&sk_plr_spore_direct2);
	CVAR_REGISTER(&sk_plr_spore_direct3);
	CVAR_REGISTER(&sk_plr_spore_direct4);
	CVAR_REGISTER(&sk_plr_spore_direct5);
	CVAR_REGISTER(&sk_plr_spore_direct6);

	CVAR_REGISTER(&sk_plr_spore_bite1);
	CVAR_REGISTER(&sk_plr_spore_bite2);
	CVAR_REGISTER(&sk_plr_spore_bite3);
	CVAR_REGISTER(&sk_plr_spore_bite4);
	CVAR_REGISTER(&sk_plr_spore_bite5);
	CVAR_REGISTER(&sk_plr_spore_bite6);

	// Shock Roach
	CVAR_REGISTER(&sk_plr_shockbolt1);
	CVAR_REGISTER(&sk_plr_shockbolt2);
	CVAR_REGISTER(&sk_plr_shockbolt3);
	CVAR_REGISTER(&sk_plr_shockbolt4);
	CVAR_REGISTER(&sk_plr_shockbolt5);
	CVAR_REGISTER(&sk_plr_shockbolt6);

	CVAR_REGISTER(&sk_plr_shocktase1);
	CVAR_REGISTER(&sk_plr_shocktase2);
	CVAR_REGISTER(&sk_plr_shocktase3);
	CVAR_REGISTER(&sk_plr_shocktase4);
	CVAR_REGISTER(&sk_plr_shocktase5);
	CVAR_REGISTER(&sk_plr_shocktase6);

	CVAR_REGISTER(&sk_plr_shockbite1);
	CVAR_REGISTER(&sk_plr_shockbite2);
	CVAR_REGISTER(&sk_plr_shockbite3);
	CVAR_REGISTER(&sk_plr_shockbite4);
	CVAR_REGISTER(&sk_plr_shockbite5);
	CVAR_REGISTER(&sk_plr_shockbite6);

	// Barnacle
	CVAR_REGISTER(&sk_barnacle_health1);
	CVAR_REGISTER(&sk_barnacle_health2);
	CVAR_REGISTER(&sk_barnacle_health3);
	CVAR_REGISTER(&sk_barnacle_health4);
	CVAR_REGISTER(&sk_barnacle_health5);
	CVAR_REGISTER(&sk_barnacle_health6);

	CVAR_REGISTER(&sk_plr_barnacle_bite1);
	CVAR_REGISTER(&sk_plr_barnacle_bite2);
	CVAR_REGISTER(&sk_plr_barnacle_bite3);
	CVAR_REGISTER(&sk_plr_barnacle_bite4);
	CVAR_REGISTER(&sk_plr_barnacle_bite5);
	CVAR_REGISTER(&sk_plr_barnacle_bite6);

	// Chumtoad
	//? ? ?

	// === 9 - SUPPORT WEAPONS === //

	// Automatic Medkit
	CVAR_REGISTER(&sk_plr_medkit_heal1);
	CVAR_REGISTER(&sk_plr_medkit_heal2);
	CVAR_REGISTER(&sk_plr_medkit_heal3);
	CVAR_REGISTER(&sk_plr_medkit_heal4);
	CVAR_REGISTER(&sk_plr_medkit_heal5);
	CVAR_REGISTER(&sk_plr_medkit_heal6);

	CVAR_REGISTER(&sk_plr_medkit_poison1);
	CVAR_REGISTER(&sk_plr_medkit_poison2);
	CVAR_REGISTER(&sk_plr_medkit_poison3);
	CVAR_REGISTER(&sk_plr_medkit_poison4);
	CVAR_REGISTER(&sk_plr_medkit_poison5);
	CVAR_REGISTER(&sk_plr_medkit_poison6);

	// EMP Tool
	//? ? ?

	// Syringe
	//? ? ?

	// Flare
	CVAR_REGISTER(&sk_plr_flare_burn1);
	CVAR_REGISTER(&sk_plr_flare_burn2);
	CVAR_REGISTER(&sk_plr_flare_burn3);
	CVAR_REGISTER(&sk_plr_flare_burn4);
	CVAR_REGISTER(&sk_plr_flare_burn5);
	CVAR_REGISTER(&sk_plr_flare_burn6);

	CVAR_REGISTER(&sk_plr_flare_hit1);
	CVAR_REGISTER(&sk_plr_flare_hit2);
	CVAR_REGISTER(&sk_plr_flare_hit3);
	CVAR_REGISTER(&sk_plr_flare_hit4);
	CVAR_REGISTER(&sk_plr_flare_hit5);
	CVAR_REGISTER(&sk_plr_flare_hit6);

	CVAR_REGISTER(&sk_plr_flare_blast1);
	CVAR_REGISTER(&sk_plr_flare_blast2);
	CVAR_REGISTER(&sk_plr_flare_blast3);
	CVAR_REGISTER(&sk_plr_flare_blast4);
	CVAR_REGISTER(&sk_plr_flare_blast5);
	CVAR_REGISTER(&sk_plr_flare_blast6);

	CVAR_REGISTER(&sk_plr_flare_heat1);
	CVAR_REGISTER(&sk_plr_flare_heat2);
	CVAR_REGISTER(&sk_plr_flare_heat3);
	CVAR_REGISTER(&sk_plr_flare_heat4);
	CVAR_REGISTER(&sk_plr_flare_heat5);
	CVAR_REGISTER(&sk_plr_flare_heat6);

	CVAR_REGISTER(&sk_plr_flare_shrap1);
	CVAR_REGISTER(&sk_plr_flare_shrap2);
	CVAR_REGISTER(&sk_plr_flare_shrap3);
	CVAR_REGISTER(&sk_plr_flare_shrap4);
	CVAR_REGISTER(&sk_plr_flare_shrap5);
	CVAR_REGISTER(&sk_plr_flare_shrap6);

	// HEALTH/SUIT CHARGE DISTRIBUTION
	CVAR_REGISTER(&sk_charger1);
	CVAR_REGISTER(&sk_charger2);
	CVAR_REGISTER(&sk_charger3);
	CVAR_REGISTER(&sk_charger4);
	CVAR_REGISTER(&sk_charger5);
	CVAR_REGISTER(&sk_charger6);

	CVAR_REGISTER(&sk_battery1);
	CVAR_REGISTER(&sk_battery2);
	CVAR_REGISTER(&sk_battery3);
	CVAR_REGISTER(&sk_battery4);
	CVAR_REGISTER(&sk_battery5);
	CVAR_REGISTER(&sk_battery6);

	CVAR_REGISTER(&sk_healthkit1);
	CVAR_REGISTER(&sk_healthkit2);
	CVAR_REGISTER(&sk_healthkit3);
	CVAR_REGISTER(&sk_healthkit4);
	CVAR_REGISTER(&sk_healthkit5);
	CVAR_REGISTER(&sk_healthkit6);

	// damage adjusters
	CVAR_REGISTER(&sk_dmgadjust_head1);
	CVAR_REGISTER(&sk_dmgadjust_head2);
	CVAR_REGISTER(&sk_dmgadjust_head3);
	CVAR_REGISTER(&sk_dmgadjust_head4);
	CVAR_REGISTER(&sk_dmgadjust_head5);
	CVAR_REGISTER(&sk_dmgadjust_head6);

	CVAR_REGISTER(&sk_dmgadjust_chest1);
	CVAR_REGISTER(&sk_dmgadjust_chest2);
	CVAR_REGISTER(&sk_dmgadjust_chest3);
	CVAR_REGISTER(&sk_dmgadjust_chest4);
	CVAR_REGISTER(&sk_dmgadjust_chest5);
	CVAR_REGISTER(&sk_dmgadjust_chest6);

	CVAR_REGISTER(&sk_dmgadjust_stomach1);
	CVAR_REGISTER(&sk_dmgadjust_stomach2);
	CVAR_REGISTER(&sk_dmgadjust_stomach3);
	CVAR_REGISTER(&sk_dmgadjust_stomach4);
	CVAR_REGISTER(&sk_dmgadjust_stomach5);
	CVAR_REGISTER(&sk_dmgadjust_stomach6);

	CVAR_REGISTER(&sk_dmgadjust_arm1);
	CVAR_REGISTER(&sk_dmgadjust_arm2);
	CVAR_REGISTER(&sk_dmgadjust_arm3);
	CVAR_REGISTER(&sk_dmgadjust_arm4);
	CVAR_REGISTER(&sk_dmgadjust_arm5);
	CVAR_REGISTER(&sk_dmgadjust_arm6);

	CVAR_REGISTER(&sk_dmgadjust_leg1);
	CVAR_REGISTER(&sk_dmgadjust_leg2);
	CVAR_REGISTER(&sk_dmgadjust_leg3);
	CVAR_REGISTER(&sk_dmgadjust_leg4);
	CVAR_REGISTER(&sk_dmgadjust_leg5);
	CVAR_REGISTER(&sk_dmgadjust_leg6);

	// END: REGISTER CVARS FOR SKILL LEVEL STUFF

	SERVER_COMMAND( "exec skill.cfg\n" );
}

