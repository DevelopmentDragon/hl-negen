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
// Ammo.cpp
//
// implementation of CHudAmmo class
//

#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include "pm_shared.h"

#include <string.h>
#include <stdio.h>

#include "ammohistory.h"
#include "vgui_TeamFortressViewport.h"
#include "../dlls/crosshairs.h"

DECLARE_MESSAGE(m_Crosshair, Crosshair)
DECLARE_MESSAGE(m_Crosshair, AutoAim)


float HUDScaleVertical(void)
{
	return ((float)ScreenRealHeight / (float)ScreenHeight);
}

float HUDScaleHorizontal(void)
{
	return ((float)ScreenRealWidth / (float)ScreenWidth);
}

float HUDScaleAdjustBoth(void)
{
	return (float)(ScreenRealWidth * ScreenRealHeight) / (float)(ScreenWidth * ScreenHeight);
}

int HUDScaleAdjustX(int x)
{
	return (int)((float)x * HUDScaleHorizontal());
}

int HUDScaleAdjustY(int y)
{
	return (int)((float)y * HUDScaleVertical());
}

int HUDScaleAdjustBoth(int coord)
{
	return (int)((float)coord * HUDScaleAdjustBoth());
}


// This is only ever used on initialization, do not use after game is loaded
crsh* CHudCrosshair::AddCrosshair(const char* szName)
{
	// Generate it
	crsh newCh = { "", { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {} } };
	strcpy((char*)newCh.name, szName);

	// Add it
	allCrosshairs.push_back(newCh);

	return &(allCrosshairs.at(allCrosshairs.size() - 1));
}

chPart* CHudCrosshair::AddPart(chSub* pSubCh)
{
	if (pSubCh)
	{
		chPart* newPart = (chPart*)malloc(sizeof(chPart));
		if (newPart)
		{
			newPart->parttype = 0;
			newPart->partsubtype = 0;
			strcpy((char*)newPart->spritename, "");
			newPart->partspr = 0;
			newPart->xoffset = 0;
			newPart->yoffset = 0;
			newPart->xpos = 0;
			newPart->ypos = 0;
			newPart->width = 0;
			newPart->height = 0;
			newPart->thickness = 1.0f;
			newPart->spanstart = 0.0f;
			newPart->spanend = 360.0f;
			newPart->colorflags;
			newPart->r = 255;
			newPart->g = 255;
			newPart->b = 255;
			newPart->a = 255;
			newPart->selfrotation = 0.0f;
			newPart->xpivot = 0;
			newPart->ypivot = 0;
			newPart->rotation = 0.0f;
			newPart->xscale = 1.0f;
			newPart->yscale = 1.0f;
			newPart->selfanglescale = 1.0f;
			newPart->xpivotscale = 1.0f;
			newPart->ypivotscale = 1.0f;
			newPart->anglescale = 1.0f;
			newPart->spanstartscale = 1.0f;
			newPart->spanendscale = 1.0f;
			newPart->wscale = 1.0f;
			newPart->hscale = 1.0f;
			newPart->thickscale = 1.0f;
			newPart->xinc = 0.0f;
			newPart->yinc = 0.0f;
			newPart->selfangleinc = 0.0f;
			newPart->xpivinc = 0.0f;
			newPart->ypivinc = 0.0f;
			newPart->angleinc = 0.0f;
			newPart->winc = 0.0f;
			newPart->hinc = 0.0f;
			newPart->thickinc = 0.0f;
			newPart->spanstartinc = 0.0f;
			newPart->spanendinc = 0.0f;
			pSubCh->push_back(*newPart);

			return &(pSubCh->at((int)pSubCh->size() - 1));
		}
	}

	return NULL;
}

chPartAnimSegment* CHudCrosshair::AddAnimation(chPart* pPart, int iAnimType)
{
	if (pPart)
	{
		if (ValidAnimationType(iAnimType))
		{
			chPartAnimSegment* pAnim = (chPartAnimSegment*)malloc(sizeof(chPartAnimSegment));
			if (pAnim)
			{
				pAnim->startFrame = 0;
				pAnim->endFrame = 0;
				pAnim->framerate = 0;
				pAnim->loop = 1; // Changed to 1 because 0 now skips it, negative values are infinite
				pAnim->nextPartAnim = -1;
				pAnim->crement = 0.0f;

				pPart->animations[iAnimType].push_back(*pAnim);
				return &(pPart->animations[iAnimType].at(pPart->animations[iAnimType].size() - 1));
			}
		}
	}

	return NULL;
}

// This function destroys all current active parts
void CHudCrosshair::ClearActiveParts(int iSubType)
{
	if (iSubType & CH_SUB_NORM)
	{
		if (GetNumActiveParts(iSubType) > 0)
			activeCrosshair.parts.clear();
	}

	if (iSubType & CH_SUB_AUTO)
	{
		if (GetNumActiveParts(iSubType) > 0)
			activeCrosshair.autoparts.clear();
	}
}

// allCrosshairs must always be initialized for this to work
int CHudCrosshair::GetNumCrosshairs(void)
{
	return (int)allCrosshairs.size();
}

// Check for validity of main crosshair index
int CHudCrosshair::ValidMainCrosshairId(int iMainCrosshairId)
{
	if (iMainCrosshairId > -1 && iMainCrosshairId < GetNumCrosshairs())
		return 1;

	return 0;
}

// Check for validy of sub crosshair index
int CHudCrosshair::ValidSubCrosshairIndex(int iSubCrosshairIndex)
{
	return (iSubCrosshairIndex > -1 && iSubCrosshairIndex < CHSB_TOTAL) ? 1 : 0;
}

// Is the part provided valid?
int CHudCrosshair::ValidPartIndex(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex)
{
	if (ValidMainCrosshairId(iMainCrosshairId) && ValidSubCrosshairIndex(iSubCrosshairIndex))
	{
		if (iPartIndex > -1 && iPartIndex < (int)(allCrosshairs.at(iMainCrosshairId).subs[iSubCrosshairIndex].size()))
			return 1;
	}

	return 0;
}

// Is this a valid animation type
int CHudCrosshair::ValidAnimationType(int iAnimType)
{
	return (iAnimType > -1 && iAnimType < CHA_TOTAL) ? 1 : 0;
}

// Is this a valid animation
int CHudCrosshair::ValidAnimationIndex(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex, int iAnimType, int iAnimIndex)
{
	if (ValidPartIndex(iMainCrosshairId, iSubCrosshairIndex, iPartIndex) && ValidAnimationType(iAnimType))
	{
		if (iAnimIndex > -1 && iAnimIndex < (int)(allCrosshairs.at(iMainCrosshairId).subs[iSubCrosshairIndex].at(iPartIndex).animations[iAnimType].size()))
			return 1;
	}

	return 0;
}

// Get pointer to crosshair
crsh* CHudCrosshair::GetCrosshairReference(int iMainCrosshairId)
{
	if (ValidMainCrosshairId(iMainCrosshairId))
		return &(allCrosshairs.at(iMainCrosshairId));

	return NULL;
}

// Get pointer to sub crosshair
chSub* CHudCrosshair::GetSubCrosshairReference(int iMainCrosshairId, int iSubCrosshairIndex)
{
	if (ValidMainCrosshairId(iMainCrosshairId) && ValidSubCrosshairIndex(iSubCrosshairIndex))
		return &(allCrosshairs.at(iMainCrosshairId).subs[iSubCrosshairIndex]);

	return NULL;
}

// Get pointer to part
chPart* CHudCrosshair::GetPartReference(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex)
{
	if (ValidPartIndex(iMainCrosshairId, iSubCrosshairIndex, iPartIndex))
		return &(allCrosshairs.at(iMainCrosshairId).subs[iSubCrosshairIndex].at(iPartIndex));

	return NULL;
}

// Get pointer to animation vector
chPartAnimSegmentVector* CHudCrosshair::GetAnimationVectorReference(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex, int iAnimType)
{
	if (ValidPartIndex(iMainCrosshairId, iSubCrosshairIndex, iPartIndex) && ValidAnimationType(iAnimType))
		return &(allCrosshairs.at(iMainCrosshairId).subs[iSubCrosshairIndex].at(iPartIndex).animations[iAnimType]);

	return NULL;
}

int CHudCrosshair::GetNumAnimationSegments(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex, int iAnimType)
{
	int result = 0;

	if (ValidPartIndex(iMainCrosshairId, iSubCrosshairIndex, iPartIndex) && ValidAnimationType(iAnimType))
		return allCrosshairs.at(iMainCrosshairId).subs[iSubCrosshairIndex].at(iPartIndex).animations[iAnimType].size();

	return result;
}

// Get pointer to animation segment
chPartAnimSegment* CHudCrosshair::GetAnimationReference(int iMainCrosshairId, int iSubCrosshairIndex, int iPartIndex, int iAnimType, int iAnimIndex)
{
	if (ValidAnimationIndex(iMainCrosshairId, iSubCrosshairIndex, iPartIndex, iAnimType, iAnimIndex))
		return &(allCrosshairs.at(iMainCrosshairId).subs[iSubCrosshairIndex].at(iPartIndex).animations[iAnimType].at(iAnimIndex));

	return NULL;
}

int CHudCrosshair::GetNumParts(chSub* pSub)
{
	int result = 0;

	if (pSub)
		result = (int)pSub->size();

	return result;
}

int CHudCrosshair::GetNumParts(int iMainCrosshairId, int iSubCrosshairIndex)
{
	chSub* pSub = GetSubCrosshairReference(iMainCrosshairId, iSubCrosshairIndex);

	return GetNumParts(pSub);
}

int CHudCrosshair::GetNumAnimationSegments(chPart* pPart, int iAnimType)
{
	int result = 0;

	if (pPart)
		result = (int)pPart->animations[iAnimType].size();

	return result;
}


