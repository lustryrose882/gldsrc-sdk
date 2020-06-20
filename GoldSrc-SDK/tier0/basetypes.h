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

#include <cmath>
#include <cstdlib>

// For backward compatibilty only...
#include "tier0/platform.h"

// stdio.h
#ifndef NULL
#define NULL 0
#endif

template <typename T>
inline T AlignValue(T val, unsigned alignment)
{
	return (T)(((uintptr_t)val + alignment - 1) & ~(alignment - 1));
}

// Pad a number so it lies on an N byte boundary.
// So PAD_NUMBER(0,4) is 0 and PAD_NUMBER(1,4) is 4
#define PAD_NUMBER(number, boundary) \
	(((number) + ((boundary) - 1)) / (boundary)) * (boundary)

#ifndef FALSE
#define FALSE 0
#define TRUE (!FALSE)
#endif

typedef int BOOL;
typedef int qboolean;
typedef unsigned long ULONG;
typedef unsigned char BYTE;
typedef unsigned char byte;
typedef unsigned short word;

#if !defined(_OSCONFIG_H) && !defined(_WIN32)
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned int UNINT32;
#endif

typedef float vec_t;

#if defined(__GNUC__)
	#define fpmin __builtin_fminf
	#define fpmax __builtin_fmaxf
#elif !defined(_X360)
	#define fpmin min
	#define fpmax max
#endif

// look for NANs, infinities, and underflows.
// This assumes the ANSI/IEEE 754-1985 standard
inline unsigned long &FloatBits(vec_t &f)
{
	return *reinterpret_cast<unsigned long *>(&f);
}

inline unsigned long const &FloatBits(vec_t const &f)
{
	return *reinterpret_cast<unsigned long const *>(&f);
}

inline vec_t BitsToFloat(unsigned long i)
{
	return *reinterpret_cast<vec_t *>(&i);
}

inline bool IsFinite(vec_t f)
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}

inline unsigned long FloatAbsBits(vec_t f)
{
	return FloatBits(f) & 0x7FFFFFFF;
}

// Given today's processors, I cannot think of any circumstance
// where bit tricks would be faster than fabs. henryg 8/16/2011
#ifdef _MSC_VER
#ifndef _In_
#define _In_
#endif
extern "C" float fabsf(_In_ float);
#else
#include <math.h>
#endif

inline float FloatMakeNegative(vec_t f)
{
	return -fabsf(f);
}

inline float FloatMakePositive(vec_t f)
{
	return fabsf(f);
}

inline float FloatNegate(vec_t f)
{
	return -f;
}

#define FLOAT32_NAN_BITS	(unsigned long)0x7FC00000	// not a number!
#define FLOAT32_NAN			BitsToFloat(FLOAT32_NAN_BITS)
#define VEC_T_NAN			FLOAT32_NAN

#ifndef UNUSED
#define UNUSED(x)	(x = x)	// for pesky compiler / lint warnings
#endif

struct vrect_t
{
	int      x, y, width, height;
	vrect_t  *pnext;
};

// MaterialRect_t struct - used for DrawDebugText
struct Rect_t
{
	int x, y;
	int width, height;
};

// Interval, used by soundemittersystem + the game
struct interval_t
{
	float start;
	float range;
};

// Declares a type-safe handle type; you can't assign one handle to the next
// 32-bit pointer handles
// Typesafe 8-bit and 16-bit handles
template <class HandleType>
class CBaseIntHandle
{
public:
	inline bool operator==(const CBaseIntHandle &other) { return m_Handle == other.m_Handle; }
	inline bool operator!=(const CBaseIntHandle &other) { return m_Handle != other.m_Handle; }

	// Only the code that doles out these handles should use these functions.
	// Everyone else should treat them as a transparent type.
	inline HandleType GetHandleValue() { return m_Handle; }
	inline void SetHandleValue(HandleType val) { m_Handle = val; }

	typedef HandleType HANDLE_TYPE;

protected:

	HandleType	m_Handle;
};

template <class DummyType>
class CIntHandle16: public CBaseIntHandle<unsigned short>
{
public:
	inline CIntHandle16() {}

	static inline CIntHandle16<DummyType> MakeHandle(HANDLE_TYPE val)
	{
		return CIntHandle16<DummyType>(val);
	}

protected:
	inline CIntHandle16(HANDLE_TYPE val)
	{
		m_Handle = val;
	}
};

template <class DummyType>
class CIntHandle32: public CBaseIntHandle<unsigned long>
{
public:
	inline CIntHandle32() {}

	static inline CIntHandle32<DummyType> MakeHandle(HANDLE_TYPE val)
	{
		return CIntHandle32<DummyType>(val);
	}

protected:
	inline CIntHandle32(HANDLE_TYPE val)
	{
		m_Handle = val;
	}
};

// NOTE: This macro is the same as windows uses; so don't change the guts of it
#define DECLARE_HANDLE_16BIT(name)	typedef CIntHandle16<struct name##__handle *> name;
#define DECLARE_HANDLE_32BIT(name)	typedef CIntHandle32<struct name##__handle *> name;

