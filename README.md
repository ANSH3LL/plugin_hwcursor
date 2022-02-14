# HwCursor
A hardware cursor plugin for the solar2D (formerly corona-sdk) game engine

# Usage
Refer to example project in ```Corona/``` directory

# Methods
- ```initPlugin``` - performs setup so the plugin can work as expected
- ```freePlugin``` - detaches the plugin (should be called when preparing to exit programmatically)
- ```loadCursor``` - loads a ```.cur``` or ```.ani``` cursor file and returns a pointer to it
- ```freeCursor``` - frees a cursor pointer returned by ```loadCursor```
- ```setCursor``` - sets a pointer returned by ```loadCursor``` as the cursor
- ```resetCursor``` - resets the cursor to the default arrow cursor provided by windows
- ```setVisibility``` - shows or hides the cursor depending on the value given (true/false)

# Changes since v0.5
- ```loadWinCursor``` has been removed as it is redundant. To set one of the cursors provided by windows or macOS, take a look [here](https://docs.coronalabs.com/api/library/native/setProperty.html).
- ```loadCursor``` no longer sets the cursor, but only serves to load it and return a pointer. To set a loaded cursor, use ```setCursor```.
- ```destroyCursor``` has been renamed to ```freeCursor```
- ```showCursor``` and ```hideCursor``` have been replaced with ```setVisibility``` to allow you more agency in how you hide and show the cursor. ```setVisibility``` is a wrapper around [ShowCursor](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showcursor).
- Stability improvements; the plugin will no longer cause the simulator to crash on exit.

# Caveats
- Only supports windows for now