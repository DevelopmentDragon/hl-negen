/*
gl_draw.c - orthogonal drawing stuff
Copyright (C) 2010 Uncle Mike

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include "common.h"
#include "client.h"
#include "gl_local.h"

/*
=============
R_GetImageParms
=============
*/
void R_GetTextureParms( int *w, int *h, int texnum )
{
	gl_texture_t	*glt;

	glt = R_GetTexture( texnum );
	if( w ) *w = glt->srcWidth;
	if( h ) *h = glt->srcHeight;
}

/*
=============
R_GetSpriteParms

same as GetImageParms but used
for sprite models
=============
*/
void R_GetSpriteParms( int *frameWidth, int *frameHeight, int *numFrames, int currentFrame, const model_t *pSprite )
{
	mspriteframe_t	*pFrame;

	if( !pSprite || pSprite->type != mod_sprite ) return; // bad model ?
	pFrame = R_GetSpriteFrame( pSprite, currentFrame, 0.0f );

	if( frameWidth ) *frameWidth = pFrame->width;
	if( frameHeight ) *frameHeight = pFrame->height;
	if( numFrames ) *numFrames = pSprite->numframes;
}

int R_GetSpriteTexture( const model_t *m_pSpriteModel, int frame )
{
	if( !m_pSpriteModel || m_pSpriteModel->type != mod_sprite || !m_pSpriteModel->cache.data )
		return 0;

	return R_GetSpriteFrame( m_pSpriteModel, frame, 0.0f )->gl_texturenum;
}

/*
=============
R_DrawStretchPic
=============
*/
void R_DrawStretchPic( float x, float y, float w, float h, float s1, float t1, float s2, float t2, int texnum )
{
	GL_Bind( GL_TEXTURE0, texnum );

	pglBegin( GL_QUADS );
		pglTexCoord2f( s1, t1 );
		pglVertex2f( x, y );

		pglTexCoord2f( s2, t1 );
		pglVertex2f( x + w, y );

		pglTexCoord2f( s2, t2 );
		pglVertex2f( x + w, y + h );

		pglTexCoord2f( s1, t2 );
		pglVertex2f( x, y + h );
	pglEnd();
}

/*
=============
R_DrawStretchPicRotate
=============
*/
void R_DrawStretchPicRotate(float x, float y, float w, float h, float s1, float t1, float s2, float t2, int texnum, float xscale, float yscale, float selfangle, float angle, float xpivot, float ypivot, float selfxpivot, float selfypivot)
{
	GL_Bind(GL_TEXTURE0, texnum);

	if (!xscale) xscale = 1.0;
	if (!yscale) yscale = 1.0;

	float invxscale = 1 / xscale;
	float invyscale = 1 / yscale;

	// Self pivot check
	if (selfxpivot == -1 || selfypivot == -1)
	{
		selfxpivot = x + w / 2;
		selfypivot = y + h / 2;
	}

	pglPushMatrix();
	pglTranslatef(xpivot, ypivot, 0.0);
	pglRotatef(angle, 0.0, 0.0, 1.0);
	pglTranslatef(-xpivot, -ypivot, 0.0);
	pglTranslatef(selfxpivot, selfypivot, 0.0);
	pglRotatef(selfangle, 0.0, 0.0, 1.0);
	pglTranslatef(-selfxpivot, -selfypivot, 0.0);

	pglBegin(GL_QUADS);
		pglTexCoord2f(s1, t1);
		pglVertex2f(x, y);

		pglTexCoord2f(s2, t1);
		pglVertex2f(x + w, y);

		pglTexCoord2f(s2, t2);
		pglVertex2f(x + w, y + h);

		pglTexCoord2f(s1, t2);
		pglVertex2f(x, y + h);
	pglEnd();

	pglPopMatrix();
}

