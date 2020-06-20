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

class IEngine
{
public:
	enum
	{
		QUIT_NOTQUITTING = 0,
		QUIT_TODESKTOP,
		QUIT_RESTART
	};

	virtual ~IEngine() {}

	virtual bool Load(bool bDedicated, const char *basedir, const char *cmdline) = 0;
	virtual void Unload() = 0;
	virtual void SetState(int iState) = 0;
	virtual int GetState() = 0;
	virtual void SetSubState(int iSubState) = 0;
	virtual int GetSubState() = 0;

	virtual int Frame() = 0;
	virtual double GetFrameTime() = 0;
	virtual double GetCurTime() = 0;

	virtual void TrapKey_Event(int key, bool down) = 0;
	virtual void TrapMouse_Event(int buttons, bool down) = 0;

	virtual void StartTrapMode() = 0;
	virtual bool IsTrapping() = 0;
	virtual bool CheckDoneTrapping(int &buttons, int &key) = 0;

	virtual int GetQuitting() = 0;
	virtual void SetQuitting(int quittype) = 0;
};

extern IEngine *eng;
