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

#include "maintypes.h"
#include "enums.h"
#include "netadr.h"
#include "common/net_shared.h"
#include "common.h"
#include "svcmsg.h"
#include "engine/Sizebuf.h"

// 0 == regular, 1 == file stream
enum
{
	FRAG_NORMAL_STREAM = 0,
	FRAG_FILE_STREAM,

	MAX_STREAMS
};

const int PORT_ANY				= -1;
const int PORT_TRY_MAX			= 10;

const int TCP_MAX_ACCEPTS		= 8;
const float TCP_CONNECT_TIMEOUT	= 4.0f;

const int LOOPBACK_SOCKETS		= 2;

// Flow control bytes per second limits
const float MAX_RATE			= 100000.0f;
const float MIN_RATE			= 1000.0f;

const int MAX_UPDATE_RATE       = 102;
const int MIN_UPDATE_RATE       = 20;

// Default data rate
const float DEFAULT_RATE		= 30000.0f;

// NETWORKING INFO

// Max size of udp packet payload
const int MAX_UDP_PACKET		= 4010; // 9 bytes SPLITHEADER + 4000 payload?

// Max length of a reliable message
const int MAX_MSGLEN			= 3990; // 10 reserved for fragheader?

// Max length of unreliable message
const int MAX_DATAGRAM			= 4000;

// This is the packet payload without any header bytes (which are attached for actual sending)
const int NET_MAX_PAYLOAD		= 65536;

// This is the payload plus any header info (excluding UDP header)

// Packet header is:
//  4 bytes of outgoing seq
//  4 bytes of incoming seq
//  and for each stream
// {
//  byte (on/off)
//  int (fragment id)
//  short (startpos)
//  short (length)
// }
#define HEADER_BYTES (8 + MAX_STREAMS * 9)

// Pad this to next higher 16 byte boundary
// This is the largest packet that can come in/out over the wire, before processing the header
//  bytes will be stripped by the networking channel layer
//#define NET_MAX_MESSAGE PAD_NUMBER( ( MAX_MSGLEN + HEADER_BYTES ), 16 )
// This is currently used value in the engine. TODO: define above gives 4016, check it why.
const int NET_MAX_MESSAGE = 4037;

enum
{
	FLOW_OUTGOING = 0,
	FLOW_INCOMING,

	MAX_FLOWS
};

// Message data
typedef struct flowstats_s
{
	int size;		// Size of message sent/received
	double time;	// Time that message was sent/received
} flowstats_t;

const int MAX_LATENT = 32;

typedef struct flow_s
{
	flowstats_t stats[MAX_LATENT];	// Data for last MAX_LATENT messages
	int current;					// Current message position
	double nextcompute;				// Time when we should recompute k/sec data
	// Average data
	float kbytespersec;
	float avgkbytespersec;
} flow_t;

const int FRAGMENT_C2S_MIN_SIZE = 16;
const int FRAGMENT_S2C_MIN_SIZE = 256;
const int FRAGMENT_S2C_MAX_SIZE = 1024;

const int CLIENT_FRAGMENT_SIZE_ONCONNECT = 128;
const int CUSTOMIZATION_MAX_SIZE = 20480;

#if !defined(REHLDS_FIXES) && !defined(_SERVER)
// Size of fragmentation buffer internal buffers
const int FRAGMENT_MAX_SIZE = 1400;
const int MAX_FRAGMENTS = 25000;
#else
const int FRAGMENT_MAX_SIZE = 1024;
#endif

// Client sends normal fragments only while connecting
#define MAX_NORMAL_FRAGMENTS (NET_MAX_PAYLOAD / CLIENT_FRAGMENT_SIZE_ONCONNECT)

// While client is connecting it sending fragments with minimal size, also it transfers sprays with minimal fragments...
// But with sv_delayed_spray_upload it sends with cl_dlmax fragment size
#define MAX_FILE_FRAGMENTS (CUSTOMIZATION_MAX_SIZE / FRAGMENT_C2S_MIN_SIZE)

