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

#include "common/event_args.h"

typedef struct event_hook_s
{
	struct event_hook_s *next;
	char *name;
	void (*pfnEvent)(struct event_args_s *args);

} event_hook_t;

extern event_hook_t *g_pEventHooks;
