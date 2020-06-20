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

#include "basetypes.h"
#include "dbgflag.h"

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

// dll export stuff
#ifndef STATIC_TIER0
	#ifdef TIER0_DLL_EXPORT
		#define DBG_INTERFACE	DLL_EXPORT
		#define DBG_OVERLOAD	DLL_GLOBAL_EXPORT
		#define DBG_CLASS		DLL_CLASS_EXPORT
	#else
		#define DBG_INTERFACE	DLL_IMPORT
		#define DBG_OVERLOAD	DLL_GLOBAL_IMPORT
		#define DBG_CLASS		DLL_CLASS_IMPORT
	#endif
#else	// BUILD_AS_DLL

#define DBG_INTERFACE	extern
#define DBG_OVERLOAD
#define DBG_CLASS

#endif	// BUILD_AS_DLL

// Usage model for the Dbg library
//
// 1. Spew.
//
//   Spew can be used in a static and a dynamic mode. The static
//   mode allows us to display assertions and other messages either only
//   in debug builds, or in non-release builds. The dynamic mode allows us to
//   turn on and off certain spew messages while the application is running.
//
//   Static Spew messages:
//
//     Assertions are used to detect and warn about invalid states
//     Spews are used to display a particular status/warning message.
//
//     To use an assertion, use
//
//     Assert((f == 5));
//     AssertMsg((f == 5), ("F needs to be %d here!\n", 5));
//     AssertFunc((f == 5), BadFunc());
//     AssertEquals(f, 5);
//     AssertFloatEquals(f, 5.0f, 1e-3);
//
//     The first will simply report that an assertion failed on a particular
//     code file and line. The second version will display a print-f formatted message
//	   along with the file and line, the third will display a generic message and
//     will also cause the function BadFunc to be executed, and the last two
//	   will report an error if f is not equal to 5 (the last one asserts within
//	   a particular tolerance).
//
//     To use a warning, use
//
//     Warning("Oh I feel so %s all over\n", "yummy");
//
//     Warning will do its magic in only Debug builds. To perform spew in *all*
//     builds, use RelWarning.
//
//	   Three other spew types, Msg, Log, and Error, are compiled into all builds.
//	   These error types do *not* need two sets of parenthesis.
//
//	   Msg("Isn't this exciting %d?", 5);
//	   Error("I'm just thrilled");
//
//   Dynamic Spew messages
//
//     It is possible to dynamically turn spew on and off. Dynamic spew is
//     identified by a spew group and priority level. To turn spew on for a
//     particular spew group, use SpewActivate("group", level). This will
//     cause all spew in that particular group with priority levels <= the
//     level specified in the SpewActivate function to be printed. Use DSpew
//     to perform the spew:
//
//     DWarning("group", level, "Oh I feel even yummier!\n");
//
//     Priority level 0 means that the spew will *always* be printed, and group
//     '*' is the default spew group. If a DWarning is encountered using a group
//     whose priority has not been set, it will use the priority of the default
//     group. The priority of the default group is initially set to 0.
//
//   Spew output
//
//     The output of the spew system can be redirected to an externally-supplied
//     function which is responsible for outputting the spew. By default, the
//     spew is simply printed using printf.
//
//     To redirect spew output, call SpewOutput.
//
//     SpewOutputFunc(OutputFunc);
//
//     This will cause OutputFunc to be called every time a spew message is
//     generated. OutputFunc will be passed a spew type and a message to print.
//     It must return a value indicating whether the debugger should be invoked,
//     whether the program should continue running, or whether the program
//     should abort.
//
// 2. Code activation
//
//   To cause code to be run only in debug builds, use DBG_CODE:
//   An example is below.
//
//   DBG_CODE(
//				{
//					int x = 5;
//					++x;
//				}
//          );
//
//   Code can be activated based on the dynamic spew groups also. Use
//
//   DBG_DCODE("group", level,
//              { int x = 5; ++x; }
//           );
//
// 3. Breaking into the debugger.
//
//   To cause an unconditional break into the debugger in debug builds only, use DBG_BREAK
//
//   DBG_BREAK();
//
//	 You can force a break in any build (release or debug) using
//
//	 DebuggerBreak();

