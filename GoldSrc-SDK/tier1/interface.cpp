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
#include <windows.h>
#endif

#include <stdio.h>
#include "interface.h"
#include "tier0/basetypes.h"
#include "tier0/dbg.h"

// InterfaceReg
InterfaceReg *InterfaceReg::s_pInterfaceRegs = nullptr;

InterfaceReg::InterfaceReg(InstantiateInterfaceFn fn, const char *pName) : m_pName(pName)
{
	m_CreateFn = fn;
	m_pNext = s_pInterfaceRegs;
	s_pInterfaceRegs = this;
}

// This is the primary exported function by a dll, referenced by name via dynamic binding
// that exposes an opqaue function pointer to the interface.
//
// We have the Internal variant so Sys_GetFactoryThis() returns the correct internal
// symbol under GCC/Linux/Mac as CreateInterface is DLL_EXPORT so its global so the loaders
// on those OS's pick exactly 1 of the CreateInterface symbols to be the one that is process wide and
// all Sys_GetFactoryThis() calls find that one, which doesn't work. Using the internal walkthrough here
// makes sure Sys_GetFactoryThis() has the dll specific symbol and GetProcAddress() returns the module specific
// function for CreateInterface again getting the dll specific symbol we need.
EXPORT_FUNCTION IBaseInterface *CreateInterface(const char *pName, int *pReturnCode)
{
	int res = -1;
	int i = 0;

	InterfaceReg *pCur;
	for (pCur = InterfaceReg::s_pInterfaceRegs; pCur; pCur = pCur->m_pNext)
	{
		if (strcmp(pCur->m_pName, pName) == 0)
		{
			if (pReturnCode)
			{
				*pReturnCode = IFACE_OK;
			}

			res = IFACE_OK;
			return pCur->m_CreateFn();
		}
	}

	if (pReturnCode)
	{
		*pReturnCode = IFACE_FAILED;
		res = IFACE_FAILED;
	}

	return nullptr;
}

#ifndef _WIN32
// Linux doesn't have this function so this emulates its functionality
void *GetModuleHandle(const char *name)
{
	void *handle;
	if (name == nullptr)
	{
		// hmm, how can this be handled under linux....
		// is it even needed?
		return nullptr;
	}

	if ((handle = dlopen(name, RTLD_NOW)) == nullptr)
	{
		//printf("Error:%s\n",dlerror());
		// couldn't open this file
		return nullptr;
	}

	// read "man dlopen" for details
	// in short dlopen() inc a ref count
	// so dec the ref count by performing the close
	dlclose(handle);
	return handle;
}
#endif // _WIN32

// Purpose: returns a pointer to a function, given a module
// Input  : pModuleName - module name
//			*pName - proc name
//static hlds_run wants to use this function
void *Sys_GetProcAddress(const char *pModuleName, const char *pName)
{
	return GetProcAddress(GetModuleHandle(pModuleName), pName);
}

// Purpose: returns a pointer to a function, given a module
// Input  : pModuleName - module name
//			*pName - proc name
// hlds_run wants to use this function
void *Sys_GetProcAddress(void *pModuleHandle, const char *pName)
{
	return GetProcAddress((HMODULE)pModuleHandle, pName);
}

CSysModule *Sys_GetModuleHandle(const char *pModuleName)
{
	return (CSysModule *)GetModuleHandle(pModuleName);
}

