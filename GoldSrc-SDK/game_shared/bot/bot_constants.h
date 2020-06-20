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

// We'll define our own version of this, because everyone else does.
// This needs to stay in sync with MAX_CLIENTS, but there's no header with the #define.
#define BOT_MAX_CLIENTS		32

// version number is MAJOR.MINOR
#define BOT_VERSION_MAJOR	1
#define BOT_VERSION_MINOR	50

// Difficulty levels
enum BotDifficultyType
{
	BOT_EASY = 0,
	BOT_NORMAL,
	BOT_HARD,
	BOT_EXPERT,

	NUM_DIFFICULTY_LEVELS
};
