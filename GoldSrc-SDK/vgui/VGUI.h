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

namespace vgui2
{

#if defined(_WIN32)
	constexpr auto lib = "vgui2.dll";
#elif defined(LINUX)
	constexpr auto lib = "vgui2.so";
#elif defined(OSX)
	constexpr auto lib = "vgui2.dylib";
#else
	#error "Unsupported Platform."
#endif // #if defined(_WIN32) || defined(LINUX) || defined(OSX)

// handle to an internal vgui panel
// this is the only handle to a panel that is valid across dll boundaries
typedef unsigned int VPANEL;

// handles to vgui objects
// NULL values signify an invalid value
typedef unsigned long HScheme;
typedef unsigned long HTexture;
typedef unsigned long HCursor;

typedef int HContext;
typedef unsigned long HPanel;
typedef unsigned long HFont;

// the value of an invalid font handle
constexpr VPANEL NULL_PANEL     = {0u};
constexpr HFont  INVALID_FONT   = {0u};
constexpr HPanel INVALID_PANEL  = {0u};

} // namespace vgui2
