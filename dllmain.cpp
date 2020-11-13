#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include "dllmain.h"
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <thread>



void init()
{
    
    std::cout << "ClanTagRank (1.0) by INSANEMODE";
    //std::cout << LogHandle << std::endl;
    //std::cout << pcod_printf << std::endl;
    //Game::Com_Printf(0, "^3test write'\n");
    //std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    //pG_LogPrintf(ch, ch[4]);
    //void (*pkillserver)();
    //pkillserver(NULL); clanTagThread()
    //std::thread first(Game::Testprint);
    //first.detach();
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
        
        //LogHandle = GetModuleHandle(TEXT("plutonium-bootstrapper-win32.exe"));
        LogHandle = GetModuleHandle(NULL);
        //pG_LogPrintf = (G_LogPrintf)(DWORD)(0x44ACE0);
        //pcod_printf = (cod_printf)(DWORD)(0xA6DA16);//00A6DA16

        

        init();
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
