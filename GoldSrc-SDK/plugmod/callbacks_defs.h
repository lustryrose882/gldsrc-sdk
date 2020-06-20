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

#include "engine/cmd.h"
#include "engine/svcmsg.h"
#include "engine/usermsg.h"

class CSizeBuf;

struct usermsg_info_t: public plugmod::callback_t<>
{
#if defined(CLIENT_CORE)
	usermsg_info_t(CSizeBuf *_msg) : msg(_msg) {}
#endif

	CSizeBuf *msg = nullptr;
};

struct svcmsg_info_t: public plugmod::callback_t<>
{
#if defined(CLIENT_CORE)
	svcmsg_info_t(CSizeBuf *_msg) : msg(_msg) {}
#endif

	CSizeBuf *msg = nullptr;
};

struct cmd_info_t: public plugmod::callback_t<>
{
#if defined(CLIENT_CORE)
	cmd_info_t(class ConParams &params);
#endif

	const char *ArgS() const
	{
		return args;
	}

	const char **ArgV() const
	{
		return const_cast<const char **>(this->argv);
	}

	const char *ArgV(int i) const
	{
		return const_cast<const char *>(this->argv[i]);
	}

	const int ArgC() const
	{
		return this->argc;
	}

private:
	char        *argv[MAX_CMD_TOKENS] = {};
	const char  *args   = nullptr;
	int          argc   = 0;
};
