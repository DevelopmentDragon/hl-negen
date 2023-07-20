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
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"

#include "usercmd.h"
#include "entity_state.h"
#include "demo_api.h"
#include "pm_defs.h"
#include "event_api.h"
#include "r_efx.h"

#include "../hud_iface.h"
#include "../com_weapons.h"
#include "../demo.h"

extern globalvars_t *gpGlobals;
extern int g_iUser1;

// Pool of client side entities/entvars_t
static entvars_t	ev[ 32 ];
static int			num_ents = 0;

// The entity we'll use to represent the local client
static CBasePlayer	player;

// Local version of game .dll global variables ( time, etc. )
static globalvars_t	Globals; 

static CBasePlayerWeapon *g_pWpns[ MAX_WEAPONS ];

float g_flApplyVel = 0.0;
int   g_irunninggausspred = 0;

vec3_t previousorigin;

// HLDM Weapon placeholder entities.
//CCrowbar g_Crowbar;
//CGlock g_Glock;
CMP5 g_Mp5;
//CPython g_Python;
//CCrossbow g_Crossbow;
//CShotgun g_Shotgun;
//CRpg g_Rpg;
//CGauss g_Gauss;
//CEgon g_Egon;
//CHgun g_HGun;
//CHandGrenade g_HandGren;
//CSatchel g_Satchel;
//CTripmine g_Tripmine;
//CSqueak g_Snark;


/*
======================
AlertMessage

Print debug messages to console
======================
*/
void AlertMessage( ALERT_TYPE atype, char *szFmt, ... )
{
	va_list		argptr;
	static char	string[1024];
	
	va_start (argptr, szFmt);
	vsprintf (string, szFmt,argptr);
	va_end (argptr);

	gEngfuncs.Con_Printf( "cl:  " );
	gEngfuncs.Con_Printf( string );
}

//Returns if it's multiplayer.
//Mostly used by the client side weapons.
bool bIsMultiplayer ( void )
{
	return gEngfuncs.GetMaxClients() == 1 ? 0 : 1;
}
//Just loads a v_ model.
void LoadVModel ( char *szViewModel, CBasePlayer *m_pPlayer )
{
	gEngfuncs.CL_LoadModel( szViewModel, &m_pPlayer->pev->viewmodel );
}

void LoadArmModel(char* szArmModel, CBasePlayer* m_pPlayer)
{
	gEngfuncs.CL_LoadModel(szArmModel, &m_pPlayer->pev->armmodel);
}


/*
=====================
HUD_PrepEntity

Links the raw entity to an entvars_s holder.  If a player is passed in as the owner, then
we set up the m_pPlayer field.
=====================
*/
void HUD_PrepEntity( CBaseEntity *pEntity, CBasePlayer *pWeaponOwner )
{
	memset( &ev[ num_ents ], 0, sizeof( entvars_t ) );
	pEntity->pev = &ev[ num_ents++ ];

	pEntity->Precache();
	pEntity->Spawn();

	if ( pWeaponOwner )
	{
		ItemInfo info;
		
		((CBasePlayerWeapon *)pEntity)->m_pPlayer = pWeaponOwner;
		
		((CBasePlayerWeapon *)pEntity)->GetItemInfo( &info );

		g_pWpns[ info.iId ] = (CBasePlayerWeapon *)pEntity;
	}
}

/*
=====================
CBaseEntity :: Killed

If weapons code "kills" an entity, just set its effects to EF_NODRAW
=====================
*/
void CBaseEntity :: Killed( entvars_t *pevAttacker, int iGib )
{
	pev->effects |= EF_NODRAW;
}

/*
=====================
CBasePlayerItem :: IncrementClip

Increment the amount of ammo in the clip
=====================
*/
void CBasePlayerItem::IncrementClip(int iClipIndex, int iAmount)
{
	if (GetClip(iClipIndex) + iAmount <= GetMaxClip(iClipIndex))
		SetClip(iClipIndex, GetClip(iClipIndex) + iAmount);
}

/*
=====================
CBasePlayerItem :: DecrementClip

Decrement the amount of ammo in the clip
=====================
*/
void CBasePlayerItem :: DecrementClip(int iClipIndex, int iAmount)
{
	if (GetClip(iClipIndex) - iAmount > -1)
		SetClip(iClipIndex, GetClip(iClipIndex) - iAmount);
}

/*
=====================
CBasePlayerWeapon :: CanDeploy
=====================
*/
BOOL CBasePlayerWeapon :: CanDeploy( void ) 
{
	return (BOOL)(!UsesAmmo() || HasAmmo(AMMO_CHECK_DEFAULT_PARAMS));
}

