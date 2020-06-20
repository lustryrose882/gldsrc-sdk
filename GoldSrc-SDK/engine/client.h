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

#include "maintypes.h"
#include "common.h"
#include "custom.h"
#include "cl_entity.h"
#include "consistency.h"
#include "delta_packet.h"
#include "dlight.h"
#include "entity_state.h"
#include "entity_types.h"
#include "event.h"
#include "info.h"
#include "net.h"
#include "keys.h"
#include "screenfade.h"
#include "usercmd.h"
#include "model.h"
#include "sound.h"
#include "kbutton.h"
#include "userid.h"

const int MAX_SCOREBOARDNAME = 32;
const int MAX_HASHID_LENGTH = 16;
const int MAX_DEMOS = 32;

const int MAX_EFRAGS = 640;
const int MAX_TEMP_ENTITIES = 500; // lightning bolts, etc
const int MAX_STATIC_ENTITIES = 32; // torches, etc
const int MAX_VISEDICTS = 512;

typedef enum cactive_e
{
	ca_dedicated,
	ca_disconnected,	// not talking to a server
	ca_connecting,		// sending request packets to the server
	ca_connected,		// netchan_t established, waiting for svc_serverinfo
	ca_uninitialized,
	ca_active,			// game views should be displayed
} cactive_t;

typedef struct cmd_s
{
	usercmd_t cmd;
	float senttime;
	float receivedtime;
	float frame_lerp;
	qboolean processedfuncs;
	qboolean heldback;
	int sendsize;
} cmd_t;

typedef struct frame_s
{
	double receivedtime;
	double latency;
	qboolean invalid;
	qboolean choked;
	entity_state_t playerstate[32];
	double time;
	clientdata_t clientdata;
	weapon_data_t weapondata[64];
	packet_entities_t packet_entities;
	uint16_t clientbytes;
	uint16_t playerinfobytes;
	uint16_t packetentitybytes;
	uint16_t tentitybytes;
	uint16_t soundbytes;
	uint16_t eventbytes;
	uint16_t usrbytes;
	uint16_t voicebytes;
	uint16_t msgbytes;
} frame_t;

typedef struct
{
	int		destcolor[3];
	int		percent;		// 0-256
} cshift_t;

#define	CSHIFT_CONTENTS	0
#define	CSHIFT_DAMAGE	1
#define	CSHIFT_BONUS	2
#define	CSHIFT_POWERUP	3
#define	NUM_CSHIFTS		4

typedef struct player_info_s
{
	// User id on server
	int userid;

	// User info string
	char userinfo[MAX_INFO_STRING];

	// Name
	char name[MAX_SCOREBOARDNAME];

	// Spectator or not, unused
	qboolean spectator;

	int ping;
	qboolean packet_loss;

	// skin information
	char model[MAX_QPATH];
	int topcolor;
	int bottomcolor;

	// last frame rendered
	int renderframe;

	// Gait frame estimation
	int gaitsequence;
	float gaitframe;
	float gaityaw;
	vec3_t prevgaitorigin;

	customization_t customdata;
	char hashedcdkey[MAX_HASHID_LENGTH];
	uint64_t m_nSteamID;
} player_info_t;

typedef struct soundfade_s
{
	int nStartPercent;
	int nClientSoundFadePercent;
	double soundFadeStartTime;
	int soundFadeOutTime;
	int soundFadeHoldTime;
	int soundFadeInTime;
} soundfade_t;

#define	SIGNONS 2 // signon messages to receive before connected

typedef struct client_static_s
{
	cactive_t state;
	netchan_t netchan;
	sizebuf_t datagram;
	byte datagram_buf[MAX_DATAGRAM];
	double connect_time;
	int connect_retry;
	int challenge;
	byte authprotocol;
	int userid;
	char trueaddress[32];
	float slist_time;
	int signon;
	char servername[MAX_PATH];
	char mapstring[64];
	char spawnparms[2048];
	char userinfo[256];
	float nextcmdtime;
	int lastoutgoingcommand;
	int demonum;
	char demos[MAX_DEMOS][16];
	qboolean demorecording;
	qboolean demoplayback;
	qboolean timedemo;
	float demostarttime;
	int demostartframe;
	int forcetrack;
	FileHandle_t demofile;
	FileHandle_t demoheader;
	qboolean demowaiting;
	qboolean demoappending;
	char demofilename[MAX_PATH];
	int demoframecount;
	int td_lastframe;
	int td_startframe;
	float td_starttime;
	incomingtransfer_t dl;
	float packet_loss;
	double packet_loss_recalc_time;
	int playerbits;
	soundfade_t soundfade;
	char physinfo[MAX_PHYSINFO_STRING];
	unsigned char md5_clientdll[16];
	netadr0_t game_stream;
	netadr0_t connect_stream;
	qboolean passive;
	qboolean spectator;
	qboolean director;
	qboolean fSecureClient;
	qboolean isVAC2Secure;
	uint64_t GameServerSteamID;
	int build_num;
} client_static_t;

