local Library = require('CoronaLibrary')

-- Create stub library
local lib = Library:new(
    {
        name = 'plugin.hwcursor',
        publisherId = 'com.ansh3ll'
    }
)

function lib.initPlugin()
    lib._initPlugin()
    -- Set clean-exit shim when running on bare metal
    if system.getInfo('environment') == 'device' then
        lib._setExitShim(native.requestExit)
    end
end

-- Return an instance
return lib
