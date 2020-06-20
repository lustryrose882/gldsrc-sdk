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

#include "maintypes.h"
#include "steam_api.h"
#include "steamappid.h"

struct GameToAppIDMapItem_t
{
	AppId_t appID;
	const char *pGameDir;
};

GameToAppIDMapItem_t g_GameToAppIDMap[] =
{
	{ GAME_APPID_CSTRIKE,      "cstrike"      },
	{ GAME_APPID_TFC,          "tfc"          },
	{ GAME_APPID_DOD,          "dod"          },
	{ GAME_APPID_DMC,          "dmc"          },
	{ GAME_APPID_GEARBOX,      "gearbox"      },
	{ GAME_APPID_RICOCHET,     "ricochet"     },
	{ GAME_APPID_VALVE,        "valve"        },
	{ GAME_APPID_CZERO,        "czero"        },
	{ GAME_APPID_CZEROR,       "czeror"       },
	{ GAME_APPID_BSHIFT,       "bshift"       },
	{ GAME_APPID_CSTRIKE_BETA, "cstrike_beta" },
};

AppId_t Steam_GetGameAppID(const char *gamedir)
{
	for (const auto &data : g_GameToAppIDMap)
	{
		if (!_stricmp(data.pGameDir, gamedir))
			return data.appID;
	}

	return GAME_APPID_VALVE;
}

bool Steam_IsGameSubscribed(const char *gamedir)
{
	if (!SteamApps())
		return false;

	for (const auto &data : g_GameToAppIDMap)
	{
		if (!_stricmp(data.pGameDir, gamedir))
		{
			return SteamApps()->BIsSubscribedApp(data.appID);
		}
	}

	return SteamApps()->BIsSubscribedApp(GAME_APPID_VALVE);
}

bool Steam_BIsValveGame(const char *gamedir)
{
	for (const auto &data : g_GameToAppIDMap)
	{
		if (!_stricmp(data.pGameDir, gamedir))
			return true;
	}

	return false;
}
