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

#ifndef SIMPLE_CHECKSUM_H
#define SIMPLE_CHECKSUM_H
#ifdef _WIN32
#pragma once
#endif

// Compute a simple checksum for the given data.
// Each byte in the data is multiplied by its position to track re-ordering changes
inline unsigned int ComputeSimpleChecksum(const unsigned char *dataPointer, int dataLength)
{
	unsigned int checksum = 0;
	for (int i = 1; i <= dataLength; i++)
	{
		checksum += (*dataPointer) * i;
		++dataPointer;
	}

	return checksum;
}

#endif // SIMPLE_CHECKSUM_H
