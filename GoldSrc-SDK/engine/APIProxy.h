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

#include "netadr.h"
#include "Sequence.h"
#include "color.h"

#ifndef _WIN32
#include "enums.h"
#endif

const int MAX_ALIAS_NAME = 32;

typedef struct cmdalias_s
{
	struct cmdalias_s	*next;
	char	name[MAX_ALIAS_NAME];
	char	*value;
} cmdalias_t;

#include "common/con_nprint.h"

// ********************************************************
// Functions exported by the client .dll
// ********************************************************

// Function type declarations for client exports
typedef int					(*INITIALIZE_FUNC)					(struct cl_enginefuncs_s*, int);
typedef void				(*HUD_INIT_FUNC)					();
typedef int					(*HUD_VIDINIT_FUNC)					();
typedef int					(*HUD_REDRAW_FUNC)					(float, int);
typedef int					(*HUD_UPDATECLIENTDATA_FUNC)		(struct client_data_s*, float);
typedef void				(*HUD_RESET_FUNC)					();
typedef void				(*HUD_CLIENTMOVE_FUNC)				(struct playermove_s *ppmove, qboolean server);
typedef void				(*HUD_CLIENTMOVEINIT_FUNC)			(struct playermove_s *ppmove);
typedef char				(*HUD_TEXTURETYPE_FUNC)				(const char *name);
typedef void				(*HUD_IN_ACTIVATEMOUSE_FUNC)		();
typedef void				(*HUD_IN_DEACTIVATEMOUSE_FUNC)		();
typedef void				(*HUD_IN_MOUSEEVENT_FUNC)			(int mstate);
typedef void				(*HUD_IN_CLEARSTATES_FUNC)			();
typedef void				(*HUD_IN_ACCUMULATE_FUNC)			();
typedef void				(*HUD_CL_CREATEMOVE_FUNC)			(float frametime, struct usercmd_s *cmd, int active);
typedef qboolean			(*HUD_CL_ISTHIRDPERSON_FUNC)		();
typedef void				(*HUD_CL_GETCAMERAOFFSETS_FUNC)		(float *ofs);
typedef struct kbutton_s *	(*HUD_KB_FIND_FUNC)					(const char *name);
typedef void				(*HUD_CAMTHINK_FUNC)				();
typedef void				(*HUD_CALCREF_FUNC)					(struct ref_params_s *pparams);
typedef qboolean			(*HUD_ADDENTITY_FUNC)				(int type, struct cl_entity_s *ent, const char *modelname);
typedef void				(*HUD_CREATEENTITIES_FUNC)			();
typedef void				(*HUD_DRAWNORMALTRIS_FUNC)			();
typedef void				(*HUD_DRAWTRANSTRIS_FUNC)			();
typedef void				(*HUD_STUDIOEVENT_FUNC)				(const struct mstudioevent_s *event, const struct cl_entity_s *entity);
typedef void				(*HUD_POSTRUNCMD_FUNC)				(struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed);
typedef void				(*HUD_SHUTDOWN_FUNC)				();
typedef void				(*HUD_TXFERLOCALOVERRIDES_FUNC)		(struct entity_state_s *state, const struct clientdata_s *client);
typedef void				(*HUD_PROCESSPLAYERSTATE_FUNC)		(struct entity_state_s *dst, const struct entity_state_s *src);
typedef void				(*HUD_TXFERPREDICTIONDATA_FUNC)		(struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd);
typedef void				(*HUD_DEMOREAD_FUNC)				(int size, unsigned char *buffer);
typedef qboolean			(*HUD_CONNECTIONLESS_FUNC)			(const struct netadr0_s *net_from_, const char *args, char *response_buffer, int *response_buffer_size);
typedef qboolean			(*HUD_GETHULLBOUNDS_FUNC)			(int hullnumber, float *mins, float *maxs);
typedef void				(*HUD_FRAME_FUNC)					(double);
typedef qboolean			(*HUD_KEY_EVENT_FUNC)				(int eventcode, int keynum, const char *pszCurrentBinding);
typedef void				(*HUD_TEMPENTUPDATE_FUNC)			(double frametime, double client_time, double cl_gravity, struct tempent_s **ppTempEntFree, struct tempent_s **ppTempEntActive, int(*Callback_AddVisibleEntity)(struct cl_entity_s *pEntity), void(*Callback_TempEntPlaySound)(struct tempent_s *pTemp, float damp));
typedef struct cl_entity_s *(*HUD_GETUSERENTITY_FUNC)			(int index);
typedef void				(*HUD_VOICESTATUS_FUNC)				(int entindex, qboolean bTalking);
typedef void				(*HUD_DIRECTORMESSAGE_FUNC)			(int iSize, void *pbuf);
typedef int					(*HUD_STUDIO_INTERFACE_FUNC)		(int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio);
typedef void				(*HUD_CHATINPUTPOSITION_FUNC)		(int *x, int *y);
typedef int					(*HUD_GETPLAYERTEAM)				(int iplayer);
typedef void *				(*CLIENTFACTORY)					(); // this should be CreateInterfaceFn but that means including interface.h
																	// which is a C++ file and some of the client files a C only...
																	// so we return a void * which we then do a typecast on later.


// Pointers to the exported client functions themselves
typedef struct
{
	INITIALIZE_FUNC						pInitFunc;
	HUD_INIT_FUNC						pHudInitFunc;
	HUD_VIDINIT_FUNC					pHudVidInitFunc;
	HUD_REDRAW_FUNC						pHudRedrawFunc;
	HUD_UPDATECLIENTDATA_FUNC			pHudUpdateClientDataFunc;
	HUD_RESET_FUNC						pHudResetFunc;
	HUD_CLIENTMOVE_FUNC					pClientMove;
	HUD_CLIENTMOVEINIT_FUNC				pClientMoveInit;
	HUD_TEXTURETYPE_FUNC				pClientTextureType;
	HUD_IN_ACTIVATEMOUSE_FUNC			pIN_ActivateMouse;
	HUD_IN_DEACTIVATEMOUSE_FUNC			pIN_DeactivateMouse;
	HUD_IN_MOUSEEVENT_FUNC				pIN_MouseEvent;
	HUD_IN_CLEARSTATES_FUNC				pIN_ClearStates;
	HUD_IN_ACCUMULATE_FUNC				pIN_Accumulate;
	HUD_CL_CREATEMOVE_FUNC				pCL_CreateMove;
	HUD_CL_ISTHIRDPERSON_FUNC			pCL_IsThirdPerson;
	HUD_CL_GETCAMERAOFFSETS_FUNC		pCL_GetCameraOffsets;
	HUD_KB_FIND_FUNC					pFindKey;
	HUD_CAMTHINK_FUNC					pCamThink;
	HUD_CALCREF_FUNC					pCalcRefdef;
	HUD_ADDENTITY_FUNC					pAddEntity;
	HUD_CREATEENTITIES_FUNC				pCreateEntities;
	HUD_DRAWNORMALTRIS_FUNC				pDrawNormalTriangles;
	HUD_DRAWTRANSTRIS_FUNC				pDrawTransparentTriangles;
	HUD_STUDIOEVENT_FUNC				pStudioEvent;
	HUD_POSTRUNCMD_FUNC					pPostRunCmd;
	HUD_SHUTDOWN_FUNC					pShutdown;
	HUD_TXFERLOCALOVERRIDES_FUNC		pTxferLocalOverrides;
	HUD_PROCESSPLAYERSTATE_FUNC			pProcessPlayerState;
	HUD_TXFERPREDICTIONDATA_FUNC		pTxferPredictionData;
	HUD_DEMOREAD_FUNC					pReadDemoBuffer;
	HUD_CONNECTIONLESS_FUNC				pConnectionlessPacket;
	HUD_GETHULLBOUNDS_FUNC				pGetHullBounds;
	HUD_FRAME_FUNC						pHudFrame;
	HUD_KEY_EVENT_FUNC					pKeyEvent;
	HUD_TEMPENTUPDATE_FUNC				pTempEntUpdate;
	HUD_GETUSERENTITY_FUNC				pGetUserEntity;
	HUD_VOICESTATUS_FUNC				pVoiceStatus;		// Possibly null on old client dlls.
	HUD_DIRECTORMESSAGE_FUNC			pDirectorMessage;	// Possibly null on old client dlls.
	HUD_STUDIO_INTERFACE_FUNC			pStudioInterface;	// Not used by all clients
	HUD_CHATINPUTPOSITION_FUNC			pChatInputPosition;	// Not used by all clients
	HUD_GETPLAYERTEAM					pGetPlayerTeam; // Not used by all clients
	CLIENTFACTORY						pClientFactory;
} cldll_func_t;

