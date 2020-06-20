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

#include "steam_api.h"

enum EServerMode
{
	eServerModeInvalid = 0,					// DO NOT USE
	eServerModeNoAuthentication = 1,		// Don't authenticate user logins and don't list on the server list
	eServerModeAuthentication = 2,			// Authenticate users, list on the server list, don't run VAC on clients that connect
	eServerModeAuthenticationAndSecure = 3,	// Authenticate users, list on the server list and VAC protect clients
};

// Initialize ISteamGameServer interface object, and set server properties which may not be changed.
//
// After calling this function, you should set any additional server parameters, and then
// call ISteamGameServer::LogOnAnonymous() or ISteamGameServer::LogOn()
//
// - usSteamPort is the local port used to communicate with the steam servers.
// - usGamePort is the port that clients will connect to for gameplay.
// - usQueryPort is the port that will manage server browser related duties and info
//		pings from clients.  If you pass MASTERSERVERUPDATERPORT_USEGAMESOCKETSHARE for usQueryPort, then it
//		will use "GameSocketShare" mode, which means that the game is responsible for sending and receiving
//		UDP packets for the master  server updater. See references to GameSocketShare in isteamgameserver.h.
// - The version string is usually in the form x.x.x.x, and is used by the master server to detect when the
//		server is out of date.  (Only servers with the latest version will be listed.)

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
S_API bool SteamGameServer_InitSafe(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, EServerMode eServerMode, const char *pchVersionString);
#endif

S_API bool SteamGameServer_Init(uint32_t unIP, uint16_t usSteamPort, uint16_t usGamePort, uint16_t usQueryPort, EServerMode eServerMode, const char *pchVersionString);

S_API ISteamGameServer011 *SteamGameServer();
S_API ISteamUtils005 *SteamGameServerUtils();
S_API ISteamNetworking005 *SteamGameServerNetworking();
S_API ISteamGameServerStats001 *SteamGameServerStats();
S_API ISteamHTTP002 *SteamGameServerHTTP();
S_API ISteamApps005 *SteamGameServerApps();

S_API void SteamGameServer_Shutdown();
S_API void SteamGameServer_RunCallbacks();

S_API bool SteamGameServer_BSecure();
S_API uint64_t SteamGameServer_GetSteamID();
S_API uint32_t SteamGameServer_GetIPCCallCount();

// utility macro for declaring the function and callback object together
#define STEAM_GAMESERVER_CALLBACK(thisclass, param, var) CCallback<thisclass, param, true> var
#define STEAM_GAMESERVER_CALLBACK_F(thisclass, func, param, var) CCallback<thisclass, param, true> var; void func(param *pParam)

// same as above, but lets you defer the callback binding by calling Register later
#define STEAM_GAMESERVER_CALLBACK_MANUAL(thisclass, param, var) CCallbackManual<thisclass, param, true> var
#define STEAM_GAMESERVER_CALLBACK_MANUAL_F(thisclass, func, param, var) CCallbackManual<thisclass, param, true> var; void func(param *pParam)

//	steamclient.dll private wrapper functions
//
//	The following functions are part of abstracting API access to the steamclient.dll, but should only be used in very specific cases
S_API HSteamPipe SteamGameServer_GetHSteamPipe();

#ifdef VERSION_SAFE_STEAM_API_INTERFACES
// VERSION_SAFE_STEAM_API_INTERFACES uses CSteamAPIContext to provide interfaces to each module in a way that
// lets them each specify the interface versions they are compiled with.
//
// It's important that these stay inlined in the header so the calling module specifies the interface versions
// for whatever Steam API version it has.

S_API HSteamUser SteamGameServer_GetHSteamUser();

class CSteamGameServerAPIContext
{
public:
	CSteamGameServerAPIContext();
	void Clear();

	bool Init();

	ISteamGameServer011			*SteamGameServer() { return m_pSteamGameServer; }
	ISteamUtils005				*SteamGameServerUtils() { return m_pSteamGameServerUtils; }
	ISteamNetworking005			*SteamGameServerNetworking() { return m_pSteamGameServerNetworking; }
	ISteamGameServerStats001	*SteamGameServerStats() { return m_pSteamGameServerStats; }
	ISteamHTTP002				*SteamHTTP() { return m_pSteamHTTP; }

private:
	ISteamGameServer011			*m_pSteamGameServer;
	ISteamUtils005				*m_pSteamGameServerUtils;
	ISteamNetworking005			*m_pSteamGameServerNetworking;
	ISteamGameServerStats001	*m_pSteamGameServerStats;
	ISteamHTTP002				*m_pSteamHTTP;
};

inline CSteamGameServerAPIContext::CSteamGameServerAPIContext()
{
	Clear();
}

inline void CSteamGameServerAPIContext::Clear()
{
	m_pSteamGameServer = nullptr;
	m_pSteamGameServerUtils = nullptr;
	m_pSteamGameServerNetworking = nullptr;
	m_pSteamGameServerStats = nullptr;
	m_pSteamHTTP = nullptr;
}

S_API ISteamClient012 *g_pSteamClientGameServer;

// This function must be inlined so the module using steam_api.dll gets the version names they want.
inline bool CSteamGameServerAPIContext::Init()
{
	if (!g_pSteamClientGameServer)
		return false;

	HSteamUser hSteamUser = SteamGameServer_GetHSteamUser();
	HSteamPipe hSteamPipe = SteamGameServer_GetHSteamPipe();

	m_pSteamGameServer = g_pSteamClientGameServer->GetISteamGameServer(hSteamUser, hSteamPipe, STEAMGAMESERVER_INTERFACE_VERSION);
	if (!m_pSteamGameServer)
		return false;

	m_pSteamGameServerUtils = g_pSteamClientGameServer->GetISteamUtils(hSteamPipe, STEAMUTILS_INTERFACE_VERSION);
	if (!m_pSteamGameServerUtils)
		return false;

	m_pSteamGameServerNetworking = g_pSteamClientGameServer->GetISteamNetworking(hSteamUser, hSteamPipe, STEAMNETWORKING_INTERFACE_VERSION);
	if (!m_pSteamGameServerNetworking)
		return false;

	m_pSteamGameServerStats = g_pSteamClientGameServer->GetISteamGameServerStats(hSteamUser, hSteamPipe, STEAMGAMESERVERSTATS_INTERFACE_VERSION);
	if (!m_pSteamGameServerStats)
		return false;

	m_pSteamHTTP = g_pSteamClientGameServer->GetISteamHTTP(hSteamUser, hSteamPipe, STEAMHTTP_INTERFACE_VERSION);
	if (!m_pSteamGameServerStats)
		return false;

	return true;
}

#endif // VERSION_SAFE_STEAM_API_INTERFACES
