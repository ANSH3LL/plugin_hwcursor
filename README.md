# HwCursor
A hardware cursor plugin for the solar2D (formerly corona-sdk) game engine

# Usage
Refer to example project in ```Corona/``` directory

# Caveats
- Only supports windows for now
- You must call ```cursor.freePlugin()``` some moments before allowing the application to exit. This is to stop the application from crashing as it exits. An example of how this can be done is provided.