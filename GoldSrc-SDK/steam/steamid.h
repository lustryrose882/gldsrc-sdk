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

#define CSTEAMID_DEFINED

#pragma pack(push, 1)

// Old Steam2 ID stuff
typedef	unsigned short SteamInstanceID_t;		// MUST be 16 bits
typedef uint64_t SteamLocalUserID_t;			// MUST be 64 bits

//
// Each Steam instance (licensed Steam Service Provider) has a unique SteamInstanceID_t.
//
// Each Steam instance as its own DB of users.
// Each user in the DB has a unique SteamLocalUserID_t (a serial number, with possible
// rare gaps in the sequence).
//
//

//
// Applications need to be able to authenticate Steam users from ANY instance.
// So a SteamIDTicket contains SteamGlobalUserID, which is a unique combination of
// instance and user id.
//
// SteamLocalUserID is an unsigned 64-bit integer.
// For platforms without 64-bit int support, we provide access via a union that splits it into
// high and low unsigned 32-bit ints.  Such platforms will only need to compare LocalUserIDs
// for equivalence anyway - not perform arithmetic with them.
//

// Old steam2 user ID structures
struct SteamSplitLocalUserID_t
{
	uint32_t Low32bits;
	uint32_t High32bits;
};

struct TSteamGlobalUserID
{
	SteamInstanceID_t m_SteamInstanceID;

	union
	{
		SteamLocalUserID_t      unAll64Bits;
		SteamSplitLocalUserID_t split;
	} m_SteamLocalUserID;
};

// Steam ID structure (64 bits total)
class CSteamID
{
public:

	// Constructor
	CSteamID()
	{
		m_steamid.m_comp.m_unAccountID = 0;
		m_steamid.m_comp.m_EAccountType = k_EAccountTypeInvalid;
		m_steamid.m_comp.m_EUniverse = k_EUniverseInvalid;
		m_steamid.m_comp.m_unAccountInstance = 0;
	}

	// Purpose: Constructor
	// Input  : unAccountID -	32-bit account ID
	//			eUniverse -		Universe this account belongs to
	//			eAccountType -	Type of account
	CSteamID(uint32_t unAccountID, EUniverse eUniverse, EAccountType eAccountType)
	{
		Set(unAccountID, eUniverse, eAccountType);
	}

	// Purpose: Constructor
	// Input  : unAccountID -	32-bit account ID
	//			unAccountInstance - instance
	//			eUniverse -		Universe this account belongs to
	//			eAccountType -	Type of account
	CSteamID(uint32_t unAccountID, unsigned int unAccountInstance, EUniverse eUniverse, EAccountType eAccountType)
	{
#if defined(_SERVER) && defined(Assert)
		Assert(! ((k_EAccountTypeIndividual == eAccountType) && (unAccountInstance > k_unSteamUserWebInstance)));	// enforce that for individual accounts, instance is always 1
#endif // _SERVER
		InstancedSet(unAccountID, unAccountInstance, eUniverse, eAccountType);
	}

	// Purpose: Constructor
	// Input  : ulSteamID -		64-bit representation of a Steam ID
	// Note:	Will not accept a uint32_t or int32_t as input, as that is a probable mistake.
	//			See the stubbed out overloads in the private: section for more info.
	CSteamID(uint64_t ulSteamID)
	{
		SetFromUint64(ulSteamID);
	}

	// Purpose: Sets parameters for steam ID
	// Input  : unAccountID -	32-bit account ID
	//			eUniverse -		Universe this account belongs to
	//			eAccountType -	Type of account
	void Set(uint32_t unAccountID, EUniverse eUniverse, EAccountType eAccountType)
	{
		m_steamid.m_comp.m_unAccountID = unAccountID;
		m_steamid.m_comp.m_EUniverse = eUniverse;
		m_steamid.m_comp.m_EAccountType = eAccountType;

		if (eAccountType == k_EAccountTypeClan)
		{
			m_steamid.m_comp.m_unAccountInstance = 0;
		}
		else
		{
			// by default we pick the desktop instance
			m_steamid.m_comp.m_unAccountInstance = k_unSteamUserDesktopInstance;
		}
	}

	// Purpose: Sets parameters for steam ID
	// Input  : unAccountID -	32-bit account ID
	//			eUniverse -		Universe this account belongs to
	//			eAccountType -	Type of account
	void InstancedSet(uint32_t unAccountID, uint32_t unInstance, EUniverse eUniverse, EAccountType eAccountType)
	{
		m_steamid.m_comp.m_unAccountID = unAccountID;
		m_steamid.m_comp.m_EUniverse = eUniverse;
		m_steamid.m_comp.m_EAccountType = eAccountType;
		m_steamid.m_comp.m_unAccountInstance = unInstance;
	}

