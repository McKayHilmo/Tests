#ifndef UNICODE 
#define UNICODE
#endif


#include <iostream>
#include <windows.h>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    
    
    switch (uMsg)
    {
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
class Window
{
private:
    HINSTANCE  m_hInstance;
    HWND m_hWnd;
public:
    Window();
    ~Window();
    bool ProcessMessages();
};

Window::Window()
    :m_hInstance(GetModuleHandle(nullptr))
{
    const wchar_t* CLASS_NAME = L"My Class";
    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    RegisterClass(&wndClass);

    DWORD style = WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX;

    m_hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Title",
        style,
        250,
        250,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
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




int main(){

    std::cout << "Creating Window...\n";

    Window* pWindow = new Window();

    bool running = true;

    while (running)
    {
        if(!pWindow->ProcessMessages()){

            std::cout << "Closing Window...\n";
            running = false;
        }
        //Render
        Sleep(10);
    }
    
    delete pWindow;

    return 0;
}