// Automatically acquires the active parts based on crosshair and sub crosshair ids
void CHudCrosshair::SetActiveParts(int iSubType)
{
	// Always clear first
	ClearActiveParts(iSubType);

	int iChMain = GetActiveMainCrosshairId();
	int iChSub = GetActiveSubCrosshairIndex();
	int iChAuto = GetActiveAutoCrosshairIndex();

	// Check for validity and set to appropriate failsafes
	if (!ValidMainCrosshairId(iChMain) || (!ValidSubCrosshairIndex(iChSub) && !ValidSubCrosshairIndex(iChAuto)))
	{
		SetActiveMainCrosshair(0);
		SetActiveSubCrosshair(0);
		SetActiveAutoCrosshair(0);
		return;
	}

	// This is only hit if other things are valid
	SetActiveMainCrosshair(iChMain);
	SetActiveSubCrosshair((ValidSubCrosshairIndex(iChSub)) ? iChSub : 0);
	SetActiveAutoCrosshair((ValidSubCrosshairIndex(iChAuto)) ? iChAuto : 0);

	if (iSubType & CH_SUB_NORM && !ValidSubCrosshairIndex(iChSub)) iSubType -= CH_SUB_NORM;
	if (iSubType & CH_SUB_AUTO && !ValidSubCrosshairIndex(iChAuto)) iSubType -= CH_SUB_AUTO;

	int iMin = (iSubType & CH_SUB_NORM) ? CH_SUB_NORM : CH_SUB_AUTO;
	int iMax = (iSubType & CH_SUB_AUTO) ? CH_SUB_AUTO + 1 : CH_SUB_AUTO;

	for (int i2 = iMin; i2 < iMax; i2++)
	{
		int chid = iChMain;
		int chsubid = (i2 == CH_SUB_NORM) ? iChAuto : iChSub;

		chSub* pSub = GetSubCrosshairReference(chid, chsubid);

		if (pSub)
		{
			// Perform the magic to switch crosshair parts
			for (int i = 0; i < GetNumParts(pSub); i++)
			{
				chPart* pPart = GetPartReference(chid, chsubid, i);
				if (pPart)
				{
					chPartActive insertActive = {
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_FRAME, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_RED, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_GREEN, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_BLUE, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_ALPHA, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_XOFFSET, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_YOFFSET, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_XSCALE, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_YSCALE, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_THICK, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_SPANSTART, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_SPANEND, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_XPIVOT, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_YPIVOT, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_SELFROTATE, 0)),
							GetAnimationLoopCount(GetAnimationReference(chid, chsubid, i, CHA_ROTATE, 0)),
						},
						{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
						SPR_Load(GetPartSpriteName(pPart))
					};

					if (i2 == CH_SUB_AUTO)
						activeCrosshair.autoparts.push_back(insertActive);

					if (i2 == CH_SUB_NORM)
						activeCrosshair.parts.push_back(insertActive);
				}
			}
		}
	}
}

int CHudCrosshair::GetPartType(chPart* pPart)
{
	if (pPart)
		return pPart->parttype;

	return 0;
}

int CHudCrosshair::GetPartSubType(chPart* pPart)
{
	if (pPart)
		return pPart->partsubtype;

	return 0;
}

const char* CHudCrosshair::GetPartSpriteName(chPart* pPart)
{
	if (pPart)
		return pPart->spritename;

	return NULL;
}

HSPR CHudCrosshair::GetPartSprite(chPart* pPart)
{
	if (pPart)
		return pPart->partspr;

	return 0;
}

int CHudCrosshair::GetPartXOffset(chPart* pPart)
{
	if (pPart)
		return pPart->xoffset;

	return 0;
}

int CHudCrosshair::GetPartYOffset(chPart* pPart)
{
	if (pPart)
		return pPart->yoffset;

	return 0;
}

int CHudCrosshair::GetPartXPosition(chPart* pPart)
{
	if (pPart)
		return pPart->xpos;

	return 0;
}

int CHudCrosshair::GetPartYPosition(chPart* pPart)
{
	if (pPart)
		return pPart->ypos;

	return 0;
}

int CHudCrosshair::GetPartHeight(chPart* pPart)
{
	if (pPart)
		return pPart->height;

	return 0;
}

int CHudCrosshair::GetPartWidth(chPart* pPart)
{
	if (pPart)
		return pPart->width;

	return 0;
}

float CHudCrosshair::GetPartThickness(chPart* pPart)
{
	if (pPart)
		return pPart->thickness;

	return 1.0f;
}

float CHudCrosshair::GetPartSpanStart(chPart* pPart)
{
	if (pPart)
		return pPart->spanstart;

	return 0.0f;
}

float CHudCrosshair::GetPartSpanEnd(chPart* pPart)
{
	if (pPart)
		return pPart->spanend;

	return 360.0f;
}

int CHudCrosshair::GetPartColorFlags(chPart* pPart)
{
	if (pPart)
		return pPart->colorflags;

	return 0;
}

int CHudCrosshair::GetPartRed(chPart* pPart)
{
	if (pPart)
		return pPart->r;

	return 0;
}

int CHudCrosshair::GetPartGreen(chPart* pPart)
{
	if (pPart)
		return pPart->g;

	return 0;
}

int CHudCrosshair::GetPartBlue(chPart* pPart)
{
	if (pPart)
		return pPart->b;

	return 0;
}

int CHudCrosshair::GetPartAlpha(chPart* pPart)
{
	if (pPart)
		return pPart->a;

	return 0;
}

float CHudCrosshair::GetPartSelfRotation(chPart* pPart)
{
	if (pPart)
		return pPart->selfrotation;

	return 0.0f;
}

int CHudCrosshair::GetPartXPivot(chPart* pPart)
{
	if (pPart)
		return pPart->xpivot;

	return 0;
}

int CHudCrosshair::GetPartYPivot(chPart* pPart)
{
	if (pPart)
		return pPart->ypivot;

	return 0;
}


float CHudCrosshair::GetPartRotation(chPart* pPart)
{
	if (pPart)
		return pPart->rotation;

	return 0.0f;
}

float CHudCrosshair::GetPartXScale(chPart* pPart)
{
	if (pPart)
		return pPart->xscale;

	return 1.0f;
}

float CHudCrosshair::GetPartYScale(chPart* pPart)
{
	if (pPart)
		return pPart->yscale;

	return 1.0f;
}

float CHudCrosshair::GetPartSelfAngleScale(chPart* pPart)
{
	if (pPart)
		return pPart->selfanglescale;

	return 1.0f;
}

float CHudCrosshair::GetPartXPivotScale(chPart* pPart)
{
	if (pPart)
		return pPart->xpivotscale;

	return 1.0f;
}

float CHudCrosshair::GetPartYPivotScale(chPart* pPart)
{
	if (pPart)
		return pPart->ypivotscale;

	return 1.0f;
}

float CHudCrosshair::GetPartAngleScale(chPart* pPart)
{
	if (pPart)
		return pPart->anglescale;

	return 1.0f;
}

float CHudCrosshair::GetPartWidthScale(chPart* pPart)
{
	if (pPart)
		return pPart->wscale;

	return 1.0f;
}

float CHudCrosshair::GetPartHeightScale(chPart* pPart)
{
	if (pPart)
		return pPart->hscale;

	return 1.0f;
}

float CHudCrosshair::GetPartThicknessScale(chPart* pPart)
{
	if (pPart)
		return pPart->thickscale;

	return 1.0f;
}

float CHudCrosshair::GetPartSpanStartScale(chPart* pPart)
{
	if (pPart)
		return pPart->spanstartscale;

	return 1.0f;
}

float CHudCrosshair::GetPartSpanEndScale(chPart* pPart)
{
	if (pPart)
		return pPart->spanendscale;

	return 1.0f;
}

float CHudCrosshair::GetPartXIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->xinc;

	return 0.0f;
}

float CHudCrosshair::GetPartYIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->yinc;

	return 0.0f;
}

float CHudCrosshair::GetPartSelfAngleIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->selfangleinc;

	return 0.0f;
}

float CHudCrosshair::GetPartXPivotIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->xpivinc;

	return 0.0f;
}

float CHudCrosshair::GetPartYPivotIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->ypivinc;

	return 0.0f;
}

float CHudCrosshair::GetPartAngleIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->angleinc;

	return 0.0f;
}

float CHudCrosshair::GetPartWidthIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->winc;

	return 0.0f;
}

float CHudCrosshair::GetPartHeightIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->hinc;

	return 0.0f;
}

float CHudCrosshair::GetPartThicknessIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->thickinc;

	return 0.0f;
}

float CHudCrosshair::GetPartSpanStartIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->spanstartinc;

	return 0.0f;
}

float CHudCrosshair::GetPartSpanEndIncrement(chPart* pPart)
{
	if (pPart)
		return pPart->spanendinc;

	return 0.0f;
}

void CHudCrosshair::SetPartType(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->parttype = iValue;
	}
}

void CHudCrosshair::SetPartSubType(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->partsubtype = iValue;
	}
}

void CHudCrosshair::SetPartSpriteName(chPart* pPart, const char* szValue)
{
	if (pPart)
	{
		strcpy((char*)pPart->spritename, szValue);
	}
}

void CHudCrosshair::SetPartSprite(chPart* pPart, const char* szSpriteName)
{
	if (pPart)
		pPart->partspr = SPR_Load(szSpriteName);
}

void CHudCrosshair::SetPartXOffset(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->xoffset = iValue;
	}
}

void CHudCrosshair::SetPartYOffset(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->yoffset = iValue;
	}
}

void CHudCrosshair::SetPartXPosition(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->xpos = iValue;
	}
}

void CHudCrosshair::SetPartYPosition(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->ypos = iValue;
	}
}

void CHudCrosshair::SetPartHeight(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->height = iValue;
	}
}

void CHudCrosshair::SetPartWidth(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->width = iValue;
	}
}

void CHudCrosshair::SetPartThickness(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->thickness = flValue;
	}
}

void CHudCrosshair::SetPartSpanStart(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->spanstart = flValue;
	}
}

void CHudCrosshair::SetPartSpanEnd(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->spanend = flValue;
	}
}

void CHudCrosshair::SetPartColorFlags(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->colorflags = iValue;
	}
}

void CHudCrosshair::SetPartRed(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->r = iValue;
	}
}

void CHudCrosshair::SetPartGreen(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->g = iValue;
	}
}

void CHudCrosshair::SetPartBlue(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->b = iValue;
	}
}

void CHudCrosshair::SetPartAlpha(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->a = iValue;
	}
}

void CHudCrosshair::SetPartSelfRotation(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->selfrotation = flValue;
	}
}

void CHudCrosshair::SetPartXPivot(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->xpivot = iValue;
	}
}

void CHudCrosshair::SetPartYPivot(chPart* pPart, int iValue)
{
	if (pPart)
	{
		pPart->ypivot = iValue;
	}
}

void CHudCrosshair::SetPartRotation(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->rotation = flValue;
	}
}

void CHudCrosshair::SetPartXScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->xscale = flValue;
	}
}

void CHudCrosshair::SetPartYScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->yscale = flValue;
	}
}

void CHudCrosshair::SetPartSelfAngleScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->selfanglescale = flValue;
	}
}

void CHudCrosshair::SetPartXPivotScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->xpivotscale = flValue;
	}
}

void CHudCrosshair::SetPartYPivotScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->ypivotscale = flValue;
	}
}

void CHudCrosshair::SetPartAngleScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->anglescale = flValue;
	}
}

void CHudCrosshair::SetPartWidthScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->wscale = flValue;
	}
}

void CHudCrosshair::SetPartHeightScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->hscale = flValue;
	}
}

void CHudCrosshair::SetPartThicknessScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->thickscale = flValue;
	}
}

