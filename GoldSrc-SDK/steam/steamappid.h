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

enum GameAppId: AppId_t
{
	GAME_APPID_CSTRIKE      = 10,
	GAME_APPID_TFC          = 20,
	GAME_APPID_DOD          = 30,
	GAME_APPID_DMC          = 40,
	GAME_APPID_GEARBOX      = 50,
	GAME_APPID_RICOCHET     = 60,
	GAME_APPID_VALVE        = 70,
	GAME_APPID_CZERO        = 80,
	GAME_APPID_CZEROR       = 100,
	GAME_APPID_BSHIFT       = 130,
	GAME_APPID_CSTRIKE_BETA = 150,
};

AppId_t Steam_GetGameAppID(const char *gamedir);
bool Steam_IsGameSubscribed(const char *gamedir);
bool Steam_BIsValveGame(const char *gamedir);
