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

// Macros to hook function calls into the HUD object
#define HOOK_MESSAGE(x) gEngfuncs.pfnHookUserMsg(#x, __MsgFunc_##x);

#define DECLARE_MESSAGE(y, x)                                         \
	int __MsgFunc_##x(const char *pszName, int iSize, void *pbuf)     \
	{                                                                 \
		return gHUD.y.MsgFunc_##x(pszName, iSize, pbuf);              \
	}

#define DECLARE_MESSAGE_BASE(x)                                       \
	int __MsgFunc_##x(const char *pszName, int iSize, void *pbuf)     \
	{                                                                 \
		return gHUD.MsgFunc_##x(pszName, iSize, pbuf);                \
	}

#define DECLARE_MESSAGE_VIEWPORT(p, x)                                \
	int __MsgFunc_##x(const char *pszName, int iSize, void *pbuf)     \
	{                                                                 \
		if (p)                                                        \
			return p->MsgFunc_##x(pszName, iSize, pbuf);              \
		return 0;                                                     \
	}

#define HOOK_COMMAND(x, y) gEngfuncs.pfnAddCommand(x, __CmdFunc_##y);
#define HOOK_EVENT(x, y)   gEngfuncs.pfnHookEvent("events/" #x ".sc", EV_##y)

#define DECLARE_COMMAND(y, x)   \
	void __CmdFunc_##x()        \
	{                           \
		gHUD.y.UserCmd_##x();   \
	}

#define DECLARE_COMMAND_BASE(x) \
	void __CmdFunc_##x()        \
	{                           \
		gHUD.##x();             \
	}

#undef CVAR_GET_FLOAT
#undef CVAR_GET_STRING
#undef CVAR_GET_POINTER
#undef CVAR_SET_FLOAT
#undef LOAD_FILE_FOR_ME
#undef FREE_FILE

inline struct cvar_s *CVAR_GET_POINTER(const char *x) { return gEngfuncs.pfnGetCvarPointer(x); }
inline float CVAR_GET_FLOAT(const char *x) { return gEngfuncs.pfnGetCvarFloat(x); }
inline int CVAR_GET_INT(const char *x) { return static_cast<int>(gEngfuncs.pfnGetCvarFloat(x)); }
inline void CVAR_SET_FLOAT(const char *x, float value) { gEngfuncs.Cvar_SetValue(x, value); }
inline const char *CVAR_GET_STRING(const char *x) { return gEngfuncs.pfnGetCvarString(x); }
inline struct cvar_s *CVAR_CREATE(const char *cv, const char *val, const int flags) { return gEngfuncs.pfnRegisterVariable(cv, val, flags); }
inline void COMMAND_CREATE(const char *cmd_name, void (*function)()) { gEngfuncs.pfnAddCommand(cmd_name, function); }
inline char *LOAD_FILE_FOR_ME(const char *filename, int *pLength = nullptr) { return reinterpret_cast<char *>(gEngfuncs.COM_LoadFile(filename, 5, pLength)); }
inline void FREE_FILE(void *buffer) { gEngfuncs.COM_FreeFile(buffer); }
inline char *PARSE_FILE(char *data, char *token) { return gEngfuncs.COM_ParseFile(data, token); }

#define SPR_Load			(*gEngfuncs.pfnSPR_Load)
#define SPR_Set				(*gEngfuncs.pfnSPR_Set)
#define SPR_Frames			(*gEngfuncs.pfnSPR_Frames)
#define SPR_GetList			(*gEngfuncs.pfnSPR_GetList)

#define SPR_Draw			(*gEngfuncs.pfnSPR_Draw)			// draws a the current sprite as solid
#define SPR_DrawHoles		(*gEngfuncs.pfnSPR_DrawHoles)		// draws the current sprites,  with color index255 not drawn (transparent)
#define SPR_DrawAdditive	(*gEngfuncs.pfnSPR_DrawAdditive)	// adds the sprites RGB values to the background  (additive transulency)

#define SPR_EnableScissor	(*gEngfuncs.pfnSPR_EnableScissor)	// sets a clipping rect for HUD sprites.  (0,0) is the top-left hand corner of the screen
#define SPR_DisableScissor	(*gEngfuncs.pfnSPR_DisableScissor)	// disables the clipping rect
#define FillRGBA			(*gEngfuncs.pfnFillRGBA)

#define ScreenHeight		(gHUD.m_scrinfo.iHeight)			// returns the height of the screen, in pixels
#define ScreenWidth			(gHUD.m_scrinfo.iWidth)				// returns the width of the screen, in pixels

#define BASE_XRES			640.f

// use this to project world coordinates to screen coordinates
#define XPROJECT(x)			((1.0f + (x)) * ScreenWidth * 0.5f)
#define YPROJECT(y)			((1.0f - (y)) * ScreenHeight * 0.5f)

