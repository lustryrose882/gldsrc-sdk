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

#include "tier0/basetypes.h" // min
#include "Sizebuf.h"

CSizeBuf::CSizeBuf() :
	m_Data(nullptr),
	m_MaxSize(0),
	m_CurSize(0),
	m_ReadCount(0),
	m_bOverflowed(false),
	m_bBadRead(false),
	m_bBitsWriting(false),
	m_bBitsReading(false),
	m_bDoFree(false)
{
	memset(&m_BFRead, 0, sizeof(m_BFRead));
	memset(&m_BFWrite, 0, sizeof(m_BFWrite));
}

CSizeBuf::CSizeBuf(uint32_t size) :
	CSizeBuf()
{
	Resize(size);
}

CSizeBuf::CSizeBuf(const void *buf, uint32_t maxSize, uint32_t unFlags) :
	CSizeBuf()
{
	SetBuffer(buf, maxSize, unFlags);
}

CSizeBuf::~CSizeBuf()
{
	Free();
}

uint8_t *CSizeBuf::GetSpace(uint32_t len)
{
	if (m_bOverflowed)
	{
		return nullptr;
	}

	if (len < 0)
	{
		Error("%s: %i negative length on", __FUNCTION__, len);
	}

	if ((m_CurSize + len /*+ BITS_WRITING_RESERVE*/) > m_MaxSize)
	{
		m_bOverflowed = true;
		return nullptr;
	}

	uint8_t *res = m_Data + m_CurSize;
	m_CurSize += len;
	return res;
}

bool CSizeBuf::Write(const void *data, uint32_t length)
{
	ensureNoBitsOp();
	uint8_t *buf = GetSpace(length);
	if (!buf)
		return false;

	memcpy(buf, data, length);
	return true;
}

bool CSizeBuf::Print(const char *data)
{
	ensureNoBitsOp();
	return Write(data, strlen(data) + 1);
}

bool CSizeBuf::WriteChar(int8_t val)
{
	return WritePrimitive(val);
}

bool CSizeBuf::WriteByte(uint8_t val)
{
	return WritePrimitive(val);
}

bool CSizeBuf::WriteShort(int16_t val)
{
	return WritePrimitive(val);
}

bool CSizeBuf::WriteWord(uint16_t val)
{
	return WritePrimitive(val);
}

bool CSizeBuf::WriteDWord(uint32_t val)
{
	return WritePrimitive(val);
}

bool CSizeBuf::WriteLong(int32_t val)
{
	return WritePrimitive(val);
}

bool CSizeBuf::WriteFloat(float val)
{
	return WritePrimitive(val);
}

bool CSizeBuf::WriteAngle(float val)
{
	return WriteByte((int64_t)(fmod((double)val, 360.0) * 256.0 / 360.0) & 0xFF);
}

bool CSizeBuf::WriteWriteHiresAngle(float val)
{
	return WriteShort((int64_t)(fmod((double)val, 360.0) * 65536.0 / 360.0) & 0xFFFF);
}

bool CSizeBuf::WriteString(const char *s)
{
	if (!s)
		s = "";

	return Write(s, strlen(s) + 1);
}

bool CSizeBuf::WriteBuf(void *src, uint32_t length)
{
	if (!src)
	{
		return false;
	}

	return Write(src, length);
}

bool CSizeBuf::WriteI64(int64_t val)
{
	return WritePrimitive(val);
}

bool CSizeBuf::WriteU64(uint64_t val)
{
	return WritePrimitive(val);
}

void CSizeBuf::WriteVec3Coord(const float *fa)
{
	StartBitWriting();
	WriteBitVec3Coord(fa);
	EndBitWriting();
}

