local Library = require "CoronaLibrary"

-- Create stub library for simulator
local lib = Library:new{ name = 'plugin.hwcursor', publisherId = 'com.ansh3ll' }

--[[
-- Default implementations
local function defaultFunction()
	print( "WARNING: The '" .. lib.name .. "' library is not available on this platform." )
end

lib.init = defaultFunction
lib.show = defaultFunction
]]--

-- Return an instance
return lib
