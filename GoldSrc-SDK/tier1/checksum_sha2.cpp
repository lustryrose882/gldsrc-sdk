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

#include "tier0/basetypes.h"
#include "tier0/commonmacros.h"
#include "checksum_sha2.h"

using namespace std;

// Hash constant words K for SHA-1:
const uint32_t K1_0_TO_19  = 0x5a827999UL;
const uint32_t K1_20_TO_39 = 0x6ed9eba1UL;
const uint32_t K1_40_TO_59 = 0x8f1bbcdcUL;
const uint32_t K1_60_TO_79 = 0xca62c1d6UL;

// Initial hash value H for SHA-1
const static uint32_t sha1_initial_hash_value[5] =
{
	0x67452301UL, 0xefcdab89UL, 0x98badcfeUL, 0x10325476UL,
	0xc3d2e1f0UL
};

// Hash constant words K for SHA-224 and SHA-256
const static uint32_t K256[64] =
{
	0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL,
	0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL,
	0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL,
	0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL,
	0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL,
	0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL,
	0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL,
	0xc6e00bf3UL, 0xd5a79147UL, 0x06ca6351UL, 0x14292967UL,
	0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL,
	0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
	0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL,
	0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL,
	0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL,
	0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL,
	0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL,
	0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL
};

// Initial hash value H for SHA-224
const static uint32_t sha224_initial_hash_value[8] =
{
	0xc1059ed8UL, 0x367cd507UL, 0x3070dd17UL, 0xf70e5939UL,
	0xffc00b31UL, 0x68581511UL, 0x64f98fa7UL, 0xbefa4fa4UL
};

// Initial hash value H for SHA-256
const static uint32_t sha256_initial_hash_value[8] =
{
	0x6a09e667UL, 0xbb67ae85UL, 0x3c6ef372UL, 0xa54ff53aUL,
	0x510e527fUL, 0x9b05688cUL, 0x1f83d9abUL, 0x5be0cd19UL
};

const static uint64_t K512[80] =
{
	0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL,
	0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
	0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
	0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
	0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
	0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
	0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL,
	0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
	0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
	0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
	0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL,
	0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
	0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL,
	0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
	0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
	0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
	0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL,
	0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
	0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL,
	0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
	0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
	0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
	0xd192e819d6ef5218ULL, 0xd69906245565a910ULL,
	0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
	0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
	0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
	0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
	0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
	0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL,
	0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
	0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL,
	0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
	0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
	0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
	0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
	0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
	0x28db77f523047d84ULL, 0x32caab7b40c72493ULL,
	0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
	0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
	0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
};

// Initial hash value H for SHA-384
const static uint64_t sha384_initial_hash_value[8] =
{
	0xcbbb9d5dc1059ed8ULL, 0x629a292a367cd507ULL,
	0x9159015a3070dd17ULL, 0x152fecd8f70e5939ULL,
	0x67332667ffc00b31ULL, 0x8eb44a8768581511ULL,
	0xdb0c2e0d64f98fa7ULL, 0x47b5481dbefa4fa4ULL
};

// Initial hash value H for SHA-512
const static uint64_t sha512_initial_hash_value[8] =
{
	0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL,
	0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
	0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL,
	0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
};

CSHA2::CSHA2()
{
	m_Type = enuSHA_NONE;
	m_boolIsBigEndian = true;
	m_boolEnded = false;

	// run-time check for endian-ness
	unsigned int test = 1;
	uint8_t *ptr = (uint8_t *)&test;
	if (ptr[0])
	{
		m_boolIsBigEndian = false;
	}

	memset(m_chrHexHash, 0, SHA512_DIGESTC_STRING_LENGTH);
	memset(m_digest,     0, SHA512_DIGESTC_LENGTH);
}

CSHA2::~CSHA2()
{

}

// Constant used by SHA224/256/384/512_End() functions for converting the
// digest to a readable hexadecimal character string:

