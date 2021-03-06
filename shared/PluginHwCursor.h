// ----------------------------------------------------------------------------
//
// PluginHwCursor.h
//
// ----------------------------------------------------------------------------

#ifndef _SimulatorPluginLibrary_H__
#define _SimulatorPluginLibrary_H__

#include <string>
#include <Windows.h>
#include <commctrl.h>
#include <stringapiset.h>

#include <CoronaLua.h>
#include <CoronaMacros.h>
#include <CoronaLibrary.h>

// ----------------------------------------------------------------------------

CORONA_EXPORT int luaopen_plugin_hwcursor(lua_State *L);

// ----------------------------------------------------------------------------

static int initPlugin(lua_State *L);
static int freePlugin(lua_State *L);

static int loadCursor(lua_State *L);
static int freeCursor(lua_State *L);

static int setCursor(lua_State *L);
static int resetCursor(lua_State *L);

static int setVisibility(lua_State *L);

static int setExitShim(lua_State* L);

// ----------------------------------------------------------------------------

std::wstring s2ws(const std::string &s) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    std::wstring buf;
    buf.resize(len);
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, const_cast<wchar_t*>(buf.c_str()), len);
    return buf;
}

// ----------------------------------------------------------------------------

#endif // _SimulatorPluginLibrary_H__