/*
=====================
CBasePlayerWeapon :: DefaultDeploy

=====================
*/
BOOL CBasePlayerWeapon :: DefaultDeploy( char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal, int	body )
{
	if ( !CanDeploy() )
		return FALSE;

	gEngfuncs.CL_LoadModel( szViewModel, &m_pPlayer->pev->viewmodel );
	
	SendWeaponAnim( iAnim, 1.0f, (byte)0, skiplocal );

	g_irunninggausspred = false;
	m_pPlayer->m_flNextAttack = 0.5;
	m_flNextWeaponIdle = 1.0;
	return TRUE;
}

// Default clip in for most weapons
void CBasePlayerWeapon::DefaultReloadClipIn(int iClipIndex)
{

}

// Default function for putting ammo into the clip
void CBasePlayerWeapon::DefaultReloadClipOut(int iClipIndex)
{

}

/*
=====================
CBasePlayerWeapon :: PlayEmptySound

=====================
*/
BOOL CBasePlayerWeapon :: PlayEmptySound( void )
{
	if (m_iPlayEmptySound)
	{
		HUD_PlaySound( "weapons/357_cock1.wav", 0.8 );
		m_iPlayEmptySound = 0;
		return 0;
	}
	return 0;
}

/*
=====================
CBasePlayerWeapon :: ResetEmptySound

=====================
*/
void CBasePlayerWeapon :: ResetEmptySound( void )
{
	m_iPlayEmptySound = 1;
}

/*
=====================
CBasePlayerWeapon::Holster

Put away weapon
=====================
*/
void CBasePlayerWeapon::Holster( int skiplocal /* = 0 */ )
{ 
	UnsetReload(); // cancel any reload in progress.
	g_irunninggausspred = false;
	m_pPlayer->pev->viewmodel = 0; 
}

/*
=====================
CBasePlayerWeapon::SendWeaponAnim

Animate weapon model
=====================
*/
void CBasePlayerWeapon::SendWeaponAnim(int iAnim, float flFramerate, byte byFrame, int skiplocal)
{
	m_pPlayer->pev->weaponanim = iAnim;
	m_pPlayer->pev->savedvanim = iAnim;
	m_pPlayer->pev->savedvframerate = flFramerate;
	m_pPlayer->pev->savedvframe = byFrame;
	
	HUD_SendWeaponAnim( iAnim, flFramerate, byFrame, skiplocal );
}

/*
=====================
CBaseEntity::FireBullets

Only produces random numbers to match the server ones.
=====================
*/
Vector CBaseEntity::FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq, int iDamage, entvars_t* pevAttacker, int shared_rand)
{
	float x, y, z;

	for (ULONG iShot = 1; iShot <= cShots; iShot++)
	{
		if (pevAttacker == NULL)
		{
			// get circular gaussian spread
			do {
				x = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
				y = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
				z = x * x + y * y;
			} while (z > 1);
		}
		else
		{
			//Use player's random seed.
			// get circular gaussian spread
			x = UTIL_SharedRandomFloat(shared_rand + iShot, -0.5, 0.5) + UTIL_SharedRandomFloat(shared_rand + (1 + iShot), -0.5, 0.5);
			y = UTIL_SharedRandomFloat(shared_rand + (2 + iShot), -0.5, 0.5) + UTIL_SharedRandomFloat(shared_rand + (3 + iShot), -0.5, 0.5);
			z = x * x + y * y;
		}

	}

	return Vector(x * vecSpread.x, y * vecSpread.y, 0.0);
}

Vector CBaseEntity::DeviateShootingVectorDirector(Vector vecBase, Vector vecDeviation, float flDeviation)
{
	// Quick redefs
	Vector vecRight = gpGlobals->v_right;
	Vector vecUp = gpGlobals->v_up;
	Vector vecForward = gpGlobals->v_forward;

	float x = flDeviation * 1.0f;
	float y = flDeviation * 1.0f;
	float z = flDeviation * 1.0f;

	Vector vecDir = vecBase +
		x * vecDeviation.x * vecRight +
		y * vecDeviation.y * vecUp +
		z * vecDeviation.z * vecForward;

	return vecDir;
}


