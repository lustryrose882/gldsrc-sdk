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

#include "dbg.h"

#if defined(_WIN32)
	#define WIN_32_LEAN_AND_MEAN
	#include <windows.h>				// Currently needed for IsBadReadPtr and IsBadWritePtr
	#pragma comment(lib, "user32.lib")	// For MessageBox
#endif // #if defined(_WIN32)

// Internal structures
enum
{
	MAX_GROUP_NAME_LENGTH = 48
};

struct SpewGroup_t
{
	char	m_GroupName[MAX_GROUP_NAME_LENGTH];
	int		m_Level;
};


// Templates to assist in validating pointers:
void _AssertValidReadPtr(void *ptr, int count)
{
#ifdef _WIN32
	Assert(!IsBadReadPtr(ptr, count));
#else
	Assert(ptr);
#endif

}

void _AssertValidWritePtr(void *ptr, int count)
{
#ifdef _WIN32
	Assert(!IsBadWritePtr(ptr, count));
#else
	Assert(ptr);
#endif
}

void _AssertValidReadWritePtr(void *ptr, int count)
{
#ifdef _WIN32
	Assert(!(IsBadWritePtr(ptr, count) || IsBadReadPtr(ptr, count)));
#else
	Assert(ptr);
#endif
}

#if defined(DBGFLAG_ASSERT)
void AssertValidStringPtr(const char *ptr, int maxchar)
{
#ifdef _WIN32
	Assert(!IsBadStringPtr(ptr, maxchar));
#else
	Assert(ptr);
#endif
}
#endif

// Globals
SpewRetval_t DefaultSpewFunc(SpewType_t type, const char *pMsg)
{
	printf("%s", pMsg);
	if (type == SPEW_ASSERT)
		return SPEW_DEBUGGER;
	else if (type == SPEW_ERROR)
		return SPEW_ABORT;
	else
		return SPEW_CONTINUE;
}

static SpewOutputFunc_t s_SpewOutputFunc         = DefaultSpewFunc;

static const char *s_pFileName;
static int         s_Line;
static SpewType_t  s_SpewType;

static SpewGroup_t *s_pSpewGroups = 0;
static int          s_GroupCount = 0;
static int          s_DefaultLevel = 0;

#if defined(STATIC_TIER0)

// Spew output management.
void SpewOutputFunc(SpewOutputFunc_t func)
{
	s_SpewOutputFunc = func ? func : DefaultSpewFunc;
}

SpewOutputFunc_t GetSpewOutputFunc()
{
	if (s_SpewOutputFunc)
	{
		return s_SpewOutputFunc;
	}
	else
	{
		return DefaultSpewFunc;
	}
}

void _ExitOnFatalAssert(const char *pFile, int line, const char *pMessage)
{
	_SpewMessage("Fatal assert failed: %s, line %d.  Application exiting.\n", pFile, line);

#if defined(_WIN32) && defined(_MINIDUMP)
	// only write out minidumps if we're not in the debugger
	if (!Plat_IsInDebugSession())
	{
		WriteMiniDump(pMessage ? pMessage : "Fatal assert", pFile, line, false, true);
	}
#endif // _WIN32

	DMsg("console", 1, "_ExitOnFatalAssert\n");
	exit(EXIT_FAILURE);
}

// Spew functions
void _SpewInfo(SpewType_t type, const char *pFile, int line)
{
	// Only grab the file name. Ignore the path.
	const char *pSlash = strrchr(pFile, '\\');
	const char *pSlash2 = strrchr(pFile, '/');

	if (pSlash < pSlash2) pSlash = pSlash2;

	s_pFileName = pSlash ? pSlash + 1 : pFile;
	s_Line = line;
	s_SpewType = type;
}

