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

typedef uint64_t UGCQueryHandle_t;

// Different lists of published UGC for a user.
// If the current logged in user is different than the specified user, then some options may not be allowed.
enum EUserUGCList
{
	k_EUserUGCList_Published,
	k_EUserUGCList_VotedOn,
	k_EUserUGCList_VotedUp,
	k_EUserUGCList_VotedDown,
	k_EUserUGCList_WillVoteLater,
	k_EUserUGCList_Favorited,
	k_EUserUGCList_Subscribed,
	k_EUserUGCList_UsedOrPlayed,
	k_EUserUGCList_Followed,
};

// Matching UGC types for queries
enum EUGCMatchingUGCType
{
	k_EUGCMatchingUGCType_Items = 0,		// both mtx items and ready-to-use items
	k_EUGCMatchingUGCType_Items_Mtx = 1,
	k_EUGCMatchingUGCType_Items_ReadyToUse = 2,
	k_EUGCMatchingUGCType_Collections = 3,
	k_EUGCMatchingUGCType_Artwork = 4,
	k_EUGCMatchingUGCType_Videos = 5,
	k_EUGCMatchingUGCType_Screenshots = 6,
	k_EUGCMatchingUGCType_AllGuides = 7,		// both web guides and integrated guides
	k_EUGCMatchingUGCType_WebGuides = 8,
	k_EUGCMatchingUGCType_IntegratedGuides = 9,
	k_EUGCMatchingUGCType_UsableInGame = 10,		// ready-to-use items and integrated guides
	k_EUGCMatchingUGCType_ControllerBindings = 11,
};

// Sort order for user published UGC lists (defaults to creation order descending)
enum EUserUGCListSortOrder
{
	k_EUserUGCListSortOrder_CreationOrderDesc,
	k_EUserUGCListSortOrder_CreationOrderAsc,
	k_EUserUGCListSortOrder_TitleAsc,
	k_EUserUGCListSortOrder_LastUpdatedDesc,
	k_EUserUGCListSortOrder_SubscriptionDateDesc,
	k_EUserUGCListSortOrder_VoteScoreDesc,
	k_EUserUGCListSortOrder_ForModeration,
};

// Combination of sorting and filtering for queries across all UGC
enum EUGCQuery
{
	k_EUGCQuery_RankedByVote = 0,
	k_EUGCQuery_RankedByPublicationDate = 1,
	k_EUGCQuery_AcceptedForGameRankedByAcceptanceDate = 2,
	k_EUGCQuery_RankedByTrend = 3,
	k_EUGCQuery_FavoritedByFriendsRankedByPublicationDate = 4,
	k_EUGCQuery_CreatedByFriendsRankedByPublicationDate = 5,
	k_EUGCQuery_RankedByNumTimesReported = 6,
	k_EUGCQuery_CreatedByFollowedUsersRankedByPublicationDate = 7,
	k_EUGCQuery_NotYetRated = 8,
	k_EUGCQuery_RankedByTotalVotesAsc = 9,
	k_EUGCQuery_RankedByVotesUp = 10,
	k_EUGCQuery_RankedByTextSearch = 11,
	k_EUGCQuery_RankedByTotalUniqueSubscriptions = 12,
};

// Details for a single published file/UGC
struct SteamUGCDetails_t
{
	PublishedFileId_t m_nPublishedFileId;
	EResult m_eResult;												// The result of the operation.
	EWorkshopFileType m_eFileType;									// Type of the file
	AppId_t m_nCreatorAppID;										// ID of the app that created this file.
	AppId_t m_nConsumerAppID;										// ID of the app that will consume this file.
	char m_rgchTitle[k_cchPublishedDocumentTitleMax];				// title of document
	char m_rgchDescription[k_cchPublishedDocumentDescriptionMax];	// description of document
	uint64_t m_ulSteamIDOwner;										// Steam ID of the user who created this content.
	uint32_t m_rtimeCreated;										// time when the published file was created
	uint32_t m_rtimeUpdated;										// time when the published file was last updated
	uint32_t m_rtimeAddedToUserList;								// time when the user added the published file to their list (not always applicable)
	ERemoteStoragePublishedFileVisibility m_eVisibility;			// visibility
	bool m_bBanned;													// whether the file was banned
	bool m_bAcceptedForUse;											// developer has specifically flagged this item as accepted in the Workshop
	bool m_bTagsTruncated;											// whether the list of tags was too long to be returned in the provided buffer
	char m_rgchTags[k_cchTagListMax];								// comma separated list of all tags associated with this file
	// file/url information
	UGCHandle_t m_hFile;											// The handle of the primary file
	UGCHandle_t m_hPreviewFile;										// The handle of the preview file
	char m_pchFileName[k_cchFilenameMax];							// The cloud filename of the primary file
	int32_t m_nFileSize;											// Size of the primary file
	int32_t m_nPreviewFileSize;										// Size of the preview file
	char m_rgchURL[k_cchPublishedFileURLMax];						// URL (for a video or a website)
	// voting information
	uint32_t m_unVotesUp;											// number of votes up
	uint32_t m_unVotesDown;											// number of votes down
	float m_flScore;												// calculated score
	uint32_t m_unNumChildren;										// if m_eFileType == k_EWorkshopFileTypeCollection, then this number will be the number of children contained within the collection
};

class ISteamUGC
{
public:
	virtual UGCQueryHandle_t CreateQueryUserUGCRequest(AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32_t unPage) = 0;
	virtual UGCQueryHandle_t CreateQueryAllUGCRequest(EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32_t unPage) = 0;
	virtual SteamAPICall_t SendQueryUGCRequest(UGCQueryHandle_t handle) = 0;
	virtual bool GetQueryUGCResult(UGCQueryHandle_t handle, uint32_t index, SteamUGCDetails_t *pDetails) = 0;

	// Release the request to free up memory, after retrieving results
	virtual bool ReleaseQueryUGCRequest(UGCQueryHandle_t handle) = 0;

	virtual bool AddRequiredTag(UGCQueryHandle_t handle, const char *pTagName) = 0;
	virtual bool AddExcludedTag(UGCQueryHandle_t handle, const char *pTagName) = 0;
	virtual bool SetReturnLongDescription(UGCQueryHandle_t handle, bool bReturnLongDescription) = 0;
	virtual bool SetReturnTotalOnly(UGCQueryHandle_t handle, bool bReturnTotalOnly) = 0;

	virtual bool SetCloudFileNameFilter(UGCQueryHandle_t handle, const char *pMatchCloudFileName) = 0;

	virtual bool SetMatchAnyTag(UGCQueryHandle_t handle, bool bMatchAnyTag) = 0;
	virtual bool SetSearchText(UGCQueryHandle_t handle, const char *pSearchText) = 0;
	virtual bool SetRankedByTrendDays(UGCQueryHandle_t handle, uint32_t unDays) = 0;

	virtual SteamAPICall_t RequestUGCDetails(PublishedFileId_t nPublishedFileID) = 0;
};

#define CLIENTUGC_INTERFACE_VERSION "CLIENTUGC_INTERFACE_VERSION_001"
