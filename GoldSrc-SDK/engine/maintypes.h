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

#ifndef MAINTYPES_H
#define MAINTYPES_H
#ifdef _WIN32
#pragma once
#endif

#include "osconfig.h"
#include "mathlib/mathlib.h"

#define BIT(n) (1<<(n))

// From engine/pr_comp.h;
typedef unsigned int string_t;

// From engine/server.h
typedef enum sv_delta_s
{
	sv_packet_nodelta,
	sv_packet_delta,
} sv_delta_t;

#endif // #ifndef MAINTYPES_H