	// Purpose: Initializes a steam ID from its 52 bit parts and universe/type
	// Input  : ulIdentifier - 52 bits of goodness
	void FullSet(uint64_t ulIdentifier, EUniverse eUniverse, EAccountType eAccountType)
	{
		m_steamid.m_comp.m_unAccountID = (ulIdentifier & k_unSteamAccountIDMask);						// account ID is low 32 bits
		m_steamid.m_comp.m_unAccountInstance = ((ulIdentifier >> 32) & k_unSteamAccountInstanceMask);	// account instance is next 20 bits
		m_steamid.m_comp.m_EUniverse = eUniverse;
		m_steamid.m_comp.m_EAccountType = eAccountType;
	}

	// Purpose: Initializes a steam ID from its 64-bit representation
	// Input  : ulSteamID -		64-bit representation of a Steam ID
	void SetFromUint64(uint64_t ulSteamID)
	{
		m_steamid.m_unAll64Bits = ulSteamID;
	}

	// Clear all fields, leaving an invalid ID.
	void Clear()
	{
		m_steamid.m_comp.m_unAccountID = 0;
		m_steamid.m_comp.m_EAccountType = k_EAccountTypeInvalid;
		m_steamid.m_comp.m_EUniverse = k_EUniverseInvalid;
		m_steamid.m_comp.m_unAccountInstance = 0;
	}

#if defined(INCLUDED_STEAM_COMMON_STEAMCOMMON_H)
	// Purpose: Initializes a steam ID from a Steam2 ID structure
	// Input:	pTSteamGlobalUserID -	Steam2 ID to convert
	//			eUniverse -				universe this ID belongs to
	void SetFromSteam2(TSteamGlobalUserID *pTSteamGlobalUserID, EUniverse eUniverse)
	{
		m_steamid.m_comp.m_unAccountID       = pTSteamGlobalUserID->m_SteamLocalUserID.split.Low32bits * 2 + pTSteamGlobalUserID->m_SteamLocalUserID.split.High32bits;
		m_steamid.m_comp.m_EUniverse         = eUniverse;								// set the universe
		m_steamid.m_comp.m_EAccountType      = k_EAccountTypeIndividual;				// Steam 2 accounts always map to account type of individual
		m_steamid.m_comp.m_unAccountInstance = k_unSteamUserDesktopInstance;	// Steam2 only knew desktop instances
	}

	// Purpose: Fills out a Steam2 ID structure
	// Input:	pTSteamGlobalUserID -	Steam2 ID to write to
	void ConvertToSteam2(TSteamGlobalUserID *pTSteamGlobalUserID) const
	{
		// only individual accounts have any meaning in Steam 2, only they can be mapped
		// Assert(m_steamid.m_comp.m_EAccountType == k_EAccountTypeIndividual);

		pTSteamGlobalUserID->m_SteamInstanceID = 0;
		pTSteamGlobalUserID->m_SteamLocalUserID.split.High32bits = m_steamid.m_comp.m_unAccountID % 2;
		pTSteamGlobalUserID->m_SteamLocalUserID.split.Low32bits  = m_steamid.m_comp.m_unAccountID / 2;
	}
#endif // defined(INCLUDED_STEAM_COMMON_STEAMCOMMON_H)

	// Purpose: Converts steam ID to its 64-bit representation
	// Output : 64-bit representation of a Steam ID
	uint64_t ConvertToUint64() const
	{
		return m_steamid.m_unAll64Bits;
	}

	// Purpose: Converts the static parts of a steam ID to a 64-bit representation.
	//			For multiseat accounts, all instances of that account will have the
	//			same static account key, so they can be grouped together by the static
	//			account key.
	// Output : 64-bit static account key
	uint64_t GetStaticAccountKey() const
	{
		// note we do NOT include the account instance (which is a dynamic property) in the static account key
		return (uint64_t)((((uint64_t)m_steamid.m_comp.m_EUniverse) << 56) + ((uint64_t)m_steamid.m_comp.m_EAccountType << 52) + m_steamid.m_comp.m_unAccountID);
	}

	// Create an anonymous game server login to be filled in by the AM
	void CreateBlankAnonLogon(EUniverse eUniverse)
	{
		m_steamid.m_comp.m_unAccountID = 0;
		m_steamid.m_comp.m_EAccountType = k_EAccountTypeAnonGameServer;
		m_steamid.m_comp.m_EUniverse = eUniverse;
		m_steamid.m_comp.m_unAccountInstance = 0;
	}

