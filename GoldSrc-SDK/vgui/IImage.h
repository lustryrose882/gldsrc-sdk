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

class Color;

namespace vgui2
{


// Interface to drawing an image
class IImage
{
public:
	// Call to Paint the image
	// Image will draw within the current panel context at the specified position
	virtual void Paint() = 0;

	virtual void SetPos(int x, int y) = 0;					// Set the position of the image
	virtual void GetContentSize(int &wide, int &tall) = 0;	// Gets the size of the content
	virtual void GetSize(int &wide, int &tall) = 0;			// Get the size the image will actually draw in (usually defaults to the content size)
	virtual void SetSize(int wide, int tall) = 0;			// Sets the size of the image
	virtual void SetColor(Color col) = 0;					// Set the draw color

	// virtual destructor
	virtual ~IImage() {}
};

} // namespace vgui2
