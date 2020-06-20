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

#include "ISystemModule.h"
#include "IVGuiModule.h"
#include "common/ObjectList.h"

namespace vgui2 {

class Panel;
} // namespace vgui2

class IFileSystem;

class IBaseSystem: virtual public ISystemModule
{
public:
	virtual ~IBaseSystem() {}

	virtual double GetTime() = 0;
	virtual unsigned int GetTick() = 0;
	virtual void SetFPS(float fps) = 0;

	virtual void Printf(const char *fmt, ...) = 0;
	virtual void DPrintf(const char *fmt, ...) = 0;

	virtual void RedirectOutput(char *buffer = nullptr, int maxSize = 0) = 0;

	virtual IFileSystem *GetFileSystem() = 0;
	virtual unsigned char *LoadFile(const char *name, int *length = nullptr) = 0;
	virtual void FreeFile(unsigned char *fileHandle) = 0;

	virtual void SetTitle(const char *text) = 0;
	virtual void SetStatusLine(const char *text) = 0;

	virtual void ShowConsole(bool visible) = 0;
	virtual void LogConsole(const char *filename) = 0;

	virtual bool InitVGUI(IVGuiModule *module) = 0;

#ifdef _WIN32
	virtual vgui2::Panel *GetPanel() = 0;
#endif // _WIN32

	virtual bool RegisterCommand(const char *name, ISystemModule *module, int commandID) = 0;
	virtual void GetCommandMatches(const char *string, ObjectList<const char> *pMatchList) = 0;
	virtual void ExecuteString(const char *commands) = 0;
	virtual void ExecuteFile(const char *filename) = 0;
	virtual void Errorf(const char *fmt, ...) = 0;

	virtual const char *CheckParam(const char *param) = 0;

	virtual bool AddModule(ISystemModule *module, const char *name) = 0;
	virtual ISystemModule *GetModule(const char *interfacename, const char *library, const char *instancename = nullptr) = 0;
	virtual bool RemoveModule(ISystemModule *module) = 0;

	virtual void Stop() = 0;
	virtual const char *GetBaseDir() = 0;
};

#define BASESYSTEM_INTERFACE_VERSION "basesystem002"
