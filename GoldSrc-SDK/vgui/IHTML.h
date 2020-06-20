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

// TODO: These methods have not been tested on compatibility.
// Check me.
namespace vgui2
{


// basic interface for a HTML window
class IHTML
{
public:
	// open a new page
	virtual void OpenURL(const char *URL, const char *postData, bool force) = 0;

	virtual bool StopLoading() = 0;	// stops the existing page from loading
	virtual bool Refresh() = 0;		// refreshes the current page
};

// basic callback interface for a HTML window
class IHTMLEvents
{
public:
	// call backs for events
	virtual bool OnStartURL(const char *url, const char *target, bool first) = 0;
	virtual void OnFinishURL(const char *url) = 0;
	virtual void OnProgressURL(long current, long maximum) = 0;
	virtual void OnSetStatusText(const char *text) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnLink() = 0;
	virtual void OffLink() = 0;
};

} // namespace vgui2
