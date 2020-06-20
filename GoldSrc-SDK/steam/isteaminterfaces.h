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

class ISteamUser016;
class ISteamApps005;
class ISteamHTTP002;
class ISteamUtils005;
class ISteamFriends013;
class ISteamUserStats011;
class ISteamNetworking005;
class ISteamScreenshots001;
class ISteamGameServer011;
class ISteamRemoteStorage010;
class ISteamGameServerStats001;
class ISteamMatchmaking009;
class ISteamMatchmakingServers002;

class ISteamClient012
{
public:
	virtual HSteamPipe CreateSteamPipe() = 0;
	virtual bool BReleaseSteamPipe(HSteamPipe hSteamPipe) = 0;
	virtual HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe) = 0;
	virtual HSteamUser CreateLocalUser(HSteamPipe *phSteamPipe, EAccountType eAccountType) = 0;
	virtual void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser) = 0;
	virtual ISteamUser016 *GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamGameServer011 *GetISteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual void SetLocalIPBinding(uint32_t unIP, uint16_t usPort) = 0;
	virtual ISteamFriends013 *GetISteamFriends(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamUtils005 *GetISteamUtils(HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamMatchmaking009 *GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamMatchmakingServers002 *GetISteamMatchmakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual void *GetISteamGenericInterface(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamUserStats011 *GetISteamUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamGameServerStats001 *GetISteamGameServerStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamApps005 *GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamNetworking005 *GetISteamNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamRemoteStorage010 *GetISteamRemoteStorage(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamScreenshots001 *GetISteamScreenshots(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual void RunFrame() = 0;
	virtual uint32_t GetIPCCallCount() = 0;
	virtual void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction) = 0;
	virtual bool BShutdownIfAllPipesClosed() = 0;
	virtual ISteamHTTP002 *GetISteamHTTP(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamUnifiedMessages *GetISteamUnifiedMessages(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamController *GetISteamController(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamUGC *GetISteamUGC(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
};

class ISteamClient013
{
public:
	virtual HSteamPipe CreateSteamPipe() = 0;
	virtual bool BReleaseSteamPipe(HSteamPipe hSteamPipe) = 0;
	virtual HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe) = 0;
	virtual HSteamUser CreateLocalUser(HSteamPipe *phSteamPipe, EAccountType eAccountType) = 0;
	virtual void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser) = 0;
	virtual ISteamUser016 *GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamGameServer011 *GetISteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual void SetLocalIPBinding(uint32_t unIP, uint16_t usPort) = 0;
	virtual ISteamFriends013 *GetISteamFriends(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamUtils005 *GetISteamUtils(HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamMatchmaking009 *GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamMatchmakingServers002 *GetISteamMatchmakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual void *GetISteamGenericInterface(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamUserStats011 *GetISteamUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamGameServerStats001 *GetISteamGameServerStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamApps005 *GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamNetworking005 *GetISteamNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamRemoteStorage010 *GetISteamRemoteStorage(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamScreenshots001 *GetISteamScreenshots(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual void RunFrame() = 0;
	virtual uint32_t GetIPCCallCount() = 0;
	virtual void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction) = 0;
	virtual bool BShutdownIfAllPipesClosed() = 0;
	virtual ISteamHTTP002 *GetISteamHTTP(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamUnifiedMessages *GetISteamUnifiedMessages(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamController *GetISteamController(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	virtual ISteamUGC *GetISteamUGC(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
};

class ISteamHTTP001
{
public:
	virtual HTTPRequestHandle CreateHTTPRequest(EHTTPMethod eHTTPRequestMethod, const char *pchAbsoluteURL) = 0;
	virtual bool SetHTTPRequestContextValue(HTTPRequestHandle hRequest, uint64_t ulContextValue) = 0;
	virtual bool SetHTTPRequestNetworkActivityTimeout(HTTPRequestHandle hRequest, uint32_t unTimeoutSeconds) = 0;
	virtual bool SetHTTPRequestHeaderValue(HTTPRequestHandle hRequest, const char *pchHeaderName, const char *pchHeaderValue) = 0;
	virtual bool SetHTTPRequestGetOrPostParameter(HTTPRequestHandle hRequest, const char *pchParamName, const char *pchParamValue) = 0;
	virtual bool SendHTTPRequest(HTTPRequestHandle hRequest, SteamAPICall_t *pCallHandle) = 0;
	virtual bool SendHTTPRequestAndStreamResponse(HTTPRequestHandle hRequest, SteamAPICall_t *pCallHandle) = 0;
	virtual bool DeferHTTPRequest(HTTPRequestHandle hRequest) = 0;
	virtual bool PrioritizeHTTPRequest(HTTPRequestHandle hRequest) = 0;
	virtual bool GetHTTPResponseHeaderSize(HTTPRequestHandle hRequest, const char *pchHeaderName, uint32_t *unResponseHeaderSize) = 0;
	virtual bool GetHTTPResponseHeaderValue(HTTPRequestHandle hRequest, const char *pchHeaderName, uint8_t *pHeaderValueBuffer, uint32_t unBufferSize) = 0;
	virtual bool GetHTTPResponseBodySize(HTTPRequestHandle hRequest, uint32_t *unBodySize) = 0;
	virtual bool GetHTTPResponseBodyData(HTTPRequestHandle hRequest, uint8_t *pBodyDataBuffer, uint32_t unBufferSize) = 0;
	virtual bool GetHTTPStreamingResponseBodyData(HTTPRequestHandle hRequest, uint32_t cOffset, uint8_t *pBodyDataBuffer, uint32_t unBufferSize) = 0;
	virtual bool ReleaseHTTPRequest(HTTPRequestHandle hRequest) = 0;
	virtual bool GetHTTPDownloadProgressPct(HTTPRequestHandle hRequest, float *pflPercentOut) = 0;
	virtual bool SetHTTPRequestRawPostBody(HTTPRequestHandle hRequest, const char *pchContentType, uint8_t *pubBody, uint32_t unBodyLen) = 0;
};

class ISteamHTTP002
{
public:
	virtual HTTPRequestHandle CreateHTTPRequest(EHTTPMethod eHTTPRequestMethod, const char *pchAbsoluteURL) = 0;
	virtual bool SetHTTPRequestContextValue(HTTPRequestHandle hRequest, uint64_t ulContextValue) = 0;
	virtual bool SetHTTPRequestNetworkActivityTimeout(HTTPRequestHandle hRequest, uint32_t unTimeoutSeconds) = 0;
	virtual bool SetHTTPRequestHeaderValue(HTTPRequestHandle hRequest, const char *pchHeaderName, const char *pchHeaderValue) = 0;
	virtual bool SetHTTPRequestGetOrPostParameter(HTTPRequestHandle hRequest, const char *pchParamName, const char *pchParamValue) = 0;
	virtual bool SendHTTPRequest(HTTPRequestHandle hRequest, SteamAPICall_t *pCallHandle) = 0;
	virtual bool SendHTTPRequestAndStreamResponse(HTTPRequestHandle hRequest, SteamAPICall_t *pCallHandle) = 0;
	virtual bool DeferHTTPRequest(HTTPRequestHandle hRequest) = 0;
	virtual bool PrioritizeHTTPRequest(HTTPRequestHandle hRequest) = 0;
	virtual bool GetHTTPResponseHeaderSize(HTTPRequestHandle hRequest, const char *pchHeaderName, uint32_t *unResponseHeaderSize) = 0;
	virtual bool GetHTTPResponseHeaderValue(HTTPRequestHandle hRequest, const char *pchHeaderName, uint8_t *pHeaderValueBuffer, uint32_t unBufferSize) = 0;
	virtual bool GetHTTPResponseBodySize(HTTPRequestHandle hRequest, uint32_t *unBodySize) = 0;
	virtual bool GetHTTPResponseBodyData(HTTPRequestHandle hRequest, uint8_t *pBodyDataBuffer, uint32_t unBufferSize) = 0;
	virtual bool GetHTTPStreamingResponseBodyData(HTTPRequestHandle hRequest, uint32_t cOffset, uint8_t *pBodyDataBuffer, uint32_t unBufferSize) = 0;
	virtual bool ReleaseHTTPRequest(HTTPRequestHandle hRequest) = 0;
	virtual bool GetHTTPDownloadProgressPct(HTTPRequestHandle hRequest, float *pflPercentOut) = 0;
	virtual bool SetHTTPRequestRawPostBody(HTTPRequestHandle hRequest, const char *pchContentType, uint8_t *pubBody, uint32_t unBodyLen) = 0;
	virtual HTTPCookieContainerHandle CreateCookieContainer(bool bAllowResponsesToModify) = 0;
	virtual bool ReleaseCookieContainer(HTTPCookieContainerHandle hCookieContainer) = 0;
	virtual bool SetCookie(HTTPCookieContainerHandle hCookieContainer, const char *pchHost, const char *pchUrl, const char *pchCookie) = 0;
	virtual bool SetHTTPRequestCookieContainer(HTTPRequestHandle hRequest, HTTPCookieContainerHandle hCookieContainer) = 0;
	virtual bool SetHTTPRequestUserAgentInfo(HTTPRequestHandle hRequest, const char *pchUserAgentInfo) = 0;
	virtual bool SetHTTPRequestRequiresVerifiedCertificate(HTTPRequestHandle hRequest, bool bRequireVerifiedCertificate) = 0;
	virtual bool SetHTTPRequestAbsoluteTimeoutMS(HTTPRequestHandle hRequest, uint32_t unMilliseconds) = 0;
	virtual bool GetHTTPRequestWasTimedOut(HTTPRequestHandle hRequest, bool *pbWasTimedOut) = 0;
};

class ISteamApps005
{
public:
	virtual bool BIsSubscribed() = 0;
	virtual bool BIsLowViolence() = 0;
	virtual bool BIsCybercafe() = 0;
	virtual bool BIsVACBanned() = 0;
	virtual const char *GetCurrentGameLanguage() = 0;
	virtual const char *GetAvailableGameLanguages() = 0;
	virtual bool BIsSubscribedApp(AppId_t appID) = 0;
	virtual bool BIsDlcInstalled(AppId_t appID) = 0;
	virtual uint32_t GetEarliestPurchaseUnixTime(AppId_t nAppID) = 0;
	virtual bool BIsSubscribedFromFreeWeekend() = 0;
	virtual int GetDLCCount() = 0;
	virtual bool BGetDLCDataByIndex(int iDLC, AppId_t *pAppID, bool *pbAvailable, char *pchName, int cchNameBufferSize) = 0;
	virtual void InstallDLC(AppId_t nAppID) = 0;
	virtual void UninstallDLC(AppId_t nAppID) = 0;
	virtual void RequestAppProofOfPurchaseKey(AppId_t nAppID) = 0;
	virtual bool GetCurrentBetaName(char *pchName, int cchNameBufferSize) = 0;
	virtual bool MarkContentCorrupt(bool bMissingFilesOnly) = 0;
	virtual uint32_t GetInstalledDepots(DepotId_t *pvecDepots, uint32_t cMaxDepots) = 0;
	virtual uint32_t GetAppInstallDir(AppId_t appID, char *pchFolder, uint32_t cchFolderBufferSize) = 0;
	virtual bool BIsAppInstalled(AppId_t appID) = 0;
};

class ISteamFriends013
{
public:
	virtual const char *GetPersonaName() = 0;
	virtual SteamAPICall_t SetPersonaName(const char *pchPersonaName) = 0;
	virtual EPersonaState GetPersonaState() = 0;
	virtual int GetFriendCount(int iFriendFlags) = 0;
	virtual CSteamID GetFriendByIndex(int iFriend, int iFriendFlags) = 0;
	virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;
	virtual bool HasFriend(CSteamID steamIDFriend, int iFriendFlags) = 0;
	virtual int GetClanCount() = 0;
	virtual CSteamID GetClanByIndex(int iClan) = 0;
	virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;
	virtual bool GetClanActivityCounts(CSteamID steamIDClan, int *pnOnline, int *pnInGame, int *pnChatting) = 0;
	virtual SteamAPICall_t DownloadClanActivityCounts(CSteamID *psteamIDClans, int cClansToRequest) = 0;
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	virtual CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int iFriend) = 0;
	virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;
	virtual void ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag) = 0;
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;
	virtual int GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;
	virtual int GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;
	virtual int GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;
	virtual bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;
	virtual SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;
	virtual CSteamID GetClanOwner(CSteamID steamIDClan) = 0;
	virtual int GetClanOfficerCount(CSteamID steamIDClan) = 0;
	virtual CSteamID GetClanOfficerByIndex(CSteamID steamIDClan, int iOfficer) = 0;
	virtual uint32_t GetUserRestrictions() = 0;
	virtual bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	virtual void ClearRichPresence() = 0;
	virtual const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	virtual int GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	virtual const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey) = 0;
	virtual void RequestFriendRichPresence(CSteamID steamIDFriend) = 0;
	virtual bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;
	virtual int GetCoplayFriendCount() = 0;
	virtual CSteamID GetCoplayFriend(int iCoplayFriend) = 0;
	virtual int GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	virtual AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;
	virtual SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan) = 0;
	virtual bool LeaveClanChatRoom(CSteamID steamIDClan) = 0;
	virtual int GetClanChatMemberCount(CSteamID steamIDClan) = 0;
	virtual CSteamID GetChatMemberByIndex(CSteamID steamIDClan, int iUser) = 0;
	virtual bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText) = 0;
	virtual int GetClanChatMessage(CSteamID steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, EChatEntryType *peChatEntryType, CSteamID *psteamidChatter) = 0;
	virtual bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) = 0;
	virtual bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool SetListenForFriendsMessages(bool bInterceptEnabled) = 0;
	virtual bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend) = 0;
	virtual int GetFriendMessage(CSteamID steamIDFriend, int iMessageID, void *pvData, int cubData, EChatEntryType *peChatEntryType) = 0;
	virtual SteamAPICall_t GetFollowerCount(CSteamID steamID) = 0;
	virtual SteamAPICall_t IsFollowing(CSteamID steamID) = 0;
	virtual SteamAPICall_t EnumerateFollowingList(uint32_t unStartIndex) = 0;
};

class ISteamGameServer011
{
public:
	virtual bool InitGameServer(uint32_t unIP, uint16_t usGamePort, uint16_t usQueryPort, uint32_t unFlags, AppId_t nGameAppId, const char *pchVersionString) = 0;
	virtual void SetProduct(const char *pszProduct) = 0;
	virtual void SetGameDescription(const char *pszGameDescription) = 0;
	virtual void SetModDir(const char *pszModDir) = 0;
	virtual void SetDedicatedServer(bool bDedicated) = 0;
	virtual void LogOn(const char *pszAccountName, const char *pszPassword) = 0;
	virtual void LogOnAnonymous() = 0;
	virtual void LogOff() = 0;
	virtual bool BLoggedOn() = 0;
	virtual bool BSecure() = 0;
	virtual CSteamID GetSteamID() = 0;
	virtual bool WasRestartRequested() = 0;
	virtual void SetMaxPlayerCount(int cPlayersMax) = 0;
	virtual void SetBotPlayerCount(int cBotplayers) = 0;
	virtual void SetServerName(const char *pszServerName) = 0;
	virtual void SetMapName(const char *pszMapName) = 0;
	virtual void SetPasswordProtected(bool bPasswordProtected) = 0;
	virtual void SetSpectatorPort(uint16_t unSpectatorPort) = 0;
	virtual void SetSpectatorServerName(const char *pszSpectatorServerName) = 0;
	virtual void ClearAllKeyValues() = 0;
	virtual void SetKeyValue(const char *pKey, const char *pValue) = 0;
	virtual void SetGameTags(const char *pchGameTags) = 0;
	virtual void SetGameData(const char *pchGameData) = 0;
	virtual void SetRegion(const char *pszRegion) = 0;
	virtual bool SendUserConnectAndAuthenticate(uint32_t unIPClient, const void *pvAuthBlob, uint32_t cubAuthBlobSize, CSteamID *pSteamIDUser) = 0;
	virtual CSteamID CreateUnauthenticatedUserConnection() = 0;
	virtual void SendUserDisconnect(CSteamID steamIDUser) = 0;
	virtual bool BUpdateUserData(CSteamID steamIDUser, const char *pchPlayerName, uint32_t uScore) = 0;
	virtual HAuthTicket GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32_t *pcbTicket) = 0;
	virtual EBeginAuthSessionResult BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID) = 0;
	virtual void EndAuthSession(CSteamID steamID) = 0;
	virtual void CancelAuthTicket(HAuthTicket hAuthTicket) = 0;
	virtual EUserHasLicenseForAppResult UserHasLicenseForApp(CSteamID steamID, AppId_t appID) = 0;
	virtual bool RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup) = 0;
	virtual void GetGameplayStats() = 0;
	virtual SteamAPICall_t GetServerReputation() = 0;
	virtual uint32_t GetPublicIP() = 0;
	virtual bool HandleIncomingPacket(const void *pData, int cbData, uint32_t srcIP, uint16_t srcPort) = 0;
	virtual int GetNextOutgoingPacket(void *pOut, int cbMaxOut, uint32_t *pNetAdr, uint16_t *pPort) = 0;
	virtual void EnableHeartbeats(bool bActive) = 0;
	virtual void SetHeartbeatInterval(int iHeartbeatInterval) = 0;
	virtual void ForceHeartbeat() = 0;
	virtual SteamAPICall_t AssociateWithClan(CSteamID steamIDClan) = 0;
	virtual SteamAPICall_t ComputeNewPlayerCompatibility(CSteamID steamIDNewPlayer) = 0;
};

class ISteamGameServerStats001
{
public:
	virtual SteamAPICall_t RequestUserStats(CSteamID steamIDUser) = 0;
	virtual bool GetUserStat(CSteamID steamIDUser, const char *pchName, int32_t *pData) = 0;
	virtual bool GetUserStat(CSteamID steamIDUser, const char *pchName, float *pData) = 0;
	virtual bool GetUserAchievement(CSteamID steamIDUser, const char *pchName, bool *pbAchieved) = 0;
	virtual bool SetUserStat(CSteamID steamIDUser, const char *pchName, int32_t nData) = 0;
	virtual bool SetUserStat(CSteamID steamIDUser, const char *pchName, float fData) = 0;
	virtual bool UpdateUserAvgRateStat(CSteamID steamIDUser, const char *pchName, float flCountThisSession, double dSessionLength) = 0;
	virtual bool SetUserAchievement(CSteamID steamIDUser, const char *pchName) = 0;
	virtual bool ClearUserAchievement(CSteamID steamIDUser, const char *pchName) = 0;
	virtual SteamAPICall_t StoreUserStats(CSteamID steamIDUser) = 0;
};

class ISteamMatchmaking009
{
public:
	virtual int GetFavoriteGameCount() = 0;
	virtual bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32_t *pnIP, uint16_t *pnConnPort, uint16_t *pnQueryPort, uint32_t *punFlags, uint32_t *pRTime32LastPlayedOnServer) = 0;
	virtual int AddFavoriteGame(AppId_t nAppID, uint32_t nIP, uint16_t nConnPort, uint16_t nQueryPort, uint32_t unFlags, uint32_t rTime32LastPlayedOnServer) = 0;
    virtual bool RemoveFavoriteGame(AppId_t nAppID, uint32_t nIP, uint16_t nConnPort, uint16_t nQueryPort, uint32_t unFlags) = 0;
	virtual SteamAPICall_t RequestLobbyList() = 0;
	virtual void AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, ELobbyComparison eComparisonType) = 0;
	virtual void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType) = 0;
	virtual void AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo) = 0;
	virtual void AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable) = 0;
	virtual void AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter) = 0;
	virtual void AddRequestLobbyListResultCountFilter(int cMaxResults) = 0;
	virtual void AddRequestLobbyListCompatibleMembersFilter(CSteamID steamIDLobby) = 0;
	virtual CSteamID GetLobbyByIndex(int iLobby) = 0;
	virtual SteamAPICall_t CreateLobby(ELobbyType eLobbyType, int cMaxMembers) = 0;
	virtual SteamAPICall_t JoinLobby(CSteamID steamIDLobby) = 0;
	virtual void LeaveLobby(CSteamID steamIDLobby) = 0;
	virtual bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee) = 0;
	virtual int GetNumLobbyMembers(CSteamID steamIDLobby) = 0;
	virtual CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember) = 0;
	virtual const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey) = 0;
	virtual bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue) = 0;
	virtual int GetLobbyDataCount(CSteamID steamIDLobby) = 0;
	virtual bool GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize) = 0;
	virtual bool DeleteLobbyData(CSteamID steamIDLobby, const char *pchKey) = 0;
	virtual const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey) = 0;
	virtual void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue) = 0;
	virtual bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody) = 0;
	virtual int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType) = 0;
	virtual bool RequestLobbyData(CSteamID steamIDLobby) = 0;
	virtual void SetLobbyGameServer(CSteamID steamIDLobby, uint32_t unGameServerIP, uint16_t unGameServerPort, CSteamID steamIDGameServer) = 0;
	virtual bool GetLobbyGameServer(CSteamID steamIDLobby, uint32_t *punGameServerIP, uint16_t *punGameServerPort, CSteamID *psteamIDGameServer) = 0;
	virtual bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers) = 0;
	virtual int GetLobbyMemberLimit(CSteamID steamIDLobby) = 0;
	virtual bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType) = 0;
	virtual bool SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable) = 0;
	virtual CSteamID GetLobbyOwner(CSteamID steamIDLobby) = 0;
	virtual bool SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner) = 0;
	virtual bool SetLinkedLobby(CSteamID steamIDLobby, CSteamID steamIDLobbyDependent) = 0;
};