/*
=============
R_DrawStretchPicRotate
=============
*/
void R_DrawStretchPicCircleRotate(float x, float y, float radius, int numshapes, int type, float thickness, float angle_start, float angle_end, int texnum, float xscale, float yscale, float selfangle, float angle, float xpivot, float ypivot)
{
	GL_Bind(GL_TEXTURE0, texnum);

	// Prepare vars
	if (!xscale) xscale = 1.0;
	if (!yscale) yscale = 1.0;

	// Initialize increment and pi
	int i = 0;
	float twicePi = 2.0f * M_PI;

	// To ensure scaling works properly
	x *= (1.0f / xscale);
	y *= (1.0f / yscale);

	// Adjustements happen here
	float total_draw = fabs(max(angle_start, angle_end) - min(angle_start, angle_end));
	float draw_ratio = total_draw / 360.0f;
	float adjusted_twicepi = twicePi * draw_ratio;
	int adjusted_numshapes = numshapes;
	if (total_draw < 360.0f) adjusted_numshapes = (int)ceil(draw_ratio * (float)adjusted_numshapes);

	// Push matrix
	pglPushMatrix();

	// draw angle adjustement
	pglTranslatef(x, y, 0.0);
	pglRotatef(angle_start, 0.0, 0.0, 1.0);
	pglTranslatef(-x, -y, 0.0);

	// Rotation around itself
	pglTranslatef(x, y, 0.0);
	pglRotatef(selfangle, 0.0, 0.0, 1.0);
	pglTranslatef(-x, -y, 0.0);

	// Rotation around defined pivot
	pglTranslatef(xpivot, ypivot, 0.0);
	pglRotatef(angle, 0.0, 0.0, 1.0);
	pglTranslatef(-xpivot, -ypivot, 0.0);

	// Overall scale
	pglScalef(xscale, yscale, 1.0f);

	// Computer GL draw style and whether or not we draw the center
	// type 0 is either a full circle or arc, depending on start and end angle
	// type 1 is a hollow segment
	// type 2 is a hollow sector
	// type 3 is a filled sector or full disc, depending on start and end angle
	// type 4 is a filled segment
	int i_gldrawstyle = (type == 3 || type == 4) ? GL_TRIANGLE_FAN : ((type != 0) ? GL_LINE_LOOP : GL_LINE_STRIP);
	int i_drawcenter = (type % 2) ? 1 : 0;

	// Draw the thing
	pglLineWidth(thickness);
	pglBegin(i_gldrawstyle);
	if (i_drawcenter) pglVertex2f(x, y); // draw center of circle
	for (i = 0; i <= adjusted_numshapes; i++) {
		pglVertex2f(
			x + (radius * xscale * cos(i * adjusted_twicepi / adjusted_numshapes)),
			y + (radius * yscale * sin(i * adjusted_twicepi / adjusted_numshapes))
		);
	}
	pglEnd();
	pglLineWidth(1.0);
	// Return to normal
	pglPopMatrix();
}

/*
=============
Draw_TileClear

This repeats a 64*64 tile graphic to fill the screen around a sized down
refresh window.
=============
*/
void R_DrawTileClear( int x, int y, int w, int h )
{
	float		tw, th;
	gl_texture_t	*glt;

	GL_SetRenderMode( kRenderNormal );
	pglColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	GL_Bind( GL_TEXTURE0, cls.tileImage );

	glt = R_GetTexture( cls.tileImage );
	tw = glt->srcWidth;
	th = glt->srcHeight;

	pglBegin( GL_QUADS );
		pglTexCoord2f( x / tw, y / th );
		pglVertex2f( x, y );
		pglTexCoord2f((x + w) / tw, y / th );
		pglVertex2f( x + w, y );
		pglTexCoord2f((x + w) / tw, (y + h) / th );
		pglVertex2f( x + w, y + h );
		pglTexCoord2f( x / tw, (y + h) / th );
		pglVertex2f( x, y + h );
	pglEnd ();
}

