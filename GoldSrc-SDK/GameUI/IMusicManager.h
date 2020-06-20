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

enum TrackType
{
	TRACKTYPE_INVALID = 1,
	TRACKTYPE_SPLASH,
	TRACKTYPE_ROUNDWIN,
	TRACKTYPE_ROUNDLOSE,
	TRACKTYPE_MATCHWIN,
	TRACKTYPE_MATCHLOSE,
	TRACKTYPE_CREDITS,
	TRACKTYPE_NUM,
};

class IMusicManager: public IBaseInterface
{
public:
	virtual void StartTrack(TrackType track, bool looping) = 0;
	virtual void StopTrack() = 0;
	virtual void FadeOutTrack() = 0;
	virtual bool IsPlayingTrack() const = 0;
	virtual bool IsPlayingTrack(TrackType track) const = 0;

protected:
	virtual ~IMusicManager() {}
};

#define MUSICMGR_INTERFACE_VERSION "MusicManager001"

extern IMusicManager *g_pMusicManager;