void CHudCrosshair::SetPartSpanStartScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->spanstartscale = flValue;
	}
}

void CHudCrosshair::SetPartSpanEndScale(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->spanendscale = flValue;
	}
}

void CHudCrosshair::SetPartXIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->xinc = flValue;
	}
}

void CHudCrosshair::SetPartYIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->yinc = flValue;
	}
}

void CHudCrosshair::SetPartSelfAngleIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->selfangleinc = flValue;
	}
}

void CHudCrosshair::SetPartXPivotIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->xpivinc = flValue;
	}
}

void CHudCrosshair::SetPartYPivotIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->ypivinc = flValue;
	}
}

void CHudCrosshair::SetPartAngleIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->angleinc = flValue;
	}
}

void CHudCrosshair::SetPartWidthIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->winc = flValue;
	}
}

void CHudCrosshair::SetPartHeightIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->hinc = flValue;
	}
}

void CHudCrosshair::SetPartThicknessIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->thickinc = flValue;
	}
}

void CHudCrosshair::SetPartSpanStartIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->spanstartinc = flValue;
	}
}

void CHudCrosshair::SetPartSpanEndIncrement(chPart* pPart, float flValue)
{
	if (pPart)
	{
		pPart->spanendinc = flValue;
	}
}


// Get the starting frame
int CHudCrosshair::GetAnimationStartFrame(chPartAnimSegment* pAnimSeg)
{
	if (pAnimSeg)
		return pAnimSeg->startFrame;

	return -1;
}

int CHudCrosshair::GetAnimationEndFrame(chPartAnimSegment* pAnimSeg)
{
	if (pAnimSeg)
		return pAnimSeg->endFrame;

	return -1;
}

int CHudCrosshair::GetAnimationFramerate(chPartAnimSegment* pAnimSeg)
{
	if (pAnimSeg)
		return pAnimSeg->framerate;

	return 0;
}

int CHudCrosshair::GetAnimationLoopCount(chPartAnimSegment* pAnimSeg)
{
	if (pAnimSeg)
		return pAnimSeg->loop;

	return 0;
}

float CHudCrosshair::GetAnimationStartCrement(chPartAnimSegment* pAnimSeg)
{
	if (pAnimSeg)
		return pAnimSeg->startcrement;

	return 0.0f;
}

float CHudCrosshair::GetAnimationCrement(chPartAnimSegment* pAnimSeg)
{
	if (pAnimSeg)
		return pAnimSeg->crement;

	return 0.0f;
}

int CHudCrosshair::GetAnimationNextIndex(chPartAnimSegment* pAnimSeg)
{
	int result = -1;

	if (pAnimSeg)
		result = pAnimSeg->nextPartAnim;

	return result;
}

void CHudCrosshair::SetAnimationStartFrame(chPartAnimSegment* pAnimSeg, int iValue)
{
	if (pAnimSeg)
		pAnimSeg->startFrame = iValue;
}

void CHudCrosshair::SetAnimationEndFrame(chPartAnimSegment* pAnimSeg, int iValue)
{
	if (pAnimSeg)
		pAnimSeg->endFrame = iValue;
}

void CHudCrosshair::SetAnimationFramerate(chPartAnimSegment* pAnimSeg, int iValue)
{
	if (pAnimSeg)
		pAnimSeg->framerate = iValue;
}

void CHudCrosshair::SetAnimationLoopCount(chPartAnimSegment* pAnimSeg, int iValue)
{
	if (pAnimSeg)
		pAnimSeg->loop = iValue;
}

void CHudCrosshair::SetAnimationStartCrement(chPartAnimSegment* pAnimSeg, float flValue)
{
	if (pAnimSeg)
		pAnimSeg->startcrement = flValue;
}

void CHudCrosshair::SetAnimationCrement(chPartAnimSegment* pAnimSeg, float flValue)
{
	if (pAnimSeg)
		pAnimSeg->crement = flValue;
}

void CHudCrosshair::SetAnimationNextIndex(chPartAnimSegment* pAnimSeg, int iValue)
{
	if (pAnimSeg)
		pAnimSeg->nextPartAnim = iValue;
}

// Is the start frame valid?
int CHudCrosshair::ValidAnimationStartFrame(chPartAnimSegment* pAnimSeg)
{
	int result = 0;

	if (pAnimSeg)
	{
		int startFrame = GetAnimationStartFrame(pAnimSeg);
		int endFrame = GetAnimationEndFrame(pAnimSeg);

		result = (startFrame <= endFrame && startFrame > -1);
	}

	return result;
}

// Is the end frame valid?
int CHudCrosshair::ValidAnimationEndFrame(chPartAnimSegment* pAnimSeg)
{
	int result = 0;

	if (pAnimSeg)
	{
		int startFrame = GetAnimationStartFrame(pAnimSeg);
		int endFrame = GetAnimationEndFrame(pAnimSeg);

		result = (endFrame >= endFrame && endFrame > -1);
	}

	return result;
}

int CHudCrosshair::ValidAnimation(chPartAnimSegment* pAnimSeg)
{
	return (ValidAnimationStartFrame(pAnimSeg) & ValidAnimationEndFrame(pAnimSeg));
}

int CHudCrosshair::GetAnimationLength(chPartAnimSegment* pAnimSeg)
{
	if (ValidAnimation(pAnimSeg))
	{
		int startFrame = GetAnimationStartFrame(pAnimSeg);
		int endFrame = GetAnimationEndFrame(pAnimSeg);

		return (endFrame - startFrame) + 1;
	}

	return 0;
}

float CHudCrosshair::GetAnimationFrameTime(chPartAnimSegment* pAnimSeg)
{
	float animLength = GetAnimationLength(pAnimSeg);
	float framerate = GetAnimationFramerate(pAnimSeg);

	if (animLength != 0 && framerate != 0)
		return (((float)animLength / fabs((float)framerate)) / (float)animLength);

	return 0;
}

// Start all animations
void CHudCrosshair::ResetAnimation(int iSubType)
{
	int iChMain = GetActiveMainCrosshairId();
	int iChSub = GetActiveSubCrosshairIndex();
	int iChAuto = GetActiveAutoCrosshairIndex();

	// Check for validity and set to appropriate failsafes
	if (!ValidMainCrosshairId(iChMain) || (!ValidSubCrosshairIndex(iChSub) && !ValidSubCrosshairIndex(iChAuto)))
	{
		// Validity checks
		return;
	}

	// This is only hit if other things are valid
	if (iSubType & CH_SUB_NORM && !ValidSubCrosshairIndex(iChSub)) iSubType -= CH_SUB_NORM;
	if (iSubType & CH_SUB_AUTO && !ValidSubCrosshairIndex(iChAuto)) iSubType -= CH_SUB_AUTO;

	int iMin = (iSubType & CH_SUB_NORM) ? CH_SUB_NORM : CH_SUB_AUTO;
	int iMax = (iSubType & CH_SUB_AUTO) ? CH_SUB_AUTO + 1 : CH_SUB_AUTO;

	for (int i2 = iMin; i2 < iMax; i2++)
	{
		// Get all needed references
		int iMainCrosshairId = iChMain;
		int iSubCrosshairIndex = (i2 == CH_SUB_NORM) ? iChSub : iChAuto;
		crsh* pChRef = GetCrosshairReference(iMainCrosshairId);
		chSub* pSubChRef = GetSubCrosshairReference(iMainCrosshairId, iSubCrosshairIndex);
		chActive* pActiveChRef = GetActiveCrosshairReference();

		// Engage failsafes
		if (!pChRef || !pSubChRef || !pActiveChRef)
			return;

		// Loop through, lack of active parts is covered by GetNumActiveParts()
		for (int iActivePart = 0; iActivePart < GetNumActiveParts(i2); iActivePart++)
		{
			// Get all needed references
			chPart* pPartRef = GetPartReference(iMainCrosshairId, iSubCrosshairIndex, iActivePart);
			chPartActive* pActivePartRef = GetActivePartReference(iActivePart, i2);

			// Engage failsafes
			if (!pPartRef || !pActivePartRef)
				continue;

			for (int iAnimType = 0; iAnimType < CHA_TOTAL; iAnimType++)
			{
				// Get all needed references
				int iNumSegs = GetNumAnimationSegments(iMainCrosshairId, iSubCrosshairIndex, iActivePart, iAnimType);
				if (iNumSegs > 0)
				{
					chPartAnimSegment* pAnimRef = GetAnimationReference(iMainCrosshairId, iSubCrosshairIndex, iActivePart, iAnimType, 0);

					// Engage failsafes
					if (!pAnimRef)
						goto failanimreset;

					int iFrameRate = GetAnimationFramerate(pAnimRef);

					int iFrame = 0;
					if (iFrameRate < 0)
						iFrame = GetAnimationEndFrame(pAnimRef);
					else
						iFrame = GetAnimationStartFrame(pAnimRef);

					// Set the stuff
					SetActivePartAnimationFrame(pActivePartRef, iAnimType, iFrame);
					SetActivePartAnimationIndex(pActivePartRef, iAnimType, 0);
					SetActivePartAnimationTime(pActivePartRef, iAnimType, GetAnimationFrameTime(pAnimRef));
					SetActivePartLoopCount(pActivePartRef, iAnimType, GetAnimationLoopCount(pAnimRef));
				}
				else
				{
				failanimreset:
					// Set the stuff
					SetActivePartAnimationFrame(pActivePartRef, iAnimType, -1);
					SetActivePartAnimationIndex(pActivePartRef, iAnimType, -1);
					SetActivePartAnimationTime(pActivePartRef, iAnimType, -1.0f);
					SetActivePartLoopCount(pActivePartRef, iAnimType, -2);
				}

			}
		}
	}
}