#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#define FORWARD_DECLARE_HANDLE(name) typedef struct name##__ *name

namespace basetypes
{
	template <class T>
	inline bool IsPowerOf2(T n)
	{
		return n > 0 && (n & (n - 1)) == 0;
	}

	template <class T1, class T2>
	inline T2 ModPowerOf2(T1 a, T2 b)
	{
		return T2(a) & (b - 1);
	}

	template <class T>
	inline T RoundDownToMultipleOf(T n, T m)
	{
		return n - (IsPowerOf2(m) ? ModPowerOf2(n, m) : (n%m));
	}

	template <class T>
	inline T RoundUpToMultipleOf(T n, T m)
	{
		if (!n)
		{
			return m;
		}
		else
		{
			return RoundDownToMultipleOf(n + m - 1, m);
		}
	}
}

// integer bitscan operations
#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
	extern "C" unsigned char _BitScanReverse(unsigned long* Index, unsigned long Mask);
	extern "C" unsigned char _BitScanForward(unsigned long* Index, unsigned long Mask);
	#pragma intrinsic(_BitScanReverse)
	#pragma intrinsic(_BitScanForward)
	#if defined(_M_X64)
		extern "C" unsigned char _BitScanReverse64(unsigned long* Index, unsigned __int64 Mask);
		extern "C" unsigned char _BitScanForward64(unsigned long* Index, unsigned __int64 Mask);
		#pragma intrinsic(_BitScanReverse64)
		#pragma intrinsic(_BitScanForward64)
	#endif
#endif

inline int FindMostSignificantBit(uint32_t n)
{
#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
	unsigned long b;
	if (!_BitScanReverse(&b, n))
		return -1;
	return (int)b;
#elif defined(GNUC)
	if (!n) return -1;
	return 31 - (int) __builtin_clz(n);
#else
	int b = -1;
	for (; n; ++b, n >>= 1) {}
	return b;
#endif
}

inline int FindMostSignificantBit64(uint64_t n)
{
#if defined(_MSC_VER) && defined(_M_X64)
	unsigned long b;
	if (!_BitScanReverse64(&b, n))
		return -1;
	return (int)b;
#elif defined(_MSC_VER) && defined(_M_IX86)
	if (n >> 32)
		return 32 + FindMostSignificantBit(n >> 32);
	return FindMostSignificantBit((uint32_t) n);
#elif defined(GNUC)
	if (!n) return -1;
	return 63 - (int) __builtin_clzll(n);
#else
	int b = -1;
	for (; n; ++b, n >>= 1) {}
	return b;
#endif
}

inline int FindLeastSignificantBit(uint32_t n)
{
#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
	unsigned long b;
	if (!_BitScanForward(&b, n))
		return -1;
	return (int)b;
#elif defined(GNUC)
	if (!n) return -1;
	return __builtin_ctz(n);
#else
	// isolate low bit and call FindMSB
	return FindMostSignificantBit(n & (uint32_t)(-(int32_t)n));
#endif
}

inline int FindLeastSignificantBit64(uint64_t n)
{
#if defined(_MSC_VER) && defined(_M_X64)
	unsigned long b;
	if (!_BitScanForward64(&b, n))
		return -1;
	return (int)b;
#elif defined(_MSC_VER) && defined(_M_IX86)
	if ((uint32_t)n)
		return FindLeastSignificantBit((uint32_t)n);
	if (n >> 32)
		return 32 + FindLeastSignificantBit((uint32_t)(n >> 32));
	return -1;
#elif defined(GNUC)
	if (!n) return -1;
	return __builtin_ctzll(n);
#else
	// isolate low bit and call FindMSB
	return FindMostSignificantBit64(n & (uint64_t)(-(int64_t)n));
#endif
}

#ifdef __cplusplus

#undef clamp
#undef min
#undef max
#undef MIN
#undef MAX

// This is the preferred min operator.
// Using the MIN macro can lead to unexpected side-effects or more expensive code.
template <class T>
static FORCEINLINE T const & min(T const &a, T const &b)
{
	return (a < b) ? a : b;
}

// This is the preferred max operator.
// Using the MAX macro can lead to unexpected side-effects or more expensive code.
template <class T>
static FORCEINLINE T const & max(T const &a, T const &b)
{
	return (a > b) ? a : b;
}

template <class T>
static FORCEINLINE T const & clamp(T const &a, T const &min, T const &max)
{
	return (a > max) ? max : (a < min) ? min : a;
}

template <typename T>
inline T bswap(T s)
{
	switch (sizeof(T))
	{
	case 2: {auto res = __builtin_bswap16(*(uint16_t *)&s); return *(T *)&res; }
	case 4: {auto res = __builtin_bswap32(*(uint32_t *)&s); return *(T *)&res; }
	case 8: {auto res = __builtin_bswap64(*(uint64_t *)&s); return *(T *)&res; }
	default: return s;
	}
}

#else // __cplusplus

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#define clamp(val, min, max) (((val) > (max)) ? (max) : (((val) < (min)) ? (min) : (val)))
#endif // __cplusplus