class ISteamMatchmakingServers001
{
public:
	virtual void RequestInternetServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, _ISteamMatchmakingServerListResponse_v001 *pRequestServersResponse) = 0;
	virtual void RequestLANServerList(AppId_t iApp, _ISteamMatchmakingServerListResponse_v001 *pRequestServersResponse) = 0;
	virtual void RequestFriendsServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, _ISteamMatchmakingServerListResponse_v001 *pRequestServersResponse) = 0;
	virtual void RequestFavoritesServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, _ISteamMatchmakingServerListResponse_v001 *pRequestServersResponse) = 0;
	virtual void RequestHistoryServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, _ISteamMatchmakingServerListResponse_v001 *pRequestServersResponse) = 0;
	virtual void RequestSpectatorServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, _ISteamMatchmakingServerListResponse_v001 *pRequestServersResponse) = 0;
	virtual gameserveritem_t *GetServerDetails(_EMatchMakingType_v001 eType, int iServer) = 0;
	virtual void CancelQuery(_EMatchMakingType_v001 eType) = 0;
	virtual void RefreshQuery(_EMatchMakingType_v001 eType) = 0;
	virtual bool IsRefreshing(_EMatchMakingType_v001 eType) = 0;
	virtual int GetServerCount(_EMatchMakingType_v001 eType) = 0;
	virtual void RefreshServer(_EMatchMakingType_v001 eType, int iServer) = 0;
	virtual HServerQuery PingServer(uint32_t unIP, uint16_t usPort, ISteamMatchmakingPingResponse *pRequestServersResponse) = 0;
	virtual HServerQuery PlayerDetails(uint32_t unIP, uint16_t usPort, ISteamMatchmakingPlayersResponse *pRequestServersResponse) = 0;
	virtual HServerQuery ServerRules(uint32_t unIP, uint16_t usPort, ISteamMatchmakingRulesResponse *pRequestServersResponse) = 0;
	virtual void CancelServerQuery(HServerQuery hServerQuery) = 0;
};