// Function type declarations for client destination functions
typedef void(*DST_INITIALIZE_FUNC)				(struct cl_enginefuncs_s**, int *);
typedef void(*DST_HUD_INIT_FUNC)				();
typedef void(*DST_HUD_VIDINIT_FUNC)				();
typedef void(*DST_HUD_REDRAW_FUNC)				(float*, int*);
typedef void(*DST_HUD_UPDATECLIENTDATA_FUNC)	(struct client_data_s**, float*);
typedef void(*DST_HUD_RESET_FUNC)				();
typedef void(*DST_HUD_CLIENTMOVE_FUNC)			(struct playermove_s **, qboolean *);
typedef void(*DST_HUD_CLIENTMOVEINIT_FUNC)		(struct playermove_s **);
typedef void(*DST_HUD_TEXTURETYPE_FUNC)			(const char **);
typedef void(*DST_HUD_IN_ACTIVATEMOUSE_FUNC)	();
typedef void(*DST_HUD_IN_DEACTIVATEMOUSE_FUNC)	();
typedef void(*DST_HUD_IN_MOUSEEVENT_FUNC)		(int *);
typedef void(*DST_HUD_IN_CLEARSTATES_FUNC)		();
typedef void(*DST_HUD_IN_ACCUMULATE_FUNC)		();
typedef void(*DST_HUD_CL_CREATEMOVE_FUNC)		(float *, struct usercmd_s **, int *);
typedef void(*DST_HUD_CL_ISTHIRDPERSON_FUNC)	();
typedef void(*DST_HUD_CL_GETCAMERAOFFSETS_FUNC)	(float **);
typedef void(*DST_HUD_KB_FIND_FUNC)				(const char **);
typedef void(*DST_HUD_CAMTHINK_FUNC)			();
typedef void(*DST_HUD_CALCREF_FUNC)				(struct ref_params_s **);
typedef void(*DST_HUD_ADDENTITY_FUNC)			(int *, struct cl_entity_s **, const char **);
typedef void(*DST_HUD_CREATEENTITIES_FUNC)		();
typedef void(*DST_HUD_DRAWNORMALTRIS_FUNC)		();
typedef void(*DST_HUD_DRAWTRANSTRIS_FUNC)		();
typedef void(*DST_HUD_STUDIOEVENT_FUNC)			(const struct mstudioevent_s **, const struct cl_entity_s **);
typedef void(*DST_HUD_POSTRUNCMD_FUNC)			(struct local_state_s **, struct local_state_s **, struct usercmd_s **, int *, double *, unsigned int *);
typedef void(*DST_HUD_SHUTDOWN_FUNC)			();
typedef void(*DST_HUD_TXFERLOCALOVERRIDES_FUNC)	(struct entity_state_s **, const struct clientdata_s **);
typedef void(*DST_HUD_PROCESSPLAYERSTATE_FUNC)	(struct entity_state_s **, const struct entity_state_s **);
typedef void(*DST_HUD_TXFERPREDICTIONDATA_FUNC)	(struct entity_state_s **, const struct entity_state_s **, struct clientdata_s **, const struct clientdata_s **, struct weapon_data_s **, const struct weapon_data_s **);
typedef void(*DST_HUD_DEMOREAD_FUNC)			(int *, unsigned char **);
typedef void(*DST_HUD_CONNECTIONLESS_FUNC)		(const struct netadr0_s **, const char **, char **, int **);
typedef void(*DST_HUD_GETHULLBOUNDS_FUNC)		(int *, float **, float **);
typedef void(*DST_HUD_FRAME_FUNC)				(double *);
typedef void(*DST_HUD_KEY_EVENT_FUNC)			(int *, int *, const char **);
typedef void(*DST_HUD_TEMPENTUPDATE_FUNC)		(double *, double *, double *, struct tempent_s ***, struct tempent_s ***, int(**Callback_AddVisibleEntity)(struct cl_entity_s *pEntity), void(**Callback_TempEntPlaySound)(struct tempent_s *pTemp, float damp));
typedef void(*DST_HUD_GETUSERENTITY_FUNC)		(int *);
typedef void(*DST_HUD_VOICESTATUS_FUNC)			(int *, qboolean *);
typedef void(*DST_HUD_DIRECTORMESSAGE_FUNC)		(int *, void **);
typedef void(*DST_HUD_STUDIO_INTERFACE_FUNC)	(int *, struct r_studio_interface_s ***, struct engine_studio_api_s **);
typedef void(*DST_HUD_CHATINPUTPOSITION_FUNC)	(int **, int **);
typedef void(*DST_HUD_GETPLAYERTEAM)			(int);

// Pointers to the client destination functions
typedef struct
{
	DST_INITIALIZE_FUNC						pInitFunc;
	DST_HUD_INIT_FUNC						pHudInitFunc;
	DST_HUD_VIDINIT_FUNC					pHudVidInitFunc;
	DST_HUD_REDRAW_FUNC						pHudRedrawFunc;
	DST_HUD_UPDATECLIENTDATA_FUNC			pHudUpdateClientDataFunc;
	DST_HUD_RESET_FUNC						pHudResetFunc;
	DST_HUD_CLIENTMOVE_FUNC					pClientMove;
	DST_HUD_CLIENTMOVEINIT_FUNC				pClientMoveInit;
	DST_HUD_TEXTURETYPE_FUNC				pClientTextureType;
	DST_HUD_IN_ACTIVATEMOUSE_FUNC			pIN_ActivateMouse;
	DST_HUD_IN_DEACTIVATEMOUSE_FUNC			pIN_DeactivateMouse;
	DST_HUD_IN_MOUSEEVENT_FUNC				pIN_MouseEvent;
	DST_HUD_IN_CLEARSTATES_FUNC				pIN_ClearStates;
	DST_HUD_IN_ACCUMULATE_FUNC				pIN_Accumulate;
	DST_HUD_CL_CREATEMOVE_FUNC				pCL_CreateMove;
	DST_HUD_CL_ISTHIRDPERSON_FUNC			pCL_IsThirdPerson;
	DST_HUD_CL_GETCAMERAOFFSETS_FUNC		pCL_GetCameraOffsets;
	DST_HUD_KB_FIND_FUNC					pFindKey;
	DST_HUD_CAMTHINK_FUNC					pCamThink;
	DST_HUD_CALCREF_FUNC					pCalcRefdef;
	DST_HUD_ADDENTITY_FUNC					pAddEntity;
	DST_HUD_CREATEENTITIES_FUNC				pCreateEntities;
	DST_HUD_DRAWNORMALTRIS_FUNC				pDrawNormalTriangles;
	DST_HUD_DRAWTRANSTRIS_FUNC				pDrawTransparentTriangles;
	DST_HUD_STUDIOEVENT_FUNC				pStudioEvent;
	DST_HUD_POSTRUNCMD_FUNC					pPostRunCmd;
	DST_HUD_SHUTDOWN_FUNC					pShutdown;
	DST_HUD_TXFERLOCALOVERRIDES_FUNC		pTxferLocalOverrides;
	DST_HUD_PROCESSPLAYERSTATE_FUNC			pProcessPlayerState;
	DST_HUD_TXFERPREDICTIONDATA_FUNC		pTxferPredictionData;
	DST_HUD_DEMOREAD_FUNC					pReadDemoBuffer;
	DST_HUD_CONNECTIONLESS_FUNC				pConnectionlessPacket;
	DST_HUD_GETHULLBOUNDS_FUNC				pGetHullBounds;
	DST_HUD_FRAME_FUNC						pHudFrame;
	DST_HUD_KEY_EVENT_FUNC					pKeyEvent;
	DST_HUD_TEMPENTUPDATE_FUNC				pTempEntUpdate;
	DST_HUD_GETUSERENTITY_FUNC				pGetUserEntity;
	DST_HUD_VOICESTATUS_FUNC				pVoiceStatus;	// Possibly null on old client dlls.
	DST_HUD_DIRECTORMESSAGE_FUNC			pDirectorMessage;	// Possibly null on old client dlls.
	DST_HUD_STUDIO_INTERFACE_FUNC			pStudioInterface;  // Not used by all clients
	DST_HUD_CHATINPUTPOSITION_FUNC			pChatInputPosition;  // Not used by all clients
	DST_HUD_GETPLAYERTEAM					pGetPlayerTeam; // Not used by all clients
} cldll_func_dst_t;

extern cldll_func_dst_t g_cldstAddrs;


// ********************************************************
// Functions exported by the engine
// ********************************************************

#ifdef _WIN32
typedef HSPRITE HSPRITE_t;
#else
typedef int HSPRITE_t;
#endif

