#include <windows.h>
//#include <WebKit/WebKit.h>
#include <WebKit/WKPage.h>
#include <WebKit/WKRetainPtr.h>
#include <WebKit/WKString.h>
#include <WebKit/WKContext.h>
#include <WebKit/WKView.h>

#pragma comment(lib, "WebKit.lib")

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
        if (g_page) {
            WKViewSetSize(g_page, width, height);
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
    WKRetainPtr<WKURLRef> wkURL(AdoptWK, WKURLCreateWithUTF8CString(url));
    WKPageLoadURL(page, wkURL.get());
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    // Step 1: Create a window
    HWND hwnd = createMainWindow(hInstance);
    if (!hwnd)
        return 0;

    // Step 2: Initialize WebKit context and view
    WKRetainPtr<WKContextRef> context(AdoptWK, WKContextCreate());
    WKRetainPtr<WKPageConfigurationRef> config(AdoptWK, WKPageConfigurationCreate());
    
    WKPageConfigurationSetContext(config.get(), context.get());
    
    WKRetainPtr<WKViewRef> webView(AdoptWK, WKViewCreate(config.get()));
    
    RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    
    WKViewSetSize(webView.get(), width, height);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(webView.get()));
    
    // Step 3: Create a WebKit page and load a default URL
    g_page = WKViewGetPage(webView.get());
    loadURL(g_page, "https://www.example.com");

    // Step 4: Message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
