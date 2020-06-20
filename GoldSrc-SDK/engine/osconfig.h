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

#ifndef _OSCONFIG_H
#define _OSCONFIG_H

#ifdef _WIN32 // WINDOWS
	#pragma warning(disable : 4005)
#endif // _WIN32

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <setjmp.h>
#include <assert.h>

#include <algorithm>
#include <deque>
#include <functional>

#ifdef _WIN32 // WINDOWS
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <wsipx.h> // for support IPX
	#define PSAPI_VERSION 1
	#include <psapi.h>
	#include <nmmintrin.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <io.h>
#else // _WIN32
	#include <arpa/inet.h>
	#include <ctype.h>
	//#include <dirent.h>
	#include <dlfcn.h>
	#include <elf.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <limits.h>
	#include <link.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <pthread.h>
	#include <sys/ioctl.h>
	#include <sys/mman.h>
	#include <sys/socket.h>
	#include <sys/stat.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <sys/sysinfo.h>
	#include <unistd.h>
#endif // _WIN32

#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

#include <smmintrin.h>
#include <xmmintrin.h>

#ifdef _WIN32 // WINDOWS
	// Define __func__ on VS less than 2015
	#if _MSC_VER < 1900
		#define __func__ __FUNCTION__
	#endif

	// We'll not use __func__ on windows because we want 'A::foo' instead of 'foo'
	#define __FUNC__ __FUNCTION__
	#define _CRT_SECURE_NO_WARNINGS
	#define WIN32_LEAN_AND_MEAN

	#ifndef CDECL
	#define CDECL __cdecl
	#endif

	#ifndef FASTCALL
	#define FASTCALL __fastcall
	#endif

	#ifndef STDCALL
	#define STDCALL __stdcall
	#endif

	#ifndef HIDDEN
	#define HIDDEN
	#endif

	#ifndef FORCEINLINE
	#define FORCEINLINE __forceinline
	#endif

	#ifndef NOINLINE
	#define NOINLINE __declspec(noinline)
	#endif

	#ifndef ALIGN16
	#define ALIGN16 __declspec(align(16))
	#endif

	#ifndef NORETURN
	#define NORETURN __declspec(noreturn)
	#endif

	#ifndef NAKED
	#define NAKED __declspec(naked)
	#endif

	#ifndef FORCE_STACK_ALIGN
	#define FORCE_STACK_ALIGN
	#endif

	#define FUNC_TARGET(x)
	#define __builtin_bswap16 _byteswap_ushort
	#define __builtin_bswap32 _byteswap_ulong
	#define __builtin_bswap64 _byteswap_uint64

	//inline bool SOCKET_FIONBIO(SOCKET s, int m) { return (ioctlsocket(s, FIONBIO, (u_long*)&m) == 0); }
	//inline int SOCKET_MSGLEN(SOCKET s, u_long& r) { return ioctlsocket(s, FIONREAD, (u_long*)&r); }
	typedef int socklen_t;
	#define SOCKET_FIONBIO(s, m)		ioctlsocket(s, FIONBIO, (u_long *)&m)
	#define SOCKET_MSGLEN(s, r)			ioctlsocket(s, FIONREAD, (u_long *)&r)
	#define SIN_GET_ADDR(saddr, r)		r = (saddr)->S_un.S_addr
	#define SIN_SET_ADDR(saddr, r)		(saddr)->S_un.S_addr = (r)
	#define SOCKET_CLOSE(s)				closesocket(s)
	#define SOCKET_AGAIN()				(WSAGetLastError() == WSAEWOULDBLOCK)

	inline void *sys_allocmem(unsigned int size) {
		return VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
	}

	inline void sys_freemem(void* ptr, unsigned int size) {
		VirtualFree(ptr, 0, MEM_RELEASE);
	}
#else // _WIN32
	#ifndef PAGESIZE
		#define PAGESIZE 4096
	#endif
	#define ALIGN(addr) (size_t)((size_t)addr & ~(PAGESIZE-1))

	#ifndef ARRAYSIZE
	#define ARRAYSIZE(p) (sizeof(p)/sizeof(p[0]))
	#endif

	#define _MAX_FNAME NAME_MAX
	#define MAX_PATH 260

	typedef void *HWND;

	typedef unsigned long DWORD;
	typedef unsigned short WORD;
	typedef unsigned int UNINT32;

	#define __FUNC__ __func__
	#ifndef FASTCALL
		#define FASTCALL
	#endif

	#ifndef CDECL
	#define CDECL __attribute__ ((cdecl))
	#endif

	#ifndef STDCALL
	#define STDCALL __attribute__ ((stdcall))
	#endif

	#ifndef HIDDEN
	#define HIDDEN __attribute__((visibility("hidden")))
	#endif

	#ifndef FORCEINLINE
	#define FORCEINLINE inline
	#endif

	#ifndef NOINLINE
	#define NOINLINE __attribute__((noinline))
	#endif

	#ifndef ALIGN16
	#define ALIGN16 __attribute__((aligned(16)))
	#endif

	#ifndef NORETURN
	#define NORETURN __attribute__((noreturn))
	#endif

	#ifndef NAKED
	#define NAKED __attribute__((naked))
	#endif

	#ifndef FORCE_STACK_ALIGN
	#define FORCE_STACK_ALIGN __attribute__((force_align_arg_pointer))
	#endif

	#if defined __INTEL_COMPILER
		#define FUNC_TARGET(x)

		#define __builtin_bswap16 _bswap16
		#define __builtin_bswap32 _bswap
		#define __builtin_bswap64 _bswap64
	#else
		#define FUNC_TARGET(x) __attribute__((target(x)))
	#endif // __INTEL_COMPILER

	//inline bool SOCKET_FIONBIO(SOCKET s, int m) { return (ioctl(s, FIONBIO, (int*)&m) == 0); }
	//inline int SOCKET_MSGLEN(SOCKET s, u_long& r) { return ioctl(s, FIONREAD, (int*)&r); }
	typedef int SOCKET;
	#define INVALID_SOCKET			(SOCKET)(~0)
	#define SOCKET_FIONBIO(s, m)	ioctl(s, FIONBIO, (char *)&m)
	#define SOCKET_MSGLEN(s, r)		ioctl(s, FIONREAD, (char *)&r)
	#define SIN_GET_ADDR(saddr, r)	r = (saddr)->s_addr
	#define SIN_SET_ADDR(saddr, r)	(saddr)->s_addr = (r)
	#define SOCKET_CLOSE(s)			close(s)
	#define SOCKET_AGAIN()			(errno == EAGAIN)
	#define SOCKET_ERROR			-1
	#define InetPton(af, src, dst)	inet_pton(af, src, dst)

	inline void *sys_allocmem(unsigned int size) {
		return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	}

	inline void sys_freemem(void* ptr, unsigned int size) {
		munmap(ptr, size);
	}

	#define WSAENOPROTOOPT ENOPROTOOPT

	#ifndef FALSE
	#define FALSE	0
	#endif
	#ifndef TRUE
	#define TRUE	1
	#endif
#endif // _WIN32

#ifdef _WIN32
	static const bool __isWindows = true;
	static const bool __isLinux = false;
#else
	static const bool __isWindows = false;
	static const bool __isLinux = true;
#endif

#define EXT_FUNC FORCE_STACK_ALIGN

// Used to obtain the string name of a variable.
#define nameof_variable(name) template_nameof_variable(name, #name)
template <typename T> const char* template_nameof_variable(const T& /*validate_type*/, const char* name) { return name; }

#endif // _OSCONFIG_H
