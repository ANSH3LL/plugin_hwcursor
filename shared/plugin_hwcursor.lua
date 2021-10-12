local Library = require('CoronaLibrary')

-- Create stub library
local lib = Library:new(
    {
        name = 'plugin.hwcursor',
        publisherId = 'com.ansh3ll'
    }
)

function lib.initPlugin()
    lib.initialize()

    -- Register default exit callback -> fixes issue with crashing on exit and negates need for pesky workaround
    lib.regExitCallback(
        function()
            lib.resetCursor()
            native.requestExit()
        end
    )
end

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

-- Return an instance
return lib