	// Create an anonymous game server login to be filled in by the AM
	void CreateBlankAnonUserLogon(EUniverse eUniverse)
	{
		m_steamid.m_comp.m_unAccountID = 0;
		m_steamid.m_comp.m_EAccountType = k_EAccountTypeAnonUser;
		m_steamid.m_comp.m_EUniverse = eUniverse;
		m_steamid.m_comp.m_unAccountInstance = 0;
	}

	// Is this an anonymous game server login that will be filled in?
	bool BBlankAnonAccount() const
	{
		return m_steamid.m_comp.m_unAccountID == 0 && BAnonAccount() && m_steamid.m_comp.m_unAccountInstance == 0;
	}

	// Is this a game server account id? (Either persistent or anonymous)
	bool BGameServerAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeGameServer || m_steamid.m_comp.m_EAccountType == k_EAccountTypeAnonGameServer;
	}

	// Is this a persistent (not anonymous) game server account id?
	bool BPersistentGameServerAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeGameServer;
	}

	// Is this an anonymous game server account id?
	bool BAnonGameServerAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeAnonGameServer;
	}

	// Is this a content server account id?
	bool BContentServerAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeContentServer;
	}

	// Is this a clan account id?
	bool BClanAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeClan;
	}

	// Is this a chat account id?
	bool BChatAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeChat;
	}

	// Is this a chat account id?
	bool IsLobby() const
	{
		return (m_steamid.m_comp.m_EAccountType == k_EAccountTypeChat)
			&& (m_steamid.m_comp.m_unAccountInstance & k_EChatInstanceFlagLobby);
	}

	// Is this an individual user account id?
	bool BIndividualAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeIndividual || m_steamid.m_comp.m_EAccountType == k_EAccountTypeConsoleUser;
	}

	// Is this an anonymous account?
	bool BAnonAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeAnonUser || m_steamid.m_comp.m_EAccountType == k_EAccountTypeAnonGameServer;
	}

	// Is this an anonymous user account? (used to create an account or reset a password)
	bool BAnonUserAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeAnonUser;
	}

	// Is this a faked up Steam ID for a PSN friend account?
	bool BConsoleUserAccount() const
	{
		return m_steamid.m_comp.m_EAccountType == k_EAccountTypeConsoleUser;
	}

	// simple accessors
	void SetAccountID(uint32_t unAccountID)		{ m_steamid.m_comp.m_unAccountID = unAccountID; }
	void SetAccountInstance(uint32_t unInstance){ m_steamid.m_comp.m_unAccountInstance = unInstance; }
	void ClearIndividualInstance()				{ if (BIndividualAccount()) m_steamid.m_comp.m_unAccountInstance = 0; }
	bool HasNoIndividualInstance() const		{ return BIndividualAccount() && (m_steamid.m_comp.m_unAccountInstance==0); }
	AccountID_t GetAccountID() const			{ return m_steamid.m_comp.m_unAccountID; }
	uint32_t GetUnAccountInstance() const		{ return m_steamid.m_comp.m_unAccountInstance; }
	EAccountType GetEAccountType() const		{ return (EAccountType)m_steamid.m_comp.m_EAccountType; }
	EUniverse GetEUniverse() const				{ return m_steamid.m_comp.m_EUniverse; }
	void SetEUniverse(EUniverse eUniverse)		{ m_steamid.m_comp.m_EUniverse = eUniverse; }
	bool IsValid() const;

	// this set of functions is hidden, will be moved out of class
	explicit CSteamID(const char *pchSteamID, EUniverse eDefaultUniverse = k_EUniverseInvalid);
	const char *Render() const;						// renders this Steam3 ID to string
	const char *Render2() const;					// renders this Steam2 ID to string (obsolete format)
	static const char *Render(uint64_t ulSteamID);	// static method to render a uint64_t representation of a Steam3 ID to a string
	static const char *Render2(uint64_t ulSteamID);	// static method to render a uint64_t representation of a Steam2 ID to a string

	void SetFromString(const char *pchSteamID, EUniverse eDefaultUniverse);
	// SetFromString allows many partially-correct strings, constraining how
	// we might be able to change things in the future.
	// SetFromStringStrict requires the exact string forms that we support
	// and is preferred when the caller knows it's safe to be strict.
	// Returns whether the string parsed correctly.
	bool SetFromStringStrict(const char *pchSteamID, EUniverse eDefaultUniverse);
	bool SetFromSteam2String(const char *pchSteam2ID, EUniverse eUniverse);

	inline bool operator==(const CSteamID &val) const { return m_steamid.m_unAll64Bits == val.m_steamid.m_unAll64Bits; }
	inline bool operator!=(const CSteamID &val) const { return !operator==(val); }
	inline bool operator<(const CSteamID &val) const { return m_steamid.m_unAll64Bits < val.m_steamid.m_unAll64Bits; }
	inline bool operator>(const CSteamID &val) const { return m_steamid.m_unAll64Bits > val.m_steamid.m_unAll64Bits; }

	// DEBUG function
	bool BValidExternalSteamID() const;

