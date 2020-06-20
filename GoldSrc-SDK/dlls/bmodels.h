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

// covering cheesy noise1, noise2, & noise3 fields so they make more sense (for rotating fans)
#define noiseStart   noise1
#define noiseStop    noise2
#define noiseRunning noise3

// This is just a solid wall if not inhibited
class CFuncWall: public CBaseEntity
{
public:
	virtual void Spawn() = 0;

	// Bmodels don't go across transitions
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

#define SF_WALL_TOOGLE_START_OFF BIT(0)
#define SF_WALL_TOOGLE_NOTSOLID  BIT(3)

class CFuncWallToggle: public CFuncWall
{
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

#define SF_CONVEYOR_VISUAL   BIT(0)
#define SF_CONVEYOR_NOTSOLID BIT(1)

class CFuncConveyor: public CFuncWall
{
public:
	virtual void Spawn() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

// A simple entity that looks solid but lets you walk through it.
class CFuncIllusionary: public CBaseToggle
{
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int ObjectCaps() = 0;
};

// Monster only clip brush
//
// This brush will be solid for any entity who has the FL_MONSTERCLIP flag set
// in pev->flags
//
// otherwise it will be invisible and not solid.  This can be used to keep
// specific monsters out of certain areas
class CFuncMonsterClip: public CFuncWall
{
public:
	virtual void Spawn() = 0;

	// Clear out func_wall's use function
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

#define SF_BRUSH_ROTATE_START_ON        BIT(0)
#define SF_BRUSH_ROTATE_BACKWARDS       BIT(1)
#define SF_BRUSH_ROTATE_Z_AXIS          BIT(2)
#define SF_BRUSH_ROTATE_X_AXIS          BIT(3)
#define SF_BRUSH_ACCDCC                 BIT(4) // Brush should accelerate and decelerate when toggled
#define SF_BRUSH_HURT                   BIT(5) // Rotating brush that inflicts pain based on rotation speed
#define SF_BRUSH_ROTATE_NOT_SOLID       BIT(6) // Some special rotating objects are not solid.
#define SF_BRUSH_ROTATE_SMALLRADIUS     BIT(7)
#define SF_BRUSH_ROTATE_MEDIUMRADIUS    BIT(8)
#define SF_BRUSH_ROTATE_LARGERADIUS     BIT(9)

const int MAX_FANPITCH = 100;
const int MIN_FANPITCH = 30;

class CFuncRotating: public CBaseEntity
{
public:
	// basic functions
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Blocked(CBaseEntity *pOther) = 0;
public:

	float m_flFanFriction;
	float m_flAttenuation;
	float m_flVolume;
	float m_pitch;
	int m_sounds;

	Vector m_angles;
};

#define SF_PENDULUM_START_ON    BIT(0)
#define SF_PENDULUM_SWING       BIT(1) // Spawnflag that makes a pendulum a rope swing
#define SF_PENDULUM_PASSABLE    BIT(3)
#define SF_PENDULUM_AUTO_RETURN BIT(4)

class CPendulum: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
	virtual void Blocked(CBaseEntity *pOther) = 0;
public:
	float m_accel;		// Acceleration
	float m_distance;
	float m_time;
	float m_damp;
	float m_maxSpeed;
	float m_dampSpeed;

	Vector m_center;
	Vector m_start;
};
