-- New in this version

-- Call cursor.loadCursor with the path to the cursor and store
-- the return value, which is a pointer to the cursor resource

-- Call cursor.setCursor and provide the pointer returned
-- by cursor.loadCursor to set the cursor for the window

local widget = require('widget')
local cursor = require('plugin.hwcursor')

cursor.initPlugin()

local visible = false

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
        fontSize = 20,
        align = 'center',
        font = native.systemFont,
        text = 'Hardware Cursor Plugin for Windows OS'
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
        label = 'Custom static cursor',
        onRelease = function() cursor.setCursor(cursors.cursor1) end,
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
        label = 'Custom animated cursor',
        onRelease = function() cursor.setCursor(cursors.cursor2) end,
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
        label = 'Custom huge cursor',
        onRelease = function() cursor.setCursor(cursors.cursor3) end,
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
            cursor.setVisibility(visible)
            visible = not visible
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
            -- Free the plugin before calling "native.requestExit()"
            cursor.freePlugin()
            native.requestExit()
        end,
        labelColor = { default = { 1, 1, 1 }, over = { 0, 0, 0, 0.5 } },
        fillColor = { default = { 1, 0.2, 0.5, 0.7 }, over = { 1, 0.2, 0.5, 1 } }
    }
)

Runtime:addEventListener('system',
    function(event)
        if event.type == 'applicationExit' then
            -- Free all cursor pointers before application exit (best practice)
            for k, v in pairs(cursors) do
                cursor.freeCursor(v)
                cursors[k] = nil
            end
        end
    end
)