// Function type declarations for engine exports
typedef HSPRITE_t					(*pfnEngSrc_pfnSPR_Load_t)				(const char *szPicName);
typedef int							(*pfnEngSrc_pfnSPR_Frames_t)			(HSPRITE_t hPic);
typedef int							(*pfnEngSrc_pfnSPR_Height_t)			(HSPRITE_t hPic, int frame);
typedef int							(*pfnEngSrc_pfnSPR_Width_t)			(HSPRITE_t hPic, int frame);
typedef void						(*pfnEngSrc_pfnSPR_Set_t)				(HSPRITE_t hPic, int r, int g, int b);
typedef void						(*pfnEngSrc_pfnSPR_Draw_t)				(int frame, int x, int y, const struct rect_s *prc);
typedef void						(*pfnEngSrc_pfnSPR_DrawHoles_t)		(int frame, int x, int y, const struct rect_s *prc);
typedef void						(*pfnEngSrc_pfnSPR_DrawAdditive_t)		(int frame, int x, int y, const struct rect_s *prc);
typedef void						(*pfnEngSrc_pfnSPR_EnableScissor_t)	(int x, int y, int width, int height);
typedef void						(*pfnEngSrc_pfnSPR_DisableScissor_t)	();
typedef struct client_sprite_s	*	(*pfnEngSrc_pfnSPR_GetList_t)			(const char *psz, int *piCount);
typedef void						(*pfnEngSrc_pfnFillRGBA_t)				(int x, int y, int width, int height, int r, int g, int b, int a);
typedef int							(*pfnEngSrc_pfnGetScreenInfo_t) 		(struct SCREENINFO_s *pscrinfo);
typedef void						(*pfnEngSrc_pfnSetCrosshair_t)			(HSPRITE_t hspr, wrect_t rc, int r, int g, int b);
typedef struct cvar_s *				(*pfnEngSrc_pfnRegisterVariable_t)		(const char *szName, const char *szValue, int flags);
typedef float						(*pfnEngSrc_pfnGetCvarFloat_t)			(const char *szName);
typedef const char*					(*pfnEngSrc_pfnGetCvarString_t)		(const char *szName);
typedef qboolean					(*pfnEngSrc_pfnAddCommand_t)			(const char *cmd_name, void (*pfnEngSrc_function)());
typedef qboolean					(*pfnEngSrc_pfnHookUserMsg_t)			(const char *szMsgName, pfnUserMsgHook pfn);
typedef qboolean					(*pfnEngSrc_pfnServerCmd_t)			(const char *szCmdString);
typedef qboolean					(*pfnEngSrc_pfnClientCmd_t)			(const char *szCmdString);
typedef qboolean					(*pfnEngSrc_pfnFilteredClientCmd_t)	(const char *szCmdString);
typedef void						(*pfnEngSrc_pfnPrimeMusicStream_t)		(const char *szFilename, int looping);
typedef void						(*pfnEngSrc_pfnGetPlayerInfo_t)		(int ent_num, struct hud_player_info_s *pinfo);
typedef void						(*pfnEngSrc_pfnPlaySoundByName_t)		(const char *szSound, float volume);
typedef void						(*pfnEngSrc_pfnPlaySoundByNameAtPitch_t)(const char *szSound, float volume, int pitch);
typedef void						(*pfnEngSrc_pfnPlaySoundVoiceByName_t)	(const char *szSound, float volume, int pitch);
typedef void						(*pfnEngSrc_pfnPlaySoundByIndex_t)		(int iSound, float volume);
typedef void						(*pfnEngSrc_pfnAngleVectors_t)			(const float * vecAngles, float * forward, float * right, float * up);
typedef struct client_textmessage_s*(*pfnEngSrc_pfnTextMessageGet_t)		(const char *pName);
typedef int							(*pfnEngSrc_pfnDrawCharacter_t)		(int x, int y, int number, int r, int g, int b);
typedef int							(*pfnEngSrc_pfnDrawConsoleString_t)	(int x, int y, const char *string);
typedef void						(*pfnEngSrc_pfnDrawSetTextColor_t)		(float r, float g, float b);
typedef void						(*pfnEngSrc_pfnDrawConsoleStringLen_t)	(const char *string, int *length, int *height);
typedef void						(*pfnEngSrc_pfnConsolePrint_t)			(const char *string);
typedef void						(*pfnEngSrc_pfnCenterPrint_t)			(const char *string);
typedef int							(*pfnEngSrc_GetWindowCenterX_t)		();
typedef int							(*pfnEngSrc_GetWindowCenterY_t)		();
typedef void						(*pfnEngSrc_GetViewAngles_t)			(float *);
typedef void						(*pfnEngSrc_SetViewAngles_t)			(float *);
typedef int							(*pfnEngSrc_GetMaxClients_t)			();
typedef void						(*pfnEngSrc_Cvar_SetValue_t)			(const char *cvar, float value);
typedef int							(*pfnEngSrc_Cmd_Argc_t)					();
typedef const char *				(*pfnEngSrc_Cmd_Argv_t)				(int arg);
typedef const char *				(*pfnEngSrc_Cmd_Args_t)				();
typedef void						(*pfnEngSrc_Con_Printf_t)				(const char *fmt, ...);
typedef void						(*pfnEngSrc_Con_DPrintf_t)				(const char *fmt, ...);
typedef void						(*pfnEngSrc_Con_PrintfColor_t)				(Color &color, const char *fmt, ...);
typedef void						(*pfnEngSrc_Con_DPrintfColor_t)				(Color &color, const char *fmt, ...);
typedef void						(*pfnEngSrc_Con_PrintfEx_t)				(const char *fmt, ...);
typedef void						(*pfnEngSrc_Con_DPrintfEx_t)				(const char *fmt, ...);
typedef void						(*pfnEngSrc_Con_InsertString)				(const char *fmt, ...);
typedef void						(*pfnEngSrc_Con_NPrintf_t)				(int pos, const char *fmt, ...);
typedef void						(*pfnEngSrc_Con_NXPrintf_t)			(struct con_nprint_s *info, const char *fmt, ...);
typedef const char *				(*pfnEngSrc_PhysInfo_ValueForKey_t)	(const char *key);
typedef const char *				(*pfnEngSrc_ServerInfo_ValueForKey_t)	(const char *key);
typedef float						(*pfnEngSrc_GetClientMaxspeed_t)		();
typedef int							(*pfnEngSrc_CheckParm_t)				(const char *parm, const char **ppnext);
typedef void						(*pfnEngSrc_Key_Event_t)				(int key, qboolean down);
typedef void						(*pfnEngSrc_GetMousePosition_t)		(int *mx, int *my);
typedef qboolean					(*pfnEngSrc_IsNoClipping_t)			();
typedef struct cl_entity_s *		(*pfnEngSrc_GetLocalPlayer_t)			();
typedef struct cl_entity_s *		(*pfnEngSrc_GetViewModel_t)			();
typedef struct cl_entity_s *		(*pfnEngSrc_GetEntityByIndex_t)		(int idx);
typedef float						(*pfnEngSrc_GetClientTime_t)			();
typedef void						(*pfnEngSrc_V_CalcShake_t)				();
typedef void						(*pfnEngSrc_V_ApplyShake_t)			(float *origin, float *angles, float factor);
typedef int							(*pfnEngSrc_PM_PointContents_t)		(float *point, int *truecontents);
typedef int							(*pfnEngSrc_PM_WaterEntity_t)			(float *p);
typedef struct pmtrace_s *			(*pfnEngSrc_PM_TraceLine_t)			(float *start, float *end, int flags, int usehull, int ignore_pe);
typedef struct model_s *			(*pfnEngSrc_CL_LoadModel_t)			(const char *modelname, int *index);
typedef qboolean					(*pfnEngSrc_CL_CreateVisibleEntity_t)	(int type, struct cl_entity_s *ent);
typedef const struct model_s *		(*pfnEngSrc_GetSpritePointer_t)		(HSPRITE_t hSprite);
typedef void						(*pfnEngSrc_pfnPlaySoundByNameAtLocation_t)(const char *szSound, float volume, float *origin);
typedef unsigned short				(*pfnEngSrc_pfnPrecacheEvent_t)		(int type, const char* psz);
typedef void						(*pfnEngSrc_pfnPlaybackEvent_t)		(int flags, const struct edict_s *pInvoker, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);
typedef void						(*pfnEngSrc_pfnWeaponAnim_t)			(int iAnim, int body);
typedef float						(*pfnEngSrc_pfnRandomFloat_t)			(float flLow, float flHigh);
typedef int32_t						(*pfnEngSrc_pfnRandomLong_t)			(int32_t lLow, int32_t lHigh);
typedef void						(*pfnEngSrc_pfnHookEvent_t)			(const char *name, void (*pfnEvent)(struct event_args_s *args));
typedef qboolean					(*pfnEngSrc_Con_IsVisible_t)			();
typedef const char *				(*pfnEngSrc_pfnGetGameDirectory_t)		();
typedef struct cvar_s *				(*pfnEngSrc_pfnGetCvarPointer_t)		(const char *szName);
typedef const char *				(*pfnEngSrc_Key_LookupBinding_t)		(const char *pBinding);
typedef const char *				(*pfnEngSrc_pfnGetLevelName_t)			();
typedef void						(*pfnEngSrc_pfnGetScreenFade_t)		(struct screenfade_s *fade);
typedef void						(*pfnEngSrc_pfnSetScreenFade_t)		(struct screenfade_s *fade);
typedef void *						(*pfnEngSrc_VGui_GetPanel_t)			();
typedef void						(*pfnEngSrc_VGui_ViewportPaintBackground_t)(int extents[4]);
typedef byte*						(*pfnEngSrc_COM_LoadFile_t)			(const char *path, int usehunk, int *pLength);
typedef char*						(*pfnEngSrc_COM_ParseFile_t)			(char *data, char *token);
typedef void						(*pfnEngSrc_COM_FreeFile_t)				(void *buffer);
typedef struct triangleapi_s *		pTriAPI;
typedef struct efx_api_s *			pEfxAPI;
typedef struct event_api_s *		pEventAPI;
typedef struct demo_api_s *			pDemoAPI;
typedef struct net_api_s *			pNetAPI;
typedef struct IVoiceTweak_s *		pVoiceTweak;
typedef qboolean					(*pfnEngSrc_IsSpectateOnly_t)			();
typedef struct model_s *			(*pfnEngSrc_LoadMapSprite_t)			(const char *filename);
typedef void						(*pfnEngSrc_COM_AddAppDirectoryToSearchPath_t) (const char *pszBaseDir, const char *appName);
typedef qboolean					(*pfnEngSrc_COM_ExpandFilename_t)		(const char *fileName, char *nameOutBuffer, int nameOutBufferSize);
typedef const char *				(*pfnEngSrc_PlayerInfo_ValueForKey_t)	(int playerNum, const char *key);
typedef void						(*pfnEngSrc_PlayerInfo_SetValueForKey_t)(const char *key, const char *value);
typedef qboolean					(*pfnEngSrc_GetPlayerUniqueID_t)		(int iPlayer, char playerID[16]);
typedef int							(*pfnEngSrc_GetTrackerIDForPlayer_t)	(int playerSlot);
typedef int							(*pfnEngSrc_GetPlayerForTrackerID_t)	(int trackerID);
typedef qboolean					(*pfnEngSrc_pfnServerCmdUnreliable_t)	(const char *szCmdString);
typedef void						(*pfnEngSrc_GetMousePos_t)				(struct tagPOINT *ppt);
typedef void						(*pfnEngSrc_SetMousePos_t)				(int x, int y);
typedef void						(*pfnEngSrc_SetMouseEnable_t)			(qboolean fEnable);
typedef struct cvar_s *				(*pfnEngSrc_GetFirstCVarPtr_t)			();
typedef struct cmd_function_s *		(*pfnEngSrc_GetFirstCmdFunctionHandle_t)();
typedef struct cmd_function_s *		(*pfnEngSrc_GetNextCmdFunctionHandle_t)	(struct cmd_function_s *cmdhandle);
typedef const char *				(*pfnEngSrc_GetCmdFunctionName_t)		(struct cmd_function_s *cmdhandle);
typedef float						(*pfnEngSrc_GetClientOldTime_t)			();
typedef float						(*pfnEngSrc_GetServerGravityValue_t)	();
typedef struct model_s	*			(*pfnEngSrc_GetModelByIndex_t)			(int index);
typedef void						(*pfnEngSrc_pfnSetFilterMode_t)		(int mode);
typedef void						(*pfnEngSrc_pfnSetFilterColor_t)		(float r, float g, float b);
typedef void						(*pfnEngSrc_pfnSetFilterBrightness_t)	(float brightness);
typedef sequenceEntry_s*			(*pfnEngSrc_pfnSequenceGet_t)			(const char *fileName, const char* entryName);
typedef void						(*pfnEngSrc_pfnSPR_DrawGeneric_t)		(int frame, int x, int y, const struct rect_s *prc, int src, int dest, int w, int h);
typedef sentenceEntry_s*			(*pfnEngSrc_pfnSequencePickSentence_t)	(const char *sentenceName, int pickMethod, int* entryPicked);
// draw a complete string
typedef int							(*pfnEngSrc_pfnDrawString_t)			(int x, int y, const char *str, int r, int g, int b);
typedef int							(*pfnEngSrc_pfnDrawStringReverse_t)	(int x, int y, const char *str, int r, int g, int b);
typedef const char *				(*pfnEngSrc_LocalPlayerInfo_ValueForKey_t)(const char *key);
typedef int							(*pfnEngSrc_pfnVGUI2DrawCharacter_t)	(int x, int y, int ch, unsigned int font);
typedef int							(*pfnEngSrc_pfnVGUI2DrawCharacterAdd_t)(int x, int y, int ch, int r, int g, int b, unsigned int font);
typedef unsigned int				(*pfnEngSrc_COM_GetApproxWavePlayLength)(const char * filename);
typedef void *						(*pfnEngSrc_pfnGetCareerUI_t)			();
typedef void						(*pfnEngSrc_Cvar_Set_t)				(const char *cvar, const char *value);
typedef qboolean					(*pfnEngSrc_pfnIsPlayingCareerMatch_t)	();
typedef double						(*pfnEngSrc_GetAbsoluteTime_t)			();
typedef void						(*pfnEngSrc_pfnProcessTutorMessageDecayBuffer_t)(int *buffer, int bufferLength);
typedef void						(*pfnEngSrc_pfnConstructTutorMessageDecayBuffer_t)(int *buffer, int bufferLength);
typedef void						(*pfnEngSrc_pfnResetTutorMessageDecayData_t)();
typedef void						(*pfnEngSrc_pfnFillRGBABlend_t)		(int x, int y, int width, int height, int r, int g, int b, int a);
typedef unsigned int				(*pfnEngSrc_pfnGetAppID_t)				();
typedef cmdalias_t*					(*pfnEngSrc_pfnGetAliases_t)			();
typedef void						(*pfnEngSrc_pfnVguiWrap2_GetMouseDelta_t)(int *x, int *y);

