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

class IBaseSystem;
class IBSPModel
{
public:
	virtual ~IBSPModel() {};

	virtual void Init(IBaseSystem *system) = 0;
	virtual void Clear() = 0;
	virtual bool Load(const char *name, bool minimal) = 0;
	virtual bool IsValid() = 0;
	virtual bool IsMinimal() = 0;
	virtual void SetPVS(float *point) = 0;
	virtual bool InPVS(float *point) = 0;
	virtual bool TraceLine(float *start, float *end, float *impact) = 0;
	virtual int TruePointContents(float *point) = 0;
};
