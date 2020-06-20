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

#include "usercmd.h"

// Don't allow overflow
#define SIZEBUF_CHECK_OVERFLOW	0
#define SIZEBUF_ALLOW_OVERFLOW	BIT(0)
#define SIZEBUF_OVERFLOWED		BIT(1)

typedef struct sizebuf_s
{
	const char *buffername;
	uint16_t flags;
	byte *data;
	int maxsize;
	int cursize;
} sizebuf_t;

#if defined(_HW) ||  defined(SWDS) ||  defined(_CLIENT)

typedef struct bf_read_s bf_read_t;
typedef struct bf_write_s bf_write_t;

extern bf_read_t bfread;
extern bf_write_t bfwrite;

extern sizebuf_t net_message;
extern int msg_badread;
extern int msg_readcount;

void MSG_WriteChar(sizebuf_t *sb, int c);
void MSG_WriteByte(sizebuf_t *sb, int c);
void MSG_WriteShort(sizebuf_t *sb, int c);
void MSG_WriteWord(sizebuf_t *sb, int c);
void MSG_WriteLong(sizebuf_t *sb, int c);
void MSG_WriteFloat(sizebuf_t *sb, float f);
void MSG_WriteString(sizebuf_t *sb, const char *s);
void MSG_WriteBuf(sizebuf_t *sb, int iSize, const void *buf);
void MSG_WriteAngle(sizebuf_t *sb, float f);
void MSG_WriteHiresAngle(sizebuf_t *sb, float f);
void MSG_WriteUsercmd(sizebuf_t *buf, usercmd_t *to, usercmd_t *from);
void MSG_BitOpsInit();
void MSG_WriteOneBit(int nValue);
void MSG_StartBitWriting(sizebuf_t *buf);
NOXREF qboolean MSG_IsBitWriting();
void MSG_EndBitWriting(sizebuf_t *buf);
void MSG_WriteBits(uint32_t data, int numbits);
void MSG_WriteSBits(int data, int numbits);
void MSG_WriteBitString(const char *p);
void MSG_WriteBitData(void *src, int length);
void MSG_WriteBitAngle(float fAngle, int numbits);
float MSG_ReadBitAngle(int numbits);
int MSG_CurrentBit();
NOXREF qboolean MSG_IsBitReading();
void MSG_StartBitReading(sizebuf_t *buf);
void MSG_EndBitReading(sizebuf_t *buf);
int MSG_ReadOneBit();
uint32_t MSG_ReadBits(int numbits);
NOXREF uint32_t MSG_PeekBits(int numbits);
int MSG_ReadSBits(int numbits);
NOXREF char *MSG_ReadBitString();
int MSG_ReadBitData(void *dest, int length);
NOXREF float MSG_ReadBitCoord();
void MSG_WriteBitCoord(const float f);
NOXREF void MSG_ReadBitVec3Coord(vec_t *fa);
void MSG_WriteBitVec3Coord(const vec_t *fa);
NOXREF float MSG_ReadCoord();
void MSG_WriteCoord(sizebuf_t *sb, const float f);
NOXREF void MSG_ReadVec3Coord(sizebuf_t *sb, vec_t *fa);
NOXREF void MSG_WriteVec3Coord(sizebuf_t *sb, const vec_t *fa);
void MSG_BeginReading();
void MSG_BeginReadingCopy();
void MSG_EndReadingCopy();
int MSG_ReadChar();
int MSG_ReadByte();
int MSG_ReadShort();
NOXREF int MSG_ReadWord();
int MSG_ReadLong();
NOXREF float MSG_ReadFloat();
int MSG_ReadBuf(int iSize, void *pbuf);
char *MSG_ReadString();
char *MSG_ReadStringLine();
NOXREF float MSG_ReadAngle();
NOXREF float MSG_ReadHiresAngle();
void MSG_ReadUsercmd(usercmd_t *to, usercmd_t *from);

void SZ_Alloc(const char *name, sizebuf_t *buf, int startsize);
void SZ_Clear(sizebuf_t *buf);
qboolean SZ_HasSpace(sizebuf_t *buf, int length);
void *SZ_GetSpace(sizebuf_t *buf, int length);
void SZ_Write(sizebuf_t *buf, const void *data, int length);
void SZ_Print(sizebuf_t *buf, const char *data);

#endif // #if defined(_HW) ||  defined(SWDS) ||  defined(_CLIENT)
