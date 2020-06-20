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

#include "hud_iface.h"

#define PLAYER_CAN_SHOOT			(1<<0)
#define PLAYER_FREEZE_TIME_OVER		(1<<1)
#define PLAYER_IN_BOMB_ZONE			(1<<2)
#define PLAYER_HOLDING_SHIELD		(1<<3)
#define PLAYER_PREVENT_DUCK			(1<<4)
#define PLAYER_PREVENT_CLIMB		(1<<5) // The player can't climb ladder

#define ACCURACY_AIR				(1<<0) // accuracy depends on FL_ONGROUND
#define ACCURACY_SPEED				(1<<1)
#define ACCURACY_DUCK				(1<<2) // more accurate when ducking
#define ACCURACY_MULTIPLY_BY_14		(1<<3) // accuracy multiply to 1.4
#define ACCURACY_MULTIPLY_BY_14_2	(1<<4) // accuracy multiply to 1.4

#define WPNSTATE_USP_SILENCED		(1<<0)
#define WPNSTATE_GLOCK18_BURST_MODE	(1<<1)
#define WPNSTATE_M4A1_SILENCED		(1<<2)
#define WPNSTATE_ELITE_LEFT			(1<<3)
#define WPNSTATE_FAMAS_BURST_MODE	(1<<4)
#define WPNSTATE_SHIELD_DRAWN		(1<<5)

void COM_Log(char *pszFile, char *fmt, ...);

float UTIL_SharedRandomFloat(unsigned int seed, float low, float high);
int UTIL_SharedRandomLong(unsigned int seed, int low, int high);

#ifdef __cplusplus
extern "C" {
#endif

CL_DLLEXPORT int HUD_GetWeaponAnim();
CL_DLLEXPORT void HUD_SendWeaponAnim(int iAnim, int iWeaponId, int iBody, int iForce = 0);
CL_DLLEXPORT int HUD_GetWeapon();
CL_DLLEXPORT void HUD_PlaySound(char *sound, float volume);
CL_DLLEXPORT void HUD_PlaybackEvent(int flags, const struct edict_s *pInvoker, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);
CL_DLLEXPORT void HUD_SetMaxSpeed(const struct edict_s *ed, float speed);

#ifdef __cplusplus
}
#endif

int stub_PrecacheModel(const char *s);
int stub_PrecacheSound(const char *s);
unsigned short stub_PrecacheEvent(int type, const char *s);
const char *stub_NameForFunction(unsigned int function);
void stub_SetModel(struct edict_s *e, const char *m);
edict_t *stub_PEntityOfEntOffset(int iEntOffset);

int GetWeaponAccuracyFlags(int weaponid);

extern cvar_t *cl_lw;

extern int g_runfuncs;
extern vec3_t v_angles;
extern float g_lastFOV;
extern bool g_bInBombZone;
extern int g_iFreezeTimeOver;
extern int g_iWaterLevel;
extern bool g_bHoldingShield;
extern bool g_bHoldingKnife;
extern vec3_t g_vPlayerVelocity;
extern struct local_state_s *g_curstate;
extern struct local_state_s *g_finalstate;
extern int g_currentanim;
extern int g_currentweapon;
