# HwCursor
A hardware cursor plugin for the solar2D (formerly corona-sdk) game engine

# Usage
Refer to example project in ```Corona/``` directory

# Methods

- ```initPlugin``` - performs setup so the plugin can work as expected
- ```freePlugin``` - detaches the plugin (should be called when preparing to exit)
- ```loadCursor``` - loads a ```.cur``` or ```.ani``` cursor file and sets it as the cursor
- ```showCursor``` - shows the cursor if it was hidden
- ```hideCursor``` - hides the cursor if it was visible
- ```resetCursor``` - resets the cursor to the default arrow cursor
- ```destroyCursor``` - destroys the cursor handle and frees its memory
- ```loadWinCursor``` - loads the specified windows-provided cursor

# Valid arguments to loadWinCursor()

**Icon**|**Constant**|**Number**
:-----:|:-----:|:-----:
![arrow](docs/arrow.png)|ARROW|1
![pointer](docs/pointer.png)|POINTER|2
![crosshair](docs/crosshair.png)|CROSSHAIR|3
![ibeam](docs/ibeam.png)|IBEAM|4
![notallowed](docs/notallowed.png)|NOTALLOWED|5
![resize](docs/resize.png)|RESIZE|6
![wait](docs/wait.png)|WAIT|7
![help](docs/help.png)|HELP|8
![busy](docs/busy.png)|BUSY|9
![resizenesw](docs/resizenesw.png)|RESIZENESW|10
![resizens](docs/resizens.png)|RESIZENS|11
![resizenwse](docs/resizenwse.png)|RESIZENWSE|12
![resizewe](docs/resizewe.png)|RESIZEWE|13
![uparrow](docs/uparrow.png)|UPARROW|14

- Both ```loadWinCursor(plugin.POINTER)``` and ```loadWinCursor(2)``` are valid and will load the pointing hand cursor.

# Caveats
- Only supports windows for now
- Destroy preloaded cursors before exiting the application programmatically. Call ```plugin.destroyCursor(cursor)```.
- You must call ```plugin.freePlugin()``` while exiting the application programmatically. An example of how this should be done is provided.