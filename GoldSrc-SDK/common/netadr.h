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

#include "tier0/platform.h"

#ifdef _WIN32
#undef SetPort	// get around stupid WINSPOOL.H macro
#endif

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#else
#include <netinet/in.h> // ntohs()
#include <netdb.h>		// getaddrinfo()
#include <sys/socket.h>	// getsockname()
#endif

typedef enum
{
	NA_NULL = 0,
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
	NA_IPX,				// Deprecated: GoldSrc
	NA_BROADCAST_IPX,	// Deprecated: GoldSrc
} netadrtype_t;

#define NETADR_DEFINED

class netadr_t;

// DEPRECATED: but legacy goldsrc way, using only goldsrc things
typedef struct netadr0_s
{
public:
	inline netadr0_s() { SetIP(0); SetPort(0); SetType(NA_IP); }
	inline netadr0_s(uint32_t unIP, uint16_t usPort) { SetIP(htonl(unIP)); SetPort(ntohs(usPort)); SetType(NA_IP); }
	inline netadr0_s(const struct netadr0_s &other) { SetIP(other.GetIP()); SetPort(other.GetPort()); SetType(other.GetType()); }
	explicit netadr0_s(const char *pch) { SetFromString(pch); }

	const char *ToString(bool onlyBase = false) const;
	void ToStringBuf(char *pchBuffer, uint32_t unBufferSize, bool onlyBase = false) const;
	void ToSockadr(struct sockaddr *s) const;
	void ToSockadr2(struct sockaddr *s) const;

	bool CompareAdr(const struct netadr0_s &a, bool onlyBase = false) const;
	bool CompareClassBAdr(const struct netadr0_s &a) const;
	bool IsReservedAdr() const;
	bool IsLoopback() const;
	void Clear();	// invalids Address
	void SetIP(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
	void SetIP(uint32_t unIP);
	void SetIP(unsigned char (&ucIP)[4]);
	void Set(const struct netadr0_s &src);
	void Set(const netadr_t &src);

	bool SetFromString(const char *psz); // returns false if you pass it a name that needs DNS resolution
	bool SetFromSockadr(const struct sockaddr *s);

	void SetType(netadrtype_t newtype);
	netadrtype_t GetType() const;
	unsigned short GetPort() const;
	uint32_t GetIP() const;
	const uint8_t *GetIPX() const;
	bool IsValid() const;
	void SetPort(unsigned short newport);
	bool operator<(const struct netadr0_s &netadr) const;

	bool operator==(const struct netadr0_s &other) const
	{
		return CompareAdr(other, true);
	}

	template <size_t maxLenInChars>
	char *ToString_safe(char (&pDest)[maxLenInChars], bool onlyBase = false) const
	{
		ToStringBuf(&pDest[0], maxLenInChars, onlyBase);
		return pDest;
	}

private:
	netadrtype_t	type;
	unsigned char	ip[4];
	unsigned char	ipx[10];	// deprecated
	unsigned short	port;
} netadr0_t;

inline void netadr0_t::ToStringBuf(char *pchBuffer, uint32_t unBufferSize, bool onlyBase) const
{
	strncpy(pchBuffer, "unknown", unBufferSize);

	if (type == NA_LOOPBACK)
	{
		strncpy(pchBuffer, "loopback", unBufferSize);
	}
	else if (type == NA_BROADCAST)
	{
		strncpy(pchBuffer, "broadcast", unBufferSize);
	}
	else if (type == NA_IP)
	{
		if (onlyBase)
		{
			_snprintf(pchBuffer, unBufferSize, "%i.%i.%i.%i", ip[0], ip[1], ip[2], ip[3]);
		}
		else
		{
			_snprintf(pchBuffer, unBufferSize, "%i.%i.%i.%i:%i", ip[0], ip[1], ip[2], ip[3], htons(port));
		}
	}
}

inline void netadr0_t::ToSockadr(struct sockaddr *s) const
{
	memset(s, 0, sizeof(*s));

	auto s_in = (sockaddr_in *)s;

	switch (type)
	{
	case NA_BROADCAST:
		s_in->sin_family = AF_INET;
		s_in->sin_addr.s_addr = INADDR_BROADCAST;
		s_in->sin_port = GetPort();
		break;
	case NA_IP:
		s_in->sin_family = AF_INET;
		s_in->sin_addr.s_addr = GetIP();
		s_in->sin_port = GetPort();
		break;
	case NA_LOOPBACK:
		s_in->sin_family = AF_INET;
		s_in->sin_addr.s_addr = GetIP();
		s_in->sin_port = GetPort();
		break;
	default:
		break;
	}
}

inline const char *netadr0_t::ToString(bool onlyBase) const
{
	static int current = 0;
	static char pchBuffer[16][64];
	current = (current + 1) % 16;

	strncpy(pchBuffer[current], "unknown", sizeof(pchBuffer[current]));

	if (type == NA_LOOPBACK)
	{
		strncpy(pchBuffer[current], "loopback", sizeof(pchBuffer[current]));
	}
	else if (type == NA_BROADCAST)
	{
		strncpy(pchBuffer[current], "broadcast", sizeof(pchBuffer[current]));
	}
	else if (type == NA_IP)
	{
		if (onlyBase)
		{
#ifdef VALVE_BIG_ENDIAN
			_snprintf(pchBuffer[current], sizeof(pchBuffer[current]), "%i.%i.%i.%i", ip[3], ip[2], ip[1], ip[0]);
#else
			_snprintf(pchBuffer[current], sizeof(pchBuffer[current]), "%i.%i.%i.%i", ip[0], ip[1], ip[2], ip[3]);
#endif
		}
		else
		{
#ifdef VALVE_BIG_ENDIAN
			_snprintf(pchBuffer[current], sizeof(pchBuffer[current]), "%i.%i.%i.%i:%i", ip[3], ip[2], ip[1], ip[0], htons(port));
#else
			_snprintf(pchBuffer[current], sizeof(pchBuffer[current]), "%i.%i.%i.%i:%i", ip[0], ip[1], ip[2], ip[3], htons(port));
#endif
		}
	}

	return pchBuffer[current];
}

inline bool netadr0_t::CompareAdr(const netadr0_t &a, bool onlyBase) const
{
	if (type != a.type)
		return false;

	if (type == NA_LOOPBACK)
		return true;

	if (type == NA_BROADCAST)
		return true;

	if (type == NA_IP)
	{
		if (ip[0] == a.ip[0] &&
			ip[1] == a.ip[1] &&
			ip[2] == a.ip[2] &&
			ip[3] == a.ip[3] &&
			(onlyBase || port == a.port))
			return true;
	}
#ifdef _WIN32
	else if (type == NA_IPX)
	{
		if (memcmp(ipx, a.ipx, sizeof(ipx)) == 0 &&
			(onlyBase || port == a.port))
			return true;
	}
#endif // _WIN32

	return false;
}

inline bool netadr0_t::CompareClassBAdr(const netadr0_t &a) const
{
	if (type != a.type)
		return false;

	if (type == NA_LOOPBACK)
		return true;

	if (type == NA_BROADCAST)
		return true;

	if (type == NA_IP)
	{
#ifdef VALVE_BIG_ENDIAN
		if (ip[0] == a.ip[0] && ip[1] == a.ip[1])
#else
		if (ip[3] == a.ip[3] && ip[2] == a.ip[2])
#endif
			return true;
	}

	return false;
}

// Is the IP part of one of the reserved blocks?
inline bool netadr0_t::IsReservedAdr() const
{
	if (type == NA_LOOPBACK)
		return true;

	// IP is stored little endian; for an IP of w.x.y.z, ip[3] will be w, ip[2] will be x, etc
	if (type == NA_IP)
	{
#ifdef VALVE_BIG_ENDIAN
		if ((ip[0] == 10) ||									// 10.x.x.x is reserved
			(ip[0] == 127) ||									// 127.x.x.x
			(ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31) ||		// 172.16.x.x  - 172.31.x.x
			(ip[0] == 192 && ip[1] >= 168)) 					// 192.168.x.x
			return true;
#else
		if ((ip[3] == 10) ||									// 10.x.x.x is reserved
			(ip[3] == 127) ||									// 127.x.x.x
			(ip[3] == 172 && ip[2] >= 16 && ip[2] <= 31) ||		// 172.16.x.x  - 172.31.x.x
			(ip[3] == 192 && ip[2] >= 168)) 					// 192.168.x.x
			return true;
#endif
	}

	return false;
}

inline bool netadr0_t::IsLoopback() const
{
	return type == NA_LOOPBACK
#ifdef VALVE_BIG_ENDIAN
		|| (type == NA_IP && ip[0] == 127);
#else
		|| (type == NA_IP && ip[3] == 127);
#endif
}

inline void netadr0_t::Clear()
{
	port = 0;
	type = NA_NULL;

	memset(ip, 0, sizeof(ip));
	memset(ipx, 0, sizeof(ipx));
}

inline void netadr0_t::SetIP(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
	*(uint32_t *)ip = (b4 << 24) + (b3 << 16) + (b2 << 8) + (b1);
}

inline void netadr0_t::SetIP(uint32_t unIP)
{
	*(uint32_t *)ip = unIP;
}

inline void netadr0_t::SetIP(unsigned char (&ucIP)[4])
{
	ip[0] = ucIP[0];
	ip[1] = ucIP[1];
	ip[2] = ucIP[2];
	ip[3] = ucIP[3];
}

inline void netadr0_t::Set(const netadr0_t &src)
{
	SetIP(src.GetIP());
	SetPort(src.GetPort());
	SetType(src.GetType());
}

inline void netadr0_t::SetType(netadrtype_t newtype)
{
	type = newtype;
}

inline netadrtype_t netadr0_t::GetType() const
{
	return type;
}

inline unsigned short netadr0_t::GetPort() const
{
	return port;
}

inline uint32_t netadr0_t::GetIP() const
{
	return *(uint32_t *)ip;
}

// TODO: Absoleted! Remove this
inline const uint8_t *netadr0_t::GetIPX() const
{
	return ipx;
}

inline bool netadr0_t::IsValid() const
{
	if (port == 0)
		return false;

	if (type == NA_NULL)
		return false;

	if (ip[0] == 0 &&
		ip[1] == 0 &&
		ip[2] == 0 &&
		ip[3] == 0)
		return false;

	return true;
}

inline void netadr0_t::SetPort(unsigned short newport)
{
	port = newport;
}

inline bool netadr0_t::operator<(const netadr0_t &netadr) const
{
	return (*(uint32_t *)ip < *(uint32_t *)netadr.ip) ||
		(*(uint32_t *)ip == *(uint32_t *)netadr.ip && port < netadr.port);
}

class netadr_t
{
public:
	inline netadr_t() { _padding = 0; SetIP(0); SetPort(0); SetType(NA_IP); }
	inline netadr_t(uint32_t unIP, uint16_t usPort) { _padding = 0; SetIP(unIP); SetPort(usPort); SetType(NA_IP); }
	inline netadr_t(const netadr0_t &other) { _padding = 0; SetIP(htonl(other.GetIP())); SetPort(ntohs(other.GetPort())); SetType(other.GetType()); }
	explicit netadr_t(const char *pch) { _padding = 0; SetFromString(pch); }
	void Clear();	// invalids Address

	void Set(const netadr_t &src);
	void Set(const netadr0_t &src);
	void SetType(netadrtype_t type);
	void SetPort(unsigned short port);
	bool SetFromSockadr(const struct sockaddr *s);
	void SetIP(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
	void SetIP(uint32_t unIP);									// Sets IP. unIP is in host order (little-endian)
	void SetIPAndPort(uint32_t unIP, unsigned short usPort) { SetIP(unIP); SetPort(usPort); }
	bool SetFromString(const char *psz); // returns false if you pass it a name that needs DNS resolution
	bool BlockingResolveAndSetFromString(const char *psz); // DNS calls may block, inadvisable from the main thread
	bool CompareAdr(const netadr_t &a, bool onlyBase = false) const;
	bool CompareClassBAdr(const netadr_t &a) const;

	netadrtype_t GetType() const;
	uint32_t GetIP() const;
	unsigned short GetPort() const;
	const char *ToString(bool onlyBase = false) const; // returns xxx.xxx.xxx.xxx:ppppp
	void ToStringBuf(char *pchBuffer, uint32_t unBufferSize, bool onlyBase = false) const;
	void ToSockadr(struct sockaddr *s) const;

	template <size_t maxLenInChars>
	char *ToString_safe(char (&pDest)[maxLenInChars], bool onlyBase = false) const
	{
		ToStringBuf(&pDest[0], maxLenInChars, onlyBase);
		return pDest;
	}

	bool IsLoopback() const;
	bool IsReservedAdr() const;
	bool IsValid() const;	// ip & port != 0
	void SetFromSocket(int hSocket);

	// Copy deprecated struct
	netadr_t &operator=(const netadr0_t &other)
	{
		SetIP(htonl(other.GetIP()));
		SetPort(ntohs(other.GetPort()));
		SetType(other.GetType());

		return (*this);
	}

	bool operator==(const netadr_t &netadr) const {return (CompareAdr(netadr));}
	bool operator!=(const netadr_t &netadr) const {return !(CompareAdr(netadr));}
	bool operator<(const netadr_t &netadr) const;
	static bool less(const netadr_t &lhs, const netadr_t &rhs);
	static unsigned int GetHashKey(const netadr_t &netadr);

private:
	netadrtype_t type;

	union {
		uint32_t ip;			// IP stored in host order (little-endian)
		byte ipByte[4];			// IP stored in host order (little-endian)
	};

	unsigned short port;		// port stored in host order (little-endian)
	unsigned short _padding;
};

class netmask_t
{
public:
	netmask_t() { SetBaseIP(0); SetMask(0); }
	netmask_t(uint32_t unBaseIP, uint32_t unMask) { SetBaseIP(unBaseIP); SetMask(unMask); }
	netmask_t(const char *pchCIDR) { SetFromString(pchCIDR); }
	netmask_t(const char *pchBaseIP, const char *pchMask) { SetFromString(pchBaseIP, pchMask); }

	void Clear();
	void SetBaseIP(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
	void SetBaseIP(uint32_t unIP);							// Sets base IP. unIP is in host order (little-endian)
	void SetMask(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
	void SetMask(uint32_t unMask);
	bool SetFromString(const char *pchCIDR);
	bool SetFromString(const char *pchBaseIP, const char *pchMask);

	bool AdrInRange(uint32_t unIP) const;

	uint32_t GetBaseIP() const;
	uint32_t GetMask() const;
	uint32_t GetLastIP() const;
	const char *ToCIDRString(char *pchBuffer, uint32_t unBufferSize) const; // returns xxx.xxx.xxx.xxx/xx

private:
	union {
		uint32_t	m_BaseIP;			// IP stored in host order (little-endian)
		byte		m_BaseIPByte[4];	// IP stored in host order (little-endian)
	};

	union {
		uint32_t	m_Mask;				// IP stored in host order (little-endian)
		byte		m_MaskByte[4];		// IP stored in host order (little-endian)
	};
};

class CUtlNetAdrRender
{
public:
	CUtlNetAdrRender(const netadr_t &obj, bool bBaseOnly = false)
	{
		obj.ToStringBuf(m_rgchString, sizeof(m_rgchString), bBaseOnly);
	}

	CUtlNetAdrRender(uint32_t unIP)
	{
		netadr_t addr(unIP, 0);
		addr.ToStringBuf(m_rgchString, sizeof(m_rgchString), true);
	}

	CUtlNetAdrRender(uint32_t unIP, uint16_t nPort)
	{
		netadr_t addr(unIP, nPort);
		addr.ToStringBuf(m_rgchString, sizeof(m_rgchString), false);
	}

	const char *String()
	{
		return m_rgchString;
	}

private:
	char m_rgchString[64];
};

class CUtlNetMaskCIDRRender
{
public:
	CUtlNetMaskCIDRRender(const netmask_t &obj)
	{
		obj.ToCIDRString(m_rgchString, sizeof(m_rgchString));
	}

	const char *String()
	{
		return m_rgchString;
	}

private:
	char m_rgchString[64];
};

inline bool netadr_t::CompareAdr(const netadr_t &a, bool onlyBase) const
{
	if (a.type != type)
		return false;

	if (type == NA_LOOPBACK)
		return true;

	if (type == NA_BROADCAST)
		return true;

	if (type == NA_IP)
	{
		if (!onlyBase && (port != a.port))
			return false;

		if (a.ip == ip)
			return true;
	}

	return false;
}

inline void netadr0_t::Set(const netadr_t &src)
{
	SetIP(src.GetIP());
	SetPort(src.GetPort());
	SetType(src.GetType());
}

inline bool netadr_t::CompareClassBAdr(const netadr_t &a) const
{
	if (a.type != type)
		return false;

	if (type == NA_LOOPBACK)
		return true;

	if (type == NA_IP)
	{
#ifdef VALVE_BIG_ENDIAN
		if (a.ipByte[0] == ipByte[0] && a.ipByte[1] == ipByte[1])
#else
		if (a.ipByte[3] == ipByte[3] && a.ipByte[2] == ipByte[2])
#endif
			return true;
	}

	return false;
}

inline bool IsPrivateIP(uint32_t unIP)
{
	// RFC 1918
	if ((unIP & 0xff000000) == 0x0a000000) // 10.0.0.0/8
		return true;

	if ((unIP & 0xfff00000) == 0xac100000) // 172.16.0.0/12
		return true;

	if ((unIP & 0xffff0000) == 0xc0a80000) // 192.168.0.0/16
		return true;

	return false;
}

// Is the IP part of one of the reserved blocks?
inline bool netadr_t::IsReservedAdr() const
{
	if (type == NA_LOOPBACK)
		return true;

	// IP is stored little endian; for an IP of w.x.y.z, ipByte[3] will be w, ipByte[2] will be x, etc
	if (type == NA_IP)
	{
#ifdef VALVE_BIG_ENDIAN
		if ((ipByte[0] == 10) ||											// 10.x.x.x is reserved
			(ipByte[0] == 127) ||											// 127.x.x.x
			(ipByte[0] == 172 && ipByte[1] >= 16 && ipByte[1] <= 31) ||		// 172.16.x.x  - 172.31.x.x
			(ipByte[0] == 192 && ipByte[1] >= 168)) 						// 192.168.x.x
			return true;
#else
		if ((ipByte[3] == 10) ||											// 10.x.x.x is reserved
			(ipByte[3] == 127) ||											// 127.x.x.x
			(ipByte[3] == 172 && ipByte[2] >= 16 && ipByte[2] <= 31) ||		// 172.16.x.x  - 172.31.x.x
			(ipByte[3] == 192 && ipByte[2] >= 168)) 						// 192.168.x.x
			return true;
#endif
	}

	return false;
}

inline bool netadr_t::IsLoopback() const
{
	return type == NA_LOOPBACK
#ifdef VALVE_BIG_ENDIAN
		|| (type == NA_IP && ipByte[0] == 127);
#else
		|| (type == NA_IP && ipByte[3] == 127);
#endif
}

inline void netadr_t::Clear()
{
	ip = 0;
	port = 0;
	type = NA_NULL;
}

inline void netadr_t::SetIP(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
	ip = (b4) + (b3 << 8) + (b2 << 16) + (b1 << 24);
}

inline void netadr_t::SetIP(uint32_t unIP)
{
	ip = unIP;
}

inline void netadr_t::Set(const netadr0_t &src)
{
	SetIP(htonl(src.GetIP()));
	SetPort(ntohs(src.GetPort()));
	SetType(src.GetType());
}

inline void netadr_t::Set(const netadr_t &src)
{
	SetIP(src.GetIP());
	SetPort(src.GetPort());
	SetType(src.GetType());
}

inline void netadr_t::SetType(netadrtype_t newtype)
{
	type = newtype;
}

inline netadrtype_t netadr_t::GetType() const
{
	return type;
}

inline unsigned short netadr_t::GetPort() const
{
	return port;
}

inline uint32_t netadr_t::GetIP() const
{
	return ip;
}

inline bool netadr_t::IsValid() const
{
	return ((port != 0) && (type != NA_NULL) &&
		(ip != 0));
}

inline void netadr_t::SetPort(unsigned short newport)
{
	port = newport;
}

inline bool netadr_t::operator<(const netadr_t &netadr) const
{
	return (ip < netadr.ip) || (ip == netadr.ip && port < netadr.port);
}

inline void netmask_t::Clear()
{
	m_BaseIP = 0;
	m_Mask = 0;
}

inline void netmask_t::SetBaseIP(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
	m_BaseIP = (b4) + (b3 << 8) + (b2 << 16) + (b1 << 24);
}

inline void netmask_t::SetBaseIP(uint32_t unIP)
{
	m_BaseIP = unIP;
}

inline void netmask_t::SetMask(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
	m_Mask = (b4) + (b3 << 8) + (b2 << 16) + (b1 << 24);
}

inline void netmask_t::SetMask(uint32_t unMask)
{
	m_Mask = unMask;
}

inline bool netmask_t::AdrInRange(uint32_t unIP) const
{
	return ((unIP & m_Mask) == m_BaseIP);
}

inline uint32_t netmask_t::GetBaseIP() const
{
	return m_BaseIP;
}

inline uint32_t netmask_t::GetMask() const
{
	return m_Mask;
}

inline uint32_t netmask_t::GetLastIP() const
{
	return m_BaseIP + ~m_Mask;
}

inline bool netadr_t::less(const netadr_t &lhs, const netadr_t &rhs)
{
	return (lhs.ip < rhs.ip) || (lhs.ip == rhs.ip && lhs.port < rhs.port);
}

inline unsigned int netadr_t::GetHashKey(const netadr_t &netadr)
{
	return (netadr.ip ^ netadr.port);
}