// Purpose: Loads a DLL/component from disk and returns a handle to it
// Input  : *pModuleName - filename of the component
// Output : opaque handle to the module (hides system dependency)
CSysModule *Sys_LoadModule(const char *pModuleName)
{
#ifdef _WIN32
	HMODULE hDLL = NULL;
	wchar_t moduleName[MAX_PATH];
	int nSize = MultiByteToWideChar(CP_UTF8, 0, pModuleName, -1, moduleName, ARRAYSIZE(moduleName));
	moduleName[ARRAYSIZE(moduleName) - 1] = '\0';

	if (nSize)
	{
		hDLL = LoadLibraryW(moduleName);
	}
#else
	HMODULE hDLL  = nullptr;
	char szAbsoluteModuleName[1024];
	if (pModuleName[0] != '/')
	{
		char szCwd[1024];
		getcwd(szCwd, sizeof(szCwd));
		if (szCwd[strlen(szCwd) - 1] == '/')
			szCwd[strlen(szCwd) - 1] = '\0';

		_snprintf(szAbsoluteModuleName, sizeof(szAbsoluteModuleName), "%s/%s", szCwd, pModuleName);
		hDLL = dlopen(szAbsoluteModuleName, RTLD_NOW);
	}
	else
	{
		_snprintf(szAbsoluteModuleName, sizeof(szAbsoluteModuleName), "%s", pModuleName);
		hDLL = dlopen(pModuleName, RTLD_NOW);
	}
#endif // _WIN32

	if (!hDLL)
	{
#if defined(_WIN32)
		wchar_t str[MAX_PATH * 2];
#else
		char str[MAX_PATH];
#endif

#if defined(_WIN32)
		_snwprintf(str, ARRAYSIZE(str), L"%s.dll", moduleName);
		hDLL = LoadLibraryW(str);
#elif defined(OSX)
		printf("Error: %s\n", dlerror());
		_snprintf(str, sizeof(str), "%s.dylib", szAbsoluteModuleName);
		hDLL = dlopen(str, RTLD_NOW);
#else
		printf("Error: %s\n", dlerror());
		_snprintf(str, sizeof(str), "%s.so", szAbsoluteModuleName);
		hDLL = dlopen(str, RTLD_NOW);
#endif
	}

	return reinterpret_cast<CSysModule *>(hDLL);
}

const char *Sys_GetLastErrorMsg()
{
	static char errstr[128] = "";

#if defined(_WIN32)
	int error_code = GetLastError();
	if (error_code != NO_ERROR)
	{
		SetLastError(0);

		int len = sprintf(errstr, "Error <%d>: ", error_code);
		len += FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			error_code,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), /* Default language */
			(LPTSTR)errstr + len,
			sizeof(errstr) - len,
			NULL
		);

		// drop \r\n
		if (len > 1 && errstr[len - 2] == '\r' && errstr[len - 1] == '\n')
		{
			if (len > 2 && errstr[len - 3] == '.')
			{
				len--;
			}
		}

		return errstr;
	}

	return "";
#else
	Q_strlcpy(errstr, dlerror());
	return errstr;
#endif // #if defined(_WIN32)
}

// Purpose: Unloads a DLL/component from
// Input  : *pModuleName - filename of the component
// Output : opaque handle to the module (hides system dependency)
bool Sys_UnloadModule(CSysModule *pModule)
{
	if (!pModule)
		return false;

	HMODULE hDLL = reinterpret_cast<HMODULE>(pModule);

#ifdef _WIN32
	return FreeLibrary(hDLL) == TRUE;
#else
	return dlclose(hDLL) == 0;
#endif // _WIN32
}

// Purpose: returns a pointer to a function, given a module
// Input  : module - windows HMODULE from Sys_LoadModule()
//			*pName - proc name
// Output : factory for this module
CreateInterfaceFn Sys_GetFactory(CSysModule *pModule)
{
	if (!pModule)
		return nullptr;

	return reinterpret_cast<CreateInterfaceFn>(Sys_GetProcAddress(pModule, CREATEINTERFACE_PROCNAME));
}

// Purpose: returns the instance of this module
// Output : CreateInterfaceFn
CreateInterfaceFn Sys_GetFactoryThis()
{
	return CreateInterface;
}

// Purpose: returns the instance of the named module
// Input  : *pModuleName - name of the module
// Output : CreateInterfaceFn - instance of that module
CreateInterfaceFn Sys_GetFactory(const char *pModuleName)
{
	return reinterpret_cast<CreateInterfaceFn>(Sys_GetProcAddress(pModuleName, CREATEINTERFACE_PROCNAME));
}

CFactoryList g_FactoryList;

void CFactoryList::Add(CreateInterfaceFn *factories, int numFactories)
{
	Assert(ARRAYSIZE(m_FactoryList) > (m_Count + numFactories));

	for (int i = 0; i < numFactories; i++)
	{
		if (FindDuplicate(factories[i]))
			continue;

		m_FactoryList[m_Count++] = factories[i];
	}
}

IBaseInterface *CFactoryList::Find(const char *pName, int *pReturnCode) const
{
	for (int i = 0; i < m_Count; i++)
	{
		if (!m_FactoryList[i])
			continue;

		auto pInterface = m_FactoryList[i](pName, pReturnCode);
		if (pInterface)
			return pInterface;
	}

	return nullptr;
}

bool CFactoryList::FindDuplicate(CreateInterfaceFn factory) const
{
	for (int i = 0; i < m_Count; i++)
	{
		if (m_FactoryList[i] == factory)
			return true;
	}

	return false;
}
