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
#include <vector>

struct MapInfo
{
	const char *name;
	bool defeated;
};

enum CareerDifficultyType
{
	CAREER_DIFFICULTY_EASY = 0,
	CAREER_DIFFICULTY_NORMAL,
	CAREER_DIFFICULTY_HARD,
	CAREER_DIFFICULTY_EXPERT,

	MAX_CAREER_DIFFICULTY,
};

class ICareerTask
{
public:
	virtual bool IsComplete() = 0;
	virtual bool IsCompletedThisRound() = 0;
	virtual bool IsCompletedThisMatch() = 0;
	virtual const char *GetMap() = 0;
	virtual const char *GetTaskName() = 0;
	virtual const wchar_t *GetLocalizedTaskName() = 0;
	virtual const wchar_t *GetLocalizedTaskNameWithCompletion() = 0;
	virtual void Reset() = 0;
	virtual void Set(bool thisRound) = 0;
	virtual void StartRound() = 0;
	virtual const char *GetWeaponName() = 0;
	virtual int GetRepeat() = 0;
	virtual bool MustSurvive() = 0;
	virtual bool InARow() = 0;
	virtual int GetPartial() = 0;
	virtual void SetPartial(int num) = 0;
	virtual bool IsMaxRoundTime() = 0;
};

using ITaskVec = std::vector<ICareerTask *>;

class ICareerUI: public IBaseInterface
{
public:
	virtual bool IsPlayingMatch() = 0;
	virtual ITaskVec *GetCurrentTaskVec() = 0;
	virtual bool PlayAsCT() = 0;
	virtual int GetReputationGained() = 0;
	virtual int GetNumMapsUnlocked() = 0;
	virtual bool DoesWinUnlockAll() = 0;
	virtual int GetRoundTimeLength() = 0;
	virtual int GetWinfastLength() = 0;
	virtual CareerDifficultyType GetDifficulty() const = 0;
	virtual int GetCurrentMapTriplet(MapInfo *maps) = 0;
	virtual void OnRoundEndMenuOpen(bool didWin) = 0;
	virtual void OnMatchEndMenuOpen(bool didWin) = 0;
	virtual void OnRoundEndMenuClose(bool stillPlaying) = 0;
	virtual void OnMatchEndMenuClose(bool stillPlaying) = 0;
};

#define CAREERUI_INTERFACE_VERSION "CareerUI001"

extern ICareerUI *g_pCareerUI;
