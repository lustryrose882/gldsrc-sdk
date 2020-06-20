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

#if !defined(_WIN32)
#define NO_ERROR 0
#else
#include <WinError.h> // NO_ERROR
#endif

using CRC32_t = unsigned int;

void CRC32_Init(CRC32_t *pulCRC);
CRC32_t CRC32_Final(CRC32_t *pulCRC);
void CRC32_ProcessByte(CRC32_t *pulCRC, unsigned char ch);
void CRC32_ProcessBuffer(CRC32_t *pulCRC, const void *pBuffer, int nBuffer);
CRC32_t	CRC32_GetTableEntry(unsigned int slot);
bool CRC_File(CRC32_t *crcvalue, const char *pchFileName);

inline CRC32_t CRC32_ProcessFile(const char *pchFileName)
{
	CRC32_t crc;
	CRC32_Init(&crc);

	if (!CRC_File(&crc, pchFileName))
	{
		return crc;
	}

	CRC32_Final(&crc);
	return crc;
}

inline CRC32_t CRC32_ProcessSingleBuffer(const void *buf, unsigned int bufLen)
{
	CRC32_t crc;
	CRC32_Init(&crc);
	CRC32_ProcessBuffer(&crc, const_cast<void *>(buf), bufLen);
	CRC32_Final(&crc);

	return crc;
}