static const char *sha_hex_digits = "0123456789abcdef";
void CSHA2::SHA1_Internal_Transform(const uint32_t *data)
{
	uint32_t  a, b, c, d, e;
	uint32_t *state = (uint32_t*)ctx.state;
	uint32_t  T1, T2, *W1 = (uint32_t *)ctx.buffer;
	int j;

	// Initialize registers with the prev. intermediate value
	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];
	e = state[4];
	j = 0;

	do
	{
		if (m_boolIsBigEndian)
			W1[j] = *data++;
		else
			REVERSE32(*data++, W1[j]); // Copy data while converting to host byte order

		T1 = ROTL32(5, a) + Ch(b, c, d) + e + K1_0_TO_19 + W1[j];
		e = d;
		d = c;
		c = ROTL32(30, b);
		b = a;
		a = T1;
		j++;
	}
	while (j < 16);

	do
	{
		T1 = W1[(j + 13) & 0x0f] ^ W1[(j + 8) & 0x0f] ^ W1[(j + 2) & 0x0f] ^ W1[j & 0x0f];
		if (j < 20)      T2 = Ch(b, c, d)     + K1_0_TO_19;
		else if (j < 40) T2 = Parity(b, c, d) + K1_20_TO_39;
		else if (j < 60) T2 = Maj(b, c, d)    + K1_40_TO_59;
		else             T2 = Parity(b, c, d) + K1_60_TO_79;
		T1 = ROTL32(5, a) + T2 + e + (W1[j & 0x0f] = ROTL32(1, T1));
		e = d;
		d = c;
		c = ROTL32(30, b);
		b = a;
		a = T1;
		j++;
	}
	while (j < 80);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
}

void CSHA2::SHA256_Internal_Transform(const uint32_t *data)
{
	uint32_t  a, b, c, d, e, f, g, h, s0, s1;
	uint32_t *state = (uint32_t *)ctx.state;
	uint32_t  T1, T2, *W256 = (uint32_t *)ctx.buffer;;
	int j;

	// Initialize registers with the prev. intermediate value
	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];
	e = state[4];
	f = state[5];
	g = state[6];
	h = state[7];

	j = 0;
	do
	{
		if (m_boolIsBigEndian)
			W256[j] = *data++;
		else
			REVERSE32(*data++,W256[j]);// Copy data while converting to host byte order

		T1 = h + Sigma1_256(e) + Ch(e, f, g) + K256[j] + W256[j];
		T2 = Sigma0_256(a) + Maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + T1;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;

		j++;
	}
	while (j < 16);

	do
	{
		// Part of the message block expansion:
		s0 = W256[(j + 1) & 0x0f];
		s0 = sigma0_256(s0);
		s1 = W256[(j + 14) & 0x0f];
		s1 = sigma1_256(s1);

		// Apply the SHA-256 compression function to update a..h
		T1 = h + Sigma1_256(e) + Ch(e, f, g) + K256[j] +
		(W256[j & 0x0f] += s1 + W256[(j + 9) & 0x0f] + s0);
		T2 = Sigma0_256(a) + Maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + T1;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;

		j++;
	}
	while (j < 64);

	// Compute the current intermediate hash value
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
	state[5] += f;
	state[6] += g;
	state[7] += h;
}

void CSHA2::SHA512_Internal_Transform(const uint64_t *data)
{
	uint64_t a, b, c, d, e, f, g, h, s0, s1;
	uint64_t *state = (uint64_t *)ctx.state;
	uint64_t T1, T2, *W512 = (uint64_t *)ctx.buffer;
	int j;

	// Initialize registers with the prev. intermediate value
	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];
	e = state[4];
	f = state[5];
	g = state[6];
	h = state[7];

	j = 0;

	do
	{
		if (m_boolIsBigEndian)
			W512[j] = *data++;
		else
			REVERSE64(*data++, W512[j]); // copy and convert TO host byte order

		T1 = h + Sigma1_512(e) + Ch(e, f, g) + K512[j] + W512[j];
		T2 = Sigma0_512(a) + Maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + T1;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;

		j++;
	}
	while (j < 16);

	do
	{
		// Part of the message block expansion:
		s0 = W512[(j + 1) & 0x0f];
		s0 = sigma0_512(s0);
		s1 = W512[(j + 14) & 0x0f];
		s1 =  sigma1_512(s1);

		// Apply the SHA-512 compression function to update a..h
		T1 = h + Sigma1_512(e) + Ch(e, f, g) + K512[j] +
			(W512[j & 0x0f] += s1 + W512[(j + 9) & 0x0f] + s0);

		T2 = Sigma0_512(a) + Maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + T1;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;

		j++;
	}
	while (j < 80);

	// Compute the current intermediate hash value
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
	state[5] += f;
	state[6] += g;
	state[7] += h;
}

