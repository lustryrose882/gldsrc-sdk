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

#include "netadr.h"
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

const char *netadr_t::ToString(bool onlyBase) const
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
			_snprintf(pchBuffer[current], sizeof(pchBuffer[current]), "%i.%i.%i.%i", ipByte[0], ipByte[1], ipByte[2], ipByte[3]);
#else
			_snprintf(pchBuffer[current], sizeof(pchBuffer[current]), "%i.%i.%i.%i", ipByte[3], ipByte[2], ipByte[1], ipByte[0]);
#endif
		}
		else
		{
#ifdef VALVE_BIG_ENDIAN
			_snprintf(pchBuffer[current], sizeof(pchBuffer[current]), "%i.%i.%i.%i:%i", ipByte[0], ipByte[1], ipByte[2], ipByte[3], port);
#else
			_snprintf(pchBuffer[current], sizeof(pchBuffer[current]), "%i.%i.%i.%i:%i", ipByte[3], ipByte[2], ipByte[1], ipByte[0], port);
#endif
		}
	}

	return pchBuffer[current];
}

void netadr_t::ToStringBuf(char *pchBuffer, uint32_t unBufferSize, bool onlyBase) const
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
			_snprintf(pchBuffer, unBufferSize, "%i.%i.%i.%i", ipByte[0], ipByte[1], ipByte[2], ipByte[3]);
		}
		else
		{
			_snprintf(pchBuffer, unBufferSize, "%i.%i.%i.%i:%i", ipByte[0], ipByte[1], ipByte[2], ipByte[3], port);
		}
	}
}

void netadr0_t::ToSockadr2(struct sockaddr *s) const
{
	memset(s, 0, sizeof(struct sockaddr));

	auto s_in = (sockaddr_in *)s;

	s_in->sin_family = AF_INET;
	s_in->sin_addr.s_addr = *(int *)&ip;
	s_in->sin_port = port;
}

void netadr_t::ToSockadr(struct sockaddr *s) const
{
	memset(s, 0, sizeof(struct sockaddr));

	// Note: we use htonl/s to convert IP & port from host (little-endian) to network (big-endian) order
	((struct sockaddr_in *)s)->sin_family = AF_INET;
	((struct sockaddr_in *)s)->sin_port = htons(port);

	if (type == NA_BROADCAST)
	{
		((struct sockaddr_in *)s)->sin_addr.s_addr = htonl(INADDR_BROADCAST);
	}
	else if (type == NA_IP)
	{
		((struct sockaddr_in *)s)->sin_addr.s_addr = htonl(ip);
	}
	else if (type == NA_LOOPBACK)
	{
		((struct sockaddr_in *)s)->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	}
}

bool netadr_t::SetFromSockadr(const struct sockaddr *s)
{
	if (s->sa_family == AF_INET)
	{
		type = NA_IP;
		// Note: we use ntohl/s to convert IP & port from network (big-endian) to host (little-endian) order
		ip = ntohl(((struct sockaddr_in *)s)->sin_addr.s_addr);
		port = ntohs(((struct sockaddr_in *)s)->sin_port);
		return true;
	}
	else
	{
		Clear();
		return false;
	}
}

bool netadr_t::SetFromString(const char *pch)
{
	ip = 0;
	port = 0;
	type = NA_IP;

	if (!pch || pch[0] == 0) // but let's not crash
		return false;

	if (pch[0] >= '0' && pch[0] <= '9' && strchr(pch, '.'))
	{
		int n1, n2, n3, n4, n5;
		int nRes = sscanf(pch, "%d.%d.%d.%d:%d", &n1, &n2, &n3, &n4, &n5);
		if (nRes >= 4)
		{
			SetIP(n1, n2, n3, n4);
		}

		if (nRes == 5)
		{
			SetPort((uint16_t)n5);
		}

		if (nRes >= 4)
			return true;
	}
	else
	{
		struct sockaddr sadr = {};

		struct sockaddr_in *p = (struct sockaddr_in *)&sadr;
		p->sin_family = AF_INET;
		p->sin_port = 0;

		char hostname[128];
		strncpy(hostname, pch, sizeof(hostname));

		// search port
		auto pchColon = strrchr(hostname, ':');
		if (pchColon)
		{
			*pchColon = '\0';
			*(short *)&p->sin_port = htons(atoi(pchColon + 1));
		}

		struct addrinfo *hostinfo = nullptr;	// will point to the results

		// DNS it
		int errcode = getaddrinfo(hostname, NULL, NULL, &hostinfo);
		if (errcode != 0 || !hostinfo)
		{
			// doesn't resolved
			return false;
		}

		// Use first result
		p->sin_addr = ((struct sockaddr_in *)hostinfo->ai_addr)->sin_addr;
		freeaddrinfo(hostinfo);

		return SetFromSockadr(&sadr);
	}

	return false;
}

void netadr_t::SetFromSocket(int hSocket)
{
	port = ip = 0;
	type = NA_IP;

	struct sockaddr address;
	socklen_t namelen = sizeof(address);
	if (getsockname(hSocket, &address, &namelen) == 0)
	{
		SetFromSockadr(&address);
	}
}