const uint32_t BITTABLE[] =
{
	0x00000001, 0x00000002, 0x00000004, 0x00000008,
	0x00000010, 0x00000020, 0x00000040, 0x00000080,
	0x00000100, 0x00000200, 0x00000400, 0x00000800,
	0x00001000, 0x00002000, 0x00004000, 0x00008000,
	0x00010000, 0x00020000, 0x00040000, 0x00080000,
	0x00100000, 0x00200000, 0x00400000, 0x00800000,
	0x01000000, 0x02000000, 0x04000000, 0x08000000,
	0x10000000, 0x20000000, 0x40000000, 0x80000000,
	0x00000000,
};

const uint32_t ROWBITTABLE[] =
{
	0x00000000, 0x00000001, 0x00000003, 0x00000007,
	0x0000000F, 0x0000001F, 0x0000003F, 0x0000007F,
	0x000000FF, 0x000001FF, 0x000003FF, 0x000007FF,
	0x00000FFF, 0x00001FFF, 0x00003FFF, 0x00007FFF,
	0x0000FFFF, 0x0001FFFF, 0x0003FFFF, 0x0007FFFF,
	0x000FFFFF, 0x001FFFFF, 0x003FFFFF, 0x007FFFFF,
	0x00FFFFFF, 0x01FFFFFF, 0x03FFFFFF, 0x07FFFFFF,
	0x0FFFFFFF, 0x1FFFFFFF, 0x3FFFFFFF, 0x7FFFFFFF,
	0xFFFFFFFF,
};

const uint32_t INVBITTABLE[] =
{
	0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFB, 0xFFFFFFF7,
	0xFFFFFFEF, 0xFFFFFFDF, 0xFFFFFFBF, 0xFFFFFF7F,
	0xFFFFFEFF, 0xFFFFFDFF, 0xFFFFFBFF, 0xFFFFF7FF,
	0xFFFFEFFF, 0xFFFFDFFF, 0xFFFFBFFF, 0xFFFF7FFF,
	0xFFFEFFFF, 0xFFFDFFFF, 0xFFFBFFFF, 0xFFF7FFFF,
	0xFFEFFFFF, 0xFFDFFFFF, 0xFFBFFFFF, 0xFF7FFFFF,
	0xFEFFFFFF, 0xFDFFFFFF, 0xFBFFFFFF, 0xF7FFFFFF,
	0xEFFFFFFF, 0xDFFFFFFF, 0xBFFFFFFF, 0x7FFFFFFF,
	0xFFFFFFFF,
};

void CSizeBuf::StartBitWriting()
{
	ensureNoBitsOp();

	m_BFWrite.nCurOutputBit = 0;
	m_BFWrite.pOutByte = m_Data + m_CurSize;
	m_bBitsWriting = true;
}

void CSizeBuf::EndBitWriting()
{
	ensureBitsWriting();
	m_bBitsWriting = false;

	if (m_bOverflowed)
	{
		return;
	}

	*m_BFWrite.pOutByte &= (255 >> (8 - m_BFWrite.nCurOutputBit));
	GetSpace(1);
	m_BFWrite.nCurOutputBit = 0;
	m_BFWrite.pOutByte = 0;
}

void CSizeBuf::WriteOneBit(int val)
{
	ensureBitsWriting();

	if (m_BFWrite.nCurOutputBit >= 8)
	{
		m_BFWrite.pOutByte = GetSpace(1);
		m_BFWrite.nCurOutputBit = 0;
	}

	if (m_bOverflowed)
		return;

	if (val)
	{
		*m_BFWrite.pOutByte |= BITTABLE[m_BFWrite.nCurOutputBit];
	}
	else
	{
		*m_BFWrite.pOutByte &= INVBITTABLE[m_BFWrite.nCurOutputBit * 4];
	}

	m_BFWrite.nCurOutputBit++;
}