/*
=====================
CBasePlayerWeapon::ItemPostFrame

Handles weapon firing, reloading, etc.
=====================
*/
void CBasePlayerWeapon::ItemPostFrame( void )
{
	if ((m_pPlayer->pev->button & IN_ATTACK5) && (m_flNextQuinaryAttack <= 0.0))
	{
		QuinaryAttack();
		m_pPlayer->pev->button &= ~IN_ATTACK5;
	}
	else if ((m_pPlayer->pev->button & IN_ATTACK4) && (m_flNextQuaternaryAttack <= 0.0))
	{
		QuaternaryAttack();
		m_pPlayer->pev->button &= ~IN_ATTACK4;
	}
	else if ((m_pPlayer->pev->button & IN_ATTACK3) && (m_flNextTertiaryAttack <= 0.0))
	{
		TertiaryAttack();
		m_pPlayer->pev->button &= ~IN_ATTACK3;
	}
	else if ((m_pPlayer->pev->button & IN_ATTACK2) && (m_flNextSecondaryAttack <= 0.0))
	{
		SecondaryAttack();
		m_pPlayer->pev->button &= ~IN_ATTACK2;
	}
	else if ((m_pPlayer->pev->button & IN_ATTACK) && (m_flNextPrimaryAttack <= 0.0))
	{
		PrimaryAttack();
	}
	else if ( m_pPlayer->pev->button & IN_RELOAD && CanReload() && !InReload() )
	{
		// reload when reload is pressed, or if no buttons are down and weapon is empty.
		Reload();
	}
	else if (!(m_pPlayer->pev->button & (IN_ATTACK | IN_ATTACK2 | IN_ATTACK3 | IN_ATTACK4 | IN_ATTACK5)))
	{
		// no fire buttons down

		m_fFireOnEmpty = FALSE;

		// weapon is useable. Reload if empty and weapon has waited as long as it has to after firing
		//if ( m_iClip == 0 && !(iFlags() & ITEM_FLAG_NOAUTORELOAD) && m_flNextPrimaryAttack < 0.0 )
		//{
		//	Reload();
		//	return;
		//}

		WeaponIdle( );
		return;
	}
	
	// catch all
	if ( ShouldWeaponIdle() )
	{
		WeaponIdle();
	}
}

/*
=====================
CBasePlayer::SelectItem

  Switch weapons
=====================
*/
void CBasePlayer::SelectItem(const char *pstr)
{
	if (!pstr)
		return;

	CBasePlayerItem *pItem = NULL;

	if (!pItem)
		return;

	
	if (pItem == m_pActiveItem)
		return;

	if (m_pActiveItem)
		m_pActiveItem->Holster( );
	
	m_pLastItem = m_pActiveItem;
	m_pActiveItem = pItem;

	if (m_pActiveItem)
	{
		m_pActiveItem->Deploy( );
	}
}

/*
=====================
CBasePlayer::SelectLastItem

=====================
*/
void CBasePlayer::SelectLastItem(void)
{
	if (!m_pLastItem)
	{
		return;
	}

	if ( m_pActiveItem && !m_pActiveItem->CanHolster() )
	{
		return;
	}

	if (m_pActiveItem)
		m_pActiveItem->Holster( );
	
	CBasePlayerItem *pTemp = m_pActiveItem;
	m_pActiveItem = m_pLastItem;
	m_pLastItem = pTemp;
	m_pActiveItem->Deploy( );
}

/*
=====================
CBasePlayer::Killed

=====================
*/
void CBasePlayer::Killed( entvars_t *pevAttacker, int iGib )
{
	// Holster weapon immediately, to allow it to cleanup
	if ( m_pActiveItem )
		 m_pActiveItem->Holster( );
	
	g_irunninggausspred = false;
}

/*
=====================
CBasePlayer::Spawn

=====================
*/
void CBasePlayer::Spawn( void )
{
	if (m_pActiveItem)
		m_pActiveItem->Deploy( );

	g_irunninggausspred = false;
}

/*
=====================
UTIL_TraceLine

Don't actually trace, but act like the trace didn't hit anything.
=====================
*/
void UTIL_TraceLine( const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, edict_t *pentIgnore, TraceResult *ptr )
{
	memset( ptr, 0, sizeof( *ptr ) );
	ptr->flFraction = 1.0;
}

/*
=====================
UTIL_ParticleBox

For debugging, draw a box around a player made out of particles
=====================
*/
void UTIL_ParticleBox( CBasePlayer *player, float *mins, float *maxs, float life, unsigned char r, unsigned char g, unsigned char b )
{
	int i;
	vec3_t mmin, mmax;

	for ( i = 0; i < 3; i++ )
	{
		mmin[ i ] = player->pev->origin[ i ] + mins[ i ];
		mmax[ i ] = player->pev->origin[ i ] + maxs[ i ];
	}

	gEngfuncs.pEfxAPI->R_ParticleBox( (float *)&mmin, (float *)&mmax, 5.0, 0, 255, 0 );
}

/*
=====================
UTIL_ParticleBoxes

For debugging, draw boxes for other collidable players
=====================
*/
void UTIL_ParticleBoxes( void )
{
	int idx;
	physent_t *pe;
	cl_entity_t *player;
	vec3_t mins, maxs;
	
	gEngfuncs.pEventAPI->EV_SetUpPlayerPrediction( false, true );

	// Store off the old count
	gEngfuncs.pEventAPI->EV_PushPMStates();

	player = gEngfuncs.GetLocalPlayer();
	// Now add in all of the players.
	gEngfuncs.pEventAPI->EV_SetSolidPlayers ( player->index - 1 );	

	for ( idx = 1; idx < 100; idx++ )
	{
		pe = gEngfuncs.pEventAPI->EV_GetPhysent( idx );
		if ( !pe )
			break;

		if ( pe->info >= 1 && pe->info <= gEngfuncs.GetMaxClients() )
		{
			mins = pe->origin + pe->mins;
			maxs = pe->origin + pe->maxs;

			gEngfuncs.pEfxAPI->R_ParticleBox( (float *)&mins, (float *)&maxs, 0, 0, 255, 2.0 );
		}
	}

	gEngfuncs.pEventAPI->EV_PopPMStates();
}

