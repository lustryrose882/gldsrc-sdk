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

#include "archtypes.h"

const int MAX_CMD_BUFFER     = 16384;
const int MAX_CMD_TOKENS     = 80;
const int MAX_CMD_LINE       = 1024;
const int MAX_CMDLIST_FILES  = 100;

typedef enum cmd_source_s
{
	src_client = 0,		// came in over a net connection as a clc_stringcmd. host_client will be valid during this state.
	src_command = 1,	// from the command buffer.
} cmd_source_t;

#define FCMD_HUD_COMMAND		BIT(0)
#define FCMD_GAME_COMMAND		BIT(1)
#define FCMD_WRAPPER_COMMAND	BIT(2)
#define FCMD_FILTERED_COMMAND	BIT(3)
#define FCMD_RESTRICTED_COMMAND	BIT(4)

using xcommand_t = void (*)();

typedef struct cmd_function_s
{
	struct cmd_function_s *next;
	const char *name;
	xcommand_t function;
	int flags;
} cmd_function_t;
