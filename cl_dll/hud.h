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
//  hud.h
//
// class CHud declaration
//
// CHud handles the message, calculation, and drawing the HUD
//


#define RGB_YELLOWISH 0x00FFA000 //255,160,0
#define RGB_REDISH 0x00FF1010 //255,160,0
#define RGB_GREENISH 0x0000A000 //0,160,0

#include "wrect.h"
#include "cl_dll.h"
#include "ammo.h"
#include "../dlls/dmg.h"

#define DHN_DRAWZERO 1
#define DHN_2DIGITS  2
#define DHN_3DIGITS  4
#define MIN_ALPHA	 100	

#define		HUDELEM_ACTIVE	1

typedef struct {
	int x, y;
} POSITION;

enum 
{ 
	MAX_PLAYERS = 64,
	MAX_TEAMS = 64,
	MAX_TEAM_NAME = 16,
};

typedef struct {
	unsigned char r,g,b,a;
} RGBA;

typedef struct cvar_s cvar_t;


#define HUD_ACTIVE	1
#define HUD_INTERMISSION 2

#define MAX_PLAYER_NAME_LENGTH		32

#define	MAX_MOTD_LENGTH				1536

//
//-----------------------------------------------------
//
class CHudBase
{
public:
	POSITION  m_pos;
	int   m_type;
	int	  m_iFlags; // active, moving, 
	virtual		~CHudBase() {}
	virtual int Init( void ) {return 0;}
	virtual int VidInit( void ) {return 0;}
	virtual int Draw(float flTime) {return 0;}
	virtual void Think(void) {return;}
	virtual void Reset(void) {return;}
	virtual void InitHUDData( void ) {}		// called every time a server is connected to

};

struct HUDLIST {
	CHudBase	*p;
	HUDLIST		*pNext;
};



//
//-----------------------------------------------------
//
#include "..\game_shared\voice_status.h"
#include "hud_spectator.h"

#include "..\dlls\crosshairs.h"

//
//-----------------------------------------------------
//
class CHudCrosshair : public CHudBase
{
public:
	int Init(void);
	int VidInit(void);
	int Draw(float flTime);
	void Think(void);
	void Reset(void);

	// Message function
	int MsgFunc_Crosshair(const char* pszName, int iSize, void* pbuf);
	int MsgFunc_AutoAim(const char* pszName, int iSize, void* pbuf);

	crosshairDatabase allCrosshairs = {};
	chActive activeCrosshair = { -1, -1, -1, {}, {} }; // The crosshair that's been currently active, remember, we can only have one active crosshair

	void DetectCVarChanges(void); // Detected CVarChanges and swap crosshairs accordingly

	// Set crosshairs
	int	ValidMainCrosshairId(int iMainCrosshairId);
	int ValidSubCrosshairIndex(int iSubCrosshairIndex);
	int ValidPartIndex(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex);
	int ValidAnimationType(int iAnimType);
	int ValidAnimationIndex(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex, int iAnimType, int iAnimIndex); // Is the animation valid? Check if it exists and validity of start and end frames

	// Helper pointer references
	crsh* GetCrosshairReference(int iMainCrosshairId);
	chSub* GetSubCrosshairReference(int iMainCrosshairId, int iSubCrosshairIndex);
	chPart* GetPartReference(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex);
	chPartAnimSegmentVector* GetAnimationVectorReference(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex, int iAnimType);
	chPartAnimSegment* GetAnimationReference(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex, int iAnimType, int iAnimIndex);

	int GetNumParts(chSub* pSub);
	int GetNumParts(int iMainCrosshairId, int iSubCrosshairIndex);
	int GetNumAnimationSegments(chPart* pPart, int iAnimType);

