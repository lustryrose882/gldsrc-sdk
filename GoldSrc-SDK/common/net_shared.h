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

const int PROTOCOL_VERSION				= 48;

// all OOB packet start with this sequence
const int CONNECTIONLESS_HEADER			= 0xFFFFFFFF;
const int CONNECTIONLESS_SPLITPACKET	= 0xFFFFFFFE;

const int MAX_VOICEDATA_LEN				= 4096;

// MAX_CHALLENGES is made large to prevent a denial
// of service attack that could cycle all of them
// out before legitimate users connected
const int MAX_CHALLENGES				= 1024;

// info request
const char S2A_SOURCE_INFO				= 'I'; // new source response (Address, hostname, map, gamedir, gamedescription, active players, maxplayers, protocol)
const char S2A_INFO						= 'C'; // deprecated goldsrc response
const char S2A_INFO_DETAILED			= 'm'; // New Query protocol, returns dedicated or not, + other performance info.

const char S2A_PROXY_LISTEN				= 'G';
const char S2A_PROXY_REDIRECT			= 'L';
const char S2A_PLAYERS					= 'D'; // Response details about each player on the server
const char S2A_RULES					= 'E'; // Number of rules + string key and string value pairs

/* ------ S2C_* - Server to client ------ */
// Rejected the connection because the password is invalid
const char S2C_REJECT_BADPASSWORD		= '8';

// Rejected the connection by explain the reason
const char S2C_REJECT					= '9';

// Client connection is initiated by requesting a challenge value
// the server sends this value back
const char S2C_CHALLENGE				= 'A';	// + challenge value

// Send a userid, client remote address, is this server secure and engine build number
const char S2C_CONNECTION				= 'B';

// HLMaster rejected a server's connection because the server needs to be updated
const char M2S_REQUESTRESTART			= 'O';

// send a log event as key value
const char S2A_LOGSTRING				= 'R';

// Send a log string
const char S2A_LOGKEY					= 'S';

// Basic information about the server
const char A2S_INFO						= 'T';

// Details about each player on the server
const char A2S_PLAYER					= 'U';

// The rules the server is using
const char A2S_RULES					= 'V';

/* ------ A2A_* - Another Answer to ------ */
// Another user is requesting a challenge value from this machine
const char A2A_GETCHALLENGE				= 'W';	// Request challenge # from another machine

// Generic Ping Request
const char A2A_PING						= 'i';	// respond with an A2A_ACK

// Generic Ack
const char A2A_ACK						= 'j';	// general acknowledgement without info

// Print to client console
const char A2A_PRINT					= 'l';	// print a message on client

// Challenge response from master
const char M2A_CHALLENGE				= 's';	// + challenge value

const char M2A_UPDATE					= 'f';	// Send server list

const char M2A_UPDATE_FINALLY			= 'Q';	// Tell me that this packet is finalized

enum clc_commands_e
{
	clc_bad,
	clc_nop,
	clc_move,
	clc_stringcmd,
	clc_delta,
	clc_resourcelist,
	clc_tmove,
	clc_fileconsistency,
	clc_voicedata,
	clc_hltv,
	clc_cvarvalue,
	clc_cvarvalue2,

	clc_custom_max,
	clc_endoflist = 255,
};
