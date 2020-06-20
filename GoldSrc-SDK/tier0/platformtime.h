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

#include <time.h>
#include "tier0/platform.h"

#if defined(_WIN32) || defined(_WIN64)
#include <intrin.h>
#endif // #if defined(_WIN32)

#ifdef STATIC_TIER0
#define STATIC_PLATFORMTIME
#endif

#ifndef STATIC_PLATFORMTIME

#ifdef TIER0_DLL_EXPORT
#define PLATFORMTIME_INTERFACE	DLL_EXPORT
#else
#define PLATFORMTIME_INTERFACE	DLL_IMPORT
#endif

#else
// STATIC BUILD
#define PLATFORMTIME_INTERFACE	extern "C"
#endif

PLATFORMTIME_INTERFACE time_t			Plat_RelativeTicks();									// Returns time in raw ticks since an arbitrary start point.
PLATFORMTIME_INTERFACE time_t			Plat_RelativeTickFrequency();
PLATFORMTIME_INTERFACE double			Plat_FloatTime();										// Returns time in seconds since the module was loaded
PLATFORMTIME_INTERFACE unsigned long	Plat_MSTime();											// Time in milliseconds
PLATFORMTIME_INTERFACE char *			Plat_asctime(const struct tm *tm, char *buf);
PLATFORMTIME_INTERFACE char *			Plat_ctime(const time_t *timep, char *buf, size_t bufsize);
PLATFORMTIME_INTERFACE struct tm *		Plat_gmtime(const time_t *timep, struct tm *result);
PLATFORMTIME_INTERFACE time_t			Plat_timegm(struct tm *timeptr);
PLATFORMTIME_INTERFACE struct tm *		Plat_localtime(const time_t *timep, struct tm *result);

#if !defined(_HW)
// b/w compatibility
#define Sys_FloatTime Plat_FloatTime
#endif

inline uint64_t Plat_Rdtsc()
{
#if defined(_X360)
	return (uint64_t)__mftb32();
#elif defined(_WIN64)
	return (uint64_t)__rdtsc();
#elif defined(_WIN32)
	#if defined(_MSC_VER) && (_MSC_VER >= 1400)
		return (uint64_t)__rdtsc();
	#else
		__asm rdtsc;
		__asm ret;
	#endif // #if defined(_MSC_VER) && (_MSC_VER >= 1400)
#elif defined(__i386__)
	uint64_t val;
	__asm__ __volatile__("rdtsc" : "=A" (val));
	return val;
#elif defined(__x86_64__)
	uint32_t lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return (((uint64_t)hi) << 32) | lo;
#else
	#error "Not implemented Plat_Rdtsc for this target platform"
#endif
}
