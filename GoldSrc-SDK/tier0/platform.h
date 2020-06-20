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

#ifdef _LINUX
	// need this for _alloca
	#include <alloca.h>

	#include <errno.h>

	// Net headers
	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <netdb.h>
	#include <limits.h>
	#include <sys/stat.h>

#endif // _LINUX

#include <malloc.h> // need this for _alloca
#include <string.h> // need this for memset
#include <algorithm>

#include "wchartypes.h"

#if defined(OSX) || defined(_LINUX)
	#include <stdarg.h>
#endif

#if !defined(COMPILER_GCC) && (defined(__GCC__) || defined(__GNUC__))
	#define COMPILER_GCC 1
#endif

#if !defined(COMPILER_CLANG) && defined(__clang__)
	#define COMPILER_CLANG 1
#endif

#ifdef _MSC_VER
	#define COMPILER_MSVC32 1
	#if defined(_M_X64)
		#define COMPILER_MSVC64 1
	#endif
#endif

#if (defined(LINUX) || defined(OSX) || defined(ANDROID)) && !defined(POSIX)
	#define POSIX
#endif

#if defined(_WIN32) && !defined(WINDED)
	#if defined(_M_IX86)
		#define __i386__	1
	#elif defined(_M_X64)
		#define __x86_64__	1
	#endif
#endif

#if (defined(__i386__) || defined(__x86_64__) || defined(__arm__) || defined(__arm64__) || defined(__aarch64__) || defined(_XBOX)) && !defined(VALVE_LITTLE_ENDIAN)
#define VALVE_LITTLE_ENDIAN 1
#endif

#if (defined(_SGI_SOURCE) || defined(_PS3)) && !defined(VALVE_BIG_ENDIAN)
#define	VALVE_BIG_ENDIAN 1
#endif

#if defined(VALVE_LITTLE_ENDIAN) == defined(VALVE_BIG_ENDIAN)
	#error "Cannot determine endianness of platform!"
#endif

// Detect C++11 support for "rvalue references" / "move semantics" / other C++11 (and up) stuff
#if defined(_MSC_VER)
	#if _MSC_VER >= 1600
		#define VALVE_RVALUE_REFS 1
	#endif
	#if _MSC_VER >= 1800
		#define VALVE_INITIALIZER_LIST_SUPPORT 1
		#define VALVE_EXPLICIT_CONVERSION_OP 1
	#endif
#elif defined(__clang__)
	#if __has_extension(cxx_rvalue_references)
		#define VALVE_RVALUE_REFS 1
	#endif
	#if __has_feature(cxx_generalized_initializers)
		#define VALVE_INITIALIZER_LIST_SUPPORT 1
	#endif
	#if __has_feature(cxx_explicit_conversions)
		#define VALVE_EXPLICIT_CONVERSION_OP 1
	#endif
#elif defined(__GNUC__)
	#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
		#if defined(__GXX_EXPERIMENTAL_CXX0X__)
			#define VALVE_RVALUE_REFS 1
			#define VALVE_INITIALIZER_LIST_SUPPORT 1
			#define VALVE_EXPLICIT_CONVERSION_OP 1
		#endif
	#endif
#endif

#ifdef _DEBUG
#define IsRelease() false
#define IsDebug() true
#else
#define IsRelease() true
#define IsDebug() false
#endif

#ifdef _WIN32
	#define IsLinux() false
	#define IsOSX() false
	#define IsPosix() false
	#define PLATFORM_WINDOWS 1 // Windows PC or Xbox 360
	#ifndef _X360
		#define IsWindows() true
		#define IsPC() true
		#define IsConsole() false
		#define IsX360() false
		#define IsPS3() false
		#define IS_WINDOWS_PC
		#define PLATFORM_WINDOWS_PC 1 // Windows PC
		#ifdef _WIN64
			#define IsPlatformWindowsPC64() true
			#define IsPlatformWindowsPC32() false
			#define PLATFORM_WINDOWS_PC64 1
		#else
			#define IsPlatformWindowsPC64() false
			#define IsPlatformWindowsPC32() true
			#define PLATFORM_WINDOWS_PC32 1
		#endif
	#else
		#define PLATFORM_X360 1
		#ifndef _CONSOLE
			#define _CONSOLE
		#endif
		#define IsWindows() false
		#define IsPC() false
		#define IsConsole() true
		#define IsX360() true
		#define IsPS3() false
	#endif
	// Adding IsPlatformOpenGL() to help fix a bunch of code that was using IsPosix() to infer if the DX->GL translation layer was being used.
	#if defined(DX_TO_GL_ABSTRACTION)
		#define IsPlatformOpenGL() true
	#else
		#define IsPlatformOpenGL() false
	#endif

	using time64_t = __time64_t;

