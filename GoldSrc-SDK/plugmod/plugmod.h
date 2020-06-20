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

#include "client_api.h"
#include "filesystem.h"
#include "tier1/interface.h"
#include "plugmod/callbacks.h"

struct gamehud_t;
class CSysModule;
class IGame;
class IVideoMode;

namespace plugmod
{


enum : size_t
{
	PLUGMOD_API_VERSION_MAJOR = 2,
	PLUGMOD_API_VERSION_MINOR = 2
};

// Flags to indicate why the plugin is being unloaded
enum plugmod_unload_reason_e
{
	PNL_NONE = 0,
	PNL_NORMAL				// Normal shutdown
};

class IPlugin;
class IPlugmodCallbackMgr;
class IPlugmodCore: public IBaseInterface
{
protected:
	virtual ~IPlugmodCore() {}

public:
	virtual size_t GetMajorVersion() const = 0;																						// Check major version Plugmod
	virtual size_t GetMinorVersion() const = 0;																						// Check minor version Plugmod
	virtual IFileSystem *GetFileSystem() const = 0;																					// Returns interface to filesystem
	virtual IPlugmodCallbackMgr *GetCallbackMgr() const = 0;																					// Returns interface to Plugmod manager useful for manage some features
	virtual size_t GetCountPlugins() const = 0;																						// Returns total of plugins
	virtual bool IsRunning(const IPlugin *pPlugin) const = 0;																		// Check state is running by plugin instance
	virtual bool IsRunning(const void *module) const = 0;																			// Check state is running by module handle
	virtual const char *GetBaseDir() const = 0;																						// Returns the path to current base directory ("C:\Games\CS")
	virtual const char *GetGameDir() const = 0;																						// Returns the path to current game directory ("C:\Games\CS\cstrike")
	virtual const char *GetFullPath(const IPlugin *pPlugin) const = 0;																// Returns the full path to current plugin directory ("C:\Games\CS\cstrike\plugmod\camera3d.dll")
	virtual const char *GetRelativePath(const IPlugin *pPlugin) const = 0;															// Returns the relative path to current plugin directory ("cstrike\plugmod\camera3d.dll")
	virtual bool GetWorkingPath(const IPlugin *pPlugin, char *destBuf, size_t unDestBufSize, const char *fmt = nullptr, ...) = 0;	// Build path from current plugin 'GetWorkingPath(this, szPath, sizeof(szPath), "config/settings.ini")'
};

class IPlugmodCallbackMgr: public IBaseInterface
{
protected:
	virtual ~IPlugmodCallbackMgr() {}

public:
	//
	// Callback
	// Plugin can callback and handle for other plugins if their are expected
	// Implemented own custom structure data into plugmod/callback.h
	//

	template <typename T>
	bool CallbackToAll(T &params)
	{
		return CallbackToAll(T::k_iCallback, &params);
	}

	template <typename T>
	bool PreCallbackToAll(T &params)
	{
		return PreCallbackToAll(T::k_iCallback, &params);
	}

	template <typename T>
	bool PostCallbackToAll(T &params)
	{
		return PostCallbackToAll(T::k_iCallback, &params);
	}

	template <typename T>
	bool RegisterCallback(const char *pszName)
	{
		return RegisterCallback(pszName, T::k_iCallback);
	}

	template <typename T>
	bool UnRegisterCallback(const char *pszName)
	{
		return UnRegisterCallback(pszName, T::k_iCallback);
	}

	virtual bool RegisterCallback(const char *pszEventName, int iCallback) = 0;
	virtual bool UnRegisterCallback(const char *pszEventName, int iCallback) = 0;

protected:
	// Callback virtual methods, you shouldn't be use directly, use only templates above
	virtual bool CallbackToAll(int iCallback, callbackbase_t *params) = 0;
	virtual bool PreCallbackToAll(int iCallback, callbackbase_t *params) = 0;
	virtual bool PostCallbackToAll(int iCallback, callbackbase_t *params) = 0;
};

#if !defined(PLUGMOD_CORE)
extern IPlugmodCallbackMgr *getInstance();

template <typename T>
inline bool CallbackToAll(T &params)
{
	if (!getInstance())
		return false;

	return getInstance()->CallbackToAll(params);
}

template <typename T>
inline bool PreCallbackToAll(T &params)
{
	if (!getInstance())
		return false;

	return getInstance()->PreCallbackToAll(params);
}

template <typename T>
inline bool PostCallbackToAll(T &params)
{
	if (!getInstance())
		return false;

	return getInstance()->PostCallbackToAll(params);
}
#endif // #if !defined(PLUGMOD_CORE)

#define PLUGMOD_CORE_VERSION "PLUGMOD_CORE_VERSION001"


// Information plugin provides about itself
struct plugin_info_t
{
	const char *name;			// full name of plugin
	const char *version;		// version
	const char *date;			// date
	const char *author;			// author name
	const char *url;			// URL
	const char *contacts;		// Skype/Telegram/email
	const char *description;	// Detailed information about this plugin

	int majorVersion;
	int minorVersion;
};

class IPluginCtx
{
protected:
	virtual ~IPluginCtx() {}

public:
	struct plugmod_funcs_t
	{
#if defined(PLUGMOD_CORE)
		void Update();
#endif // #if defined(PLUGMOD_CORE)