SpewRetval_t _SpewMessageType(SpewType_t spewType, tchar const* pMsgFormat, va_list args)
{
	//LOCAL_THREAD_LOCK();

#ifndef _XBOX
	tchar pTempBuffer[5020];
#else
	char pTempBuffer[1024];
#endif

	// check that we won't artifically truncate the string
	Assert(_tcslen(pMsgFormat) < sizeof(pTempBuffer));

	// Printf the file and line for warning + assert only...
	int len = 0;
	if (spewType == SPEW_ASSERT)
	{
		len = _sntprintf(pTempBuffer, sizeof(pTempBuffer) - 1, _T("%s (%d) : "), s_pFileName, s_Line);
	}

	if (len == -1)
	{
		return SPEW_ABORT;
	}

	// Create the message....
	int val = _vsntprintf(&pTempBuffer[len], sizeof(pTempBuffer) - len - 1, pMsgFormat, args);
	if (val == -1)
	{
		return SPEW_ABORT;
	}

	len += val;

	// Use normal assert here; to avoid recursion
	Assert(len * sizeof(*pMsgFormat) < sizeof(pTempBuffer));

	// Add \n for warning and assert
	if (spewType == SPEW_ASSERT)
	{
		len += _stprintf(&pTempBuffer[len], _T("\n"));
#ifdef WIN32
		OutputDebugString(pTempBuffer);
#endif
	}

	// use normal assert here; to avoid recursion
	Assert((uint32_t)len < (sizeof(pTempBuffer) / sizeof(pTempBuffer[0]) - 1));
	Assert(s_SpewOutputFunc);

	// direct it to the appropriate target(s)
	SpewRetval_t ret = s_SpewOutputFunc(spewType, pTempBuffer);
	switch (ret)
	{
// Asserts put the break into the macro so it occurs in the right place
	case SPEW_DEBUGGER:
		if (spewType != SPEW_ASSERT)
		{
			DebuggerBreak();
		}
		break;

	case SPEW_ABORT:
		//MessageBox(nullptr, "Error in _SpewMessageType", "Error", MB_OK);
		//DMsg("console",  1, _T("Exiting on SPEW_ABORT\n"));
		//int *null = 0;
		//*null = 0;
#ifdef _WIN32
		TerminateProcess(GetCurrentProcess(), EXIT_FAILURE); // die, die RIGHT NOW! (don't call exit() so destructors will not get run)
#elif defined(_PS3)
		sys_process_exit(EXIT_FAILURE);
#else
		_exit(EXIT_FAILURE); // forcefully shutdown of the process without destructors running
#endif
	default:
		break;
	}

	return ret;
}

SpewRetval_t _SpewMessage(const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	SpewRetval_t ret = _SpewMessageType(s_SpewType, pMsgFormat, args);
	va_end(args);
	return ret;
}

SpewRetval_t _DSpewMessage(const char *pGroupName, int level, const char *pMsgFormat, ...)
{
	if (!IsSpewActive(pGroupName, level))
		return SPEW_CONTINUE;

	va_list args;
	va_start(args, pMsgFormat);
	SpewRetval_t ret = _SpewMessageType(s_SpewType, pMsgFormat, args);
	va_end(args);
	return ret;
}

void Msg(const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_MESSAGE, pMsgFormat, args);
	va_end(args);
}

void DMsg(const char *pGroupName, int level, const char *pMsgFormat, ...)
{
	if (!IsSpewActive(pGroupName, level))
		return;

	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_MESSAGE, pMsgFormat, args);
	va_end(args);
}

void Warning(const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_WARNING, pMsgFormat, args);
	va_end(args);
}

void DWarning(const char *pGroupName, int level, const char *pMsgFormat, ...)
{
	if (!IsSpewActive(pGroupName, level))
		return;

	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_WARNING, pMsgFormat, args);
	va_end(args);
}

void Log(const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_LOG, pMsgFormat, args);
	va_end(args);
}

void DLog(const char *pGroupName, int level, const char *pMsgFormat, ...)
{
	if (!IsSpewActive(pGroupName, level))
		return;

	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_LOG, pMsgFormat, args);
	va_end(args);
}

void Error(const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_ERROR, pMsgFormat, args);
	va_end(args);
}

// Find a group, return true if found, false if not. Return in ind the
// index of the found group, or the index of the group right before where the
// group should be inserted into the list to maintain sorted order.
bool FindSpewGroup(const char *pGroupName, int *pInd)
{
	int s = 0;
	if (s_GroupCount)
	{
		int e = (int)(s_GroupCount - 1);
		while (s <= e)
		{
			int m = (s + e) >> 1;
			int cmp = _stricmp(pGroupName, s_pSpewGroups[m].m_GroupName);
			if (!cmp)
			{
				*pInd = m;
				return true;
			}

			if (cmp < 0)
				e = m - 1;
			else
				s = m + 1;
		}
	}

	*pInd = s;
	return false;
}