#elif defined(POSIX)
	#define IsPC() true
	#define IsWindows() false
	#define IsConsole() false
	#define IsX360() false
	#define IsPS3() false
	#if defined(LINUX)
		#define IsLinux() true
	#else
		#define IsLinux() false
	#endif

	#if defined(OSX)
		#define IsOSX() true
	#else
		#define IsOSX() false
	#endif

	#define IsPosix() true
	#define IsPlatformOpenGL() true

	using time64_t = int64_t;
#else
	#error Undefined platform
#endif

#if defined(__x86_64__) || defined(__arm64__) || defined(__aarch64__) || defined(_WIN64)
	#define X64BITS
	#define PLATFORM_64BITS
#endif // __x86_64__

#if defined(_WIN32)
	#ifdef X64BITS
		typedef __int64 intp_t;					// intp_t is an integer that can accomodate a pointer
		typedef unsigned __int64 uintp_t;		// (ie, sizeof(intp_t) >= sizeof(int) && sizeof(intp_t) >= sizeof(void *)
	#else
		typedef __int32 intp_t;
		typedef unsigned __int32 uintp_t;
	#endif
#else // _WIN32
	#ifdef X64BITS
		typedef long long intp_t;
		typedef unsigned long long uintp_t;
	#else
		typedef int intp_t;
		typedef unsigned int uintp_t;
	#endif
#endif // else _WIN32

typedef float  float32;
typedef double float64;

// MSVC CRT uses 0x7fff while gcc uses MAX_INT, leading to mismatches between platforms
// As a result, we pick the least common denominator here. This should be used anywhere
// you might typically want to use RAND_MAX
#define VALVE_RAND_MAX 0x7fff

#define MAX_FILEPATH 512

// Defines MAX_PATH
#ifndef MAX_PATH
	#define MAX_PATH 260
#endif

#ifdef _WIN32
	#define MAX_UNICODE_PATH 32767
#else
	#define MAX_UNICODE_PATH MAX_PATH
#endif

#define MAX_UNICODE_PATH_IN_UTF8 MAX_UNICODE_PATH * 4

// Need macro for constant expression
#define ALIGN_VALUE(val, alignment) ((val + alignment - 1) & ~(alignment - 1))

// Used to step into the debugger
#if defined(__GNUC__) && !defined(__clang__)
	#define DebuggerBreak() __asm__ __volatile__("int3;")
#else
	#define DebuggerBreak() __asm { int 3 }
#endif

#define	DebuggerBreakIfDebugging() if (!Plat_IsInDebugSession()) ; else DebuggerBreak()

#define DebuggerSegFault()\
		int *null = 0;\
		*null = 0;

// Decls for aligning data
#ifdef _WIN32
	#define DECL_ALIGN(x) __declspec(align(x))

#elif GNUC
	#define DECL_ALIGN(x) __attribute__((aligned(x)))
#else
	#define DECL_ALIGN(x) /* */
#endif

#ifdef _MSC_VER
	#define PACKED

	// MSVC has the align at the start of the struct
	#define ALIGN4 DECL_ALIGN(4)
	#define ALIGN8 DECL_ALIGN(8)
	#define ALIGN16 DECL_ALIGN(16)
	#define ALIGN32 DECL_ALIGN(32)
	#define ALIGN128 DECL_ALIGN(128)

	#define ALIGN4_POST
	#define ALIGN8_POST
	#define ALIGN16_POST
	#define ALIGN32_POST
	#define ALIGN128_POST
#elif defined(_LINUX) || defined(GNUC)
	#define PACKED __attribute__((packed))

	// gnuc has the align decoration at the end
	#define ALIGN4
	#define ALIGN8
	#define ALIGN16
	#define ALIGN32
	#define ALIGN128

	#define ALIGN4_POST DECL_ALIGN(4)
	#define ALIGN8_POST DECL_ALIGN(8)
	#define ALIGN16_POST DECL_ALIGN(16)
	#define ALIGN32_POST DECL_ALIGN(32)
	#define ALIGN128_POST DECL_ALIGN(128)
#else
	#error "Unsupported Platform."
#endif