void CSHA2::SHA256_Internal_Last(bool isSha1)
{
	uint32_t usedspace;
	usedspace = (uint32_t)(ctx.bitcount[0] >> 3) % 64;
	if (usedspace == 0)
	{
		MEMSET_BZERO(ctx.buffer, 56);
		ctx.buffer[0] = 0x80;
	}
	else
	{
		ctx.buffer[usedspace++] = 0x80;
		if (usedspace <= 56)
		{
			MEMSET_BZERO(&ctx.buffer[usedspace], 56 - usedspace);
		}
		else
		{
			if (usedspace < 64)
			{
				MEMSET_BZERO(&ctx.buffer[usedspace], 64 - usedspace);
			}

			if (isSha1)
				SHA1_Internal_Transform((uint32_t *)ctx.buffer);
			else
				SHA256_Internal_Transform((uint32_t *)ctx.buffer);

			MEMSET_BZERO(ctx.buffer, 56);
		}
	}

	if (!m_boolIsBigEndian)
		REVERSE64(ctx.bitcount[0], ctx.bitcount[0]);

	*(uint64_t *)&ctx.buffer[56] = ctx.bitcount[0];

	if (isSha1)
		SHA1_Internal_Transform((uint32_t *)ctx.buffer);
	else
		SHA256_Internal_Transform((uint32_t *)ctx.buffer);
}

void CSHA2::SHA512_Internal_Last()
{
	uint32_t usedspace;
	usedspace = (uint32_t)(ctx.bitcount[0] >> 3) % 128;
	if (usedspace == 0)
	{
		MEMSET_BZERO(ctx.buffer, 112);
		ctx.buffer[0] = 0x80;
	}
	else
	{
		ctx.buffer[usedspace++] = 0x80;
		if (usedspace <= 112)
		{
			MEMSET_BZERO(&ctx.buffer[usedspace], 112 - usedspace);
		}
		else
		{
			if (usedspace < 128)
			{
				MEMSET_BZERO(&ctx.buffer[usedspace], 128 - usedspace);
			}

			SHA512_Internal_Transform((uint64_t *)ctx.buffer);
			MEMSET_BZERO(ctx.buffer, 112);
		}

		usedspace = 0;
	}

	if (!m_boolIsBigEndian)
	{
		REVERSE64(ctx.bitcount[0], ctx.bitcount[0]);
		REVERSE64(ctx.bitcount[1], ctx.bitcount[1]);
	}

	*(uint64_t *)&ctx.buffer[112] = ctx.bitcount[1];
	*(uint64_t *)&ctx.buffer[120] = ctx.bitcount[0];
	SHA512_Internal_Transform((uint64_t *)ctx.buffer);
}

