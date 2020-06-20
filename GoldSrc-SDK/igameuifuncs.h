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
#include "vgui/KeyCode.h"
#include "modes.h"

class IGameUIFuncs: public IBaseInterface
{
public:
	virtual bool IsKeyDown(const char *keyname, bool &isdown) = 0;
	virtual const char *Key_NameForKey(int keynum) = 0;
	virtual const char *Key_BindingForKey(int keynum) = 0;
	virtual vgui2::KeyCode GetVGUI2KeyCodeForBind(const char *bind) = 0;
	virtual void GetVideoModes(vmode_t **liststart, int *count) = 0;
	virtual void GetCurrentVideoMode(int *wide, int *tall, int *bpp) = 0;
	virtual void GetCurrentRenderer(char *name, int namelen, int *windowed, int *hdmodels, int *addons_folder, int *vid_level) = 0;
	virtual bool IsConnectedToVACSecureServer() = 0;
	virtual int Key_KeyStringToKeyNum(const char *pchKey) = 0;

protected:
	virtual ~IGameUIFuncs() {}
};

#define VENGINE_GAMEUIFUNCS_VERSION "VENGINE_GAMEUIFUNCS_VERSION001"