// C functions for external declarations that call the appropriate C++ methods
#ifndef EXPORT
	#ifdef _WIN32
		#define EXPORT __declspec(dllexport)
	#else
		#define EXPORT /**/
	#endif
#endif

// Macro to assist in asserting constant invariants during compilation
//
// If available use static_assert instead of weird language tricks. This
// leads to much more readable messages when compile time assert constraints
// are violated.
#if !defined(OSX) && (_MSC_VER > 1500 || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
	#define PLAT_COMPILE_TIME_ASSERT(pred) static_assert(pred, "Compile time assert constraint is not true: " #pred)
#else
	#define PLAT_COMPILE_TIME_ASSERT(pred) typedef int UNIQUE_ID[ (pred) ? 1 : -1]
#endif

#define FUNC_INIT_ONCE(func, ...)	\
{									\
static bool onceinit = false;		\
if (!onceinit)						\
{									\
	func(__VA_ARGS__);				\
	onceinit = true;				\
}									\
}									\

#ifdef _WIN32

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

	#define __FUNC__ __FUNCTION__
	#define FORCEINLINE __forceinline
	#define DEPRECATED __declspec(deprecated)

	// Used for dll exporting and importing
	#define DLL_EXPORT extern "C" __declspec(dllexport)
	#define DLL_IMPORT extern "C" __declspec(dllimport)

	// Can't use extern "C" when DLL exporting a class
	#define DLL_CLASS_EXPORT __declspec(dllexport)
	#define DLL_CLASS_IMPORT __declspec(dllimport)

	// Can't use extern "C" when DLL exporting a global
	#define DLL_GLOBAL_EXPORT extern __declspec(dllexport)
	#define DLL_GLOBAL_IMPORT extern __declspec(dllimport)

	#define FUNC_TARGET(x)
	#define __builtin_bswap16 _byteswap_ushort
	#define __builtin_bswap32 _byteswap_ulong
	#define __builtin_bswap64 _byteswap_uint64

	typedef int socklen_t;
	#define SOCKET_FIONBIO(s, m) ioctlsocket(s, FIONBIO, (u_long *)&m)
	#define SOCKET_MSGLEN(s, r) ioctlsocket(s, FIONREAD, (u_long *)&r)
	#define SIN_GET_ADDR(saddr, r) r = (saddr)->S_un.S_addr
	#define SIN_SET_ADDR(saddr, r) (saddr)->S_un.S_addr = (r)
	#define SOCKET_CLOSE(s) closesocket(s)
	#define SOCKET_AGAIN() (WSAGetLastError() == WSAEWOULDBLOCK)

	#define rotl _rotl
	#define rotr _rotr

	#define rotl64 _rotl64
	#define rotr64 _rotr64

	#define PLATFORM_EXT "dll"

#elif defined __linux__

	typedef uintp_t HMODULE;
	typedef void *HANDLE;
	#define __cdecl

	#ifndef CDECL
	#define CDECL __attribute__ ((cdecl))
	#endif

	#ifndef FASTCALL
	#define FASTCALL
	#endif

	#ifndef STDCALL
	#define STDCALL
	#endif

	#ifndef HIDDEN
	#define HIDDEN __attribute__((visibility("hidden")))
	#endif

	#define __FUNC__ __func__
	#define FORCEINLINE inline
	#define DEPRECATED __attribute__((deprecated))

	// Used for dll exporting and importing
	#define DLL_EXPORT extern "C"
	#define DLL_IMPORT extern "C"

	// Can't use extern "C" when DLL exporting a class
	#define DLL_CLASS_EXPORT
	#define DLL_CLASS_IMPORT

	// Can't use extern "C" when DLL exporting a global
	#define DLL_GLOBAL_EXPORT extern
	#define DLL_GLOBAL_IMPORT extern

	#if defined __INTEL_COMPILER
		#define FUNC_TARGET(x)

		#define __builtin_bswap16 _bswap16
		#define __builtin_bswap32 _bswap
		#define __builtin_bswap64 _bswap64
	#else
		#define FUNC_TARGET(x) __attribute__((target(x)))
	#endif // #if defined __INTEL_COMPILER

	typedef int SOCKET;
	#define INVALID_SOCKET (SOCKET)(~0)
	#define SOCKET_FIONBIO(s, m) ioctl(s, FIONBIO, (char *)&m)
	#define SOCKET_MSGLEN(s, r) ioctl(s, FIONREAD, (char *)&r)
	#define SIN_GET_ADDR(saddr, r) r = (saddr)->s_addr
	#define SIN_SET_ADDR(saddr, r) (saddr)->s_addr = (r)
	#define SOCKET_CLOSE(s) close(s)
	#define SOCKET_AGAIN() (errno == EAGAIN)
	#define SOCKET_ERROR -1

	#define SD_RECEIVE SHUT_RD
	#define SD_SEND SHUT_WR
	#define SD_BOTH SHUT_RDWR

	inline int ioctlsocket(int fd, int cmd, unsigned long *argp) { return ioctl(fd, cmd, argp); }
	inline int closesocket(int fd) { return close(fd); }
	inline int WSAGetLastError() { return errno; }

	#define ZeroMemory(dest, size) memset(dest, 0x0, size)

	#undef rotl
	#undef rotr

	inline uint32_t rotl(uint32_t x, int r)
	{
		return (x << r) | (x >> (32 - r));
	}

	inline uint32_t rotr(uint32_t x, int r)
	{
		return (x >> r) | (x << (32 - r));
	}

	inline uint64_t rotl64(uint64_t x, int r)
	{
		return (x << r) | (x >> (64 - r));
	}

	inline uint64_t rotr64(uint64_t x, int r)
	{
		return (x >> r) | (x << (64 - r));
	}

	#define _wtoi(arg) wcstol(arg, NULL, 10)
	#define _wtoi64(arg) wcstoll(arg, NULL, 10)

	#define PLATFORM_EXT "so"

