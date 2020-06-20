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
#include "vgui/VGUI.h"
#include "common/SteamCommon.h"

// Forward declarations
namespace vgui2
{
	class Panel;
};

enum VGUIPANEL
{
	PANEL_ROOT = 0,
	PANEL_CLIENTDLL,
	PANEL_GAMEUIDLL
};

class IEngineVGui: public IBaseInterface
{
public:
	virtual vgui2::VPANEL GetPanel(VGUIPANEL type) = 0;
	virtual bool SteamRefreshLogin(const char *password, bool isSecure) = 0;
	virtual bool SteamProcessCall(bool *finished, TSteamProgress *progress, TSteamError *steamError) = 0;
};

extern IEngineVGui *g_pEngineVGUI;

#define VENGINE_VGUI_VERSION "VEngineVGui001"
