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

#include "ref_params.h"
#include "IObjectContainer.h"
#include "net/BitBuffer.h"
#include "common/demo_info.h"

class IWorld;
class IProxy;
class DirectorCmd;
class IBaseSystem;
class ISystemModule;

const int DEMOPLAYER_API_VERSION = 1;

struct demofuncs_t
{
	int version;

	void (*pfnDemoFullyLoaded)(const char *filename);
	void (*pfnReceiveSignal)(ISystemModule *module, unsigned int signal, void *data);
	bool (*pfnExecuteCommand)(int commandID, const char *commandLine);
	void (*pfnShutdown)();
	void (*pfnNewGame)(IWorld *world, IProxy *proxy);
	void (*pfnWriteCommands)(BitBuffer *stream, float startTime, float endTime);
	void (*pfnExecuteDirectorCmd)(DirectorCmd *cmd);
	void (*pfnSaveGame)(const char *filename);
	void (*pfnLoadGame)(const char *filename);
	void (*pfnStop)();
	void (*pfnGetDemoViewInfo)(struct demoframe_s *from, struct demoframe_s *to, ref_params_t *rp, float *view, int *viewmodel);
	int  (*pfnReadDemoMessage)(unsigned char *buffer, int size);
};

enum
{
	DIRECTOR_SIGNAL_UPDATE = 1,
	DIRECTOR_SIGNAL_LASTCMD,
};

class IDemoPlayer
{
public:
	virtual ~IDemoPlayer() {}

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

	virtual void NewGame(IWorld *world, IProxy *proxy = nullptr) = 0;
	virtual const char *GetModName() = 0;
	virtual void WriteCommands(BitBuffer *stream, float startTime, float endTime) = 0;
	virtual int AddCommand(DirectorCmd *cmd) = 0;
	virtual bool RemoveCommand(int index) = 0;
	virtual DirectorCmd *GetLastCommand() = 0;
	virtual IObjectContainer<DirectorCmd> *GetCommands() = 0;
	virtual void SetWorldTime(double time, bool relative) = 0;
	virtual void SetTimeScale(float scale) = 0;
	virtual void SetPaused(bool state) = 0;
	virtual void SetEditMode(bool state) = 0;
	virtual void SetMasterMode(bool state) = 0;
	virtual bool IsPaused() = 0;
	virtual bool IsLoading() = 0;
	virtual bool IsActive() = 0;
	virtual bool IsEditMode() = 0;
	virtual bool IsMasterMode() = 0;
	virtual void RemoveFrames(double starttime, double endtime) = 0;
	virtual void ExecuteDirectorCmd(DirectorCmd *cmd) = 0;
	virtual double GetWorldTime() = 0;
	virtual double GetStartTime() = 0;
	virtual double GetEndTime() = 0;
	virtual float GetTimeScale() = 0;
	virtual IWorld *GetWorld() = 0;
	virtual const char *GetFileName() = 0;
	virtual bool SaveGame(const char *filename) = 0;
	virtual bool LoadGame(const char *filename) = 0;
	virtual void Stop() = 0;
	virtual void ForceHLTV(bool state) = 0;
	virtual void GetDemoViewInfo(ref_params_t *rp, float *view, int *viewmodel) = 0;
	virtual int ReadDemoMessage(unsigned char *buffer, int size) = 0;
	virtual void ReadNetchanState(int *incoming_sequence, int *incoming_acknowledged, int *incoming_reliable_acknowledged, int *incoming_reliable_sequence, int *outgoing_sequence, int *reliable_sequence, int *last_reliable_sequence) = 0;
	virtual bool InitApiFuncs(demofuncs_t *pDemofuncs) = 0;
};

#define DEMOPLAYER_INTERFACE_VERSION "demoplayer001"
