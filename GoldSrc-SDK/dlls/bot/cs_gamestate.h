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

class CCSBot;

// This class represents the game state as known by a particular bot
class CSGameState
{
public:
	// bomb defuse scenario
	enum BombState
	{
		MOVING,		// being carried by a Terrorist
		LOOSE,		// loose on the ground somewhere
		PLANTED,	// planted and ticking
		DEFUSED,	// the bomb has been defused
		EXPLODED,	// the bomb has exploded
	};

	bool IsBombMoving() const { return (m_bombState == MOVING); }
	bool IsBombLoose() const { return (m_bombState == LOOSE); }
	bool IsBombPlanted() const { return (m_bombState == PLANTED); }
	bool IsBombDefused() const { return (m_bombState == DEFUSED); }
	bool IsBombExploded() const { return (m_bombState == EXPLODED); }

public:
	CCSBot *m_owner;				// who owns this gamestate
	bool m_isRoundOver;				// true if round is over, but no yet reset

	// bomb defuse scenario
	BombState GetBombState() { return m_bombState; }
	BombState m_bombState;			// what we think the bomb is doing

	IntervalTimer m_lastSawBomber;
	Vector m_bomberPos;

	IntervalTimer m_lastSawLooseBomb;
	Vector m_looseBombPos;

	bool m_isBombsiteClear[4];		// corresponds to zone indices in CCSBotManager
	int m_bombsiteSearchOrder[4];	// randomized order of bombsites to search
	int m_bombsiteCount;
	int m_bombsiteSearchIndex;		// the next step in the search

	int m_plantedBombsite;			// zone index of the bombsite where the planted bomb is

	bool m_isPlantedBombPosKnown;	// if true, we know the exact location of the bomb
	Vector m_plantedBombPos;

	// hostage rescue scenario
	struct HostageInfo
	{
		CHostage *hostage;
		Vector knownPos;
		bool isValid;
		bool isAlive;
		bool isFree;				// not being escorted by a CT
	}
	m_hostage[MAX_HOSTAGES];
	int m_hostageCount;				// number of hostages left in map
	CountdownTimer m_validateInterval;

	bool m_allHostagesRescued;				// if true, so every hostages been is rescued
	bool m_haveSomeHostagesBeenTaken;		// true if a hostage has been moved by a CT (and we've seen it)
};