/*
=====================
UTIL_ParticleLine

For debugging, draw a line made out of particles
=====================
*/
void UTIL_ParticleLine( CBasePlayer *player, float *start, float *end, float life, unsigned char r, unsigned char g, unsigned char b )
{
	gEngfuncs.pEfxAPI->R_ParticleLine( start, end, r, g, b, life );
}

/*
=====================
CBasePlayerWeapon::PrintState

For debugging, print out state variables to log file
=====================
*/
void CBasePlayerWeapon::PrintState( void )
{
	COM_Log( "c:\\hl.log", "%.4f ", gpGlobals->time );
	COM_Log( "c:\\hl.log", "%.4f ", m_pPlayer->m_flNextAttack );
	COM_Log( "c:\\hl.log", "%.4f ", m_flNextPrimaryAttack );
	COM_Log( "c:\\hl.log", "%.4f ", m_flNextWeaponIdle - gpGlobals->time);
}

/*
=====================
HUD_InitClientWeapons

Set up weapons, player and functions needed to run weapons code client-side.
=====================
*/
void HUD_InitClientWeapons( void )
{
	static int initialized = 0;
	if ( initialized )
		return;

	initialized = 1;

	// Set up pointer ( dummy object )
	gpGlobals = &Globals;

	// Fill in current time ( probably not needed )
	gpGlobals->time = gEngfuncs.GetClientTime();

	// Fake functions
	g_engfuncs.pfnPrecacheModel		= stub_PrecacheModel;
	g_engfuncs.pfnPrecacheSound		= stub_PrecacheSound;
	g_engfuncs.pfnPrecacheEvent		= stub_PrecacheEvent;
	g_engfuncs.pfnNameForFunction	= stub_NameForFunction;
	g_engfuncs.pfnSetModel			= stub_SetModel;
	g_engfuncs.pfnSetClientMaxspeed = HUD_SetMaxSpeed;

	// Handled locally
	g_engfuncs.pfnPlaybackEvent		= HUD_PlaybackEvent;
	g_engfuncs.pfnAlertMessage		= AlertMessage;

	// Pass through to engine
	g_engfuncs.pfnPrecacheEvent		= gEngfuncs.pfnPrecacheEvent;
	g_engfuncs.pfnRandomFloat		= gEngfuncs.pfnRandomFloat;
	g_engfuncs.pfnRandomLong		= gEngfuncs.pfnRandomLong;

	// Allocate a slot for the local player
	HUD_PrepEntity( &player		, NULL );

	// Allocate slot(s) for each weapon that we are going to be predicting
	//HUD_PrepEntity( &g_Glock	, &player );
	//HUD_PrepEntity( &g_Crowbar	, &player );
	//HUD_PrepEntity( &g_Python	, &player );
	HUD_PrepEntity( &g_Mp5	, &player );
	//HUD_PrepEntity( &g_Crossbow	, &player );
	//HUD_PrepEntity( &g_Shotgun	, &player );
	//HUD_PrepEntity( &g_Rpg	, &player );
	//HUD_PrepEntity( &g_Gauss	, &player );
	//HUD_PrepEntity( &g_Egon	, &player );
	//HUD_PrepEntity( &g_HGun	, &player );
	//HUD_PrepEntity( &g_HandGren	, &player );
	//HUD_PrepEntity( &g_Satchel	, &player );
	//HUD_PrepEntity( &g_Tripmine	, &player );
	//HUD_PrepEntity( &g_Snark	, &player );
}

/*
=====================
HUD_GetLastOrg

Retruns the last position that we stored for egon beam endpoint.
=====================
*/
void HUD_GetLastOrg( float *org )
{
	int i;
	
	// Return last origin
	for ( i = 0; i < 3; i++ )
	{
		org[i] = previousorigin[i];
	}
}

/*
=====================
HUD_SetLastOrg

Remember our exact predicted origin so we can draw the egon to the right position.
=====================
*/
void HUD_SetLastOrg( void )
{
	int i;
	
	// Offset final origin by view_offset
	for ( i = 0; i < 3; i++ )
	{
		previousorigin[i] = g_finalstate->playerstate.origin[i] + g_finalstate->client.view_ofs[ i ];
	}
}

