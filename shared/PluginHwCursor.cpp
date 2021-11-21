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
            {"destroyCursor", destroyCursor},
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
                CoronaLuaError(state, "[hwcursor] The error below occurred while calling the callback function");
                CoronaLuaError(state, lua_tostring(state, -1));
            }
        }
        else {
            CoronaLuaError(state, "[hwcursor] No exit callback was found");
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

// Requires 2 calls to actually set the cursor
// 1st is to preload and second to actually set the cursor using pointer to preloaded resource
static int loadCursor(lua_State *L) {
    if(lua_islightuserdata(L, 1)) {
        currentCursor = (HCURSOR)lua_touserdata(L, 1);
        SetCursor(currentCursor);
        return 0;
    }
    else {
        std::string cursorLoc = lua_tostring(L, 1);
        // Allows for actual cursor size to be used with no constraints, i.e: even 256x256 size cursors will display at this
        // size with no downsizing being performed as happens with LoadCursorFromFile
        HCURSOR cursor = (HCURSOR)LoadImage(NULL, s2ws(cursorLoc).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
        lua_pushlightuserdata(L, cursor);
        return 1;
    }
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
    SetCursor(currentCursor);
    return 0;
}

// ----------------------------------------------------------------------------

static int destroyCursor(lua_State *L) {
    HCURSOR cursor = (HCURSOR)lua_touserdata(L, 1);
    if(cursor == currentCursor) {
        currentCursor = NULL;
        SetCursor(currentCursor);
    }
    DestroyCursor(cursor);
    /*
    if(!DestroyCursor(cursor)) {
        CoronaLuaError(L, "[hwcursor] The error below occurred while destroying the cursor");
        CoronaLuaError(L, GetLastErrorAsString().c_str());
    }
    */
    return 0;
}

// ----------------------------------------------------------------------------

static int loadWinCursor(lua_State *L) {
    int cursor = lua_tonumber(L, 1);
    switch(cursor) {
        case 1:
            currentCursor = LoadCursor(NULL, IDC_ARROW);
            break;
        case 2:
            currentCursor = LoadCursor(NULL, IDC_HAND);
            break;
        case 3:
            currentCursor = LoadCursor(NULL, IDC_CROSS);
            break;
        case 4:
            currentCursor = LoadCursor(NULL, IDC_IBEAM);
            break;
        case 5:
            currentCursor = LoadCursor(NULL, IDC_NO);
            break;
        case 6:
            currentCursor = LoadCursor(NULL, IDC_SIZEALL);
            break;
        case 7:
            currentCursor = LoadCursor(NULL, IDC_WAIT);
            break;
        case 8:
            currentCursor = LoadCursor(NULL, IDC_HELP);
            break;
        case 9:
            currentCursor = LoadCursor(NULL, IDC_APPSTARTING);
            break;
        case 10:
            currentCursor = LoadCursor(NULL, IDC_SIZENESW);
            break;
        case 11:
            currentCursor = LoadCursor(NULL, IDC_SIZENS);
            break;
        case 12:
            currentCursor = LoadCursor(NULL, IDC_SIZENWSE);
            break;
        case 13:
            currentCursor = LoadCursor(NULL, IDC_SIZEWE);
            break;
        case 14:
            currentCursor = LoadCursor(NULL, IDC_UPARROW);
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
