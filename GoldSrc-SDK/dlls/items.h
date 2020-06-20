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

enum ItemRestType
{
	ITEM_TYPE_BUYING,  // When a player is buying items
	ITEM_TYPE_TOUCHED, // When the player touches with a weaponbox or armoury_entity
	ITEM_TYPE_EQUIPPED // When an entity game_player_equip gives item to player or default items on player spawn
};

// Constant items
#define ITEM_ID_ANTIDOTE 2
#define ITEM_ID_SECURITY 3

enum ItemID
{
	ITEM_NONE = -1,
	ITEM_SHIELDGUN,
	ITEM_P228,
	ITEM_GLOCK,
	ITEM_SCOUT,
	ITEM_HEGRENADE,
	ITEM_XM1014,
	ITEM_C4,
	ITEM_MAC10,
	ITEM_AUG,
	ITEM_SMOKEGRENADE,
	ITEM_ELITE,
	ITEM_FIVESEVEN,
	ITEM_UMP45,
	ITEM_SG550,
	ITEM_GALIL,
	ITEM_FAMAS,
	ITEM_USP,
	ITEM_GLOCK18,
	ITEM_AWP,
	ITEM_MP5N,
	ITEM_M249,
	ITEM_M3,
	ITEM_M4A1,
	ITEM_TMP,
	ITEM_G3SG1,
	ITEM_FLASHBANG,
	ITEM_DEAGLE,
	ITEM_SG552,
	ITEM_AK47,
	ITEM_KNIFE,
	ITEM_P90,
	ITEM_NVG,
	ITEM_DEFUSEKIT,
	ITEM_KEVLAR,
	ITEM_ASSAULT,
	ITEM_LONGJUMP,
	ITEM_SODACAN,
	ITEM_HEALTHKIT,
	ITEM_ANTIDOTE,
	ITEM_BATTERY
};

class CItem: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual CBaseEntity *Respawn() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CWorldItem: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
public:
	int m_iType;
};

class CItemSuit: public CItem
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemBattery: public CItem
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemAntidote: public CItem
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemSecurity: public CItem
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemLongJump: public CItem
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemKevlar: public CItem
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemAssaultSuit: public CItem
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemThighPack: public CItem
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};