	// Helper functions to get part data
	int GetPartType(chPart* pPart);
	int GetPartSubType(chPart* pPart);
	const char* GetPartSpriteName(chPart* pPart);
	HSPR GetPartSprite(chPart* pPart);
	int GetPartXOffset(chPart* pPart);
	int GetPartYOffset(chPart* pPart);
	int GetPartXPosition(chPart* pPart);
	int GetPartYPosition(chPart* pPart);
	int GetPartHeight(chPart* pPart);
	int GetPartWidth(chPart* pPart);
	float GetPartThickness(chPart* pPart);
	float GetPartSpanStart(chPart* pPart);
	float GetPartSpanEnd(chPart* pPart);
	int GetPartColorFlags(chPart* pPart);
	int GetPartRed(chPart* pPart);
	int GetPartGreen(chPart* pPart);
	int GetPartBlue(chPart* pPart);
	int GetPartAlpha(chPart* pPart);
	float GetPartSelfRotation(chPart* pPart);
	int GetPartXPivot(chPart* pPart);
	int GetPartYPivot(chPart* pPart);
	float GetPartRotation(chPart* pPart);
	float GetPartXScale(chPart* pPart);
	float GetPartYScale(chPart* pPart);
	float GetPartSelfAngleScale(chPart* pPart);
	float GetPartXPivotScale(chPart* pPart);
	float GetPartYPivotScale(chPart* pPart);
	float GetPartAngleScale(chPart* pPart);
	float GetPartWidthScale(chPart* pPart);
	float GetPartHeightScale(chPart* pPart);
	float GetPartThicknessScale(chPart* pPart);
	float GetPartSpanStartScale(chPart* pPart);
	float GetPartSpanEndScale(chPart* pPart);
	float GetPartXIncrement(chPart* pPart);
	float GetPartYIncrement(chPart* pPart);
	float GetPartSelfAngleIncrement(chPart* pPart);
	float GetPartXPivotIncrement(chPart* pPart);
	float GetPartYPivotIncrement(chPart* pPart);
	float GetPartAngleIncrement(chPart* pPart);
	float GetPartWidthIncrement(chPart* pPart);
	float GetPartHeightIncrement(chPart* pPart);
	float GetPartThicknessIncrement(chPart* pPart);
	float GetPartSpanStartIncrement(chPart* pPart);
	float GetPartSpanEndIncrement(chPart* pPart);

	// Helper functions to set part data
	void SetPartType(chPart* pPart, int iValue);
	void SetPartSubType(chPart* pPart, int iValue);
	void SetPartSpriteName(chPart* pPart, const char* szValue);
	void SetPartSprite(chPart* pPart, const char* szSpriteName);
	void SetPartXOffset(chPart* pPart, int iValue);
	void SetPartYOffset(chPart* pPart, int iValue);
	void SetPartXPosition(chPart* pPart, int iValue);
	void SetPartYPosition(chPart* pPart, int iValue);
	void SetPartHeight(chPart* pPart, int iValue);
	void SetPartWidth(chPart* pPart, int iValue);
	void SetPartThickness(chPart* pPart, float flValue);
	void SetPartSpanStart(chPart* pPart, float flValue);
	void SetPartSpanEnd(chPart* pPart, float flValue);
	void SetPartColorFlags(chPart* pPart, int iValue);
	void SetPartRed(chPart* pPart, int iValue);
	void SetPartGreen(chPart* pPart, int iValue);
	void SetPartBlue(chPart* pPart, int iValue);
	void SetPartAlpha(chPart* pPart, int iValue);
	void SetPartSelfRotation(chPart* pPart, float flValue);
	void SetPartXPivot(chPart* pPart, int iValue);
	void SetPartYPivot(chPart* pPart, int iValue);
	void SetPartRotation(chPart* pPart, float flValue);
	void SetPartXScale(chPart* pPart, float flValue);
	void SetPartYScale(chPart* pPart, float flValue);
	void SetPartSelfAngleScale(chPart* pPart, float flValue);
	void SetPartXPivotScale(chPart* pPart, float flValue);
	void SetPartYPivotScale(chPart* pPart, float flValue);
	void SetPartAngleScale(chPart* pPart, float flValue);
	void SetPartWidthScale(chPart* pPart, float flValue);
	void SetPartHeightScale(chPart* pPart, float flValue);
	void SetPartThicknessScale(chPart* pPart, float flValue);
	void SetPartSpanStartScale(chPart* pPart, float flValue);
	void SetPartSpanEndScale(chPart* pPart, float flValue);
	void SetPartXIncrement(chPart* pPart, float flValue);
	void SetPartYIncrement(chPart* pPart, float flValue);
	void SetPartSelfAngleIncrement(chPart* pPart, float flValue);
	void SetPartXPivotIncrement(chPart* pPart, float flValue);
	void SetPartYPivotIncrement(chPart* pPart, float flValue);
	void SetPartAngleIncrement(chPart* pPart, float flValue);
	void SetPartWidthIncrement(chPart* pPart, float flValue);
	void SetPartHeightIncrement(chPart* pPart, float flValue);
	void SetPartThicknessIncrement(chPart* pPart, float flValue);
	void SetPartSpanStartIncrement(chPart* pPart, float flValue);
	void SetPartSpanEndIncrement(chPart* pPart, float flValue);
	
