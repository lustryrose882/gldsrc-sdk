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

#include <plugmod/plugmod.h>
#include <steam/steam_api.h>
#include <cl_dll/hud.h>

using namespace plugmod;

class CStubPlugin: public IPlugin
{
public:
	CStubPlugin();
	~CStubPlugin() {}

	IBaseInterface *QueryInterface(const char *pName) const;
	IPlugmodCore *GetCore() const;

	bool Query(plugin_info_t *plmInfo);
	bool Attach(IPlugmodCore *plmICore);
	void Detach(plugmod_unload_reason_e reason);
	void PreInit(plugmod_funcs_t *plmFuncs);
	void PostInit(plugmod_api_t *plmAPI);
	void RunFrame(double frametime);
	void Pause();
	void UnPause();

	plugin_info_t &GetInfo() const;
	bool IsRunning() const;

protected:
	//
	// Declare callback members
	//
	PLUGIN_CALLBACK_F(CStubPlugin, ConnectedToServer_t, ConnectedToServer, m_OnConnected);
	PLUGIN_CALLBACK_F(CStubPlugin, ValidateFilterCmd_t, ValidateFilterCmd, m_OnValidateFilterCmd);
	PLUGIN_CALLBACK_F(CStubPlugin, DisconnectedFromServer_t, DisconnectedFromServer, m_OnDisconnected);
	PLUGIN_CALLBACK_F(CStubPlugin, PreparedConColorPrint_t, PreparedConColorPrint, m_OnPreparedConColorPrint);
	PLUGIN_CALLBACK_F(CStubPlugin, DemoPlayerFileLoad_t, DemoPlayerFileLoad, m_OnDemoPlayerFileLoad);
	PLUGIN_CALLBACK_F(CStubPlugin, DemoPlayerFileStop_t, DemoPlayerFileStop, m_OnDemoPlayerFileStop);
	PLUGIN_CALLBACK_F(CStubPlugin, DemoPlayerViewInfo_t, DemoPlayerViewInfo, m_OnDemoPlayerViewInfo);
	PLUGIN_CALLBACK_F(CStubPlugin, cmd_info_t, OnStubCallbackToCall, m_OnStubCallbackToCall);

private:
	static plugin_info_t m_PluginInfo;

	cl_exportfuncs_t        m_Exportfuncs    = {};
	cl_exportmsgfuncs_t     m_ExportMsgFuncs = {};

	svc_func_t*             m_pSVCfuncs      = nullptr;
	cldll_func_t*           m_pClient        = nullptr;
	cl_enginefunc_t*        m_pEngine        = nullptr;
	engine_studio_api_t*    m_pStudio        = nullptr;
	r_studio_interface_t**  m_pRStudioAPI    = nullptr;

	client_state_t*         m_pClientState   = nullptr;
	client_static_t*        m_pClientStatic  = nullptr;

	event_hook_t**          m_pEventHooks    = nullptr;

	cldll_func_t            m_Client         = {};
	cl_enginefuncex_t       m_Engine         = {};
	engine_studio_api_t     m_Studio         = {};
	r_studio_interface_t*   m_RStudioAPI     = nullptr;

	IPlugmodCore*           m_pICore         = nullptr;
	IPlugmodCallbackMgr*    m_pICallbackMgr  = nullptr;
	IFileSystem*            m_pFileSystem    = nullptr;
	gamehud_t				m_gameHUD        = {};
};

plugin_info_t CStubPlugin::m_PluginInfo =
{
	"StubPlugin",				// name
	"1.0",						// version
	__DATE__,					// date
	"Dev-MS",					// author
	"https://dev-ms.ru",		// url
	"@devms",					// Telegram
	"Simply stub plugin",		// Detailed information about this plugin

	PLUGMOD_API_VERSION_MAJOR,
	PLUGMOD_API_VERSION_MINOR
};