#elif defined(OSX)

	#define PLATFORM_EXT "dylib"

	#error "Uncompleted configuration for OSX Platform."
#else
	#error "Unsupported Platform."
#endif

// Pull in the /analyze code annotations.
#include "annotations.h"
#include "platformtime.h"

// Stack-based allocation related helpers
#if defined(GNUC)
	#define stackalloc(_size)	alloca(ALIGN_VALUE(_size, 16))
#ifdef _LINUX
	#define mallocsize(_p)		(malloc_usable_size(_p))
#elif defined(OSX)
	#define mallocsize(_p)		(malloc_size(_p))
#else
	#error
#endif
#elif defined (_WIN32)
	#define stackalloc(_size)	_alloca(ALIGN_VALUE(_size, 16))
	#define mallocsize(_p)		(_msize(_p))
#endif

#define stackfree(_p) 0

#if defined(_WIN32)
	#define RESTRICT __restrict
	#define RESTRICT_FUNC __declspec(restrict)
	#define FMTFUNCTION(a, b)
	#define NOINLINE __declspec(noinline)

#elif defined(COMPILER_GCC)

	#if defined(__clang__)
		// [will] - clang is very strict about restrict, and we have a bunch of core functions that use the keyword which have issues with it.
		// This seemed to be a cleaner solution for now so we don't have to fill core code with tons of #ifdefs.
		#define RESTRICT
	#else
		#define RESTRICT __restrict__
	#endif

	#define RESTRICT_FUNC
	#define FMTFUNCTION(fmtargnumber, firstvarargnumber) __attribute__((format(printf, fmtargnumber, firstvarargnumber)))
	#define NOINLINE __attribute__((noinline))

#else
	#error "Unsupported Platform."
#endif

#ifdef _WIN32
	// Remove warnings from warning level 4.
	#pragma warning(disable:4514) // warning C4514: 'acosl' : unreferenced inline function has been removed
	#pragma warning(disable:4100) // warning C4100: 'hwnd' : unreferenced formal parameter
	#pragma warning(disable:4127) // warning C4127: conditional expression is constant
	#pragma warning(disable:4512) // warning C4512: 'InFileRIFF' : assignment operator could not be generated
	#pragma warning(disable:4611) // warning C4611: interaction between '_setjmp' and C++ object destruction is non-portable
	#pragma warning(disable:4706) // warning C4706: assignment within conditional expression
	#pragma warning(disable:4710) // warning C4710: function 'x' not inlined
	#pragma warning(disable:4702) // warning C4702: unreachable code
	#pragma warning(disable:4505) // unreferenced local function has been removed
	#pragma warning(disable:4239) // nonstandard extension used : 'argument' ( conversion from class Vector to class Vector& )
	#pragma warning(disable:4097) // typedef-name 'BaseClass' used as synonym for class-name 'CFlexCycler::CBaseFlex'
	#pragma warning(disable:4324) // Padding was added at the end of a structure
	#pragma warning(disable:4244) // type conversion warning.
	#pragma warning(disable:4305) // truncation from 'const double ' to 'float '
	#pragma warning(disable:4786) // Disable warnings about long symbol names

	#if _MSC_VER >= 1300
		#pragma warning(disable:4511) // Disable warnings about private copy constructors
	#endif
