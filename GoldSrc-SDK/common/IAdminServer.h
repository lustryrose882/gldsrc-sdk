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

// handle to a game window
typedef unsigned int ManageServerUIHandle_t;
class IManageServer;

// Purpose: Interface to server administration functions
class IAdminServer: public IBaseInterface
{
public:
	// opens a manage server dialog for a local server
	virtual ManageServerUIHandle_t OpenManageServerDialog(const char *serverName, const char *gameDir) = 0;

	// opens a manage server dialog to a remote server
	virtual ManageServerUIHandle_t OpenManageServerDialog(unsigned int gameIP, unsigned int gamePort, const char *password) = 0;

	// forces the game info dialog closed
	virtual void CloseManageServerDialog(ManageServerUIHandle_t gameDialog) = 0;

	// Gets a handle to the interface
	virtual IManageServer *GetManageServerInterface(ManageServerUIHandle_t handle) = 0;
};

#define ADMINSERVER_INTERFACE_VERSION "AdminServer002"
