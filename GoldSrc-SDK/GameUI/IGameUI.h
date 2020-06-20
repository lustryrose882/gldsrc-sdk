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

#include <IBaseSystem.h>
#include <tier1/interface.h>

// Reasons why the user can't connect to a game server
enum ESteamLoginFailure
{
	STEAMLOGINFAILURE_NONE,
	STEAMLOGINFAILURE_BADTICKET,
	STEAMLOGINFAILURE_NOSTEAMLOGIN,
	STEAMLOGINFAILURE_VACBANNED,
	STEAMLOGINFAILURE_LOGGED_IN_ELSEWHERE,
	STEAMLOGINFAILURE_CONNECTIONLOST,
	STEAMLOGINFAILURE_NOCONNECTION
};

#if defined(_WIN32)
	constexpr auto GAMEUI_LIB = "cl_dlls\\GameUI.dll";
#elif defined(LINUX)
	constexpr auto GAMEUI_LIB = "cl_dlls/gameui.so";
#elif defined(OSX)
	constexpr auto GAMEUI_LIB = "cl_dlls/gameui.dylib";
#else
	#error "Unsupported Platform."
#endif // #if defined(_WIN32) || defined(LINUX) || defined(OSX)

// Contains all the functions that the GameUI dll exports
class IGameUI: public IBaseInterface
{
public:
	// initialization/shutdown
	virtual void Initialize(CreateInterfaceFn *factories, int count) = 0;
	virtual void Start(struct cl_enginefuncs_s *engineFuncs, int interfaceVersion, IBaseSystem *system) = 0;
	virtual void Shutdown() = 0;

	// notifications
	virtual BOOL ActivateGameUI() = 0;
	virtual BOOL ActivateDemoUI() = 0;

	virtual BOOL HasExclusiveInput() = 0;
	virtual void RunFrame() = 0;

	virtual void ConnectToServer(const char *gamename, unsigned int unIP, unsigned short usPort) = 0;
	virtual void DisconnectFromServer() = 0;
	virtual void HideGameUI() = 0;
	virtual bool IsGameUIActive() = 0;
	virtual void LoadingStarted(const char *resourceType, const char *resourceName) = 0;
	virtual void LoadingFinished(const char *resourceType, const char *resourceName) = 0;

	// level loading progress, returns true if the screen needs updating
	virtual void StartProgressBar(const char *progressType, int progressSteps) = 0;
	virtual BOOL ContinueProgressBar(int progressPoint, float progressFraction) = 0;

	virtual void StopProgressBar(bool bError, const char *failureReason, const char *extendedReason = nullptr) = 0;
	virtual BOOL SetProgressBarStatusText(const char *statusText) = 0;
	virtual void SetSecondaryProgressBar(float progress) = 0;
	virtual void SetSecondaryProgressBarText(const char *statusText) = 0;
	virtual void ValidateCDKey(bool force = false, bool inConnect = false) = 0;
	virtual void OnDisconnectFromServer(ESteamLoginFailure eSteamLoginFailure, const char *username = "") = 0;

	// Extended only GSClient
	virtual void StartEx(cl_enginefuncex_t *engineFuncsex) = 0;
	virtual void InitializeEx(CreateInterfaceFn *factories, int count) = 0;
};

extern IGameUI *g_pGameUIPanel;

#define GAMEUI_INTERFACE_VERSION "GameUI007"
#define GAMEUI_INTERFACE_VERSION_ENHANCED "GameUI008"
