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

class CHalfLifeTraining: public CHalfLifeMultiplay
{
protected:
	virtual ~CHalfLifeTraining() {};
public:
	virtual BOOL IsMultiplayer() = 0;
	virtual BOOL IsDeathmatch() = 0;
	virtual void InitHUD(CBasePlayer *pl) = 0;
	virtual void PlayerSpawn(CBasePlayer *pPlayer) = 0;
	virtual void PlayerThink(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer) = 0;
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer) = 0;
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) = 0;
	virtual int ItemShouldRespawn(CItem *pItem) = 0;
	virtual void CheckMapConditions() = 0;
	virtual void CheckWinConditions() = 0;
public:
	float FillAccountTime;
	float ServerRestartTime;
	BOOL fInBuyArea;
	BOOL fVisitedBuyArea;
	bool fVGUIMenus;
};

enum GrenCatchType : int
{
	GRENADETYPE_NONE  = 0,
	GRENADETYPE_SMOKE,
	GRENADETYPE_FLASH,
};

class CBaseGrenCatch: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
public:
	GrenCatchType m_NeedGrenadeType;
	string_t sTriggerOnGrenade;
	string_t sDisableOnGrenade;
	bool m_fSmokeTouching;
	bool m_fFlashTouched;
};

const int MAX_ITEM_COUNTS = 32;

class CFuncWeaponCheck: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
private:
	string_t sTriggerWithItems;
	string_t sTriggerNoItems;
	string_t sMaster;
	string_t sItemName[MAX_ITEM_COUNTS];
	int iItemCount;
	int iAnyWeapon;
};
