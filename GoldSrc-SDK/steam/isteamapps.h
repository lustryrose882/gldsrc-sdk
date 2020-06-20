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

const int k_cubAppProofOfPurchaseKeyMax = 64; // max bytes of a legacy cd key we support

enum EAppInfoSection
{
	k_EAppInfoSectionUnknown = 0,
	k_EAppInfoSectionAll,
	k_EAppInfoSectionCommon,
	k_EAppInfoSectionExtended,
	k_EAppInfoSectionConfig,
	k_EAppInfoSectionStats,
	k_EAppInfoSectionInstall,
	k_EAppInfoSectionDepots,
	k_EAppInfoSectionVac,
	k_EAppInfoSectionDrm,
	k_EAppInfoSectionUfs,
	k_EAppInfoSectionOgg,
	k_EAppInfoSectionItems,
	k_EAppInfoSectionPolicies,
	k_EAppInfoSectionSysreqs,
	k_EAppInfoSectionCommunity
};

enum ELanguage
{
	k_Lang_None = -1,
	k_Lang_First = 0,
	k_Lang_English = 0,
	k_Lang_German,
	k_Lang_French,
	k_Lang_Italian,
	k_Lang_Korean,
	k_Lang_Spanish,
	k_Lang_Simplified_Chinese,
	k_Lang_Traditional_Chinese,
	k_Lang_Russian,
	k_Lang_Thai,
	k_Lang_Japanese,
	k_Lang_Portuguese,
	k_Lang_Polish,
	k_Lang_Danish,
	k_Lang_Dutch,
	k_Lang_Finnish,
	k_Lang_Norwegian,
	k_Lang_Swedish,
	k_Lang_Romanian,
	k_Lang_Turkish,
	k_Lang_Hungarian,
	k_Lang_Czech,
	k_Lang_Brazilian,
	k_Lang_Bulgarian,
	k_Lang_Greek,
	k_Lang_Ukrainian,
	k_Lang_MAX
};

#if !defined(STEAM_API_BUILD)
// interface to app data
class ISteamApps
{
public:
	virtual bool BIsSubscribed() = 0;
	virtual bool BIsLowViolence() = 0;
	virtual bool BIsCybercafe() = 0;
	virtual bool BIsVACBanned() = 0;
	virtual const char *GetCurrentGameLanguage() = 0;
	virtual const char *GetAvailableGameLanguages() = 0;

	// only use this member if you need to check ownership of another game related to yours, a demo for example
	virtual bool BIsSubscribedApp(AppId_t appID) = 0;

	// Takes AppID of DLC and checks if the user owns the DLC & if the DLC is installed
	virtual bool BIsDlcInstalled(AppId_t appID) = 0;

	// returns the Unix time of the purchase of the app
	virtual uint32_t GetEarliestPurchaseUnixTime(AppId_t nAppID) = 0;

	// Checks if the user is subscribed to the current app through a free weekend
	// This function will return false for users who have a retail or other type of license
	// Before using, please ask your Valve technical contact how to package and secure your free weekened
	virtual bool BIsSubscribedFromFreeWeekend() = 0;

	// Returns the number of DLC pieces for the running app
	virtual int GetDLCCount() = 0;

	// Returns metadata for DLC by index, of range [0, GetDLCCount()]
	virtual bool BGetDLCDataByIndex(int iDLC, AppId_t *pAppID, bool *pbAvailable, char *pchName, int cchNameBufferSize) = 0;

	// Install/Uninstall control for optional DLC
	virtual void InstallDLC(AppId_t nAppID) = 0;
	virtual void UninstallDLC(AppId_t nAppID) = 0;

	// Request cd-key for yourself or owned DLC. If you are interested in this
	// data then make sure you provide us with a list of valid keys to be distributed
	// to users when they purchase the game, before the game ships.
	// You'll receive an AppProofOfPurchaseKeyResponse_t callback when
	// the key is available (which may be immediately).
	virtual void RequestAppProofOfPurchaseKey(AppId_t nAppID) = 0;

	virtual bool GetCurrentBetaName(char *pchName, int cchNameBufferSize) = 0; // returns current beta branch name, 'public' is the default branch
	virtual bool MarkContentCorrupt(bool bMissingFilesOnly) = 0; // signal Steam that game files seems corrupt or missing
	virtual uint32_t GetInstalledDepots(DepotId_t *pvecDepots, uint32_t cMaxDepots) = 0; // return installed depots in mount order

	// returns current app install folder for AppID, returns folder name length
	virtual uint32_t GetAppInstallDir(AppId_t appID, char *pchFolder, uint32_t cchFolderBufferSize) = 0;
	virtual bool BIsAppInstalled(AppId_t appID) = 0;
};

#else

#define ISteamApps ISteamApps005

#endif // #if !defined(STEAM_API_BUILD)

#define STEAMAPPS_INTERFACE_VERSION "STEAMAPPS_INTERFACE_VERSION005"

// callbacks
#if defined(VALVE_CALLBACK_PACK_SMALL)
#pragma pack(push, 4)
#elif defined(VALVE_CALLBACK_PACK_LARGE)
#pragma pack(push, 8)
#else
#error isteamclient.h must be included
#endif

// Posted after the user gains ownership of DLC & that DLC is installed
struct DlcInstalled_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 5 };
	AppId_t m_nAppID;		// AppID of the DLC
};

// Possible results when registering an activation code
enum ERegisterActivationCodeResult
{
	k_ERegisterActivationCodeResultOK = 0,
	k_ERegisterActivationCodeResultFail = 1,
	k_ERegisterActivationCodeResultAlreadyRegistered = 2,
	k_ERegisterActivationCodeResultTimeout = 3,
	k_ERegisterActivationCodeAlreadyOwned = 4,
};

// Response to RegisterActivationCode()
struct RegisterActivationCodeResponse_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 8 };
	ERegisterActivationCodeResult m_eResult;
	uint32_t m_unPackageRegistered;						// package that was registered. Only set on success
};

// Response to RegisterActivationCode()
struct AppProofOfPurchaseKeyResponse_t
{
	enum { k_iCallback = k_iSteamAppsCallbacks + 13 };
	EResult m_eResult;
	uint32_t	m_nAppID;
	char	m_rgchKey[ k_cubAppProofOfPurchaseKeyMax ];
};

#pragma pack(pop)
