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

struct cl_enginefuncs_s;

// Contains all the functions that the BaseUI code exports
class IBaseUI: public IBaseInterface
{
public:
	virtual void Initialize(CreateInterfaceFn *factories, int count) = 0;
	virtual void Start(struct cl_enginefuncs_s *engineFuncs, int interfaceVersion) = 0;
	virtual void Shutdown() = 0;

	virtual BOOL Key_Event(BOOL down, int keynum, const char *pszCurrentBinding) = 0;
	virtual void CallEngineSurfaceAppHandler(void *event, void *userData) = 0;
	virtual void Paint(int x, int y, int right, int bottom) = 0;
	virtual void HideGameUI() = 0;
	virtual void ActivateGameUI() = 0;
	virtual void HideConsole() = 0;
	virtual void ShowConsole() = 0;
};

extern IBaseUI *g_pIBaseUI;

#define BASEUI_INTERFACE_VERSION "BaseUI001"