CStubPlugin::CStubPlugin() :
	// Initialize callback members
	m_OnConnected(this, &CStubPlugin::ConnectedToServer),
	m_OnValidateFilterCmd(this, &CStubPlugin::ValidateFilterCmd),
	m_OnDisconnected(this, &CStubPlugin::DisconnectedFromServer),
	m_OnPreparedConColorPrint(this, &CStubPlugin::PreparedConColorPrint),
	m_OnDemoPlayerFileLoad(this, &CStubPlugin::DemoPlayerFileLoad),
	m_OnDemoPlayerFileStop(this, &CStubPlugin::DemoPlayerFileStop),
	m_OnDemoPlayerViewInfo(this, &CStubPlugin::DemoPlayerViewInfo),
	m_OnStubCallbackToCall(this, &CStubPlugin::OnStubCallbackToCall)
{
}

IBaseInterface *CStubPlugin::QueryInterface(const char *pName) const
{
	return CreateInterface(pName);
}

IPlugmodCore *CStubPlugin::GetCore() const
{
	return m_pICore;
}

bool CStubPlugin::Query(plugin_info_t *plmInfo)
{
	*plmInfo = m_PluginInfo;
	return true;
}

bool CStubPlugin::Attach(IPlugmodCore *plmICore)
{
	m_pICore = plmICore;
	m_pICallbackMgr = plmICore->GetCallbackMgr();
	m_pFileSystem = plmICore->GetFileSystem();
	return true;
}

void CStubPlugin::Detach(plugmod_unload_reason_e reason)
{
	SteamAPI_Shutdown();
}

// My custom data for callback "OnStubPluginCallbackSignaled"
struct StubPluginCallbackSignaled_t: public callback_t<k_iPlugmodUserCallbacks + 30 /* my random id callback */>
{
	const char *string;
	int value;
};

void CStubPlugin::PreInit(plugmod_funcs_t *plmFuncs)
{
	if (!SteamAPI_Init())
		return;

	m_pClient        = plmFuncs->pclfuncs;
	m_pEngine        = plmFuncs->pengfuncs;
	m_pSVCfuncs      = plmFuncs->psvcfuncs;

	m_pClientState   = plmFuncs->pcl;
	m_pClientStatic  = plmFuncs->pcls;
	m_pEventHooks    = plmFuncs->peventhook;

	m_pStudio        =  plmFuncs->pstudio;
	m_pRStudioAPI    =  plmFuncs->ppinterface;

	m_Client         = *plmFuncs->clfuncs;
	m_Engine         = *plmFuncs->engfuncs;
	m_Studio         = *plmFuncs->studio;
	m_RStudioAPI     = *plmFuncs->pinterface;
	m_Exportfuncs    = *plmFuncs->exportfuncs;
	m_ExportMsgFuncs = *plmFuncs->exportmsgfuncs;

	// Example callback manager
	// Create custom callback for my pool of plugins
	m_pICallbackMgr->RegisterCallback<StubPluginCallbackSignaled_t>("OnStubPluginCallbackSignaled");

	//
	// Another plugin as listener can itself hook this callback id
	//
	// In PostInit or somewhere else, but not PreInit because callback not registered yet by core
	// m_Exportfuncs.RegisterCallback("OnStubPluginCallbackSignaled", &m_OnStubPluginCallbackSignaled);

	// Declare inside class and initialize m_OnStubPluginCallbackSignaled on constructor
	//		CStubAnotherPlugin() :
	//		m_OnStubPluginCallbackSignaled(this, &CStubAnotherPlugin::OnStubPluginCallbackSignaled)
	//		{
	//		}
	//
	// PLUGIN_CALLBACK_F(CStubAnotherPlugin, StubPluginCallbackSignaled_t, OnStubPluginCallbackSignaled, m_OnStubPluginCallbackSignaled);
	//

	//m_pClient->pHudInitFunc = HUD_Init;
	//m_pClient->pHudFrame = HUD_Frame;
}

void CStubPlugin::OnStubCallbackToCall(cmd_info_t *info)
{
	StubPluginCallbackSignaled_t params;
	params.string = "StubPlugin.FireSignal";
	params.value = 35;

	// Fire callback for plugin listener
	m_pICallbackMgr->CallbackToAll(params);
}

