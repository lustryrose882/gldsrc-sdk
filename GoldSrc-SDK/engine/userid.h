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

#include "archtypes.h"

// Authentication types
enum AUTH_IDTYPE
{
	AUTH_IDTYPE_UNKNOWN	= 0,
	AUTH_IDTYPE_STEAM	= 1,
	AUTH_IDTYPE_VALVE	= 2,
	AUTH_IDTYPE_LOCAL	= 3
};

typedef struct USERID_s
{
	int idtype;
	uint64_t m_SteamID;
	unsigned int clientip;
} USERID_t;