class ISteamMatchmakingServers002
{
public:
	virtual HServerListRequest RequestInternetServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse) = 0;
	virtual HServerListRequest RequestLANServerList(AppId_t iApp, ISteamMatchmakingServerListResponse *pRequestServersResponse) = 0;
	virtual HServerListRequest RequestFriendsServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse) = 0;
	virtual HServerListRequest RequestFavoritesServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse) = 0;
	virtual HServerListRequest RequestHistoryServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse) = 0;
	virtual HServerListRequest RequestSpectatorServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32_t nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse) = 0;
	virtual void ReleaseRequest(HServerListRequest hServerListRequest) = 0;
	virtual gameserveritem_t *GetServerDetails(HServerListRequest hRequest, int iServer) = 0;
	virtual void CancelQuery(HServerListRequest hRequest) = 0;
	virtual void RefreshQuery(HServerListRequest hRequest) = 0;
	virtual bool IsRefreshing(HServerListRequest hRequest) = 0;
	virtual int GetServerCount(HServerListRequest hRequest) = 0;
	virtual void RefreshServer(HServerListRequest hRequest, int iServer) = 0;
	virtual HServerQuery PingServer(uint32_t unIP, uint16_t usPort, ISteamMatchmakingPingResponse *pRequestServersResponse) = 0;
	virtual HServerQuery PlayerDetails(uint32_t unIP, uint16_t usPort, ISteamMatchmakingPlayersResponse *pRequestServersResponse) = 0;
	virtual HServerQuery ServerRules(uint32_t unIP, uint16_t usPort, ISteamMatchmakingRulesResponse *pRequestServersResponse) = 0;
	virtual void CancelServerQuery(HServerQuery hServerQuery) = 0;
};