	// Helper functions to get animation 
	int GetAnimationStartFrame(chPartAnimSegment* pAnimSeg);
	int GetAnimationEndFrame(chPartAnimSegment* pAnimSeg);
	int GetAnimationFramerate(chPartAnimSegment* pAnimSeg);
	int GetAnimationLoopCount(chPartAnimSegment* pAnimSeg);
	float GetAnimationStartCrement(chPartAnimSegment* pAnimSeg);
	float GetAnimationCrement(chPartAnimSegment* pAnimSeg);
	int GetAnimationNextIndex(chPartAnimSegment* pAnimSeg);

	// Helper functions to set animation 
	void SetAnimationStartFrame(chPartAnimSegment* pAnimSeg, int iValue);
	void SetAnimationEndFrame(chPartAnimSegment* pAnimSeg, int iValue);
	void SetAnimationFramerate(chPartAnimSegment* pAnimSeg, int iValue);
	void SetAnimationLoopCount(chPartAnimSegment* pAnimSeg, int iValue);
	void SetAnimationStartCrement(chPartAnimSegment* pAnimSeg, float flValue);
	void SetAnimationCrement(chPartAnimSegment* pAnimSeg, float flValue);
	void SetAnimationNextIndex(chPartAnimSegment* pAnimSeg, int iValue);
	
	int ValidAnimationStartFrame(chPartAnimSegment* pAnimSeg); // Is the start frame provided valid
	int ValidAnimationEndFrame(chPartAnimSegment* pAnimSeg); // Is the end frame provided valid
	int GetAnimationLength(chPartAnimSegment* pAnimSeg); // Return length of animation
	int ValidAnimation(chPartAnimSegment* pAnimSeg);
	float GetAnimationFrameTime(chPartAnimSegment* pAnimSeg);

	int GetNumAnimationSegments(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex, int iAnimType);

	// Helper functions for active crosshairs
	chActive* GetActiveCrosshairReference(void); // Do we need this?
	void SetActiveCrosshair(int iMainCrosshairIndex, int iSubCrosshairIndex, int iSubAutoCrosshairIndex);
	int GetActiveMainCrosshairId(void);
	void SetActiveMainCrosshair(int iMainCrosshairId);
	int GetActiveSubCrosshairIndex(void);
	void SetActiveSubCrosshair(int iSubCrosshairIndex);
	int GetActiveAutoCrosshairIndex(void);
	void SetActiveAutoCrosshair(int iAutoCrosshairIndex);

	chPartActiveVector* GetActivePartVectorReference(int iSubType);
	int GetNumActiveParts(int iSubType);
	chPartActive* GetActivePartReference(int iPartIndex, int iSubType);
	wrect_t GetActivePartRect(chPartActive* pActivePart);
	void SetActivePartRect(chPartActive* pActivePart, wrect_t rc);
	int GetActivePartAnimationIndex(chPartActive* pActivePart, int iAnimType);
	void SetActivePartAnimationIndex(chPartActive* pActivePart, int iAnimType, int iAnimIndex);
	int GetActivePartAnimationFrame(chPartActive* pActivePart, int iAnimType);
	void SetActivePartAnimationFrame(chPartActive* pActivePart, int iAnimType, int iFrame);
	void IncrementActivePartAnimationFrame(chPartActive* pActivePart, int iAnimType);
	void DecrementActivePartAnimationFrame(chPartActive* pActivePart, int iAnimType);
	float GetActivePartAnimationTime(chPartActive* pActivePart, int iAnimType);
	void SetActivePartAnimationTime(chPartActive* pActivePart, int iAnimType, float flTime);
	void DecrementActivePartAnimationTime(chPartActive* pActivePart, int iAnimType);
	int GetActivePartLoopCount(chPartActive* pActivePart, int iAnimType);
	void SetActivePartLoopCount(chPartActive* pActivePart, int iAnimType, int iLoopCount);
	void DecrementActivePartLoopCount(chPartActive* pActivePart, int iAnimType);
	void IncrementActivePartLoopCount(chPartActive* pActivePart, int iAnimType);

