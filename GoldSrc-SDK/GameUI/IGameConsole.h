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

#include "tier1/interface.h"

// Interface to game/dev console
class IGameConsole: public IBaseInterface
{
public:
	// activates the console, makes it visible and brings it to the foreground
	virtual void Activate() = 0;
	virtual void Initialize() = 0;

	// hides the console
	virtual void Hide() = 0;

	// clears the console
	virtual void Clear() = 0;

	// return true if the console has focus
	virtual bool IsConsoleVisible() = 0;
	virtual void Printf(const char *format, ...) = 0;
	virtual void DPrintf(const char *format, ...) = 0;

	virtual void SetParent(vgui2::VPANEL parent) = 0;

	// Extended only GSClient
	virtual void PrintfColor(char (&string)[4096]) = 0;
	virtual void PrintfColor(const Color &clr, const char *format, ...) = 0;

	virtual Color &GetColor() = 0;
	virtual Color &GetDColor() = 0;
};

extern IGameConsole *g_pIGameConsole;

#define GAMECONSOLE_INTERFACE_VERSION "GameConsole003"
#define GAMECONSOLE_INTERFACE_VERSION_ENHANCED "GameConsole004"
