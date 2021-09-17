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
            {"initPlugin", initPlugin},
            {"freePlugin", freePlugin},
            {"loadCursor", loadCursor},
            {"showCursor", showCursor},
            {"hideCursor", hideCursor},
            {"resetCursor", resetCursor},
            {NULL, NULL}
        };
    
        luaL_register(L, NULL, kFunctions);
    }
    
    return result;
}

// ----------------------------------------------------------------------------

HWND windowHandle;
HCURSOR currentCursor;
bool cursorHidden = false;

// ----------------------------------------------------------------------------

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
    if(uMsg == WM_SETCURSOR) {
        if(currentCursor && !cursorHidden) {
            SetCursor(currentCursor);
            return true;
        }
    }
    /*
    else if(uMsg == WM_CLOSE || uMsg == WM_DESTROY) {
        RemoveWindowSubclass(windowHandle, &WindowProc, 1);
    }
    */
    return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}

// ----------------------------------------------------------------------------

static int initPlugin(lua_State *L) {
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
