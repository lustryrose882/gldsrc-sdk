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

#include "maintypes.h"
#include "tier1/interface.h"

class IGameServerData : public IBaseInterface
{
public:
	virtual ~IGameServerData() {};

	virtual void WriteDataRequest(const void *buffer, int bufferSize) = 0;
	virtual int ReadDataResponse(void *data, int len) = 0;
};

#define GAMESERVERDATA_INTERFACE_VERSION "GameServerData001"
