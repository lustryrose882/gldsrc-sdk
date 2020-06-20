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

#pragma warning (disable:4514)

#include "utlsymbol.h"

LessCtx_t g_LessCtx;
CUtlSymbolTable *CUtlSymbol::s_pSymbolTable = nullptr;

void CUtlSymbol::Initialize()
{
	// necessary to allow us to create global symbols
	static bool symbolsInitialized = false;
	if (!symbolsInitialized)
	{
		s_pSymbolTable = new CUtlSymbolTable;
		symbolsInitialized = true;
	}
}

CUtlSymbolTable *CUtlSymbol::CurrTable()
{
	Initialize();
	return s_pSymbolTable;
}

CUtlSymbol::CUtlSymbol(const char *pStr)
{
	m_Id = CurrTable()->AddString(pStr);
}

const char *CUtlSymbol::String() const
{
	return CurrTable()->String(m_Id);
}

// Checks if the symbol matches a string
bool CUtlSymbol::operator==(const char *pStr) const
{
	if (m_Id == UTL_INVAL_SYMBOL)
		return false;

	return strcmp(String(), pStr) == 0;
}

bool CUtlSymbolTable::SymLess(const unsigned int &i1, const unsigned int &i2)
{
	const char *str1 = (i1 == UTL_INVALID_STRING_INDEX) ? g_LessCtx.m_pUserString : g_LessCtx.m_pTable->StringFromIndex(i1);
	const char *str2 = (i2 == UTL_INVALID_STRING_INDEX) ? g_LessCtx.m_pUserString : g_LessCtx.m_pTable->StringFromIndex(i2);

	return strcmp(str1, str2) < 0;
}

bool CUtlSymbolTable::SymLessi(const unsigned int &i1, const unsigned int &i2)
{
	const char *str1 = (i1 == UTL_INVALID_STRING_INDEX) ? g_LessCtx.m_pUserString : g_LessCtx.m_pTable->StringFromIndex(i1);
	const char *str2 = (i2 == UTL_INVALID_STRING_INDEX) ? g_LessCtx.m_pUserString : g_LessCtx.m_pTable->StringFromIndex(i2);

	return _stricmp(str1, str2) < 0;
}

// Constructor, Destructor
CUtlSymbolTable::CUtlSymbolTable(int growSize, int initSize, bool caseInsensitive) :
	m_Lookup(growSize, initSize, caseInsensitive ? SymLess : SymLessi),
	m_StringPools(MAX_STRING_POOL_SIZE)
{
	;
}

CUtlSymbolTable::~CUtlSymbolTable()
{
	// Release the stringpool string data
	RemoveAll();
}

CUtlSymbol CUtlSymbolTable::Find(const char *pString)
{
	if (!pString)
		return CUtlSymbol();

	// Store a special context used to help with insertion
	g_LessCtx.m_pUserString = pString;
	g_LessCtx.m_pTable = this;

	// Passing this special invalid symbol makes the comparison function
	// use the string passed in the context
	UtlSymId_t idx = m_Lookup.Find(UTL_INVALID_STRING_INDEX);
	return CUtlSymbol(idx);
}

// Finds and/or creates a symbol based on the string
CUtlSymbol CUtlSymbolTable::AddString(const char *pString)
{
	if (!pString)
		return CUtlSymbol(UTL_INVAL_SYMBOL);

	// Find a pool with space for this string, or allocate a new one
	CUtlSymbol id = Find(pString);

	if (id.IsValid())
		return id;

	// Add a new pool
	int len = strlen(pString) + 1;
	int stridx = m_StringPools.AddMultipleToTail(len);
	memcpy(&m_StringPools[stridx], pString, len);

	// Didn't find, insert the string into the vector
	UtlSymId_t idx = m_Lookup.Insert(stridx);
	return CUtlSymbol(idx);
}

// Look up the string associated with a particular symbol
const char *CUtlSymbolTable::String(CUtlSymbol id) const
{
	if (!id.IsValid())
		return "";

	Assert(m_Lookup.IsValidIndex((UtlSymId_t)id));
	return StringFromIndex(m_Lookup[id]);
}

// Remove all symbols in the table
void CUtlSymbolTable::RemoveAll()
{
	m_Lookup.RemoveAll();
	m_StringPools.RemoveAll();
}