/*
=============
R_DrawStretchRaw
=============
*/
void R_DrawStretchRaw( float x, float y, float w, float h, int cols, int rows, const byte *data, qboolean dirty )
{
	byte		*raw = NULL;
	gl_texture_t	*tex;

	if( !GL_Support( GL_ARB_TEXTURE_NPOT_EXT ))
	{
		int	width = 1, height = 1;
	
		// check the dimensions
		width = NearestPOW( cols, true );
		height = NearestPOW( rows, false );

		if( cols != width || rows != height )
		{
			raw = GL_ResampleTexture( data, cols, rows, width, height, false );
			cols = width;
			rows = height;
		}
	}
	else
	{
		raw = (byte *)data;
	}

	if( cols > glConfig.max_2d_texture_size )
		Host_Error( "R_DrawStretchRaw: size %i exceeds hardware limits\n", cols );
	if( rows > glConfig.max_2d_texture_size )
		Host_Error( "R_DrawStretchRaw: size %i exceeds hardware limits\n", rows );

	pglDisable( GL_BLEND );
	pglDisable( GL_ALPHA_TEST );
	pglTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

	tex = R_GetTexture( tr.cinTexture );
	GL_Bind( GL_TEXTURE0, tr.cinTexture );

	if( cols == tex->width && rows == tex->height )
	{
		if( dirty )
		{
			pglTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, cols, rows, GL_BGRA, GL_UNSIGNED_BYTE, raw );
		}
	}
	else
	{
		tex->size = cols * rows * 4;
		tex->width = cols;
		tex->height = rows;
		if( dirty )
		{
			pglTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, cols, rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, raw );
		}
	}

	pglBegin( GL_QUADS );
	pglTexCoord2f( 0, 0 );
	pglVertex2f( x, y );
	pglTexCoord2f( 1, 0 );
	pglVertex2f( x + w, y );
	pglTexCoord2f( 1, 1 );
	pglVertex2f( x + w, y + h );
	pglTexCoord2f( 0, 1 );
	pglVertex2f( x, y + h );
	pglEnd();
}

/*
=============
R_UploadStretchRaw
=============
*/
void R_UploadStretchRaw( int texture, int cols, int rows, int width, int height, const byte *data )
{
	byte		*raw = NULL;
	gl_texture_t	*tex;

	if( !GL_Support( GL_ARB_TEXTURE_NPOT_EXT ))
	{
		// check the dimensions
		width = NearestPOW( width, true );
		height = NearestPOW( height, false );
	}
	else
	{
		width = bound( 128, width, glConfig.max_2d_texture_size );
		height = bound( 128, height, glConfig.max_2d_texture_size );
	}

	if( cols != width || rows != height )
	{
		raw = GL_ResampleTexture( data, cols, rows, width, height, false );
		cols = width;
		rows = height;
	}
	else
	{
		raw = (byte *)data;
	}

	if( cols > glConfig.max_2d_texture_size )
		Host_Error( "R_UploadStretchRaw: size %i exceeds hardware limits\n", cols );
	if( rows > glConfig.max_2d_texture_size )
		Host_Error( "R_UploadStretchRaw: size %i exceeds hardware limits\n", rows );

	tex = R_GetTexture( texture );
	GL_Bind( GL_KEEP_UNIT, texture );
	tex->width = cols;
	tex->height = rows;

	pglTexImage2D( GL_TEXTURE_2D, 0, tex->format, cols, rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, raw );
	GL_ApplyTextureParams( tex );
}

/*
===============
R_Set2DMode
===============
*/
void R_Set2DMode( qboolean enable )
{
	if( enable )
	{
		if( glState.in2DMode )
			return;

		// set 2D virtual screen size
		pglViewport( 0, 0, glState.width, glState.height );
		pglMatrixMode( GL_PROJECTION );
		pglLoadIdentity();
		pglOrtho( 0, glState.width, glState.height, 0, -99999, 99999 );
		pglMatrixMode( GL_MODELVIEW );
		pglLoadIdentity();

		GL_Cull( GL_NONE );

		pglDepthMask( GL_FALSE );
		pglDisable( GL_DEPTH_TEST );
		pglEnable( GL_ALPHA_TEST );
		pglColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

		glState.in2DMode = true;
		RI.currententity = NULL;
		RI.currentmodel = NULL;
	}
	else
	{
		pglDepthMask( GL_TRUE );
		pglEnable( GL_DEPTH_TEST );
		glState.in2DMode = false;

		pglMatrixMode( GL_PROJECTION );
		GL_LoadMatrix( RI.projectionMatrix );

		pglMatrixMode( GL_MODELVIEW );
		GL_LoadMatrix( RI.worldviewMatrix );

		GL_Cull( GL_FRONT );
	}
}