class ISteamNetworking005
{
public:
	virtual bool SendP2PPacket(CSteamID steamIDRemote, const void *pubData, uint32_t cubData, EP2PSend eP2PSendType, int nChannel) = 0;
	virtual bool IsP2PPacketAvailable(uint32_t *pcubMsgSize, int nChannel) = 0;
	virtual bool ReadP2PPacket(void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize, CSteamID *psteamIDRemote, int nChannel) = 0;
	virtual bool AcceptP2PSessionWithUser(CSteamID steamIDRemote) = 0;
	virtual bool CloseP2PSessionWithUser(CSteamID steamIDRemote) = 0;
	virtual bool CloseP2PChannelWithUser(CSteamID steamIDRemote, int nChannel) = 0;
	virtual bool GetP2PSessionState(CSteamID steamIDRemote, P2PSessionState_t *pConnectionState) = 0;
	virtual bool AllowP2PPacketRelay(bool bAllow) = 0;
	virtual SNetListenSocket_t CreateListenSocket(int nVirtualP2PPort, uint32_t nIP, uint16_t nPort, bool bAllowUseOfPacketRelay) = 0;
	virtual SNetSocket_t CreateP2PConnectionSocket(CSteamID steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay) = 0;
	virtual SNetSocket_t CreateConnectionSocket(uint32_t nIP, uint16_t nPort, int nTimeoutSec) = 0;
	virtual bool DestroySocket(SNetSocket_t hSocket, bool bNotifyRemoteEnd) = 0;
	virtual bool DestroyListenSocket(SNetListenSocket_t hSocket, bool bNotifyRemoteEnd) = 0;
	virtual bool SendDataOnSocket(SNetSocket_t hSocket, void *pubData, uint32_t cubData, bool bReliable) = 0;
	virtual bool IsDataAvailableOnSocket(SNetSocket_t hSocket, uint32_t *pcubMsgSize) = 0;
	virtual bool RetrieveDataFromSocket(SNetSocket_t hSocket, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize) = 0;
	virtual bool IsDataAvailable(SNetListenSocket_t hListenSocket, uint32_t *pcubMsgSize, SNetSocket_t *phSocket) = 0;
	virtual bool RetrieveData(SNetListenSocket_t hListenSocket, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize, SNetSocket_t *phSocket) = 0;
	virtual bool GetSocketInfo(SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, uint32_t *punIPRemote, uint16_t *punPortRemote) = 0;
	virtual bool GetListenSocketInfo(SNetListenSocket_t hListenSocket, uint32_t *pnIP, uint16_t *pnPort) = 0;
	virtual ESNetSocketConnectionType GetSocketConnectionType(SNetSocket_t hSocket) = 0;
	virtual int GetMaxPacketSize(SNetSocket_t hSocket) = 0;
};

