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

#include "IBSPModel.h"
#include "IDirector.h"
#include "ISystemModule.h"

#include "pm_shared/pm_movevars.h"
#include "engine/usermsg.h"
#include "common/entity_state.h"

#include "tier1/checksum_crc.h"
#include "engine/custom.h"
#include "common/demo_info.h"

typedef struct serverinfo_s
{
	char address[64];
	char name[80];
	char map[16];
	char gamedir[256];
	char description[256];

	int activePlayers;
	int maxPlayers;

	char type; // HLServerType
	char os;
	char pw;
	bool mod;

	char url_info[256];
	char url_dl[256];
	char hlversion[256];

	int ver;
	int size;

	bool svonly;
	bool cldll;

	unsigned char protocol;
} serverinfo_t;

enum HLServerType {
	HLST_Dedicated,
	HLST_NonDedicated,
	HLST_TV,
};

class InfoString;
class NetAddress;

class IWorld
{
public:
	virtual ~IWorld() {}

	virtual bool Init(IBaseSystem *system, int serial, const char *name) = 0;
	virtual void RunFrame(double time) = 0;
	virtual void ReceiveSignal(ISystemModule *module, unsigned int signal, void *data) = 0;
	virtual void ExecuteCommand(int commandID, const char *commandLine) = 0;
	virtual void RegisterListener(ISystemModule *module) = 0;
	virtual void RemoveListener(ISystemModule *module) = 0;
	virtual IBaseSystem *GetSystem() = 0;
	virtual int GetSerial() = 0;
	virtual const char *GetStatusLine() = 0;
	virtual const char *GetType() = 0;
	virtual const char *GetName() = 0;
	virtual int GetState() = 0;
	virtual int GetVersion() = 0;
	virtual void ShutDown() = 0;

	virtual double GetTime() = 0;
	virtual NetAddress *GetGameServerAddress() = 0;
	virtual const char *GetLevelName() = 0;
	virtual const char *GetGameDir() = 0;
	virtual demoframe_t *GetFrameByTime(double time) = 0;
	virtual demoframe_t *GetFrameBySeqNr(unsigned int seqnr) = 0;
	virtual demoframe_t *GetLastFrame() = 0;
	virtual demoframe_t *GetFirstFrame() = 0;
	virtual int GetServerCount() = 0;
	virtual int GetSlotNumber() = 0;
	virtual int GetMaxClients() = 0;
	virtual int GetNumPlayers() = 0;
	virtual IBSPModel *GetWorldModel() = 0;
	virtual InfoString *GetServerInfoString() = 0;
	virtual bool GetPlayerInfoString(int playerNum, InfoString *infoString) = 0;
	virtual UserMsg *GetUserMsg(int msgNumber) = 0;
	virtual const char *GetHostName() = 0;
	virtual serverinfo_t *GetServerInfo() = 0;
	virtual bool IsPlayerIndex(int index) = 0;
	virtual bool IsVoiceEnabled() = 0;
	virtual bool IsActive() = 0;
	virtual bool IsPaused() = 0;
	virtual bool IsComplete() = 0;
	virtual bool IsHLTV() = 0;
	virtual void Reset() = 0;
	virtual void SetServerInfo(int protocol, CRC32_t nserverCRC, byte *nclientdllmd5, int nmaxclients, int nplayernum, int ngametype, char *ngamedir, char *nservername, char *nlevelname) = 0;
	virtual void SetServerInfoString(const char *infostring) = 0;
	virtual void SetServerInfo(serverinfo_t *serverinfo) = 0;
	virtual void UpdateServerInfo() = 0;
	virtual void SetPaused(bool state) = 0;
	virtual void SetTime(double newTime) = 0;
	virtual void SetBufferSize(float seconds) = 0;
	virtual void SetVoiceEnabled(bool state) = 0;
	virtual void SetMoveVars(movevars_t *nmovevars) = 0;
	virtual void SetCDInfo(int ncdtrack, int nlooptrack) = 0;
	virtual void SetHLTV(bool state) = 0;
	virtual void SetExtraInfo(const char *nclientfallback, int nallowCheats) = 0;
	virtual void SetViewEntity(int nviewentity) = 0;
	virtual void SetGameServerAddress(NetAddress *address) = 0;
	virtual void SetHostName(const char *name) = 0;
	virtual void NewGame(int newServerCount) = 0;
	virtual void FinishGame() = 0;
	virtual bool SaveAsDemo(const char *filename, IDirector *director) = 0;
	virtual void StopGame() = 0;
	virtual int FindUserMsgByName(const char *name) = 0;
	virtual void ParseDeltaDescription(BitBuffer *stream) = 0;
	virtual void ParseBaseline(BitBuffer *stream) = 0;
	virtual void ParseEvent(BitBuffer *stream) = 0;
	virtual void ParseClientData(BitBuffer *stream, unsigned int deltaSeqNr, BitBuffer *to, clientdata_t *clientData) = 0;
	virtual bool GetUncompressedFrame(unsigned int seqNr, demoframe_t *frame) = 0;
	virtual bool UncompressEntitiesFromStream(demoframe_t *frame, BitBuffer *stream) = 0;
	virtual bool UncompressEntitiesFromStream(demoframe_t *frame, BitBuffer *stream, unsigned int from) = 0;
	virtual bool GetClientData(unsigned int SeqNr, clientdata_t *clientData) = 0;
	virtual bool GetClientData(demoframe_t *frame, clientdata_t *clientData) = 0;
	virtual int AddFrame(demoframe_t *newFrame) = 0;
	virtual bool AddResource(resource_t *resource) = 0;
	virtual void AddLightStyle(int index, const char *style) = 0;
	virtual bool AddSignonData(unsigned char type, unsigned char *data, int size) = 0;
	virtual bool AddUserMessage(int msgNumber, int size, const char *name) = 0;
	virtual void AddBaselineEntity(int index, entity_state_t *ent) = 0;
	virtual void AddInstancedBaselineEntity(int index, entity_state_t *ent) = 0;
	virtual void UpdatePlayer(int playerNum, int userId, const char *infostring, const char *hashedcdkey) = 0;
	virtual void WriteFrame(demoframe_t *frame, unsigned int lastFrameSeqnr, BitBuffer *reliableStream, BitBuffer *unreliableStream, unsigned int deltaSeqNr, unsigned int clientDelta, bool addVoice) = 0;
	virtual void WriteNewData(BitBuffer *stream) = 0;
	virtual void WriteClientUpdate(BitBuffer *stream, int playerIndex) = 0;
	virtual void WriteMovevars(BitBuffer *stream) = 0;
	virtual void WriteSigonData(BitBuffer *stream) = 0;
	virtual void WriteLightStyles(BitBuffer *stream) = 0;
	virtual int RemoveFrames(unsigned int startSeqNr, unsigned int endSeqNr) = 0;
	virtual int DuplicateFrames(unsigned int startSeqNr, unsigned int endSeqNr) = 0;
	virtual int MoveFrames(unsigned int startSeqNr, unsigned int endSeqNr, double destSeqnr) = 0;
	virtual int RevertFrames(unsigned int startSeqNr, unsigned int endSeqNr) = 0;
};

#define WORLD_INTERFACE_VERSION "world001"
