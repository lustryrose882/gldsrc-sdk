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

namespace vgui2
{


class IScheme;
class KeyValues;

// Interface to panel borders
//	Borders have a close relationship with panels
//	They are the edges of the panel.
class IBorder
{
public:
	virtual void Paint(VPANEL panel) = 0;
	virtual void Paint(int x0, int y0, int x1, int y1) = 0;
	virtual void Paint(int x0, int y0, int x1, int y1, int breakSide, int breakStart, int breakStop) = 0;
	virtual void SetInset(int left, int top, int right, int bottom) = 0;
	virtual void GetInset(int &left, int &top, int &right, int &bottom) = 0;
	virtual void ApplySchemeSettings(IScheme *pScheme, KeyValues *inResourceData) = 0;
	virtual const char *GetName() = 0;
	virtual void SetName(const char *name) = 0;

	enum sides_e
	{
		SIDE_LEFT = 0,
		SIDE_TOP = 1,
		SIDE_RIGHT = 2,
		SIDE_BOTTOM = 3
	};
};

} // namespace vgui2
