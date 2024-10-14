set(MiniBrowser_PRIVATE_INCLUDE_DIRECTORIES
    ${CMAKE_BINARY_DIR}
)

# Essential sources for the simplified MiniBrowser
set(MiniBrowser_SOURCES
    MiniBrowser.cpp          # The new simplified single C++ source file that integrates WebKit
)

# Keep essential definitions
set(MiniBrowser_PRIVATE_DEFINITIONS _UNICODE)

# Only required libraries for window handling and WebKit
set(MiniBrowser_PRIVATE_LIBRARIES
    comctl32
    shlwapi
    user32
)

# WebKit frameworks required for rendering pages
set(MiniBrowser_FRAMEWORKS
    JavaScriptCore
    WTF
    WebCore
    WebKit
)

# Generate the executable for the simplified browser
WEBKIT_EXECUTABLE_DECLARE(MiniBrowser)
WEBKIT_EXECUTABLE(MiniBrowser)

# Ensure the output is a Windows executable
set_target_properties(MiniBrowser PROPERTIES WIN32_EXECUTABLE ON)