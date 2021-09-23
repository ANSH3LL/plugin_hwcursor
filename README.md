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

# Caveats
- Only supports windows for now
- You must call ```cursor.freePlugin()``` while exiting the application programmatically. An example of how this should be done is provided.