const int UDP_HEADER_SIZE = 28;
const int MAX_RELIABLE_PAYLOAD = 1200;

#define MAKE_FRAGID(id,count)	((( id & 0xffff) << 16) | (count & 0xffff))
#define FRAG_GETID(fragid)		((fragid >> 16) & 0xffff)
#define FRAG_GETCOUNT(fragid)	(fragid & 0xffff)

// Generic fragment structure
typedef struct fragbuf_s
{
	struct fragbuf_s	*next;									// Next buffer in chain
	int					bufferid;								// Id of this buffer
	sizebuf_t			frag_message;							// Message buffer where raw data is stored
	byte				frag_message_buf[FRAGMENT_MAX_SIZE];	// The actual data sits here
	qboolean			isfile;									// Is this a file buffer?
	qboolean			isbuffer;								// Is this file buffer from memory ( custom decal, etc. ).
	qboolean			iscompressed;
	char				filename[MAX_PATH];						// Name of the file to save out on remote host
	int					foffset;								// Offset in file from which to read data
	int					size;									// Size of data to read at that offset
} fragbuf_t;

// Waiting list of fragbuf chains
typedef struct fragbufwaiting_s
{
	fragbufwaiting_s	*next;			// Next chain in waiting list
	int					fragbufcount;	// Number of buffers in this chain
	fragbuf_t			*fragbufs;		// The actual buffers
} fragbufwaiting_t;

// Network Connection Channel
typedef struct netchan_s
{
	netsrc_t sock;							// NS_SERVER or NS_CLIENT, depending on channel.
	netadr0_t remote_address;				// Address this channel is talking to.

	int player_slot;
	float last_received;					// For timeouts.  Time last message was received.
	float connect_time;						// Time when channel was connected.

	// Bandwidth choke
	//
	double rate;							// Bytes per second
	double cleartime;						// If realtime > cleartime, free to send next packet

	// Sequencing variables
	//
	int incoming_sequence;					// Increasing count of sequence numbers
	int incoming_acknowledged;				// # of last outgoing message that has been ack'd.
	int incoming_reliable_acknowledged;		// Toggles T/F as reliable messages are received.
	int incoming_reliable_sequence;			// single bit, maintained local
	int outgoing_sequence;					// Message we are sending to remote
	int reliable_sequence;					// Whether the message contains reliable payload, single bit
	int last_reliable_sequence;				// Outgoing sequence number of last send that had reliable data

	void *connection_status;
	int (*pfnNetchan_Blocksize)(void *);

	// Staging and holding areas
	sizebuf_t message;
	byte message_buf[MAX_MSGLEN];

	// Reliable message buffer. We keep adding to it until reliable is acknowledged. Then we clear it.
	int reliable_length;
	byte reliable_buf[MAX_MSGLEN];

	// Waiting list of buffered fragments to go onto queue. Multiple outgoing buffers can be queued in succession.
	fragbufwaiting_t *waitlist[MAX_STREAMS];

	// Is reliable waiting buf a fragment?
	int reliable_fragment[MAX_STREAMS];
	// Buffer id for each waiting fragment
	unsigned int reliable_fragid[MAX_STREAMS];

	// The current fragment being set
	fragbuf_t *fragbufs[MAX_STREAMS];
	// The total number of fragments in this stream
	int fragbufcount[MAX_STREAMS];

	// Position in outgoing buffer where frag data starts
	short int frag_startpos[MAX_STREAMS];
	// Length of frag data in the buffer
	short int frag_length[MAX_STREAMS];

	// Incoming fragments are stored here
	fragbuf_t *incomingbufs[MAX_STREAMS];
	// Set to true when incoming data is ready
	qboolean incomingready[MAX_STREAMS];

	// Only referenced by the FRAG_FILE_STREAM component
	// Name of file being downloaded
	char incomingfilename[MAX_PATH];

	void *tempbuffer;
	int tempbuffersize;

	// Incoming and outgoing flow metrics
	flow_t flow[MAX_FLOWS];
} netchan_t;
