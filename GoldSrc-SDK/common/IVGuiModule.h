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

#include <vgui/VGUI.h>
#include "tier1/interface.h"

// Standard interface to loading vgui modules
class IVGuiModule: public IBaseInterface
{
public:
	// called first to setup the module with the vgui
	// returns true on success, false on failure
	virtual bool Initialize(CreateInterfaceFn *vguiFactories, int factoryCount) = 0;

	// called after all the modules have been initialized
	// modules should use this time to link to all the other module interfaces
	virtual bool PostInitialize(CreateInterfaceFn *modules = nullptr, int factoryCount = 0) = 0;

	// called when the module is selected from the menu or otherwise activated
	virtual bool Activate() = 0;

	// returns true if the module is successfully initialized and available
	virtual bool IsValid() = 0;

	// requests that the UI is temporarily disabled and all data files saved
	virtual void Deactivate() = 0;

	// restart from a Deactivate()
	virtual void Reactivate() = 0;

	// called when the module is about to be shutdown
	virtual void Shutdown() = 0;

	// returns a handle to the main module panel
	virtual vgui2::VPANEL GetPanel() = 0;

	// sets the parent of the main module panel
	virtual void SetParent(vgui2::VPANEL parent) = 0;

	// messages sent through through the panel returned by GetPanel():
	//
	//  "ConnectedToGame"	"ip" "port" "gamedir"
	//	"DisconnectedFromGame"
	//  "ActiveGameName"	"name"
	//	"LoadingStarted"	"type"	"name"
	//  "LoadingFinished"	"type"	"name"

	virtual void RunFrame() = 0;
};

#define VGUIMODULE_ADMIN_INTERFACE_VERSION "VGuiModuleAdminServer001"
#define VGUIMODULE_INTERFACE_VERSION       "VGuiModuleServerBrowser001"
