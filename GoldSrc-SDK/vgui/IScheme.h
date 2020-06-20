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

class Color;

namespace vgui2
{


using HScheme   = unsigned long;
using HTexture  = unsigned long;

class IImage;
class IBorder;
class KeyValues;

// Holds all panel rendering data
//	This functionality is all wrapped in the Panel::GetScheme*() functions
class IScheme: public IBaseInterface
{
public:
	// gets a string from the default settings section
	virtual const char *GetResourceString(const char *stringName) = 0;

	// returns a pointer to an existing border
	virtual IBorder *GetBorder(const char *borderName) = 0;

	// returns a pointer to an existing font
	virtual HFont GetFont(const char *fontName, bool proportional = false) = 0;

	// colors
	virtual Color GetColor(const char *colorName, Color defaultColor) = 0;

	// virtual destructor
	virtual ~IScheme() {}
};

class ISchemeManager: public IBaseInterface
{
public:
	// loads a scheme from a file
	// first scheme loaded becomes the default scheme, and all subsequent loaded scheme are derivitives of that
	virtual HScheme LoadSchemeFromFile(const char *fileName, const char *tag) = 0;

	// reloads the scheme from the file - should only be used during development
	virtual void ReloadSchemes() = 0;

	// returns a handle to the default (first loaded) scheme
	virtual HScheme GetDefaultScheme() = 0;

	// returns a handle to the scheme identified by "tag"
	virtual HScheme GetScheme(const char *tag) = 0;

	// returns a pointer to an image
	virtual IImage *GetImage(const char *imageName, bool hardwareFiltered = false) = 0;
	virtual HTexture GetImageID(const char *imageName, bool hardwareFiltered = false) = 0;

	// This can only be called at certain times, like during paint()
	// It will assert-fail if you call it at the wrong time...

	// FIXME: This interface should go away!!! It's an icky back-door
	// If you're using this interface, try instead to cache off the information
	// in ApplySchemeSettings
	virtual IScheme *GetIScheme(HScheme scheme) = 0;

	// unload all schemes
	virtual void Shutdown(bool full = true) = 0;

	// gets the proportional coordinates for doing screen-size independant panel layouts
	// use these for font, image and panel size scaling (they all use the pixel height of the display for scaling)
	virtual int GetProportionalScaledValue(int normalizedValue) = 0;
	virtual int GetProportionalNormalizedValue(int scaledValue) = 0;

	// GoldSrc compatibility
	int GetProportionalScaledValueEx(HScheme scheme, int normalizedValue);
	int GetProportionalNormalizedValueEx(HScheme scheme, int scaledValue);
};

inline int ISchemeManager::GetProportionalScaledValueEx(HScheme scheme, int normalizedValue)
{
	return GetProportionalScaledValue(normalizedValue);
}

inline int ISchemeManager::GetProportionalNormalizedValueEx(HScheme scheme, int scaledValue)
{
	return GetProportionalNormalizedValue(scaledValue);
}

class ISchemeManagerEx: public IBaseInterface
{
public:
	// returns a pointer to an image
	virtual IImage *GetImage(const char *imageName, bool hardwareFiltered = false) = 0;
	virtual HTexture GetImageID(const char *imageName, bool hardwareFiltered = false) = 0;
	virtual void DeleteImage(const char *pImageName) = 0;
};

extern ISchemeManagerEx *schemeex();

} // namespace vgui2

#define VGUI_SCHEME_INTERFACE_VERSION "VGUI_Scheme009"