	int GetNumCrosshairs(void);

	void ClearActiveParts(int iSubType);
	void SetActiveParts(int iSubType);

	void AnimateParts(int iSubType);
	void ResetAnimation(int iSubType);
	void NextAnimation(int iSubType, int iPartIndex, int iAnimType);
	
	crsh* AddCrosshair(const char* szName); // Add crosshair to active crosshair database
	chPart* AddPart(chSub* pChSub);
	chPartAnimSegment* AddAnimation(chPart* pPart, int iAnimType);

	
	void InitDefaultCrosshair(void); // Hard-coded crosshairs
	void ParseCrosshairs(void); // Custom crosshairs

	int DrawHudStringAlt(int iX, int iDir, int iSubType, char* szString, int r, int g, int b, int a, int xpos, int ypos, float xscale, float yscale, int xpivot, int ypivot, float angle, float selfangle);

	int m_iMinRecoil;
	int m_iRecoil;
	int m_iMaxRecoil;

	float m_flRecoilCooldown;
	int m_iTargetSubCrosshair;
	int m_iTargetAutoCrosshair;
	int m_iTargetCrosshair;

	// Crosshair position and auto-aim position, by default, it's the center of the screen, unless auto-aim changes that
	int m_iChAdjustType;
	int m_iChx, m_iChy, m_iChxAuto, m_iChyAuto;
	int m_iChxActual, m_iChyActual, m_iChxAutoActual, m_iChyAutoActual;
	int m_iChxTarget, m_iChyTarget, m_iChxAutoTarget, m_iChyAutoTarget;

	// Logic to adjust auto-aiming position
	void AutoPositionAdjust(void);
	// Time to takes for regular and auto-crosshair to snap onto target. These timers are reset if a new target is acquired
	float m_flSnapTime, m_flSnapTimeLeft;
	float m_flAutoSnapTime, m_flAutoSnapTimeLeft;
};

class CHudAmmo: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	void Think(void);
	void Reset(void);
	int DrawWList(float flTime);
	int MsgFunc_CurWeapon(const char *pszName, int iSize, void *pbuf);
	int MsgFunc_WeaponList(const char *pszName, int iSize, void *pbuf);
	int MsgFunc_AmmoX(const char *pszName, int iSize, void *pbuf);
	int MsgFunc_AmmoPickup( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_WeapPickup( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_ItemPickup( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_HideWeapon( const char *pszName, int iSize, void *pbuf );

	void SlotInput( int iSlot );
	void _cdecl UserCmd_Slot1( void );
	void _cdecl UserCmd_Slot2( void );
	void _cdecl UserCmd_Slot3( void );
	void _cdecl UserCmd_Slot4( void );
	void _cdecl UserCmd_Slot5( void );
	void _cdecl UserCmd_Slot6( void );
	void _cdecl UserCmd_Slot7( void );
	void _cdecl UserCmd_Slot8( void );
	void _cdecl UserCmd_Slot9( void );
	void _cdecl UserCmd_Slot10( void );
	void _cdecl UserCmd_Close( void );
	void _cdecl UserCmd_NextWeapon( void );
	void _cdecl UserCmd_PrevWeapon( void );

	int recoil;
	float speenangle;
	float selfspeenangle;
	int centeroffset;
	HSPR m_hTestCH;

private:
	float m_fFade;
	RGBA  m_rgba;
	WEAPON *m_pWeapon;
	int	m_HUD_bucket0;
	int m_HUD_selection;

};

//
//-----------------------------------------------------
//

class CHudAmmoSecondary: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	void Reset( void );
	int Draw(float flTime);

	int MsgFunc_SecAmmoVal( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_SecAmmoIcon( const char *pszName, int iSize, void *pbuf );

private:
	enum {
		MAX_SEC_AMMO_VALUES = 4
	};

	int m_HUD_ammoicon; // sprite indices
	int m_iAmmoAmounts[MAX_SEC_AMMO_VALUES];
	float m_fFade;
};


#include "health.h"


#define FADE_TIME 100


//
//-----------------------------------------------------
//
class CHudGeiger: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	int MsgFunc_Geiger(const char *pszName, int iSize, void *pbuf);
	
private:
	int m_iGeigerRange;

};

//
//-----------------------------------------------------
//
class CHudTrain: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	int MsgFunc_Train(const char *pszName, int iSize, void *pbuf);

private:
	HSPR m_hSprite;
	int m_iPos;

};

