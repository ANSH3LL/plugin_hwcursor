// ----------------------------------------------------------------------------
// 
// PluginHwCursor.cpp
// 
// ----------------------------------------------------------------------------

#include "PluginHwCursor.h"

#include <CoronaAssert.h>
#include <CoronaLibrary.h>

// ----------------------------------------------------------------------------

CORONA_EXPORT int CoronaPluginLuaLoad_plugin_hwcursor(lua_State *);

// ----------------------------------------------------------------------------

CORONA_EXPORT
int luaopen_plugin_hwcursor(lua_State *L) {

    lua_CFunction factory = Corona::Lua::Open<CoronaPluginLuaLoad_plugin_hwcursor>;
    int result = CoronaLibraryNewWithFactory(L, factory, NULL, NULL);

    if(result) {
        const luaL_Reg kFunctions[] = {
            {"initialize", initialize},
            {"freePlugin", freePlugin},
            {"loadCursor", loadCursor},
            {"showCursor", showCursor},
            {"hideCursor", hideCursor},
            {"resetCursor", resetCursor},
            {"loadWinCursor", loadWinCursor},
            {"regExitCallback", regExitCallback},
            {NULL, NULL}
        };

        luaL_register(L, NULL, kFunctions);
    }

    return result;
}

// ----------------------------------------------------------------------------

lua_State *state;
HWND windowHandle;
HCURSOR currentCursor;
bool cursorHidden = false;
static int exitCallback = 0;

// ----------------------------------------------------------------------------

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
    if(uMsg == WM_SETCURSOR) {
        if(currentCursor && !cursorHidden) {
            SetCursor(currentCursor);
            return true;
        }
    }
    else if(uMsg == WM_CLOSE) {
        RemoveWindowSubclass(windowHandle, &WindowProc, uIdSubclass);

        if(exitCallback != 0) {
            lua_rawgeti(state, LUA_REGISTRYINDEX, exitCallback);
            if(lua_pcall(state, 0, 0, 0) != 0) {
                CoronaLuaLog(state, "[hwcursor] the error below occurred while calling the callback function");
                CoronaLuaLog(state, lua_tostring(state, -1));
            }
        }
        else {
            CoronaLuaLog(state, "[hwcursor] no exit callback was found");
        }

        return false;
    }
    return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}

// ----------------------------------------------------------------------------

// Do NOT use this function unless you're sure you know what you're doing
// Instead use "initPlugin" as defined in plugin_hwcursor.lua
static int initialize(lua_State *L) {
    state = L;
    windowHandle = GetForegroundWindow();
    SetWindowSubclass(windowHandle, &WindowProc, 1, 0);
    return 0;
}

// ----------------------------------------------------------------------------

static int freePlugin(lua_State *L) {
    RemoveWindowSubclass(windowHandle, &WindowProc, 1);
    return 0;
}

// ----------------------------------------------------------------------------

static int loadCursor(lua_State *L) {
    std::string cursorLoc = lua_tostring(L, 1);
    currentCursor = LoadCursorFromFile(s2ws(cursorLoc).c_str());
    SetCursor(currentCursor);
    return 0;
}

// ----------------------------------------------------------------------------

static int showCursor(lua_State *L) {
    if(cursorHidden) {
        ShowCursor(true);
        cursorHidden = false;
    }
    return 0;
}

// ----------------------------------------------------------------------------

static int hideCursor(lua_State *L) {
    if(!cursorHidden) {
        ShowCursor(false);
        cursorHidden = true;
    }
    return 0;
}

// ----------------------------------------------------------------------------

static int resetCursor(lua_State *L) {
    currentCursor = NULL;
    return 0;
}

// ----------------------------------------------------------------------------

static int loadWinCursor(lua_State *L) {
    int cursor = lua_tonumber(L, 1);
    switch(cursor) {
        case 1:
            currentCursor = LoadCursorW(NULL, IDC_ARROW);
            break;
        case 2:
            currentCursor = LoadCursorW(NULL, IDC_HAND);
            break;
        case 3:
            currentCursor = LoadCursorW(NULL, IDC_CROSS);
            break;
        case 4:
            currentCursor = LoadCursorW(NULL, IDC_IBEAM);
            break;
        case 5:
            currentCursor = LoadCursorW(NULL, IDC_NO);
            break;
        case 6:
            currentCursor = LoadCursorW(NULL, IDC_SIZEALL);
            break;
        case 7:
            currentCursor = LoadCursorW(NULL, IDC_WAIT);
            break;
        case 8:
            currentCursor = LoadCursorW(NULL, IDC_HELP);
            break;
        case 9:
            currentCursor = LoadCursorW(NULL, IDC_APPSTARTING);
            break;
        case 10:
            currentCursor = LoadCursorW(NULL, IDC_SIZENESW);
            break;
        case 11:
            currentCursor = LoadCursorW(NULL, IDC_SIZENS);
            break;
        case 12:
            currentCursor = LoadCursorW(NULL, IDC_SIZENWSE);
            break;
        case 13:
            currentCursor = LoadCursorW(NULL, IDC_SIZEWE);
            break;
        case 14:
            currentCursor = LoadCursorW(NULL, IDC_UPARROW);
            break;
    }
    SetCursor(currentCursor);
    return 0;
}

// ----------------------------------------------------------------------------

// Do NOT use this function unless you're sure you know what you're doing
static int regExitCallback(lua_State *L) {
    exitCallback = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}
