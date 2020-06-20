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

#ifdef _INC_TCHAR
	#error ("Must include tier0 type headers before tchar.h")
#endif

#if !defined(_WCHAR_T_DEFINED) && !defined(GNUC)
	typedef unsigned short wchar_t;
	#define _WCHAR_T_DEFINED
#endif

//#if _MSC_VER <= 1916
// char8_t
// char8_t is equivalent to char, and should be used when you really need a char
// (for example, when calling an external function that's declared to take
// chars).
//typedef char char8_t;
//#endif

// uint8_t
// uint8_t is equivalent to byte (but is preferred over byte for clarity).  Use this
// whenever you mean a byte (for example, one byte of a network packet).
typedef unsigned char uint8_t;
typedef unsigned char BYTE;
typedef unsigned char byte;

// wchar
// wchar is a single character of text (currently 16 bits, as all of our text is
// Unicode).  Use this whenever you mean a piece of text (for example, in a string).
typedef wchar_t wchar;
//typedef char wchar;

// __WFILE__
// This is a Unicode version of __FILE__
#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)

#ifdef STEAM
	#ifndef _UNICODE
		#define FORCED_UNICODE
	#endif
	#define _UNICODE
#endif

#if defined(_WIN32)
	#include <tchar.h>
#else
	#define _tcsstr strstr
	#define _tcsicmp stricmp
	#define _tcscmp strcmp
	#define _tcscpy strcpy
	#define _tcsncpy strncpy
	#define _tcsrchr strrchr
	#define _tcslen strlen
	#define _tfopen fopen
	#define _stprintf sprintf
	#define _ftprintf fprintf
	#define _vsntprintf _vsnprintf
	#define _tprintf printf
	#define _sntprintf _snprintf
	#define _T(s) s
#endif // #if defined(_WIN32)

#if defined(_UNICODE)
	typedef wchar tchar;
	#define tstring wstring
	#define __TFILE__ __WFILE__
	#define TCHAR_IS_WCHAR
#else
	typedef char tchar;
	#define tstring string
	#define __TFILE__ __FILE__
	#define TCHAR_IS_CHAR
#endif

#if defined(_WIN32)
	typedef wchar_t uchar16; // 2 byte
	typedef unsigned int uchar32; // 4 byte
#else
	typedef unsigned short uchar16; // 2 byte
	typedef unsigned int uchar32; // 4 byte
	//typedef wchar_t uchar32; // 4 byte but not is unsigned
#endif

#ifdef GNUC
	typedef unsigned short ucs2; // wchar_t is 4 bytes on sane os's, specially define a ucs2 type so we can read out localization files and the list saved as 2 byte wchar (or ucs16 Matt tells me)
#elif defined(_WIN32)
	typedef wchar_t ucs2; // under windows wchar_t is ucs2
#endif

#ifdef FORCED_UNICODE
	#undef _UNICODE
#endif
