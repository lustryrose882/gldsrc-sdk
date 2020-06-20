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

struct gamehud_t;

// Exports a set of functions for the GameUI interface to interact with the game client
class IGameClientExports: public IBaseInterface
{
public:
	virtual void Start(cl_enginefuncex_t *engineFuncsEx) = 0;
	virtual void Initialize(CreateInterfaceFn *factories, int count) = 0;

	// returns the name of the server the user is connected to, if any
	virtual const char *GetServerHostName() = 0;

	// ingame voice manipulation
	virtual bool IsPlayerGameVoiceMuted(int playerIndex) = 0;
	virtual void MutePlayerGameVoice(int playerIndex) = 0;
	virtual void UnmutePlayerGameVoice(int playerIndex) = 0;

private:
	// NOTE: This functions not supposes to use for external stuff
	virtual void SetInternalPadFunction(void *addr) = 0;
	virtual bool GetClientHudBinding(gamehud_t *phud, int iSize) = 0;
};

#define GAMECLIENTEXPORTS_INTERFACE_VERSION "GameClientExports002"
