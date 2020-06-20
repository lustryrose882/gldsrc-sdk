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

class CShower: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
};

#define SF_ENVEXPLOSION_NODAMAGE   BIT(0) // when set, ENV_EXPLOSION will not actually inflict damage
#define SF_ENVEXPLOSION_REPEATABLE BIT(1) // can this entity be refired?
#define SF_ENVEXPLOSION_NOFIREBALL BIT(2) // don't draw the fireball
#define SF_ENVEXPLOSION_NOSMOKE    BIT(3) // don't draw the smoke
#define SF_ENVEXPLOSION_NODECAL    BIT(4) // don't make a scorch mark
#define SF_ENVEXPLOSION_NOSPARKS   BIT(5) // don't make a scorch mark

class CEnvExplosion: public CBaseMonster
{
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	int m_iMagnitude;
	int m_spriteScale;
};
