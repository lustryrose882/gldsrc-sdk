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

#include "callresult.h"
#include "callbacks_defs.h"

enum { k_iPlugmodCallbacks     = 100 };
enum { k_iPlugmodUserCallbacks = 700 };

enum ECallbackId
{
	k_ECallbackId_None,
	k_ECallbackId_ConnectionToServer = k_iPlugmodCallbacks,
	k_ECallbackId_ConnectedToServer,
	k_ECallbackId_ConnectionAccepted,
	k_ECallbackId_DisconnectedFromServer,
	k_ECallbackId_ValidateFilterCmd,
	k_ECallbackId_ValidateFilterDownloadFile,
	k_ECallbackId_SendConsistencyInfo,
	k_ECallbackId_PreparedConColorPrint,
	k_ECallbackId_DemoPlayerFileLoad,
	k_ECallbackId_DemoPlayerFileStop,
	k_ECallbackId_DemoPlayerFileLoadComplete,
	k_ECallbackId_DemoPlayerViewInfo,
	k_ECallbackId_VGuiPaint,
	k_ECallbackId_DrawBackgroundImage,
	k_ECallbackId_ActivateDemoUI,
	k_ECallbackId_ActivateGameUI,
	k_ECallbackId_HideGameUI,
	k_ECallbackId_LoadingStarted,
	k_ECallbackId_LoadingFinished,
	k_ECallbackId_GameSizeChanged
};

#include <tier1/utlvector.h>
#include "common/demo_info.h"

// Called when a player connecting to server
//
// @event OnConnectingToServer
//
struct ConnectingToServer_t: public plugmod::callback_t<k_ECallbackId_ConnectionToServer>
{
	netadr_t adr;
	bool secure; // true on server have secure connection (authemu), false otherwise
};

// Called when a player fully connected to server
//
// @event OnConnectedToServer
//
struct ConnectedToServer_t: public plugmod::callback_t<k_ECallbackId_ConnectedToServer>
{
	netadr_t adr;
	bool secure; // true on server have secure connection (authemu), false otherwise
};

// Called when a server accepted our request to connect secure (authemu)
//
// @event OnConnectionAccepted
//
struct ConnectionAccepted_t: public plugmod::callback_t<k_ECallbackId_ConnectionAccepted>
{
	netadr_t adr;
};

// Called when a player disconnected from server
//
// @event OnDisconnectedFromServer
//
struct DisconnectedFromServer_t: public plugmod::callback_t<k_ECallbackId_DisconnectedFromServer>
{
	netadr_t adr;
	bool secure;
};

// Called when validate command from server
//
// @event OnValidateFilterCmd
//
// @note command and value pointers it's allocated on the stack,
//       therefore, you must be copying for itself these pointers.
//
struct ValidateFilterCmd_t: public plugmod::callback_t<k_ECallbackId_ValidateFilterCmd>
{
	enum FilterType : uint8_t
	{
		k_EFilterType_Director = 0,
		k_EFilterType_StuffText,
		k_EFilterType_Other,
	};

	const char *command   = nullptr;
	const char *value     = nullptr;
	FilterType  type      = k_EFilterType_Director;
	bool        validate  = false;		// true if command is valid, false otherwise
	bool        notify    = true;		// true print to console invalid command, false otherwise
};

// Called when validate file download to client
//
// @event OnValidateFilterDownloadFile
//
struct ValidateFilterDownloadFile_t: public plugmod::callback_t<k_ECallbackId_ValidateFilterDownloadFile>
{
	const char *filename = nullptr;
	bool validate        = false;	// true if command is valid, false otherwise
	bool notify          = true;	// true print to console invalid command, false otherwise
};

// Called when a client sends files info to server
//
// @event OnSendConsistencyInfo
//
struct SendConsistencyInfo_t: public plugmod::callback_t<k_ECallbackId_SendConsistencyInfo>
{
	struct sizebuf_s      *msg;
	struct client_state_s *client;
};

// Called when a chat text is printed to console output
//
// @event OnPreparedConColorPrint
//
struct PreparedConColorPrint_t: public plugmod::callback_t<k_ECallbackId_PreparedConColorPrint>
{
	struct con_print_t
	{
		Color color        = {};
		const char *string = nullptr;
	};

	CUtlVectorShared<con_print_t> strings;	// Vector of colored strings, not contains newline
	char *(*clone)(const char *string);		// Use clone string via plugmod core
};

// Called when the engine loads a demo file
//
// @event OnDemoPlayerFileLoad
//
struct DemoPlayerFileLoad_t: plugmod::callback_t<k_ECallbackId_DemoPlayerFileLoad>
{
	const char *filename; // the demo file
};

// Called when the engine want stop a demo file
//
// @event OnDemoPlayerFileStop
//
struct DemoPlayerFileStop_t: plugmod::callback_t<k_ECallbackId_DemoPlayerFileStop>
{

};

// Called when a demo player has fully loaded the demo file
//
// @event OnDemoPlayerFileLoadComplete
//
struct DemoPlayerFileLoadComplete_t: plugmod::callback_t<k_ECallbackId_DemoPlayerFileLoadComplete>
{
	const char *filename; // the demo file
};

// Called when the engine render a view based on data from the demo file
//
// @event OnDemoPlayerViewInfo
//
struct DemoPlayerViewInfo_t: plugmod::callback_t<k_ECallbackId_DemoPlayerViewInfo>
{
	struct demoframe_s   *from;
	struct demoframe_s   *to;
	struct ref_params_s  *rp;
	float                *view;
};

// Called when the VGui is painted
//
// @event OnVGuiPaint
//
// @pre   yes
// @post  yes
struct VGuiPaint_t: plugmod::callback_t<k_ECallbackId_VGuiPaint>
{
};

// Called when the GameUI draws background base panel
//
// @event OnDrawBackgroundImage
//
struct DrawBackgroundImage_t: plugmod::callback_t<k_ECallbackId_DrawBackgroundImage>
{
};

// Called when Demo VGUI panel is activated
//
// @event OnActivateDemoUI
//
struct ActivateDemoUI_t: plugmod::callback_t<k_ECallbackId_ActivateDemoUI>
{
};

// Called when Game VGUI panel is activated
//
//
struct ActivateGameUI_t: plugmod::callback_t<k_ECallbackId_ActivateGameUI>
{
};

// Called when Game VGUI panel is hidden
//
// @event OnHideGameUI
//
struct HideGameUI_t: plugmod::callback_t<k_ECallbackId_HideGameUI>
{
};

// Called when progressbar is begin
//
// @event OnLoadingStarted
//
struct LoadingStarted_t: plugmod::callback_t<k_ECallbackId_LoadingStarted>
{
	const char *resourceType;
	const char *resourceName;
};

// Called when progressbar is completed
//
// @event OnLoadingFinished
//
struct LoadingFinished_t: plugmod::callback_t<k_ECallbackId_LoadingFinished>
{
	const char *resourceType;
	const char *resourceName;
};

// Called when the client has changed the game screen resolution
//
// @event OnGameSizeChanged
//
struct GameSizeChanged_t: plugmod::callback_t<k_ECallbackId_GameSizeChanged>
{
	int oldwidth, oldheight;
	int width,    height;
};
