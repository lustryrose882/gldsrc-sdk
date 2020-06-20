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

//	100% free public domain implementation of the SHA-1
//	algorithm by Dominik Reichl <dominik.reichl@t-online.de>
//
//
//	=== Test Vectors (from FIPS PUB 180-1) ===
//
//	SHA1("abc") =
//		A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
//
//	SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") =
//		84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
//
//	SHA1(A million repetitions of "a") =
//		34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F

#include <intrin.h>		// memcpy, memset etc... will be inlined.

#include <stdio.h>  // Needed for file access
#if defined(_PS3)
	#include <sys/memory.h>
#else
	#include <memory.h>
#endif
#include <string.h> // Needed for strcat and strcpy

// If you're compiling big endian, just comment out the following line
#define SHA1_LITTLE_ENDIAN

typedef union
{
	unsigned char c[64];
	unsigned long l[16];
} SHA1_WORKSPACE_BLOCK;

// SHA1 hash
const unsigned int k_cubHash = 20;
const unsigned int k_cchHash = 41; // k_cubHash * 2, plus 1 for terminator

#pragma pack(push, 1)
typedef	unsigned char SHADigest_t[k_cubHash];
#pragma pack(pop)

class CSHA1
{
public:
	// Two different formats for ReportHash(...)
	enum
	{
		REPORT_HEX = 0,
		REPORT_DIGIT = 1
	};

	// Constructor and Destructor
	CSHA1();
	virtual ~CSHA1();

	unsigned long m_state[5];
	unsigned long m_count[2];
	unsigned char m_buffer[64];
	unsigned char m_digest[k_cubHash];

	void Reset();

	// Update the hash value
	void Update(const unsigned char *data, unsigned int len);
	bool HashFile(char *szFileName);

	// Finalize hash and report
	void Final();

	void ReportHash(char *szReport, unsigned char uReportType = REPORT_HEX);
	void GetHash(unsigned char *uDest);
	const char *RawStringHash();

private:
	// Private SHA-1 transformation
	void Transform(unsigned long state[5], const unsigned char buffer[64]);

	// Member variables
	unsigned char m_workspace[64];
	SHA1_WORKSPACE_BLOCK *m_block; // SHA1 pointer to the byte array above
};

#define GenerateHash(hash, pubData, cubData) { CSHA1 sha1; sha1.Update((uint8_t *)pubData, cubData); sha1.Final(); sha1.GetHash(hash); }

// hash comparison function, for use with CUtlMap/CUtlRBTree
bool HashLessFunc(SHADigest_t const &lhs, SHADigest_t const &rhs);

// utility class for manipulating SHA1 hashes in their compact form
struct CSHA
{
public:
	SHADigest_t m_shaDigest;

	CSHA()
	{
		memset(m_shaDigest, 0, k_cubHash);
	}

	explicit CSHA(const SHADigest_t rhs)
	{
		memcpy(m_shaDigest, rhs, k_cubHash);
	}

	SHADigest_t &SHADigest()
	{
		return m_shaDigest;
	}

	bool operator<(const CSHA &rhs) const
	{
		return memcmp(m_shaDigest, rhs.m_shaDigest, k_cubHash) < 0;
	}

	bool operator==(const CSHA &rhs) const
	{
		return memcmp(m_shaDigest, rhs.m_shaDigest, k_cubHash) == 0;
	}

	bool operator!=(const CSHA &rhs) const
	{
		return !(*this == rhs);
	}

	bool operator==(const SHADigest_t &rhs) const
	{
		return memcmp(m_shaDigest, rhs, k_cubHash) == 0;
	}

	bool operator!=(const SHADigest_t &rhs) const
	{
		return !(*this == rhs);
	}

	CSHA &operator=(const SHADigest_t rhs)
	{
		memcpy(m_shaDigest, rhs, k_cubHash);
		return *this;
	}

	void AssignTo(SHADigest_t rhs) const
	{
		memcpy(rhs, m_shaDigest, k_cubHash);
	}
};