#define XRES(x)				(x  * ((float)ScreenWidth / 640))
#define YRES(y)				(y  * ((float)ScreenHeight / 480))

#define GetScreenInfo				(*gEngfuncs.pfnGetScreenInfo)
#define ServerCmd					(*gEngfuncs.pfnServerCmd)
#define EngineClientCmd				(*gEngfuncs.pfnClientCmd)
#define EngineFilteredClientCmd		(*gEngfuncs.pfnFilteredClientCmd)
#define SetCrosshair				(*gEngfuncs.pfnSetCrosshair)
//#define AngleVectors				(*gEngfuncs.pfnAngleVectors)

// Gets the height & width of a sprite,  at the specified frame
inline int SPR_Height(HSPRITE x, int f)	{ return gEngfuncs.pfnSPR_Height(x, f); }
inline int SPR_Width(HSPRITE x, int f)	{ return gEngfuncs.pfnSPR_Width(x, f); }

inline client_textmessage_t *TextMessageGet(const char *pName) { return gEngfuncs.pfnTextMessageGet(pName); }
inline int TextMessageDrawChar(int x, int y, int number, int r, int g, int b)
{
	return gEngfuncs.pfnDrawCharacter(x, y, number, r, g, b);
}

inline int TextVGUI2MessageDrawCharAdd(int x, int y, int number, int r, int g, int b, unsigned int font)
{
	return gEngfuncs.pfnVGUI2DrawCharacterAdd(x, y, number, r, g, b, font);
}

inline int DrawConsoleString(int x, int y, const char *string)
{
	return gEngfuncs.pfnDrawConsoleString(x, y, string);
}

inline void DrawSetTextColor(float r, float g, float b)
{
	gEngfuncs.pfnDrawSetTextColor(r, g, b);
}

inline void GetConsoleStringSize(const char *string, int *width, int *height)
{
	gEngfuncs.pfnDrawConsoleStringLen(string, width, height);
}

inline int ConsoleStringLen(const char *string)
{
	int _width, _height;
	GetConsoleStringSize(string, &_width, &_height);
	return _width;
}

inline void ConsolePrint(const char *string)
{
	gEngfuncs.pfnConsolePrint(string);
}

inline void CenterPrint(const char *string)
{
	gEngfuncs.pfnCenterPrint(string);
}

inline char *safe_strcpy(char *dst, const char *src, int len_dst)
{
	if (len_dst <= 0)
	{
		return NULL; // this is bad
	}

	strncpy(dst, src, len_dst);
	dst[len_dst - 1] = '\0';

	return dst;
}

inline int safe_sprintf(char *dst, int len_dst, const char *format, ...)
{
	if (len_dst <= 0)
	{
		return -1; // this is bad
	}

	va_list v;
    va_start(v, format);
	_vsnprintf(dst,len_dst,format,v);
	va_end(v);

	dst[len_dst - 1] = '\0';

	return 0;
}

// sound functions
inline void PlaySound(char *pszSound, float vol) { gEngfuncs.pfnPlaySoundByName(pszSound, vol); }
inline void PlaySound(int iSound, float vol) { gEngfuncs.pfnPlaySoundByIndex(iSound, vol); }
inline void PlaySoundVoice(const char *pszSound, float vol, int pitch) { gEngfuncs.pfnPlaySoundVoiceByName(pszSound, vol, pitch); }
inline void PlaySoundAtPitch(const char *pszSound, float vol, int pitch) { gEngfuncs.pfnPlaySoundByNameAtPitch(pszSound, vol, pitch); }

void ScaleColors(int &r, int &g, int &b, int a);
void ScaleColors(float &r, float &g, float &b, int a);

//#define DotProduct(x,y) ((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
//#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
//#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
//#define VectorCopy(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}
//inline void VectorClear(float *a) { a[0]=0.0;a[1]=0.0;a[2]=0.0;}
//float Length(const float *v);
//void VectorMA(const float *veca, float scale, const float *vecb, float *vecc);
//void VectorScale(const float *in, float scale, float *out);
//float VectorNormalize(float *v);
//void VectorInverse(float *v);

//extern Vector vec3_origin;

// disable 'possible loss of data converting float to int' warning message
#pragma warning(disable:4244)

// disable 'truncation from 'const double' to 'float' warning message
#pragma warning(disable:4305)

inline void UnpackRGB(int &r, int &g, int &b, unsigned long ulRGB)
{
	r = (ulRGB & 0xFF0000) >> 16;
	g = (ulRGB & 0xFF00) >> 8;
	b = (ulRGB & 0xFF);
}

inline void UnpackRGB(float &r, float &g, float &b, unsigned long ulRGB)
{
	r = static_cast<float>((ulRGB & 0xFF0000) >> 16);
	g = static_cast<float>((ulRGB & 0xFF00) >> 8);
	b = static_cast<float>((ulRGB & 0xFF));
}

HSPRITE LoadSprite(const char *pszName);