// Move to the next animation once we're done
void CHudCrosshair::NextAnimation(int iSubType, int iPartIndex, int iAnimType)
{
	int iChMain = GetActiveMainCrosshairId();
	int iChSub = GetActiveSubCrosshairIndex();
	int iChAuto = GetActiveAutoCrosshairIndex();

	// Check for validity and set to appropriate failsafes
	if (!ValidMainCrosshairId(iChMain) || (!ValidSubCrosshairIndex(iChSub) && !ValidSubCrosshairIndex(iChAuto)))
	{
		// Validity checks
		return;
	}

	// This is only hit if other things are valid
	if (iSubType & CH_SUB_NORM && !ValidSubCrosshairIndex(iChSub)) iSubType -= CH_SUB_NORM;
	if (iSubType & CH_SUB_AUTO && !ValidSubCrosshairIndex(iChAuto)) iSubType -= CH_SUB_AUTO;

	int iMin = (iSubType & CH_SUB_NORM) ? CH_SUB_NORM : CH_SUB_AUTO;
	int iMax = (iSubType & CH_SUB_AUTO) ? CH_SUB_AUTO + 1 : CH_SUB_AUTO;

	for (int i2 = iMin; i2 < iMax; i2++)
	{
		// Get all needed references
		int iMainCrosshairId = iChMain;
		int iSubCrosshairIndex = (i2 == 1) ? iChSub : iChAuto;
		chPart* pPart = GetPartReference(iMainCrosshairId, iSubCrosshairIndex, iPartIndex);
		chPartActive* pActivePart = GetActivePartReference(iPartIndex, i2);

		// Engage failsafes
		if (!pPart || !pActivePart)
			continue;

		// Get some additional references
		int iCurAnimIndex = GetActivePartAnimationIndex(pActivePart, iAnimType);
		chPartAnimSegment* pCurAnim = GetAnimationReference(iMainCrosshairId, iSubCrosshairIndex, iPartIndex, iAnimType, iCurAnimIndex);
		int iNextAnim = GetAnimationNextIndex(pCurAnim);
		chPartAnimSegment* pNextAnim = GetAnimationReference(iMainCrosshairId, iSubCrosshairIndex, iPartIndex, iAnimType, iNextAnim);

		// Engage failsafes
		if (!pCurAnim)
			continue;

		// Some additional info you may need
		int iNumLoops = GetAnimationLoopCount(pCurAnim);
		int iNumActiveLoops = GetActivePartLoopCount(pActivePart, iAnimType);
		bool bDecremented = false;

		// Catch for identical animation or missing next animation
		if (iCurAnimIndex == iNextAnim || !pNextAnim || iNumActiveLoops > 0 || iNumLoops < 0)
		{
			if (iNumActiveLoops > 0 && iNumLoops > 0)
			{
				DecrementActivePartLoopCount(pActivePart, iAnimType);
				bDecremented = true;
			}
			pNextAnim = pCurAnim;
		}

		// Set stuff
		if (!bDecremented)
		{
			SetActivePartAnimationIndex(pActivePart, iAnimType, iNextAnim);
			SetActivePartAnimationTime(pActivePart, iAnimType, GetAnimationFrameTime(pNextAnim));
			SetActivePartLoopCount(pActivePart, iAnimType, GetAnimationLoopCount(pNextAnim));
		}

		// Since this called either way, do it
		int iSetFrame = GetAnimationStartFrame(pNextAnim);
		if (GetAnimationFramerate(pNextAnim) < 0)
			iSetFrame = GetAnimationEndFrame(pNextAnim);
		SetActivePartAnimationFrame(pActivePart, iAnimType, iSetFrame);
	}
}

// Animate the crosshair by looping over the parts
void CHudCrosshair::AnimateParts(int iSubType)
{
	// If the game is paused, do not animate parts
	if (gHUD.m_flTimeDelta <= 0)
		return;

	// If we're experiencing recoil, freeze it in place
	if (m_iRecoil != 0)
		return;

	int iChMain = GetActiveMainCrosshairId();
	int iChSub = GetActiveSubCrosshairIndex();
	int iChAuto = GetActiveAutoCrosshairIndex();

	// Check for validity and set to appropriate failsafes
	if (!ValidMainCrosshairId(iChMain) || (!ValidSubCrosshairIndex(iChSub) && !ValidSubCrosshairIndex(iChAuto)))
	{
		// Validity checks
		return;
	}

	// This is only hit if other things are valid
	if (iSubType & CH_SUB_NORM && !ValidSubCrosshairIndex(iChSub)) iSubType -= CH_SUB_NORM;
	if (iSubType & CH_SUB_AUTO && !ValidSubCrosshairIndex(iChAuto)) iSubType -= CH_SUB_AUTO;

	int iMin = (iSubType & CH_SUB_NORM) ? CH_SUB_NORM : CH_SUB_AUTO;
	int iMax = (iSubType & CH_SUB_AUTO) ? CH_SUB_AUTO + 1 : CH_SUB_AUTO;

	for (int i2 = iMin; i2 < iMax; i2++)
	{
		int iMainCrosshairId = iChMain;
		int iSubCrosshairIndex = (i2 == CH_SUB_NORM) ? iChSub : iChAuto;
		crsh* pChRef = GetCrosshairReference(iMainCrosshairId);
		chSub* pSubChRef = GetSubCrosshairReference(iMainCrosshairId, iSubCrosshairIndex);
		chActive* pActiveChRef = GetActiveCrosshairReference();

		// Engage failsafes
		if (!pChRef || !pSubChRef || !pActiveChRef)
			continue;

		// Loop through, lack of active parts is covered by GetNumActiveParts()
		for (int iActivePart = 0; iActivePart < GetNumActiveParts(i2); iActivePart++)
		{
			// Get all needed references
			chPart* pPartRef = GetPartReference(iMainCrosshairId, iSubCrosshairIndex, iActivePart);
			chPartActive* pActivePartRef = GetActivePartReference(iActivePart, i2);

			// Engage failsafes
			if (!pPartRef || !pActivePartRef)
				continue;

			for (int iAnimType = 0; iAnimType < CHA_TOTAL; iAnimType++)
			{
				// Get all needed references
				int iAnimIndex = GetActivePartAnimationIndex(pActivePartRef, iAnimType);

				chPartAnimSegment* pAnimRef = GetAnimationReference(iMainCrosshairId, iSubCrosshairIndex, iActivePart, iAnimType, iAnimIndex);

				// Engage failsafes
				if (!pAnimRef || iAnimIndex == CH_ANIM_INDEX_INVALID)
					continue;

				// Failsafe for if animation doesn't an appropriate loop count
				if (GetAnimationLoopCount(pAnimRef) == 0)
				{
					goto moveon;
				}

				// Decrement timer
				DecrementActivePartAnimationTime(pActivePartRef, iAnimType);

				if (GetActivePartAnimationTime(pActivePartRef, iAnimType) <= 0.0f)
				{
					bool resetTimer = false;
					bool nextAnim = false;

					if (GetAnimationFramerate(pAnimRef) != 0.0f)
					{
						if (GetAnimationFramerate(pAnimRef) > 0)
						{
							IncrementActivePartAnimationFrame(pActivePartRef, iAnimType);
							if (GetActivePartAnimationFrame(pActivePartRef, iAnimType) >= GetAnimationLength(pAnimRef))
								nextAnim = true;
							else
								resetTimer = true;
						}
						else if (GetAnimationFramerate(pAnimRef) < 0)
						{
							DecrementActivePartAnimationFrame(pActivePartRef, iAnimType);
							if (GetActivePartAnimationFrame(pActivePartRef, iAnimType) < 0)
								nextAnim = true;
							else
								resetTimer = true;
						}
					}

					if (resetTimer)
					{
						SetActivePartAnimationTime(pActivePartRef, iAnimType, GetAnimationFrameTime(pAnimRef));
						float flFrameTime = GetAnimationFrameTime(pAnimRef);
					}

					if (nextAnim)
					{
					moveon:
						NextAnimation(i2, iActivePart, iAnimType);
					}
				}
			}
		}
	}
}

chActive* CHudCrosshair::GetActiveCrosshairReference(void)
{
	return &activeCrosshair;
}

// Set main crosshair
void CHudCrosshair::SetActiveMainCrosshair(int iMainCrosshairId)
{
	activeCrosshair.id = iMainCrosshairId;
}

int CHudCrosshair::GetActiveMainCrosshairId(void)
{
	return activeCrosshair.id;
}

// Set sub crosshair
void CHudCrosshair::SetActiveSubCrosshair(int iSubCrosshairIndex)
{
	activeCrosshair.sub_id = iSubCrosshairIndex;
}

int CHudCrosshair::GetActiveSubCrosshairIndex(void)
{
	return activeCrosshair.sub_id;
}

void CHudCrosshair::SetActiveAutoCrosshair(int iAutoCrosshairIndex)
{
	activeCrosshair.auto_id = iAutoCrosshairIndex;
}

int CHudCrosshair::GetActiveAutoCrosshairIndex(void)
{
	return activeCrosshair.auto_id;
}

// Set main and sub crosshair
void CHudCrosshair::SetActiveCrosshair(int iMainCrosshairId, int iSubCrosshairIndex, int iAutoCrosshairIndex)
{
	SetActiveMainCrosshair(iMainCrosshairId);
	SetActiveSubCrosshair(iSubCrosshairIndex);
	SetActiveAutoCrosshair(iAutoCrosshairIndex);
	SetActiveParts(CH_SUB_ALL);
	ResetAnimation(CH_SUB_ALL);
}

chPartActiveVector* CHudCrosshair::GetActivePartVectorReference(int iSubType)
{
	if (iSubType == CH_SUB_NORM)
	{
		return &(activeCrosshair.parts);
	}

	if (iSubType == CH_SUB_AUTO)
	{
		return &(activeCrosshair.autoparts);
	}

	return NULL;
}

// Get number of active parts for the crosshair
int CHudCrosshair::GetNumActiveParts(int iSubType)
{
	int result = 0;

	int iMin = (iSubType & CH_SUB_NORM) ? CH_SUB_NORM : CH_SUB_AUTO;
	int iMax = (iSubType & CH_SUB_AUTO) ? CH_SUB_AUTO + 1 : CH_SUB_AUTO;

	for (int iType = iMin; iType < iMax; iType++)
	{
		chPartActiveVector* pVector = GetActivePartVectorReference(iType);

		if (pVector)
			result += (int)pVector->size();
	}

	return result;
}

// Return reference to active part
chPartActive* CHudCrosshair::GetActivePartReference(int iPartIndex, int iSubType)
{
	if (iSubType == CH_SUB_NORM)
	{
		if (iPartIndex > -1 && iPartIndex < GetNumActiveParts(iSubType))
			return &(activeCrosshair.parts.at(iPartIndex));
	}

	if (iSubType == CH_SUB_AUTO)
	{
		if (iPartIndex > -1 && iPartIndex < GetNumActiveParts(iSubType))
			return &(activeCrosshair.autoparts.at(iPartIndex));
	}

	return NULL;
}

// Get reference to sprite
wrect_t CHudCrosshair::GetActivePartRect(chPartActive* pActivePart)
{
	if (pActivePart)
		return pActivePart->partrc;

	return { 0,0,0,0 };
}

// Set active part sprite
void CHudCrosshair::SetActivePartRect(chPartActive* pActivePart, wrect_t rc)
{
	if (pActivePart)
		pActivePart->partrc = rc;
}

int CHudCrosshair::GetActivePartAnimationIndex(chPartActive* pActivePart, int iAnimType)
{
	int iResult = -1;

	if (pActivePart)
	{
		//ConsolePrint("Found!\n");
		iResult = pActivePart->animindex[iAnimType];
	}

	return iResult;
}

void CHudCrosshair::SetActivePartAnimationIndex(chPartActive* pActivePart, int iAnimType, int iAnimIndex)
{
	if (pActivePart)
		pActivePart->animindex[iAnimType] = iAnimIndex;
}