//
//-----------------------------------------------------
//
// REMOVED: Vgui has replaced this.
//
/*
class CHudMOTD : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );
	void Reset( void );

	int MsgFunc_MOTD( const char *pszName, int iSize, void *pbuf );

protected:
	static int MOTD_DISPLAY_TIME;
	char m_szMOTD[ MAX_MOTD_LENGTH ];
	float m_flActiveRemaining;
	int m_iLines;
};
*/

//
//-----------------------------------------------------
//
class CHudStatusBar : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );
	void Reset( void );
	void ParseStatusString( int line_num );

	int MsgFunc_StatusText( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_StatusValue( const char *pszName, int iSize, void *pbuf );

protected:
	enum { 
		MAX_STATUSTEXT_LENGTH = 128,
		MAX_STATUSBAR_VALUES = 8,
		MAX_STATUSBAR_LINES = 2,
	};

	char m_szStatusText[MAX_STATUSBAR_LINES][MAX_STATUSTEXT_LENGTH];  // a text string describing how the status bar is to be drawn
	char m_szStatusBar[MAX_STATUSBAR_LINES][MAX_STATUSTEXT_LENGTH];	// the constructed bar that is drawn
	int m_iStatusValues[MAX_STATUSBAR_VALUES];  // an array of values for use in the status bar

	int m_bReparseString; // set to TRUE whenever the m_szStatusBar needs to be recalculated

	// an array of colors...one color for each line
	float *m_pflNameColors[MAX_STATUSBAR_LINES];
};

//
//-----------------------------------------------------
//
// REMOVED: Vgui has replaced this.
//
/*
class CHudScoreboard: public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	int Draw( float flTime );
	int DrawPlayers( int xoffset, float listslot, int nameoffset = 0, char *team = NULL ); // returns the ypos where it finishes drawing
	void UserCmd_ShowScores( void );
	void UserCmd_HideScores( void );
	int MsgFunc_ScoreInfo( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_TeamInfo( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_TeamScore( const char *pszName, int iSize, void *pbuf );
	void DeathMsg( int killer, int victim );

	int m_iNumTeams;

	int m_iLastKilledBy;
	int m_fLastKillTime;
	int m_iPlayerNum;
	int m_iShowscoresHeld;

	void GetAllPlayersInfo( void );
private:
	struct cvar_s *cl_showpacketloss;

};
*/

struct extra_player_info_t 
{
	short frags;
	short deaths;
	short playerclass;
	short teamnumber;
	char teamname[MAX_TEAM_NAME];
};

struct team_info_t 
{
	char name[MAX_TEAM_NAME];
	short frags;
	short deaths;
	short ping;
	short packetloss;
	short ownteam;
	short players;
	int already_drawn;
	int scores_overriden;
	int teamnumber;
};

extern hud_player_info_t	g_PlayerInfoList[MAX_PLAYERS+1];	   // player info from the engine
extern extra_player_info_t  g_PlayerExtraInfo[MAX_PLAYERS+1];   // additional player info sent directly to the client dll
extern team_info_t			g_TeamInfo[MAX_TEAMS+1];
extern int					g_IsSpectator[MAX_PLAYERS+1];


//
//-----------------------------------------------------
//
class CHudDeathNotice : public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	int Draw( float flTime );
	int MsgFunc_DeathMsg( const char *pszName, int iSize, void *pbuf );

private:
	int m_HUD_d_skull;  // sprite index of skull icon
};

//
//-----------------------------------------------------
//
class CHudMenu : public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	void Reset( void );
	int Draw( float flTime );
	int MsgFunc_ShowMenu( const char *pszName, int iSize, void *pbuf );

	void SelectMenuItem( int menu_item );

	int m_fMenuDisplayed;
	int m_bitsValidSlots;
	float m_flShutoffTime;
	int m_fWaitingForMore;
};

//
//-----------------------------------------------------
//
class CHudSayText : public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	int Draw( float flTime );
	int MsgFunc_SayText( const char *pszName, int iSize, void *pbuf );
	void SayTextPrint( const char *pszBuf, int iBufSize, int clientIndex = -1 );
	void EnsureTextFitsInOneLineAndWrapIfHaveTo( int line );
friend class CHudSpectator;

private:

	struct cvar_s *	m_HUD_saytext;
	struct cvar_s *	m_HUD_saytext_time;
};

