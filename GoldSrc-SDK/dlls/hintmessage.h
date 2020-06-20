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

#include "tier1/utlvector.h"

#define DHF_ROUND_STARTED     BIT(1)
#define DHF_HOSTAGE_SEEN_FAR  BIT(2)
#define DHF_HOSTAGE_SEEN_NEAR BIT(3)
#define DHF_HOSTAGE_USED      BIT(4)
#define DHF_HOSTAGE_INJURED   BIT(5)
#define DHF_HOSTAGE_KILLED    BIT(6)
#define DHF_FRIEND_SEEN       BIT(7)
#define DHF_ENEMY_SEEN        BIT(8)
#define DHF_FRIEND_INJURED    BIT(9)
#define DHF_FRIEND_KILLED     BIT(10)
#define DHF_ENEMY_KILLED      BIT(11)
#define DHF_BOMB_RETRIEVED    BIT(12)
#define DHF_AMMO_EXHAUSTED    BIT(15)
#define DHF_IN_TARGET_ZONE    BIT(16)
#define DHF_IN_RESCUE_ZONE    BIT(17)
#define DHF_IN_ESCAPE_ZONE    BIT(18)
#define DHF_IN_VIPSAFETY_ZONE BIT(19)
#define DHF_NIGHTVISION       BIT(20)
#define DHF_HOSTAGE_CTMOVE    BIT(21)
#define DHF_SPEC_DUCK         BIT(22)

#define DHM_ROUND_CLEAR       (DHF_ROUND_STARTED | DHF_HOSTAGE_KILLED | DHF_FRIEND_KILLED | DHF_BOMB_RETRIEVED)
#define DHM_CONNECT_CLEAR     (DHF_HOSTAGE_SEEN_FAR | DHF_HOSTAGE_SEEN_NEAR | DHF_HOSTAGE_USED | DHF_HOSTAGE_INJURED | DHF_FRIEND_SEEN | DHF_ENEMY_SEEN | DHF_FRIEND_INJURED | DHF_ENEMY_KILLED | DHF_AMMO_EXHAUSTED | DHF_IN_TARGET_ZONE | DHF_IN_RESCUE_ZONE | DHF_IN_ESCAPE_ZONE | DHF_IN_VIPSAFETY_ZONE | DHF_HOSTAGE_CTMOVE | DHF_SPEC_DUCK)

class CHintMessage
{
public:
	CHintMessage(const char *hintString, bool isHint, CUtlVector<const char *> *args, float duration);
	~CHintMessage();
public:
	float GetDuration() const { return m_duration; }
	void Send(CBaseEntity *client);

private:
	const char *m_hintString;
	bool m_isHint;
	CUtlVector<char *> m_args;
	float m_duration;
};

class CHintMessageQueue
{
public:
	void Reset();
	void Update(CBaseEntity *client);
	bool AddMessage(const char *message, float duration, bool isHint, CUtlVector<const char *> *args);
	bool IsEmpty() const { return m_messages.Count() == 0; }

private:
	float m_tmMessageEnd;
	CUtlVector<CHintMessage *> m_messages;
};