private:
	// These are defined here to prevent accidental implicit conversion of a u32AccountID to a CSteamID.
	// If you get a compiler error about an ambiguous constructor/function then it may be because you're
	// passing a 32-bit int to a function that takes a CSteamID. You should explicitly create the SteamID
	// using the correct Universe and account Type/Instance values.
	CSteamID(uint32_t);
	CSteamID(int32_t);

	// 64 bits total
	union
	{
		struct SteamIDComponent_t
		{
#ifdef VALVE_BIG_ENDIAN
			EUniverse			m_EUniverse : 8;			// universe this account belongs to
			unsigned int		m_EAccountType : 4;			// type of account - can't show as EAccountType, due to signed / unsigned difference
			unsigned int		m_unAccountInstance : 20;	// dynamic instance ID
			uint32_t			m_unAccountID : 32;			// unique account identifier
#else
			uint32_t			m_unAccountID : 32;			// unique account identifier
			unsigned int		m_unAccountInstance : 20;	// dynamic instance ID
			unsigned int		m_EAccountType : 4;			// type of account - can't show as EAccountType, due to signed / unsigned difference
			EUniverse			m_EUniverse : 8;			// universe this account belongs to
#endif
		} m_comp;

		uint64_t m_unAll64Bits;
	} m_steamid;
};

union SteamID_t
{
	SteamID_t() : unAll64Bits(0ull) {}
	SteamID_t(CSteamID steamID) : unAll64Bits(steamID.ConvertToUint64()) {}
	SteamID_t(uint64_t ulSteamID) : unAll64Bits(ulSteamID) {}

	uint64_t unAll64Bits;
	SteamSplitLocalUserID_t split;
};

inline bool CSteamID::IsValid() const
{
	if (m_steamid.m_comp.m_EAccountType <= k_EAccountTypeInvalid || m_steamid.m_comp.m_EAccountType >= k_EAccountTypeMax)
		return false;

	if (m_steamid.m_comp.m_EUniverse <= k_EUniverseInvalid || m_steamid.m_comp.m_EUniverse >= k_EUniverseMax)
		return false;

	if (m_steamid.m_comp.m_EAccountType == k_EAccountTypeIndividual)
	{
		if (m_steamid.m_comp.m_unAccountID == 0 || m_steamid.m_comp.m_unAccountInstance > k_unSteamUserWebInstance)
			return false;
	}

	if (m_steamid.m_comp.m_EAccountType == k_EAccountTypeClan)
	{
		if (m_steamid.m_comp.m_unAccountID == 0 || m_steamid.m_comp.m_unAccountInstance != 0)
			return false;
	}

	if (m_steamid.m_comp.m_EAccountType == k_EAccountTypeGameServer)
	{
		if (m_steamid.m_comp.m_unAccountID == 0)
			return false;
		// Any limit on instances? We use them for local users and bots
	}

	return true;
}

// generic invalid CSteamID
#define k_steamIDNil CSteamID()

// This steamID comes from a user game connection to an out of date GS that hasnt implemented the protocol
// to provide its steamID
#define k_steamIDOutofDateGS CSteamID(0, 0, k_EUniverseInvalid, k_EAccountTypeInvalid)

// This steamID comes from a user game connection to an sv_lan GS
#define k_steamIDLanModeGS CSteamID(0, 0, k_EUniversePublic, k_EAccountTypeInvalid)

// This steamID can come from a user game connection to a GS that has just booted but hasnt yet even initialized
// its steam3 component and started logging on.
#define k_steamIDNotInitYetGS CSteamID(1, 0, k_EUniverseInvalid, k_EAccountTypeInvalid)

// This steamID can come from a user game connection to a GS that isn't using the steam authentication system but still
// wants to support the "Join Game" option in the friends list
#define k_steamIDNonSteamGS CSteamID(2, 0, k_EUniverseInvalid, k_EAccountTypeInvalid)

#pragma pack(pop)
