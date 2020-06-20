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

class INetwork;
class INetChannel;
class NetPacket;

class INetSocket
{
public:
	virtual ~INetSocket() {};

	virtual NetPacket *ReceivePacket() = 0;
	virtual void FreePacket(NetPacket *packet) = 0;
	virtual bool SendPacket(NetPacket *packet) = 0;
	virtual bool SendPacket(NetAddress *to, const void *data, int length) = 0;
	virtual void AddPacket(NetPacket *packet) = 0;
	virtual bool AddChannel(INetChannel *channel) = 0;
	virtual bool RemoveChannel(INetChannel *channel) = 0;

	virtual INetwork *GetNetwork() = 0;
	virtual void OutOfBandPrintf(NetAddress *to, const char *format, ...) = 0;
	virtual void Flush() = 0;
	virtual void GetFlowStats(float *totalIn, float *totalOut) = 0;
	virtual bool LeaveGroup(NetAddress *group) = 0;
	virtual bool JoinGroup(NetAddress *group) = 0;
	virtual void Close() = 0;
	virtual int GetPort() = 0;
};