void AssertMsgImplementation(const tchar *_msg, const tchar *pstrFile, unsigned int nLine)
{
	nLine &= ~(DBGSPEW_FLAG_FULLWRITEDUMP | DBGSPEW_FLAG_FULLDUMP);

	_SpewInfo(SPEW_ASSERT, pstrFile, nLine);
	SpewRetval_t ret = _SpewMessage("%s", _msg);
	if (ret == SPEW_DEBUGGER)
	{
//#if !defined(DBGFLAG_NO_ASSERTDLG)
//		if (!ShouldUseNewAssertDialog() || DoNewAssertDialog(pstrFile, nLine, _msg))
			DebuggerBreak();
//#endif

		_ExitOnFatalAssert(pstrFile, nLine, _msg);
	}
}

// Sets the priority level for a spew group
void SpewActivate(const char *pGroupName, int level)
{
	Assert(pGroupName);

	// check for the default group first...
	if ((pGroupName[0] == '*') && (pGroupName[1] == '\0'))
	{
		s_DefaultLevel = level;
		return;
	}

	// Normal case, search in group list using binary search.
	// If not found, grow the list of groups and insert it into the
	// right place to maintain sorted order. Then set the level.
	int ind;
	if (!FindSpewGroup(pGroupName, &ind))
	{
		// not defined yet, insert an entry.
		s_GroupCount++;
		if (s_pSpewGroups)
		{
			s_pSpewGroups = (SpewGroup_t *)realloc(s_pSpewGroups, s_GroupCount * sizeof(SpewGroup_t));

			// shift elements down to preserve order
			int numToMove = s_GroupCount - ind - 1;
			memmove(&s_pSpewGroups[ind + 1], &s_pSpewGroups[ind], numToMove * sizeof(SpewGroup_t));
		}
		else
		{
			s_pSpewGroups = (SpewGroup_t *)malloc(s_GroupCount * sizeof(SpewGroup_t));
		}

		Assert(strlen(pGroupName) < MAX_GROUP_NAME_LENGTH);

		uint32_t len = sizeof(s_pSpewGroups[ind].m_GroupName);
		strncpy(s_pSpewGroups[ind].m_GroupName, pGroupName, len - 1);
		s_pSpewGroups[ind].m_GroupName[len - 1] = '\0';
	}

	s_pSpewGroups[ind].m_Level = level;
}

// Tests to see if a particular spew is active
bool IsSpewActive(const char *pGroupName, int level)
{
	// If we don't find the spew group, use the default level.
	int ind;
	if (FindSpewGroup(pGroupName, &ind))
		return s_pSpewGroups[ind].m_Level >= level;
	else
		return s_DefaultLevel >= level;
}

#endif // #if defined(STATIC_TIER0)

bool g_bAPIWarningEnabled = false;
bool g_bAPIMsgEnabled = false;

void ConMsg(const char *pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_CONSOLE, pMsgFormat, args);
	va_end(args);
}

void DMsg(const char *pMsgFormat, ...)
{
#if defined(CLIENT_CORE)
	if (!g_cmdlineparmDeveloper.Exists())
		return;
#elif defined(_SERVER)
	if (!g_engfuncs.pfnCVarGetFloat("developer"))
		return;
#else
	// Not implemented yet
	return;
#endif

	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_MESSAGE, pMsgFormat, args);
	va_end(args);
}

void DError(const char *pMsgFormat, ...)
{
#ifdef CLIENT_CORE
	if (!g_cmdlineparmDeveloper.Exists())
		return;
#else
	// Not implemented yet
	return;
#endif

	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_DERROR, pMsgFormat, args);
	va_end(args);
}

void DWarning(const char *pMsgFormat, ...)
{
#ifdef CLIENT_CORE
	if (!g_cmdlineparmDeveloper.Exists())
		return;
#else
	// Not implemented yet
	return;
#endif

	va_list args;
	va_start(args, pMsgFormat);
	_SpewMessageType(SPEW_WARNING, pMsgFormat, args);
	va_end(args);
}

void _APIWarning(const char *fmt, ...)
{
	if (!g_bAPIWarningEnabled)
		return;

	char buf[4096];
	va_list args;
	va_start(args, fmt);
	int len = _snprintf(buf, sizeof(buf) - 1, "[S_API WARN] ");
	_vsnprintf(&buf[len], (sizeof(buf) - 1) - len, fmt, args);
	va_end(args);
	//Msg("%s", buf);
	Warning("%s", buf);
}
