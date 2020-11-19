#pragma once
#include <Windows.h>



namespace Game
{

    void addCommands();

    struct cmd_function_t
    {
        cmd_function_t* next;
        const char* name;
        const char* autoCompleteDir;
        const char* autoCompleteExt;
        void(__cdecl* function)();
        int flags;
    };


    typedef void (*Cmd_AddCommand_t)(const char* cmdName, void (*function)(), cmd_function_t* allocedCmd);
    extern Cmd_AddCommand_t Cmd_AddCommand;

    typedef char* (*Cmd_Argv_t)(int arg);
}
