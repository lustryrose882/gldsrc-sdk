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

#include <coordsize.h>

#include "tier0/platform.h"
#include "tier0/dbg.h" // Error
#include "tier0/commonmacros.h" // ARRAYSIZE

class CSizeBuf
{
private:
	struct bf_write_t
	{
		uint32_t nCurOutputBit;
		uint8_t *pOutByte;
	};

	struct bf_read_t
	{
		uint32_t nMsgReadCount;	// was msg_readcount
		uint32_t nBitFieldReadStartByte;
		uint32_t nBytesRead;
		uint32_t nCurInputBit;
		uint8_t *pInByte;
	};

	static const uint32_t BITS_WRITING_RESERVE = 5;

protected:
	uint8_t *m_Data;
	uint8_t  m_nFlags;
	uint32_t m_MaxSize;
	uint32_t m_CurSize;
	uint32_t m_ReadCount;
	bool m_bOverflowed;
	bool m_bBadRead;
	bool m_bBitsWriting;
	bool m_bBitsReading;
	bool m_bDoFree;
	bf_read_t m_BFRead;
	bf_write_t m_BFWrite;

	void ensureNoBitsOp();
	void ensureBitsWriting();
	void ensureBitsReading();

	template <typename T>
	inline bool WritePrimitive(T val);

	template <typename T>
	inline T ReadPrimitive();

public:
	enum SizeBufFlags_t
	{
		READ_ONLY = 0x1	// For external buffers
	};

	CSizeBuf();
	CSizeBuf(const void *buf, uint32_t maxSize, uint32_t unFlags = 0);
	CSizeBuf(uint32_t size);
	~CSizeBuf();

	uint8_t*    GetSpace(uint32_t len);
	bool        Write(const void *data, uint32_t length);
	bool        Print(const char *data);

	bool        WriteChar(int8_t val);
	bool        WriteByte(uint8_t val);
	bool        WriteShort(int16_t val);
	bool        WriteWord(uint16_t val);
	bool        WriteDWord(uint32_t val);
	bool        WriteLong(int32_t val);
	bool        WriteFloat(float val);
	bool        WriteAngle(float val);
	bool        WriteWriteHiresAngle(float val);
	bool        WriteString(const char *s);
	bool        WriteBuf(void *src, uint32_t length);
	bool        WriteI64(int64_t val);
	bool        WriteU64(uint64_t val);
	void        WriteVec3Coord(const float *fa);

	void        StartBitWriting();
	void        EndBitWriting();
	void        WriteOneBit(int val);
	void        WriteBits(uint32_t data, uint32_t numbits);
	void        WriteSBits(int data, uint32_t numbits);
	void        WriteBitString(const char *p);
	void        WriteBitData(void *src, uint32_t length);
	void        WriteBitFloat(float data);
	void        WriteBitAngle(float fAngle, uint32_t numbits);
	void        WriteBitCoord(float data);
	void        WriteBitVec3Coord(const float *fa);

	void        StartBitReading();
	void        EndBitReading();
	int         CurrentBit();

	int         ReadOneBit();
	uint32_t    PeekBits(int numbits);
	uint32_t    ReadBits(uint32_t numbits);
	int         ReadSBits(uint32_t numbits);
	const char *ReadBitString();
	int         ReadBitData(void *dest, int length);
	float       ReadBitFloat();
	float       ReadBitAngle(uint32_t numbits);
	float       ReadBitCoord();
	void        ReadBitVec3Coord(float *fa);

	int8_t      ReadChar();
	uint8_t     ReadByte();
	int16_t     ReadShort();
	uint16_t    ReadWord();
	uint32_t    ReadDWord();
	int32_t     ReadLong();
	float       ReadFloat();
	float       ReadAngle();
	float       ReadHiresAngle();
	char       *ReadString();
	bool        ReadString(char *dest, uint32_t length);
	char       *ReadStringLine();
	bool        ReadBuf(void *dest, uint32_t length, uint32_t startPos = 0);
	int64_t     ReadI64();
	uint64_t    ReadU64();
	void        ReadVec3Coord(float *fa);

	bool        Resize(int size);
	void        Free();
	void        Clear();
	void        FastClear();
	void        Reset();
	void        Cut(uint32_t cutpos, uint32_t cutlen);
	void        SetBuffer(const void *buf, uint32_t maxSize, uint32_t unFlags = 0);
	int         SkipString();
	void        SkipBits(int numbits);
	void        SkipBytes(int nbytes);
	void        ConcatBuffer(CSizeBuf *buffer);

	bool        IsReadOnly()         const { return (m_nFlags & READ_ONLY) == READ_ONLY; }
	bool        IsOverflowed()       const { return m_bOverflowed; }
	bool        IsBadRead()          const { return m_bBadRead; }
	int         SpaceLeft()          const { return m_MaxSize - m_ReadCount; }
	uint32_t    GetCurSize()         const { return m_CurSize; }
	uint8_t*    GetData()            const { return m_Data; }
	uint32_t    GetMaxSize()         const { return m_MaxSize; }
	uint8_t*    GetReadPtr()         const { return &m_Data[m_ReadCount]; }
	uint8_t*    GetWritePtr()        const { return &m_Data[m_CurSize]; }
	uint32_t    GetReadPos()         const { return m_ReadCount; }
	uint32_t    RemainingReadBytes() const { return m_CurSize - m_ReadCount;  }

	template <typename T = bool>
	bool HasSomethingToRead()        const { return !m_bBadRead && ((m_ReadCount + sizeof(T)) <= m_CurSize); }
};

template <size_t N>
class CSizeBufN: public CSizeBuf
{
public:
	CSizeBufN() :
		CSizeBuf(m_Buffer, N)
	{
	}

private:
	uint8_t m_Buffer[N];
};

inline void CSizeBuf::ensureNoBitsOp()
{
#if defined(_DEBUG)
	if (m_bBitsWriting || m_bBitsReading) {
		Error("%s: Invalid BitsWriting/BitsReading mode", __FUNC__);
	}
#endif
}

inline void CSizeBuf::ensureBitsWriting()
{
#if defined(_DEBUG)
	if (!m_bBitsWriting || m_bBitsReading) {
		Error("%s: Invalid BitsWriting/BitsReading mode", __FUNC__);
	}
#endif
}

inline void CSizeBuf::ensureBitsReading()
{
#if defined(_DEBUG)
	if (m_bBitsWriting || !m_bBitsReading) {
		Error("%s: Invalid BitsWriting/BitsReading mode", __FUNC__);
	}
#endif
}

template <typename T>
inline bool CSizeBuf::WritePrimitive(T val)
{
	ensureNoBitsOp();

	T *buf = (T *)GetSpace(sizeof(T));
	if (!buf)
	{
		return false;
	}

	*buf = val;
	return true;
}

template <typename T>
inline T CSizeBuf::ReadPrimitive()
{
	ensureNoBitsOp();

	T res;
	if (HasSomethingToRead<T>())
	{
		res = *(T *)(m_Data + m_ReadCount);
		m_ReadCount += sizeof(T);
	}
	else
	{
		m_bBadRead = true;
		res = (T)-1;
	}

	return res;
}
