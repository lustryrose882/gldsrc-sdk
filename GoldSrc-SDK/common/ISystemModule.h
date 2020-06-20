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

class IBaseSystem;
class ISystemModule;

class ISystemModule: public IBaseInterface
{
public:
	virtual ~ISystemModule() {}
	virtual bool Init(IBaseSystem *system, int serial, const char *name) = 0;

	virtual void RunFrame(double time) = 0;
	virtual void ReceiveSignal(ISystemModule *module, unsigned int signal, void *data = nullptr) = 0;
	virtual void ExecuteCommand(int commandID, const char *commandLine) = 0;
	virtual void RegisterListener(ISystemModule *module) = 0;
	virtual void RemoveListener(ISystemModule *module) = 0;

	virtual IBaseSystem *GetSystem() = 0;

	virtual int GetSerial() = 0;
	virtual const char *GetStatusLine() = 0;
	virtual const char *GetType() = 0;
	virtual const char *GetName() = 0;

	virtual int GetState() = 0;
	virtual int GetVersion() = 0;
	virtual void ShutDown() = 0;
};
