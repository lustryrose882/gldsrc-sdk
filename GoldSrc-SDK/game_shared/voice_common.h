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

#include "bitvec.h"

// TODO: this should just be set to MAX_CLIENTS
#define VOICE_MAX_PLAYERS			32
#define VOICE_MAX_PLAYERS_DW		((VOICE_MAX_PLAYERS / 32) + !!(VOICE_MAX_PLAYERS & 31))

typedef CBitVec<VOICE_MAX_PLAYERS> CPlayerBitVec;
