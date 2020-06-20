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

// Here are all the flags we support:
// DBGFLAG_MEMORY:         Enables our memory debugging system, which overrides malloc & free
// DBGFLAG_MEMORY_NEWDEL:  Enables new / delete tracking for memory debug system.  Requires DBGFLAG_MEMORY to be enabled.
// DBGFLAG_VALIDATE:       Enables our recursive validation system for checking integrity and memory leaks
// DBGFLAG_ASSERT:         Turns Assert on or off (when off, it isn't compiled at all)
// DBGFLAG_ASSERTFATAL:    Turns AssertFatal on or off (when off, it isn't compiled at all)
// DBGFLAG_ASSERTDLG:      Turns assert dialogs on or off and debug breaks on or off when not under the debugger.
//                         (Dialogs will always be on when process is being debugged.)
// DBGFLAG_STRINGS:        Turns on hardcore string validation (slow but safe)

#undef DBGFLAG_MEMORY
#undef DBGFLAG_MEMORY_NEWDEL
#undef DBGFLAG_VALIDATE
#undef DBGFLAG_ASSERT
#undef DBGFLAG_ASSERTFATAL
#undef DBGFLAG_ASSERTDLG
#undef DBGFLAG_STRINGS

// Default flags for debug builds
#ifdef _DEBUG

#define DBGFLAG_MEMORY
#ifdef _SERVER	// only enable new & delete tracking for server; on client it conflicts with CRT mem leak tracking
#define DBGFLAG_MEMORY_NEWDEL
#endif

#if !defined(DBGFLAG_NO_VALIDATE) || defined(STEAM)
//#define DBGFLAG_VALIDATE		// note: not implemented yet
#endif

#if !defined(DBGFLAG_NO_ASSERT)
#define DBGFLAG_ASSERT
#endif

#if !defined(DBGFLAG_NO_ASSERTFATAL)
#define DBGFLAG_ASSERTFATAL				// note: fatal asserts are enabled in release builds
#endif

#if !defined(DBGFLAG_NO_ASSERTDLG)
#define DBGFLAG_ASSERTDLG
#endif

#if !defined(DBGFLAG_NO_STRINGS)
#define DBGFLAG_STRINGS
#endif

// Default flags for release builds
#else // _DEBUG

#ifdef STEAM
#define DBGFLAG_ASSERT
#endif

#if !defined(DBGFLAG_NO_VALIDATE)
//#define DBGFLAG_VALIDATE		// note: not implemented yet
#endif

#if !defined(DBGFLAG_NO_ASSERT)
#define DBGFLAG_ASSERT
#endif

#if !defined(DBGFLAG_NO_ASSERTFATAL)
#define DBGFLAG_ASSERTFATAL				// note: fatal asserts are enabled in release builds
#endif

#if !defined(DBGFLAG_NO_ASSERTDLG)
#define DBGFLAG_ASSERTDLG
#endif

#endif // _DEBUG