// Pointers to the exported engine functions themselves
typedef struct cl_enginefuncs_s
{
	pfnEngSrc_pfnSPR_Load_t							pfnSPR_Load;
	pfnEngSrc_pfnSPR_Frames_t						pfnSPR_Frames;
	pfnEngSrc_pfnSPR_Height_t						pfnSPR_Height;
	pfnEngSrc_pfnSPR_Width_t						pfnSPR_Width;
	pfnEngSrc_pfnSPR_Set_t							pfnSPR_Set;
	pfnEngSrc_pfnSPR_Draw_t							pfnSPR_Draw;
	pfnEngSrc_pfnSPR_DrawHoles_t					pfnSPR_DrawHoles;
	pfnEngSrc_pfnSPR_DrawAdditive_t					pfnSPR_DrawAdditive;
	pfnEngSrc_pfnSPR_EnableScissor_t				pfnSPR_EnableScissor;
	pfnEngSrc_pfnSPR_DisableScissor_t				pfnSPR_DisableScissor;
	pfnEngSrc_pfnSPR_GetList_t						pfnSPR_GetList;
	pfnEngSrc_pfnFillRGBA_t							pfnFillRGBA;
	pfnEngSrc_pfnGetScreenInfo_t					pfnGetScreenInfo;
	pfnEngSrc_pfnSetCrosshair_t						pfnSetCrosshair;
	pfnEngSrc_pfnRegisterVariable_t					pfnRegisterVariable;
	pfnEngSrc_pfnGetCvarFloat_t						pfnGetCvarFloat;
	pfnEngSrc_pfnGetCvarString_t					pfnGetCvarString;
	pfnEngSrc_pfnAddCommand_t						pfnAddCommand;
	pfnEngSrc_pfnHookUserMsg_t						pfnHookUserMsg;
	pfnEngSrc_pfnServerCmd_t						pfnServerCmd;
	pfnEngSrc_pfnClientCmd_t						pfnClientCmd;
	pfnEngSrc_pfnGetPlayerInfo_t					pfnGetPlayerInfo;
	pfnEngSrc_pfnPlaySoundByName_t					pfnPlaySoundByName;
	pfnEngSrc_pfnPlaySoundByIndex_t					pfnPlaySoundByIndex;
	pfnEngSrc_pfnAngleVectors_t						pfnAngleVectors;
	pfnEngSrc_pfnTextMessageGet_t					pfnTextMessageGet;
	pfnEngSrc_pfnDrawCharacter_t					pfnDrawCharacter;
	pfnEngSrc_pfnDrawConsoleString_t				pfnDrawConsoleString;
	pfnEngSrc_pfnDrawSetTextColor_t					pfnDrawSetTextColor;
	pfnEngSrc_pfnDrawConsoleStringLen_t				pfnDrawConsoleStringLen;
	pfnEngSrc_pfnConsolePrint_t						pfnConsolePrint;
	pfnEngSrc_pfnCenterPrint_t						pfnCenterPrint;
	pfnEngSrc_GetWindowCenterX_t					GetWindowCenterX;
	pfnEngSrc_GetWindowCenterY_t					GetWindowCenterY;
	pfnEngSrc_GetViewAngles_t						GetViewAngles;
	pfnEngSrc_SetViewAngles_t						SetViewAngles;
	pfnEngSrc_GetMaxClients_t						GetMaxClients;
	pfnEngSrc_Cvar_SetValue_t						Cvar_SetValue;
	pfnEngSrc_Cmd_Argc_t							Cmd_Argc;
	pfnEngSrc_Cmd_Argv_t							Cmd_Argv;
	pfnEngSrc_Con_Printf_t							Con_Printf;
	pfnEngSrc_Con_DPrintf_t							Con_DPrintf;
	pfnEngSrc_Con_NPrintf_t							Con_NPrintf;
	pfnEngSrc_Con_NXPrintf_t						Con_NXPrintf;
	pfnEngSrc_PhysInfo_ValueForKey_t				PhysInfo_ValueForKey;
	pfnEngSrc_ServerInfo_ValueForKey_t				ServerInfo_ValueForKey;
	pfnEngSrc_GetClientMaxspeed_t					GetClientMaxspeed;
	pfnEngSrc_CheckParm_t							CheckParm;
	pfnEngSrc_Key_Event_t							Key_Event;
	pfnEngSrc_GetMousePosition_t					GetMousePosition;
	pfnEngSrc_IsNoClipping_t						IsNoClipping;
	pfnEngSrc_GetLocalPlayer_t						GetLocalPlayer;
	pfnEngSrc_GetViewModel_t						GetViewModel;
	pfnEngSrc_GetEntityByIndex_t					GetEntityByIndex;
	pfnEngSrc_GetClientTime_t						GetClientTime;
	pfnEngSrc_V_CalcShake_t							V_CalcShake;
	pfnEngSrc_V_ApplyShake_t						V_ApplyShake;
	pfnEngSrc_PM_PointContents_t					PM_PointContents;
	pfnEngSrc_PM_WaterEntity_t						PM_WaterEntity;
	pfnEngSrc_PM_TraceLine_t						PM_TraceLine;
	pfnEngSrc_CL_LoadModel_t						CL_LoadModel;
	pfnEngSrc_CL_CreateVisibleEntity_t				CL_CreateVisibleEntity;
	pfnEngSrc_GetSpritePointer_t					GetSpritePointer;
	pfnEngSrc_pfnPlaySoundByNameAtLocation_t		pfnPlaySoundByNameAtLocation;
	pfnEngSrc_pfnPrecacheEvent_t					pfnPrecacheEvent;
	pfnEngSrc_pfnPlaybackEvent_t					pfnPlaybackEvent;
	pfnEngSrc_pfnWeaponAnim_t						pfnWeaponAnim;
	pfnEngSrc_pfnRandomFloat_t						pfnRandomFloat;
	pfnEngSrc_pfnRandomLong_t						pfnRandomLong;
	pfnEngSrc_pfnHookEvent_t						pfnHookEvent;
	pfnEngSrc_Con_IsVisible_t						Con_IsVisible;
	pfnEngSrc_pfnGetGameDirectory_t					pfnGetGameDirectory;
	pfnEngSrc_pfnGetCvarPointer_t					pfnGetCvarPointer;
	pfnEngSrc_Key_LookupBinding_t					Key_LookupBinding;
	pfnEngSrc_pfnGetLevelName_t						pfnGetLevelName;
	pfnEngSrc_pfnGetScreenFade_t					pfnGetScreenFade;
	pfnEngSrc_pfnSetScreenFade_t					pfnSetScreenFade;
	pfnEngSrc_VGui_GetPanel_t						VGui_GetPanel;
	pfnEngSrc_VGui_ViewportPaintBackground_t		VGui_ViewportPaintBackground;
	pfnEngSrc_COM_LoadFile_t						COM_LoadFile;
	pfnEngSrc_COM_ParseFile_t						COM_ParseFile;
	pfnEngSrc_COM_FreeFile_t						COM_FreeFile;
	struct triangleapi_s							*pTriAPI;
	struct efx_api_s								*pEfxAPI;
	struct event_api_s								*pEventAPI;
	struct demo_api_s								*pDemoAPI;
	struct net_api_s								*pNetAPI;
	struct IVoiceTweak_s							*pVoiceTweak;
	pfnEngSrc_IsSpectateOnly_t						IsSpectateOnly;
	pfnEngSrc_LoadMapSprite_t						LoadMapSprite;
	pfnEngSrc_COM_AddAppDirectoryToSearchPath_t		COM_AddAppDirectoryToSearchPath;
	pfnEngSrc_COM_ExpandFilename_t					COM_ExpandFilename;
	pfnEngSrc_PlayerInfo_ValueForKey_t				PlayerInfo_ValueForKey;
	pfnEngSrc_PlayerInfo_SetValueForKey_t			PlayerInfo_SetValueForKey;
	pfnEngSrc_GetPlayerUniqueID_t					GetPlayerUniqueID;
	pfnEngSrc_GetTrackerIDForPlayer_t				GetTrackerIDForPlayer;
	pfnEngSrc_GetPlayerForTrackerID_t				GetPlayerForTrackerID;
	pfnEngSrc_pfnServerCmdUnreliable_t				pfnServerCmdUnreliable;
	pfnEngSrc_GetMousePos_t							pfnGetMousePos;
	pfnEngSrc_SetMousePos_t							pfnSetMousePos;
	pfnEngSrc_SetMouseEnable_t						pfnSetMouseEnable;
	pfnEngSrc_GetFirstCVarPtr_t						GetFirstCvarPtr;
	pfnEngSrc_GetFirstCmdFunctionHandle_t			GetFirstCmdFunctionHandle;
	pfnEngSrc_GetNextCmdFunctionHandle_t			GetNextCmdFunctionHandle;
	pfnEngSrc_GetCmdFunctionName_t					GetCmdFunctionName;
	pfnEngSrc_GetClientOldTime_t					hudGetClientOldTime;
	pfnEngSrc_GetServerGravityValue_t				hudGetServerGravityValue;
	pfnEngSrc_GetModelByIndex_t						hudGetModelByIndex;
	pfnEngSrc_pfnSetFilterMode_t					pfnSetFilterMode;
	pfnEngSrc_pfnSetFilterColor_t					pfnSetFilterColor;
	pfnEngSrc_pfnSetFilterBrightness_t				pfnSetFilterBrightness;
	pfnEngSrc_pfnSequenceGet_t						pfnSequenceGet;
	pfnEngSrc_pfnSPR_DrawGeneric_t					pfnSPR_DrawGeneric;
	pfnEngSrc_pfnSequencePickSentence_t				pfnSequencePickSentence;
	pfnEngSrc_pfnDrawString_t						pfnDrawString;
	pfnEngSrc_pfnDrawStringReverse_t				pfnDrawStringReverse;
	pfnEngSrc_LocalPlayerInfo_ValueForKey_t			LocalPlayerInfo_ValueForKey;
	pfnEngSrc_pfnVGUI2DrawCharacter_t				pfnVGUI2DrawCharacter;
	pfnEngSrc_pfnVGUI2DrawCharacterAdd_t			pfnVGUI2DrawCharacterAdd;
	pfnEngSrc_COM_GetApproxWavePlayLength			COM_GetApproxWavePlayLength;
	pfnEngSrc_pfnGetCareerUI_t						pfnGetCareerUI;
	pfnEngSrc_Cvar_Set_t							Cvar_Set;
	pfnEngSrc_pfnIsPlayingCareerMatch_t				pfnIsCareerMatch;
	pfnEngSrc_pfnPlaySoundVoiceByName_t				pfnPlaySoundVoiceByName;
	pfnEngSrc_pfnPrimeMusicStream_t					pfnPrimeMusicStream;
	pfnEngSrc_GetAbsoluteTime_t						GetAbsoluteTime;
	pfnEngSrc_pfnProcessTutorMessageDecayBuffer_t	pfnProcessTutorMessageDecayBuffer;
	pfnEngSrc_pfnConstructTutorMessageDecayBuffer_t	pfnConstructTutorMessageDecayBuffer;
	pfnEngSrc_pfnResetTutorMessageDecayData_t		pfnResetTutorMessageDecayData;
	pfnEngSrc_pfnPlaySoundByNameAtPitch_t			pfnPlaySoundByNameAtPitch;
	pfnEngSrc_pfnFillRGBABlend_t					pfnFillRGBABlend;
	pfnEngSrc_pfnGetAppID_t							pfnGetAppID;
	pfnEngSrc_pfnGetAliases_t						pfnGetAliasList;
	pfnEngSrc_pfnVguiWrap2_GetMouseDelta_t			pfnVguiWrap2_GetMouseDelta;
	pfnEngSrc_pfnFilteredClientCmd_t				pfnFilteredClientCmd;

} cl_enginefunc_t;

