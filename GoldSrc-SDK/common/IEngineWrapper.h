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

#include "event_args.h"
#include "vmodes.h"

class IBaseSystem;
class ISystemModule;

class IEngineWrapper
{
public:
	virtual ~IEngineWrapper() {}

	virtual bool Init(IBaseSystem *system, int serial, const char *name) = 0;
	virtual void RunFrame(double time) = 0;
	virtual void ReceiveSignal(ISystemModule *module, unsigned int signal, void *data) = 0;
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

	virtual bool GetViewOrigin(float *origin) = 0;
	virtual bool GetViewAngles(float *angles) = 0;
	virtual int GetTraceEntity() = 0;
	virtual float GetCvarFloat(const char *szName) = 0;
	virtual const char *GetCvarString(const char *szName) = 0;
	virtual void SetCvar(const char *szName, const char *szValue) = 0;
	virtual void Cbuf_AddText(const char *text) = 0;
	virtual void DemoUpdateClientData(struct client_data_s *cdat) = 0;
	virtual void CL_QueueEvent(int flags, int index, float delay, event_args_t *pargs) = 0;
	virtual void HudWeaponAnim(int iAnim, int body) = 0;
	virtual void CL_DemoPlaySound(int channel, const char *sample, float attenuation, float vol, int flags, int pitch) = 0;
	virtual void ClientDLL_ReadDemoBuffer(int size, unsigned char *buffer) = 0;
	virtual bool ValidStuffText(const char *cmd) = 0;
	virtual void Cbuf_AddFilteredText(const char *text) = 0;
};

#define ENGINEWRAPPER_INTERFACE_VERSION "enginewrapper002"
