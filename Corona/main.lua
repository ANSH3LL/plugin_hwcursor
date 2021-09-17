local widget = require('widget')
local cursor = require('plugin.hwcursor')

local hidden = false
cursor.initPlugin()

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
            timer.performWithDelay(500, function() native.requestExit() end)
        end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)