struct cl_enginefuncex_t: public cl_enginefunc_t
{
private:
	enum { NUM_DUMMIES = 20 };
	using dummy_func_t = void (*)();

	// We use our own versions of the engine/dll interface structs.
	// We add a few dummy entries to the end and set them to 0.
	// That way we are protected from updates to the HL SDK adding new functions
	dummy_func_t dummies[NUM_DUMMIES] = {nullptr};

public:
	cl_enginefuncex_t &operator=(const cl_enginefunc_t &other)
	{
		this->pfnSPR_Load                         = other.pfnSPR_Load;
		this->pfnSPR_Frames                       = other.pfnSPR_Frames;
		this->pfnSPR_Height                       = other.pfnSPR_Height;
		this->pfnSPR_Width                        = other.pfnSPR_Width;
		this->pfnSPR_Set                          = other.pfnSPR_Set;
		this->pfnSPR_Draw                         = other.pfnSPR_Draw;
		this->pfnSPR_DrawHoles                    = other.pfnSPR_DrawHoles;
		this->pfnSPR_DrawAdditive                 = other.pfnSPR_DrawAdditive;
		this->pfnSPR_EnableScissor                = other.pfnSPR_EnableScissor;
		this->pfnSPR_DisableScissor               = other.pfnSPR_DisableScissor;
		this->pfnSPR_GetList                      = other.pfnSPR_GetList;
		this->pfnFillRGBA                         = other.pfnFillRGBA;
		this->pfnGetScreenInfo                    = other.pfnGetScreenInfo;
		this->pfnSetCrosshair                     = other.pfnSetCrosshair;
		this->pfnRegisterVariable                 = other.pfnRegisterVariable;
		this->pfnGetCvarFloat                     = other.pfnGetCvarFloat;
		this->pfnGetCvarString                    = other.pfnGetCvarString;
		this->pfnAddCommand                       = other.pfnAddCommand;
		this->pfnHookUserMsg                      = other.pfnHookUserMsg;
		this->pfnServerCmd                        = other.pfnServerCmd;
		this->pfnClientCmd                        = other.pfnClientCmd;
		this->pfnGetPlayerInfo                    = other.pfnGetPlayerInfo;
		this->pfnPlaySoundByName                  = other.pfnPlaySoundByName;
		this->pfnPlaySoundByIndex                 = other.pfnPlaySoundByIndex;
		this->pfnAngleVectors                     = other.pfnAngleVectors;
		this->pfnTextMessageGet                   = other.pfnTextMessageGet;
		this->pfnDrawCharacter                    = other.pfnDrawCharacter;
		this->pfnDrawConsoleString                = other.pfnDrawConsoleString;
		this->pfnDrawSetTextColor                 = other.pfnDrawSetTextColor;
		this->pfnDrawConsoleStringLen             = other.pfnDrawConsoleStringLen;
		this->pfnConsolePrint                     = other.pfnConsolePrint;
		this->pfnCenterPrint                      = other.pfnCenterPrint;
		this->GetWindowCenterX                    = other.GetWindowCenterX;
		this->GetWindowCenterY                    = other.GetWindowCenterY;
		this->GetViewAngles                       = other.GetViewAngles;
		this->SetViewAngles                       = other.SetViewAngles;
		this->GetMaxClients                       = other.GetMaxClients;
		this->Cvar_SetValue                       = other.Cvar_SetValue;
		this->Cmd_Argc                            = other.Cmd_Argc;
		this->Cmd_Argv                            = other.Cmd_Argv;
		this->Con_Printf                          = other.Con_Printf;
		this->Con_DPrintf                         = other.Con_DPrintf;
		this->Con_NPrintf                         = other.Con_NPrintf;
		this->Con_NXPrintf                        = other.Con_NXPrintf;
		this->PhysInfo_ValueForKey                = other.PhysInfo_ValueForKey;
		this->ServerInfo_ValueForKey              = other.ServerInfo_ValueForKey;
		this->GetClientMaxspeed                   = other.GetClientMaxspeed;
		this->CheckParm                           = other.CheckParm;
		this->Key_Event                           = other.Key_Event;
		this->GetMousePosition                    = other.GetMousePosition;
		this->IsNoClipping                        = other.IsNoClipping;
		this->GetLocalPlayer                      = other.GetLocalPlayer;
		this->GetViewModel                        = other.GetViewModel;
		this->GetEntityByIndex                    = other.GetEntityByIndex;
		this->GetClientTime                       = other.GetClientTime;
		this->V_CalcShake                         = other.V_CalcShake;
		this->V_ApplyShake                        = other.V_ApplyShake;
		this->PM_PointContents                    = other.PM_PointContents;
		this->PM_WaterEntity                      = other.PM_WaterEntity;
		this->PM_TraceLine                        = other.PM_TraceLine;
		this->CL_LoadModel                        = other.CL_LoadModel;
		this->CL_CreateVisibleEntity              = other.CL_CreateVisibleEntity;
		this->GetSpritePointer                    = other.GetSpritePointer;
		this->pfnPlaySoundByNameAtLocation        = other.pfnPlaySoundByNameAtLocation;
		this->pfnPrecacheEvent                    = other.pfnPrecacheEvent;
		this->pfnPlaybackEvent                    = other.pfnPlaybackEvent;
		this->pfnWeaponAnim                       = other.pfnWeaponAnim;
		this->pfnRandomFloat                      = other.pfnRandomFloat;
		this->pfnRandomLong                       = other.pfnRandomLong;
		this->pfnHookEvent                        = other.pfnHookEvent;
		this->Con_IsVisible                       = other.Con_IsVisible;
		this->pfnGetGameDirectory                 = other.pfnGetGameDirectory;
		this->pfnGetCvarPointer                   = other.pfnGetCvarPointer;
		this->Key_LookupBinding                   = other.Key_LookupBinding;
		this->pfnGetLevelName                     = other.pfnGetLevelName;
		this->pfnGetScreenFade                    = other.pfnGetScreenFade;
		this->pfnSetScreenFade                    = other.pfnSetScreenFade;
		this->VGui_GetPanel                       = other.VGui_GetPanel;
		this->VGui_ViewportPaintBackground        = other.VGui_ViewportPaintBackground;
		this->COM_LoadFile                        = other.COM_LoadFile;
		this->COM_ParseFile                       = other.COM_ParseFile;
		this->COM_FreeFile                        = other.COM_FreeFile;
		this->pTriAPI                             = other.pTriAPI;
		this->pEfxAPI                             = other.pEfxAPI;
		this->pEventAPI                           = other.pEventAPI;
		this->pDemoAPI                            = other.pDemoAPI;
		this->pNetAPI                             = other.pNetAPI;
		this->pVoiceTweak                         = other.pVoiceTweak;
		this->IsSpectateOnly                      = other.IsSpectateOnly;
		this->LoadMapSprite                       = other.LoadMapSprite;
		this->COM_AddAppDirectoryToSearchPath     = other.COM_AddAppDirectoryToSearchPath;
		this->COM_ExpandFilename                  = other.COM_ExpandFilename;
		this->PlayerInfo_ValueForKey              = other.PlayerInfo_ValueForKey;
		this->PlayerInfo_SetValueForKey           = other.PlayerInfo_SetValueForKey;
		this->GetPlayerUniqueID                   = other.GetPlayerUniqueID;
		this->GetTrackerIDForPlayer               = other.GetTrackerIDForPlayer;
		this->GetPlayerForTrackerID               = other.GetPlayerForTrackerID;
		this->pfnServerCmdUnreliable              = other.pfnServerCmdUnreliable;
		this->pfnGetMousePos                      = other.pfnGetMousePos;
		this->pfnSetMousePos                      = other.pfnSetMousePos;
		this->pfnSetMouseEnable                   = other.pfnSetMouseEnable;
		this->GetFirstCvarPtr                     = other.GetFirstCvarPtr;
		this->GetFirstCmdFunctionHandle           = other.GetFirstCmdFunctionHandle;
		this->GetNextCmdFunctionHandle            = other.GetNextCmdFunctionHandle;
		this->GetCmdFunctionName                  = other.GetCmdFunctionName;
		this->hudGetClientOldTime                 = other.hudGetClientOldTime;
		this->hudGetServerGravityValue            = other.hudGetServerGravityValue;
		this->hudGetModelByIndex                  = other.hudGetModelByIndex;
		this->pfnSetFilterMode                    = other.pfnSetFilterMode;
		this->pfnSetFilterColor                   = other.pfnSetFilterColor;
		this->pfnSetFilterBrightness              = other.pfnSetFilterBrightness;
		this->pfnSequenceGet                      = other.pfnSequenceGet;
		this->pfnSPR_DrawGeneric                  = other.pfnSPR_DrawGeneric;
		this->pfnSequencePickSentence             = other.pfnSequencePickSentence;
		this->pfnDrawString                       = other.pfnDrawString;
		this->pfnDrawStringReverse                = other.pfnDrawStringReverse;
		this->LocalPlayerInfo_ValueForKey         = other.LocalPlayerInfo_ValueForKey;
		this->pfnVGUI2DrawCharacter               = other.pfnVGUI2DrawCharacter;
		this->pfnVGUI2DrawCharacterAdd            = other.pfnVGUI2DrawCharacterAdd;
		this->COM_GetApproxWavePlayLength         = other.COM_GetApproxWavePlayLength;
		this->pfnGetCareerUI                      = other.pfnGetCareerUI;
		this->Cvar_Set                            = other.Cvar_Set;
		this->pfnIsCareerMatch                    = other.pfnIsCareerMatch;
		this->pfnPlaySoundVoiceByName             = other.pfnPlaySoundVoiceByName;
		this->pfnPrimeMusicStream                 = other.pfnPrimeMusicStream;
		this->GetAbsoluteTime                     = other.GetAbsoluteTime;
		this->pfnProcessTutorMessageDecayBuffer   = other.pfnProcessTutorMessageDecayBuffer;
		this->pfnConstructTutorMessageDecayBuffer = other.pfnConstructTutorMessageDecayBuffer;
		this->pfnResetTutorMessageDecayData       = other.pfnResetTutorMessageDecayData;
		this->pfnPlaySoundByNameAtPitch           = other.pfnPlaySoundByNameAtPitch;
		this->pfnFillRGBABlend                    = other.pfnFillRGBABlend;
		this->pfnGetAppID                         = other.pfnGetAppID;
		this->pfnGetAliasList                     = other.pfnGetAliasList;
		this->pfnVguiWrap2_GetMouseDelta          = other.pfnVguiWrap2_GetMouseDelta;
		this->pfnFilteredClientCmd                = other.pfnFilteredClientCmd;

		this->Con_PrintfColor                     = nullptr;
		this->Con_DPrintfColor                    = nullptr;
		this->Con_PrintfEx                        = nullptr;
		this->Con_DPrintfEx                       = nullptr;

		this->Cmd_Args                            = nullptr;
		this->Con_InsertString                    = nullptr;

		memset(dummies, 0, sizeof(dummies));

		return (*this);
	}