typedef struct client_state_s
{
	int max_edicts;
	resource_t resourcesonhand;
	resource_t resourcesneeded;
	resource_t resourcelist[MAX_RESOURCE_LIST];
	int num_resources;
	qboolean need_force_consistency_response;
	char serverinfo[512];
	int servercount;
	int validsequence;
	int parsecount;
	int parsecountmod;
	int stats[32];
	int weapons;
	usercmd_t cmd;
	vec3_t viewangles;
	vec3_t punchangle;
	vec3_t crosshairangle;
	vec3_t simorg;
	vec3_t simvel;
	vec3_t simangles;
	vec3_t predicted_origins[64];
	vec3_t prediction_error;
	float idealpitch;
	vec3_t viewheight;
	screenfade_t sf;
	qboolean paused;
	int onground;
	int moving;
	int waterlevel;
	int usehull;
	float maxspeed;
	int pushmsec;
	int light_level;
	int intermission;
	double mtime[2];
	double time;
	double oldtime;
	frame_t frames[64];
	cmd_t commands[64];
	local_state_t predicted_frames[64];
	int delta_sequence;
	int playernum;
	event_t event_precache[MAX_EVENTS];
	model_t *model_precache[MAX_MODELS];
	int model_precache_count;
	sfx_s *sound_precache[MAX_SOUNDS];
	consistency_t consistency_list[MAX_CONSISTENCY_LIST];
	int num_consistency;
	int highentity;
	char levelname[40];
	int maxclients;
	int gametype;
	int viewentity;
	model_t *worldmodel;
	efrag_t *free_efrags;
	int num_entities;
	int num_statics;
	cl_entity_t viewent;
	int cdtrack;
	int looptrack;
	CRC32_t serverCRC;
	unsigned char clientdllmd5[16];
	float weaponstarttime;
	int weaponsequence;
	int fPrecaching;
	dlight_t *pLight;
	player_info_t players[MAX_CLIENTS];
	entity_state_t instanced_baseline[64];
	int instanced_baseline_number;
	CRC32_t mapCRC;
	event_state_t events;
	char downloadUrl[128];
} client_state_t;

#include "delta_packet.h"

typedef struct client_frame_s
{
	double senttime;
	float ping_time;
	clientdata_t clientdata;
	weapon_data_t weapondata[64];
	packet_entities_t entities;
} client_frame_t;

typedef struct client_s
{
	qboolean active;
	qboolean spawned;
	qboolean fully_connected;
	qboolean connected;
	qboolean uploading;
	qboolean hasusrmsgs;
	qboolean has_force_unmodified;
	netchan_t netchan;
	int chokecount;
	int delta_sequence;
	qboolean fakeclient;
	qboolean proxy;
	usercmd_t lastcmd;
	double connecttime;
	double cmdtime;
	double ignorecmdtime;
	float latency;
	float packet_loss;
	double localtime;
	double nextping;
	double svtimebase;
	sizebuf_t datagram;
	byte datagram_buf[MAX_DATAGRAM];
	double connection_started;
	double next_messagetime;
	double next_messageinterval;
	qboolean send_message;
	qboolean skip_message;
	client_frame_t *frames;
	event_state_t events;
	edict_t *edict;
	const edict_t *pViewEntity;
	int userid;
	USERID_t network_userid;
	char userinfo[MAX_INFO_STRING];
	qboolean sendinfo;
	float sendinfo_time;
	char hashedcdkey[64];
	char name[32];
	int topcolor;
	int bottomcolor;
	int entityId;
	resource_t resourcesonhand;
	resource_t resourcesneeded;
	FileHandle_t upload;
	qboolean uploaddoneregistering;
	customization_t customdata;
	int crcValue;
	int lw;
	int lc;
	char physinfo[MAX_INFO_STRING];
	qboolean m_bLoopback;
	uint32_t m_VoiceStreams[2];
	double m_lastvoicetime;
	int m_sendrescount;
} client_t;

typedef enum CareerStateType_e
{
	CAREER_NONE = 0,
	CAREER_LOADING = 1,
	CAREER_PLAYING = 2,
} CareerStateType;

#ifdef __cplusplus
extern "C" {
#endif

void CL_RecordHUDCommand(const char *cmdname);
void R_DecalRemoveAll(int textureIndex);
void CL_CheckForResend();
qboolean CL_CheckFile(sizebuf_t *msg, char *filename);
void CL_ClearClientState();
void CL_Connect_f();
void CL_DecayLights();
void CL_Disconnect();
void CL_Disconnect_f();
void CL_EmitEntities();
void CL_InitClosest();
void CL_Init();
void CL_Particle(vec_t *origin, int color, float life, int zpos, int zvel);
void CL_PredictMove(qboolean repredicting);
void CL_PrintLogos();
void CL_ReadPackets();
qboolean CL_RequestMissingResources();
void CL_Move();
void CL_SendConnectPacket();
void CL_StopPlayback();
void CL_UpdateSoundFade();
void CL_AdjustClock();
void CL_Save(const char *name);
void CL_HudMessage(const char *pMessage);

void ClientDLL_UpdateClientData();
void ClientDLL_HudVidInit();
void Chase_Init();
void Chase_Update();
void ClientDLL_Init();
void Con_Shutdown();
int DispatchDirectUserMsg(const char *pszName, int iSize, void *pBuf);
void CL_ShutDownUsrMessages();
void CL_ShutDownClientStatic();
void ClientDLL_MoveClient(struct playermove_s *ppmove);
void CL_Shutdown();
void ClientDLL_Frame(double time);
void ClientDLL_CAM_Think();
void CL_CheckClientState();
void CL_RedoPrediction();
void CL_SetLastUpdate();
void Con_NPrintf(int idx, const char *fmt, ...);
void CL_WriteMessageHistory(int starting_count, int cmd);
void CL_MoveSpectatorCamera();
void CL_AddVoiceToDatagram(qboolean bFinal);
void CL_VoiceIdle();
void PollDInputDevices();
void CL_KeepConnectionActive();
void CL_UpdateModuleC();

#ifdef __cplusplus
}
#endif
