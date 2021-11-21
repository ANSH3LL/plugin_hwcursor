local widget = require('widget')
local cursor = require('plugin.hwcursor')

local hidden = false
cursor.initPlugin()

-- New in this version

-- Call cursor.loadCursor the first time with the path to the cursor
-- and store the return value, which is a pointer to the cursor resource (preload step)

-- Call cursor.loadCursor the second time with the previously returned pointer
-- to actually set the cursor (usage step)

-- Cursors must be preloaded before being used
local cursors = {
    cursor1 = cursor.loadCursor(system.pathForFile('cursor1.cur')), -- Bigger than normal
    cursor2 = cursor.loadCursor(system.pathForFile('cursor2.ani')), -- Regular size
    cursor3 = cursor.loadCursor(system.pathForFile('cursor3.ani'))  -- Huge (256x256)
}

display.newText(
    {
        x = display.contentCenterX,
        y = 50,
        width = 300,
        align = 'center',
        font = native.systemFont,
        text = 'Press numbers 1-0 and keys q-r on your keyboard for windows-provided cursors'
    }
)

widget.newButton(
    {
        width = 200,
        height = 30,
        shape = 'roundedRect',
        x = display.contentCenterX,
        y = display.contentCenterY - 100,
        label = 'Reset to system cursor',
        onRelease = function() cursor.resetCursor() end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

widget.newButton(
    {
        width = 200,
        height = 30,
        shape = 'roundedRect',
        x = display.contentCenterX,
        y = display.contentCenterY - 50,
        label = 'Custom cursor 1',
        -- Set cursor using stored pointer
        onRelease = function() cursor.loadCursor(cursors.cursor1) end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

widget.newButton(
    {
        width = 200,
        height = 30,
        shape = 'roundedRect',
        x = display.contentCenterX,
        y = display.contentCenterY,
        label = 'Custom cursor 2',
        -- Set cursor using stored pointer
        onRelease = function() cursor.loadCursor(cursors.cursor2) end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

widget.newButton(
    {
        width = 200,
        height = 30,
        shape = 'roundedRect',
        x = display.contentCenterX,
        y = display.contentCenterY + 50,
        label = 'Custom cursor 3',
        -- Set cursor using stored pointer
        onRelease = function() cursor.loadCursor(cursors.cursor3) end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

widget.newButton(
    {
        width = 200,
        height = 30,
        shape = 'roundedRect',
        x = display.contentCenterX,
        y = display.contentCenterY + 100,
        label = 'Show/Hide cursor',
        onRelease = function()
            if hidden then
                cursor.showCursor()
            else
                cursor.hideCursor()
            end
            hidden = not hidden
        end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

widget.newButton(
    {
        width = 200,
        height = 30,
        shape = 'roundedRect',
        x = display.contentCenterX,
        y = display.contentCenterY + 150,
        label = 'Exit application',
        onRelease = function()
            -- Destroy all cursors before exiting
            for k, v in pairs(cursors) do
                cursor.destroyCursor(v)
                cursors[k] = nil
            end
            cursor.freePlugin()
            native.requestExit()
        end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

--[[
widget.newButton(
    {
        width = 200,
        height = 30,
        shape = 'roundedRect',
        x = display.contentCenterX,
        y = display.contentCenterY + 200,
        label = 'Destroy cursor 1',
        onRelease = function()
            cursor.destroyCursor(cursors.cursor1)
            cursors.cursor1 = nil
        end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

widget.newButton(
    {
        width = 200,
        height = 30,
        shape = 'roundedRect',
        x = display.contentCenterX,
        y = display.contentCenterY + 250,
        label = 'Destroy cursor 2',
        onRelease = function()
            cursor.destroyCursor(cursors.cursor2)
            cursors.cursor2 = nil
        end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

widget.newButton(
    {
        width = 200,
        height = 30,
        shape = 'roundedRect',
        x = display.contentCenterX,
        y = display.contentCenterY + 300,
        label = 'Destroy cursor 3',
        onRelease = function()
            cursor.destroyCursor(cursors.cursor3)
            cursors.cursor3 = nil
        end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)
]]--

Runtime:addEventListener('key',
    function(event)
        if event.phase == 'up' then
            if event.keyName == '1' then
                cursor.loadWinCursor(cursor.ARROW)
            elseif event.keyName == '2' then
                cursor.loadWinCursor(cursor.POINTER)
            elseif event.keyName == '3' then
                cursor.loadWinCursor(cursor.CROSSHAIR)
            elseif event.keyName == '4' then
                cursor.loadWinCursor(cursor.IBEAM)
            elseif event.keyName == '5' then
                cursor.loadWinCursor(cursor.NOTALLOWED)
            elseif event.keyName == '6' then
                cursor.loadWinCursor(cursor.RESIZE)
            elseif event.keyName == '7' then
                cursor.loadWinCursor(cursor.WAIT)
            elseif event.keyName == '8' then
                cursor.loadWinCursor(cursor.HELP)
            elseif event.keyName == '9' then
                cursor.loadWinCursor(cursor.BUSY)
            elseif event.keyName == '0' then
                cursor.loadWinCursor(cursor.RESIZENESW)
            elseif event.keyName == 'q' then
                cursor.loadWinCursor(cursor.RESIZENS)
            elseif event.keyName == 'w' then
                cursor.loadWinCursor(cursor.RESIZENWSE)
            elseif event.keyName == 'e' then
                cursor.loadWinCursor(cursor.RESIZEWE)
            elseif event.keyName == 'r' then
                cursor.loadWinCursor(cursor.UPARROW)
            end
        end
    end
)
