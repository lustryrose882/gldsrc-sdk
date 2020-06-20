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

const float DOOR_SENTENCEWAIT   = 6.0f;
const float DOOR_SOUNDWAIT      = 3.0f;
const float BUTTON_SOUNDWAIT    = 0.5f;

#define SF_DOOR_START_OPEN          BIT(0)
#define SF_DOOR_PASSABLE            BIT(3)
#define SF_DOOR_NO_AUTO_RETURN      BIT(5)
#define SF_DOOR_USE_ONLY            BIT(8)  // Door must be opened by player's use button.
#define SF_DOOR_TOUCH_ONLY_CLIENTS  BIT(10) // Only clients can touch
#define SF_DOOR_ACTUALLY_WATER      BIT(31) // This bit marks that func_door are actually func_water

class CBaseDoor: public CBaseToggle
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void SetToggleState(int state) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void Blocked(CBaseEntity *pOther) = 0;
public:
	byte m_bHealthValue;		// some doors are medi-kit doors, they give players health
	byte m_bMoveSnd;			// sound a door makes while moving
	byte m_bStopSnd;			// sound a door makes when it stops

	locksound_t m_ls;			// door lock sounds

	byte m_bLockedSound;		// ordinals from entity selection
	byte m_bLockedSentence;
	byte m_bUnlockedSound;
	byte m_bUnlockedSentence;

	float m_lastBlockedTimestamp;
};

#define SF_DOOR_ROTATE_BACKWARDS BIT(1)
#define SF_DOOR_ROTATE_ONEWAY    BIT(4)
#define SF_DOOR_ROTATE_Z         BIT(6)
#define SF_DOOR_ROTATE_X         BIT(7)

class CRotDoor: public CBaseDoor
{
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual void SetToggleState(int state) = 0;
};

class CMomentaryDoor: public CBaseToggle
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	byte m_bMoveSnd;	// sound a door makes while moving
};