/*
=====================
HUD_WeaponsPostThink

Run Weapon firing code on client
=====================
*/
void HUD_WeaponsPostThink( local_state_s *from, local_state_s *to, usercmd_t *cmd, double time, unsigned int random_seed )
{
	int i;
	int buttonsChanged;
	CBasePlayerWeapon *pWeapon = NULL;
	CBasePlayerWeapon *pCurrent;
	weapon_data_t nulldata, *pfrom, *pto;
	static int lasthealth;

	memset( &nulldata, 0, sizeof( nulldata ) );

	HUD_InitClientWeapons();	

	// Get current clock
	gpGlobals->time = time;

	// Fill in data based on selected weapon
	// FIXME, make this a method in each weapon?  where you pass in an entity_state_t *?
	switch ( from->client.m_iId )
	{
		case WEAPON_MP5:
			pWeapon = &g_Mp5;
			break;
	}

	// Store pointer to our destination entity_state_t so we can get our origin, etc. from it
	//  for setting up events on the client
	g_finalstate = to;

	// If we are running events/etc. go ahead and see if we
	//  managed to die between last frame and this one
	// If so, run the appropriate player killed or spawn function
	if ( g_runfuncs )
	{
		if ( to->client.health <= 0 && lasthealth > 0 )
		{
			player.Killed( NULL, 0 );
			
		}
		else if ( to->client.health > 0 && lasthealth <= 0 )
		{
			player.Spawn();
		}

		lasthealth = to->client.health;
	}

	// We are not predicting the current weapon, just bow out here.
	if ( !pWeapon )
		return;

	for ( i = 0; i < 32; i++ )
	{
		pCurrent = g_pWpns[ i ];
		if ( !pCurrent )
		{
			continue;
		}

		pfrom = &from->weapondata[ i ];
		
//		pCurrent->m_flPumpTime			= pfrom->m_flPumpTime;
		pCurrent->m_flNextPrimaryAttack	= pfrom->m_flNextPrimaryAttack;
		pCurrent->m_flNextSecondaryAttack = pfrom->m_flNextSecondaryAttack;
		pCurrent->m_flNextTertiaryAttack = pfrom->m_flNextTertiaryAttack;
		pCurrent->m_flNextQuaternaryAttack = pfrom->m_flNextQuaternaryAttack;
		pCurrent->m_flNextQuinaryAttack = pfrom->m_flNextQuinaryAttack;
		pCurrent->m_flNextWeaponIdle	= pfrom->m_flNextWeaponIdle;
		pCurrent->m_flNextReload		= pfrom->m_flNextReload;
		pCurrent->pev->fuser1			= pfrom->fuser1;
		pCurrent->m_flStartThrow		= pfrom->fuser2;
		pCurrent->m_flReleaseThrow		= pfrom->fuser3;
		pCurrent->m_chargeReady			= pfrom->iuser1;
		pCurrent->m_fInAttack			= pfrom->iuser2;
		pCurrent->m_fireState			= pfrom->iuser3;
	}

	// For random weapon events, use this seed to seed random # generator
	player.random_seed = random_seed;

	// Get old buttons from previous state.
	player.m_afButtonLast = from->playerstate.oldbuttons;

	// Which buttsons chave changed
	buttonsChanged = (player.m_afButtonLast ^ cmd->buttons);	// These buttons have changed this frame
	
	// Debounced button codes for pressed/released
	// The changed ones still down are "pressed"
	player.m_afButtonPressed =  buttonsChanged & cmd->buttons;	
	// The ones not down are "released"
	player.m_afButtonReleased = buttonsChanged & (~cmd->buttons);

	// Set player variables that weapons code might check/alter
	player.pev->button = cmd->buttons;

	player.pev->velocity = from->client.velocity;
	player.pev->flags = from->client.flags;

	player.pev->deadflag = from->client.deadflag;
	player.pev->waterlevel = from->client.waterlevel;
	player.pev->maxspeed    = from->client.maxspeed;
	player.pev->fov = from->client.fov;
	player.pev->viewmodelbody = from->client.viewmodelbody;
	player.pev->playmodelbody = from->client.playmodelbody;
	player.pev->armmodelbody = from->client.armmodelbody;
	player.pev->viewmodelskin = from->client.viewmodelskin;
	player.pev->playmodelskin = from->client.playmodelskin;
	player.pev->armmodelskin = from->client.armmodelskin;
	player.pev->weaponanim = from->client.weaponanim;
	player.pev->viewmodel = from->client.viewmodel;
	player.pev->armmodel = from->client.armmodel;
	//player.pev->weaponmodel = from->client.weaponmodel;

	player.m_flNextAttack = from->client.m_flNextAttack;
	player.m_flNextAmmoBurn = from->client.fuser2;
	player.m_flAmmoStartCharge = from->client.fuser3;

	//Stores all our ammo info, so the client side weapons can use them.
	//for (int it = 0; it < MAX_AMMO_TYPES; it++)
	//{
	//	(player.m_iaAmmo)[it] = (int)from->client.ammo[it];
	//}

	//player.ammo_9mm			= (int)from->client.vuser1[0];
	//player.ammo_357			= (int)from->client.vuser1[1];
	//player.ammo_argrens		= (int)from->client.vuser1[2];
	//player.ammo_bolts		= (int)from->client.ammo_nails; //is an int anyways...
	//player.ammo_buckshot	= (int)from->client.ammo_shells; 
	//player.ammo_uranium		= (int)from->client.ammo_cells;
	//player.ammo_hornets		= (int)from->client.vuser2[0];
	//player.ammo_rockets		= (int)from->client.ammo_rockets;

	
	// Point to current weapon object
	if ( from->client.m_iId )
	{
		player.m_pActiveItem = g_pWpns[ from->client.m_iId ];
	}

	/*
	if ( player.m_pActiveItem->m_iId == WEAPON_RPG )
	{
		 ( player.m_pActiveItem)->m_fSpotActive = (int)from->client.vuser2[ 1 ];
		 ( player.m_pActiveItem)->m_cActiveRockets = (int)from->client.vuser2[ 2 ];
	}
	*/
	
	// Don't go firing anything if we have died.
	// Or if we don't have a weapon model deployed
	if ( ( player.pev->deadflag != ( DEAD_DISCARDBODY + 1 ) ) && 
		 !CL_IsDead() && player.pev->viewmodel && !g_iUser1 )
	{
		if ( player.m_flNextAttack <= 0 )
		{
			pWeapon->ItemPostFrame();
		}
	}

	// Assume that we are not going to switch weapons
	to->client.m_iId					= from->client.m_iId;

	// Now see if we issued a changeweapon command ( and we're not dead )
	if ( cmd->weaponselect && ( player.pev->deadflag != ( DEAD_DISCARDBODY + 1 ) ) )
	{
		// Switched to a different weapon?
		if ( from->weapondata[ cmd->weaponselect ].m_iId == cmd->weaponselect )
		{
			CBasePlayerWeapon *pNew = g_pWpns[ cmd->weaponselect ];
			if ( pNew && ( pNew != pWeapon ) )
			{
				// Put away old weapon
				if (player.m_pActiveItem)
					player.m_pActiveItem->Holster( );
				
				player.m_pLastItem = player.m_pActiveItem;
				player.m_pActiveItem = pNew;

				// Deploy new weapon
				if (player.m_pActiveItem)
				{
					player.m_pActiveItem->Deploy( );
				}

				// Update weapon id so we can predict things correctly.
				to->client.m_iId = cmd->weaponselect;
			}
		}
	}

	// Copy in results of prediction code
	to->client.viewmodel				= player.pev->viewmodel;
	to->client.armmodel					= player.pev->armmodel;
	to->client.fov						= player.pev->fov;
	to->client.weaponanim				= player.pev->weaponanim;
	to->client.viewmodelbody = player.pev->viewmodelbody;
	to->client.playmodelbody = player.pev->playmodelbody;
	to->client.armmodelbody = player.pev->armmodelbody;
	to->client.viewmodelskin = player.pev->viewmodelskin;
	to->client.playmodelskin = player.pev->playmodelskin;
	to->client.armmodelskin = player.pev->armmodelskin;
	to->client.savedvanim = player.pev->savedvanim;
	to->client.savedvframerate = player.pev->savedvframerate;
	to->client.savedvframe = player.pev->savedvframe;
	to->client.m_flNextAttack			= player.m_flNextAttack;
	to->client.fuser2					= player.m_flNextAmmoBurn;
	to->client.fuser3					= player.m_flAmmoStartCharge;
	to->client.maxspeed					= player.pev->maxspeed;

	//HL Weapons

	//for (int it = 0; it < MAX_AMMO_TYPES; it++)
	//{
	//	to->client.ammo[it]				= player.m_iaAmmo[it];
	//}

	//to->client.vuser1[0]				= player.ammo_9mm;
	//to->client.vuser1[1]				= player.ammo_357;
	//to->client.vuser1[2]				= player.ammo_argrens;
	//to->client.ammo_nails				= player.ammo_bolts;
	//to->client.ammo_shells				= player.ammo_buckshot;
	//to->client.ammo_cells				= player.ammo_uranium;
	//to->client.vuser2[0]				= player.ammo_hornets;
	//to->client.ammo_rockets				= player.ammo_rockets;

	/*
	if ( player.m_pActiveItem->m_iId == WEAPON_RPG )
	{
		 from->client.vuser2[ 1 ] = ( ( CRpg * )player.m_pActiveItem)->m_fSpotActive;
		 from->client.vuser2[ 2 ] = ( ( CRpg * )player.m_pActiveItem)->m_cActiveRockets;
	}
	*/

	// Make sure that weapon animation matches what the game .dll is telling us
	//  over the wire ( fixes some animation glitches )
	if ( g_runfuncs && ( HUD_GetWeaponAnim() != to->client.weaponanim ) )
	{		
		// Force a fixed anim down to viewmodel
		HUD_SendWeaponAnim( to->client.weaponanim, to->client.savedvframerate, to->client.savedvframe, 1 );
	}

	for ( i = 0; i < 32; i++ )
	{
		pCurrent = g_pWpns[ i ];

		pto = &to->weapondata[ i ];

		if ( !pCurrent )
		{
			memset( pto, 0, sizeof( weapon_data_t ) );
			continue;
		}
	
//		pto->m_flPumpTime				= pCurrent->m_flPumpTime;
		//pto->m_iClip					= pCurrent->m_iClip; 
		pto->m_flNextPrimaryAttack		= pCurrent->m_flNextPrimaryAttack;
		pto->m_flNextSecondaryAttack	= pCurrent->m_flNextSecondaryAttack;
		pto->m_flNextTertiaryAttack		= pCurrent->m_flNextTertiaryAttack;
		pto->m_flNextTertiaryAttack = pCurrent->m_flNextTertiaryAttack;
		pto->m_flNextQuaternaryAttack = pCurrent->m_flNextQuaternaryAttack;
		pto->m_flNextReload				= pCurrent->m_flNextReload;
		pto->m_flNextWeaponIdle			= pCurrent->m_flNextWeaponIdle;
		pto->fuser1						= pCurrent->pev->fuser1;
		pto->fuser2						= pCurrent->m_flStartThrow;
		pto->fuser3						= pCurrent->m_flReleaseThrow;
		pto->iuser1						= pCurrent->m_chargeReady;
		pto->iuser2						= pCurrent->m_fInAttack;
		pto->iuser3						= pCurrent->m_fireState;

		// Decrement weapon counters, server does this at same time ( during post think, after doing everything else )
		pto->m_flNextReload				-= cmd->msec / 1000.0;
		pto->m_fNextAimBonus			-= cmd->msec / 1000.0;
		pto->m_flNextPrimaryAttack		-= cmd->msec / 1000.0;
		pto->m_flNextSecondaryAttack	-= cmd->msec / 1000.0;
		pto->m_flNextTertiaryAttack		-= cmd->msec / 1000.0;
		pto->m_flNextQuaternaryAttack	-= cmd->msec / 1000.0;
		pto->m_flNextQuinaryAttack		-= cmd->msec / 1000.0;
		pto->m_flNextWeaponIdle			-= cmd->msec / 1000.0;
		pto->fuser1						-= cmd->msec / 1000.0;

/*		if ( pto->m_flPumpTime != -9999 )
		{
			pto->m_flPumpTime -= cmd->msec / 1000.0;
			if ( pto->m_flPumpTime < -0.001 )
				pto->m_flPumpTime = -0.001;
		}*/

		if ( pto->m_fNextAimBonus < -1.0 )
		{
			pto->m_fNextAimBonus = -1.0;
		}

		if ( pto->m_flNextPrimaryAttack < -1.0 )
		{
			pto->m_flNextPrimaryAttack = -1.0;
		}

		if ( pto->m_flNextSecondaryAttack < -0.001 )
		{
			pto->m_flNextSecondaryAttack = -0.001;
		}

		if (pto->m_flNextTertiaryAttack < -0.001)
		{
			pto->m_flNextTertiaryAttack = -0.001;
		}

		if (pto->m_flNextQuaternaryAttack < -0.001)
		{
			pto->m_flNextQuaternaryAttack = -0.001;
		}

		if (pto->m_flNextQuinaryAttack < -0.001)
		{
			pto->m_flNextQuinaryAttack = -0.001;
		}

		if ( pto->m_flNextWeaponIdle < -0.001 )
		{
			pto->m_flNextWeaponIdle = -0.001;
		}

		if ( pto->m_flNextReload < -0.001 )
		{
			pto->m_flNextReload = -0.001;
		}

		if ( pto->fuser1 < -0.001 )
		{
			pto->fuser1 = -0.001;
		}
	}

	// m_flNextAttack is now part of the weapons, but is part of the player instead
	to->client.m_flNextAttack -= cmd->msec / 1000.0;
	if ( to->client.m_flNextAttack < -0.001 )
	{
		to->client.m_flNextAttack = -0.001;
	}

	to->client.fuser2 -= cmd->msec / 1000.0;
	if ( to->client.fuser2 < -0.001 )
	{
		to->client.fuser2 = -0.001;
	}
	
	to->client.fuser3 -= cmd->msec / 1000.0;
	if ( to->client.fuser3 < -0.001 )
	{
		to->client.fuser3 = -0.001;
	}

	// Store off the last position from the predicted state.
	HUD_SetLastOrg();

	// Wipe it so we can't use it after this frame
	g_finalstate = NULL;
}

