local Library = require('CoronaLibrary')
--[[
local function setmt__gc(tbl, metatable)
    local proxy = newproxy(true)
    getmetatable(proxy).__gc = function() metatable.__gc(tbl) end
    tbl[proxy] = true
    return setmetatable(tbl, metatable)
end
]]--
-- Create stub library for simulator
local lib = Library:new(
    {
        name = 'plugin.hwcursor',
        publisherId = 'com.ansh3ll'
    }
)
--[[
local function cleanup(self)
    lib.resetCursor()
    lib.freePlugin()
end

function lib.init(self)
    setmt__gc(self, {__gc = cleanup})
    lib.initPlugin()
end
]]--
-- Return an instance

-- Cursors provided by windows, for use with plugin.loadWinCursor()
lib.ARROW = 1
lib.POINTER = 2
lib.CROSSHAIR = 3
lib.IBEAM = 4
lib.NOTALLOWED = 5
lib.RESIZE = 6
lib.WAIT = 7
lib.HELP = 8
lib.BUSY = 9
lib.RESIZENESW = 10
lib.RESIZENS = 11
lib.RESIZENWSE = 12
lib.RESIZEWE = 13
lib.UPARROW = 14

return lib
