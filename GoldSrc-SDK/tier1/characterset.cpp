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

#include <string.h>
#include "characterset.h"

// Builds a simple lookup table of a group of important characters
// Input  : *pParseGroup - pointer to the buffer for the group
//			*pGroupString - null terminated list of characters to flag
void CharacterSetBuild(characterset_t *pSetBuffer, const char *pszSetString)
{
	int i = 0;

	// Test our pointers
	if (!pSetBuffer || !pszSetString)
		return;

	memset(pSetBuffer->set, 0, sizeof(pSetBuffer->set));

	while (pszSetString[i])
	{
		pSetBuffer->set[pszSetString[i]] = 1;
		i++;
	}
}
