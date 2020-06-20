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

#include "tier0/dbg.h"
#include "steamclientpublic.h"
#include "steamid.h"

// Purpose: Constructor
// Input  : pchSteamID - text representation of a Steam ID
CSteamID::CSteamID(const char *pchSteamID, EUniverse eDefaultUniverse /* = k_EUniverseInvalid */ )
{
	SetFromString(pchSteamID, eDefaultUniverse);
}

// Purpose: Initializes a steam ID from a string
// Input  : pchSteamID -		text representation of a Steam ID
void CSteamID::SetFromString(const char *pchSteamID, EUniverse eDefaultUniverse)
{
	int nAccountID = -1;
	int nInstance = 1;
	EUniverse eUniverse = eDefaultUniverse;
	EAccountType eAccountType = k_EAccountTypeIndividual;
	// BUGBUG Rich use the Q_ functions
	if (*pchSteamID == 'A')
	{
		// This is test only
		pchSteamID++; // skip the A
		eAccountType = k_EAccountTypeAnonGameServer;
		if (*pchSteamID == '-' || *pchSteamID == ':')
			pchSteamID++; // skip the optional - or :

		if (strchr(pchSteamID, '('))
		{
			sscanf(strchr(pchSteamID, '('), "(%d)", &nInstance);
		}

		if (strchr(pchSteamID, ':'))
		{
			sscanf(pchSteamID, "%d:%d", reinterpret_cast<int *>(&eUniverse), &nAccountID);
		}
		else
		{
			sscanf(pchSteamID, "%d", &nAccountID);
		}

		if (nAccountID == 0)
		{
			// i dont care what number you entered
			CreateBlankAnonLogon(eUniverse);
		}
		else
		{
			InstancedSet(nAccountID, nInstance, eUniverse, eAccountType);
		}
		return;
	}
	else if (*pchSteamID == 'G')
	{
		pchSteamID++; // skip the G
		eAccountType = k_EAccountTypeGameServer;
		if (*pchSteamID == '-' || *pchSteamID == ':')
			pchSteamID++; // skip the optional - or :
	}
	else if (*pchSteamID == 'C')
	{
		pchSteamID++; // skip the C
		eAccountType = k_EAccountTypeContentServer;
		if (*pchSteamID == '-' || *pchSteamID == ':')
			pchSteamID++; // skip the optional - or :
	}

	if (strchr(pchSteamID, ':'))
	{
		if (*pchSteamID == '[')
			pchSteamID++; // skip the optional [

		sscanf(pchSteamID, "%d:%d", reinterpret_cast<int *>(&eUniverse), &nAccountID);
		if (eUniverse == k_EUniverseInvalid)
			eUniverse = eDefaultUniverse;
	}
	else
	{
		sscanf(pchSteamID, "%d", &nAccountID);
	}

	Assert((eUniverse > k_EUniverseInvalid) && (eUniverse < k_EUniverseMax));

	Set(nAccountID, eUniverse, eAccountType);
}

#if defined(INCLUDED_STEAM_COMMON_STEAMCOMMON_H)
// Purpose: Initializes a steam ID from a Steam2 ID string
// Input:	pchSteam2ID -	Steam2 ID (as a string #:#:#) to convert
//			eUniverse -		universe this ID belongs to
// Output:	true if successful, false otherwise
bool CSteamID::SetFromSteam2String(const char *pchSteam2ID, EUniverse eUniverse)
{
	Assert(pchSteam2ID);

	// Convert the Steam2 ID string to a Steam2 ID structure
	TSteamGlobalUserID steam2ID;
	steam2ID.m_SteamInstanceID = 0;
	steam2ID.m_SteamLocalUserID.split.High32bits = 0;
	steam2ID.m_SteamLocalUserID.split.Low32bits	= 0;

	const char *pchTSteam2ID = pchSteam2ID;

	// Customer support is fond of entering steam IDs in the following form:  STEAM_n:x:y
	char *pchOptionalLeadString = "STEAM_";
	if (_strnicmp(pchSteam2ID, pchOptionalLeadString, strlen(pchOptionalLeadString)) == 0)
		pchTSteam2ID = pchSteam2ID + strlen(pchOptionalLeadString);

	char cExtraCharCheck = 0;

	int cFieldConverted = sscanf(pchTSteam2ID, "%hu:%u:%u%c", &steam2ID.m_SteamInstanceID,
		&steam2ID.m_SteamLocalUserID.split.High32bits, &steam2ID.m_SteamLocalUserID.split.Low32bits, &cExtraCharCheck);

	// Validate the conversion ... a special case is steam2 instance ID 1 which is reserved for special DoD handling
	if (cExtraCharCheck != 0 || cFieldConverted == EOF || cFieldConverted < 2 || (cFieldConverted < 3 && steam2ID.m_SteamInstanceID != 1))
		return false;

	// Now convert to steam ID from the Steam2 ID structure
	SetFromSteam2(&steam2ID, eUniverse);
	return true;
}
#endif

