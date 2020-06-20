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

struct SDL_Window;
class IGame
{
public:
	virtual ~IGame() {}

	virtual bool Init(void *pvInstance) = 0;
	virtual bool Shutdown() = 0;
	virtual bool CreateGameWindow() = 0;
	virtual void SleepUntilInput(int time) = 0;
	virtual SDL_Window *GetMainWindow() const = 0;
	virtual SDL_Window **GetMainWindowAddress() = 0;
	virtual void SetWindowXY(int x, int y) = 0;
	virtual void SetWindowSize(int w, int h) = 0;
	virtual void GetWindowRect(int *x, int *y, int *w, int *h) = 0;
	virtual bool IsActiveApp() const = 0;
	virtual bool IsMultiplayer() const = 0;
	virtual void PlayStartupVideos() = 0;
	virtual void PlayAVIAndWait(const char *aviFile) = 0;
	virtual void SetCursorVisible(bool bState) = 0;
};
