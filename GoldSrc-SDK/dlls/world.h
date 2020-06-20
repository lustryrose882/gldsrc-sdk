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

#define SF_WORLD_DARK       BIT(0) // Fade from black at startup
#define SF_WORLD_TITLE      BIT(1) // Display game title at startup
#define SF_WORLD_FORCETEAM  BIT(2) // Force teams

// This spawns first when each level begins.
class CWorld: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
};

#define SF_DECAL_NOTINDEATHMATCH BIT(11)

class CDecal: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
};