int CHudCrosshair::GetActivePartAnimationFrame(chPartActive* pActivePart, int iAnimType)
{
	int iResult = -1;

	if (pActivePart)
		iResult = pActivePart->animframe[iAnimType];

	return iResult;
}

void CHudCrosshair::SetActivePartAnimationFrame(chPartActive* pActivePart, int iAnimType, int iFrame)
{
	if (pActivePart)
		pActivePart->animframe[iAnimType] = iFrame;
}

void CHudCrosshair::IncrementActivePartAnimationFrame(chPartActive* pActivePart, int iAnimType)
{
	if (pActivePart)
		SetActivePartAnimationFrame(pActivePart, iAnimType, GetActivePartAnimationFrame(pActivePart, iAnimType) + 1);
}

void CHudCrosshair::DecrementActivePartAnimationFrame(chPartActive* pActivePart, int iAnimType)
{
	if (pActivePart)
		SetActivePartAnimationFrame(pActivePart, iAnimType, GetActivePartAnimationFrame(pActivePart, iAnimType) - 1);
}

float CHudCrosshair::GetActivePartAnimationTime(chPartActive* pActivePart, int iAnimType)
{
	float flResult = -1.0f;

	if (pActivePart)
		flResult = pActivePart->animtime[iAnimType];

	return flResult;
}

void CHudCrosshair::SetActivePartAnimationTime(chPartActive* pActivePart, int iAnimType, float flTime)
{
	if (pActivePart)
		pActivePart->animtime[iAnimType] = flTime;
}

void CHudCrosshair::DecrementActivePartAnimationTime(chPartActive* pActivePart, int iAnimType)
{
	if (pActivePart)
		SetActivePartAnimationTime(pActivePart, iAnimType, max(0.0f, GetActivePartAnimationTime(pActivePart, iAnimType) - gHUD.m_flHackedDelta));
}

int CHudCrosshair::GetActivePartLoopCount(chPartActive* pActivePart, int iAnimType)
{
	int result = 0;

	if (pActivePart)
		result = pActivePart->animloop[iAnimType];

	return result;
}

void CHudCrosshair::SetActivePartLoopCount(chPartActive* pActivePart, int iAnimType, int iLoopCount)
{
	if (pActivePart)
		pActivePart->animloop[iAnimType] = iLoopCount;
}

void CHudCrosshair::DecrementActivePartLoopCount(chPartActive* pActivePart, int iAnimType)
{
	if (pActivePart)
		pActivePart->animloop[iAnimType] -= 1;
}

void CHudCrosshair::IncrementActivePartLoopCount(chPartActive* pActivePart, int iAnimType)
{
	if (pActivePart)
		pActivePart->animloop[iAnimType] += 1;
}


