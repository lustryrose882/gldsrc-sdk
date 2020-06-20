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

// com_model.h
#pragma once

#define STUDIO_RENDER 1
#define STUDIO_EVENTS 2

//#define MAX_MODEL_NAME		64
//#define MAX_MAP_HULLS		4
//#define MIPLEVELS			4
//#define NUM_AMBIENTS		4		// automatic ambient sounds
//#define MAXLIGHTMAPS		4

#define ALIAS_Z_CLIP_PLANE	5

// flags in finalvert_t.flags
#define ALIAS_LEFT_CLIP				0x0001
#define ALIAS_TOP_CLIP				0x0002
#define ALIAS_RIGHT_CLIP			0x0004
#define ALIAS_BOTTOM_CLIP			0x0008
#define ALIAS_Z_CLIP				0x0010
#define ALIAS_ONSEAM				0x0020
#define ALIAS_XY_CLIP_MASK			0x000F

#define ZISCALE	((float)0x8000)

#define CACHE_SIZE	32		// used to align key data structures

typedef struct cache_user_s
{
	void	*data;
} cache_user_t;

typedef struct alight_s
{
	int			ambientlight;	// clip at 128
	int			shadelight;		// clip at 192 - ambientlight
	vec3_t		color;
	float		*plightvec;
} alight_t;

typedef struct auxvert_s
{
	float	fv[3];		// viewspace x, y
} auxvert_t;

#include "custom.h"
