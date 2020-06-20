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

class INetSocket;
class IBaseSystem;
class INetChannel
{
public:
	virtual ~INetChannel() {}

	virtual bool Create(IBaseSystem *system, INetSocket *netsocket = nullptr, NetAddress *adr = nullptr) = 0;
	virtual NetAddress *GetTargetAddress() = 0;
	virtual void Close() = 0;
	virtual void Clear() = 0;
	virtual void Reset() = 0;
	virtual bool IsConnected() = 0;
	virtual bool IsReadyToSend() = 0;
	virtual bool IsCrashed() = 0;
	virtual bool IsTimedOut() = 0;
	virtual bool IsFakeChannel() = 0;
	virtual bool KeepAlive() = 0;
	virtual void SetRate(int newRate) = 0;
	virtual void SetUpdateRate(int newupdaterate) = 0;
	virtual void SetTimeOut(float time) = 0;
	virtual void SetKeepAlive(bool flag) = 0;
	virtual float GetIdleTime() = 0;
	virtual int GetRate() = 0;
	virtual int GetUpdateRate() = 0;
	virtual float GetLoss() = 0;
	virtual void TransmitOutgoing() = 0;
	virtual void ProcessIncoming(unsigned char *data, int size) = 0;
	virtual void OutOfBandPrintf(const char *format, ...) = 0;
	virtual void FakeAcknowledgement() = 0;
};