void CSizeBuf::WriteBits(uint32_t data, uint32_t numbits)
{
	ensureBitsWriting();
	if (numbits < 32)
	{
		if (data >= (uint32_t)(1 << numbits))
			data = ROWBITTABLE[numbits];
	}

	int surplusBytes = 0;
	if ((uint32_t)m_BFWrite.nCurOutputBit >= 8)
	{
		surplusBytes = 1;
		m_BFWrite.nCurOutputBit = 0;
		m_BFWrite.pOutByte++;
	}

	int bits = numbits + m_BFWrite.nCurOutputBit;
	if (bits <= 32)
	{
		int bytesToWrite = bits >> 3;
		int bitsLeft = bits & 7;
		if (!bitsLeft)
		{
			bytesToWrite--;
		}

		GetSpace(surplusBytes + bytesToWrite);
		if (!m_bOverflowed)
		{
			*(uint32_t *)m_BFWrite.pOutByte = (data << m_BFWrite.nCurOutputBit) | *(uint32_t *)m_BFWrite.pOutByte & ROWBITTABLE[m_BFWrite.nCurOutputBit];
			m_BFWrite.nCurOutputBit = 8;

			if (bitsLeft)
			{
				m_BFWrite.nCurOutputBit = bitsLeft;
			}

			m_BFWrite.pOutByte = &m_BFWrite.pOutByte[bytesToWrite];
		}
	}
	else
	{
		GetSpace(surplusBytes + 4);
		if (!m_bOverflowed)
		{
			*(uint32_t *)m_BFWrite.pOutByte = (data << m_BFWrite.nCurOutputBit) | *(uint32_t *)m_BFWrite.pOutByte & ROWBITTABLE[m_BFWrite.nCurOutputBit];
			int leftBits = 32 - m_BFWrite.nCurOutputBit;
			m_BFWrite.nCurOutputBit = bits & 7;
			m_BFWrite.pOutByte += 4;
			*(uint32_t *)m_BFWrite.pOutByte = data >> leftBits;
		}
	}
}

void CSizeBuf::WriteSBits(int data, uint32_t numbits)
{
	ensureBitsWriting();

	int idata = data;
	if (numbits < 32)
	{
		int maxnum = (1 << (numbits - 1)) - 1;

		if (data > maxnum || (maxnum = -maxnum, data < maxnum))
		{
			idata = maxnum;
		}
	}

	int sigbits = idata < 0;

	WriteOneBit(sigbits);
	WriteBits(abs(idata), numbits - 1);
}

void CSizeBuf::WriteBitString(const char *p)
{
	ensureBitsWriting();

	const uint8_t *pch = reinterpret_cast<const uint8_t *>(p);
	while (*pch)
	{
		WriteBits(*pch, 8);
		pch++;
	}

	WriteBits(0, 8);
}

void CSizeBuf::WriteBitData(void *src, uint32_t length)
{
	ensureBitsWriting();
	uint8_t *p = (uint8_t *)src;

	for (uint32_t i = 0; i < length; i++, p++)
	{
		WriteBits(*p, 8);
	}
}

void CSizeBuf::WriteBitFloat(float data)
{
	WriteSBits(*((int *)&data), 32);
}

void CSizeBuf::WriteBitAngle(float fAngle, uint32_t numbits)
{
	if (numbits >= 32)
	{
		m_bOverflowed = true;
		return;
	}

	uint32_t shift = (1 << numbits);
	uint32_t mask = shift - 1;

	int d = (int)((fAngle / 360.0) * shift);
	d    &= mask;

	WriteBits(d, numbits);
}

void CSizeBuf::WriteBitCoord(float data)
{
	ensureBitsWriting();

	int signbit  = (data <= -COORD_RESOLUTION_LOWPRECISION);
	int intval   = abs((int32_t)data);
	int fractval = abs(((int32_t)data * COORD_DENOMINATOR_LOWPRECISION)) & (COORD_DENOMINATOR_LOWPRECISION - 1);

	// Send the bit flags that indicate whether we have an integer part and/or a fraction part
	WriteOneBit(intval);
	WriteOneBit(fractval);

	if (intval || fractval)
	{
		// Send the sign bit
		WriteOneBit(signbit);

		// Send the integer if we have one
		if (intval)
			WriteBits(intval, COORD_INTEGER_BITS_MP);

		// Send the fraction if we have one
		if (fractval)
			WriteBits(fractval, COORD_FRACTIONAL_BITS_MP_LOWPRECISION);
	}
}