// This is way less prone to cause compiler issues, yeah...
void CHudCrosshair::InitDefaultCrosshair(void)
{
	// Null crosshair must also be initialized
	crsh* pNullCh = AddCrosshair("null_crosshair");

	// Add system default crosshair 
	crsh* pCh = AddCrosshair("system_default");

	// Normal crosshair
	chSub* pSubNormal = GetSubCrosshairReference(1, CHSB_NORMAL);
	chSub* pSubNormalDeny = GetSubCrosshairReference(1, CHSB_NORMAL_DENY);
	chSub* pSubAim = GetSubCrosshairReference(1, CHSB_AIM);
	chSub* pSubAimDeny = GetSubCrosshairReference(1, CHSB_AIM_DENY);
	chSub* pSubZoom = GetSubCrosshairReference(1, CHSB_ZOOM);
	chSub* pSubZoomDeny = GetSubCrosshairReference(1, CHSB_ZOOM_DENY);
	chSub* pSubZoomAim = GetSubCrosshairReference(1, CHSB_ZOOM_AIM);
	chSub* pSubZoomAimDeny = GetSubCrosshairReference(0, CHSB_ZOOM_AIM_DENY);
	chSub* pSubAuto = GetSubCrosshairReference(1, CHSB_AUTO);
	chSub* pSubAutoAim = GetSubCrosshairReference(1, CHSB_AUTO_AIM);
	chSub* pSubAutoLock = GetSubCrosshairReference(1, CHSB_AUTO_LOCK);

	// Normal Crosshair
	chPart* pPartNormalRight = AddPart(pSubNormal);
	if (pPartNormalRight)
	{
		pPartNormalRight->parttype = CHPT_LINE;
		pPartNormalRight->partsubtype = LSHAPE_RADIUS;
		pPartNormalRight->xoffset = 5;
		pPartNormalRight->width = 10;
		pPartNormalRight->height = 10;
		pPartNormalRight->thickness = 1.0f;
		pPartNormalRight->xinc = 1.0f;
		pPartNormalRight->yinc = 0.0f;
		pPartNormalRight->selfangleinc = 0.0f;
		pPartNormalRight->xpivinc = 0.0f;
		pPartNormalRight->ypivinc = 0.0f;
		pPartNormalRight->angleinc = 0.0f;
		pPartNormalRight->winc = 0.0f;
		pPartNormalRight->hinc = 0.0f;
		pPartNormalRight->thickinc = 0.0f;
	}

	chPart* pPartNormalDown = AddPart(pSubNormal);
	if (pPartNormalDown)
	{
		pPartNormalDown->parttype = CHPT_LINE;
		pPartNormalDown->partsubtype = LSHAPE_RADIUS;
		pPartNormalDown->xoffset = 5;
		pPartNormalDown->width = 10;
		pPartNormalDown->height = 10;
		pPartNormalDown->thickness = 1.0f;
		pPartNormalDown->rotation = 90.0f;
		pPartNormalDown->xinc = 1.0f;
		pPartNormalDown->yinc = 0.0f;
		pPartNormalDown->selfangleinc = 0.0f;
		pPartNormalDown->xpivinc = 0.0f;
		pPartNormalDown->ypivinc = 0.0f;
		pPartNormalDown->angleinc = 0.0f;
		pPartNormalDown->winc = 0.0f;
		pPartNormalDown->hinc = 0.0f;
		pPartNormalDown->thickinc = 0.0f;

	}

	chPart* pPartNormalLeft = AddPart(pSubNormal);
	if (pPartNormalLeft)
	{
		pPartNormalLeft->parttype = CHPT_LINE;
		pPartNormalLeft->partsubtype = LSHAPE_RADIUS;
		pPartNormalLeft->xoffset = 5;
		pPartNormalLeft->width = 10;
		pPartNormalLeft->height = 10;
		pPartNormalLeft->thickness = 1.0f;
		pPartNormalLeft->rotation = 180.0f;
		pPartNormalLeft->xinc = 1.0f;
		pPartNormalLeft->yinc = 0.0f;
		pPartNormalLeft->selfangleinc = 0.0f;
		pPartNormalLeft->xpivinc = 0.0f;
		pPartNormalLeft->ypivinc = 0.0f;
		pPartNormalLeft->angleinc = 0.0f;
		pPartNormalLeft->winc = 0.0f;
		pPartNormalLeft->hinc = 0.0f;
		pPartNormalLeft->thickinc = 0.0f;

	}

	chPart* pPartNormalUp = AddPart(pSubNormal);
	if (pPartNormalUp)
	{
		pPartNormalUp->parttype = CHPT_LINE;
		pPartNormalUp->partsubtype = LSHAPE_RADIUS;
		pPartNormalUp->xoffset = 5;
		pPartNormalUp->width = 10;
		pPartNormalUp->height = 10;
		pPartNormalUp->thickness = 1.0f;
		pPartNormalUp->rotation = 270.0f;
		pPartNormalUp->xinc = 1.0f;
		pPartNormalUp->yinc = 0.0f;
		pPartNormalUp->selfangleinc = 0.0f;
		pPartNormalUp->xpivinc = 0.0f;
		pPartNormalUp->ypivinc = 0.0f;
		pPartNormalUp->angleinc = 0.0f;
		pPartNormalUp->winc = 0.0f;
		pPartNormalUp->hinc = 0.0f;
		pPartNormalUp->thickinc = 0.0f;

	}

	chPart* pPartAimRight = AddPart(pSubAim);
	if (pPartAimRight)
	{
		pPartAimRight->parttype = CHPT_LINE;
		pPartAimRight->partsubtype = LSHAPE_RADIUS;
		pPartAimRight->xoffset = 5;
		pPartAimRight->width = 10;
		pPartAimRight->height = 10;
		pPartAimRight->thickness = 1.0f;
		pPartAimRight->xinc = 1.0f;
		pPartAimRight->yinc = 0.0f;
		pPartAimRight->selfangleinc = 0.0f;
		pPartAimRight->xpivinc = 0.0f;
		pPartAimRight->ypivinc = 0.0f;
		pPartAimRight->angleinc = 0.0f;
		pPartAimRight->winc = 0.0f;
		pPartAimRight->hinc = 0.0f;
		pPartAimRight->thickinc = 0.0f;

		chPartAnimSegment* pAnimAimRight0 = AddAnimation(pPartAimRight, CHA_XOFFSET);
		if (pAnimAimRight0)
		{
			pAnimAimRight0->startFrame = 0;
			pAnimAimRight0->endFrame = 3; // If from a sprite, which frame do we stop at
			pAnimAimRight0->framerate = 4; // Frame rate of the animation
			pAnimAimRight0->nextPartAnim = 1;
			pAnimAimRight0->loop = 1;
			pAnimAimRight0->startcrement = 0.0f;
			pAnimAimRight0->crement = 1.0f;
		}

		chPartAnimSegment* pAnimAimRight1 = AddAnimation(pPartAimRight, CHA_XOFFSET);
		if (pAnimAimRight1)
		{
			pAnimAimRight1->startFrame = 0;
			pAnimAimRight1->endFrame = 3; // If from a sprite, which frame do we stop at
			pAnimAimRight1->framerate = 4; // Frame rate of the animation
			pAnimAimRight1->nextPartAnim = 0;
			pAnimAimRight1->loop = 1;
			pAnimAimRight1->startcrement = 3.0f;
			pAnimAimRight1->crement = -1.0f;
		}
	}

	chPart* pPartAimDown = AddPart(pSubAim);
	if (pPartAimDown)
	{
		pPartAimDown->parttype = CHPT_LINE;
		pPartAimDown->partsubtype = LSHAPE_RADIUS;
		pPartAimDown->xoffset = 5;
		pPartAimDown->width = 10;
		pPartAimDown->height = 10;
		pPartAimDown->thickness = 1.0f;
		pPartAimDown->rotation = 90.0f;
		pPartAimDown->xinc = 1.0f;
		pPartAimDown->yinc = 0.0f;
		pPartAimDown->selfangleinc = 0.0f;
		pPartAimDown->xpivinc = 0.0f;
		pPartAimDown->ypivinc = 0.0f;
		pPartAimDown->angleinc = 0.0f;
		pPartAimDown->winc = 0.0f;
		pPartAimDown->hinc = 0.0f;
		pPartAimDown->thickinc = 0.0f;

		chPartAnimSegment* pAnimAimDown0 = AddAnimation(pPartAimDown, CHA_XOFFSET);
		if (pAnimAimDown0)
		{
			pAnimAimDown0->startFrame = 0;
			pAnimAimDown0->endFrame = 3; // If from a sprite, which frame do we stop at
			pAnimAimDown0->framerate = 4; // Frame rate of the animation
			pAnimAimDown0->nextPartAnim = 1;
			pAnimAimDown0->loop = 1;
			pAnimAimDown0->startcrement = 0.0f;
			pAnimAimDown0->crement = 1.0f;
		}

		chPartAnimSegment* pAnimAimDown1 = AddAnimation(pPartAimDown, CHA_XOFFSET);
		if (pAnimAimDown1)
		{
			pAnimAimDown1->startFrame = 0;
			pAnimAimDown1->endFrame = 3; // If from a sprite, which frame do we stop at
			pAnimAimDown1->framerate = 4; // Frame rate of the animation
			pAnimAimDown1->nextPartAnim = 0;
			pAnimAimDown1->loop = 1;
			pAnimAimDown1->startcrement = 3.0f;
			pAnimAimDown1->crement = -1.0f;
		}
	}

	chPart* pPartAimLeft = AddPart(pSubAim);
	if (pPartAimLeft)
	{
		pPartAimLeft->parttype = CHPT_LINE;
		pPartAimLeft->partsubtype = LSHAPE_RADIUS;
		pPartAimLeft->xoffset = 5;
		pPartAimLeft->width = 10;
		pPartAimLeft->height = 10;
		pPartAimLeft->thickness = 1.0f;
		pPartAimLeft->rotation = 180.0f;
		pPartAimLeft->xinc = 1.0f;
		pPartAimLeft->yinc = 0.0f;
		pPartAimLeft->selfangleinc = 0.0f;
		pPartAimLeft->xpivinc = 0.0f;
		pPartAimLeft->ypivinc = 0.0f;
		pPartAimLeft->angleinc = 0.0f;
		pPartAimLeft->winc = 0.0f;
		pPartAimLeft->hinc = 0.0f;
		pPartAimLeft->thickinc = 0.0f;

		chPartAnimSegment* pAnimAimLeft0 = AddAnimation(pPartAimLeft, CHA_XOFFSET);
		if (pAnimAimLeft0)
		{
			pAnimAimLeft0->startFrame = 0;
			pAnimAimLeft0->endFrame = 3; // If from a sprite, which frame do we stop at
			pAnimAimLeft0->framerate = 4; // Frame rate of the animation
			pAnimAimLeft0->nextPartAnim = 1;
			pAnimAimLeft0->loop = 1;
			pAnimAimLeft0->startcrement = 0.0f;
			pAnimAimLeft0->crement = 1.0f;
		}

		chPartAnimSegment* pAnimAimLeft1 = AddAnimation(pPartAimLeft, CHA_XOFFSET);
		if (pAnimAimLeft1)
		{
			pAnimAimLeft1->startFrame = 0;
			pAnimAimLeft1->endFrame = 3; // If from a sprite, which frame do we stop at
			pAnimAimLeft1->framerate = 4; // Frame rate of the animation
			pAnimAimLeft1->nextPartAnim = 0;
			pAnimAimLeft1->loop = 1;
			pAnimAimLeft1->startcrement = 3.0f;
			pAnimAimLeft1->crement = -1.0f;
		}
	}

	chPart* pPartAimUp = AddPart(pSubAim);
	if (pPartAimUp)
	{
		pPartAimUp->parttype = CHPT_LINE;
		pPartAimUp->partsubtype = LSHAPE_RADIUS;
		pPartAimUp->xoffset = 5;
		pPartAimUp->width = 10;
		pPartAimUp->height = 10;
		pPartAimUp->thickness = 1.0f;
		pPartAimUp->rotation = 270.0f;
		pPartAimUp->xinc = 1.0f;
		pPartAimUp->yinc = 0.0f;
		pPartAimUp->selfangleinc = 0.0f;
		pPartAimUp->xpivinc = 0.0f;
		pPartAimUp->ypivinc = 0.0f;
		pPartAimUp->angleinc = 0.0f;
		pPartAimUp->winc = 0.0f;
		pPartAimUp->hinc = 0.0f;
		pPartAimUp->thickinc = 0.0f;

		chPartAnimSegment* pAnimAimUp0 = AddAnimation(pPartAimUp, CHA_XOFFSET);
		if (pAnimAimUp0)
		{
			pAnimAimUp0->startFrame = 0;
			pAnimAimUp0->endFrame = 3; // If from a sprite, which frame do we stop at
			pAnimAimUp0->framerate = 4; // Frame rate of the animation
			pAnimAimUp0->nextPartAnim = 1;
			pAnimAimUp0->loop = 1;
			pAnimAimUp0->startcrement = 0.0f;
			pAnimAimUp0->crement = 1.0f;
		}

		chPartAnimSegment* pAnimAimUp1 = AddAnimation(pPartAimUp, CHA_XOFFSET);
		if (pAnimAimUp1)
		{
			pAnimAimUp1->startFrame = 0;
			pAnimAimUp1->endFrame = 3; // If from a sprite, which frame do we stop at
			pAnimAimUp1->framerate = 4; // Frame rate of the animation
			pAnimAimUp1->nextPartAnim = 0;
			pAnimAimUp1->loop = 1;
			pAnimAimUp1->startcrement = 3.0f;
			pAnimAimUp1->crement = -1.0f;
		}
	}

	// Auto Aim crosshair test
	chPart* pPartAutoLeft = AddPart(pSubAuto);
	if (pPartAutoLeft)
	{
		pPartAutoLeft->parttype = CHPT_CIRCLE;
		pPartAutoLeft->partsubtype = CSHAPE_ARC;

		pPartAutoLeft->spanstart = 90.0f;
		pPartAutoLeft->spanend = 270.0f;
		pPartAutoLeft->xoffset = -8;
		pPartAutoLeft->width = 8;
		pPartAutoLeft->height = 8;
		pPartAutoLeft->thickness = 4.0f;
		pPartAutoLeft->rotation = 0.0f;
		pPartAutoLeft->xinc = -0.75f;
		pPartAutoLeft->yinc = 0.0f;
		pPartAutoLeft->selfangleinc = 0.0f;
		pPartAutoLeft->xpivinc = 0.0f;
		pPartAutoLeft->ypivinc = 0.0f;
		pPartAutoLeft->angleinc = 0.0f;
		pPartAutoLeft->winc = 0.15f;
		pPartAutoLeft->hinc = 0.15f;
		pPartAutoLeft->thickinc = 0.0f;
	}

	chPart* pPartAutoRight = AddPart(pSubAuto);
	if (pPartAutoRight)
	{
		pPartAutoRight->parttype = CHPT_CIRCLE;
		pPartAutoRight->partsubtype = CSHAPE_ARC;
		pPartAutoRight->spanstart = -90.0f;
		pPartAutoRight->spanend = 90.0f;
		pPartAutoRight->xoffset = 10;
		pPartAutoRight->width = 8;
		pPartAutoRight->height = 8;
		pPartAutoRight->thickness = 4.0f;
		pPartAutoRight->rotation = 0.0f;
		pPartAutoRight->xinc = 0.75f;
		pPartAutoRight->yinc = 0.0f;
		pPartAutoRight->selfangleinc = 0.0f;
		pPartAutoRight->xpivinc = 0.0f;
		pPartAutoRight->ypivinc = 0.0f;
		pPartAutoRight->angleinc = 0.0f;
		pPartAutoRight->winc = 0.15f;
		pPartAutoRight->hinc = 0.15f;
		pPartAutoRight->thickinc = 0.0f;
	}

	// Test Sprite Crosshair
	/*
	crsh* pCh2 = AddCrosshair("valve_spin");
	chSub* pSubNormal2 = GetSubCrosshairReference(1, CHSB_NORMAL);
	chPart* pPartNormalSprite = AddPart(pSubNormal2);
	if (pPartNormalSprite)
	{
		pPartNormalSprite->parttype = CHPT_SPRITE;
		pPartNormalSprite->partsubtype = 1;
		strcpy((char *)pPartNormalSprite->spritename, "sprites/valve2.spr");
		pPartNormalSprite->partspr = SPR_Load(pPartNormalSprite->spritename);
		pPartNormalSprite->xpos = 0;
		pPartNormalSprite->ypos = 0;
		pPartNormalSprite->xoffset = 64;
		pPartNormalSprite->yoffset = -32;
		pPartNormalSprite->width = 64;
		pPartNormalSprite->height = 64;
		pPartNormalSprite->xpivot = 0;
		pPartNormalSprite->ypivot = 0;
	}
	*/
}

// ParseCrosshairs
// Input: void
// Output: void
// Reads all the info from the crosshair.txt and parses them into the HUD
void CHudCrosshair::ParseCrosshairs(void)
{
	
}

int CHudCrosshair::Init(void)
{
	gHUD.AddHudElem(this);

	HOOK_MESSAGE(Crosshair);

	HOOK_MESSAGE(AutoAim);

	Reset();

	CVAR_CREATE("hud_crosshair_draw", "1", FCVAR_ARCHIVE);		  // Do we draw the crosshair or not?
	CVAR_CREATE("hud_crosshair_scale", "1.0f", FCVAR_ARCHIVE);	  // Player's own custom scale for crosshair
	CVAR_CREATE("hud_crosshair_animate", "1", FCVAR_ARCHIVE);	  // Do we animate crosshairs at all?
	CVAR_CREATE("hud_crosshair_custom_main", "-1", FCVAR_ARCHIVE);	  // -1 is weapon defined, 0 is system default, any else is custom
	CVAR_CREATE("hud_crosshair_custom_sub", "-1", FCVAR_ARCHIVE);	  // -1 is weapon defined, 0 is system default, any else is custom
	CVAR_CREATE("hud_crosshair_custom_auto", "-1", FCVAR_ARCHIVE);	  // -1 is weapon defined, 0 is system default, any else is custom
	CVAR_CREATE("hud_crosshair_color", "default", FCVAR_ARCHIVE); // "default", "hud" or custom color
	CVAR_CREATE("hud_crosshair_alpha", "default", FCVAR_ARCHIVE);  // "default", "hud" or custom alpha
	CVAR_CREATE("hud_crosshair_scale_recoil", "1", FCVAR_ARCHIVE); // "0 disables recoil scale

	CVAR_CREATE("hud_crosshair_snap", "0", FCVAR_ARCHIVE); // "0 means the auto crosshair transitions over to the target instead of snapping instantly
	CVAR_CREATE("hud_crosshair_auto_snap", "0", FCVAR_ARCHIVE); // "0 means the auto crosshair transitions over to the target instead of snapping instantly

	m_iMinRecoil = -20;
	m_iRecoil = 0;
	m_iMaxRecoil = 100;
	m_flRecoilCooldown = -1.0f;

	InitDefaultCrosshair();

	m_iTargetCrosshair = 1;
	m_iTargetSubCrosshair = 0;
	m_iTargetAutoCrosshair = 0;

	m_iFlags |= HUD_ACTIVE; //!!!

	m_iChxAuto = ScreenWidth / 2;
	m_iChyAuto = ScreenHeight / 2;

	return 1;
};