void CSHA2::SHA32bit_Update(const uint8_t *data, size_t len, bool isSha1)
{
	uint32_t freespace, usedspace;
	if (len < 1)
	{
		// Calling with no data is valid - we do nothing
		return;
	}

	usedspace = (uint32_t)(ctx.bitcount[0] >> 3) % 64;
	if (usedspace > 0)
	{
		// Calculate how much free space is available in the buffer
		freespace = 64 - usedspace;
		if (len >= freespace)
		{
			// Fill the buffer completely and process it
			MEMCPY_BCOPY(&ctx.buffer[usedspace], data, freespace);
			ctx.bitcount[0] += freespace << 3;
			len -= freespace;
			data += freespace;

			if (isSha1)
				SHA1_Internal_Transform((uint32_t *)ctx.buffer);
			else
				SHA256_Internal_Transform((uint32_t *)ctx.buffer);
		}
		else
		{
			// The buffer is not yet full
			MEMCPY_BCOPY(&ctx.buffer[usedspace], data, len);
			ctx.bitcount[0] += len << 3;
			return;
		}
	}
	while (len >= 64)
	{
		// Process as many complete blocks as we can
		if (isSha1)
			SHA1_Internal_Transform((uint32_t *)data);
		else
			SHA256_Internal_Transform((uint32_t *)data);

		ctx.bitcount[0] += 512;
		len -= 64;
		data += 64;
	}

	if (len > 0)
	{
		// There's left-overs, so save 'em
		MEMCPY_BCOPY(&ctx.buffer, data, len);
		ctx.bitcount[0] += len << 3;
	}
}

void CSHA2::SHA64bit_Update(const uint8_t *data, size_t len)
{
	uint32_t freespace, usedspace;

	if (len < 1)
	{
		return;
	}
	// Calling with no data is valid - we do nothing

	usedspace = (uint32_t)(ctx.bitcount[0] >> 3) % 128;
	if (usedspace > 0)
	{
		// Calculate how much free space is available in the buffer
		freespace = 128 - usedspace;
		if (len >= freespace)
		{
			// Fill the buffer completely and process it
			MEMCPY_BCOPY(&ctx.buffer[usedspace], data, freespace);
			ADDINC128(ctx.bitcount, freespace << 3);
			len -= freespace;
			data += freespace;
			SHA512_Internal_Transform((uint64_t *)ctx.buffer);
		}
		else
		{
			// The buffer is not yet full
			MEMCPY_BCOPY(&ctx.buffer[usedspace], data, len);
			ADDINC128(ctx.bitcount, len << 3);
			return;
		}
	}

	while (len >= 128)
	{
		// Process as many complete blocks as we can
		SHA512_Internal_Transform((uint64_t *)data);
		ADDINC128(ctx.bitcount, 1024);
		len -= 128;
		data += 128;
	}

	if (len > 0)
	{
		// There's left-overs, so save 'em
		MEMCPY_BCOPY(ctx.buffer, data, len);
		ADDINC128(ctx.bitcount, len << 3);
	}
}

void CSHA2::Init(SHA_TYPE type)
{
	m_Type = type;
	m_boolEnded = false;
	MEMSET_BZERO(&ctx, sizeof(SHA_CTX));
	switch (m_Type)
	{
	case enuSHA1   : MEMCPY_BCOPY(ctx.state, sha1_initial_hash_value,   sizeof(uint32_t) * 5); break;
	case enuSHA224 : MEMCPY_BCOPY(ctx.state, sha224_initial_hash_value, sizeof(uint32_t) * 8); break;
	case enuSHA256 : MEMCPY_BCOPY(ctx.state, sha256_initial_hash_value, sizeof(uint32_t) * 8); break;
	case enuSHA384 : MEMCPY_BCOPY(ctx.state, sha384_initial_hash_value, sizeof(uint64_t) * 8); break;
	case enuSHA512 : MEMCPY_BCOPY(ctx.state, sha512_initial_hash_value, sizeof(uint64_t) * 8); break;
	default: break;
	}
}

const char *CSHA2::GetTypeString() const
{
	switch (m_Type)
	{
	case CSHA2::enuSHA1   : return "SHA160";
	case CSHA2::enuSHA224 : return "SHA224";
	case CSHA2::enuSHA256 : return "SHA256";
	case CSHA2::enuSHA384 : return "SHA384";
	case CSHA2::enuSHA512 : return "SHA512";
	default : return "Unknown!";
	}
};

void CSHA2::Update(const uint8_t *data, size_t len)
{
	switch (m_Type)
	{
	case enuSHA1:	SHA32bit_Update(data, len, true); break;
	case enuSHA224:	SHA32bit_Update(data, len); break;
	case enuSHA256:	SHA32bit_Update(data, len); break;
	case enuSHA384:	SHA64bit_Update(data, len); break;
	case enuSHA512:	SHA64bit_Update(data, len); break;
	default: break;
	}
}

