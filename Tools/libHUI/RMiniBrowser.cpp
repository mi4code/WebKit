#include <windows.h>
#include <WebKit/WKBase.h>
#include <WebKit/WKContext.h>
#include <WebKit/WKPage.h>
#include <WebKit/WKView.h>
#include <WebKit/WKString.h>
#include <WebKit/WKURL.h>

#pragma comment(lib, "WebKit2.lib")

static WKPageRef g_page;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_SIZE: {
        // Resize the WebKit view when the window is resized.
        RECT rect;
        GetClientRect(hwnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        // Resize the WebKit view using the Win32 MoveWindow function
        if (g_page) {
            HWND viewHwnd = reinterpret_cast<HWND>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            MoveWindow(viewHwnd, 0, 0, width, height, TRUE);
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

HWND createMainWindow(HINSTANCE hInstance)
{
    const wchar_t* className = L"SimpleMiniBrowser";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;

    RegisterClass(&wc);

    return CreateWindowEx(0, className, L"WebKit MiniBrowser", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, nullptr, nullptr, hInstance, nullptr);
}

void loadURL(WKPageRef page, const char* url)
{
    WKURLRef wkURL = WKURLCreateWithUTF8CString(url);
    WKPageLoadURL(page, wkURL);
    WKRelease(wkURL); // Release after use
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    // Step 1: Create a window
    HWND hwnd = createMainWindow(hInstance);
    if (!hwnd)
        return 0;

    // Step 2: Initialize WebKit context and view
    WKContextRef context = WKContextCreate();
    WKPageConfigurationRef config = WKPageConfigurationCreate();
    
    WKPageConfigurationSetContext(config, context);
    
    // Create the WKView (WebKit View)
    WKViewRef webView = WKViewCreate(config);

    // Step 3: Attach the WKView to the window and set the WebKit page
    RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // Set the WebView's HWND to handle resizing
    HWND viewHwnd = reinterpret_cast<HWND>(webView);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(viewHwnd));
    MoveWindow(viewHwnd, 0, 0, width, height, TRUE);

    g_page = WKViewGetPage(webView);

    // Step 4: Load a default URL
    loadURL(g_page, "https://www.example.com");

    // Step 5: Message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up WebKit objects
    WKRelease(config);
    WKRelease(context);
    WKRelease(webView);

    return 0;
}
