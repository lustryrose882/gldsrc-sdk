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

class BitBuffer
{
public:
	BitBuffer();
	BitBuffer(unsigned int size);
	BitBuffer(void *newData, unsigned int size);
	virtual ~BitBuffer();

	unsigned int PeekBits(int numbits);
	int CurrentBit();
	int CurrentSize();
	int GetCurSize() { return CurrentSize(); } // GetReadPos
	int GetReadPos() { return CurrentSize(); } // GetReadPos
	unsigned char *CurrentByte();
	unsigned char *GetReadPtr() { return CurrentByte(); }

	int GetMaxSize() const { return m_MaxSize; }
	unsigned char *GetData() const { return m_Data; }
	bool IsOverflowed() const { return m_Overflowed; }

	void SetBuffer(void *buffer, int size);
	void Free();
	void Reset();
	void Clear();
	void FastClear();
	int SpaceLeft();
	void EndBitMode();
	void StartBitMode();
	bool Resize(unsigned int size);
	void ConcatBuffer(BitBuffer *buffer);
	int SkipString();

	void SkipBits(int numbits);
	void SkipBytes(int numbits);

	void AlignByte();

	// function's read stuff
	unsigned int ReadBits(int numbits);
	int ReadBit();
	int ReadChar();
	int ReadByte();
	int ReadShort();
	int ReadWord();

	unsigned int ReadLong();
	float ReadFloat();
	char *ReadString();
	char *ReadStringLine();
	char *ReadBitString();
	int ReadSBits(int numbits);
	float ReadBitAngle(int numbits);
	int ReadBitData(void *dest, int length);
	bool ReadBuf(int iSize, void *pbuf);
	float ReadAngle();
	float ReadHiresAngle();
	float ReadCoord();
	float ReadBitCoord();
	void ReadBitVec3Coord(float *fa);

	// function's write stuff
	void WriteBits(unsigned int data, int numbits);
	void WriteBit(int c);
	void WriteChar(int c);
	void WriteByte(int c);
	void WriteShort(int c);
	void WriteWord(int c);
	void WriteLong(unsigned int c);
	void WriteFloat(float f);
	void WriteString(const char *p);
	void WriteBitString(const char *p);
	void WriteSBits(int data, int numbits);
	void WriteBitAngle(float fAngle, int numbits);
	void WriteBitData(void *src, int length);
	void WriteBuf(const void *buf, int iSize);
	void WriteBuf(BitBuffer *buf, int length);
	void WriteAngle(float f);
	void WriteHiresAngle(float f);
	void WriteCoord(float f);

	bool m_Overflowed;
	unsigned char *m_Data;
	unsigned char *m_CurByte;
	int m_CurBit;
	int m_MaxSize;

protected:
	bool m_LittleEndian;
	bool m_OwnData;
};