int CHudCrosshair::VidInit(void)
{
	// Load and others
	SetActiveCrosshair(0, 0, 0);
	SetActiveParts(CH_SUB_ALL);

	return 1;
}

void CHudCrosshair::Think(void)
{
	if (gHUD.m_fPlayerDead)
		return;

	// Decrement recoil while making sure it never goes above or below the prescribed range
	if (gHUD.m_flTimeDelta > 0)
	{
		m_flRecoilCooldown = (m_flRecoilCooldown - gHUD.m_flHackedDelta < 0.0f) ? -1.0f : m_flRecoilCooldown - gHUD.m_flHackedDelta;

		if (m_flRecoilCooldown <= 0.0f)
		{
			if (m_iRecoil != 0)
			{
				m_iRecoil = (m_iRecoil > 0) ? m_iRecoil - 1 : m_iRecoil + 1;
				m_flRecoilCooldown = 0.02f; // Temp value, we need to set it to something appropriate
			}
		}
	}
}

int CHudCrosshair::MsgFunc_Crosshair(const char* pszName, int iSize, void* pbuf)
{
	BEGIN_READ(pbuf, iSize);
	int iAmount = READ_LONG();

	m_iRecoil = max(min(m_iRecoil + iAmount, m_iMaxRecoil), m_iMinRecoil);
	m_flRecoilCooldown = 0.15f;

	return 1;
}

int CHudCrosshair::MsgFunc_AutoAim(const char* pszName, int iSize, void* pbuf)
{
	BEGIN_READ(pbuf, iSize);
	float flxCoord = READ_LONG();
	float flyCoord = READ_LONG();
	int iStop = READ_BYTE();

	if (iStop)
	{
		m_iChxAuto = ScreenWidth / 2;
		m_iChyAuto = ScreenHeight / 2;
	}
	else
	{
		// Compute actual screen coordinates for these
		m_iChxAuto = flxCoord * 5.0f * 0.2f;
		m_iChyAuto = flyCoord * 5.0f * 0.2f;
	}
		

	return 1;
}

// DetectCvarChanges
// Input: void
// Output: void
// Detects any change in the custom crosshair and sub crosshair console varriables and performs the appropriate changes
void CHudCrosshair::DetectCVarChanges(void)
{
	int customChId = (int)CVAR_GET_FLOAT("hud_crosshair_custom_main");
	int customSubChId = (int)CVAR_GET_FLOAT("hud_crosshair_custom_sub");
	int customAutoChId = (int)CVAR_GET_FLOAT("hud_crosshair_custom_auto");

	int currentId = GetActiveMainCrosshairId();
	int currentSubId = GetActiveSubCrosshairIndex();
	int currentAutoId = GetActiveAutoCrosshairIndex();

	// Safety.
	// For main crosshairs. -1 is default behavior, anything above the max number of crosshairs should fall back to the nulll crosshair
	// For sub-crosshairs, do not include lock-on crosshairs as selectable ones
	customChId = (customChId > -1) ? (customChId > GetNumCrosshairs() - 1 ? 0 : customChId) : (-1);
	customSubChId = (customSubChId > -1) ? (customSubChId > CHSB_ZOOM_AIM_DENY ? 0 : customSubChId) : (-1);
	customAutoChId = (customSubChId > -1) ? ((customAutoChId > CHSB_ZOOM_AIM_DENY && customAutoChId < CHSB_AUTO_LOCK + 1) ? 0 : customAutoChId) : (-1);

	// This is the variable that will be used to determine what to switch or not
	int switchValue = (currentId != (customChId <= -1 ? m_iTargetCrosshair : customChId) ? 1 : 0) + (currentSubId != (customSubChId <= -1 ? m_iTargetSubCrosshair : customSubChId) ? 2 : 0);
	int switchValueAuto = (currentAutoId != (customAutoChId <= -1 ? m_iTargetAutoCrosshair : customAutoChId) ? 1 : 0);

	// Perform the switch if it must be done
	if (switchValue != 0)
	{
		SetActiveCrosshair(switchValue & 1 ? (customChId <= -1 ? m_iTargetCrosshair : customChId) : currentId,
			switchValue & 2 ? (customSubChId <= -1 ? m_iTargetSubCrosshair : customSubChId) : currentSubId,
			switchValueAuto ? (customAutoChId <= -1 ? m_iTargetAutoCrosshair : currentAutoId) : currentAutoId);
	}
	else
	{
		if (switchValueAuto != 0)
			SetActiveAutoCrosshair(switchValueAuto ? (customAutoChId <= -1 ? m_iTargetAutoCrosshair : currentAutoId) : currentAutoId);
	}
}

// Special 
int CHudCrosshair::DrawHudStringAlt(int iX, int iDir, int iSubType, char* szString, int r, int g, int b, int a, int xpos, int ypos, float xscale, float yscale, int xpivot, int ypivot, float angle, float selfangle)
{
	// Secure iDir to make sure it doesn't go haywire
	int iLocalDir = (iDir >= 1) ? 1 : 0;

	// We use either way
	char* szIt = szString;

	// Set szIt to the end of the string should we write the string in reverse order
	if (iLocalDir)
		for (szIt; *szIt != 0; szIt++) {}

	// Remember to decrement before the loop if reversed
	if (iLocalDir)
		szIt--;

	// pivots have to be modified for entire strings as the center is the center of the sequence, not individual characters
	int selfxpivot, selfypivot = -1;

	// Determine length of string to determine pivot based on summed character length
	if (iSubType == FSHAPE_NORM)
	{
		char* szPivot = szIt;
		int iStrLength = 0;
		while ((iLocalDir && szPivot != (szString - 1)) || (!iLocalDir && *szPivot != 0 && *szPivot != '\n'))
		{
			iStrLength += gHUD.m_scrinfo.charWidths[*szPivot];

			// Loop decrement
			if (iLocalDir) szPivot--; else szPivot++;
		}
		selfxpivot = xpos + (int)((float)iStrLength * xscale * 0.5);
		selfypivot = ypos + (int)((float)gHUD.m_scrinfo.iCharHeight * yscale * 0.5);
	}

	// Dangerous, but we have break and return conditions
	while ((iLocalDir && szIt != (szString - 1)) || (!iLocalDir && *szIt != 0 && *szIt != '\n'))
	{
		int next = xpos + ((iLocalDir) ? -1 : 1) * gHUD.m_scrinfo.charWidths[*szIt];

		if ((iLocalDir && next < iX) || (!iLocalDir && next > iX))
			return xpos;

		if (iLocalDir) xpos = next;
		TextMessageDrawCharAlt(xpos, ypos, *szIt, r, g, b, a, xscale, yscale, xpivot, ypivot, angle, selfangle, selfxpivot, selfypivot);
		if (!iLocalDir) xpos = next;

		// Loop decrement
		if (iLocalDir) szIt--; else szIt++;
	}

	return xpos;
}

//-------------------------------------------------------------------------
// Function that determines the adjustments necessary for auto-aiming
// and lock-on
//-------------------------------------------------------------------------
void CHudCrosshair::AutoPositionAdjust(void)
{
	// Do not go through this if the game is paused
	if (gHUD.m_flTimeDelta <= 0)
		return;

	// Timer stuff goes here
	if (m_flSnapTimeLeft > 0.0f)
		m_flSnapTimeLeft -= gHUD.m_flHackedDelta;

	if (m_flAutoSnapTimeLeft > 0.0f)
		m_flAutoSnapTimeLeft -= gHUD.m_flHackedDelta;

	// Regular aim adjustment
	if (m_iChAdjustType & CH_SUB_NORM)
	{
		if (m_flSnapTime <= 0.0f || (int)CVAR_GET_FLOAT("hud_crosshair_snap") == 0)
		{
			int iDirX = 0;
			int iDirY = 0;

			if (m_iChxActual != m_iChxTarget)
				iDirX = (m_iChxActual > m_iChxTarget) ? -1 : 1;

			if (m_iChyActual != m_iChyTarget)
				iDirY = (m_iChyActual > m_iChyTarget) ? -1 : 1;

			// Distance from current (X,Y) to target (X,Y) 
			int iDistX = abs(m_iChx - m_iChxTarget);
			int iDistY = abs(m_iChy - m_iChyTarget);

			float flDelta = (m_flSnapTime - m_flSnapTimeLeft) / m_flSnapTime;

			// Adjust
			m_iChxActual = m_iChx + iDirX * (flDelta);
			m_iChyActual = m_iChy + iDirY * (flDelta);
		}
		else
		{
			m_iChxActual = m_iChxTarget;
			m_iChyActual = m_iChyTarget;
		}
	}
	else
	{
		// We have nothing to adjust here, move on
		m_iChxActual = m_iChx;
		m_iChyActual = m_iChy;
	}

	// Auto-aim adjustment
	if (m_iChAdjustType & CH_SUB_AUTO)
	{
		if (m_flAutoSnapTime <= 0.0f || (int)CVAR_GET_FLOAT("hud_crosshair_auto_snap") == 0)
		{
			int iDirX = 0;
			int iDirY = 0;

			if (m_iChxAutoActual != m_iChxAutoTarget)
				iDirX = (m_iChxAutoActual > m_iChxAutoTarget) ? -1 : 1;

			if (m_iChyAutoActual != m_iChyAutoTarget)
				iDirY = (m_iChyAutoActual > m_iChyAutoTarget) ? -1 : 1;

			// Distance from current (X,Y) to target (X,Y) 
			int iDistX = abs(m_iChxAuto - m_iChxAutoTarget);
			int iDistY = abs(m_iChyAuto - m_iChyAutoTarget);

			float flDelta = (m_flAutoSnapTime - m_flAutoSnapTimeLeft) / m_flAutoSnapTime;

			// Adjust
			m_iChxAutoActual = m_iChxAuto + iDirX * (flDelta);
			m_iChyAutoActual = m_iChyAuto + iDirY * (flDelta);
		}
		else
		{
			m_iChxAutoActual = m_iChxAutoTarget;
			m_iChxAutoActual = m_iChyAutoTarget;
		}
	}
	else
	{
		m_iChxAutoActual = m_iChxAuto;
		m_iChyAutoActual = m_iChyAuto;
	}
}

