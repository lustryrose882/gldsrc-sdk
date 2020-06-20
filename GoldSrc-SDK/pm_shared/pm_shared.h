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

#define PM_DEAD_VIEWHEIGHT             -8

// Spectator Movement modes (stored in pev->iuser1, so the physics code can get at them)
#define OBS_NONE                        0
#define OBS_CHASE_LOCKED                1
#define OBS_CHASE_FREE                  2
#define OBS_ROAMING                     3
#define OBS_IN_EYE                      4
#define OBS_MAP_FREE                    5
#define OBS_MAP_CHASE                   6

// Spectator modes based on cvar mp_forcechasecam/mp_forcecamera
#define OBS_ANYONE                      0
#define OBS_ONLY_TEAM                   1
#define OBS_ONLY_FIRST_PERSON           2

#define STEP_CONCRETE                   0
#define STEP_METAL                      1
#define STEP_DIRT                       2
#define STEP_VENT                       3
#define STEP_GRATE                      4
#define STEP_TILE                       5
#define STEP_SLOSH                      6
#define STEP_WADE                       7
#define STEP_LADDER                     8
#define STEP_SNOW                       9

#define WJ_HEIGHT                       8
#define STOP_EPSILON                    0.1
#define MAX_CLIMB_SPEED                 200
#define PLAYER_DUCKING_MULTIPLIER       0.333
#define PM_CHECKSTUCK_MINTIME           0.05   // Don't check again too quickly.

#define PLAYER_LONGJUMP_SPEED           350.0f // how fast we longjump

// Ducking time
#define TIME_TO_DUCK                    0.4
#define STUCK_MOVEUP                    1

#define PM_VEC_DUCK_HULL_MIN            -18
#define PM_VEC_HULL_MIN                 -36
#define PM_VEC_DUCK_VIEW                12
#define PM_VEC_VIEW                     17

#define PM_PLAYER_MAX_SAFE_FALL_SPEED   580 // approx 20 feet
#define PM_PLAYER_MIN_BOUNCE_SPEED      350
#define PM_PLAYER_FALL_PUNCH_THRESHHOLD 250 // won't punch player's screen/make scrape noise unless player falling at least this fast.

// Only allow bunny jumping up to 1.2x server / player maxspeed setting
#define BUNNYJUMP_MAX_SPEED_FACTOR      1.2f

void PM_Init(struct playermove_s *ppmove);
void PM_Move(struct playermove_s *ppmove, int server);
char PM_FindTextureType(const char *name);
void PM_AirMove();

int PM_GetPhysEntInfo(int ent);
qboolean PM_IsThereGrassTexture();

#ifdef HOOK_CLIENT
#define iJumpSpectator  (*piJumpSpectator)
#define vJumpOrigin     (*pvJumpOrigin)
#define vJumpAngles     (*pvJumpAngles)
#endif

#if defined(_CLIENT) || defined(CLIENT_DLL)
extern int iJumpSpectator;
extern float vJumpOrigin[3];
extern float vJumpAngles[3];
#endif // #if defined(_CLIENT) || defined(CLIENT_DLL)

extern struct playermove_s *pmove;