#endif

// There is no requirement that a va_list be usable in multiple calls,
// but the Steam code does this.  Linux64 does not support reuse, whereas
// Windows does, so Linux64 breaks on code that was written and working
// on Windows.  Fortunately Linux has va_copy, which provides a simple
// way to let a va_list be used multiple times.  Unfortunately Windows
// does not have va_copy, so here we provide things to hide the difference.
class CReuseVaList
{
public:
	CReuseVaList(va_list List)
	{
#if defined(LINUX) || defined(OSX)
		va_copy(m_ReuseList, List);
#else
		m_ReuseList = List;
#endif
	}

	~CReuseVaList()
	{
#if defined(LINUX) || defined(OSX)
		va_end(m_ReuseList);
#endif
	}

	va_list m_ReuseList;
};

// Methods to invoke the constructor, copy constructor, and destructor
template <class T>
inline void Construct(T *pMemory)
{
	new (pMemory) T;
}

template <class T>
inline void CopyConstruct(T *pMemory, T const &src)
{
	new (pMemory) T(src);
}

template <class T>
inline void Destruct(T *pMemory)
{
	pMemory->~T();

#ifdef _DEBUG
	memset((void *)pMemory, 0xDD, sizeof(T));
#endif
}

// Portability casting
template <typename Tdst, typename Tsrc>
FORCEINLINE Tdst size_cast(Tsrc val)
{
	static_assert(sizeof(Tdst) <= sizeof(uint64_t) && sizeof(Tsrc) <= sizeof(uint64_t), "Okay in my defense there weren't any types larger than 64-bits when this code was written.");

#ifdef _DEBUG
	if (sizeof(Tdst) < sizeof(Tsrc))
	{
		Tdst cmpValDst = (Tdst)val;

		// If this fails, the source value didn't actually fit in the destination value--you'll need to
		// change the return type's size to match the source type in the calling code.
		if (val != (Tsrc)cmpValDst)
		{
			// Can't use assert here, and if this happens when running on a machine internally we should crash
			// in preference to missing the problem ( so not DebuggerBreakIfDebugging() ).
			DebuggerBreak();
		}
	}
#endif

	return (Tdst)val;
}

//
// GET_OUTER()
//
// A platform-independent way for a contained class to get a pointer to its
// owner. If you know a class is exclusively used in the context of some
// "outer" class, this is a much more space efficient way to get at the outer
// class than having the inner class store a pointer to it.
//
//	class COuter
//	{
//		class CInner // Note: this does not need to be a nested class to work
//		{
//			void PrintAddressOfOuter()
//			{
//				printf("Outer is at 0x%x\n", GET_OUTER(COuter, m_Inner));
//			}
//		};
//
//		CInner m_Inner;
//		friend class CInner;
//	};

#define GET_OUTER(OuterType, OuterMember) \
	((OuterType *)((uint8_t *)this - offsetof(OuterType, OuterMember)))

template <typename T>
inline T WordSwapC(T w)
{
	PLAT_COMPILE_TIME_ASSERT(sizeof(T) == sizeof(uint16_t));

	uint16_t temp;
#if defined(_MSC_VER)
	temp = _byteswap_ushort(*(uint16_t *)&w);
#else
	// This translates into a single rotate on x86/x64
	temp = *(uint16_t *)&w;
	temp = (temp << 8) | (temp >> 8);
#endif
	return *((T *)&temp);
}

