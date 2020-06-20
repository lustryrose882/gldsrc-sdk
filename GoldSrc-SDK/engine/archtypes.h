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

#ifndef ARCHTYPES_H
#define ARCHTYPES_H

#ifdef __x86_64__
#define X64BITS
#endif

#if !defined(_STDINT) && !defined(_STDINT_H)
#if defined(_WIN32) && (!defined(__MINGW32__))

typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
typedef __int32 intp_t;					// intp is an integer that can accomodate a pointer
typedef unsigned __int32 uintp_t;		// (ie, sizeof(intp) >= sizeof(int) && sizeof(intp) >= sizeof(void *)

#else // #if defined(_WIN32)
typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
#ifdef X64BITS
typedef long long intp_t;
typedef unsigned long long uintp_t;
#else
typedef int intp_t;
typedef unsigned int uintp_t;
#endif

#endif // #if defined(_WIN32)
#endif // #if !defined(_STDINT) && !defined(_STDINT_H)
#endif // #ifndef ARCHTYPES_H
