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

#include "common/usercmd.h"
#include "pm_shared/pm_movevars.h"
#include "common/ref_params.h"

typedef struct demo_info_s
{
	float timestamp;
	ref_params_t rp;
	usercmd_t cmd;
	movevars_t movevars;
	vec3_t view;
	int viewmodel;
} demo_info_t;

typedef struct demoentry_s
{
	int nEntryType;				// DEMO_STARTUP or DEMO_NORMAL
	char szDescription[64];
	int nFlags;
	int nCDTrack;
	float fTrackTime;			// time of track
	int nFrames;				// # of frames in track
	int nOffset;				// file offset of track data
	int nFileLength;			// length of track
} demoentry_t;

typedef struct demoheader_s
{
	char szFileStamp[8];
	int nDemoProtocol;			// should be DEMO_PROTOCOL
	int nNetProtocolVersion;	// should be PROTOCOL_VERSION
	char szMapName[260];		// name of map
	char szDllDir[260];			// name of game directory
	CRC32_t mapCRC;
	int nDirectoryOffset;		// offset of Entry Directory.
} demoheader_t;

typedef struct demodirectory_s
{
	int nEntries;
	demoentry_t *p_rgEntries;
} demodirectory_t;

typedef struct demoframe_s
{
	float time;
	unsigned int seqnr;
	unsigned char *data;
	void *entities;
	unsigned int entitiesSize;
	unsigned int entitynum;
	void *clientData;
	unsigned int clientDataSize;
	unsigned char *events;
	unsigned int eventsSize;
	unsigned int eventnum;
	unsigned char *reliableData;
	unsigned int reliableDataSize;
	unsigned char *unreliableData;
	unsigned int unreliableDataSize;
	unsigned char *userMessages;
	unsigned int userMessagesSize;
	unsigned char *voiceData;
	unsigned int voiceDataSize;
	unsigned char *demoData;
	unsigned int demoDataSize;
	void *demoInfo;
	unsigned int delta;
} demoframe_t;