// Various types of spew messages
// I'm sure you're asking yourself why SPEW_ instead of DBG_ ?
// It's because DBG_ is used all over the place in windows.h
// For example, DBG_CONTINUE is defined. Feh.
enum SpewType_t
{
	SPEW_MESSAGE = 0,
	SPEW_WARNING,
	SPEW_ASSERT,
	SPEW_ERROR,
	SPEW_LOG,
	SPEW_DERROR,
	SPEW_CONSOLE,

	SPEW_ANY,
	SPEW_TYPE_COUNT
};

enum SpewRetval_t
{
	SPEW_DEBUGGER = 0,
	SPEW_CONTINUE,
	SPEW_ABORT
};

// Type of externally defined function used to display debug spew
typedef SpewRetval_t (*SpewOutputFunc_t)(SpewType_t spewType, const char *pMsg);

// Used to redirect spew output
DBG_INTERFACE void SpewOutputFunc(SpewOutputFunc_t func);

// Used ot get the current spew output function
DBG_INTERFACE SpewOutputFunc_t GetSpewOutputFunc();

// Used to manage spew groups and subgroups
DBG_INTERFACE void SpewActivate(const char *pGroupName, int level);
DBG_INTERFACE bool IsSpewActive(const char *pGroupName, int level);

// Used to display messages, should never be called directly.
DBG_INTERFACE void _SpewInfo(SpewType_t type, tchar const *pFile, int line);
DBG_INTERFACE SpewRetval_t _SpewMessage(tchar const *pMsg, ...);
DBG_INTERFACE SpewRetval_t _DSpewMessage(tchar const *pGroupName, int level, tchar const *pMsg, ...);
DBG_INTERFACE bool ShouldUseNewAssertDialog();

#define DBGSPEW_FLAG_FULLDUMP		(1 << 31)
#define DBGSPEW_FLAG_FULLWRITEDUMP	(1 << 30)
#define DBG_SPEW_FLAGS				0

DBG_INTERFACE SpewRetval_t _SpewMessageType(SpewType_t spewType, tchar const *pMsgFormat, va_list args);
DBG_INTERFACE void _ExitOnFatalAssert(tchar const *pFile, int line, tchar const *pMessage);
DBG_INTERFACE SpewRetval_t _DSpewMessage(tchar const *pGroupName, int level, tchar const *pMsg, ...);
DBG_INTERFACE void AssertMsgImplementation(const tchar *_msg, const tchar *pstrFile, unsigned int nLine);

#ifndef _XBOX
	// Returns true if they want to break in the debugger.
	DBG_INTERFACE bool DoNewAssertDialog(const char *pFile, int line, const char *pExpression);
#else
	#define DoNewAssertDialog(a,b,c)	0
#endif

DBG_INTERFACE bool IsInAssert();
DBG_INTERFACE void SetInAssert(bool bState);

typedef void (*FlushLogFunc_t)();
DBG_INTERFACE void SetFlushLogFunc(FlushLogFunc_t func);
DBG_INTERFACE void CallFlushLogFunc();

typedef void (*AssertFailedNotifyFunc_t)();
DBG_INTERFACE void SetAssertFailedNotifyFunc(AssertFailedNotifyFunc_t func);
DBG_INTERFACE void CallAssertFailedNotifyFunc();

inline void AssertDebuggerSegFault()
{
#if !defined(_WIN32)
	DebuggerSegFault();
#endif // #if !defined(_WIN32)
}

// predec of minidump methods
// #include "tier0/minidump.h"