	// custom funcs
	pfnEngSrc_Con_PrintfColor_t						Con_PrintfColor;
	pfnEngSrc_Con_DPrintfColor_t					Con_DPrintfColor;

	// Supports color formatting
	//
	// An example of the use of keywords
	//
	// Hex color      - "#{ffd700}Gold text#{}, plain text."
	// Color name     - "${gold}Gold text${}, plain text."
	// Console color  - "${c}Console color text${}, plain text." (NOTE: The color is based on the value of cvar 'con_color')
	//
	// Supported color names
	//
	//   black
	//   white
	//
	//
	//   red        > green       > blue        > yellow      > aqua          > grey
	//   brown      > greeny      > lightblue   > orange      > aquamarine    > silver
	//   magenta    > springgreen > skyblue     > gold        > turquoise     > slategrey
	//   coral      > palegreen   > deepskyblue > yellowgreen > darkturquoise > dimgrey
	//   lightcoral > seagreen    > blueviolet  > khaki       > paleturquoise > gainsboro
	//   pink       > forestgreen > royalblue   > moccasin    > teal
	//                            > darkblue    > sundance
	//
	pfnEngSrc_Con_PrintfEx_t						Con_PrintfEx;
	pfnEngSrc_Con_DPrintfEx_t						Con_DPrintfEx;

	pfnEngSrc_Cmd_Args_t							Cmd_Args;
	pfnEngSrc_Con_InsertString						Con_InsertString;
};

// Compatibility sizeof
constexpr int MAX_SIZEOF_CLENGINEFUNCS = sizeof(cl_enginefunc_t);

// Function type declarations for engine destination functions
typedef void (*pfnEngDst_pfnSPR_Load_t)							(const char **);
typedef void (*pfnEngDst_pfnSPR_Frames_t)						(HSPRITE_t *);
typedef void (*pfnEngDst_pfnSPR_Height_t)						(HSPRITE_t *, int *);
typedef void (*pfnEngDst_pfnSPR_Width_t)						(HSPRITE_t *, int *);
typedef void (*pfnEngDst_pfnSPR_Set_t)							(HSPRITE_t *, int *, int *, int *);
typedef void (*pfnEngDst_pfnSPR_Draw_t)							(int *, int *, int *, const struct rect_s **);
typedef void (*pfnEngDst_pfnSPR_DrawHoles_t)					(int *, int *, int *, const struct rect_s **);
typedef void (*pfnEngDst_pfnSPR_DrawAdditive_t)					(int *, int *, int *, const struct rect_s **);
typedef void (*pfnEngDst_pfnSPR_EnableScissor_t)				(int *, int *, int *, int *);
typedef void (*pfnEngDst_pfnSPR_DisableScissor_t)				();
typedef void (*pfnEngDst_pfnSPR_GetList_t)						(const char **, int **);
typedef void (*pfnEngDst_pfnFillRGBA_t)							(int *, int *, int *, int *, int *, int *, int *, int *);
typedef void (*pfnEngDst_pfnGetScreenInfo_t) 					(struct SCREENINFO_s **);
typedef void (*pfnEngDst_pfnSetCrosshair_t)						(HSPRITE_t *, struct rect_s *, int *, int *, int *);
typedef void (*pfnEngDst_pfnRegisterVariable_t)					(const char **, const char **, int *);
typedef void (*pfnEngDst_pfnGetCvarFloat_t)						(const char **);
typedef void (*pfnEngDst_pfnGetCvarString_t)					(const char **);
typedef void (*pfnEngDst_pfnAddCommand_t)						(const char **, void(**pfnEngDst_function)());
typedef void (*pfnEngDst_pfnHookUserMsg_t)						(const char **, pfnUserMsgHook *);
typedef void (*pfnEngDst_pfnServerCmd_t)						(const char **);
typedef void (*pfnEngDst_pfnClientCmd_t)						(const char **);
typedef void (*pfnEngDst_pfnFilteredClientCmd_t)				(const char **);
typedef void (*pfnEngDst_pfnPrimeMusicStream_t)					(const char **, int *);
typedef void (*pfnEngDst_pfnGetPlayerInfo_t)					(int *, struct hud_player_info_s **);
typedef void (*pfnEngDst_pfnPlaySoundByName_t)					(const char **, float *);
typedef void (*pfnEngDst_pfnPlaySoundByNameAtPitch_t)			(const char **, float *, int *);
typedef void (*pfnEngDst_pfnPlaySoundVoiceByName_t)				(const char **, float *, int *);
typedef void (*pfnEngDst_pfnPlaySoundByIndex_t)					(int *, float *);
typedef void (*pfnEngDst_pfnAngleVectors_t)						(const float * *, float * *, float * *, float * *);
typedef void (*pfnEngDst_pfnTextMessageGet_t)					(const char **);
typedef void (*pfnEngDst_pfnDrawCharacter_t)					(int *, int *, int *, int *, int *, int *);
typedef void (*pfnEngDst_pfnDrawConsoleString_t)				(int *, int *, const char **);
typedef void (*pfnEngDst_pfnDrawSetTextColor_t)					(float *, float *, float *);
typedef void (*pfnEngDst_pfnDrawConsoleStringLen_t)				(const char **, int **, int **);
typedef void (*pfnEngDst_pfnConsolePrint_t)						(const char **);
typedef void (*pfnEngDst_pfnCenterPrint_t)						(const char **);
typedef void (*pfnEngDst_GetWindowCenterX_t)					();
typedef void (*pfnEngDst_GetWindowCenterY_t)					();
typedef void (*pfnEngDst_GetViewAngles_t)						(float **);
typedef void (*pfnEngDst_SetViewAngles_t)						(float **);
typedef void (*pfnEngDst_GetMaxClients_t)						();
typedef void (*pfnEngDst_Cvar_SetValue_t)						(const char **, float *);
typedef void (*pfnEngDst_Cmd_Argc_t)							();
typedef void (*pfnEngDst_Cmd_Argv_t)							(int *);
typedef void (*pfnEngDst_Con_Printf_t)							(const char **);
typedef void (*pfnEngDst_Con_DPrintf_t)							(const char **);
typedef void (*pfnEngDst_Con_NPrintf_t)							(int *, const char **);
typedef void (*pfnEngDst_Con_NXPrintf_t)						(struct con_nprint_s **, const char **);
typedef void (*pfnEngDst_PhysInfo_ValueForKey_t)				(const char **);
typedef void (*pfnEngDst_ServerInfo_ValueForKey_t)				(const char **);
typedef void (*pfnEngDst_GetClientMaxspeed_t)					();
typedef void (*pfnEngDst_CheckParm_t)							(const char **, const char ***);
typedef void (*pfnEngDst_Key_Event_t)							(int *, qboolean *);
typedef void (*pfnEngDst_GetMousePosition_t)					(int **, int **);
typedef void (*pfnEngDst_IsNoClipping_t)						();
typedef void (*pfnEngDst_GetLocalPlayer_t)						();
typedef void (*pfnEngDst_GetViewModel_t)						();
typedef void (*pfnEngDst_GetEntityByIndex_t)					(int *);
typedef void (*pfnEngDst_GetClientTime_t)						();
typedef void (*pfnEngDst_V_CalcShake_t)							();
typedef void (*pfnEngDst_V_ApplyShake_t)						(float **, float **, float *);
typedef void (*pfnEngDst_PM_PointContents_t)					(float **, int **);
typedef void (*pfnEngDst_PM_WaterEntity_t)						(float **);
typedef void (*pfnEngDst_PM_TraceLine_t)						(float **, float **, int *, int *, int *);
typedef void (*pfnEngDst_CL_LoadModel_t)						(const char **, int **);
typedef void (*pfnEngDst_CL_CreateVisibleEntity_t)				(int *, struct cl_entity_s **);
typedef void (*pfnEngDst_GetSpritePointer_t)					(HSPRITE_t *);
typedef void (*pfnEngDst_pfnPlaySoundByNameAtLocation_t)		(const char **, float *, float **);
typedef void (*pfnEngDst_pfnPrecacheEvent_t)					(int *, const char* *);
typedef void (*pfnEngDst_pfnPlaybackEvent_t)					(int *, const struct edict_s **, unsigned short *, float *, float **, float **, float *, float *, int *, int *, int *, int *);
typedef void (*pfnEngDst_pfnWeaponAnim_t)						(int *, int *);
typedef void (*pfnEngDst_pfnRandomFloat_t)						(float *, float *);
typedef void (*pfnEngDst_pfnRandomLong_t)						(int32_t *, int32_t *);
typedef void (*pfnEngDst_pfnHookEvent_t)						(const char **, void(**pfnEvent)(struct event_args_s *args));
typedef void (*pfnEngDst_Con_IsVisible_t)						();
typedef void (*pfnEngDst_pfnGetGameDirectory_t)					();
typedef void (*pfnEngDst_pfnGetCvarPointer_t)					(const char **);
typedef void (*pfnEngDst_Key_LookupBinding_t)					(const char **);
typedef void (*pfnEngDst_pfnGetLevelName_t)						();
typedef void (*pfnEngDst_pfnGetScreenFade_t)					(struct screenfade_s **);
typedef void (*pfnEngDst_pfnSetScreenFade_t)					(struct screenfade_s **);
typedef void (*pfnEngDst_VGui_GetPanel_t)						();
typedef void (*pfnEngDst_VGui_ViewportPaintBackground_t)		(int **);
typedef void (*pfnEngDst_COM_LoadFile_t)						(const char **, int *, int **);
typedef void (*pfnEngDst_COM_ParseFile_t)						(char **, char **);
typedef void (*pfnEngDst_COM_FreeFile_t)						(void **);
typedef void (*pfnEngDst_IsSpectateOnly_t)						();
typedef void (*pfnEngDst_LoadMapSprite_t)						(const char **);
typedef void (*pfnEngDst_COM_AddAppDirectoryToSearchPath_t)		(const char **, const char **);
typedef void (*pfnEngDst_COM_ExpandFilename_t)					(const char **, char **, int *);
typedef void (*pfnEngDst_PlayerInfo_ValueForKey_t)				(int *, const char **);
typedef void (*pfnEngDst_PlayerInfo_SetValueForKey_t)			(const char **, const char **);
typedef void (*pfnEngDst_GetPlayerUniqueID_t)					(int *, char **);
typedef void (*pfnEngDst_GetTrackerIDForPlayer_t)				(int *);
typedef void (*pfnEngDst_GetPlayerForTrackerID_t)				(int *);
typedef void (*pfnEngDst_pfnServerCmdUnreliable_t)				(const char **);
typedef void (*pfnEngDst_GetMousePos_t)							(struct tagPOINT **);
typedef void (*pfnEngDst_SetMousePos_t)							(int *, int *);
typedef void (*pfnEngDst_SetMouseEnable_t)						(qboolean *);
typedef void (*pfnEngDst_pfnSetFilterMode_t)					(int *);
typedef void (*pfnEngDst_pfnSetFilterColor_t)					(float *, float *, float *);
typedef void (*pfnEngDst_pfnSetFilterBrightness_t)				(float *);
typedef void (*pfnEngDst_pfnSequenceGet_t)						(const char**, const char**);
typedef void (*pfnEngDst_pfnSPR_DrawGeneric_t)					(int *, int *, int *, const struct rect_s **, int *, int *, int *, int *);
typedef void (*pfnEngDst_pfnSequencePickSentence_t)				(const char**, int *, int **);
typedef void (*pfnEngDst_pfnDrawString_t)						(int *, int *, const char *, int *, int *, int *);
typedef void (*pfnEngDst_pfnDrawStringReverse_t)				(int *, int *, const char *, int *, int *, int *);
typedef void (*pfnEngDst_LocalPlayerInfo_ValueForKey_t)			(const char **);
typedef void (*pfnEngDst_pfnVGUI2DrawCharacter_t)				(int *, int *, int *, unsigned int *);
typedef void (*pfnEngDst_pfnVGUI2DrawCharacterAdd_t)			(int *, int *, int *, int *, int *, int *, unsigned int *);
typedef void (*pfnEngDst_pfnProcessTutorMessageDecayBuffer_t)	(int **, int *);
typedef void (*pfnEngDst_pfnConstructTutorMessageDecayBuffer_t)	(int **, int *);
typedef void (*pfnEngDst_pfnResetTutorMessageDecayData_t)		();
typedef void (*pfnEngDst_pfnFillRGBABlend_t)					(int *, int *, int *, int *, int *, int *, int *, int *);
typedef void (*pfnEngDst_pfnGetAppID_t)							();
typedef void (*pfnEngDst_pfnGetAliases_t)						();
typedef void (*pfnEngDst_pfnVguiWrap2_GetMouseDelta_t)			(int *x, int *y);


