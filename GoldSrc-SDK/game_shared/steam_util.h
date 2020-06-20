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

class SteamFile
{
public:
	SteamFile(const char *filename);
	~SteamFile();

	bool IsValid() const { return (m_fileData) ? true : false; }
	bool Read(void *data, int length);

private:
	byte *m_fileData;
	int m_fileDataLength;

	byte *m_cursor;
	int m_bytesLeft;
};

inline SteamFile::SteamFile(const char *filename)
{
	m_fileData = (byte *)LOAD_FILE_FOR_ME(const_cast<char *>(filename), &m_fileDataLength);
	m_cursor = m_fileData;
	m_bytesLeft = m_fileDataLength;
}

inline SteamFile::~SteamFile()
{
	if (m_fileData)
	{
		FREE_FILE(m_fileData);
		m_fileData = NULL;
	}
}

inline bool SteamFile::Read(void *data, int length)
{
	if (length > m_bytesLeft || m_cursor == NULL || m_bytesLeft <= 0)
		return false;

	byte *readCursor = static_cast<byte *>(data);
	for (int i = 0; i < length; ++i)
	{
		*readCursor++ = *m_cursor++;
		--m_bytesLeft;
	}

	return true;
}
