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

#if !defined(STEAM_API_BUILD)
// Functions for authenticating users via Steam to download content
class ISteamContentServer
{
public:
	// connection functions
	virtual bool LogOn(uint32_t uContentServerID) = 0;
	virtual bool LogOff() = 0;
	virtual bool BLoggedOn() = 0;

	// user authentication functions
	// the IP address and port should be in host order, i.e 127.0.0.1 == 0x7f000001
	virtual void SendClientContentAuthRequest(CSteamID steamID, uint32_t uContentID, uint64_t ulSessionToken, bool bTokenPresent) = 0;
	virtual bool BCheckTicket(CSteamID steamID, uint32_t uContentID, const void *pvTicketData, uint32_t cubTicketLength) = 0;

	// some sort of status stuff here eventually
};

#else

#define ISteamContentServer ISteamContentServer002

#endif // #if !defined(STEAM_API_BUILD)

#define STEAMCONTENTSERVER_INTERFACE_VERSION "SteamContentServer002"

// client has been approved to download the content
struct CSClientApprove_t
{
	enum { k_iCallback = k_iSteamContentServerCallbacks + 1 };
	CSteamID m_SteamID;
	uint32_t m_uContentID;
};