// Pointers to the engine destination functions
typedef struct
{
	pfnEngDst_pfnSPR_Load_t							pfnSPR_Load;
	pfnEngDst_pfnSPR_Frames_t						pfnSPR_Frames;
	pfnEngDst_pfnSPR_Height_t						pfnSPR_Height;
	pfnEngDst_pfnSPR_Width_t						pfnSPR_Width;
	pfnEngDst_pfnSPR_Set_t							pfnSPR_Set;
	pfnEngDst_pfnSPR_Draw_t							pfnSPR_Draw;
	pfnEngDst_pfnSPR_DrawHoles_t					pfnSPR_DrawHoles;
	pfnEngDst_pfnSPR_DrawAdditive_t					pfnSPR_DrawAdditive;
	pfnEngDst_pfnSPR_EnableScissor_t				pfnSPR_EnableScissor;
	pfnEngDst_pfnSPR_DisableScissor_t				pfnSPR_DisableScissor;
	pfnEngDst_pfnSPR_GetList_t						pfnSPR_GetList;
	pfnEngDst_pfnFillRGBA_t							pfnFillRGBA;
	pfnEngDst_pfnGetScreenInfo_t					pfnGetScreenInfo;
	pfnEngDst_pfnSetCrosshair_t						pfnSetCrosshair;
	pfnEngDst_pfnRegisterVariable_t					pfnRegisterVariable;
	pfnEngDst_pfnGetCvarFloat_t						pfnGetCvarFloat;
	pfnEngDst_pfnGetCvarString_t					pfnGetCvarString;
	pfnEngDst_pfnAddCommand_t						pfnAddCommand;
	pfnEngDst_pfnHookUserMsg_t						pfnHookUserMsg;
	pfnEngDst_pfnServerCmd_t						pfnServerCmd;
	pfnEngDst_pfnClientCmd_t						pfnClientCmd;
	pfnEngDst_pfnGetPlayerInfo_t					pfnGetPlayerInfo;
	pfnEngDst_pfnPlaySoundByName_t					pfnPlaySoundByName;
	pfnEngDst_pfnPlaySoundByIndex_t					pfnPlaySoundByIndex;
	pfnEngDst_pfnAngleVectors_t						pfnAngleVectors;
	pfnEngDst_pfnTextMessageGet_t					pfnTextMessageGet;
	pfnEngDst_pfnDrawCharacter_t					pfnDrawCharacter;
	pfnEngDst_pfnDrawConsoleString_t				pfnDrawConsoleString;
	pfnEngDst_pfnDrawSetTextColor_t					pfnDrawSetTextColor;
	pfnEngDst_pfnDrawConsoleStringLen_t				pfnDrawConsoleStringLen;
	pfnEngDst_pfnConsolePrint_t						pfnConsolePrint;
	pfnEngDst_pfnCenterPrint_t						pfnCenterPrint;
	pfnEngDst_GetWindowCenterX_t					GetWindowCenterX;
	pfnEngDst_GetWindowCenterY_t					GetWindowCenterY;
	pfnEngDst_GetViewAngles_t						GetViewAngles;
	pfnEngDst_SetViewAngles_t						SetViewAngles;
	pfnEngDst_GetMaxClients_t						GetMaxClients;
	pfnEngDst_Cvar_SetValue_t						Cvar_SetValue;
	pfnEngDst_Cmd_Argc_t							Cmd_Argc;
	pfnEngDst_Cmd_Argv_t							Cmd_Argv;
	pfnEngDst_Con_Printf_t							Con_Printf;
	pfnEngDst_Con_DPrintf_t							Con_DPrintf;
	pfnEngDst_Con_NPrintf_t							Con_NPrintf;
	pfnEngDst_Con_NXPrintf_t						Con_NXPrintf;
	pfnEngDst_PhysInfo_ValueForKey_t				PhysInfo_ValueForKey;
	pfnEngDst_ServerInfo_ValueForKey_t				ServerInfo_ValueForKey;
	pfnEngDst_GetClientMaxspeed_t					GetClientMaxspeed;
	pfnEngDst_CheckParm_t							CheckParm;
	pfnEngDst_Key_Event_t							Key_Event;
	pfnEngDst_GetMousePosition_t					GetMousePosition;
	pfnEngDst_IsNoClipping_t						IsNoClipping;
	pfnEngDst_GetLocalPlayer_t						GetLocalPlayer;
	pfnEngDst_GetViewModel_t						GetViewModel;
	pfnEngDst_GetEntityByIndex_t					GetEntityByIndex;
	pfnEngDst_GetClientTime_t						GetClientTime;
	pfnEngDst_V_CalcShake_t							V_CalcShake;
	pfnEngDst_V_ApplyShake_t						V_ApplyShake;
	pfnEngDst_PM_PointContents_t					PM_PointContents;
	pfnEngDst_PM_WaterEntity_t						PM_WaterEntity;
	pfnEngDst_PM_TraceLine_t						PM_TraceLine;
	pfnEngDst_CL_LoadModel_t						CL_LoadModel;
	pfnEngDst_CL_CreateVisibleEntity_t				CL_CreateVisibleEntity;
	pfnEngDst_GetSpritePointer_t					GetSpritePointer;
	pfnEngDst_pfnPlaySoundByNameAtLocation_t		pfnPlaySoundByNameAtLocation;
	pfnEngDst_pfnPrecacheEvent_t					pfnPrecacheEvent;
	pfnEngDst_pfnPlaybackEvent_t					pfnPlaybackEvent;
	pfnEngDst_pfnWeaponAnim_t						pfnWeaponAnim;
	pfnEngDst_pfnRandomFloat_t						pfnRandomFloat;
	pfnEngDst_pfnRandomLong_t						pfnRandomLong;
	pfnEngDst_pfnHookEvent_t						pfnHookEvent;
	pfnEngDst_Con_IsVisible_t						Con_IsVisible;
	pfnEngDst_pfnGetGameDirectory_t					pfnGetGameDirectory;
	pfnEngDst_pfnGetCvarPointer_t					pfnGetCvarPointer;
	pfnEngDst_Key_LookupBinding_t					Key_LookupBinding;
	pfnEngDst_pfnGetLevelName_t						pfnGetLevelName;
	pfnEngDst_pfnGetScreenFade_t					pfnGetScreenFade;
	pfnEngDst_pfnSetScreenFade_t					pfnSetScreenFade;
	pfnEngDst_VGui_GetPanel_t						VGui_GetPanel;
	pfnEngDst_VGui_ViewportPaintBackground_t		VGui_ViewportPaintBackground;
	pfnEngDst_COM_LoadFile_t						COM_LoadFile;
	pfnEngDst_COM_ParseFile_t						COM_ParseFile;
	pfnEngDst_COM_FreeFile_t						COM_FreeFile;
	struct triangleapi_s							*pTriAPI;
	struct efx_api_s								*pEfxAPI;
	struct event_api_s								*pEventAPI;
	struct demo_api_s								*pDemoAPI;
	struct net_api_s								*pNetAPI;
	struct IVoiceTweak_s							*pVoiceTweak;
	pfnEngDst_IsSpectateOnly_t						IsSpectateOnly;
	pfnEngDst_LoadMapSprite_t						LoadMapSprite;
	pfnEngDst_COM_AddAppDirectoryToSearchPath_t		COM_AddAppDirectoryToSearchPath;
	pfnEngDst_COM_ExpandFilename_t					COM_ExpandFilename;
	pfnEngDst_PlayerInfo_ValueForKey_t				PlayerInfo_ValueForKey;
	pfnEngDst_PlayerInfo_SetValueForKey_t			PlayerInfo_SetValueForKey;
	pfnEngDst_GetPlayerUniqueID_t					GetPlayerUniqueID;
	pfnEngDst_GetTrackerIDForPlayer_t				GetTrackerIDForPlayer;
	pfnEngDst_GetPlayerForTrackerID_t				GetPlayerForTrackerID;
	pfnEngDst_pfnServerCmdUnreliable_t				pfnServerCmdUnreliable;
	pfnEngDst_GetMousePos_t							pfnGetMousePos;
	pfnEngDst_SetMousePos_t							pfnSetMousePos;
	pfnEngDst_SetMouseEnable_t						pfnSetMouseEnable;
	pfnEngDst_pfnSetFilterMode_t					pfnSetFilterMode;
	pfnEngDst_pfnSetFilterColor_t					pfnSetFilterColor;
	pfnEngDst_pfnSetFilterBrightness_t				pfnSetFilterBrightness;
	pfnEngDst_pfnSequenceGet_t						pfnSequenceGet;
	pfnEngDst_pfnSPR_DrawGeneric_t					pfnSPR_DrawGeneric;
	pfnEngDst_pfnSequencePickSentence_t				pfnSequencePickSentence;
	pfnEngDst_pfnDrawString_t						pfnDrawString;
	pfnEngDst_pfnDrawString_t						pfnDrawStringReverse;
	pfnEngDst_LocalPlayerInfo_ValueForKey_t			LocalPlayerInfo_ValueForKey;
	pfnEngDst_pfnVGUI2DrawCharacter_t				pfnVGUI2DrawCharacter;
	pfnEngDst_pfnVGUI2DrawCharacterAdd_t			pfnVGUI2DrawCharacterAdd;
	pfnEngDst_pfnPlaySoundVoiceByName_t				pfnPlaySoundVoiceByName;
	pfnEngDst_pfnPrimeMusicStream_t					pfnPrimeMusicStream;
	pfnEngDst_pfnProcessTutorMessageDecayBuffer_t	pfnProcessTutorMessageDecayBuffer;
	pfnEngDst_pfnConstructTutorMessageDecayBuffer_t	pfnConstructTutorMessageDecayBuffer;
	pfnEngDst_pfnResetTutorMessageDecayData_t		pfnResetTutorMessageDecayData;
	pfnEngDst_pfnPlaySoundByNameAtPitch_t			pfnPlaySoundByNameAtPitch;
	pfnEngDst_pfnFillRGBABlend_t					pfnFillRGBABlend;
	pfnEngDst_pfnGetAppID_t							pfnGetAppID;
	pfnEngDst_pfnGetAliases_t						pfnGetAliasList;
	pfnEngDst_pfnVguiWrap2_GetMouseDelta_t			pfnVguiWrap2_GetMouseDelta;
	pfnEngDst_pfnFilteredClientCmd_t				pfnFilteredClientCmd;

} cl_enginefunc_dst_t;


