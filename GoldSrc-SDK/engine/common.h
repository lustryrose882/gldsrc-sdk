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

#include "const.h"
#include "qlimits.h"
#include "bspfile.h"
#include "filesystem.h"
#include "quakedef.h"
#include "usercmd.h"
#include "info.h"
#include "com_model.h"

#if !defined(STRTOOLS_DEFINES)
	#ifdef _WIN32
		#define PATHSEPARATOR(c) ((c) == '\\' || (c) == '/')
		const auto CORRECT_PATH_SEPARATOR    = '\\';
		const auto INCORRECT_PATH_SEPARATOR  = '/';
		const auto CORRECT_PATH_PSEPARATOR   = "\\";
		const auto INCORRECT_PATH_PSEPARATOR = "/";
	#else
		#define PATHSEPARATOR(c) ((c) == '/')
		const auto CORRECT_PATH_SEPARATOR    = '/';
		const auto INCORRECT_PATH_SEPARATOR  = '\\';
		const auto CORRECT_PATH_PSEPARATOR   = "/";
		const auto INCORRECT_PATH_PSEPARATOR = "\\";
	#endif // #ifdef _WIN32
#endif // #if !defined(STRTOOLS_DEFINES)

#define COM_TOKEN_LEN			2048

#define MAX_NUM_ARGVS			50
#define NUM_SAFE_ARGVS			7

#define COM_COPY_CHUNK_SIZE		1024
#define COM_MAX_CMD_LINE		256

typedef struct downloadtime_s
{
	qboolean bUsed;
	float fTime;
	int nBytesRemaining;
} downloadtime_t;

typedef struct incomingtransfer_s
{
	qboolean doneregistering;
	int percent;
	qboolean downloadrequested;
	downloadtime_t rgStats[8];
	int nCurStat;
	int nTotalSize;
	int nTotalToTransfer;
	int nRemainingToTransfer;
	float fLastStatusUpdate;
	qboolean custom;
} incomingtransfer_t;

extern char serverinfo[MAX_INFO_STRING];

extern qboolean bigendien;

extern short (*BigShort)(short l);
extern short (*LittleShort)(short l);
extern int (*BigLong)(int l);
extern int (*LittleLong)(int l);
extern float (*BigFloat)(float l);
extern float (*LittleFloat)(float l);

extern int com_argc;
extern char **com_argv;

extern char com_token[COM_TOKEN_LEN];

extern qboolean com_ignorecolons;
extern qboolean s_com_token_unget;
extern char com_clientfallback[MAX_PATH];
extern char com_gamedir[MAX_PATH];
extern char com_cmdline[COM_MAX_CMD_LINE];

extern cache_user_t *loadcache;
extern unsigned char *loadbuf;
extern int loadsize;

int build_number();
char *Info_Serverinfo();

unsigned char COM_Nibble(char c);
void COM_HexConvert(const char *pszInput, int nInputLength, unsigned char *pOutput);
char *COM_BinPrintf(unsigned char *buf, int nLen);
void COM_ExplainDisconnection(qboolean bPrint, const char *fmt, ...);
void COM_ExtendedExplainDisconnection(qboolean bPrint, const char *fmt, ...);

int LongSwap(int l);
short ShortSwap(short l);
short ShortNoSwap(short l);
int LongNoSwap(int l);
float FloatSwap(float f);
float FloatNoSwap(float f);

const char *COM_SkipPath(const char *pathname);
void COM_StripExtension(const char *in, char *out, int outLen);
const char *COM_FileExtension(const char *in);
void COM_FileBase(const char *in, char *out);
const char *COM_FileBase_s(const char *in, char *out, int size);
qboolean COM_HasFileExtension(const char *in, char *ext);
void COM_AddExtension(char *path, const char *extension, int size);
void COM_DefaultExtension(char *path, const char *extension, int pathStringLength);
void COM_UngetToken();
char *COM_Parse(char *data);
char *COM_ParseLine(char *data);
int COM_TokenWaiting(const char *buffer);
int COM_CheckParm(const char *parm);
void COM_InitArgv(int argc, char *argv[]);
void COM_Init(const char *basedir);
const char *va(const char *format, ...);
const char *vstr(vec_t *v);
int memsearch(unsigned char *start, int count, int search);
void COM_WriteFile(const char *filename, void *data, int len);
void COM_FixSlashes(char *pname);
void COM_FixURLSlashes(char *pname);
char *COM_CloneString(const char *original);
void COM_CreateDirHierarchy(const char *path);
int COM_CreateDirectory(const char *path);
void COM_CreatePath(const char *path);
const char *COM_NextToken(char **pbuf);
void COM_CopyFile(const char *netpath, const char *cachepath);
qboolean COM_ExpandFilename(const char *fileName, char *nameOutBuffer, int nameOutBufferSize);
int COM_FileSize(const char *filename);
unsigned char *COM_LoadFile(const char *path, int usehunk, int *pLength);
void COM_FreeFile(void *buffer);
void COM_CopyFileChunk(FileHandle_t dst, FileHandle_t src, int nSize);
unsigned char *COM_LoadFileLimit(const char *path, int pos, int cbmax, int *pcbread, FileHandle_t *phFile);
unsigned char *COM_LoadHunkFile(const char *path);
unsigned char *COM_LoadTempFile(const char *path, int *pLength);
void COM_LoadCacheFile(const char *path, struct cache_user_s *cu);
unsigned char *COM_LoadStackFile(const char *path, void *buffer, int bufsize, int *length);
void COM_Shutdown();
void COM_AddAppDirectory(const char *pszBaseDir);
void COM_AddDefaultDir(const char *pszDir);
void COM_StripTrailingSlash(char *ppath);
void COM_ParseDirectoryFromCmd(const char *pCmdName, char *pDirName, int iOutputSize, const char *pDefault);
qboolean COM_SetupDirectories();
void COM_CheckPrintMap(dheader_t *header, const char *mapname, qboolean bShowOutdated);
void COM_ListMaps(const char *pszSubString);
void COM_Log(const char *pszFile, const char *fmt, ...);
unsigned char *COM_LoadFileForMe(const char *filename, int *pLength);
int COM_CompareFileTime(const char *filename1, const char *filename2, int *iCompare);
void COM_GetGameDir(char *szGameDir);
int COM_EntsForPlayerSlots(int nPlayers);
void COM_NormalizeAngles(vec_t *angles);
void COM_Munge(unsigned char *data, int len, int seq);
void COM_UnMunge(unsigned char *data, int len, int seq);
void COM_Munge2(unsigned char *data, int len, int seq);
void COM_UnMunge2(unsigned char *data, int len, int seq);
void COM_Munge3(unsigned char *data, int len, int seq);
void COM_UnMunge3(unsigned char *data, int len, int seq);
void COM_Munge4(unsigned char *data, int len, int seq, unsigned char(&mungify_table)[16]);
void COM_UnMunge4(unsigned char *data, int len, int seq, unsigned char(&mungify_table)[16]);
unsigned int COM_GetApproxWavePlayLength(const char *filepath);