void CStubPlugin::ValidateFilterCmd(ValidateFilterCmd_t *info)
{
	m_Engine.Con_PrintfEx(
		"${greeny}command${}  - ${skyblue}(%s)\n"
		"${greeny}value${}    - ${skyblue}(%s)\n"
		"${greeny}type${}     - ${skyblue}(%d)\n"
		"${greeny}validate${} - ${skyblue}(%d)\n\n",
		info->command, info->value, info->type, info->validate);
}

void CStubPlugin::ConnectedToServer(ConnectedToServer_t *info)
{
	// example output info about connect to server
	m_Engine.Con_PrintfEx("${greeny}Connected to ${red}%s\n", info->adr.ToString());
}

void CStubPlugin::DisconnectedFromServer(DisconnectedFromServer_t *info)
{
	m_Engine.Con_PrintfEx("${greeny}Disconnected from ${red}%s\n", info->adr.ToString());
}

void CStubPlugin::PreparedConColorPrint(PreparedConColorPrint_t *info)
{
	// Append time to chat text for console output
	// e.g [20:35:41] Player: Hello!

	char timedate[256];
	time_t ltime = time(nullptr);
	tm *now = localtime(&ltime);
	strftime(timedate, sizeof(timedate), "[%H:%M:%S] ", now);

	PreparedConColorPrint_t::con_print_t elem;
	elem.color  = Color(0, 255, 0, 255);
	elem.string = info->clone(timedate); // clone string, because the pointer will be destroyed at the end of this procedure

	info->strings.AddToHead(elem);
	info->Result(override);
}

void CStubPlugin::DemoPlayerFileLoad(DemoPlayerFileLoad_t *info)
{
	m_Engine.Con_PrintfEx("${red}%s:${yellow} load demo file: ${green}%s\n", __FUNC__, info->filename);
}

void CStubPlugin::DemoPlayerFileStop(DemoPlayerFileStop_t *info)
{
	m_Engine.Con_PrintfEx("${red}%s:${yellow} demo file is stopped\n", __FUNC__);
}

void CStubPlugin::DemoPlayerViewInfo(DemoPlayerViewInfo_t *info)
{
	//m_Engine.Con_PrintfEx("${red}%s:${yellow} frame %0.2f\n", __FUNC__, info.to->time);
}

void CStubPlugin::PostInit(plugmod_api_t *plmAPI)
{
	m_gameHUD = *plmAPI->phud;

	// example to get steamid
	m_Engine.Con_PrintfEx("${greeny}Your SteamID3 %s\n", SteamUser()->GetSteamID().Render());

	// register cmd for test callback manager
	m_Exportfuncs.RegisterCmd("stub_fire_callback", &m_OnStubCallbackToCall);

	// see more plugmod/callback.h
	m_Exportfuncs.RegisterCallback("OnValidateFilterCmd", &m_OnValidateFilterCmd);
	m_Exportfuncs.RegisterCallback("OnConnectedToServer", &m_OnConnected);
	m_Exportfuncs.RegisterCallback("OnDisconnectedFromServer", &m_OnDisconnected);
	m_Exportfuncs.RegisterCallback("OnPreparedConColorPrint", &m_OnPreparedConColorPrint);
	m_Exportfuncs.RegisterCallback("OnDemoPlayerFileLoad", &m_OnDemoPlayerFileLoad, true);
	m_Exportfuncs.RegisterCallback("OnDemoPlayerFileStop", &m_OnDemoPlayerFileStop);
	m_Exportfuncs.RegisterCallback("OnDemoPlayerViewInfo", &m_OnDemoPlayerViewInfo);
}

void CStubPlugin::RunFrame(double frametime)
{
	//if (m_gameHUD.initialized)
	//{
	//	m_Engine.Con_Printf(" -> health: (%d)\n", m_gameHUD.m_Health->m_iHealth);
	//}

	/* do nothing */
}

void CStubPlugin::Pause()
{
	/* do nothing */
}

void CStubPlugin::UnPause()
{
	/* do nothing */
}

plugin_info_t &CStubPlugin::GetInfo() const
{
	return m_PluginInfo;
}

bool CStubPlugin::IsRunning() const
{
	return m_pICore ? m_pICore->IsRunning(this) : false;
}

EXPOSE_SINGLE_INTERFACE(CStubPlugin, IPlugin, PLUGMOD_API_VERSION);
