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

#include "isteamclient.h"

// Functions for authenticating users via Steam to play on a game server
#if !defined(STEAM_API_BUILD)
class ISteamGameServerStats
{
public:
	// downloads stats for the user
	// returns a GSStatsReceived_t callback when completed
	// if the user has no stats, GSStatsReceived_t.m_eResult will be set to k_EResultFail
	// these stats will only be auto-updated for clients playing on the server. For other
	// users you'll need to call RequestUserStats() again to refresh any data
	virtual SteamAPICall_t RequestUserStats(CSteamID steamIDUser) = 0;

	// requests stat information for a user, usable after a successful call to RequestUserStats()
	virtual bool GetUserStat(CSteamID steamIDUser, const char *pchName, int32_t *pData) = 0;
	virtual bool GetUserStat(CSteamID steamIDUser, const char *pchName, float *pData) = 0;
	virtual bool GetUserAchievement(CSteamID steamIDUser, const char *pchName, bool *pbAchieved) = 0;

	// Set / update stats and achievements.
	// Note: These updates will work only on stats game servers are allowed to edit and only for
	// game servers that have been declared as officially controlled by the game creators.
	// Set the IP range of your official servers on the Steamworks page
	virtual bool SetUserStat(CSteamID steamIDUser, const char *pchName, int32_t nData) = 0;
	virtual bool SetUserStat(CSteamID steamIDUser, const char *pchName, float fData) = 0;
	virtual bool UpdateUserAvgRateStat(CSteamID steamIDUser, const char *pchName, float flCountThisSession, double dSessionLength) = 0;

	virtual bool SetUserAchievement(CSteamID steamIDUser, const char *pchName) = 0;
	virtual bool ClearUserAchievement(CSteamID steamIDUser, const char *pchName) = 0;

	// Store the current data on the server, will get a GSStatsStored_t callback when set.
	//
	// If the callback has a result of k_EResultInvalidParam, one or more stats
	// uploaded has been rejected, either because they broke constraints
	// or were out of date. In this case the server sends back updated values.
	// The stats should be re-iterated to keep in sync.
	virtual SteamAPICall_t StoreUserStats(CSteamID steamIDUser) = 0;
};

#else

#define ISteamGameServerStats ISteamGameServerStats001

#endif // #if !defined(STEAM_API_BUILD)

#define STEAMGAMESERVERSTATS_INTERFACE_VERSION "SteamGameServerStats001"

// callbacks
#if defined(VALVE_CALLBACK_PACK_SMALL)
#pragma pack(push, 4)
#elif defined(VALVE_CALLBACK_PACK_LARGE)
#pragma pack(push, 8)
#else
#error isteamclient.h must be included
#endif

// Called when the latests stats and achievements have been received
// from the server
struct GSStatsReceived_t
{
	enum { k_iCallback = k_iSteamGameServerStatsCallbacks };
	EResult		m_eResult;		// Success / error fetching the stats
	CSteamID	m_steamIDUser;	// The user for whom the stats are retrieved for
};

// Result of a request to store the user stats for a game
struct GSStatsStored_t
{
	enum { k_iCallback = k_iSteamGameServerStatsCallbacks + 1 };
	EResult		m_eResult;		// success / error
	CSteamID	m_steamIDUser;	// The user for whom the stats were stored
};

// Callback indicating that a user's stats have been unloaded.
// Call RequestUserStats again to access stats for this user
struct GSStatsUnloaded_t
{
	enum { k_iCallback = k_iSteamUserStatsCallbacks + 8 };
	CSteamID	m_steamIDUser;	// User whose stats have been unloaded
};

#pragma pack(pop)