class ISteamRemoteStorage010
{
public:
	virtual bool FileWrite(const char *pchFile, const void *pvData, int32_t cubData) = 0;
	virtual int32_t FileRead(const char *pchFile, void *pvData, int32_t cubDataToRead) = 0;
	virtual bool FileForget(const char *pchFile) = 0;
	virtual bool FileDelete(const char *pchFile) = 0;
	virtual SteamAPICall_t FileShare(const char *pchFile) = 0;
	virtual bool SetSyncPlatforms(const char *pchFile, ERemoteStoragePlatform eRemoteStoragePlatform) = 0;
	virtual UGCFileWriteStreamHandle_t FileWriteStreamOpen(const char *pchFile) = 0;
	virtual EResult FileWriteStreamWriteChunk(UGCFileWriteStreamHandle_t writeHandle, const void *pvData, int32_t cubData) = 0;
	virtual EResult FileWriteStreamClose(UGCFileWriteStreamHandle_t writeHandle) = 0;
	virtual EResult FileWriteStreamCancel(UGCFileWriteStreamHandle_t writeHandle) = 0;
	virtual bool FileExists(const char *pchFile) = 0;
	virtual bool FilePersisted(const char *pchFile) = 0;
	virtual int32_t GetFileSize(const char *pchFile) = 0;
	virtual int64_t GetFileTimestamp(const char *pchFile) = 0;
	virtual ERemoteStoragePlatform GetSyncPlatforms(const char *pchFile) = 0;
	virtual int32_t GetFileCount() = 0;
	virtual const char *GetFileNameAndSize(int iFile, int32_t *pnFileSizeInBytes) = 0;
	virtual bool GetQuota(int32_t *pnTotalBytes, int32_t *puAvailableBytes) = 0;
	virtual bool IsCloudEnabledForAccount() = 0;
	virtual bool IsCloudEnabledForApp() = 0;
	virtual void SetCloudEnabledForApp(bool bEnabled) = 0;
	virtual SteamAPICall_t UGCDownload(UGCHandle_t hContent, uint32_t unPriority) = 0;
	virtual bool GetUGCDownloadProgress(UGCHandle_t hContent, uint32_t *pnBytesDownloaded, uint32_t *pnBytesExpected) = 0;
	virtual bool GetUGCDetails(UGCHandle_t hContent, AppId_t *pnAppID, char **ppchName, int32_t *pnFileSizeInBytes, CSteamID *pSteamIDOwner) = 0;
	virtual int32_t UGCRead(UGCHandle_t hContent, void *pvData, int32_t cubDataToRead, uint32_t cOffset) = 0;
	virtual int32_t GetCachedUGCCount() = 0;
	virtual UGCHandle_t GetCachedUGCHandle(int32_t iCachedContent) = 0;
	virtual SteamAPICall_t PublishWorkshopFile(const char *pchFile, const char *pchPreviewFile, AppId_t nConsumerAppId, const char *pchTitle, const char *pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t *pTags, EWorkshopFileType eWorkshopFileType) = 0;
	virtual PublishedFileUpdateHandle_t CreatePublishedFileUpdateRequest(PublishedFileId_t unPublishedFileId) = 0;
	virtual bool UpdatePublishedFileFile(PublishedFileUpdateHandle_t updateHandle, const char *pchFile) = 0;
	virtual bool UpdatePublishedFilePreviewFile(PublishedFileUpdateHandle_t updateHandle, const char *pchPreviewFile) = 0;
	virtual bool UpdatePublishedFileTitle(PublishedFileUpdateHandle_t updateHandle, const char *pchTitle) = 0;
	virtual bool UpdatePublishedFileDescription(PublishedFileUpdateHandle_t updateHandle, const char *pchDescription) = 0;
	virtual bool UpdatePublishedFileVisibility(PublishedFileUpdateHandle_t updateHandle, ERemoteStoragePublishedFileVisibility eVisibility) = 0;
	virtual bool UpdatePublishedFileTags(PublishedFileUpdateHandle_t updateHandle, SteamParamStringArray_t *pTags) = 0;
	virtual SteamAPICall_t CommitPublishedFileUpdate(PublishedFileUpdateHandle_t updateHandle) = 0;
	virtual SteamAPICall_t GetPublishedFileDetails(PublishedFileId_t unPublishedFileId) = 0;
	virtual SteamAPICall_t DeletePublishedFile(PublishedFileId_t unPublishedFileId) = 0;
	virtual SteamAPICall_t EnumerateUserPublishedFiles(uint32_t unStartIndex) = 0;
	virtual SteamAPICall_t SubscribePublishedFile(PublishedFileId_t unPublishedFileId) = 0;
	virtual SteamAPICall_t EnumerateUserSubscribedFiles(uint32_t unStartIndex) = 0;
	virtual SteamAPICall_t UnsubscribePublishedFile(PublishedFileId_t unPublishedFileId) = 0;
	virtual bool UpdatePublishedFileSetChangeDescription(PublishedFileUpdateHandle_t updateHandle, const char *pchChangeDescription) = 0;
	virtual SteamAPICall_t GetPublishedItemVoteDetails(PublishedFileId_t unPublishedFileId) = 0;
	virtual SteamAPICall_t UpdateUserPublishedItemVote(PublishedFileId_t unPublishedFileId, bool bVoteUp) = 0;
	virtual SteamAPICall_t GetUserPublishedItemVoteDetails(PublishedFileId_t unPublishedFileId) = 0;
	virtual SteamAPICall_t EnumerateUserSharedWorkshopFiles(CSteamID steamId, uint32_t unStartIndex, SteamParamStringArray_t *pRequiredTags, SteamParamStringArray_t *pExcludedTags) = 0;
	virtual SteamAPICall_t PublishVideo(EWorkshopVideoProvider eVideoProvider, const char *pchVideoAccount, const char *pchVideoIdentifier, const char *pchPreviewFile, AppId_t nConsumerAppId, const char *pchTitle, const char *pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t *pTags) = 0;
	virtual SteamAPICall_t SetUserPublishedFileAction(PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction) = 0;
	virtual SteamAPICall_t EnumeratePublishedFilesByUserAction(EWorkshopFileAction eAction, uint32_t unStartIndex) = 0;
	virtual SteamAPICall_t EnumeratePublishedWorkshopFiles(EWorkshopEnumerationType eEnumerationType, uint32_t unStartIndex, uint32_t unCount, uint32_t unDays, SteamParamStringArray_t *pTags, SteamParamStringArray_t *pUserTags) = 0;
	virtual SteamAPICall_t UGCDownloadToLocation(UGCHandle_t hContent, const char *pchLocation, uint32_t unPriority) = 0;
};

