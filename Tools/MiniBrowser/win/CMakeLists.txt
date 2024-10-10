set(MiniBrowser_PRIVATE_INCLUDE_DIRECTORIES
    ${CMAKE_BINARY_DIR}
)

set(MiniBrowser_SOURCES
    WinMain.cpp
)

set(MiniBrowser_PRIVATE_DEFINITIONS _UNICODE)
set(MiniBrowser_PRIVATE_LIBRARIES
    comctl32
    shlwapi
    user32
)
set(MiniBrowser_FRAMEWORKS
    JavaScriptCore
    PAL
    WTF
    WebCore
    WebKit
)

add_library(MiniBrowserInjectedBundle SHARED
    InjectedBundle.cpp
)
target_link_libraries(MiniBrowserInjectedBundle WebKit::WebKit)
target_include_directories(MiniBrowserInjectedBundle PRIVATE ${CMAKE_BINARY_DIR})

WEBKIT_EXECUTABLE_DECLARE(MiniBrowser)
WEBKIT_EXECUTABLE(MiniBrowser)

set_target_properties(MiniBrowser PROPERTIES)
