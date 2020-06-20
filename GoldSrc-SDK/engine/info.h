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

#include "maintypes.h"

// Max key/value length (with a NULL char)
const int MAX_KV_LEN             = 127;

// Key + value + 2 x slash + NULL
const int MAX_INFO_STRING        = 256;
const int INFO_MAX_BUFFER_VALUES = 4;
const int MAX_LOCALINFO          = MAX_INFO_STRING * 128;

const char *Info_ValueForKey(const char *s, const char *lookup);
void Info_RemoveKey(char *s, const char *lookup);
void Info_RemovePrefixedKeys(char *s, const char prefix);
qboolean Info_IsKeyImportant(const char *key);
qboolean Info_IsKeyImportant(const char *key, size_t keyLen);
const char *Info_FindLargestKey(const char *s, size_t maxsize);
qboolean Info_SetValueForStarKey(char *s, const char *key, const char *value, size_t maxsize);
void Info_SetValueForKey(char *s, const char *key, const char *value, int maxsize);
void Info_Print(const char *s);
qboolean Info_IsValid(const char *s);
void Info_SetFieldsToTransmit();
void Info_CollectFields(char *destInfo, const char *srcInfo, size_t maxsize);