// ********************************************************
// Functions exposed by the engine to the module
// ********************************************************

// Functions for ModuleS
typedef void (*PFN_KICKPLAYER)(int nPlayerSlot, int nReason);

typedef struct modshelpers_s
{
	PFN_KICKPLAYER m_pfnKickPlayer;

	// reserved for future expansion
	int m_nVoid1;
	int m_nVoid2;
	int m_nVoid3;
	int m_nVoid4;
	int m_nVoid5;
	int m_nVoid6;
	int m_nVoid7;
	int m_nVoid8;
	int m_nVoid9;
} modshelpers_t;

// Functions for moduleC
typedef struct modchelpers_s
{
	// reserved for future expansion
	int m_nVoid0;
	int m_nVoid1;
	int m_nVoid2;
	int m_nVoid3;
	int m_nVoid4;
	int m_nVoid5;
	int m_nVoid6;
	int m_nVoid7;
	int m_nVoid8;
	int m_nVoid9;
} modchelpers_t;


// ********************************************************
// Information about the engine
// ********************************************************
typedef struct engdata_s
{
	cl_enginefunc_t *pcl_enginefuncs;					// functions exported by the engine
	cl_enginefunc_dst_t *pg_engdstAddrs;				// destination handlers for engine exports
	cldll_func_t *pcl_funcs;							// client exports
	cldll_func_dst_t *pg_cldstAddrs;					// client export destination handlers
	struct modfuncs_s *pg_modfuncs;						// engine's pointer to module functions
	struct cmd_function_s **pcmd_functions;				// list of all registered commands
	void *pkeybindings;									// all key bindings (not really a void *, but easier this way)
	void (*pfnConPrintf)(const char *, ...);			// dump to console
	struct cvar_s **pcvar_vars;							// pointer to head of cvar list
	struct glwstate_t *pglwstate;						// OpenGl information
	void *(*pfnSZ_GetSpace)(struct sizebuf_s *, int);	// pointer to SZ_GetSpace
	struct modfuncs_s *pmodfuncs;						// &g_modfuncs
	void *pfnGetProcAddress;							// &GetProcAddress
	void *pfnGetModuleHandle;							// &GetModuleHandle
	struct server_static_s *psvs;						// &svs
	struct client_static_s *pcls;						// &cls
	void (*pfnSV_DropClient)(struct client_s *, qboolean, const char *, ...);	// pointer to SV_DropClient
	void (*pfnNetchan_Transmit)(struct netchan_s *, int, byte *);		// pointer to Netchan_Transmit
	void (*pfnNET_SendPacket)(enum netsrc_s sock, int length, const void *data, const netadr0_t &to); // &NET_SendPacket
	struct cvar_s *(*pfnCvarFindVar)(const char *pchName);				// pointer to Cvar_FindVar
	int *phinstOpenGlEarly;								// &g_hinstOpenGlEarly

	// Reserved for future expansion
	void *pVoid0;							// reserved for future expan
	void *pVoid1;							// reserved for future expan
	void *pVoid2;							// reserved for future expan
	void *pVoid3;							// reserved for future expan
	void *pVoid4;							// reserved for future expan
	void *pVoid5;							// reserved for future expan
	void *pVoid6;							// reserved for future expan
	void *pVoid7;							// reserved for future expan
	void *pVoid8;							// reserved for future expan
	void *pVoid9;							// reserved for future expan
} engdata_t;


// ********************************************************
// Functions exposed by the security module
// ********************************************************
typedef void (*PFN_LOADMOD)(const char *pchModule);
typedef void (*PFN_CLOSEMOD)();
typedef int (*PFN_NCALL)(int ijump, int cnArg, ...);

typedef void (*PFN_GETCLDSTADDRS)(cldll_func_dst_t *pcldstAddrs);
typedef void (*PFN_GETENGDSTADDRS)(cl_enginefunc_dst_t *pengdstAddrs);
typedef void (*PFN_MODULELOADED)();

typedef void (*PFN_PROCESSOUTGOINGNET)(struct netchan_s *pchan, struct sizebuf_s *psizebuf);
typedef qboolean (*PFN_PROCESSINCOMINGNET)(struct netchan_s *pchan, struct sizebuf_s *psizebuf);

typedef void (*PFN_TEXTURELOAD)(const char *pszName, int dxWidth, int dyHeight, char *pbData);
typedef void (*PFN_MODELLOAD)(struct model_s *pmodel, void *pvBuf);

typedef void (*PFN_FRAMEBEGIN)();
typedef void (*PFN_FRAMERENDER1)();
typedef void (*PFN_FRAMERENDER2)();

typedef void (*PFN_SETMODSHELPERS)(modshelpers_t *pmodshelpers);
typedef void (*PFN_SETMODCHELPERS)(modchelpers_t *pmodchelpers);
typedef void (*PFN_SETENGDATA)(engdata_t *pengdata);

typedef void (*PFN_CONNECTCLIENT)(int iPlayer);
typedef void (*PFN_RECORDIP)(unsigned int pnIP);
typedef void (*PFN_PLAYERSTATUS)(unsigned char *pbData, int cbData);

typedef void (*PFN_SETENGINEVERSION)(int nVersion);

// typedef class CMachine *(*PFN_PCMACHINE)();
typedef int (*PFN_PCMACHINE)();
typedef void (*PFN_SETIP)(int ijump);
typedef void (*PFN_EXECUTE)();

typedef struct modfuncs_s
{
	// Functions for the pcode interpreter
	PFN_LOADMOD m_pfnLoadMod;
	PFN_CLOSEMOD m_pfnCloseMod;
	PFN_NCALL m_pfnNCall;

	// API destination functions
	PFN_GETCLDSTADDRS m_pfnGetClDstAddrs;
	PFN_GETENGDSTADDRS m_pfnGetEngDstAddrs;

	// Miscellaneous functions
	PFN_MODULELOADED m_pfnModuleLoaded;					// Called right after the module is loaded

	// Functions for processing network traffic
	PFN_PROCESSOUTGOINGNET m_pfnProcessOutgoingNet;		// Every outgoing packet gets run through this
	PFN_PROCESSINCOMINGNET m_pfnProcessIncomingNet;		// Every incoming packet gets run through this

	// Resource functions
	PFN_TEXTURELOAD m_pfnTextureLoad;					// Called as each texture is loaded
	PFN_MODELLOAD m_pfnModelLoad;						// Called as each model is loaded

	// Functions called every frame
	PFN_FRAMEBEGIN m_pfnFrameBegin;						// Called at the beginning of each frame cycle
	PFN_FRAMERENDER1 m_pfnFrameRender1;					// Called at the beginning of the render loop
	PFN_FRAMERENDER2 m_pfnFrameRender2;					// Called at the end of the render loop

	// Module helper transfer
	PFN_SETMODSHELPERS m_pfnSetModSHelpers;
	PFN_SETMODCHELPERS m_pfnSetModCHelpers;
	PFN_SETENGDATA m_pfnSetEngData;

	// Which version of the module is this?
	int m_nVersion;

	// Miscellaneous game stuff
	PFN_CONNECTCLIENT m_pfnConnectClient;				// Called whenever a new client connects
	PFN_RECORDIP m_pfnRecordIP;							// Secure master has reported a new IP for us
	PFN_PLAYERSTATUS m_pfnPlayerStatus;					// Called whenever we receive a PlayerStatus packet

	// Recent additions
	PFN_SETENGINEVERSION m_pfnSetEngineVersion;			// 1 = patched engine

	// reserved for future expansion
	int m_nVoid2;
	int m_nVoid3;
	int m_nVoid4;
	int m_nVoid5;
	int m_nVoid6;
	int m_nVoid7;
	int m_nVoid8;
	int m_nVoid9;
} modfuncs_t;

enum
{
	k_nEngineVersion15Base	= 0,
	k_nEngineVersion15Patch,
	k_nEngineVersion16Base,
	k_nEngineVersion16Validated	// 1.6 engine with built-in validation
};

typedef struct validator_s
{
	int m_nRandomizer;			// Random number to be XOR'd into all subsequent fields
	int m_nSignature1;			// First signature that identifies this structure
	int m_nSignature2;			// Second signature
	int m_pbCode;				// Beginning of the code block
	int m_cbCode;				// Size of the code block
	int m_nChecksum;			// Checksum of the code block
	int m_nSpecial;				// For engine, 1 if hw.dll, 0 if sw.dll.  For client, pclfuncs checksum
	int m_nCompensator;			// Keeps the checksum correct
} validator_t;

#define k_nChecksumCompensator 0x36a8f09c	// Don't change this value: it's hardcorded in cdll_int.cpp,

#define k_nModuleVersionCur 0x43210004