//
//-----------------------------------------------------
//
class CHudBattery: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	int MsgFunc_Battery(const char *pszName,  int iSize, void *pbuf );
	
private:
	HSPR m_hSprite1;
	HSPR m_hSprite2;
	wrect_t *m_prc1;
	wrect_t *m_prc2;
	int	  m_iBat;	
	float m_fFade;
	int	  m_iHeight;		// width of the battery innards
};


//
//-----------------------------------------------------
//
class CHudFlashlight: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	void Reset( void );
	int MsgFunc_Flashlight(const char *pszName,  int iSize, void *pbuf );
	int MsgFunc_FlashBat(const char *pszName,  int iSize, void *pbuf );
	
private:
	HSPR m_hSprite1;
	HSPR m_hSprite2;
	HSPR m_hBeam;
	wrect_t *m_prc1;
	wrect_t *m_prc2;
	wrect_t *m_prcBeam;
	float m_flBat;	
	int	  m_iBat;	
	int	  m_fOn;
	float m_fFade;
	int	  m_iWidth;		// width of the battery innards
};

//
//-----------------------------------------------------
//
const int maxHUDMessages = 16;
struct message_parms_t
{
	client_textmessage_t	*pMessage;
	float	time;
	int x, y;
	int	totalWidth, totalHeight;
	int width;
	int lines;
	int lineLength;
	int length;
	int r, g, b;
	int text;
	int fadeBlend;
	float charTime;
	float fadeTime;
};

//
//-----------------------------------------------------
//

class CHudTextMessage: public CHudBase
{
public:
	int Init( void );
	static char *LocaliseTextString( const char *msg, char *dst_buffer, int buffer_size );
	static char *BufferedLocaliseTextString( const char *msg );
	char *LookupString( const char *msg_name, int *msg_dest = NULL );
	int MsgFunc_TextMsg(const char *pszName, int iSize, void *pbuf);
};

//
//-----------------------------------------------------
//

class CHudMessage: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	int MsgFunc_HudText(const char *pszName, int iSize, void *pbuf);
	int MsgFunc_GameTitle(const char *pszName, int iSize, void *pbuf);

	float FadeBlend( float fadein, float fadeout, float hold, float localTime );
	int	XPosition( float x, int width, int lineWidth );
	int YPosition( float y, int height );

	void MessageAdd( const char *pName, float time );
	void MessageAdd(client_textmessage_t * newMessage );
	void MessageDrawScan( client_textmessage_t *pMessage, float time );
	void MessageScanStart( void );
	void MessageScanNextChar( void );
	void Reset( void );

private:
	client_textmessage_t		*m_pMessages[maxHUDMessages];
	float						m_startTime[maxHUDMessages];
	message_parms_t				m_parms;
	float						m_gameTitleTime;
	client_textmessage_t		*m_pGameTitle;

	int m_HUD_title_life;
	int m_HUD_title_half;
};

//
//-----------------------------------------------------
//
#define MAX_SPRITE_NAME_LENGTH	24

class CHudStatusIcons: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	void Reset( void );
	int Draw(float flTime);
	int MsgFunc_StatusIcon(const char *pszName, int iSize, void *pbuf);

	enum { 
		MAX_ICONSPRITENAME_LENGTH = MAX_SPRITE_NAME_LENGTH,
		MAX_ICONSPRITES = 4,
	};

	
	//had to make these public so CHud could access them (to enable concussion icon)
	//could use a friend declaration instead...
	void EnableIcon( char *pszIconName, unsigned char red, unsigned char green, unsigned char blue );
	void DisableIcon( char *pszIconName );

private:

	typedef struct
	{
		char szSpriteName[MAX_ICONSPRITENAME_LENGTH];
		HSPR spr;
		wrect_t rc;
		unsigned char r, g, b;
	} icon_sprite_t;

	icon_sprite_t m_IconList[MAX_ICONSPRITES];

};

//
//-----------------------------------------------------
//



class CHud
{
private:
	HUDLIST						*m_pHudList;
	HSPR						m_hsprLogo;
	int							m_iLogo;
	client_sprite_t				*m_pSpriteList;
	int							m_iSpriteCount;
	int							m_iSpriteCountAllRes;
	float						m_flMouseSensitivity;
	int							m_iConcussionEffect; 

public:

