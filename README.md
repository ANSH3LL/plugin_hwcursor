# HwCursor
A hardware cursor plugin for the solar2D (formerly corona-sdk) game engine

# Usage
```lua
local cursor = require(plugin.hwcursor)
cursor.initPlugin()
cursor.loadCursor(system.pathForFile('cursor.ani'))
-- cursor.loadCursor(system.pathForFile('cursor.cur'))

timer.performWithDelay(5000,
    function()
        cursor.resetCursor() -- reset to default arrow cursor
    end
)

-- Make sure to free the plugin some moments before the application needs to exit or it will crash during exit (don't currently know how to fix this)
cursor.freePlugin()

--Untested
cursor.showCursor()
cursor.hideCursor()
```

# Installation
- TBD
- Only supports windows for now