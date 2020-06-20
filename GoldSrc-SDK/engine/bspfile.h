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

#pragma once

// header
#define Q1BSP_VERSION			29		// quake1 regular version (beta is 28)
#define HLBSP_VERSION			30		// half-life regular version

#define MAX_MAP_HULLS			4

#define	MAX_MAP_MODELS			256
#define	MAX_MAP_BRUSHES			4096
#define	MAX_MAP_ENTITIES		1024
#define	MAX_MAP_ENTSTRING		65536

#define	MAX_MAP_PLANES			32767
#define	MAX_MAP_NODES			32767		// because negative shorts are contents
#define	MAX_MAP_CLIPNODES		32767		//
#define	MAX_MAP_LEAFS			8192
#define	MAX_MAP_VERTS			65535
#define	MAX_MAP_FACES			65535
#define	MAX_MAP_MARKSURFACES	65535
#define	MAX_MAP_TEXINFO			4096
#define	MAX_MAP_EDGES			256000
#define	MAX_MAP_SURFEDGES		512000
#define	MAX_MAP_TEXTURES		512
#define	MAX_MAP_MIPTEX			0x200000
#define	MAX_MAP_LIGHTING		0x100000
#define	MAX_MAP_VISIBILITY		0x100000

#define CONTENTS_ORIGIN			-7		// removed at csg time
#define CONTENTS_CLIP			-8		// changed to contents_solid
#define CONTENTS_CURRENT_0		-9
#define CONTENTS_CURRENT_90		-10
#define CONTENTS_CURRENT_180	-11
#define CONTENTS_CURRENT_270	-12
#define CONTENTS_CURRENT_UP		-13
#define CONTENTS_CURRENT_DOWN	-14

#define CONTENTS_TRANSLUCENT	-15

#define	LUMP_ENTITIES			0
#define	LUMP_PLANES				1
#define	LUMP_TEXTURES			2
#define	LUMP_VERTEXES			3
#define	LUMP_VISIBILITY			4
#define	LUMP_NODES				5
#define	LUMP_TEXINFO			6
#define	LUMP_FACES				7
#define	LUMP_LIGHTING			8
#define	LUMP_CLIPNODES			9
#define	LUMP_LEAFS				10
#define	LUMP_MARKSURFACES		11
#define	LUMP_EDGES				12
#define	LUMP_SURFEDGES			13
#define	LUMP_MODELS				14

#define	HEADER_LUMPS			15

#if !defined(TEXTURE_NAME_LENGTH)
#define TEXTURE_NAME_LENGTH 16
#endif

#if !defined(MIPLEVELS)
#define MIPLEVELS 4
#endif

typedef struct lump_s
{
	int				fileofs;
	int				filelen;
} lump_t;

typedef struct dmodel_s
{
	float			mins[3], maxs[3];
	float			origin[3];
	int				headnode[MAX_MAP_HULLS];
	int				visleafs;		// not including the solid leaf 0
	int				firstface, numfaces;
} dmodel_t;

typedef struct dheader_s
{
	int				version;
	lump_t			lumps[15];
} dheader_t;

typedef struct dmiptexlump_s
{
	int				_nummiptex;
	int				dataofs[4];
} dmiptexlump_t;

typedef struct miptex_s
{
	char			name[TEXTURE_NAME_LENGTH];
	unsigned		width;
	unsigned		height;
	unsigned		offsets[MIPLEVELS];		// four mip maps stored
} miptex_t;

typedef struct dvertex_s
{
	float			point[3];
} dvertex_t;

typedef struct dplane_s
{
	float			normal[3];
	float			dist;
	int				type;
} dplane_t;

typedef struct dnode_s
{
	int				planenum;
	short			children[2];
	short			mins[3];
	short			maxs[3];
	unsigned short	firstface;
	unsigned short	numfaces;
} dnode_t;

typedef struct dclipnode_s
{
	int				planenum;
	short			children[2];	// negative numbers are contents
} dclipnode_t;

typedef struct texinfo_s
{
	float			vecs[2][4];
	int				miptex;
	int				flags;
} texinfo_t;

typedef struct dedge_s
{
	unsigned short	v[2];
} dedge_t;

typedef struct dface_s
{
	short			planenum;
	short			side;
	int				firstedge;
	short			numedges;
	short			texinfo;
	byte			styles[4];
	int				lightofs;
} dface_t;

typedef struct dleaf_s
{
	int				contents;
	int				visofs;
	short			mins[3];
	short			maxs[3];
	unsigned short	firstmarksurface;
	unsigned short	nummarksurfaces;
	byte			ambient_level[4];
} dleaf_t;