// Used to define macros, never use these directly.
#define _Assert(_exp)                                                      \
	do {                                                                   \
		if (!(_exp))                                                       \
		{                                                                  \
			_SpewInfo(SPEW_ASSERT, __FILE__, __LINE__);                    \
			if (_SpewMessage("Assertion Failed: " #_exp) == SPEW_DEBUGGER) \
			{                                                              \
				DebuggerBreak();                                           \
			}                                                              \
		}                                                                  \
	} while (0)

#define _AssertMsgSmall(_exp, _msg)                                                       \
	do {                                                                                  \
		if (!(_exp))                                                                      \
		{                                                                                 \
			AssertMsgImplementation(_msg, __TFILE__, __LINE__ | DBG_SPEW_FLAGS);          \
			AssertDebuggerSegFault();                                                     \
		}                                                                                 \
	} while (0)

#define _AssertMsgOnce(_exp, _msg)                                                        \
	do {																                  \
		static bool fAsserted = false;									                  \
		if (!fAsserted && !(_exp))									                      \
		{ 																                  \
			fAsserted = true;											                  \
			AssertMsgImplementation(_msg, __TFILE__, __LINE__ | DBG_SPEW_FLAGS);          \
			AssertDebuggerSegFault();                                                     \
		}																                  \
	} while (0)

#define _AssertMsg1(_exp, _msg, _executeExp, _bFatal)            \
	do {                                                         \
		if (!(_exp))                                             \
		{                                                        \
			_SpewInfo(SPEW_ASSERT, __FILE__, __LINE__);          \
			if (_SpewMessage(_msg) == SPEW_DEBUGGER)             \
			{                                                    \
				DebuggerBreak();                                 \
			}                                                    \
			_executeExp;                                         \
			if (_bFatal)                                         \
			{                                                    \
				_ExitOnFatalAssert(__TFILE__, __LINE__, _msg);   \
			}                                                    \
		}                                                        \
	} while (0)

#define _AssertMsgOnce1(_exp, _msg, _bFatal)                     \
	do {                                                         \
		static bool fAsserted;                                   \
		if (!fAsserted)                                          \
		{                                                        \
			_AssertMsg(_exp, _msg, (fAsserted = true), _bFatal); \
		}                                                        \
	} while (0)

#define _AssertFunc(_exp, _f)                                           \
	do {                                                                \
		if (!(_exp))                                                    \
		{                                                               \
			_SpewInfo(SPEW_ASSERT, __FILE__, __LINE__);                 \
			SpewRetval_t ret = _SpewMessage("Assertion Failed!" #_exp); \
			_f;                                                         \
			if (ret == SPEW_DEBUGGER)                                   \
			{                                                           \
				DebuggerBreak();                                        \
			}                                                           \
		}                                                               \
	} while (0)

#define _AssertEquals(_exp, _expectedValue)                                                       \
	do {                                                                                          \
		if ((_exp) != (_expectedValue))                                                           \
		{                                                                                         \
			_SpewInfo(SPEW_ASSERT, __FILE__, __LINE__);                                           \
			SpewRetval_t ret = _SpewMessage("Expected %d but got %d!", (_expectedValue), (_exp)); \
			if (ret == SPEW_DEBUGGER)                                                             \
			{                                                                                     \
				DebuggerBreak();                                                                  \
			}                                                                                     \
		}                                                                                         \
	} while (0)

#define _AssertFloatEquals(_exp, _expectedValue, _tol)                                            \
	do {                                                                                          \
		if (fabs((_exp) - (_expectedValue)) > (_tol))                                             \
		{                                                                                         \
			_SpewInfo(SPEW_ASSERT, __FILE__, __LINE__);                                           \
			SpewRetval_t ret = _SpewMessage("Expected %f but got %f!", (_expectedValue), (_exp)); \
			if (ret == SPEW_DEBUGGER)                                                             \
			{                                                                                     \
				DebuggerBreak();                                                                  \
			}                                                                                     \
		}                                                                                         \
	} while (0)

// Spew macros...
// AssertFatal macros
// AssertFatal is used to detect an unrecoverable error condition.
// If enabled, it may display an assert dialog (if DBGFLAG_ASSERTDLG is turned on or running under the debugger),
// and always terminates the application

#ifdef DBGFLAG_ASSERTFATAL

#define AssertFatal(_exp)												_AssertMsgSmall(_exp, _T("Fatal Assertion Failed: ") _T(#_exp))
#define AssertFatalOnce(_exp)											_AssertMsgOnce(_exp, _T("Fatal Assertion Failed: ") _T(#_exp))
#define AssertFatalMsg(_exp, _msg)										_AssertMsgSmall(_exp, CDbgFmtMsg(_T("Fatal Assertion Failed: %s"), (const char *)_msg).ToString())
#define AssertFatalMsgOnce(_exp, _msg)									_AssertMsgOnce(_exp, CDbgFmtMsg(_T("Fatal Assertion Failed: %s"), (const char *)_msg).ToString())
#define AssertFatalEquals(_exp, _expectedValue)							AssertFatalMsg2((_exp) == (_expectedValue), _T("Expected %d but got %d!"), (_expectedValue), (_exp))
#define AssertFatalFloatEquals(_exp, _expectedValue, _tol)				AssertFatalMsg2(fabs((_exp) - (_expectedValue)) <= (_tol), _T("Expected %f but got %f!"), (_expectedValue), (_exp))
#define VerifyFatal(_exp)												AssertFatal(_exp)
#define VerifyEqualsFatal(_exp, _expectedValue)							AssertFatalEquals(_exp, _expectedValue)
#define DbgVerifyFatal(_exp)											AssertFatal(_exp)

#define AssertFatalFullDumpMsg(_exp, _msg)								_AssertMsgSmall(_exp, CDbgFmtMsg(_T("Fatal Assertion Failed: %s"), (const char *)_msg).ToString())
#define AssertFatalFullDump(_exp)										_AssertMsgSmall(_exp, _T("Fatal Assertion Failed: ") _T(#_exp))
#define AssertFatalOnceFullDump(_exp)									_AssertMsgOnce(_exp, _T("Fatal Assertion Failed: ") _T(#_exp))

#define AssertFatalMsg1(_exp, _msg, a1)									AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1).ToString())
#define AssertFatalMsg2(_exp, _msg, a1, a2)								AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2).ToString())
#define AssertFatalMsg3(_exp, _msg, a1, a2, a3)							AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3).ToString())
#define AssertFatalMsg4(_exp, _msg, a1, a2, a3, a4)						AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4).ToString())
#define AssertFatalMsg5(_exp, _msg, a1, a2, a3, a4, a5)					AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5).ToString())
#define AssertFatalMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)				AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6).ToString())
#define AssertFatalMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)				AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6).ToString())
#define AssertFatalMsg7(_exp, _msg, a1, a2, a3, a4, a5, a6, a7)			AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7).ToString())
#define AssertFatalMsg8(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8)		AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7, a8).ToString())
#define AssertFatalMsg9(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8, a9)	AssertFatalMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7, a8, a9).ToString())

#else // DBGFLAG_ASSERTFATAL

#define AssertFatal(_exp)												((void)0)
#define AssertFatalOnce(_exp)											((void)0)
#define AssertFatalMsg(_exp, _msg)										((void)0)
#define AssertFatalMsgOnce(_exp, _msg)									((void)0)
#define AssertFatalFunc(_exp, _f)										((void)0)
#define AssertFatalEquals(_exp, _expectedValue)							((void)0)
#define AssertFatalFloatEquals(_exp, _expectedValue, _tol)				((void)0)
#define VerifyFatal(_exp)												(_exp)
#define VerifyEqualsFatal(_exp, _expectedValue)							(_exp)
#define DbgVerifyFatal(_exp)											(_exp)

#define AssertFatalFullDumpMsg(_exp, _msg)								((void)0)

#define AssertFatalMsg1(_exp, _msg, a1)									((void)0)
#define AssertFatalMsg2(_exp, _msg, a1, a2)								((void)0)
#define AssertFatalMsg3(_exp, _msg, a1, a2, a3)							((void)0)
#define AssertFatalMsg4(_exp, _msg, a1, a2, a3, a4)						((void)0)
#define AssertFatalMsg5(_exp, _msg, a1, a2, a3, a4, a5)					((void)0)
#define AssertFatalMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)				((void)0)
#define AssertFatalMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)				((void)0)
#define AssertFatalMsg7(_exp, _msg, a1, a2, a3, a4, a5, a6, a7)			((void)0)
#define AssertFatalMsg8(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8)		((void)0)
#define AssertFatalMsg9(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8, a9)	((void)0)

#endif // DBGFLAG_ASSERTFATAL

// Assert macros
// Assert is used to detect an important but survivable error.
// It's only turned on when DBGFLAG_ASSERT is true.

#ifdef DBGFLAG_ASSERT

#define Assert(_exp)												_AssertMsgSmall(_exp, _T("Assertion failed ") _T(#_exp))
#define AssertMsg(_exp, _msg)										_AssertMsgSmall(_exp, CDbgFmtMsg(_T("Assertion failed %s"), (const char *)_msg).ToString())
#define AssertOnce(_exp)											_AssertMsgOnce(_exp, _T("Assertion failed: ") _T(#_exp))
#define AssertMsgOnce(_exp, _msg)									_AssertMsgOnce(_exp, CDbgFmtMsg(_T("Assertion failed: %s"), (const char *)_msg).ToString())
#define AssertEquals(_exp, _expectedValue)							AssertMsg2((_exp) == (_expectedValue), _T("Expected %d but got %d!"), (_expectedValue), (_exp))
#define AssertStrEquals(_exp, _expectedString)						AssertMsg2(Q_strcmp(_exp, _expectedString) == 0, _T("Expected %s but got %s!"), (_expectedString), (_exp))
#define AssertFloatEquals(_exp, _expectedValue, _tol)				AssertMsg2(fabs((_exp) - (_expectedValue)) <= (_tol), _T("Expected %f but got %f!"), (_expectedValue), (_exp))
#define VerifyEquals(_exp, _expectedValue)							AssertEquals(_exp, _expectedValue)

#ifdef _DEBUG
#define DbgVerify(_exp)				Assert(_exp)
#define DbgAssert(_exp)				Assert(_exp)
#define DbgAssertMsg(_exp, _msg)	AssertMsg(_exp, _msg)
#else
#define DbgVerify(_exp)				((void)(_exp))
#define DbgAssert(_exp)				((void)0)
#define DbgAssertMsg(_exp, _msg)	((void)0)
#endif

#if defined(_SERVER)
// full dumps only available on _SERVER side
#define AssertFullDump(_exp)										_AssertMsgSmall(_exp, _T("Assertion failed ") _T(#_exp))
#define AssertOnceFullDump(_exp)									_AssertMsgOnce(_exp, _T("Assertion failed ") _T(#_exp))
#else
// anywhere else, they silently regress to minidumps
#define AssertFullDump(_exp)										_AssertMsgSmall(_exp, _T("Assertion failed ") _T(#_exp))
#define AssertOnceFullDump(_exp)									_AssertMsgOnce(_exp, _T("Assertion failed ") _T(#_exp))
#endif

#define AssertMsg1(_exp, _msg, a1)									AssertMsg(_exp, CDbgFmtMsg(_msg, a1).ToString())
#define AssertMsg2(_exp, _msg, a1, a2)								AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2).ToString())
#define AssertMsg3(_exp, _msg, a1, a2, a3)							AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3).ToString())
#define AssertMsg4(_exp, _msg, a1, a2, a3, a4)						AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4).ToString())
#define AssertMsg5(_exp, _msg, a1, a2, a3, a4, a5)					AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5).ToString())
#define AssertMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)				AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6).ToString())
#define AssertMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)				AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6).ToString())
#define AssertMsg7(_exp, _msg, a1, a2, a3, a4, a5, a6, a7)			AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7).ToString())
#define AssertMsg8(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8)		AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7, a8).ToString())
#define AssertMsg9(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8, a9)	AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3, a4, a5, a6, a7, a8, a9).ToString())

#if defined(_DEBUG)
#define DbgAssertMsg1(_exp, _msg, a1)								AssertMsg(_exp, CDbgFmtMsg(_msg, a1).ToString())
#define DbgAssertMsg2(_exp, _msg, a1, a2)							AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2).ToString())
#define DbgAssertMsg3(_exp, _msg, a1, a2, a3)						AssertMsg(_exp, CDbgFmtMsg(_msg, a1, a2, a3).ToString())
#else
#define DbgAssertMsg1(_exp, _msg, a1)								((void)0)
#define DbgAssertMsg2(_exp, _msg, a1, a2)							((void)0)
#define DbgAssertMsg3(_exp, _msg, a1, a2, a3)						((void)0)
#endif

#else // DBGFLAG_ASSERT

#define Assert(_exp)												((void)0)
#define AssertOnce(_exp)											((void)0)
#define AssertMsg(_exp, _msg)										((void)0)
#define AssertMsgOnce(_exp, _msg)									((void)0)
#define AssertEquals(_exp, _expectedValue)							((void)0)
#define AssertStrEquals(_exp, _expectedString)						((void)0)
#define AssertFloatEquals(_exp, _expectedValue, _tol)				((void)0)
#define VerifyEquals(_exp, _expectedValue)							(_exp)
#define DbgVerify(_exp)												(_exp)
#define AssertFullDump(_exp)										((void)0)
#define AssertOnceFullDump(_exp)									((void)0)
#define DbgAssert(_exp)												((void)0)

#define AssertMsg1(_exp, _msg, a1)									((void)0)
#define AssertMsg2(_exp, _msg, a1, a2)								((void)0)
#define AssertMsg3(_exp, _msg, a1, a2, a3)							((void)0)
#define AssertMsg4(_exp, _msg, a1, a2, a3, a4)						((void)0)
#define AssertMsg5(_exp, _msg, a1, a2, a3, a4, a5)					((void)0)
#define AssertMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)				((void)0)
#define AssertMsg6(_exp, _msg, a1, a2, a3, a4, a5, a6)				((void)0)
#define AssertMsg7(_exp, _msg, a1, a2, a3, a4, a5, a6, a7)			((void)0)
#define AssertMsg8(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8)		((void)0)
#define AssertMsg9(_exp, _msg, a1, a2, a3, a4, a5, a6, a7, a8, a9)	((void)0)

#define DbgAssertMsg1(_exp, _msg, a1)								((void)0)
#define DbgAssertMsg2(_exp, _msg, a1, a2)							((void)0)
#define DbgAssertMsg3(_exp, _msg, a1, a2, a3)						((void)0)

#endif // DBGFLAG_ASSERT

#define Plat_FatalError Error
#define DMsg _DMsg

// These are always compiled in
DBG_INTERFACE void Msg(const char *pMsg, ...);
DBG_INTERFACE void _DMsg(const char *pGroupName, int level, const char *pMsg, ...);
void _DMsg(const char *pMsg, ...);

DBG_INTERFACE void Warning(const char *pMsg, ...);
DBG_INTERFACE void DWarning(const char *pGroupName, int level, const char *pMsg, ...);
void DWarning(const char *pMsgFormat, ...);

DBG_INTERFACE void Log(const char *pMsg, ...);
DBG_INTERFACE void DLog(const char *pGroupName, int level, const char *pMsg, ...);

DBG_INTERFACE void Error(const char *pMsg, ...);
void DError(const char *pMsgFormat, ...);
void ConMsg(const char *pMsgFormat, ...);

// You can use this macro like a runtime assert macro.
// If the condition fails, then Error is called with the message. This macro is called
// like AssertMsg, where msg must be enclosed in parenthesis:
//
// ErrorIfNot(bCondition, ("a b c %d %d %d", 1, 2, 3));
#define ErrorIfNot(condition, msg) \
	if ((condition))               \
		;                          \
				else               \
	{                              \
		Error msg;                 \
	}

// Code macros, debugger interface
#ifdef _DEBUG
	#define DBG_CODE(_code)				if (0) ; else { _code }
	#define DBG_DCODE(_g, _l, _code)	if (IsSpewActive(_g, _l)) { _code } else {}
	#define DBG_BREAK()					DebuggerBreak()
#else // _DEBUG
	#define DBG_CODE(_code)				((void)0)
	#define DBG_DCODE(_g, _l, _code)	((void)0)
	#define DBG_BREAK()					((void)0)
#endif // _DEBUG

// Macro to assist in asserting constant invariants during compilation
#define UID_PREFIX generated_id_
#define UID_CAT1(a, c) a ## c
#define UID_CAT2(a, c) UID_CAT1(a, c)
#define UNIQUE_ID UID_CAT2(UID_PREFIX, __LINE__)

#ifdef _DEBUG
#define COMPILE_TIME_ASSERT(pred) switch(0){case 0:case pred:;}
#define ASSERT_INVARIANT(pred)    static void UNIQUE_ID() { COMPILE_TIME_ASSERT(pred) }
#else
#define COMPILE_TIME_ASSERT(pred)
#define ASSERT_INVARIANT(pred)
#endif

extern bool g_bAPIWarningEnabled;
extern bool g_bAPIMsgEnabled;

void _APIWarning(const char *fmt, ...);

// Templates to assist in validating pointers:
// Have to use these stubs so we don't have to include windows.h here.
void _AssertValidReadPtr(void *ptr, int count = 1);
void _AssertValidWritePtr(void *ptr, int count = 1);
void _AssertValidReadWritePtr(void *ptr, int count = 1);

#if defined(DBGFLAG_ASSERT)
void AssertValidStringPtr(const char *ptr, int maxchar = 0xFFFFFF);
template <class T> inline void AssertValidReadPtr(T *ptr, int count = 1)      { _AssertValidReadPtr((void *)ptr, count); }
template <class T> inline void AssertValidWritePtr(T *ptr, int count = 1)     { _AssertValidWritePtr((void *)ptr, count); }
template <class T> inline void AssertValidReadWritePtr(T *ptr, int count = 1) { _AssertValidReadWritePtr((void *)ptr, count); }
#else
#define AssertValidStringPtr(...) ((void)0)
#define AssertValidReadPtr(...) ((void)0)
#define AssertValidWritePtr(...) ((void)0)
#define AssertValidReadWritePtr(...) ((void)0)
#endif // #if defined(DBGFLAG_ASSERT)

#define AssertValidThis() AssertValidReadWritePtr(this, sizeof(*this))

// Macro to protect functions that are not reentrant
#ifdef _DEBUG
class CReentryGuard
{
public:
	CReentryGuard(int *pSemaphore)
		: m_pSemaphore(pSemaphore)
	{
		(*m_pSemaphore)++;
	}
	~CReentryGuard()
	{
		(*m_pSemaphore)--;
	}

private:
	int *m_pSemaphore;
};

#define ASSERT_NO_REENTRY()          \
	static int fSemaphore##__LINE__; \
	Assert(!fSemaphore##__LINE__);   \
	CReentryGuard ReentryGuard##__LINE__(&fSemaphore##__LINE__)
#else // _DEBUG
#define ASSERT_NO_REENTRY()
#endif // _DEBUG

// Inline string formatter
class CDbgFmtMsg
{
public:
	CDbgFmtMsg(const tchar *pszFormat, ...)
	{
		va_list arg_ptr;
		va_start(arg_ptr, pszFormat);
		_vsntprintf(m_szBuf, sizeof(m_szBuf) - 1, pszFormat, arg_ptr);
		va_end(arg_ptr);

		m_szBuf[sizeof(m_szBuf) - 1] = '\0';
	}

	operator const tchar *() const
	{
		return m_szBuf;
	}

	const tchar *ToString() const
	{
		return m_szBuf;
	}

private:
	tchar m_szBuf[256];
};
