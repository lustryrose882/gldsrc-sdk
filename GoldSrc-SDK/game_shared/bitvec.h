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

class CBitVecAccessor
{
public:
	CBitVecAccessor(uint32_t *pDWords, int iBit);

	void operator=(int val);
	operator uint32_t();

private:
	uint32_t *m_pDWords;
	int m_iBit;
};

// CBitVec allows you to store a list of bits and do operations on them like they were
// an atomic type
template <int NUM_BITS>
class CBitVec
{
public:
	CBitVec();

	// Set all values to the specified value (0 or 1..)
	void Init(int val = 0);

	// Access the bits like an array.
	CBitVecAccessor	operator[](int i);

	// Operations on other bit vectors.
	CBitVec &operator=(CBitVec<NUM_BITS> const &other);
	bool operator==(CBitVec<NUM_BITS> const &other);
	bool operator!=(CBitVec<NUM_BITS> const &other);

	// Get underlying dword representations of the bits.
	int GetNumDWords() { return NUM_DWORDS; }
	uint32_t GetDWord(int i);
	void SetDWord(int i, uint32_t val);
	int GetNumBits();

private:
	enum { NUM_DWORDS = NUM_BITS / 32 + !!(NUM_BITS & 31) };

	unsigned int m_DWords[NUM_DWORDS];
};

inline CBitVecAccessor::CBitVecAccessor(uint32_t *pDWords, int iBit)
{
	m_pDWords = pDWords;
	m_iBit = iBit;
}

inline void CBitVecAccessor::operator=(int val)
{
	if (val)
		m_pDWords[m_iBit >> 5] |= (1 << (m_iBit & 31));
	else
		m_pDWords[m_iBit >> 5] &= ~(uint32_t)(1 << (m_iBit & 31));
}

inline CBitVecAccessor::operator uint32_t()
{
	return m_pDWords[m_iBit >> 5] & (1 << (m_iBit & 31));
}

template <int NUM_BITS>
inline int CBitVec<NUM_BITS>::GetNumBits()
{
	return NUM_BITS;
}

template <int NUM_BITS>
inline CBitVec<NUM_BITS>::CBitVec()
{
	for (int i = 0; i < NUM_DWORDS; ++i)
		m_DWords[i] = 0;
}

template <int NUM_BITS>
inline void CBitVec<NUM_BITS>::Init(int val)
{
	for (int i = 0; i < GetNumBits(); ++i)
	{
		(*this)[i] = val;
	}
}

template <int NUM_BITS>
inline CBitVec<NUM_BITS> &CBitVec<NUM_BITS>::operator=(CBitVec<NUM_BITS> const &other)
{
	Q_memcpy(m_DWords, other.m_DWords, sizeof(m_DWords));
	return *this;
}

template <int NUM_BITS>
inline CBitVecAccessor CBitVec<NUM_BITS>::operator[](int i)
{
	assert(i >= 0 && i < GetNumBits());
	return CBitVecAccessor(m_DWords, i);
}

template <int NUM_BITS>
inline bool CBitVec<NUM_BITS>::operator==(CBitVec<NUM_BITS> const &other)
{
	for (int i = 0; i < NUM_DWORDS; ++i)
	{
		if (m_DWords[i] != other.m_DWords[i])
			return false;
	}

	return true;
}

template <int NUM_BITS>
inline bool CBitVec<NUM_BITS>::operator!=(CBitVec<NUM_BITS> const &other)
{
	return !(*this == other);
}

template <int NUM_BITS>
inline uint32_t CBitVec<NUM_BITS>::GetDWord(int i)
{
	assert(i >= 0 && i < NUM_DWORDS);
	return m_DWords[i];
}

template <int NUM_BITS>
inline void CBitVec<NUM_BITS>::SetDWord(int i, uint32_t val)
{
	assert(i >= 0 && i < NUM_DWORDS);
	m_DWords[i] = val;
}

// Support functions
#define LOG2_BITS_PER_INT	5
#define BITS_PER_INT		32

#if _WIN32
#include <intrin.h>
#pragma intrinsic(_BitScanForward)
#endif

inline int FirstBitInWord(unsigned int elem, int offset)
{
#if _WIN32
	if (!elem)
		return -1;

	unsigned long out;
	_BitScanForward(&out, elem);
	return out + offset;

#else
	static unsigned firstBitLUT[256] =
	{
		0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5, 0, 1, 0, 2, 0, 1, 0,
		3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
		4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0,
		3, 0, 1, 0, 2, 0, 1, 0, 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
		5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 6, 0, 1, 0, 2, 0, 1, 0,
		3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
		4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
	};

	unsigned elemByte;

	elemByte = (elem & 0xFF);
	if (elemByte)
		return offset + firstBitLUT[elemByte];

	elem >>= 8;
	offset += 8;
	elemByte = (elem & 0xFF);
	if (elemByte)
		return offset + firstBitLUT[elemByte];

	elem >>= 8;
	offset += 8;
	elemByte = (elem & 0xFF);
	if (elemByte)
		return offset + firstBitLUT[elemByte];

	elem >>= 8;
	offset += 8;
	elemByte = (elem & 0xFF);
	if (elemByte)
		return offset + firstBitLUT[elemByte];

	return -1;
#endif
}

inline unsigned GetEndMask(int numBits)
{
	static unsigned bitStringEndMasks[] =
	{
		0xffffffff,
		0x00000001,
		0x00000003,
		0x00000007,
		0x0000000f,
		0x0000001f,
		0x0000003f,
		0x0000007f,
		0x000000ff,
		0x000001ff,
		0x000003ff,
		0x000007ff,
		0x00000fff,
		0x00001fff,
		0x00003fff,
		0x00007fff,
		0x0000ffff,
		0x0001ffff,
		0x0003ffff,
		0x0007ffff,
		0x000fffff,
		0x001fffff,
		0x003fffff,
		0x007fffff,
		0x00ffffff,
		0x01ffffff,
		0x03ffffff,
		0x07ffffff,
		0x0fffffff,
		0x1fffffff,
		0x3fffffff,
		0x7fffffff,
	};

	return bitStringEndMasks[numBits % BITS_PER_INT];
}

inline int GetBitForBitnum(int bitNum)
{
	static int bitsForBitnum[] =
	{
		(1 << 0),
		(1 << 1),
		(1 << 2),
		(1 << 3),
		(1 << 4),
		(1 << 5),
		(1 << 6),
		(1 << 7),
		(1 << 8),
		(1 << 9),
		(1 << 10),
		(1 << 11),
		(1 << 12),
		(1 << 13),
		(1 << 14),
		(1 << 15),
		(1 << 16),
		(1 << 17),
		(1 << 18),
		(1 << 19),
		(1 << 20),
		(1 << 21),
		(1 << 22),
		(1 << 23),
		(1 << 24),
		(1 << 25),
		(1 << 26),
		(1 << 27),
		(1 << 28),
		(1 << 29),
		(1 << 30),
		(1 << 31),
	};

	return bitsForBitnum[(bitNum) & (BITS_PER_INT - 1)];
}


inline int GetBitForBitnumByte(int bitNum)
{
	static int bitsForBitnum[] =
	{
		(1 << 0),
		(1 << 1),
		(1 << 2),
		(1 << 3),
		(1 << 4),
		(1 << 5),
		(1 << 6),
		(1 << 7),
	};

	return bitsForBitnum[bitNum & 7];
}

inline int CalcNumIntsForBits(int numBits)	{ return (numBits + (BITS_PER_INT - 1)) / BITS_PER_INT; }
