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

#include "tier1/utlrbtree.h"
#include "tier1/utlvector.h"

class CUtlSymbolTable;

using UtlSymId_t = unsigned short;

const int MAX_STRING_POOL_SIZE = 256;
const UtlSymId_t UTL_INVAL_SYMBOL = ((UtlSymId_t)~0);
const unsigned int UTL_INVALID_STRING_INDEX = ((unsigned int)~0);

struct LessCtx_t
{
	const char *m_pUserString;
	CUtlSymbolTable *m_pTable;

	LessCtx_t() : m_pUserString(0), m_pTable(0) {}
};

class CUtlSymbol
{
public:
	// constructor, destructor
	CUtlSymbol() : m_Id(UTL_INVAL_SYMBOL) {}
	CUtlSymbol(UtlSymId_t id) : m_Id(id) {}
	CUtlSymbol(const char *pStr);
	CUtlSymbol(CUtlSymbol const &sym) : m_Id(sym.m_Id) {}

	// operator=
	CUtlSymbol &operator=(CUtlSymbol const &src)
	{
		m_Id = src.m_Id;
		return *this;
	}

	// operator==
	bool operator==(CUtlSymbol const &src) const { return m_Id == src.m_Id; }
	bool operator==(const char *pStr) const;

	// Is valid?
	bool IsValid() const { return m_Id != UTL_INVAL_SYMBOL; }

	operator UtlSymId_t() const { return m_Id; }	// Gets at the symbol
	const char *String() const;						// Gets the string associated with the symbol

protected:
	static void Initialize();						// Initializes the symbol table
	static CUtlSymbolTable *CurrTable();			// returns the current symbol table

	UtlSymId_t m_Id;
	static CUtlSymbolTable *s_pSymbolTable;
};

class CUtlSymbolTable
{
public:
	// constructor, destructor
	CUtlSymbolTable(int growSize = 0, int initSize = 32, bool caseInsensitive = false);
	~CUtlSymbolTable();

	CUtlSymbol AddString(const char *pString);		// Finds and/or creates a symbol based on the string
	CUtlSymbol Find(const char *pString);			// Finds the symbol for pString

	const char *String(CUtlSymbol id) const;		// Look up the string associated with a particular symbol
	void RemoveAll();								// Remove all symbols in the table

public:
	static bool SymLess(const unsigned int &i1, const unsigned int &i2);
	static bool SymLessi(const unsigned int &i1, const unsigned int &i2);

private:
	const char *StringFromIndex(const UtlSymId_t &index) const;

protected:
	CUtlRBTree<unsigned int, UtlSymId_t> m_Lookup;
	CUtlVector<char> m_StringPools;
};

inline const char *CUtlSymbolTable::StringFromIndex(const UtlSymId_t &index) const
{
	Assert(index < m_StringPools.Count());
	return &m_StringPools[index];
}
