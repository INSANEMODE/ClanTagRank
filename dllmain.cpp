#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include "functions.h"
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <thread>



void init()
{
    
    std::cout << "ClanTagRank (1.0.2) by INSANEMODE\n";
    std::thread rank(Game::clanTagThread);
    rank.detach();
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