//-------------------------------------------------------------------------
// Drawing code
//-------------------------------------------------------------------------
int CHudCrosshair::Draw(float flTime)
{
	if (!(gHUD.m_iWeaponBits & (1 << (WEAPON_SUIT))))
		return 1;

	if ((gHUD.m_iHideHUDDisplay & (HIDEHUD_WEAPONS | HIDEHUD_ALL)))
		return 1;

	// Do not draw if we have this disabled
	if (CVAR_GET_FLOAT("hud_crosshair_draw") == 0)
		return 1;

	int a, x, y, r, g, b;

	float flCustomScale = CVAR_GET_FLOAT("hud_crosshair_scale");

	unsigned long color = RGB_YELLOWISH;
	if (strcmp(CVAR_GET_STRING("hud_crosshair_color"),"hud") && strcmp(CVAR_GET_STRING("hud_crosshair_color"), "default"))
		color = CVAR_GET_FLOAT("hud_crosshair_color");

	// Value updates are done here
	DetectCVarChanges();
	
	int customChId = GetActiveMainCrosshairId();
	int customSubChId = GetActiveSubCrosshairIndex();
	int customAutoChId = GetActiveAutoCrosshairIndex();

	UnpackRGB(r, g, b, color);
	ScaleColors(r, g, b, 255);

	// Compute x and y positions on the screen
	x = ScreenWidth / 2;
	y = ScreenHeight / 2;

	// Do the animations
	AnimateParts(CH_SUB_ALL);

	// Draw both crosshair and auto-aim crosshair
	for (int i2 = 0; i2 < 2; i2++)
	{
		if (i2 == 1)
		{
			x = (int)((float)GetCrosshairPosX() / HUDScaleHorizontal());
			y = (int)((float)GetCrosshairPosY() / HUDScaleVertical());
			customSubChId = 8;
		}

		// Begin drawing the crosshair, overly complicated logic inbound
		// Check if crosshair id and crosshair sub_id are valid then get to it
		if (ValidMainCrosshairId(customChId) && ValidSubCrosshairIndex(customSubChId))
		{
			crsh* pChRef = GetCrosshairReference(customChId);
			chSub* pSubRef = GetSubCrosshairReference(customChId, customSubChId);

			for (int i = 0; i < GetNumParts(pSubRef); i++)
			{
				chPart* pPartRef = GetPartReference(customChId, customSubChId, i);

				// Acquire all the info we need about said crosshairs
				int type = GetPartType(pPartRef);
				int subtype = GetPartSubType(pPartRef);

				int xpart = GetPartXOffset(pPartRef);
				int ypart = GetPartYOffset(pPartRef);
				int xpos = GetPartXPosition(pPartRef);
				int ypos = GetPartYPosition(pPartRef);
				int heightpart = GetPartHeight(pPartRef);
				int widthpart = GetPartWidth(pPartRef);
				float thickness = GetPartThickness(pPartRef);
				float spanstart = GetPartSpanStart(pPartRef);
				float spanend = GetPartSpanEnd(pPartRef);

				int red = GetPartRed(pPartRef);
				int green = GetPartGreen(pPartRef);
				int blue = GetPartBlue(pPartRef);
				int alpha = GetPartAlpha(pPartRef);

				float selfangle = GetPartSelfRotation(pPartRef);

				int xpivot = GetPartXPivot(pPartRef);
				int ypivot = GetPartYPivot(pPartRef);
				float angle = GetPartRotation(pPartRef);

				float xscale = GetPartXScale(pPartRef);
				float yscale = GetPartYScale(pPartRef);
				float selfanglescale = GetPartSelfAngleScale(pPartRef);
				float xpivotscale = GetPartXPivotScale(pPartRef);
				float ypivotscale = GetPartYPivotScale(pPartRef);
				float anglescale = GetPartAngleScale(pPartRef);
				float widthscale = GetPartWidthScale(pPartRef);
				float heightscale = GetPartHeightScale(pPartRef);
				float thickscale = GetPartThicknessScale(pPartRef);
				float spanstartscale = GetPartSpanStartScale(pPartRef);
				float spanendscale = GetPartSpanEndScale(pPartRef);

				float xinc = GetPartXIncrement(pPartRef);
				float yinc = GetPartYIncrement(pPartRef);
				float selfangleinc = GetPartSelfAngleIncrement(pPartRef);
				float xpivinc = GetPartXPivotIncrement(pPartRef);
				float ypivinc = GetPartYPivotIncrement(pPartRef);
				float angleinc = GetPartAngleIncrement(pPartRef);
				float winc = GetPartWidthIncrement(pPartRef);
				float hinc = GetPartHeightIncrement(pPartRef);
				float thickinc = GetPartThicknessIncrement(pPartRef);
				float spanstartinc = GetPartSpanStartIncrement(pPartRef);
				float spanendinc = GetPartSpanEndIncrement(pPartRef);

				const char* pSpriteName = GetPartSpriteName(pPartRef);
				HSPR sprite = GetPartSprite(pPartRef);
				int frame = 0;

				chPartActive* pActivePart = GetActivePartReference(i, i2 + 1);

				for (int iAnimType = CHA_FRAME; iAnimType < CHA_TOTAL; iAnimType++)
				{
					if (pActivePart)
					{
						int aframe = pActivePart->animframe[iAnimType];
						int aindex = pActivePart->animindex[iAnimType];
						chPartAnimSegment* pAnimRef = GetAnimationReference(customChId, customSubChId, i, iAnimType, aindex);

						// Compute animation stuff
						if (pAnimRef)
						{
							int iModifier = (int)GetAnimationStartCrement(pAnimRef) + GetActivePartAnimationFrame(pActivePart, iAnimType) * (int)GetAnimationCrement(pAnimRef);
							float flModifier = GetAnimationStartCrement(pAnimRef) + (float)GetActivePartAnimationFrame(pActivePart, iAnimType) * GetAnimationCrement(pAnimRef);
							switch (iAnimType)
							{
							case CHA_FRAME:
								frame += iModifier;
								break;
							case CHA_RED:
								red += iModifier;
								break;
							case CHA_GREEN:
								green += iModifier;
								break;
							case CHA_BLUE:
								blue += iModifier;
								break;
							case CHA_ALPHA:
								alpha += iModifier;
								break;
							case CHA_XOFFSET:
								xpart += iModifier;
								break;
							case CHA_YOFFSET:
								ypart += iModifier;
								break;
							case CHA_XSCALE:
								xscale += flModifier;
								break;
							case CHA_YSCALE:
								yscale += flModifier;
								break;
							case CHA_THICK:
								thickness += flModifier;
								break;
							case CHA_SPANSTART:
								spanstart += flModifier;
								break;
							case CHA_SPANEND:
								spanend += flModifier;
								break;
							case CHA_XPIVOT:
								xpivot += iModifier;
								break;
							case CHA_YPIVOT:
								ypivot += iModifier;
								break;
							case CHA_SELFROTATE:
								selfangle += flModifier;
								break;
							case CHA_ROTATE:
								angle += flModifier;
								break;
							}
						}
					}
				}

				// Compute Recoil Scales
				if ((int)CVAR_GET_FLOAT("hud_crosshair_scale_recoil") != 0)
				{
					if (xinc != 0.0f) xpart += (int)(ceil(xinc * (float)m_iRecoil));
					if (yinc != 0.0f) yinc += (int)(ceil(yinc * (float)m_iRecoil));
					if (selfangleinc != 0.0f) selfangle += (int)(ceil(selfangleinc * (float)m_iRecoil));
					if (xpivinc != 0.0f) xpivot += (int)(ceil(xpivinc * (float)m_iRecoil));
					if (ypivinc != 0.0f) ypivot += (int)(ceil(ypivinc * (float)m_iRecoil));
					if (angleinc != 0.0f) angle += (int)(ceil(angleinc * (float)m_iRecoil));
					if (winc != 0.0f) widthpart += (int)(ceil(winc * (float)m_iRecoil));
					if (hinc != 0.0f) heightpart += (int)(ceil(hinc * (float)m_iRecoil));
					if (thickinc != 0.0f) thickness += (int)(ceil(thickinc * (float)m_iRecoil));
					if (spanstartinc != 0.0f) spanstart += (int)(ceil(spanstartinc * (float)m_iRecoil));
					if (spanendinc != 0.0f) spanstart += (int)(ceil(spanstartinc * (float)m_iRecoil));
				}

				// Safeties before drawing

				// Draw the elements
				switch (type)
				{
				case CHPT_SPRITE:
					SetActivePartRect(pActivePart, { xpos, ypos, widthpart, heightpart });
					SPR_Set(sprite, r, g, b);
					//SPR_DrawAdditiveScale(0, x + xpart, y + ypart, &GetActivePartRect(pActivePart), xscale, yscale, selfangle, angle, x + xpivot, y + ypivot);
					break;
				case CHPT_SYSFONT:
					// Do not upscale, this is already handled by the engine's inner works
					DrawHudStringAlt(320, 0, subtype, "ass", r, g, b, a, x + xpart, y + ypart, xscale, yscale, xpivot, ypivot, 0, 0);
					break;
				case CHPT_LINE:
					FillRGBA(HUDScaleAdjustX(x + (int)((float)xpart * flCustomScale)), HUDScaleAdjustY(y + (int)((float)ypart * flCustomScale)),
						(int)((float)HUDScaleAdjustBoth(widthpart) * flCustomScale), (int)((float)HUDScaleAdjustBoth(heightpart) * flCustomScale),
						subtype,
						HUDScaleAdjustBoth() * thickscale * flCustomScale,
						r, g, b, 255,
						HUDScaleHorizontal() * xscale * flCustomScale, HUDScaleVertical() * yscale * flCustomScale,
						selfangle,
						angle, HUDScaleAdjustX(x + (int)((float)xpivot * flCustomScale)), HUDScaleAdjustY(y + (int)((float)ypivot * flCustomScale)));
					break;
				case CHPT_CIRCLE:
					FillRGBACircle(HUDScaleAdjustX(x + xpart), HUDScaleAdjustY(y + ypart), HUDScaleAdjustBoth(widthpart), HUDScaleAdjustBoth(heightpart), (int)ceil((float)60), subtype, thickscale, spanstart, spanend, r, g, b, 255, xscale, yscale, selfangle, angle, x + xpivot, y + ypivot);
					break;
				default:
					break;
				}
			}
		}
	}

	return 1;
}

void CHudCrosshair::Reset(void)
{
	m_iFlags |= HUD_ACTIVE; //!!!

	gHUD.m_iHideHUDDisplay = 0;

	//	VidInit();
}