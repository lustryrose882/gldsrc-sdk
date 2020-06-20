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

class CRevertSaved: public CPointEntity
{
public:
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	float Duration() const { return pev->dmg_take; }
	float HoldTime() const { return pev->dmg_save; }
	float MessageTime() const { return m_messageTime; }
	float LoadTime() const { return m_loadTime; }

	void SetDuration(float duration) { pev->dmg_take = duration; }
	void SetHoldTime(float hold) { pev->dmg_save = hold; }
	void SetMessageTime(float time) { m_messageTime = time; }
	void SetLoadTime(float time) { m_loadTime = time; }
public:
	float m_messageTime;
	float m_loadTime;
};