class ISteamScreenshots001
{
public:
	virtual ScreenshotHandle WriteScreenshot(void *pubRGB, uint32_t cubRGB, int nWidth, int nHeight) = 0;
	virtual ScreenshotHandle AddScreenshotToLibrary(const char *pchFilename, const char *pchThumbnailFilename, int nWidth, int nHeight) = 0;
	virtual void TriggerScreenshot() = 0;
	virtual void HookScreenshots(bool bHook) = 0;
	virtual bool SetLocation(ScreenshotHandle hScreenshot, const char *pchLocation) = 0;
	virtual bool TagUser(ScreenshotHandle hScreenshot, CSteamID steamID) = 0;
};

class ISteamUser016
{
public:
	virtual HSteamUser GetHSteamUser() = 0;
	virtual bool BLoggedOn() = 0;
	virtual CSteamID GetSteamID() = 0;
	virtual int InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32_t unIPServer, uint16_t usPortServer, bool bSecure) = 0;
	virtual void TerminateGameConnection(uint32_t unIPServer, uint16_t usPortServer) = 0;
	virtual void TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent, const char *pchExtraInfo = "") = 0;
	virtual bool GetUserDataFolder(char *pchBuffer, int cubBuffer) = 0;
	virtual void StartVoiceRecording() = 0;
	virtual void StopVoiceRecording() = 0;
	virtual EVoiceResult GetAvailableVoice(uint32_t *pcbCompressed, uint32_t *pcbUncompressed, uint32_t nUncompressedVoiceDesiredSampleRate) = 0;
	virtual EVoiceResult GetVoice(bool bWantCompressed, void *pDestBuffer, uint32_t cbDestBufferSize, uint32_t *nBytesWritten, bool bWantUncompressed, void *pUncompressedDestBuffer, uint32_t cbRawDestBufferSize, uint32_t *nUncompressBytesWritten, uint32_t nUncompressedVoiceDesiredSampleRate) = 0;
	virtual EVoiceResult DecompressVoice(const void *pCompressed, uint32_t cbCompressed, void *pDestBuffer, uint32_t cbDestBufferSize, uint32_t *nBytesWritten, uint32_t nDesiredSampleRate) = 0;
	virtual uint32_t GetVoiceOptimalSampleRate() = 0;
	virtual HAuthTicket GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32_t *pcbTicket) = 0;
	virtual EBeginAuthSessionResult BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID) = 0;
	virtual void EndAuthSession(CSteamID steamID) = 0;
	virtual void CancelAuthTicket(HAuthTicket hAuthTicket) = 0;
	virtual EUserHasLicenseForAppResult UserHasLicenseForApp(CSteamID steamID, AppId_t appID) = 0;
	virtual bool BIsBehindNAT() = 0;
	virtual void AdvertiseGame(CSteamID steamIDGameServer, uint32_t unIPServer, uint16_t usPortServer) = 0;
	virtual SteamAPICall_t RequestEncryptedAppTicket(void *pDataToInclude, int cbDataToInclude) = 0;
	virtual bool GetEncryptedAppTicket(void *pTicket, int cbMaxTicket, uint32_t *pcbTicket) = 0;
};

