set(HMiniBrowser_PRIVATE_INCLUDE_DIRECTORIES
    ${CMAKE_BINARY_DIR}
)

set(HMiniBrowser_SOURCES
    BrowserWindow.cpp
    Common.cpp
    Common2.cpp
    MainWindow.cpp
#    MiniBrowser.exe.manifest
    MiniBrowserLib.rc
    WebKitBrowserWindow.cpp
    WinMain.cpp
#    stdafx.cpp
)

set(HMiniBrowser_PRIVATE_DEFINITIONS _UNICODE)
set(HMiniBrowser_PRIVATE_LIBRARIES
    comctl32
    shlwapi
    user32
)
set(HMiniBrowser_FRAMEWORKS
    JavaScriptCore
    PAL
    WTF
    WebCore
    WebKit
)

add_library(HMiniBrowserInjectedBundle SHARED
    Common2.cpp
    InjectedBundle.cpp
)
target_link_libraries(HMiniBrowserInjectedBundle WebKit::WebKit)
target_include_directories(HMiniBrowserInjectedBundle PRIVATE ${CMAKE_BINARY_DIR})

WEBKIT_EXECUTABLE_DECLARE(HMiniBrowser)
WEBKIT_EXECUTABLE(HMiniBrowser)

set_target_properties(HMiniBrowser PROPERTIES WIN32_EXECUTABLE ON)
