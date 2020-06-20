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

#ifndef _WIN32
#include <string.h>
#include <wchar.h>
#endif

// Simple utility function to allocate memory and duplicate a string
inline char *CloneString(const char *str)
{
	if (!str)
	{
		char *cloneStr = new char[1];
		cloneStr[0] = '\0';
		return cloneStr;
	}

	char *cloneStr = new char [strlen(str) + 1];
	strcpy(cloneStr, str);
	return cloneStr;
}

// Simple utility function to allocate memory and duplicate a wide string
inline wchar_t *CloneWString(const wchar_t *str)
{
	if (!str)
	{
		wchar_t *cloneStr = new wchar_t[1];
		cloneStr[0] = L'\0';
		return cloneStr;
	}

	wchar_t *cloneStr = new wchar_t [wcslen(str) + 1];
	wcscpy(cloneStr, str);
	return cloneStr;
}