void CSizeBuf::WriteBitVec3Coord(const float *fa)
{
	bool xflag = (fa[0] >= COORD_RESOLUTION_LOWPRECISION) || (fa[0] <= -COORD_RESOLUTION_LOWPRECISION);
	bool yflag = (fa[1] >= COORD_RESOLUTION_LOWPRECISION) || (fa[1] <= -COORD_RESOLUTION_LOWPRECISION);
	bool zflag = (fa[2] >= COORD_RESOLUTION_LOWPRECISION) || (fa[2] <= -COORD_RESOLUTION_LOWPRECISION);

	WriteOneBit(xflag);
	WriteOneBit(yflag);
	WriteOneBit(zflag);

	if (xflag)
		WriteBitCoord(fa[0]);

	if (yflag)
		WriteBitCoord(fa[1]);

	if (zflag)
		WriteBitCoord(fa[2]);
}

void CSizeBuf::StartBitReading()
{
	ensureNoBitsOp();
	m_BFRead.nCurInputBit = 0;
	m_BFRead.nBytesRead = 0;
	m_BFRead.nBitFieldReadStartByte = m_ReadCount;
	m_BFRead.pInByte = m_Data + m_ReadCount;
	m_BFRead.nMsgReadCount = m_ReadCount + 1;

	if (m_ReadCount + 1 > m_CurSize)
	{
		m_bBadRead = true;
	}

	m_bBitsReading = true;
}

void CSizeBuf::EndBitReading()
{
	ensureBitsReading();

	if (m_BFRead.nMsgReadCount > m_CurSize)
	{
		m_bBadRead = true;
	}

	m_ReadCount = m_BFRead.nMsgReadCount;
	m_BFRead.nBitFieldReadStartByte = 0;
	m_BFRead.nCurInputBit = 0;
	m_BFRead.nBytesRead = 0;
	m_BFRead.pInByte = 0;

	m_bBitsReading = false;
}

int CSizeBuf::CurrentBit()
{
	ensureBitsReading();
	return m_BFRead.nCurInputBit + 8 * m_BFRead.nBytesRead;
}

int CSizeBuf::ReadOneBit()
{
	int nValue;
	if (m_bBadRead)
	{
		return 1;
	}

	if (m_BFRead.nCurInputBit >= 8)
	{
		m_BFRead.nMsgReadCount++;
		m_BFRead.nBytesRead++;
		m_BFRead.pInByte++;

		m_BFRead.nCurInputBit = 0;
	}

	if (m_BFRead.nMsgReadCount <= m_CurSize)
	{
		nValue = (*m_BFRead.pInByte & BITTABLE[m_BFRead.nCurInputBit]) != 0;
		m_BFRead.nCurInputBit++;
	}
	else
	{
		nValue = 1;
		m_bBadRead = true;
	}

	return nValue;
}

uint32_t CSizeBuf::PeekBits(int numbits)
{
	bf_read_t savebf = m_BFRead;
	uint32_t r = ReadBits(numbits);
	m_BFRead = savebf;
	return r;
}

