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

#include <vgui/IInput.h>

namespace vgui2
{

typedef int HInputContext;

#define DEFAULT_INPUT_CONTEXT ((vgui2::HInputContext)~0)

class IInputInternal: public IInput
{
public:
	// processes input for a frame
	virtual void RunFrame() = 0;
	virtual void UpdateMouseFocus(int x, int y) = 0;

	// called when a panel becomes invalid
	virtual void PanelDeleted(VPANEL panel) = 0;

	// inputs into vgui2 input handling
	virtual bool InternalCursorMoved(int x,int y) = 0; //expects input in surface space
	virtual bool InternalMousePressed(MouseCode code) = 0;
	virtual bool InternalMouseDoublePressed(MouseCode code) = 0;
	virtual bool InternalMouseReleased(MouseCode code) = 0;
	virtual bool InternalMouseWheeled(int delta) = 0;
	virtual bool InternalKeyCodePressed(KeyCode code) = 0;
	virtual void InternalKeyCodeTyped(KeyCode code) = 0;
	virtual void InternalKeyTyped(wchar_t unichar) = 0;
	virtual bool InternalKeyCodeReleased(KeyCode code) = 0;

	// Creates/ destroys "input" contexts, which contains information
	// about which controls have mouse + key focus, for example.
	virtual HInputContext CreateInputContext() = 0;
	virtual void DestroyInputContext(HInputContext context) = 0;

	// Associates a particular panel with an input context
	// Associating NULL is valid; it disconnects the panel from the context
	virtual void AssociatePanelWithInputContext(HInputContext context, VPANEL pRoot) = 0;

	// Activates a particular input context, use DEFAULT_INPUT_CONTEXT
	// to get the one normally used by VGUI
	virtual void ActivateInputContext(HInputContext context) = 0;

	// virtual destructor
	virtual ~IInputInternal() {}
};

} // namespace vgui2

#define VGUI_INPUTINTERNAL_INTERFACE_VERSION "VGUI_InputInternal001"
