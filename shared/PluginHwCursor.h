//////////////////////////////////////////////////////////////////////////////
//
// This file is part of the Corona game engine.
// For overview and more information on licensing please refer to README.md 
// Home page: https://github.com/coronalabs/corona
// Contact: support@coronalabs.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _SimulatorPluginLibrary_H__
#define _SimulatorPluginLibrary_H__

#include <string>
#include <Windows.h>
#include <stringapiset.h>

#include <CoronaLua.h>
#include <CoronaMacros.h>

// ----------------------------------------------------------------------------

// This corresponds to the name of the library, e.g. [Lua] require "plugin.hwcursor"
// where the '.' is replaced with '_'
CORONA_EXPORT int luaopen_plugin_hwcursor( lua_State *L );

// ----------------------------------------------------------------------------

#endif // _SimulatorPluginLibrary_H__

// ----------------------------------------------------------------------------

static int initPlugin(lua_State *L);
static int loadCursor(lua_State *L);
static int freeCursor(lua_State *L);
static int showCursor(lua_State *L);
static int hideCursor(lua_State *L);
static int resetCursor(lua_State *L);

// ----------------------------------------------------------------------------

std::wstring s2ws(const std::string &s) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    std::wstring buf;
    buf.resize(len);
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, const_cast<wchar_t *>(buf.c_str()), len);
    return buf;
}