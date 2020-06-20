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

#include "modes.h"

class IVideoMode
{
public:
	virtual	const char		*GetName() const = 0;

	virtual	bool			Init(void *pvInstance) = 0;
	virtual void			Shutdown() = 0;
	virtual bool			AddMode(int width, int height, int bpp) = 0;

	// Returns the fullscreen modes for the adapter the game was started on
	virtual struct vmode_s *GetCurrentMode() = 0;
	virtual struct vmode_s *GetMode(int num = 0) = 0;
	virtual int				GetModeCount() const = 0;

	virtual bool			IsWindowedMode() const = 0;
	virtual bool			GetInitialized() const = 0;
	virtual void			SetInitialized(bool init) = 0;

	// This is called in response to a WM_MOVE message
	// or whatever the equivalent that would be under linux
	virtual void			UpdateWindowPosition() = 0;
	virtual void			FlipScreen() = 0;

	// Alt-tab handling
	virtual void			RestoreVideo() = 0;
	virtual void			ReleaseVideo() = 0;
};