class ISteamUserStats011
{
public:
	virtual bool RequestCurrentStats() = 0;
	virtual bool GetStat(const char *pchName, int32_t *pData) = 0;
	virtual bool GetStat(const char *pchName, float *pData) = 0;
	virtual bool SetStat(const char *pchName, int32_t nData) = 0;
	virtual bool SetStat(const char *pchName, float fData) = 0;
	virtual bool UpdateAvgRateStat(const char *pchName, float flCountThisSession, double dSessionLength) = 0;
	virtual bool GetAchievement(const char *pchName, bool *pbAchieved) = 0;
	virtual bool SetAchievement(const char *pchName) = 0;
	virtual bool ClearAchievement(const char *pchName) = 0;
	virtual bool GetAchievementAndUnlockTime(const char *pchName, bool *pbAchieved, uint32_t *punUnlockTime) = 0;
	virtual bool StoreStats() = 0;
	virtual int GetAchievementIcon(const char *pchName) = 0;
	virtual const char *GetAchievementDisplayAttribute(const char *pchName, const char *pchKey) = 0;
	virtual bool IndicateAchievementProgress(const char *pchName, uint32_t nCurProgress, uint32_t nMaxProgress) = 0;
	virtual uint32_t GetNumAchievements() = 0;
	virtual const char *GetAchievementName(uint32_t iAchievement) = 0;
	virtual SteamAPICall_t RequestUserStats(CSteamID steamIDUser) = 0;
	virtual bool GetUserStat(CSteamID steamIDUser, const char *pchName, int32_t *pData) = 0;
	virtual bool GetUserStat(CSteamID steamIDUser, const char *pchName, float *pData) = 0;
	virtual bool GetUserAchievement(CSteamID steamIDUser, const char *pchName, bool *pbAchieved) = 0;
	virtual bool GetUserAchievementAndUnlockTime(CSteamID steamIDUser, const char *pchName, bool *pbAchieved, uint32_t *punUnlockTime) = 0;
	virtual bool ResetAllStats(bool bAchievementsToo) = 0;
	virtual SteamAPICall_t FindOrCreateLeaderboard(const char *pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType) = 0;
	virtual SteamAPICall_t FindLeaderboard(const char *pchLeaderboardName) = 0;
	virtual const char *GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard) = 0;
	virtual int GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard) = 0;
	virtual ELeaderboardSortMethod GetLeaderboardSortMethod(SteamLeaderboard_t hSteamLeaderboard) = 0;
	virtual ELeaderboardDisplayType GetLeaderboardDisplayType(SteamLeaderboard_t hSteamLeaderboard) = 0;
	virtual SteamAPICall_t DownloadLeaderboardEntries(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd) = 0;
	virtual SteamAPICall_t DownloadLeaderboardEntriesForUsers(SteamLeaderboard_t hSteamLeaderboard, CSteamID *prgUsers, int cUsers) = 0;
	virtual bool GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t *pLeaderboardEntry, int32_t *pDetails, int cDetailsMax) = 0;
	virtual SteamAPICall_t UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32_t nScore, const int32_t *pScoreDetails, int cScoreDetailsCount) = 0;
	virtual SteamAPICall_t AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC) = 0;
	virtual SteamAPICall_t GetNumberOfCurrentPlayers() = 0;
	virtual SteamAPICall_t RequestGlobalAchievementPercentages() = 0;
	virtual int GetMostAchievedAchievementInfo(char *pchName, uint32_t unNameBufLen, float *pflPercent, bool *pbAchieved) = 0;
	virtual int GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char *pchName, uint32_t unNameBufLen, float *pflPercent, bool *pbAchieved) = 0;
	virtual bool GetAchievementAchievedPercent(const char *pchName, float *pflPercent) = 0;
	virtual SteamAPICall_t RequestGlobalStats(int nHistoryDays) = 0;
	virtual bool GetGlobalStat(const char *pchStatName, int64_t *pData) = 0;
	virtual bool GetGlobalStat(const char *pchStatName, double *pData) = 0;
	virtual int32_t GetGlobalStatHistory(const char *pchStatName, int64_t *pData, uint32_t cubData) = 0;
	virtual int32_t GetGlobalStatHistory(const char *pchStatName, double *pData, uint32_t cubData) = 0;
};

