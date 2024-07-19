#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND textfield, buttonTest;

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




