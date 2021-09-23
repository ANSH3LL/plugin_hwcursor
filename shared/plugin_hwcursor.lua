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
local lib = Library:new { name = 'plugin.hwcursor', publisherId = 'com.ansh3ll' }
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
return lib