		svc_func_t            *psvcfuncs = nullptr;
		cl_enginefunc_t       *pengfuncs = nullptr;
		cldll_func_t          *pclfuncs  = nullptr;

		svc_func_t            *svcfuncs = nullptr;
		cl_enginefuncex_t     *engfuncs = nullptr;
		cldll_func_t          *clfuncs  = nullptr;

		cl_exportfuncs_t      *exportfuncs    = nullptr;
		cl_exportmsgfuncs_t   *exportmsgfuncs = nullptr;

		int buildId = 0;
		uint32_t hashCommit = 0u;

		client_state_t        *pcl          = nullptr;
		client_static_t       *pcls         = nullptr;
		event_hook_t         **peventhook   = nullptr;

		r_studio_interface_t **ppinterface  = nullptr;
		r_studio_interface_t **pinterface   = nullptr;

		engine_studio_api_t   *pstudio      = nullptr;
		engine_studio_api_t   *studio       = nullptr;

		IGame                **pgame        = nullptr;
		IVideoMode           **pvideomode   = nullptr;

		IFactoryList          *(*GetFactoryList)() = nullptr;

#if !defined(PLUGMOD_CORE)
	private:
#endif
		IBaseInterface        *(*InitializeInterface_Internal)(const char *interfaceName) = nullptr;

	public:
		template <class T = IBaseInterface>
		T *InitializeInterface(const char *interfaceName)
		{
			return static_cast<T *>(InitializeInterface_Internal(interfaceName));
		}
	};

	struct plugmod_api_t
	{
		int version;
		gamehud_t               *phud;
		const IPlugin           *(*GetPluginApi)(const char *name);
	};

#if !defined(PLUGMOD_CORE)
private:
#endif // #if !defined(PLUGMOD_CORE)
	virtual bool Query(plugin_info_t *plmInfo) = 0;				// Called when the plugmod query info about the plug-in
	virtual bool Attach(IPlugmodCore *plmICore) = 0;			// Called when the plug-in attach to process while a launcher start up
	virtual void Detach(plugmod_unload_reason_e reason) = 0;	// Called when launcher going shut-down or detach manually
	virtual void PreInit(plugmod_funcs_t *plmFuncs) = 0;		// Called when engine calls pInitFunc to provide cl_enginefunc_t
	virtual void PostInit(plugmod_api_t *plmAPI) = 0;			// Called when each module/plugin is loaded
	virtual void RunFrame(double time) = 0;						// Called when every frame handled by game
	virtual void Pause() = 0;									// Called when the plugin is paused (i.e should stop running but isn't unloaded)
	virtual void UnPause() = 0;									// Called when the plugin is unpaused (i.e should start executing again)
};

class IPlugin: public IBaseInterface, public IPluginCtx
{
protected:
	virtual ~IPlugin() {}

public:
	virtual IBaseInterface *QueryInterface(const char *pName) const = 0;
	virtual IPlugmodCore *GetCore() const = 0;
	virtual plugin_info_t &GetInfo() const = 0;
	virtual bool IsRunning() const = 0;
};

// Base for callbacks, used only by CPluginCallback, shouldn't be used directly
class IPluginCallback
{
public:
	IPluginCallback() { m_bThisClass = false; m_iCallback = 0; }
	virtual ~IPluginCallback() {}
	int GetICallback() const { return m_iCallback; }

	// don't add a virtual destructor because we export this binary interface across dll's
	virtual void Run(void *pvParam) = 0;

protected:
	bool m_bThisClass;
	int m_iCallback;
};

// Maps a plugmod callback to a class member function
// template params:
//	T = local class
//	P = parameter struct
template <class T, class P>
class CPluginCallback: public IPluginCallback
{
public:
	typedef void (T::*func_t)(P *);

	CPluginCallback(T *pObj, func_t func) :
		m_pObj(pObj),
		m_Func(func)
	{
		m_bThisClass = true;
		m_iCallback = P::k_iCallback;
	}

	~CPluginCallback()
	{
	}

protected:
	virtual void Run(void *pvParam)
	{
		(m_pObj->*m_Func)(static_cast<P *>(pvParam));
	}

	T *m_pObj;
	func_t m_Func;
};

template <class P>
class CPluginGlobCallback: public IPluginCallback
{
public:
	typedef void (*func_t)(P *);

	CPluginGlobCallback(func_t func) :
		m_Func(func)
	{
		m_bThisClass = false;
		m_iCallback  = P::k_iCallback;
	}

	~CPluginGlobCallback()
	{
	}

protected:
	virtual void Run(void *pvParam)
	{
		m_Func(static_cast<P *>(pvParam));
	}

	func_t m_Func;
};

// utility macro for declaring the function and callback object together
#define PLUGIN_CALLBACK(thisclass, param, var) CPluginCallback<thisclass, param> var
#define PLUGIN_CALLBACK_F(thisclass, param, func, var) CPluginCallback<thisclass, param> var; void func(param *info)

#define PLUGIN_CALLBACK_GLOB(param, var) CPluginGlobCallback<param> var
#define PLUGIN_CALLBACK_GLOB_F(param, func, var) void func(param *info); CPluginGlobCallback<param> var(&func); void func(param *info)

} // namespace plugmod

#define PLUGMOD_API_VERSION "PLUGMOD_API_VERSION001"
