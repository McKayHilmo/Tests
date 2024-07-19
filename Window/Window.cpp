#include "Window.h"
#include <stdint.h>
#include <iostream>
#define u32 uint32_t

int width = 0, height = 0;
void* memory;
BITMAPINFO bitmap_info;
HDC hdc;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    
    RECT rect;
    GetClientRect(hWnd, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
    memory = VirtualAlloc(0,width * height * 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = width;
    bitmap_info.bmiHeader.biHeight = height;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;
    hdc = GetDC(hWnd);
    
    switch (uMsg)
    {
    case WM_CREATE:
        textfield = CreateWindowEx(
            0,
            L"STATIC",
            L"HELLO",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            50,
            60,
            50,
            20,
            hWnd,
            NULL,
            NULL,
            NULL);
        buttonTest = CreateWindowEx(
            0,
            L"BUTTON",
            L"Fill",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            50,
            85,
            50,
            20,
            hWnd,
            (HMENU) 1,
            NULL,
            NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 1:
            ::MessageBox(hWnd,L"Box",L"Button was clicked",0);
            break;
        
        default:
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;    
}

Window::Window()
    :m_hInstance(GetModuleHandle(nullptr))
{
    const wchar_t* CLASS_NAME = L"McKays Window Class";
    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    RegisterClass(&wndClass);

    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    int width = 640;
    int height = 480;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, style, false);

    m_hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Title",
        style,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        m_hInstance,
        NULL
    );

    ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
    const wchar_t* CLASS_NAME = L"McKays Window Class";

    UnregisterClass(CLASS_NAME, m_hInstance);
}


bool Window::ProcessMessages(){
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }
        

        TranslateMessage(&msg);
        //Dispatch calls WndowProc
        DispatchMessage(&msg);
    }

    return true;
    
} 

