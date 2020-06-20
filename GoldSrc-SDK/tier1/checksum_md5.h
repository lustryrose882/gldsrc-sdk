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

// 16 bytes == 128 bit digest
#define MD5_DIGEST_LENGTH		16
#define MD5_BIT_LENGTH			(MD5_DIGEST_LENGTH * sizeof(unsigned char))

struct MD5Value_t
{
	unsigned char bits[MD5_DIGEST_LENGTH];

	void Zero();
	bool IsZero() const;

	bool operator==(const MD5Value_t &src) const;
	bool operator!=(const MD5Value_t &src) const;
};

// MD5 Hash
struct MD5Context_t
{
	unsigned int	buf[4];
    unsigned int	bits[2];
    unsigned char	in[64];
};

void MD5Init(MD5Context_t *context);
void MD5Update(MD5Context_t *context, unsigned char const *buf, unsigned int len);
void MD5Final(unsigned char digest[MD5_DIGEST_LENGTH], MD5Context_t *context);

const char *MD5_Print(unsigned char *digest, int hashlen);

/// Convenience wrapper to calculate the MD5 for a buffer, all in one step, without
/// bothering with the context object.
void MD5_ProcessSingleBuffer(const void *p, int len, MD5Value_t &md5Result);

unsigned int MD5_PseudoRandom(unsigned int nSeed);

/// Returns true if the values match.
bool MD5_Compare(const MD5Value_t &data, const MD5Value_t &compare);

inline bool MD5Value_t::operator==(const MD5Value_t &src) const
{
	return MD5_Compare(*this, src);
}

inline bool MD5Value_t::operator!=(const MD5Value_t &src) const
{
	return !MD5_Compare(*this, src);
}