BOOL CanAttack(float attack_time, float curtime, BOOL isPredicted)
{
#if defined( CLIENT_WEAPONS )
	if (!isPredicted)
#else
	if (1)
#endif
	{
		return (attack_time <= curtime) ? TRUE : FALSE;
	}
	else
	{
		return (attack_time <= 0.0) ? TRUE : FALSE;
	}
}

BOOL CBasePlayerItem::ShouldRedeploy(CBasePlayerItem* pOriginal)
{
	if (pOriginal->m_pPlayer)
	{
		if (pOriginal->m_pPlayer->m_pActiveItem)
		{
			if (FClassnameIs(pOriginal->m_pPlayer->m_pActiveItem->pev, STRING(pev->classname)))
			{
				if (IsUpgradeable(pOriginal))
					return TRUE;
			}
		}
	}

	return FALSE;
}

// Viewmodel animation saving crap goes here
void CBasePlayerWeapon::UpdateAnimationInfo(void)
{
	/*
	// Sanity check as always
	if (m_pPlayer)
	{
		// Get all the handles you need
		int iAnim = m_pPlayer->pev->savedvanim;
		float flFramerate = m_pPlayer->pev->savedvframerate;
		const animinfo_t* animInfo = &(weaponAnimInfoArray[m_iId].pWeaponAnimInfoArray[iAnim]);
		float flModelFramerate = (float)(animInfo->framerate);
		float flModelNumFrames = (float)(animInfo->numframes - 1);

		// Multiply by server frame rate as it applies after the model framerate
		float flFinalTime = (flModelNumFrames / flModelFramerate) * fabs(flFramerate);

		// Increment time, don't do it if the time is 
		if (!(animInfo->looping) && m_flWeaponAnimTime < flFinalTime)
			m_flWeaponAnimTime += gpGlobals->frametime;

		// Save the fucking thing
		m_pPlayer->pev->savedvframe = (byte)((float)255.0f * (m_flWeaponAnimTime / flFinalTime));

		// Reset if this animation is looping and do it depending on the sign of the server framerate
		if (animInfo->looping)
		{
			if (m_flWeaponAnimTime >= flFinalTime)
			{
				m_flWeaponAnimTime = 0.0f;
				if (m_pPlayer->pev->savedvframe > 0)
					m_pPlayer->pev->savedvframe = (byte)0;
				else
					m_pPlayer->pev->savedvframe = (byte)255.0f;
			}
		}
	}
	else
	{
		m_flWeaponAnimTime = 0.0f;
	}
	*/
}

