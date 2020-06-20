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

// STL uses exceptions, but we are not compiling with them - ignore warning
#ifdef _MSC_VER
#pragma warning(disable:4530)
#endif

#include <list>

class CNavArea;
class CGrenade;

class ActiveGrenade
{
public:
	int m_id;
	CGrenade *m_entity;
	Vector m_detonationPosition;
	float m_dieTimestamp;
};

typedef std::list<ActiveGrenade *> ActiveGrenadeList;

class CBotManager
{
public:
	virtual ~CBotManager() {}

	virtual void ClientDisconnect(CBasePlayer *pPlayer) = 0;
	virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd) = 0;

	virtual void ServerActivate() = 0;
	virtual void ServerDeactivate() = 0;

	virtual void ServerCommand(const char *pcmd) = 0;
	virtual void AddServerCommand(const char *cmd) = 0;
	virtual void AddServerCommands() = 0;

	virtual void RestartRound() = 0;
	virtual void StartFrame() = 0;

	// Events are propogated to all bots.
	virtual void OnEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL) = 0;		// Invoked when event occurs in the game (some events have NULL entity).
	virtual unsigned int GetPlayerPriority(CBasePlayer *player) const = 0;						// return priority of player (0 = max pri)

public:
	// the list of active grenades the bots are aware of
	ActiveGrenadeList m_activeGrenadeList;
};
