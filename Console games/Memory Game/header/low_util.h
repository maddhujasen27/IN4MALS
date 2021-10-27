#pragma once

#ifdef _WIN32
	#include<windows.h>
#elif unix
	#include<unistd.h>
#endif

namespace lutil{
    void clearScreen()
    {
        #ifdef _WIN32
            system("CLS");
        #elif unix
            system("clear");
        #endif
    }

    void delay(float time)
    {
        #ifdef _WIN32
            Sleep(time);
        #elif unix
            usleep(time * 1000);
        #endif
    }
}