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

#include "gib.h"
#include "activity.h"

enum
{
	ITBD_PARALLYZE = 0,
	ITBD_NERVE_GAS,
	ITBD_POISON,
	ITBD_RADIATION,
	ITBD_DROWN_RECOVER,
	ITBD_ACID,
	ITBD_SLOW_BURN,
	ITBD_SLOW_FREEZE,
	ITBD_END
};

enum MONSTERSTATE
{
	MONSTERSTATE_NONE = 0,
	MONSTERSTATE_IDLE,
	MONSTERSTATE_COMBAT,
	MONSTERSTATE_ALERT,
	MONSTERSTATE_HUNT,
	MONSTERSTATE_PRONE,
	MONSTERSTATE_SCRIPT,
	MONSTERSTATE_PLAYDEAD,
	MONSTERSTATE_DEAD
};

class CBaseToggle;
class CBaseMonster: public CBaseToggle
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	virtual BOOL TakeHealth(float flHealth, int bitsDamageType);
	virtual void Killed(entvars_t *pevAttacker, int iGib);
	virtual int BloodColor() { return m_bloodColor; }
	virtual BOOL IsAlive() { return (pev->deadflag != DEAD_DEAD); }
	virtual float ChangeYaw(int speed);
	virtual BOOL HasHumanGibs();
	virtual BOOL HasAlienGibs();
	virtual void FadeMonster();
	virtual void GibMonster();
	virtual Activity GetDeathActivity();
	virtual void BecomeDead();
	virtual BOOL ShouldFadeOnDeath();
	virtual int IRelationship(CBaseEntity *pTarget);
	virtual void PainSound() {}
	virtual void ResetMaxSpeed() {}
	virtual void ReportAIState() {}
	virtual void MonsterInitDead();
	virtual void Look(int iDistance);
	virtual CBaseEntity *BestVisibleEnemy();
	virtual BOOL FInViewCone(CBaseEntity *pEntity);
	virtual BOOL FInViewCone(const Vector *pOrigin);

public:
	void SetConditions(int iConditions) { m_afConditions |= iConditions; }
	void ClearConditions(int iConditions) { m_afConditions &= ~iConditions; }
	BOOL HasConditions(int iConditions) { return (m_afConditions & iConditions) ? TRUE : FALSE; }
	BOOL HasAllConditions(int iConditions) { return ((m_afConditions & iConditions) == iConditions) ? TRUE : FALSE; }

	void Remember(int iMemory) { m_afMemory |= iMemory; }
	void Forget(int iMemory) { m_afMemory &= ~iMemory; }
	BOOL HasMemory(int iMemory) { return (m_afMemory & iMemory) ? TRUE : FALSE; }
	BOOL HasAllMemories(int iMemory) { return ((m_afMemory & iMemory) == iMemory) ? TRUE : FALSE; }

	void StopAnimation() { pev->framerate = 0.0f; }
public:
	Activity m_Activity;			// what the monster is doing (animation)
	Activity m_IdealActivity;		// monster should switch to this activity
	int m_LastHitGroup;				// the last body region that took damage
	int m_bitsDamageType;			// what types of damage has monster (player) taken
	byte m_rgbTimeBasedDamage[ITBD_END];

	MONSTERSTATE m_MonsterState;		// monster's current state
	MONSTERSTATE m_IdealMonsterState;	// monster should change to this state
	int m_afConditions;
	int m_afMemory;

	float m_flNextAttack;	// cannot attack again until this time
	EHANDLE m_hEnemy;		// the entity that the monster is fighting.
	EHANDLE m_hTargetEnt;	// the entity that the monster is trying to reach
	float m_flFieldOfView;	// width of monster's field of view (dot product)
	int m_bloodColor;		// color of blood particless
	Vector m_HackedGunPos;	// HACK until we can query end of gun
	Vector m_vecEnemyLKP;	// last known position of enemy. (enemy's origin)
};
