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
#ifndef ENTITY_STATE_H
#define ENTITY_STATE_H

// For entityType below
#define ENTITY_NORMAL		(1<<0)
#define ENTITY_BEAM			(1<<1)

// Entity state is used for the baseline and for delta compression of a packet of 
//  entities that is sent to a client.
typedef struct entity_state_s entity_state_t;

struct entity_state_s
{
// Fields which are filled in by routines outside of delta compression
	int		entityType;
	// Index into cl_entities array for this entity.
	int		number;      
	float		msg_time;

	// Message number last time the player/entity state was updated.
	int		messagenum;

// Fields which can be transitted and reconstructed over the network stream
	vec3_t		origin;
	vec3_t		angles;

	int		modelindex;
	int		sequence;
	float		frame;
	int		colormap;

	short		solid;
	int		effects;
	float		scale;
	byte		eflags;

	// Render information
	int		rendermode;
	int		renderamt;
	color24		rendercolor;
	int		renderfx;

	int		movetype;
	float		animtime;
	float		framerate;
	byte		controller[4];
	byte		blending[4];
	vec3_t		velocity;

	int		body;
	int		viewmodelbody;
	int		playmodelbody;
	int		armmodelbody;
	int		skin;
	int		viewmodelskin;
	int		armmodelskin;
	int		playmodelskin;

	int savedvanim;
	float savedvframerate;
	byte savedvframe;

	// Send bbox down to client for use during prediction.
	vec3_t		mins;    
	vec3_t		maxs;

	int		aiment;
	// If owned by a player, the index of that player ( for projectiles ).
	int		owner; 

	// Friction, for prediction.
	float		friction;       
	// Gravity multiplier
	float		gravity;				

// PLAYER SPECIFIC
	int		team;
	int		playerclass;
	float		health;
	int			health_type;
	float		health_max;
	float		health_over_max;
	float		health_temp;
	float		health_temp_max;
	float		armor;
	int			armor_type;
	float		armor_max;
	float		armor_over_max;
	float		armor_temp;
	float		armor_temp_max;
	float		shield;
	int			shield_type;
	float		shield_max;
	float		shield_over_max;
	float		shield_temp;
	float		shield_temp_max;
	qboolean		spectator;  
	int		armmodel;
	int		weaponmodel;
	int		gaitsequence;
	// If standing on conveyor, e.g.
	vec3_t		basevelocity;   
	// Use the crouched hull, or the regular player hull.
	int		usehull;		
	// Latched buttons last time state updated.
	int		oldbuttons;     
	// -1 = in air, else pmove entity number
	int		onground;		
	int		iStepLeft;
	// How fast we are falling
	float		flFallVelocity;  

	float		fov;
	int		weaponanim;

	// Parametric movement overrides
	vec3_t		startpos;
	vec3_t		endpos;
	float		impacttime;
	float		starttime;

	// For mods
	int		iuser1;
	int		iuser2;
	int		iuser3;
	int		iuser4;
	float		fuser1;
	float		fuser2;
	float		fuser3;
	float		fuser4;
	vec3_t		vuser1;
	vec3_t		vuser2;
	vec3_t		vuser3;
	vec3_t		vuser4;
};

#include "pm_info.h"

typedef struct clientdata_s
{
	vec3_t		origin;
	vec3_t		velocity;

	int		viewmodel;
	int		armmodel;
	vec3_t		punchangle;
	int		flags;
	int		waterlevel;
	int		watertype;
	vec3_t		view_ofs;

	float		health;
	int			health_type;
	float		health_max;
	float		health_over_max;
	float		health_temp;
	float		health_temp_max;
	float		armor;
	int			armor_type;
	float		armor_max;
	float		armor_over_max;
	float		armor_temp;
	float		armor_temp_max;
	float		shield;
	int			shield_type;
	float		shield_max;
	float		shield_over_max;
	float		shield_temp;
	float		shield_temp_max;

	int		bInDuck;
	int		weapons; // remove?
	
	int		flTimeStepSound;
	int		flDuckTime;
	int		flSwimTime;
	int		waterjumptime;

	float		maxspeed;

	float		fov;
	int		weaponanim;

	int		viewmodelbody;
	int		playmodelbody;
	int		armmodelbody;
	int		viewmodelskin;
	int		armmodelskin;
	int		playmodelskin;

	int savedvanim;
	float savedvframerate;
	float savedvframe;

	int		m_iId;
	float		m_flNextAttack;
	
	int		tfstate;
	int		pushmsec;
	int		deadflag;
	char		physinfo[MAX_PHYSINFO_STRING];

	// For mods
	int		iuser1;
	int		iuser2;
	int		iuser3;
	int		iuser4;
	float		fuser1;
	float		fuser2;
	float		fuser3;
	float		fuser4;
	vec3_t		vuser1;
	vec3_t		vuser2;
	vec3_t		vuser3;
	vec3_t		vuser4;

	int ammo[MAX_AMMO_TYPES];

} clientdata_t;

#include "weaponinfo.h"

#define MAX_LOCAL_WEAPONS	64	// max weapons that can be predicted on the client

typedef struct local_state_s
{
	entity_state_t	playerstate;
	clientdata_t	client;
	weapon_data_t	weapondata[MAX_LOCAL_WEAPONS];
} local_state_t;

#endif//ENTITY_STATE_H