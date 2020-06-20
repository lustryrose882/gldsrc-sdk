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

class IWorld;
class IProxy;
class IDirector;
class INetSocket;
class ISystemModule;
class IBaseSystem;

class NetAddress;
class InfoString;
class BitBuffer;

class IServer
{
public:
	virtual ~IServer() {}

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

	virtual bool Connect(IWorld *world, NetAddress *adr, INetSocket *socket) = 0;
	virtual bool LoadDemo(IWorld *world, const char *filename, bool forceHLTV, bool continuous) = 0;
	virtual void Reconnect() = 0;
	virtual void Disconnect() = 0;
	virtual void Retry() = 0;
	virtual void StopRetry() = 0;
	virtual void SendStringCommand(const char *command) = 0;
	virtual void SendHLTVCommand(BitBuffer *msg) = 0;
	virtual bool IsConnected() = 0;
	virtual bool IsDemoFile() = 0;
	virtual bool IsGameServer() = 0;
	virtual bool IsRelayProxy() = 0;
	virtual bool IsVoiceBlocking() = 0;
	virtual void SetProxy(IProxy *proxy) = 0;
	virtual void SetDirector(IDirector *director) = 0;
	virtual void SetPlayerName(const char *newName) = 0;
	virtual void SetDelayReconnect(bool state) = 0;
	virtual void SetAutoRetry(bool state) = 0;
	virtual void SetVoiceBlocking(bool state) = 0;
	virtual void SetRate(int rate) = 0;
	virtual void SetUpdateRate(int updaterate) = 0;
	virtual void SetUserInfo(const char *key, const char *value) = 0;
	virtual bool SetProtocol(int version) = 0;
	virtual void SetGameDirectory(const char *defaultDir, const char *gameDir = nullptr) = 0;
	virtual int GetRate() = 0;
	virtual int GetUpdateRate() = 0;
	virtual InfoString *GetServerInfoString() = 0;
	virtual const char *GetPlayerName() = 0;
	virtual float GetTime() = 0;
	virtual IWorld *GetWorld() = 0;
	virtual const char *GetDemoFileName() = 0;
	virtual NetAddress *GetAddress() = 0;
	virtual const char *GetHostName() = 0;
	virtual bool GetAutoRetry() = 0;
	virtual float GetPacketLoss() = 0;
	virtual int GetProtocol() = 0;
};

#define SERVER_INTERFACE_VERSION "server001"
