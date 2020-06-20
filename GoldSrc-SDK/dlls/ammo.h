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

class C9MMAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};

class CBuckShotAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};

class C556NatoAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};

class C556NatoBoxAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};

class C762NatoAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};

class C45ACPAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};

class C50AEAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};

class C338MagnumAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};

class C57MMAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};

class C357SIGAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL AddAmmo(CBaseEntity *pOther) = 0;
};
