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

class IServerBrowser
{
public:
	// activates the server browser window, brings it to the foreground
	virtual bool Activate() = 0;

	// joins a game directly
	virtual bool JoinGame(uint32_t unGameIP, uint16_t usGamePort) = 0;

	// joins a specified game - game info dialog will only be opened if the server is fully or passworded
	virtual bool JoinGame(uint64_t ulSteamIDFriend) = 0;

	// opens a game info dialog to watch the specified server; associated with the friend 'userName'
	virtual bool OpenGameInfoDialog(uint64_t ulSteamIDFriend) = 0;

	// forces the game info dialog closed
	virtual void CloseGameInfoDialog(uint64_t ulSteamIDFriend) = 0;

	// closes all the game info dialogs
	virtual void CloseAllGameInfoDialogs() = 0;
};

#define SERVERBROWSER_INTERFACE_VERSION "ServerBrowser003"
