// ----------------------------------------------------------------------------
// 
// PluginHwCursor.cpp
// 
// ----------------------------------------------------------------------------

#include "PluginHwCursor.h"

// ----------------------------------------------------------------------------

CORONA_EXPORT int CoronaPluginLuaLoad_plugin_hwcursor(lua_State *);

// ----------------------------------------------------------------------------

CORONA_EXPORT int luaopen_plugin_hwcursor(lua_State *L) {

    lua_CFunction factory = Corona::Lua::Open<CoronaPluginLuaLoad_plugin_hwcursor>;
    int result = CoronaLibraryNewWithFactory(L, factory, NULL, NULL);

    if(result) {
        const luaL_Reg kFunctions[] = {
            {"_initPlugin", initPlugin},
            {"freePlugin", freePlugin},

            {"loadCursor", loadCursor},
            {"freeCursor", freeCursor},

            {"setCursor", setCursor},
            {"resetCursor", resetCursor},

            {"setVisibility", setVisibility},

            {"_setExitShim", setExitShim},
            {NULL, NULL}
        };

        luaL_register(L, NULL, kFunctions);
    }

    return result;
}

// ----------------------------------------------------------------------------

HWND windowHandle;
HCURSOR currentCursor;

lua_State *state;
static int shim = 0;
bool bare_metal = FALSE;

// ----------------------------------------------------------------------------

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
    if(uMsg == WM_SETCURSOR) {
        if(currentCursor && LOWORD(lParam) == HTCLIENT) {
            SetCursor(currentCursor);
            return TRUE;
        }
    }
    else if(uMsg == WM_CLOSE) {
        RemoveWindowSubclass(windowHandle, &WindowProc, 1);

        if(bare_metal) {
            // Hack to prevent crashing on exit and having to click "Close" twice
            if(shim != 0) {
                lua_rawgeti(state, LUA_REGISTRYINDEX, shim);
                if(lua_pcall(state, 0, 0, 0) != 0) {
                    CoronaLuaError(state, "[hwcursor] Clean-exit shim failed with error message:");
                    CoronaLuaError(state, lua_tostring(state, -1));
                }
            }
            else {
                CoronaLuaError(state, "[hwcursor] Clean-exit shim was set incorrectly, cannot guarantee clean exit");
            }
            return FALSE;
        }
    }
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
    HCURSOR cursor = (HCURSOR)LoadImage(NULL, s2ws(cursorLoc).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
    lua_pushlightuserdata(L, cursor);
    return 1;
}

// ----------------------------------------------------------------------------

static int freeCursor(lua_State *L) {
    HCURSOR cursor = (HCURSOR)lua_touserdata(L, 1);
    if(cursor == currentCursor) {
        resetCursor(L);
    }
    DestroyCursor(cursor);
    return 0;
}

// ----------------------------------------------------------------------------

static int setCursor(lua_State *L) {
    currentCursor = (HCURSOR)lua_touserdata(L, 1);
    SetCursor(currentCursor);
    return 0;
}

// ----------------------------------------------------------------------------

static int resetCursor(lua_State *L) {
    currentCursor = NULL;
    SetCursor(currentCursor);
    return 0;
}

// ----------------------------------------------------------------------------

static int setVisibility(lua_State *L) {
    bool visibility = lua_toboolean(L, 1);
    ShowCursor(visibility);
    return 0;
}

// ----------------------------------------------------------------------------
// --------------------------------!DANGER ZONE!-------------------------------

static int setExitShim(lua_State *L) {
    state = L;
    bare_metal = TRUE;
    shim = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}
