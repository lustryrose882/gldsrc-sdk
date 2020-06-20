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

S_API bool SteamContentServer_Init(uint32_t uContentServerID, uint32_t unIP, uint16_t usPort, uint16_t usClientContentPort);
S_API void SteamContentServer_Shutdown();
S_API void SteamContentServer_RunCallbacks();

S_API ISteamContentServer002 *SteamContentServer();
S_API ISteamUtils005 *SteamContentServerUtils();

#define STEAM_CONTENTSERVER_CALLBACK(thisclass, func, param, var) CCallback<thisclass, param, true> var; void func(param *pParam)
