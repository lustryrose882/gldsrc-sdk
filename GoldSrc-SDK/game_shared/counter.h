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

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
	#include <windows.h>
	#include <io.h>
	#include <direct.h>
#else
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <fcntl.h>
	#include <unistd.h>
	#ifdef OSX
		#include <limits.h>
	#else
		#include <linux/limits.h>
	#endif
	#include <sys/time.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

class CCounter
{
public:
	CCounter();

	bool Init();
	double GetCurTime();

private:
	int m_iLowShift;
	double m_flPerfCounterFreq;
	double m_flCurrentTime;
	double m_flLastCurrentTime;
};

inline CCounter::CCounter() :
	m_iLowShift(0),
	m_flPerfCounterFreq(0),
	m_flCurrentTime(0),
	m_flLastCurrentTime(0)
{
	Init();
}

inline bool CCounter::Init()
{
#ifdef _WIN32

	LARGE_INTEGER performanceFreq;
	if (!QueryPerformanceFrequency(&performanceFreq))
		return false;

	// get 32 out of the 64 time bits such that we have around
	// 1 microsecond resolution
	unsigned int lowpart, highpart;
	lowpart = (unsigned int)performanceFreq.LowPart;
	highpart = (unsigned int)performanceFreq.HighPart;
	m_iLowShift = 0;

	while (highpart || (lowpart > 2000000.0))
	{
		m_iLowShift++;
		lowpart >>= 1;
		lowpart |= (highpart & 1) << 31;
		highpart >>= 1;
	}

	m_flPerfCounterFreq = 1.0 / (double)lowpart;

#endif // _WIN32

	return true;
}

inline double CCounter::GetCurTime()
{
#ifdef _WIN32

	static int sametimecount;
	static unsigned int oldtime;
	static int first = 1;
	LARGE_INTEGER PerformanceCount;
	unsigned int temp, t2;
	double time;

	QueryPerformanceCounter(&PerformanceCount);
	if (m_iLowShift == 0)
	{
		temp = (unsigned int)PerformanceCount.LowPart;
	}
	else
	{
		temp = ((unsigned int)PerformanceCount.LowPart >> m_iLowShift) |
			((unsigned int)PerformanceCount.HighPart << (32 - m_iLowShift));
	}

	if (first)
	{
		oldtime = temp;
		first = 0;
	}
	else
	{
		// check for turnover or backward time
		if ((temp <= oldtime) && ((oldtime - temp) < 0x10000000))
		{
			// so we can't get stuck
			oldtime = temp;
		}
		else
		{
			t2 = temp - oldtime;

			time = (double)t2 * m_flPerfCounterFreq;
			oldtime = temp;

			m_flCurrentTime += time;

			if (m_flCurrentTime == m_flLastCurrentTime)
			{
				if (++sametimecount > 100000)
				{
					m_flCurrentTime += 1.0;
					sametimecount = 0;
				}
			}
			else
			{
				sametimecount = 0;
			}

			m_flLastCurrentTime = m_flCurrentTime;
		}
	}

	return m_flCurrentTime;

#else // _WIN32

	struct timeval tp;
	static int secbase = 0;

	gettimeofday(&tp, NULL);

	if (!secbase)
	{
		secbase = tp.tv_sec;
		return (tp.tv_usec / 1000000.0);
	}

	return ((tp.tv_sec - secbase) + tp.tv_usec / 1000000.0);

#endif // _WIN32
}
