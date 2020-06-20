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

#if !defined(DLIGHTH)
#define DLIGHTH
#ifdef _WIN32
#pragma once
#endif

#define	MAX_STYLESTRING	64
#define	MAX_DLIGHTS 32 // dynamic lights (rendered per one frame)
#define MAX_ELIGHTS 64 // entity only point lights

typedef struct dlight_s
{
	vec3_t	origin;
	float	radius;
	color24	color;
	float	die;				// stop lighting after this time
	float	decay;				// drop this each second
	float	minlight;			// don't add when contributing less
	int		key;
	qboolean	dark;			// subtracts light instead of adding
} dlight_t;

typedef struct
{
	int		length;
	char	map[MAX_STYLESTRING];
} lightstyle_t;

#endif // #if !defined(DLIGHTH)
