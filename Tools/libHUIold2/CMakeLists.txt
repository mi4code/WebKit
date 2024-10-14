set(HUItest_PRIVATE_INCLUDE_DIRECTORIES
    ${CMAKE_BINARY_DIR}
)

set(HUItest_SOURCES
    BrowserWindow.cpp
    Common.cpp
#    Common2.cpp
    MainWindow.cpp
#    MiniBrowser.exe.manifest
    MiniBrowserLib.rc
    WebKitBrowserWindow.cpp
    WinMain.cpp
#    stdafx.cpp
)

set(HUItest_PRIVATE_DEFINITIONS _UNICODE)
set(HUItest_PRIVATE_LIBRARIES
    comctl32
    shlwapi
    user32
)
set(HUItest_FRAMEWORKS
    JavaScriptCore
    PAL
    WTF
    WebCore
    WebKit
)

add_library(HUItestInjectedBundle SHARED
#    Common2.cpp
    InjectedBundle.cpp
)
target_link_libraries(HUItestInjectedBundle WebKit::WebKit)
target_include_directories(HUItestInjectedBundle PRIVATE ${CMAKE_BINARY_DIR})

WEBKIT_EXECUTABLE_DECLARE(HUItest)
WEBKIT_EXECUTABLE(HUItest)

#set_target_properties(HUItest PROPERTIES WIN32_EXECUTABLE ON)
