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

class CCycler: public CBaseMonster
{
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;

	// Don't treat as a live target
	virtual BOOL IsAlive() = 0;
	virtual void Think() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	int m_animate;
};

// We should get rid of all the other cyclers and replace them with this.
class CGenericCycler: public CCycler
{
public:
	virtual void Spawn() = 0;
};

// Probe droid imported for tech demo compatibility
class CCyclerProbe: public CCycler
{
public:
	virtual void Spawn() = 0;
};

class CCyclerSprite: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Think() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	inline int ShouldAnimate() { return (m_animate && m_maxFrame > 1.0f); }
public:
	int m_animate;
	float m_lastTime;
	float m_maxFrame;
	int m_renderfx;
	int m_rendermode;
	float m_renderamt;
	vec3_t m_rendercolor;
};

class CWeaponCycler: public CBasePlayerWeapon
{
public:
	virtual void Spawn() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual BOOL Deploy() = 0;
	virtual void Holster(int skiplocal = 0) = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
public:
	int m_iszModel;
	int m_iModel;
};

// Flaming Wreakage
class CWreckage: public CBaseMonster
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
public:
	int m_flStartTime;
};
