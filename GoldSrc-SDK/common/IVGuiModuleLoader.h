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

// Interface to accessing all loaded modules
class IVGuiModuleLoader: public IBaseInterface
{
public:
	virtual int GetModuleCount() = 0;
	virtual const char *GetModuleLabel(int moduleIndex) = 0;
	virtual CreateInterfaceFn GetModuleFactory(int moduleIndex) = 0;
	virtual bool ActivateModule(int moduleIndex) = 0;
	virtual bool ActivateModule(const char *moduleName) = 0;
	virtual void SetPlatformToRestart() = 0;
};

#define VGUIMODULELOADER_INTERFACE_VERSION "VGuiModuleLoader003"
