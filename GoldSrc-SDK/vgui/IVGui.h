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

#include <vgui/VGUI.h>
#include <appframework/IAppSystem.h>

namespace vgui2
{


class KeyValues;

enum
{
	DEFAULT_VGUI_CONTEXT = ((vgui2::HContext)~0)
};

// undefine windows function macros that overlap
#ifdef PostMessage
#undef PostMessage
#endif

#ifdef SetCursor
#undef SetCursor
#endif

// Interface to core vgui components
class IVGui: public IBaseInterface, public IAppSystem
{
public:
	virtual bool Init(CreateInterfaceFn *factoryList, int numFactories) = 0;
	virtual void Shutdown() = 0;

	virtual void Start() = 0;			// activates vgui message pump
	virtual void Stop() = 0;			// signals vgui to Stop running
	virtual bool IsRunning() = 0;		// returns true if vgui is current active
	virtual void RunFrame() = 0;		// runs a single frame of vgui

	// broadcasts "ShutdownRequest" "id" message to all top-level panels in the app
	virtual void ShutdownMessage(unsigned int shutdownID) = 0;

	// panel allocation
	virtual VPANEL AllocPanel() = 0;
	virtual void FreePanel(VPANEL panel) = 0;

	// debugging prints
	virtual void DPrintf(const char *format, ...) = 0;
	virtual void DPrintf2(const char *format, ...) = 0;
	virtual void SpewAllActivePanelNames() = 0;

	// safe-pointer handle methods
	virtual HPanel PanelToHandle(VPANEL panel) = 0;
	virtual VPANEL HandleToPanel(HPanel index) = 0;
	virtual void MarkPanelForDeletion(VPANEL panel) = 0;

	// makes panel receive a 'Tick' message every frame (~50ms, depending on sleep times/framerate)
	// panel is automatically removed from tick signal list when it's deleted
	virtual void AddTickSignal(VPANEL panel, int intervalMilliseconds = 0) = 0;
	virtual void RemoveTickSignal(VPANEL panel) = 0;

	// message sending
	virtual void PostMessage(VPANEL target, KeyValues *params, VPANEL from, float delaySeconds = 0.0f) = 0;

	// Creates/ destroys vgui contexts, which contains information
	// about which controls have mouse + key focus, for example.
	virtual HContext CreateContext() = 0;
	virtual void DestroyContext(HContext context) = 0;

	// Associates a particular panel with a vgui context
	// Associating NULL is valid; it disconnects the panel from the context
	virtual void AssociatePanelWithContext(HContext context, VPANEL pRoot) = 0;

	// Activates a particular context, use DEFAULT_VGUI_CONTEXT
	// to get the one normally used by VGUI
	virtual void ActivateContext(HContext context) = 0;

	virtual void SetSleep(bool state) = 0;			// whether to sleep each frame or not, true = sleep
	virtual bool GetShouldVGuiControlSleep() = 0;	// data accessor for above

	// virtual destructor
	virtual ~IVGui() {}
};

} // namespace vgui2

#define VGUI_IVGUI_INTERFACE_VERSION "VGUI_ivgui006"
