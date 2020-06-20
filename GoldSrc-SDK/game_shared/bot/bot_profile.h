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

// long STL names get truncated in browse info.
#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#ifndef _WIN32
#include <strings.h>
#include <stdio.h>
#endif // _WIN32

#undef min
#undef max

#include <list>
#include <vector>

#include "bot_constants.h"

enum
{
	FirstCustomSkin = 100,
	NumCustomSkins = 100,
	LastCustomSkin = FirstCustomSkin + NumCustomSkins - 1,
};

enum BotProfileTeamType
{
	BOT_TEAM_T,
	BOT_TEAM_CT,
	BOT_TEAM_ANY
};

class BotProfile {
public:
	const char *GetName() const { return m_name; }
	float GetAggression() const { return m_aggression; }
	float GetSkill() const { return m_skill; }
	float GetTeamwork() const { return m_teamwork; }
	int GetWeaponPreference(int i) const { return m_weaponPreference[i]; }
	int GetWeaponPreferenceCount() const { return m_weaponPreferenceCount; }
	int GetCost() const { return m_cost; }
	int GetSkin() const { return m_skin; }
	int GetVoicePitch() const { return m_voicePitch; }
	float GetReactionTime() const { return m_reactionTime; }
	float GetAttackDelay() const { return m_attackDelay; }
	int GetVoiceBank() const { return m_voiceBank; }
	bool PrefersSilencer() const { return m_prefersSilencer; }
public:
	friend class BotProfileManager;

	char *m_name;
	float m_aggression;
	float m_skill;
	float m_teamwork;

	enum { MAX_WEAPON_PREFS = 16 };

	int m_weaponPreference[MAX_WEAPON_PREFS];
	int m_weaponPreferenceCount;

	int m_cost;
	int m_skin;

	unsigned char m_difficultyFlags;
	int m_voicePitch;
	float m_reactionTime;
	float m_attackDelay;
	enum BotProfileTeamType m_teams;
	bool m_prefersSilencer;
	int m_voiceBank;
};

typedef std::list<BotProfile *> BotProfileList;

class BotProfileManager
{
public:
	typedef std::vector<char *> VoiceBankList;
	const BotProfileList *GetProfileList() const { return &m_profileList; }
	const VoiceBankList *GetVoiceBanks() const { return &m_voiceBanks; }

public:
	BotProfileList m_profileList;
	VoiceBankList m_voiceBanks;

	char *m_skins[NumCustomSkins];
	char *m_skinModelnames[NumCustomSkins];
	char *m_skinFilenames[NumCustomSkins];
	int m_nextSkin;
};
