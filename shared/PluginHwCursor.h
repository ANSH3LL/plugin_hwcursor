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

// ----------------------------------------------------------------------------

CORONA_EXPORT int luaopen_plugin_hwcursor(lua_State *L);

// ----------------------------------------------------------------------------

#endif // _SimulatorPluginLibrary_H__

// ----------------------------------------------------------------------------

static int initialize(lua_State *L);
static int freePlugin(lua_State *L);
static int loadCursor(lua_State *L);
static int showCursor(lua_State *L);
static int hideCursor(lua_State *L);
static int resetCursor(lua_State *L);
static int destroyCursor(lua_State *L);
static int loadWinCursor(lua_State *L);
static int regExitCallback(lua_State *L);

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
// https://stackoverflow.com/a/17387176
/*
std::string GetLastErrorAsString() {
    //Get the error message ID, if any.
    DWORD errorMessageID = GetLastError();
    if(errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    return message;
}
*/
