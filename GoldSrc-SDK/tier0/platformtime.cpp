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

#if defined(_WIN32)
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#endif // #if defined(_WIN32)

#include "platformtime.h"

#ifdef STATIC_TIER0

#ifdef _WIN32
LARGE_INTEGER g_PerformanceFrequency;
LARGE_INTEGER g_MSPerformanceFrequency;
LARGE_INTEGER g_ClockStart;

void InitTime()
{
	if (!g_PerformanceFrequency.QuadPart)
	{
		QueryPerformanceFrequency(&g_PerformanceFrequency);
		g_MSPerformanceFrequency.QuadPart = g_PerformanceFrequency.QuadPart / 1000;
		QueryPerformanceCounter(&g_ClockStart);
	}
}

double Plat_FloatTime()
{
	InitTime();

	LARGE_INTEGER CurrentTime;
	QueryPerformanceCounter(&CurrentTime);

	double fRawSeconds = (double)(CurrentTime.QuadPart - g_ClockStart.QuadPart) / (double)(g_PerformanceFrequency.QuadPart);

	return fRawSeconds;
}

unsigned long Plat_MSTime()
{
	InitTime();

	LARGE_INTEGER CurrentTime;
	QueryPerformanceCounter(&CurrentTime);

	return (unsigned long)((CurrentTime.QuadPart - g_ClockStart.QuadPart) / g_MSPerformanceFrequency.QuadPart);
}

#else // #ifdef _WIN32

double Plat_FloatTime()
{
	struct timeval tp;
	static int secbase = 0;

	gettimeofday(&tp, NULL);

	if (!secbase)
	{
		secbase = tp.tv_sec;
		return (tp.tv_usec / 1000000.0);
	}

	return ((tp.tv_sec - secbase) + tp.tv_usec / 1000000.0);
}

unsigned long Plat_MSTime()
{
	struct timeval tp;
	static int secbase = 0;

	gettimeofday(&tp, NULL);

	if (!secbase)
	{
		secbase = tp.tv_sec;
		return (tp.tv_usec / 1000.0);
	}

	return (unsigned long)((tp.tv_sec - secbase) * 1000.0f + tp.tv_usec / 1000.0);
}
#endif // #ifdef _WIN32

char *Plat_ctime(const time_t *timep, char *buf, size_t bufsize)
{
#ifdef _WIN32
	char *buf_ = buf;
	if (ctime_s(buf, bufsize, timep) == EINVAL)
		return nullptr;
	return buf_;
#else
	return ctime_r(timep, buf);
#endif
}

tm *Plat_gmtime(const time_t *timep, struct tm *result)
{
#ifdef _WIN32
	struct tm *tm_ = result;
	if (gmtime_s(result, timep) == EINVAL)
		return nullptr;
	return tm_;
#else
	return gmtime_r(timep, result);
#endif
}

time_t Plat_timegm(struct tm *timeptr)
{
#ifdef _WIN32
	return _mkgmtime(timeptr);
#else
	return timegm(timeptr);
#endif
}

tm *Plat_localtime(const time_t *timep, struct tm *result)
{
#ifdef _WIN32
	struct tm *tm_ = result;
	if (localtime_s(result, timep) == EINVAL)
		return nullptr;
	return tm_;
#else
	return localtime_r(timep, result);
#endif
}

#endif // STATIC_TIER0
