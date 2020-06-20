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

enum
{
	DEFAULT_BPP    =
#if defined(_WIN32)
						16
#else
						32
#endif
	,
	DEFAULT_HEIGHT =  640,
	DEFAULT_WIDTH  =  480,
};

typedef struct vmode_s
{
	int		width;
	int		height;
	int		bpp;
} vmode_t;
