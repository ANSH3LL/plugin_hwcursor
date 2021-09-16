// ----------------------------------------------------------------------------
// 
// PluginHwCursor.cpp
// 
// ----------------------------------------------------------------------------

#include "PluginHwCursor.h"

#include <CoronaAssert.h>
#include <CoronaLibrary.h>

// ----------------------------------------------------------------------------

// This corresponds to the name of the Lua file (plugin_hwcursor.lua)
// where the prefix 'CoronaPluginLuaLoad' is prepended.
CORONA_EXPORT int CoronaPluginLuaLoad_plugin_hwcursor(lua_State *);

// ----------------------------------------------------------------------------

CORONA_EXPORT
int luaopen_plugin_hwcursor(lua_State *L) {

	lua_CFunction factory = Corona::Lua::Open <CoronaPluginLuaLoad_plugin_hwcursor>;
	int result = CoronaLibraryNewWithFactory(L, factory, NULL, NULL);

    if(result) {
        const luaL_Reg kFunctions[] = {
            {"initPlugin", initPlugin},
            {"loadCursor", loadCursor},
            {"freeCursor", freeCursor},
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
LONG_PTR prevWndProc;
HCURSOR currentCursor;
bool cursorHidden = false;

// ----------------------------------------------------------------------------

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result;

	if(uMsg == WM_SETCURSOR) {
		if (currentCursor && !cursorHidden) {
			SetCursor(currentCursor);
			result = 1;
		}
	}
	else {
		result = CallWindowProc((WNDPROC)prevWndProc, hwnd, uMsg, wParam, lParam);
	}

    return result;
}

// ----------------------------------------------------------------------------

static int initPlugin(lua_State *L) {
    windowHandle = GetForegroundWindow();
    prevWndProc = SetWindowLongPtr(windowHandle, GWLP_WNDPROC, (LONG)WindowProc);
	CoronaLuaLog(L, "init");
    return 0;
}

// ----------------------------------------------------------------------------

static int loadCursor(lua_State *L) {
    std::string cursorLoc = lua_tostring(L, 1);
    currentCursor = LoadCursorFromFile(s2ws(cursorLoc).c_str());
    SetCursor(currentCursor);
    CoronaLuaLog(L, cursorLoc.c_str());
    return 0;
}

// ----------------------------------------------------------------------------

static int freeCursor(lua_State *L) {
    return 0;
}

// ----------------------------------------------------------------------------

static int showCursor(lua_State *L) {
	if(cursorHidden) {
		ShowCursor(true);
	}
    return 0;
}

// ----------------------------------------------------------------------------

static int hideCursor(lua_State *L) {
	if (!cursorHidden) {
		ShowCursor(false);
	}
    return 0;
}

// ----------------------------------------------------------------------------

static int resetCursor(lua_State *L) {
    currentCursor = NULL;
    return 0;
}
