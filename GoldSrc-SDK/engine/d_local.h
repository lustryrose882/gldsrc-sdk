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

typedef struct surfcache_s
{
	struct surfcache_s *next;
	struct surfcache_s **owner;
	int lightadj[4];
	int dlight;
	int size;
	unsigned width;
	unsigned height;
	float mipscale;
	struct texture_s *texture;
	unsigned char data[4];
} surfcache_t;
