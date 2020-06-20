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

class INetSocket;
class INetwork
{
public:
	virtual ~INetwork() {};

	virtual bool Init(IBaseSystem *system, int serial, char *name) = 0;
	virtual void RunFrame(double time) = 0;
	virtual void ReceiveSignal(ISystemModule *module, unsigned int signal, void *data) = 0;
	virtual void ExecuteCommand(int commandID, char *commandLine) = 0;
	virtual void RegisterListener(ISystemModule *module) = 0;
	virtual void RemoveListener(ISystemModule *module) = 0;
	virtual IBaseSystem *GetSystem() = 0;
	virtual int GetSerial() = 0;
	virtual char *GetStatusLine() = 0;
	virtual char *GetType() = 0;
	virtual char *GetName() = 0;
	virtual int GetState() = 0;
	virtual int GetVersion() = 0;
	virtual void ShutDown() = 0;

	virtual INetSocket *CreateSocket(int port, bool reuse = false, bool loopback = false) = 0;
	virtual bool RemoveSocket(INetSocket *netsocket) = 0;
	virtual NetAddress *GetLocalAddress() = 0;
	virtual bool ResolveAddress(char *string, NetAddress *address) = 0;
	virtual void GetFlowStats(float *totalIn, float *totalOut) = 0;
	virtual int GetLastErrorCode() = 0;
	virtual char *GetErrorText(int code) = 0;
};

#define NETWORK_INTERFACE_VERSION "network001"