// Purpose: Renders the Steam3 ID to a buffer.  NOTE: for convenience of calling
//			code, this code returns a pointer to a static buffer and is NOT thread-safe.
// Output:  buffer with rendered Steam ID
const char *CSteamID::Render() const
{
	const int k_cBufLen = 255;
	const int k_cBufs = 4;	// # of static bufs to use (so people can compose output with multiple calls to Render())
	static char rgchBuf[k_cBufs][k_cBufLen];
	static int nBuf = 0;
	char *pchBuf = rgchBuf[nBuf];	// get pointer to current static buf
	nBuf++;	// use next buffer for next call to this method
	nBuf %= k_cBufs;

	switch (m_steamid.m_comp.m_EAccountType)
	{
	case k_EAccountTypeAnonGameServer:
		_snprintf(pchBuf, k_cBufLen, "STEAM_%u:%u(%u)", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID, m_steamid.m_comp.m_unAccountInstance);
		break;
	case k_EAccountTypeGameServer:
		_snprintf(pchBuf, k_cBufLen, "STEAM_%u:%u", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
		break;
	case k_EAccountTypeMultiseat:
		_snprintf(pchBuf, k_cBufLen, "STEAM_%u:%u(%u)", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID, m_steamid.m_comp.m_unAccountInstance);
		break;
	case k_EAccountTypePending:
		_snprintf(pchBuf, k_cBufLen, "STEAM_%u:%u(pending)", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
		break;
	case k_EAccountTypeContentServer:
		_snprintf(pchBuf, k_cBufLen, "STEAM_%u:%u", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
		break;
	default:
		_snprintf(pchBuf, k_cBufLen, "STEAM_%u:%u", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
		break;
	}

	return pchBuf;
}

// Purpose: Renders the Steam2 ID to a buffer.  NOTE: for convenience of calling
//			code, this code returns a pointer to a static buffer and is NOT thread-safe.
// Output:  buffer with rendered Steam2 ID
const char *CSteamID::Render2() const
{
	const int k_cBufLen = 255;
	const int k_cBufs = 4;	// # of static bufs to use (so people can compose output with multiple calls to Render())
	static char rgchBuf[k_cBufs][k_cBufLen];
	static int nBuf = 0;
	char *pchBuf = rgchBuf[nBuf];	// get pointer to current static buf
	nBuf++;	// use next buffer for next call to this method
	nBuf %= k_cBufs;

	switch (m_steamid.m_comp.m_EAccountType)
	{
	// only individual accounts have any meaning in Steam 2, only they can be mapped
	case k_EAccountTypeInvalid:
	case k_EAccountTypeIndividual:
		_snprintf(pchBuf, k_cBufLen, "STEAM_0:%u:%u", (m_steamid.m_comp.m_unAccountID % 2u) ? 1u : 0u, m_steamid.m_comp.m_unAccountID / 2u);
		break;
	default:
		_snprintf(pchBuf, k_cBufLen, "%llu", ConvertToUint64());
		break;
	}

	return pchBuf;
}

// Purpose: Renders the passed-in Steam3 ID to a buffer.  NOTE: for convenience of calling
//			code, this code returns a pointer to a static buffer and is NOT thread-safe.
// Input:	64-bit representation of Steam ID to render
// Output:  buffer with rendered Steam ID
const char *CSteamID::Render(uint64_t ulSteamID)
{
	CSteamID steamID(ulSteamID);
	return steamID.Render();
}

// Purpose: Renders the passed-in Steam2 ID to a buffer.  NOTE: for convenience of calling
//			code, this code returns a pointer to a static buffer and is NOT thread-safe.
// Input:	64-bit representation of Steam ID to render
// Output:  buffer with rendered Steam ID
const char *CSteamID::Render2(uint64_t ulSteamID)
{
	CSteamID steamID(ulSteamID);
	return steamID.Render2();
}

// Purpose: some steamIDs are for internal use only
// This is really debug code, but we run with asserts on in retail, so ...
bool CSteamID::BValidExternalSteamID() const
{
	if (m_steamid.m_comp.m_EAccountType == k_EAccountTypePending)
		return false;

	if (m_steamid.m_comp.m_EAccountType != k_EAccountTypeAnonGameServer && m_steamid.m_comp.m_EAccountType != k_EAccountTypeContentServer)
	{
		if (m_steamid.m_comp.m_unAccountID == 0 && m_steamid.m_comp.m_unAccountInstance == 0)
			return false;
	}

	return true;
}
