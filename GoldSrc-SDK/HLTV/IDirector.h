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
#include "IObjectContainer.h"

class IWorld;
class IProxy;
class BitBuffer;
class DirectorCmd;

class IDirector: virtual public ISystemModule
{
public:
	virtual ~IDirector() {}

	virtual void NewGame(IWorld *world, IProxy *proxy) = 0;
	virtual const char *GetModName() = 0;
	virtual void WriteCommands(BitBuffer *stream, float startTime, float endTime) = 0;
	virtual int AddCommand(DirectorCmd *cmd) = 0;
	virtual bool RemoveCommand(int index) = 0;
	virtual DirectorCmd *GetLastCommand() = 0;
	virtual IObjectContainer<DirectorCmd> *GetCommands() = 0;
};

#define DIRECTOR_INTERFACE_VERSION "director001"