	HSPR						m_hsprCursor;
	float m_flTime;	   // the current client time
	float m_fOldTime;  // the time at which the HUD was last redrawn
	double m_flTimeDelta; // the difference between flTime and fOldTime
	double m_flHackedDelta;
	bool deltaSet = false;
	Vector	m_vecOrigin;
	Vector	m_vecAngles;
	int		m_iKeyBits;
	int		m_iHideHUDDisplay;
	int		m_iFOV;
	int		m_Teamplay;
	int		m_iRes;
	cvar_t  *m_pCvarStealMouse;
	cvar_t	*m_pCvarDraw;

	int m_iFontHeight;
	int DrawHudNumber(int x, int y, int iFlags, int iNumber, int r, int g, int b );
	int DrawHudString(int x, int y, int iMaxX, char *szString, int r, int g, int b );
	virtual int DrawHudStringReverse(int xpos, int ypos, int iMinX, char* szString, int r, int g, int b);
	int DrawHudNumberString( int xpos, int ypos, int iMinX, int iNumber, int r, int g, int b );
	int GetNumWidth(int iNumber, int iFlags);

private:
	// the memory for these arrays are allocated in the first call to CHud::VidInit(), when the hud.txt and associated sprites are loaded.
	// freed in ~CHud()
	HSPR *m_rghSprites;	/*[HUD_SPRITE_COUNT]*/			// the sprites loaded from hud.txt
	wrect_t *m_rgrcRects;	/*[HUD_SPRITE_COUNT]*/
	char *m_rgszSpriteNames; /*[HUD_SPRITE_COUNT][MAX_SPRITE_NAME_LENGTH]*/

	struct cvar_s *default_fov;
public:
	HSPR GetSprite( int index ) 
	{
		return (index < 0) ? 0 : m_rghSprites[index];
	}

	wrect_t& GetSpriteRect( int index )
	{
		return m_rgrcRects[index];
	}

	
	int GetSpriteIndex( const char *SpriteName );	// gets a sprite index, for use in the m_rghSprites[] array

	CHudAmmo		m_Ammo;
	CHudHealth		m_Health;
	CHudSpectator		m_Spectator;
	CHudGeiger		m_Geiger;
	CHudBattery		m_Battery;
	CHudTrain		m_Train;
	CHudFlashlight	m_Flash;
	CHudMessage		m_Message;
	CHudStatusBar   m_StatusBar;
	CHudDeathNotice m_DeathNotice;
	CHudSayText		m_SayText;
	CHudMenu		m_Menu;
	CHudAmmoSecondary	m_AmmoSecondary;
	CHudTextMessage m_TextMessage;
	CHudStatusIcons m_StatusIcons;
	CHudCrosshair m_Crosshair;

	void Init( void );
	void VidInit( void );
	void Think(void);
	int Redraw( float flTime, int intermission );
	int UpdateClientData( client_data_t *cdata, float time );

	CHud() : m_iSpriteCount(0), m_pHudList(NULL) {}  
	~CHud();			// destructor, frees allocated memory

	// user messages
	int _cdecl MsgFunc_Damage(const char *pszName, int iSize, void *pbuf );
	int _cdecl MsgFunc_GameMode(const char *pszName, int iSize, void *pbuf );
	int _cdecl MsgFunc_Logo(const char *pszName,  int iSize, void *pbuf);
	int _cdecl MsgFunc_ResetHUD(const char *pszName,  int iSize, void *pbuf);
	void _cdecl MsgFunc_InitHUD( const char *pszName, int iSize, void *pbuf );
	void _cdecl MsgFunc_ViewMode( const char *pszName, int iSize, void *pbuf );
	int _cdecl MsgFunc_SetFOV(const char *pszName,  int iSize, void *pbuf);
	int  _cdecl MsgFunc_Concuss( const char *pszName, int iSize, void *pbuf );

	// Screen information
	SCREENINFO	m_scrinfo;

	int	m_iWeaponBits;
	int	m_fPlayerDead;
	int m_iIntermission;

	// sprite indexes
	int m_HUD_number_0;


	void AddHudElem(CHudBase *p);

	float GetSensitivity();

};

class TeamFortressViewport;

extern CHud gHUD;
extern TeamFortressViewport *gViewPort;

extern int g_iPlayerClass;
extern int g_iTeamNumber;
extern int g_iUser1;
extern int g_iUser2;
extern int g_iUser3;