void CSHA2::End()
{
	uint8_t *d = m_digest;
	char *buf = m_chrHexHash;
	int i, j, diglen, statecnt = 8;
	bool is64bit = false;
	uint32_t *state32 = (uint32_t *)ctx.state;
	uint64_t *state64 = (uint64_t *)ctx.state;

	switch (m_Type)
	{
	case enuSHA1:
	{
		SHA256_Internal_Last(true);
		statecnt = 5;
		diglen = SHA1_DIGESTC_LENGTH;
		break;
	}
	case enuSHA224:
	{
		SHA256_Internal_Last();
		diglen = SHA224_DIGESTC_LENGTH;
		break;
	}
	case enuSHA256:
	{
		SHA256_Internal_Last();
		diglen = SHA256_DIGESTC_LENGTH;
		break;
	}
	case enuSHA384:
	{
		SHA512_Internal_Last();
		is64bit = true;
		diglen = SHA384_DIGESTC_LENGTH;
		break;
	}
	case enuSHA512:
	{
		SHA512_Internal_Last();
		is64bit = true;
		diglen = SHA512_DIGESTC_LENGTH;
		break;
	}
	}

	if (m_boolIsBigEndian)
	{
		MEMCPY_BCOPY(&m_digest, &ctx.state, diglen);
	}
	else
	{
		uint8_t *dp = m_digest, *ptr;
		for (i = 0; i < statecnt; i++)
		{
			if (is64bit)
				ptr = (uint8_t *)&state64[i];
			else
				ptr = (uint8_t *)&state32[i];

			for (j = is64bit ? 7 : 3; j > -1; --j)
				*dp++ = ptr[j];
		}
	}

	for (i = 0; i < diglen; i++)
	{
		*buf++ = sha_hex_digits[(*d & 0xf0) >> 4];
		*buf++ = sha_hex_digits[*d & 0x0f];
		d++;
	}

	*buf = '\0';
	m_boolEnded = true;
}

const char *CSHA2::RawHash(int &length)
{
	if (!m_boolEnded)
	{
		length = 0;
		return nullptr;
	}

	switch (m_Type)
	{
	case enuSHA1:	length = SHA1_DIGESTC_LENGTH;   break;
	case enuSHA224:	length = SHA224_DIGESTC_LENGTH; break;
	case enuSHA256:	length = SHA256_DIGESTC_LENGTH; break;
	case enuSHA384:	length = SHA384_DIGESTC_LENGTH; break;
	case enuSHA512:	length = SHA512_DIGESTC_LENGTH; break;
	default:		length = 0;
	}

	return (const char *)m_digest;
}

const char *CSHA2::RawStringHash()
{
	return m_chrHexHash;
}

// Get the final hash as a pre-formatted string
void CSHA2::ReportHash(char *szReport, unsigned char uReportType)
{
	int length;
	switch (m_Type)
	{
	case enuSHA1:	length = SHA1_DIGESTC_LENGTH;   break;
	case enuSHA224:	length = SHA224_DIGESTC_LENGTH; break;
	case enuSHA256:	length = SHA256_DIGESTC_LENGTH; break;
	case enuSHA384:	length = SHA384_DIGESTC_LENGTH; break;
	case enuSHA512:	length = SHA512_DIGESTC_LENGTH; break;
	default:		length = 0;
	}

	unsigned char i = 0;
	char szTemp[12];

	if (!szReport)
		return;

	if (uReportType == REPORT_HEX)
	{
		for (i = 0; i < length; i++)
		{
			sprintf(szTemp, "%02x", m_digest[i]);
			strcat(szReport, szTemp);
		}
	}
	else if (uReportType == REPORT_DIGIT)
	{
		for (i = 0; i < length; i++)
		{
			sprintf(szTemp, "%u", m_digest[i]);
			strcat(szReport, szTemp);
		}
	}
	else
	{
		strcpy(szReport, "Error: Unknown report type!");
	}
}
