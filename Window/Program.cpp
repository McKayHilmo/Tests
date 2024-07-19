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
        StretchDIBits(hdc,0,0,width,height,0,0,width,height,memory,&bitmap_info,DIB_RGB_COLORS,SRCCOPY);
        Sleep(10);
    }
    
    delete pWindow;

    return 0;
}