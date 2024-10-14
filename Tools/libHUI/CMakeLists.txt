set(RMiniBrowser_PRIVATE_INCLUDE_DIRECTORIES
    ${CMAKE_BINARY_DIR}
)

# Essential sources for the simplified MiniBrowser
set(RMiniBrowser_SOURCES
    RMiniBrowser.cpp          # The new simplified single C++ source file that integrates WebKit
)

# Keep essential definitions
set(RMiniBrowser_PRIVATE_DEFINITIONS _UNICODE)

# Only required libraries for window handling and WebKit
set(RMiniBrowser_PRIVATE_LIBRARIES
    comctl32
    shlwapi
    user32
)

# WebKit frameworks required for rendering pages
set(RMiniBrowser_FRAMEWORKS
    JavaScriptCore
    WTF
    WebCore
    WebKit
)

# Generate the executable for the simplified browser
WEBKIT_EXECUTABLE_DECLARE(RMiniBrowser)
WEBKIT_EXECUTABLE(RMiniBrowser)

# Ensure the output is a Windows executable
set_target_properties(RMiniBrowser PROPERTIES WIN32_EXECUTABLE ON)