uint32_t CSizeBuf::ReadBits(uint32_t numbits)
{
	if (numbits > 32)
		Error("%s: invalid numbits %d\n", __FUNCTION__, numbits);

	uint32_t result;
	if (m_bBadRead)
		return 1;

	if (m_BFRead.nCurInputBit >= 8)
	{
		m_BFRead.nMsgReadCount++;
		m_BFRead.nBytesRead++;
		m_BFRead.pInByte++;

		m_BFRead.nCurInputBit = 0;
	}

	uint32_t bits = (m_BFRead.nCurInputBit + numbits) & 7;
	if ((uint32_t)(m_BFRead.nCurInputBit + numbits) <= 32)
	{
		result = (*(uint32_t *)m_BFRead.pInByte >> m_BFRead.nCurInputBit) & ROWBITTABLE[numbits];

		uint32_t bytes = (m_BFRead.nCurInputBit + numbits) >> 3;
		if (bits)
		{
			m_BFRead.nCurInputBit = bits;
		}
		else
		{
			m_BFRead.nCurInputBit = 8;
			bytes--;
		}

		m_BFRead.pInByte       += bytes;
		m_BFRead.nMsgReadCount += bytes;
		m_BFRead.nBytesRead    += bytes;
	}
	else
	{
		result = ((*(uint32_t *)(m_BFRead.pInByte + 4) & ROWBITTABLE[bits]) << (32 - m_BFRead.nCurInputBit)) | (*(uint32_t *)m_BFRead.pInByte >> m_BFRead.nCurInputBit);
		m_BFRead.nCurInputBit   = bits;
		m_BFRead.pInByte       += 4;
		m_BFRead.nMsgReadCount += 4;
		m_BFRead.nBytesRead    += 4;
	}

	if (m_BFRead.nMsgReadCount > m_CurSize)
	{
		result = 1;
		m_bBadRead = true;
	}

	return result;
}

int CSizeBuf::ReadSBits(uint32_t numbits)
{
	int nSignBit = ReadOneBit();
	int result = ReadBits(numbits - 1);

	if (nSignBit)
	{
		result = -result;
	}

	return result;
}

const char *CSizeBuf::ReadBitString()
{
	static char buf[8192];

	char *p = &buf[0];
	for (char c = ReadBits(8); c; c = ReadBits(8))
	{
		// Prevent infinite cycle if m_bBadRead
		if (m_bBadRead)
			break;

		*p++ = c;
	}

	*p = '\0';
	return buf;
}

int CSizeBuf::ReadBitData(void *dest, int length)
{
	if (length > 0)
	{
		int i = length;
		uint8_t *p = (uint8_t *)dest;

		do
		{
			*p = (uint8_t)ReadBits(8);
			p++;
			i--;
		}
		while (i);
	}

	return length;
}

float CSizeBuf::ReadBitFloat()
{
	union { int u; float f; } c = { ReadSBits(32) };
	return c.f;
}

float CSizeBuf::ReadBitAngle(uint32_t numbits)
{
	return (float)(ReadBits(numbits) * (360.0 / (1 << numbits)));
}

float CSizeBuf::ReadBitCoord()
{
	auto value    = 0.0f;
	auto intval   = ReadOneBit();
	auto fractval = ReadOneBit();

	if (intval || fractval)
	{
		auto signbit = ReadOneBit();
		if (intval)
		{
			intval = ReadBits(12);
		}

		if (fractval)
		{
			fractval = ReadBits(3);
		}

		value = (float)(fractval / 8.0 + intval);

		if (signbit)
		{
			value = -value;
		}
	}

	return value;
}

void CSizeBuf::ReadBitVec3Coord(float *fa)
{
	int xflag = ReadOneBit();
	int yflag = ReadOneBit();
	int zflag = ReadOneBit();

	if (xflag)
		fa[0] = ReadBitCoord();

	if (yflag)
		fa[1] = ReadBitCoord();

	if (zflag)
		fa[2] = ReadBitCoord();
}

bool CSizeBuf::Resize(int size)
{
	Free();

	m_Data = (uint8_t *)malloc(size);
	memset(m_Data, 0, size);

	if (!m_Data)
	{
		return false;
	}

	m_MaxSize = size;
	m_bDoFree = true;
	return true;
}

