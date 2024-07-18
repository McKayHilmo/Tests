#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include "Window.cpp"

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