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

// Digest lengths for SHA-1/224/256/384/512
const uint32_t SHA1_DIGESTC_LENGTH = 20;
const uint32_t SHA1_DIGESTC_STRING_LENGTH	= (SHA1_DIGESTC_LENGTH   * 2 + 1);

const uint32_t SHA224_DIGESTC_LENGTH = 28;
const uint32_t SHA224_DIGESTC_STRING_LENGTH	= (SHA224_DIGESTC_LENGTH * 2 + 1);

const uint32_t SHA256_DIGESTC_LENGTH = 32;
const uint32_t SHA256_DIGESTC_STRING_LENGTH	= (SHA256_DIGESTC_LENGTH * 2 + 1);

const uint32_t SHA384_DIGESTC_LENGTH = 48;
const uint32_t SHA384_DIGESTC_STRING_LENGTH	= (SHA384_DIGESTC_LENGTH * 2 + 1);

const uint32_t SHA512_DIGESTC_LENGTH = 64;
const uint32_t SHA512_DIGESTC_STRING_LENGTH	= (SHA512_DIGESTC_LENGTH * 2 + 1);// SHA512_DIGESTC_LENGTH * 2, plus 1 for terminator

class CSHA2
{
public:
	// Two different formats for ReportHash(...)
	enum
	{
		REPORT_HEX = 0,
		REPORT_DIGIT = 1
	};

	enum SHA_TYPE
	{
		enuSHA_NONE,
		enuSHA1,
		enuSHA160 = enuSHA1,
		enuSHA224,
		enuSHA256,
		enuSHA384,
		enuSHA512,
		enuSHA_LAST // for easier looping during testing
	};

	CSHA2();
	virtual ~CSHA2();

	SHA_TYPE GetEnumType() const { return m_Type; };
	bool IsBigEndian() const { return m_boolIsBigEndian; };

	const char *GetTypeString() const;

	// call these three in order if you want to load chunk-by-chunk...
	void Init(SHA_TYPE type);

	void Update(const uint8_t *data, size_t len); // call as many times as needed
	void End();

	void ReportHash(char *szReport, unsigned char uReportType = REPORT_HEX);
	const char *RawHash(int &length); // NO NULL termination! size stored in 'length'
	const char *RawStringHash();

private:
	SHA_TYPE m_Type;
	bool m_boolEnded, m_boolIsBigEndian;
	char m_chrHexHash[SHA512_DIGESTC_STRING_LENGTH];
	uint8_t m_digest[SHA512_DIGESTC_LENGTH];

	// these are common buffers for maintaining the hash
	struct SHA_CTX
	{
		uint8_t state[sizeof(uint64_t) * 8]; // maximum size
		uint64_t bitcount[2]; // sha1, 224 and 256 only use the first entry
		uint8_t buffer[128];
	} ctx;

	// INTERNAL FUNCTION PROTOTYPES
	void SHA256_Internal_Last(bool isSha1 = false);
	void SHA512_Internal_Last();

	void SHA1_Internal_Transform(const uint32_t *data);
	void SHA256_Internal_Transform(const uint32_t *data);
	void SHA512_Internal_Transform(const uint64_t *);

	void SHA32bit_Update(const uint8_t *data, size_t len, bool isSha1 = false);
	void SHA64bit_Update(const uint8_t *data, size_t len);

	// Macro replacements
	inline void MEMSET_BZERO(void *p, size_t l) { memset(p, 0, l); };
	inline void MEMCPY_BCOPY(void *d, const void *s, size_t l) { memcpy(d, s, l); };

	// For incrementally adding the unsigned 64-bit integer n to the
	// unsigned 128-bit integer (represented using a two-element array of 64-bit words)
	inline void ADDINC128(uint64_t *w, uint32_t n)
	{
		w[0] += (uint64_t)(n);
		if (w[0] < (n))
			w[1]++;
	}

	// Shift-right (used in SHA-256, SHA-384, and SHA-512)
	inline uint32_t SHR(uint32_t b, uint32_t x) { return (x >> b); };
	inline uint64_t SHR(uint64_t b, uint64_t x) { return (x >> b); };

	// 32-bit Rotate-right (used in SHA-256)
	inline uint32_t ROTR32(uint32_t b, uint32_t x) { return rotr(x, b); };

	// 64-bit Rotate-right (used in SHA-384 and SHA-512)
	inline uint64_t ROTR64(uint64_t b, uint64_t x) { return rotr64(x, b); };

	// 32-bit Rotate-left (used in SHA-1)
	inline uint32_t ROTL32(uint32_t b, uint32_t x) { return rotl(x, b); };

	// Two logical functions used in SHA-1, SHA-254, SHA-256, SHA-384, and SHA-512
	inline uint32_t Ch(uint32_t x, uint32_t y, uint32_t z)  { return ((x & y) ^ ((~x) & z)); };
	inline uint64_t Ch(uint64_t x, uint64_t y, uint64_t z)  { return ((x & y) ^ ((~x) & z)); };
	inline uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) { return ((x & y) ^ (x & z) ^ (y & z)); };
	inline uint64_t Maj(uint64_t x, uint64_t y, uint64_t z) { return ((x & y) ^ (x & z) ^ (y & z)); };

	// Function used in SHA-1
	inline uint32_t Parity(uint32_t x, uint32_t y, uint32_t z) { return (x ^ y ^ z); };

	// Four logical functions used in SHA-256
	inline uint32_t Sigma0_256(uint32_t x) { return (ROTR32(2, x) ^ ROTR32(13, x) ^ ROTR32(22, x));};
	inline uint32_t Sigma1_256(uint32_t x) { return (ROTR32(6, x) ^ ROTR32(11, x) ^ ROTR32(25, x));};
	inline uint32_t sigma0_256(uint32_t x) { return (ROTR32(7, x) ^ ROTR32(18, x) ^ SHR(   3 , x));};
	inline uint32_t sigma1_256(uint32_t x) { return (ROTR32(17,x) ^ ROTR32(19, x) ^ SHR(   10, x));};

	// Four of six logical functions used in SHA-384 and SHA-512:
	inline uint64_t Sigma0_512(uint64_t x) { return (ROTR64(28, x) ^ ROTR64(34, x) ^ ROTR64(39, x));};
	inline uint64_t Sigma1_512(uint64_t x) { return (ROTR64(14, x) ^ ROTR64(18, x) ^ ROTR64(41, x));};
	inline uint64_t sigma0_512(uint64_t x) { return (ROTR64( 1, x) ^ ROTR64( 8, x) ^ SHR(    7, x));};
	inline uint64_t sigma1_512(uint64_t x) { return (ROTR64(19, x) ^ ROTR64(61, x) ^ SHR(    6, x));};

	inline void REVERSE32(uint32_t w, uint32_t &x) { x = bswap(w); };
	inline void REVERSE64(uint64_t w, uint64_t &x) { x = bswap(w); };
};
