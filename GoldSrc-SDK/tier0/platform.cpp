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
#define _WIN32_WINNT 0x0403
#include <windows.h>
#endif // #if defined(_WIN32)

#include "platform.h"
#include "dbg.h"

#if defined(STATIC_TIER0)
bool Plat_IsInDebugSession()
{
#if defined( _WIN32 ) && !defined( _X360 )
	return (IsDebuggerPresent() != 0);
#elif defined( _WIN32 ) && defined( _X360 )
	return (XBX_IsDebuggerPresent() != 0);
#else
	return false;
#endif
}

void Plat_OutputDebugStringRaw(const char *psz)
{
#ifdef _WIN32
	OutputDebugString(psz);
#endif // #ifdef _WIN32
}

void Plat_OutputDebugString(const char *psz)
{
#ifdef _WIN32
	static char buf[4096];
	int len = _snprintf(buf, sizeof(buf) - 1, "%s", psz);
	Assert(len > 0);

	OutputDebugString(buf);
#endif // #ifdef _WIN32
}

bool Is64BitOS()
{
#ifdef _WIN32
	static bool bInit = false;
	static BOOL bIsWow64 = FALSE;

	if (bInit)
	{
		return bIsWow64 == TRUE;
	}

	bInit = true;

	using LPFN_ISWOW64PROCESS = BOOL (WINAPI *)(HANDLE, PBOOL);
	static LPFN_ISWOW64PROCESS fnIsWow64Process = NULL;

	if (!fnIsWow64Process)
	{
		fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");
	}

	// IsWow64Process is not available on all supported versions of Windows.
	// Use GetModuleHandle to get a handle to the DLL that contains the function
	// and GetProcAddress to get a pointer to the function if available.
	if (fnIsWow64Process && fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
	{
		if (bIsWow64)
		{
			return true;
		}
	}

	return false;
#elif defined(_WIN64)
	return true;
#else
	return false;
#endif // #ifdef _WIN32
}

#endif // #if defined(STATIC_TIER0)

void Plat_DebugString(const char *psz)
{
	Plat_OutputDebugString(psz);
}

#ifdef _WIN32
const tchar *Plat_GetCommandLine()
{
#ifdef TCHAR_IS_WCHAR
	return GetCommandLineW();
#else
	return GetCommandLine();
#endif
}

const char *Plat_GetCommandLineA()
{
	return GetCommandLineA();
}

#endif // _WIN32