template <typename T>
inline T DWordSwapC(T dw)
{
	PLAT_COMPILE_TIME_ASSERT(sizeof(T) == sizeof(uint32_t));

	uint32_t temp;
#if defined(_MSC_VER)
	temp = _byteswap_ulong(*(uint32_t *)&dw);
#elif defined(__clang__) || defined(__GNUC__)
	temp = __builtin_bswap32(*(uint32_t *)&dw);
#else
	temp = *((uint32_t *)&dw) >> 24;
	temp |= ((*((uint32_t *)&dw) & 0x00FF0000) >> 8);
	temp |= ((*((uint32_t *)&dw) & 0x0000FF00) << 8);
	temp |= (*((uint32_t *)&dw) << 24;
#endif
	return *((T *)&temp);
}

template <typename T>
inline T QWordSwapC(T dw)
{
	PLAT_COMPILE_TIME_ASSERT(sizeof(dw) == sizeof(uint64_t));
	uint64_t temp;
#if defined(_MSC_VER)
	temp = _byteswap_uint64(*(uint64_t *)&dw);
#elif defined(__clang__) || defined(__GNUC__)
	temp = __builtin_bswap64(*(uint64_t *)&dw);
#else
	temp = (uint64_t)DWordSwapC((uint32_t)((*(uint64_t *)&dw) >> 32));
	temp |= (uint64_t)DWordSwapC((uint32_t)(*(uint64_t *)&dw)) << 32;
#endif
	return *((T *)&temp);
}

#define WordSwap	WordSwapC
#define DWordSwap	DWordSwapC
#define QWordSwap	QWordSwapC

#if defined(VALVE_LITTLE_ENDIAN)

	#define BigInt16(val)		WordSwap(val)
	#define BigWord(val)		WordSwap(val)
	#define BigInt32(val)		DWordSwap(val)
	#define BigDWord(val)		DWordSwap(val)
	#define BigQWord(val)		QWordSwap(val)
	#define BigFloat(val)		DWordSwap(val)
	#define LittleInt16(val)	(val)
	#define LittleWord(val)		(val)
	#define LittleInt32(val)	(val)
	#define LittleDWord(val)	(val)
	#define LittleQWord(val)	(val)

	#define LittleFloat(val)	(val)

#elif defined(VALVE_BIG_ENDIAN)

	#define BigInt16(val)		(val)
	#define BigWord(val)		(val)
	#define BigInt32(val)		(val)
	#define BigDWord(val)		(val)
	#define BigQWord(val)		(val)
	#define BigFloat(val)		(val)
	#define LittleInt16(val)	WordSwap(val)
	#define LittleWord(val)		WordSwap(val)
	#define LittleInt32(val)	DWordSwap(val)
	#define LittleDWord(val)	DWordSwap(val)
	#define LittleQWord(val)	QWordSwap(val)
	#define LittleFloat(val)	DWordSwap(val)

#else

	// @Note (toml 05-02-02): this technique expects the compiler to
	// optimize the expression and eliminate the other path. On any new
	// platform/compiler this should be tested.
	// little endian if true (*(char *)&test == 1)
	inline short BigInt16(int16_t val)			{ int test = 1; return (*(char *)&test == 1) ? WordSwap(val)  : val; }
	inline uint16_t BigWord(uint16_t val)		{ int test = 1; return (*(char *)&test == 1) ? WordSwap(val)  : val; }
	inline int32_t BigInt32(int32_t val)		{ int test = 1; return (*(char *)&test == 1) ? DWordSwap(val) : val; }
	inline uint32_t BigDWord(uint32_t val)		{ int test = 1; return (*(char *)&test == 1) ? DWordSwap(val) : val; }
	inline uint64_t BigQWord(uint64_t val)		{ int test = 1; return (*(char *)&test == 1) ? QWordSwap(val) : val; }
	inline float BigFloat(float val)			{ int test = 1; return (*(char *)&test == 1) ? DWordSwap(val) : val; }
	inline short LittleInt16(int16_t val)		{ int test = 1; return (*(char *)&test == 1) ? val : WordSwap(val); }
	inline uint16_t LittleWord(uint16_t val)	{ int test = 1; return (*(char *)&test == 1) ? val : WordSwap(val); }
	inline long LittleInt32(int32_t val)		{ int test = 1; return (*(char *)&test == 1) ? val : DWordSwap(val); }
	inline uint32_t LittleDWord(uint32_t val)	{ int test = 1; return (*(char *)&test == 1) ? val : DWordSwap(val); }
	inline uint64_t LittleQWord(uint64_t val)	{ int test = 1; return (*(char *)&test == 1) ? val : QWordSwap(val); }
	inline float LittleFloat(float val)			{ int test = 1; return (*(char *)&test == 1) ? val : DWordSwap(val); }

#endif

#ifdef VALVE_BIG_ENDIAN
	#if defined(_PS3)
		inline uint32_t LoadLittleDWord(uint32_t *base, unsigned int dwordIndex)
		{
			return __lwbrx(base + dwordIndex);
		}

		inline void StoreLittleDWord(uint32_t *base, unsigned int dwordIndex, uint32_t dword)
		{
			__stwbrx(base + dwordIndex, dword);
		}
		inline uint64_t LoadLittleInt64(uint64_t *base, unsigned int nWordIndex)
		{
			return __ldbrx(base + nWordIndex);
		}

		inline void StoreLittleInt64(uint64_t *base, unsigned int nWordIndex, uint64_t nWord)
		{
			__stdbrx(base + nWordIndex, nWord);
		}
	#else
		inline uint32_t LoadLittleDWord(uint32_t *base, unsigned int dwordIndex)
		{
			return __loadwordbytereverse(dwordIndex<<2, base);
		}

		inline void StoreLittleDWord(uint32_t *base, unsigned int dwordIndex, uint32_t dword)
		{
			__storewordbytereverse(dword, dwordIndex<<2, base);
		}
		inline uint64_t LoadLittleInt64(uint64_t *base, unsigned int nWordIndex)
		{
			return __loaddoublewordbytereverse(nWordIndex<<2, base);
		}

		inline void StoreLittleInt64(uint64_t *base, unsigned int nWordIndex, uint64_t nWord)
		{
			__storedoublewordbytereverse(nWord, nWordIndex<<2, base);
		}
	#endif
#else
	inline uint32_t LoadLittleDWord(uint32_t *base, unsigned int dwordIndex)
	{
		return LittleDWord(base[dwordIndex]);
	}

	inline void StoreLittleDWord(uint32_t *base, unsigned int dwordIndex, uint32_t dword)
	{
		base[dwordIndex] = LittleDWord(dword);
	}
#endif

class indestructible_base
{
	~indestructible_base();
};

template <class T>
class CNoAutoDestruct: indestructible_base
{
public:
	static T *Instance()
	{
		static T s_Instance;
		return &s_Instance;
	}

protected:
	explicit CNoAutoDestruct();								// Prevent construction
	CNoAutoDestruct(const CNoAutoDestruct &);				// Prevent construction by copying
	CNoAutoDestruct &operator=(const CNoAutoDestruct &);	// Prevent assignment
	~CNoAutoDestruct();										// Prevent unwanted destruction
};

#define PLATFORM_CXX_INTERFACE

// DLL export for platform utilities
#ifndef STATIC_TIER0

	#ifdef TIER0_DLL_EXPORT
		#define PLATFORM_INTERFACE	DLL_EXPORT
		#define PLATFORM_OVERLOAD	DLL_GLOBAL_EXPORT
		#define PLATFORM_CLASS		DLL_CLASS_EXPORT
	#else
		#define PLATFORM_INTERFACE	DLL_IMPORT
		#define PLATFORM_OVERLOAD	DLL_GLOBAL_IMPORT
		#define PLATFORM_CLASS		DLL_CLASS_IMPORT
	#endif

#else	// BUILD_AS_DLL

#define PLATFORM_INTERFACE	extern
#define PLATFORM_OVERLOAD
#define PLATFORM_CLASS

#endif	// BUILD_AS_DLL

// Processor Information:
#if defined(TIER0_S)
// sizeof: win(40), lin(36)
struct CPUInformation
{
	int	 m_Size;			// Size of this structure, for forward compatability.
	bool m_bRDTSC : 1,		// Is RDTSC supported?
		 m_bCMOV  : 1,		// Is CMOV supported?
		 m_bFCMOV : 1,		// Is FCMOV supported?
		 m_bSSE	  : 1,		// Is SSE supported?
		 m_bSSE2  : 1,		// Is SSE2 Supported?
		 m_bSSE3  : 1,		// Is SSE3 Supported?
		 m_bSSSE3 : 1,		// Is SSSE3 Supported?
		 m_bSSE41 : 1,		// Is SSE41 Supported?
		 m_bSSE42 : 1,		// Is SSE42 Supported?
		 m_bSSE4a : 1,		// Is SSE4a Supported?
		 m_b3DNow : 1,		// Is 3DNow! Supported?
		 m_bMMX   : 1,		// Is MMX supported?
		 m_bHT	  : 1,		// Is HyperThreading supported?
		 m_bAES   : 1,		// Is AES supported?
		 m_bAVX   : 1,		// Is AVX supported?
		 m_bCMPXCHG16B : 1,	// Is CMPXCHG16B supported?
		 m_bLAHFSAHF : 1,	// Is LAHF/SAHFsupported?
		 m_bPrefetchW : 1;	// Is PrefetchWsupported?

	uint8_t m_nLogicalProcessors;		// Number op logical processors.
	uint8_t m_nPhysicalProcessors;		// Number of physical processors

	int64_t m_Speed;					// In cycles per second.

	const char *m_szProcessorID;		// Processor vendor Identification.
	const char *m_szProcessorBrand;		// Processor brand string.
	int32_t m_cunProcessDetail;
	const uint32_t *m_punProcessDetail; // All the bits from cpuid glued together
};

#else

// sizeof: win(24), lin(20)
struct CPUInformation
{
	int	 m_Size;						// Size of this structure, for forward compatability.
	bool m_bRDTSC : 1,					// Is RDTSC supported?
		 m_bCMOV  : 1,					// Is CMOV supported?
		 m_bFCMOV : 1,					// Is FCMOV supported?
		 m_bSSE	  : 1,					// Is SSE supported?
		 m_bSSE2  : 1,					// Is SSE2 Supported?
		 m_b3DNow : 1,					// Is 3DNow! Supported?
		 m_bMMX   : 1,					// Is MMX supported?
		 m_bHT	  : 1;					// Is HyperThreading supported?

	uint8_t m_nLogicalProcessors;		// Number op logical processors.
	uint8_t m_nPhysicalProcessors;		// Number of physical processors
	int64_t m_Speed;					// In cycles per second.
	const char *m_szProcessorID;		// Processor vendor Identification.
};

#endif // #if defined(TIER0_S)

// Have to return a pointer, not a reference, because references are not compatible with the
// extern "C" implied by PLATFORM_INTERFACE.
PLATFORM_CXX_INTERFACE const CPUInformation &GetCPUInformation();

// This struct is passed between platforms, such as a Linux client
// sending its information to a server running on Windows.
// It must compile to the same thing on all platforms and must be
// completely self-contained.
// Additions should only come at the end for cross-version compatibility.

// Bit fields in CPUInformation are not portable, so express as explicit flags.
#define PROC_FEATURE_RDTSC			0x00000001
#define PROC_FEATURE_CMOV			0x00000002
#define PROC_FEATURE_FCMOV			0x00000004
#define PROC_FEATURE_SSE			0x00000008
#define PROC_FEATURE_SSE2			0x00000010
#define PROC_FEATURE_SSE3			0x00000020
#define PROC_FEATURE_SSSE3			0x00000040
#define PROC_FEATURE_SSE41			0x00000080
#define PROC_FEATURE_SSE42			0x00000100
#define PROC_FEATURE_SSE4A			0x00000200
#define PROC_FEATURE_3DNOW			0x00000400
#define PROC_FEATURE_MMX			0x00000800
#define PROC_FEATURE_HT				0x00001000
#define PROC_FEATURE_AES			0x00002000
#define PROC_FEATURE_AVX			0x00004000
#define PROC_FEATURE_CMPXCHG16B		0x00008000
#define PROC_FEATURE_LAHFSAHF		0x00010000
#define PROC_FEATURE_PREFETCHW		0x00020000

// m_VendorId is a null-terminated string.
#define PROC_FLAG_VENDOR_ID_IS_STR 0x0001

enum EProcessorType
{
	k_EProcessorTypeUnknown,
	k_EProcessorTypeX86,
	k_EProcessorTypeX64,
};

PLATFORM_INTERFACE bool Plat_IsInDebugSession();
PLATFORM_INTERFACE void Plat_OutputDebugString(const char *psz);
PLATFORM_INTERFACE void Plat_OutputDebugStringRaw(const char *psz);

// Performance Monitoring Events - L2 stats etc...
PLATFORM_INTERFACE void InitPME();
PLATFORM_INTERFACE void ShutdownPME();

// Returns true if running on a 64 bit (windows) OS
PLATFORM_INTERFACE bool Is64BitOS();

void Plat_DebugString(const char *psz);

inline bool Plat_IsHddsnNumber(const char *authstring)
{
	for (const char *c = authstring; *c; c++)
	{
		// HHDSN have spaces or letters
		if (*c < '0' || *c > '9')
			return true;
	}

	return strtoull(authstring, nullptr, 10) >= UINT32_MAX; // SSD
}

#if !defined(SecureZeroMemory)
inline void SecureZeroMemory(void* pMemory, size_t nBytes)
{
	// The intent of this routine is to avoid being optimized away
	// by a compiler that sees that the buffer is no longer used,
	// so cast to volatile to indicate we want the accesses to occur.
	volatile unsigned char *pMem = (volatile unsigned char *)pMemory;
	while (nBytes > 0)
	{
		*pMem++ = 0;
		nBytes--;
	}
}
#endif

#ifdef _WIN32
// Process related functions
const tchar *Plat_GetCommandLine();
const char *Plat_GetCommandLineA();
#endif // #ifdef _WIN32
