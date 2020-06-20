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

#ifndef MODELGEN_H
#define MODELGEN_H
#ifdef _WIN32
#pragma once
#endif

typedef enum synctype_e
{
	ST_SYNC = 0,
	ST_RAND = 1,
} synctype_t;

typedef enum aliasframetype_s
{
	ALIAS_SINGLE = 0,
	ALIAS_GROUP = 1,
} aliasframetype_t;

typedef enum aliasskintype_s
{
	ALIAS_SKIN_SINGLE = 0,
	ALIAS_SKIN_GROUP = 1,
} aliasskintype_t;

typedef struct mdl_s
{
	int				ident;
	int				version;
	vec3_t			scale;
	vec3_t			scale_origin;
	float			boundingradius;
	vec3_t			eyeposition;
	int				numskins;
	int				skinwidth;
	int				skinheight;
	int				numverts;
	int				numtris;
	int				numframes;
	synctype_t		synctype;
	int				flags;
	float			size;
} mdl_t;

typedef struct stvert_s
{
	int				onseam;
	int				s;
	int				t;
} stvert_t;

typedef struct dtriangle_s
{
	int				facesfront;
	int				vertindex[3];
} dtriangle_t;

typedef struct trivertx_s
{
	byte			v[3];
	byte			lightnormalindex;
} trivertx_t;

typedef struct daliasframe_s
{
	trivertx_t		bboxmin, bboxmax;
	char			name[16];
} daliasframe_t;

typedef struct daliasgroup_s
{
	int				numframes;
	trivertx_t		bboxmin, bboxmax;
} daliasgroup_t;

typedef struct daliasskingroup_s
{
	int				numskins;
} daliasskingroup_t;

typedef struct daliasinterval_s
{
	float			interval;
} daliasinterval_t;

typedef struct daliasskininterval_s
{
	float			interval;
} daliasskininterval_t;

typedef struct daliasframetype_s
{
	aliasframetype_t type;
} daliasframetype_t;

typedef struct daliasskintype_s
{
	aliasskintype_t type;
} daliasskintype_t;

#endif // #ifndef MODELGEN_H
