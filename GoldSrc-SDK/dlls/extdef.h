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

#include "regamedll_const.h"

#undef DLLEXPORT
#ifdef _WIN32
	// Attributes to specify an "exported" function, visible from outside the
	// DLL.
	#define DLLEXPORT	__declspec(dllexport)
	// WINAPI should be provided in the windows compiler headers.
	// It's usually defined to something like "__stdcall".

	#define NOINLINE __declspec(noinline)
#else
	#define DLLEXPORT	__attribute__((visibility("default")))
	#define WINAPI		/* */
	#define NOINLINE	__attribute__((noinline))
#endif // _WIN32

// Manual branch optimization for GCC 3.0.0 and newer
#if !defined(__GNUC__) || __GNUC__ < 3
	#define likely(x) (x)
	#define unlikely(x) (x)
#else
	#define likely(x) __builtin_expect(!!(x), 1)
	#define unlikely(x) __builtin_expect(!!(x), 0)
#endif

const int MAX_MAPNAME_LENGHT = 32;

// Simplified macro for declaring/defining exported DLL functions.  They
// need to be 'extern "C"' so that the C++ compiler enforces parameter
// type-matching, rather than considering routines with mis-matched
// arguments/types to be overloaded functions...
//
// AFAIK, this is os-independent, but it's included here in osdep.h where
// DLLEXPORT is defined, for convenience.
#define C_DLLEXPORT extern "C" DLLEXPORT

enum hash_types_e { CLASSNAME };

// Things that toggle (buttons/triggers/doors) need this
enum TOGGLE_STATE { TS_AT_TOP, TS_AT_BOTTOM, TS_GOING_UP, TS_GOING_DOWN };

typedef struct hash_item_s
{
	entvars_t *pev;
	struct hash_item_s *next;
	struct hash_item_s *lastHash;
	int pevIndex;

} hash_item_t;

typedef struct locksounds
{
	string_t sLockedSound;
	string_t sLockedSentence;
	string_t sUnlockedSound;
	string_t sUnlockedSentence;
	int iLockedSentence;
	int iUnlockedSentence;
	float flwaitSound;
	float flwaitSentence;
	byte bEOFLocked;
	byte bEOFUnlocked;

} locksound_t;

typedef struct hudtextparms_s
{
	float x;
	float y;
	int effect;
	byte r1,g1,b1,a1;
	byte r2,g2,b2,a2;
	float fadeinTime;
	float fadeoutTime;
	float holdTime;
	float fxTime;
	int channel;

} hudtextparms_t;

enum USE_TYPE { USE_OFF, USE_ON, USE_SET, USE_TOGGLE };
enum IGNORE_MONSTERS { ignore_monsters = 1, dont_ignore_monsters = 0, missile = 2 };
enum IGNORE_GLASS { ignore_glass = 1, dont_ignore_glass = 0 };
enum { point_hull = 0, human_hull = 1, large_hull = 2, head_hull = 3 };
