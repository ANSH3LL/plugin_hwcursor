local widget = require('widget')
local cursor = require('plugin.hwcursor')

local hidden = false
cursor.initPlugin()

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
        onRelease = function() cursor.loadCursor(system.pathForFile('cursor1.cur')) end,
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
        onRelease = function() cursor.loadCursor(system.pathForFile('cursor2.ani')) end,
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
        y = display.contentCenterY + 100,
        label = 'Exit application',
        onRelease = function()
            cursor.resetCursor()
            cursor.freePlugin()
            native.requestExit()
        end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

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