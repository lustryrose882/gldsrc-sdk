/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#pragma once

// Client's stuff
#include "dlls/extdll.h"

#include "common/const.h"
#include "engine/edict.h"
#include "engine/eiface.h"
#include "common/const.h"
#include "common/vmodes.h"
#include "engine/usermsg.h"
#include "engine/eventhook.h"
#include "engine/APIProxy.h"
#include "common/r_studioint.h"
#include "common/cl_entity.h"
#include "common/triangleapi.h"
#include "common/pmtrace.h"
#include "pm_shared/pm_defs.h"
#include "pm_shared/pm_info.h"
#include "common/cvardef.h"
#include "engine/studio.h"
#include "common/event_args.h"
#include "common/event_flags.h"
#include "engine/keydefs.h"
#include "common/kbutton.h"
#include "common/com_model.h"
#include "common/ref_params.h"
#include "common/studio_event.h"
#include "common/net_api.h"
#include "common/r_efx.h"
#include "common/parsemsg.h"
#include "common/event_api.h"
#include "common/screenfade.h"
#include "common/entity_types.h"
#include "engine/cdll_int.h"
#include "engine/svcmsg.h"
#include "dlls/cdll_dll.h"
#include "engine/client.h"

struct cl_exportmsgfuncs_t
{
	// Read functions
	int      (*MSG_ReadChar)();
	int      (*MSG_ReadByte)();
	int      (*MSG_ReadShort)();
	int      (*MSG_ReadLong)();
	float    (*MSG_ReadFloat)();
	int      (*MSG_ReadBuf)(int iSize, void *pbuf);
	char    *(*MSG_ReadString)();
	char    *(*MSG_ReadStringLine)();
	float    (*MSG_ReadAngle)();
	float    (*MSG_ReadHiresAngle)();
	//void     (*MSG_ReadUsercmd)(usercmd_t *to, usercmd_t *from);
	float    (*MSG_ReadCoord)();
	void     (*MSG_ReadVec3Coord)(sizebuf_t *sb, vec_t *fa);

	// Read bit functions
	qboolean (*MSG_IsBitReading)();
	void     (*MSG_StartBitReading)(sizebuf_t *buf);
	void     (*MSG_EndBitReading)(sizebuf_t *buf);
	uint32_t (*MSG_PeekBits)(int numbits);
	int      (*MSG_ReadOneBit)();
	uint32_t (*MSG_ReadBits)(int numbits);
	int      (*MSG_ReadSBits)(int numbits);
	float    (*MSG_ReadBitCoord)();
	void     (*MSG_ReadBitVec3Coord)(vec_t *fa);
	float    (*MSG_ReadBitAngle)(int numbits);
	int      (*MSG_ReadBitData)(void *dest, int length);
	char    *(*MSG_ReadBitString)();
	int      (*MSG_CurrentBit)();

	// Write functions
	void     (*MSG_WriteByte)(sizebuf_t *sb, int c);
	void     (*MSG_WriteShort)(sizebuf_t *sb, int c);
	void     (*MSG_WriteLong)(sizebuf_t *sb, int c);
	void     (*MSG_WriteFloat)(sizebuf_t *sb, float f);
	void     (*MSG_WriteAngle)(sizebuf_t *sb, float f);
	void     (*MSG_WriteHiresAngle)(sizebuf_t *sb, float f);
	void     (*MSG_WriteString)(sizebuf_t *sb, const char *s);
	//void     (*MSG_WriteUsercmd)(sizebuf_t *sb, usercmd_t *to, usercmd_t *from);
	void     (*MSG_WriteCoord)(sizebuf_t *sb, float f);
	void     (*MSG_WriteVec3Coord)(sizebuf_t *sb, const vec_t *fa);
	void     (*MSG_WriteBuf)(sizebuf_t *sb, int iSize, const void *buf);

	// Write bit functions
	void     (*MSG_StartBitWriting)(sizebuf_t *buf);
	void     (*MSG_WriteBits)(uint32_t data, int numbits);
	void     (*MSG_WriteBitVec3Coord)(const float *fa);
	void     (*MSG_EndBitWriting)(sizebuf_t *buf);
	qboolean (*MSG_IsBitWriting)();
	void     (*MSG_WriteOneBit)(int nValue);
	void     (*MSG_WriteSBits)(int data, int numbits);
	void     (*MSG_WriteBitCoord)(float f);
	void     (*MSG_WriteBitAngle)(float fAngle, int numbits);
	void     (*MSG_WriteBitData)(void *src, int length);
	void     (*MSG_WriteBitString)(const char *p);
	void     (*SZ_Write)(sizebuf_t *buf, const void *data, int length);
	void     (*SZ_Print)(sizebuf_t *buf, const char *data);
	void     (*SZ_Clear)(sizebuf_t *buf);
	void    *(*SZ_GetSpace)(sizebuf_t *buf, int length);
	bool     (*NetMsgTransformToBuffer)(class CSizeBuf *buf);
};

namespace plugmod {
	class IPluginCallback;
}

#define DECLARE_FUNC(name, arg1name, postvalue)                                                                                                              \
protected:                                                                                                                                                   \
	bool (*name##_Internal)(const char *arg1name, plugmod::IPluginCallback *callback, bool post);                                                            \
	bool (*Un##name##_Internal)(const char *arg1name, plugmod::IPluginCallback *callback);                                                                   \
public:                                                                                                                                                      \
	bool name(const char *arg1name, plugmod::IPluginCallback *callback, bool post = postvalue) { return this->name##_Internal(arg1name, callback, post); }   \
	bool Un##name(const char *arg1name, plugmod::IPluginCallback *callback) { return this->Un##name##_Internal(arg1name, callback); }                        \

struct cl_exportfuncs_t
{
	DECLARE_FUNC(RegisterCallback,  pszName,    true);
	DECLARE_FUNC(RegisterSVCMsg,    pszMsgName, false);
	DECLARE_FUNC(RegisterUserMsg,   pszMsgName, false);
	DECLARE_FUNC(RegisterCmd,       pszCmdName, false);
};

extern cl_exportfuncs_t     gExportfuncs;
extern cl_exportmsgfuncs_t  gExportMsgFuncs;

extern svc_func_t          *g_pSVCfuncs;
extern cldll_func_t        *g_pClient;
extern cl_enginefunc_t     *g_pEngine;
extern engine_studio_api_t *g_pStudio;

extern cldll_func_t         g_Client;
extern cl_enginefunc_t      g_Engine;
extern engine_studio_api_t  g_Studio;
