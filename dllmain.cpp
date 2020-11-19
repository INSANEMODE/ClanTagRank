
#include <Windows.h>
#include <iostream>
#include <string>
#include "functions.h"
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <thread>
HMODULE LogHandle;



void init()
{
    
    std::cout << "ClanTagRank (1.3) by INSANEMODE\n";
    
    std::thread addcommands(Game::addCommands);
    addcommands.detach();
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        LogHandle = GetModuleHandle(NULL);
        init();
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
