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

enum class HLServerType: uint8_t
{
	HLST_Dedicated		= 'd',
	HLST_NonDedicated	= 'i',
	HLST_TV				= 'p',
};

struct ServerInfoResponse_t
{
	int protocol;				// Protocol version used by the server
	char hostname[256];
	char name[256];				// Name of the server
	char map[256];				// Map the server has currently loaded
	char gamedir[256];			// Name of the folder containing the game files
	char description[256];		// Full name of the game

	int activePlayers;			// Number of players on the server
	int maxPlayers;				// Maximum number of players the server reports it can hold

	int activeBots;				// Number of bots on the server
	HLServerType serverType;	// Indicates the type of server
								//	'd' for a dedicated server
								//	'i' for a non-dedicated server
								//	'p' for a SourceTV relay (proxy)

	bool has_password;			// Indicates whether the server requires a password
	bool has_secure;			// Specifies whether the server uses VAC

	int appid;					// Steam Application ID of game

	char app_version[128];		// Version of the game installed on the server
	char tags[128];				// Tags that describe the game according to the server

	uint16_t game_port;			// The server's game port number
	uint16_t spec_port;			// Spectator port number for SourceTV

	CSteamID steamId;			// Server's SteamID
};

// Data describing a single server
struct serveritem_t
{
	serveritem_t()
	{
		pings[0] = 0;
		pings[1] = 0;
		pings[2] = 0;
	}

	unsigned char ip[4];
	int port;
	int received;
	float time;
	int ping;								// current ping time, derived from pings[]
	int pings[3];							// last 3 ping times
	bool hadSuccessfulResponse;				// server has responded successfully in the past
	bool doNotRefresh;						// server is marked as not responding and should no longer be refreshed
	char gameDir[32];						// current game directory
	char map[32];							// current map
	char gameDescription[64];				// game description
	char name[64];							// server name
	int players;
	int maxPlayers;
	int botPlayers;
	bool proxy;
	bool password;
	bool secure;
	bool loadedFromFile;					// true if this entry was loaded from file rather than comming from the master
	unsigned int serverID;
	int listEntryID;
	char rconPassword[64];					// the rcon password for this server
};

// Callback interface for server updates
class IServerRefreshResponse
{
public:
	// called when the server has successfully responded
	virtual void ServerRespondedWithDetails(const netadr_t &to, double time, const ServerInfoResponse_t &server) = 0;
	virtual void AddPlayerToList(const char *pchName, int nScore, float flTimePlayed) = 0;

	// called when the current players refresh list is complete
	virtual void PlayersRefreshComplete() = 0;
	virtual void AddRulesToList(const char *pchRule, const char *pchValue) = 0;

	// called when the current rules refresh list is complete
	virtual void RulesRefreshComplete() = 0;

	// called when a server response has timed out
	virtual void ServerFailedToRespond() = 0;

	virtual ~IServerRefreshResponse() {}
};