void CSizeBuf::Free()
{
	if (m_Data && m_bDoFree)
	{
		free(m_Data);

		m_Data = nullptr;
		m_bDoFree = false;
	}

	m_MaxSize = m_CurSize = m_ReadCount = 0;
	m_bOverflowed = m_bBadRead = false;
	m_bBitsWriting = m_bBitsReading = false;

	memset(&m_BFRead, 0, sizeof(m_BFRead));
	memset(&m_BFWrite, 0, sizeof(m_BFWrite));
}

void CSizeBuf::Clear()
{
	memset(m_Data, 0, m_MaxSize);

	m_CurSize = m_ReadCount = 0;
	m_bOverflowed = m_bBadRead = false;
	m_bBitsWriting = m_bBitsReading = false;
}

void CSizeBuf::FastClear()
{
	memset(m_Data, 0, min(m_MaxSize, m_CurSize + 4));

	m_CurSize = m_ReadCount = 0;
	m_bOverflowed = m_bBadRead = false;
	m_bBitsWriting = m_bBitsReading = false;
}

void CSizeBuf::Reset()
{
	m_nFlags = 0;
	m_ReadCount = 0;
	m_BFRead.nCurInputBit = 0;
	m_BFRead.nBytesRead = 0;
	m_bOverflowed = false;
}

uint32_t CSizeBuf::ReadDWord()
{
	return ReadPrimitive<uint32_t>();
}

int32_t CSizeBuf::ReadLong()
{
	return ReadPrimitive<int32_t>();
}

float CSizeBuf::ReadFloat()
{
	//union {
	//	float f;
	//	int i;
	//} dat;

	//dat.i = LittleFloat(ReadLong());
	//return dat.f;

	return LittleFloat(ReadPrimitive<float>());
}

float CSizeBuf::ReadAngle()
{
	int c = ReadChar();
	if (c == -1)
	{
		// FIXED: Added check for wrong value, but just return 0 instead of -1 * (360.0 / 65536)
		return 0;
	}

	return (float)(c * (360.0 / 256));
}

float CSizeBuf::ReadHiresAngle()
{
	int c = ReadShort();
	if (c == -1)
	{
		// FIXED: Added check for wrong value, but just return 0 instead of -1 * (360.0 / 65536)
		return 0;
	}

	return (float)(ReadShort() * (360.0 / 65536));
}

int8_t CSizeBuf::ReadChar()
{
	return ReadPrimitive<int8_t>();
}

uint8_t CSizeBuf::ReadByte()
{
	return ReadPrimitive<uint8_t>();
}

int16_t CSizeBuf::ReadShort()
{
	return ReadPrimitive<int16_t>();
}

uint16_t CSizeBuf::ReadWord()
{
	return ReadPrimitive<uint16_t>();
}

char *CSizeBuf::ReadString()
{
	int c = 0, l = 0;
	static char string[8192] = "";

	while ((c = ReadChar(), c) && c != -1 && l < ARRAYSIZE(string) - 1)
	{
		string[l++] = c;
	}

	string[l] = '\0';
	return string;
}

bool CSizeBuf::ReadString(char *dest, uint32_t length)
{
	const auto pszStringBuf = ReadString();
	auto len = min(length, strlen(pszStringBuf) + 1);
	strncpy(dest, pszStringBuf, len);
	dest[len] = '\0';

	return true;
}

char *CSizeBuf::ReadStringLine()
{
	int c = 0, l = 0;
	static char string[8192] = "";

	while ((c = ReadChar(), c) && c != '\n' && c != -1 && l < ARRAYSIZE(string) - 1)
	{
		string[l++] = c;
	}

	string[l] = '\0';
	return string;
}

bool CSizeBuf::ReadBuf(void *dest, uint32_t length, uint32_t startPos)
{
	if (!dest)
	{
		return false;
	}

	if ((m_ReadCount + length + startPos) > m_CurSize)
	{
		return false;
	}

	memcpy(dest, &m_Data[m_ReadCount + startPos], length);
	m_ReadCount += length + startPos;
	return true;
}