class ISteamUtils005
{
public:
	virtual uint32_t GetSecondsSinceAppActive() = 0;
	virtual uint32_t GetSecondsSinceComputerActive() = 0;
	virtual EUniverse GetConnectedUniverse() = 0;
	virtual uint32_t GetServerRealTime() = 0;
	virtual const char *GetIPCountry() = 0;
	virtual bool GetImageSize(int iImage, uint32_t *pnWidth, uint32_t *pnHeight) = 0;
	virtual bool GetImageRGBA(int iImage, uint8_t *pubDest, int nDestBufferSize) = 0;
	virtual bool GetCSERIPPort(uint32_t *unIP, uint16_t *usPort) = 0;
	virtual uint8_t GetCurrentBatteryPower() = 0;
	virtual uint32_t GetAppID() = 0;
	virtual void SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition) = 0;
	virtual bool IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool *pbFailed) = 0;
	virtual ESteamAPICallFailure GetAPICallFailureReason(SteamAPICall_t hSteamAPICall) = 0;
	virtual bool GetAPICallResult(SteamAPICall_t hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed) = 0;
	virtual void RunFrame() = 0;
	virtual uint32_t GetIPCCallCount() = 0;
	virtual void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction) = 0;
	virtual bool IsOverlayEnabled() = 0;
	virtual bool BOverlayNeedsPresent() = 0;
	virtual SteamAPICall_t CheckFileSignature(const char *szFileName) = 0;
	virtual bool ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax) = 0;
	virtual uint32_t GetEnteredGamepadTextLength() = 0;
	virtual bool GetEnteredGamepadTextInput(char *pchText, uint32_t cchText) = 0;
};

class ISteamContentServer002
{
public:
	virtual bool LogOn(uint32_t uContentServerID) = 0;
	virtual bool LogOff() = 0;
	virtual bool BLoggedOn() = 0;
	virtual void SendClientContentAuthRequest(CSteamID steamID, uint32_t uContentID, uint64_t ulSessionToken, bool bTokenPresent) = 0;
	virtual bool BCheckTicket(CSteamID steamID, uint32_t uContentID, const void *pvTicketData, uint32_t cubTicketLength) = 0;
};