bool netmask_t::SetFromString(const char *pchCIDR)
{
	if (!pchCIDR)			// but let's not crash
		return false;

	uint32_t uFirstByte = 0;
	uint32_t uSecondByte = 0;
	uint32_t uThirdByte = 0;
	uint32_t uFourthByte = 0;
	uint32_t uNumNetworkBits;
	uint32_t uNumCharsConsumed = 0;

	char buf[32];

	// This is an MS extension (the regexp), it'll compile but not likely work under other platforms
	int NumMatches = sscanf(pchCIDR, "%16[^/]/%u%n", buf, &uNumNetworkBits, &uNumCharsConsumed);

	if (NumMatches != 2)
	{
		return false;
	}

	if (uNumNetworkBits > 32)
	{
		//AssertMsg(false, "Invalid CIDR mask size");
		return false;
	}

	// Guarantee null-termination.
	buf[ARRAYSIZE(buf) - 1] = '\0';

	if (sscanf(buf, "%d.%d.%d.%d", &uFirstByte, &uSecondByte, &uThirdByte, &uFourthByte) < (int)((uNumNetworkBits + 7) / 8))
	{
		return false;
	}

	SetBaseIP(uFirstByte, uSecondByte, uThirdByte, uFourthByte);
	uint32_t unMask = uNumNetworkBits ? (~0u << (32 - uNumNetworkBits)) : 0;
	SetMask(unMask);

	return true;
}

bool netmask_t::SetFromString(const char *pchBaseIP, const char *pchMask)
{
	if (!pchBaseIP)			// but let's not crash
		return false;

	if (!pchMask)			// but let's not crash
		return false;

	SetBaseIP(0, 0, 0, 0);
	SetMask(255, 255, 255, 255);
	int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
	if (sscanf(pchBaseIP, "%d.%d.%d.%d", &n1, &n2, &n3, &n4) < 4)
		return false;

	SetBaseIP(n1, n2, n3, n4);

	if (sscanf(pchMask, "%d.%d.%d.%d", &n1, &n2, &n3, &n4) < 4)
		return false;

	SetMask(n1, n2, n3, n4);
	return true;
}

// returns xxx.xxx.xxx.xxx/xx
const char *netmask_t::ToCIDRString(char *pchBuffer, uint32_t unBufferSize) const
{
	uint32_t uMask = ~m_Mask; // invert, so looks like 0000111
	uint32_t uNumNetworkBits = 0;
	while (uNumNetworkBits <= 32)
	{
		if (!uMask)
			break;

		uMask >>= 1;
		uNumNetworkBits++;
	}

	uNumNetworkBits = 32 - uNumNetworkBits;
	_snprintf(pchBuffer, unBufferSize, "%i.%i.%i.%i/%i", m_BaseIPByte[3], m_BaseIPByte[2], m_BaseIPByte[1], m_BaseIPByte[0], uNumNetworkBits);
	return pchBuffer;
}

bool netadr0_t::SetFromString(const char *pch)
{
	memset(ip, 0, sizeof(ip));
	memset(ipx, 0, sizeof(ipx));

	port = 0;
	type = NA_IP;

	if (!pch || pch[0] == 0)			// but let's not crash
		return false;

	if (pch[0] >= '0' && pch[0] <= '9' && strchr(pch, '.'))
	{
		int n1, n2, n3, n4, n5;
		int nRes = sscanf(pch, "%d.%d.%d.%d:%d", &n1, &n2, &n3, &n4, &n5);
		if (nRes >= 4)
		{
			SetIP(n1, n2, n3, n4);
		}

		if (nRes == 5)
		{
			SetPort(htons((uint16_t)n5));
		}

		if (nRes >= 4)
			return true;
	}
	else
	{
		struct sockaddr sadr = {};

		struct sockaddr_in *p = (struct sockaddr_in *)&sadr;
		p->sin_family = AF_INET;
		p->sin_port = 0;

		char hostname[128];
		strncpy(hostname, pch, sizeof(hostname));

		// search port
		auto pchColon = strrchr(hostname, ':');
		if (pchColon)
		{
			*pchColon = '\0';
			*(short *)&p->sin_port = htons(atoi(pchColon + 1));
		}

		struct addrinfo *hostinfo = nullptr;	// will point to the results

		// DNS it
		int errcode = getaddrinfo(hostname, NULL, NULL, &hostinfo);
		if (errcode != 0 || !hostinfo)
		{
			// doesn't resolved
			return false;
		}

		// Use first result
		p->sin_addr = ((struct sockaddr_in *)hostinfo->ai_addr)->sin_addr;
		freeaddrinfo(hostinfo);

		return SetFromSockadr(&sadr);
	}

	return false;
}

bool netadr0_t::SetFromSockadr(const struct sockaddr *s)
{
	if (s->sa_family == AF_INET)
	{
		type = NA_IP;

		*(int *)&ip = ((struct sockaddr_in *)s)->sin_addr.s_addr;
		port = ((struct sockaddr_in *)s)->sin_port;
		return true;
	}
	else
	{
		Clear();
		return false;
	}
}
