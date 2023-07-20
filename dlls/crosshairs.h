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
//
// crosshairs.h
//
// Definitions for all of the new crosshair content
//

#pragma once

#include <vector>

// Some invalid values
#define CH_ANIM_INDEX_INVALID -1
#define CH_ANIM_FRAME_INVALID -1
#define CH_ANIM_TIME_INVALID -1.0f

// Default behavior value
#define CH_INVALID -2
#define CH_DEFAULT -1

enum circleShapes_e
{
	CSHAPE_ARC = 0,
	CSHAPE_SEC,
	CSHAPE_SEG,
	CSHAPE_SEC_FULL,
	CSHAPE_SEG_FULL,
};

enum lineShapes_e
{
	LSHAPE_NORMAL = 0,
	LSHAPE_RADIUS,
	LSHAPE_DIAMETER,
	LSHAPE_RAY,
	LSHAPE_RAYDIUS,
	LSHAPE_DIAMETER_RAY,
	LSHAPE_LINE
};

enum spriteShapes_e
{
	SSHAPE_ADDITIVE = 0,
	SSHAPE_ALPHATEST,
	SSHAPE_NORMAL,
	SSHAPE_INDEXEDALPHA
};

enum fontShapes_e
{
	FSHAPE_NORM,
	FSHAPE_SELF,
};

enum chPartType_e 
{
	CHPT_NONE = 0,
	CHPT_SPRITE,
	CHPT_SYSFONT,
	CHPT_NUMBER,
	CHPT_LINE,
	CHPT_CIRCLE,
};

enum chAnim_e
{
	CHA_FRAME = 0,
	CHA_RED,
	CHA_GREEN,
	CHA_BLUE,
	CHA_ALPHA,
	CHA_XOFFSET,
	CHA_YOFFSET,
	CHA_XSCALE,
	CHA_YSCALE,
	CHA_THICK,
	CHA_SPANSTART,
	CHA_SPANEND,
	CHA_XPIVOT,
	CHA_YPIVOT,
	CHA_SELFROTATE,
	CHA_ROTATE,

	CHA_TOTAL,
};

// Hardcoded crosshair sub types
enum chSubType_e
{
	CHSB_NORMAL = 0, // Normal crosshair
	CHSB_NORMAL_DENY, // Crosshair with a deny sign on
	CHSB_AIM, // Crosshair when aiming
	CHSB_AIM_DENY, // Crosshair when aiming and a deny sign
	CHSB_ZOOM, 
	CHSB_ZOOM_DENY,
	CHSB_ZOOM_AIM,
	CHSB_ZOOM_AIM_DENY,

	CHSB_AUTO, // This is a special crosshair that's drawn with the auto-aim system, PS2 style
	CHSB_AUTO_AIM, // This is a special crosshair that's drawn with the auto-aim system, PS2 style
	CHSB_AUTO_LOCK, 

	CHSB_TOTAL,
};

#define CH_CFLAG_NONE 0 // No color flag
#define CH_CFLAG_HUD 1 // Follow hard-coded hud behavior
#define CH_CFLAG_LOW 2
#define CH_CFLAG_MED 3
#define CH_CFLAG_HIGH 4
#define CH_CFLAG_PART 5 // Used the RGB values defined by the part itself
#define CH_CFLAG_CUSTOM 6 // Use the colors defined by the player (DIFFICULT TO IMPLEMENT)	

#define CH_SUB_NEITHER 0
#define CH_SUB_NORM	   1
#define CH_SUB_AUTO	   2
#define CH_SUB_ALL	   3

#define CH_BEHAVIOR_NONE	0
#define CH_BEHAVIOR_CLASSIC	1 // Regular sub-crosshair is used as auto-crosshair
#define CH_BEHAVIOR_NEO		2	// Auto and sub-crosshair are split

// Crosshair parts can be individually animated
typedef struct crosshair_part_anim_seg
{
	int startFrame; // If from a sprite, which frame do we start at
	int endFrame; // If from a sprite, which frame do we stop at
	int framerate; // Frame rate of the animation
	int nextPartAnim; // Index of next part anim, if invalid check for loop condition
	int loop; // This is only ever used if we can't move to another valid loop animation

	// Scales are increment, goal scales are the goals to reach
	float startcrement; // How much crement do we start at?
	float crement; // How much do we increment or decrement per frame
} chPartAnimSegment;

typedef std::vector<chPartAnimSegment> chPartAnimSegmentVector;

// Portion of a crosshair
typedef struct crosshairs_part
{
	//=======================================
	// STATIC PARTS
	//=======================================

	// Drawing ressources
	int parttype, partsubtype; // Part and sub partype
	const char spritename[128]; // Name of the sprite used, note if font or sprite, this is used as a path to file, otherwise, it's set to null
	HSPR partspr; // Sprite that's loaded, spritename must be set

	// Drawing properties
	int xoffset, yoffset; // X and Y offset from the center the crosshair
	int xpos, ypos; // If sprite, this is used to determine the starting y position of the sprite drawing
	int width, height;
	float thickness;
	float spanstart; // This is mostly for circles and maybe later along the line graphics that may need to be partially drawn
	float spanend;

	// Color control, see above for flags
	int	colorflags;
	int r, g, b, a;

	// Self rotation
	float selfrotation; // rotation around itself, static

	// Pivot rotation
	int xpivot, ypivot; // x and y offsets from the center to determine rotation pivot.
	float rotation; // rotation around the pivot, static

	//=======================================
	// MOVING PARTS
	//=======================================

	// Scale factors when applying inaccuracy scales, note that weapons will define min and max scaling amounts/percentages
	float xscale, yscale; // x and y scaling
	float selfanglescale;
	float xpivotscale, ypivotscale;
	float anglescale;
	float wscale, hscale; // width and height scaling of part
	float thickscale; // thickness scale if applicable
	float spanstartscale; // Span increment
	float spanendscale;

	// Scaling information related to accuracy/recoil
	float xinc, yinc;
	float selfangleinc;
	float xpivinc, ypivinc;
	float angleinc;
	float winc, hinc;
	float thickinc;
	float spanstartinc; // Span increment
	float spanendinc;

	chPartAnimSegmentVector animations[CHA_TOTAL];
} chPart;

typedef std::vector<chPart> chSub;

// Crosshair containing multiple subparts
typedef struct crosshair
{
	const char name[128]; // The name of the crosshair, this will be used to identify the crosshair and associate
	chSub subs[CHSB_TOTAL];
} crsh;

typedef std::vector<crsh> crosshairDatabase;

// This struct is solely meant for active crosshair parts
typedef struct crosshairPartsActive
{
	int animindex[CHA_TOTAL];
	int animframe[CHA_TOTAL];
	int animloop[CHA_TOTAL];
	float animtime[CHA_TOTAL];
	wrect_t partrc;
} chPartActive;

typedef std::vector<chPartActive> chPartActiveVector;

// This struct is solely meant for active crosshairs
typedef struct crosshairActive {
	int id; // Id of the crosshair being used
	int sub_id; // id of the sub crosshair being used
	int auto_id; // id of the auto-aim crosshair
	chPartActiveVector parts;
	chPartActiveVector autoparts;
} chActive;

// Scale adjustment garbage
int HUDScaleAdjustX(int x);
int HUDScaleAdjustY(int y);
float HUDScaleVertical(void);
float HUDScaleHorizontal(void);
float HUDScaleAdjustBoth(void);