/*
=====================
HUD_PostRunCmd

Client calls this during prediction, after it has moved the player and updated any info changed into to->
time is the current client clock based on prediction
cmd is the command that caused the movement, etc
runfuncs is 1 if this is the first time we've predicted this command.  If so, sounds and effects should play, otherwise, they should
be ignored
=====================
*/
void _DLLEXPORT HUD_PostRunCmd( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed )
{
	g_runfuncs = runfuncs;

#if defined( CLIENT_WEAPONS )
	if ( cl_lw && cl_lw->value )
	{
		HUD_WeaponsPostThink( from, to, cmd, time, random_seed );
	}
	else
#endif
	{
		to->client.fov = g_lastFOV;
	}

	if ( g_irunninggausspred == 1 )
	{
		Vector forward;
		gEngfuncs.pfnAngleVectors( v_angles, forward, NULL, NULL );
		to->client.velocity = to->client.velocity - forward * g_flApplyVel * 5; 
		g_irunninggausspred = false;
	}
	
	// All games can use FOV state
	g_lastFOV = to->client.fov;
}

void FindHullIntersection(const Vector& vecSrc, TraceResult& tr, float* mins, float* maxs, edict_t* pEntity)
{
	int			i, j, k;
	float		distance;
	float* minmaxs[2] = { mins, maxs };
	TraceResult tmpTrace;
	Vector		vecHullEnd = tr.vecEndPos;
	Vector		vecEnd;

	distance = 1e6f;

	vecHullEnd = vecSrc + ((vecHullEnd - vecSrc) * 2);
	UTIL_TraceLine(vecSrc, vecHullEnd, dont_ignore_monsters, pEntity, &tmpTrace);
	if (tmpTrace.flFraction < 1.0)
	{
		tr = tmpTrace;
		return;
	}

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			for (k = 0; k < 2; k++)
			{
				vecEnd.x = vecHullEnd.x + minmaxs[i][0];
				vecEnd.y = vecHullEnd.y + minmaxs[j][1];
				vecEnd.z = vecHullEnd.z + minmaxs[k][2];

				UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, pEntity, &tmpTrace);
				if (tmpTrace.flFraction < 1.0)
				{
					float thisDistance = (tmpTrace.vecEndPos - vecSrc).Length();
					if (thisDistance < distance)
					{
						tr = tmpTrace;
						distance = thisDistance;
					}
				}
			}
		}
	}
}