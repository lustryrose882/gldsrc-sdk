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

class IWorld;
class InfoString;
class IClient: virtual public ISystemModule
{
public:
	virtual ~IClient() {}

	virtual bool Connect(INetSocket *socket, NetAddress *adr, char *userinfo) = 0;
	virtual void Send(unsigned char *data, int length, bool isReliable) = 0;
	virtual void Disconnect(const char *reason = nullptr) = 0;
	virtual void Reconnect() = 0;
	virtual void SetWorld(IWorld *world) = 0;
	virtual int GetClientType() = 0;
	virtual char *GetClientName() = 0;
	virtual InfoString *GetUserInfo() = 0;
	virtual NetAddress *GetAddress() = 0;
	virtual bool IsActive() = 0;
	virtual bool IsHearingVoices() = 0;
	virtual bool HasChatEnabled() = 0;
};

#define CLIENT_INTERFACE_VERSION "client001"
