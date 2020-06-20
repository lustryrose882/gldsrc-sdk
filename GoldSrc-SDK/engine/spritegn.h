/*
*
*    Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*    This product contains software technology licensed from Id
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*    All Rights Reserved.
*
*    Use, distribution, and modification of this source code and/or resulting
*    object code is restricted to non-commercial enhancements to products from
*    Valve LLC.  All other use, distribution, or modification is prohibited
*    without written permission from Valve LLC.
*
*/

#ifndef SPRITEGN_H
#define SPRITEGN_H
#ifdef _WIN32
#pragma once
#endif

#include "modelgen.h"
#include "tier0/commonmacros.h"

#define SPRITE_VERSION		2							// Half-Life sprites
#define IDSPRITEHEADER		MAKEID('I', 'D', 'S', 'P')	// little-endian "IDSP"

typedef enum spriteframetype_e
{
	SPR_SINGLE = 0,
	SPR_GROUP,
	SPR_ANGLED
} spriteframetype_t;

typedef struct dsprite_s
{
	int				ident;
	int				version;
	int				type;
	int				texFormat;
	float			boundingradius;
	int				width;
	int				height;
	int				numframes;
	float			beamlength;
	synctype_t		synctype;
} dsprite_t;

#define SPR_VP_PARALLEL_UPRIGHT		0
#define SPR_FACING_UPRIGHT			1
#define SPR_VP_PARALLEL				2
#define SPR_ORIENTED				3
#define SPR_VP_PARALLEL_ORIENTED	4

#define SPR_NORMAL					0
#define SPR_ADDITIVE				1
#define SPR_INDEXALPHA				2
#define SPR_ALPHATEST				3

typedef struct dspriteframe_s
{
	int				origin[2];
	int				width;
	int				height;
} dspriteframe_t;

typedef struct dspritegroup_s
{
	int				numframes;
} dspritegroup_t;

typedef struct dspriteinterval_s
{
	float			interval;
} dspriteinterval_t;

typedef struct dspriteframetype_s
{
	spriteframetype_t type;
} dspriteframetype_t;

#endif // #ifndef SPRITEGN_H
