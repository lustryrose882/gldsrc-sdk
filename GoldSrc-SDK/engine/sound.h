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

#include "quakedef.h"

// max number of sentences in game. NOTE: this must match CVOXFILESENTENCEMAX in dlls\util.h!!!
const int CVOXFILESENTENCEMAX = 1536;

typedef struct sfx_s
{
	char name[64];
	cache_user_t cache;
	int servercount;
} sfx_t;

typedef struct sfxcache_s
{
	int length;
	int loopstart;
	int speed;
	int width;
	int stereo;
	byte data[1];
} sfxcache_t;

void S_Init();
void S_AmbientOff();
void S_AmbientOn();
void S_Shutdown();
void S_TouchSound(const char *name);
sfx_t *S_FindName(const char *name, int *pfInCache);
void S_ClearBuffer();
void S_StartStaticSound(int entnum, int entchannel, sfx_t *sfx, vec_t *origin, float vol, float attenuation, int flags, int pitch);
void S_StartDynamicSound(int entnum, int entchannel, sfx_t *sfx, vec_t *origin, float fvol, float attenuation, int flags, int pitch);
void S_StopSound(int entnum, int entchannel);
sfx_t *S_PrecacheSound(const char *name);
void S_ClearPrecache();
void S_Update(vec_t * origin, vec_t * v_forward, vec_t * v_right, vec_t * v_up);
void S_StopAllSounds(qboolean clear);
void S_BeginPrecaching();
void S_EndPrecaching();
void S_ExtraUpdate();
void S_LocalSound(const char *sound);
void S_BlockSound();
void S_UnblockSound();
void S_PrintStats();
qboolean Voice_RecordStart(const char  * pUncompressedFile, const char  * pDecompressedFile, const char  * pMicInputFile);
qboolean Voice_IsRecording();
void Voice_RegisterCvars();
void Voice_Deinit();
void Voice_Idle(float frametime);
qboolean Voice_RecordStop();

extern qboolean g_fUseDInput;
