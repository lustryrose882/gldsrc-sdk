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

#include <vgui/VGUI.h>

class IClientVGUI: public IBaseInterface
{
public:
	virtual void Initialize(CreateInterfaceFn *factories, int count) = 0;
	virtual void Start() = 0;
	virtual void SetParent(vgui2::VPANEL parent) = 0;
	virtual bool UseVGUI1() = 0;
	virtual void HideScoreBoard() = 0;
	virtual void HideAllVGUIMenu() = 0;
	virtual void ActivateClientUI() = 0;
	virtual void HideClientUI() = 0;
	virtual void Shutdown() = 0;
};

#define CLIENTVGUI_INTERFACE_VERSION "VClientVGUI001"

extern IClientVGUI *g_pClientVGUI;
