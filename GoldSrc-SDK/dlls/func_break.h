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

enum Explosions
{
	expRandom = 0,
	expDirected,
};

enum Materials
{
	matGlass = 0,
	matWood,
	matMetal,
	matFlesh,
	matCinderBlock,
	matCeilingTile,
	matComputer,
	matUnbreakableGlass,
	matRocks,
	matNone,
	matLastMaterial,
};

// this many shards spawned when breakable objects break
#define NUM_SHARDS            6      // this many shards spawned when breakable objects break

// func breakable
#define SF_BREAK_TRIGGER_ONLY BIT(0) // may only be broken by trigger
#define SF_BREAK_TOUCH        BIT(1) // can be 'crashed through' by running player (plate glass)
#define SF_BREAK_PRESSURE     BIT(2) // can be broken by a player standing on it
#define SF_BREAK_CROWBAR      BIT(8) // instant break if hit with crowbar

class CBreakable: public CBaseDelay
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

	// To spark when hit
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) = 0;

	// breakables use an overridden takedamage
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;

	virtual int DamageDecal(int bitsDamageType) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;

public:
	BOOL Explodable() const { return ExplosionMagnitude() > 0; }
	int ExplosionMagnitude() const { return pev->impulse; }
	void ExplosionSetMagnitude(int magnitude) { pev->impulse = magnitude; }

public:
	Materials m_Material;
	Explosions m_Explosion;
	int m_idShard;
	float m_angle;
	int m_iszGibModel;
	int m_iszSpawnObject;
	float m_flHealth;
};

#define SF_PUSH_BREAKABLE BIT(7) // func_pushable (it's also func_breakable, so don't collide with those flags)

class CPushable: public CBreakable
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;

public:
	float MaxSpeed() const { return m_maxSpeed; }

public:
	int m_lastSound;
	float m_maxSpeed;
	float m_soundTime;
};
