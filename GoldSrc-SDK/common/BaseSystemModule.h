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

#include "ObjectList.h"
#include "IBaseSystem.h"

// C4250 - 'class1' : inherits 'BaseSystemModule::member' via dominance
#ifdef _MSC_VER
#pragma warning(disable:4250)
#endif

class BaseSystemModule: virtual public ISystemModule
{
public:
	BaseSystemModule();
	virtual ~BaseSystemModule() {}

	virtual bool Init(IBaseSystem *system, int serial, const char *name);
	virtual void RunFrame(double time);
	virtual void ReceiveSignal(ISystemModule *module, unsigned int signal, void *data);
	virtual void ExecuteCommand(int commandID, const char *commandLine);
	virtual void RegisterListener(ISystemModule *module);
	virtual void RemoveListener(ISystemModule *module);
	virtual IBaseSystem *GetSystem();
	virtual int GetSerial();
	virtual const char *GetStatusLine();
	virtual const char *GetType();
	virtual const char *GetName();

	enum ModuleState
	{
		MODULE_UNDEFINED = 0,
		MODULE_INITIALIZING,
		MODULE_CONNECTING,
		MODULE_RUNNING,
		MODULE_DISCONNECTED
	};

	virtual int GetState();
	virtual int GetVersion();
	virtual void ShutDown();
	virtual const char *GetBaseDir() { return ""; }
	void FireSignal(unsigned int signal, void *data = nullptr);

protected:
	IBaseSystem *m_System;
	ObjectList<ISystemModule> m_Listener;
	char m_Name[255];
	unsigned int m_State;
	unsigned int m_Serial;
	double m_SystemTime;
};
