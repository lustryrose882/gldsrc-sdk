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

extern CBotManager *TheBots;

// The manager for Counter-Strike specific bots
class CCSBotManager: public CBotManager
{
public:
	virtual void ClientDisconnect(CBasePlayer *pPlayer) = 0;
	virtual BOOL ClientCommand(CBasePlayer *pPlayer, const char *pcmd) = 0;

	virtual void ServerActivate() = 0;
	virtual void ServerDeactivate() = 0;

	virtual void ServerCommand(const char *pcmd) = 0;
	virtual void AddServerCommand(const char *cmd) = 0;
	virtual void AddServerCommands() = 0;

	virtual void RestartRound() = 0;										// (EXTEND) invoked when a new round begins
	virtual void StartFrame() = 0;											// (EXTEND) called each frame

	virtual void OnEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL) = 0;
	virtual unsigned int GetPlayerPriority(CBasePlayer *player) const = 0;				// return priority of player (0 = max pri)
	virtual bool IsImportantPlayer(CBasePlayer *player) const = 0;						// return true if player is important to scenario (VIP, bomb carrier, etc)

public:
	// the supported game scenarios
	enum GameScenarioType
	{
		SCENARIO_DEATHMATCH,
		SCENARIO_DEFUSE_BOMB,
		SCENARIO_RESCUE_HOSTAGES,
		SCENARIO_ESCORT_VIP
	};
	GameScenarioType GetScenario() const { return m_gameScenario; }

	// "zones"
	// depending on the game mode, these are bomb zones, rescue zones, etc.
	enum { MAX_ZONES = 4 };							// max # of zones in a map
	enum { MAX_ZONE_NAV_AREAS = 16 };				// max # of nav areas in a zone
	struct Zone
	{
		CBaseEntity *m_entity;						// the map entity
		CNavArea *m_area[MAX_ZONE_NAV_AREAS];		// nav areas that overlap this zone
		int m_areaCount;
		Vector m_center;
		bool m_isLegacy;					// if true, use pev->origin and 256 unit radius as zone
		int m_index;
		Extent m_extent;
	};

	const Zone *GetZone(int i) const { return &m_zone[i]; }
	int GetZoneCount() const { return m_zoneCount; }

	// pick a zone at random and return it
	const Zone *GetRandomZone() const
	{
		if (!m_zoneCount)
			return NULL;

		return &m_zone[RANDOM_LONG(0, m_zoneCount - 1)];
	}

	bool IsBombPlanted() const { return m_isBombPlanted; }											// returns true if bomb has been planted
	float GetBombPlantTimestamp() const { return m_bombPlantTimestamp; }							// return time bomb was planted
	bool IsTimeToPlantBomb() const { return (gpGlobals->time >= m_earliestBombPlantTimestamp); }	// return true if it's ok to try to plant bomb
	CBasePlayer *GetBombDefuser() const { return m_bombDefuser; }									// return the player currently defusing the bomb, or NULL
	CBaseEntity *GetLooseBomb() { return m_looseBomb; }												// return the bomb if it is loose on the ground
	CNavArea *GetLooseBombArea() const { return m_looseBombArea; }									// return area that bomb is in/near

	float GetLastSeenEnemyTimestamp() const { return m_lastSeenEnemyTimestamp; }					// return the last time anyone has seen an enemy
	void SetLastSeenEnemyTimestamp() { m_lastSeenEnemyTimestamp = gpGlobals->time; }

	float GetRoundStartTime() const { return m_roundStartTimestamp; }
	float GetElapsedRoundTime() const { return gpGlobals->time - m_roundStartTimestamp; }			// return the elapsed time since the current round began

	bool IsDefenseRushing() const { return m_isDefenseRushing; }					// returns true if defense team has "decided" to rush this round
	bool IsRoundOver() const { return m_isRoundOver; }								// return true if the round has ended

	unsigned int GetNavPlace() const { return m_navPlace; }
	void SetNavPlace(unsigned int place) { m_navPlace = place; }

public:
	GameScenarioType m_gameScenario;			// what kind of game are we playing

	Zone m_zone[MAX_ZONES];
	int m_zoneCount;

	bool m_isBombPlanted;						// true if bomb has been planted
	float m_bombPlantTimestamp;					// time bomb was planted
	float m_earliestBombPlantTimestamp;			// don't allow planting until after this time has elapsed
	CBasePlayer *m_bombDefuser;					// the player currently defusing a bomb
	EHANDLE m_looseBomb;						// will be non-NULL if bomb is loose on the ground
	CNavArea *m_looseBombArea;					// area that bomb is is/near

	bool m_isRoundOver;							// true if the round has ended
	float m_radioMsgTimestamp[24][2];

	float m_lastSeenEnemyTimestamp;
	float m_roundStartTimestamp;				// the time when the current round began

	bool m_isDefenseRushing;					// whether defensive team is rushing this round or not

	unsigned int m_navPlace;
	CountdownTimer m_respawnTimer;
	bool m_isRespawnStarted;
	bool m_canRespawn;
	bool m_bServerActive;
};

inline int OtherTeam(int team)
{
	return (team == TERRORIST) ? CT : TERRORIST;
}

inline CCSBotManager *TheCSBots()
{
	return reinterpret_cast<CCSBotManager *>(TheBots);
}