int64_t CSizeBuf::ReadI64()
{
	return ReadPrimitive<int64_t>();
}

uint64_t CSizeBuf::ReadU64()
{
	return ReadPrimitive<uint64_t>();
}

void CSizeBuf::ReadVec3Coord(float *fa)
{
	if (m_bBitsReading)
	{
		ReadBitVec3Coord(fa);
	}
	else
	{
		StartBitReading();
		ReadBitVec3Coord(fa);
		EndBitReading();
	}
}

void CSizeBuf::Cut(uint32_t cutpos, uint32_t cutlen)
{
	if (cutpos + cutlen > m_CurSize)
	{
		Error("%s: Invalid cut request; cutpos=%u, cutlen=%u, curSize=%u", __FUNC__, cutpos, cutlen, m_CurSize);
		return;
	}

	uint8_t *wpos = m_Data + cutpos;
	uint8_t *rpos = m_Data + cutpos + cutlen;
	uint32_t moveLen = m_CurSize - (cutpos + cutlen);
	if (moveLen)
	{
		memmove(wpos, rpos, moveLen);
	}

	m_CurSize -= cutlen;
}

void CSizeBuf::SetBuffer(const void *buf, uint32_t maxSize, uint32_t unFlags)
{
	Free();

	m_Data         = (uint8_t *)buf;
	m_nFlags       = unFlags;
	m_MaxSize      = maxSize;
	m_ReadCount    = 0;
	m_bOverflowed  = m_bBadRead = false;
	m_bBitsWriting = m_bBitsReading = false;
	m_bDoFree      = false;

	if (IsReadOnly())
	{
		m_CurSize = maxSize;
	}
}

int CSizeBuf::SkipString()
{
	int c = 0, l = 1;
	const int maxString = 8192;

	while ((c = ReadChar(), c) && c != -1 && l < maxString)
	{
		l++;
	}

	return l;
}

void CSizeBuf::SkipBits(int numbits)
{
	if (m_bBadRead)
	{
		return;
	}

	if (m_BFRead.nCurInputBit >= 8)
	{
		m_BFRead.nMsgReadCount++;
		m_BFRead.nBytesRead++;
		m_BFRead.pInByte++;

		m_BFRead.nCurInputBit = 0;
	}

	uint32_t bits = (m_BFRead.nCurInputBit + numbits) & 7;
	if ((uint32_t)(m_BFRead.nCurInputBit + numbits) <= 32)
	{
		uint32_t bytes = (m_BFRead.nCurInputBit + numbits) >> 3;
		if (bits)
		{
			m_BFRead.nCurInputBit = bits;
		}
		else
		{
			m_BFRead.nCurInputBit = 8;
			bytes--;
		}

		m_BFRead.pInByte       += bytes;
		m_BFRead.nMsgReadCount += bytes;
		m_BFRead.nBytesRead    += bytes;
	}
	else
	{
		m_BFRead.nCurInputBit   = bits;
		m_BFRead.pInByte       += 4;
		m_BFRead.nMsgReadCount += 4;
		m_BFRead.nBytesRead    += 4;
	}

	if (m_BFRead.nMsgReadCount > m_CurSize)
	{
		m_bBadRead = true;
	}
}

void CSizeBuf::SkipBytes(int nbytes)
{
	if (IsReadOnly())
	{
		if ((m_ReadCount + nbytes) > m_MaxSize)
		{
			m_bOverflowed = true;
		}

		m_ReadCount += nbytes;
	}
	else
	{
		if ((m_CurSize + nbytes) > m_MaxSize)
		{
			m_bOverflowed = true;
		}

		m_CurSize += nbytes;
	}
}

void CSizeBuf::ConcatBuffer(CSizeBuf *buffer)
{
	WriteBuf(buffer->GetData(), buffer->GetCurSize());
}
