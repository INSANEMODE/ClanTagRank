
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>
#include "curl\curl.h"
#include "simpleini.h"
#include <filesystem>
#include "utils/hook.hpp"
#include "utils/memory.hpp"
#include <functional>
#include "functions.h"

utils::memory::allocator allocator;

std::function<void(const std::string& code)> callback;

int clientAddr{ 0x02347D10 - 0x57F8 };// check for client GUID instead of name
int clientNameAddr{ 0x02347cd4 - 0x57F8 };
int clanTagAddr{ 0x30 };
int clientOffset{ 0x57F8 };

namespace Game

{
    static Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x004DC2A0);
    static Cmd_Argv_t Cmd_Argv = (Cmd_Argv_t)0x006B3D40;

    void clanTagChanger_guid(unsigned int guid, std::string rank)
    {
       

        unsigned int clientguid{};
        const char* changeClanTag{};

        //loop through clients to get their guid
        for (int i = 1; i < 9; i++)
        {
            memcpy(&clientguid, (void*)((clientAddr + (clientOffset * i))), 4);
            if (clientguid == guid)
            {

                changeClanTag = rank.c_str();
                memcpy((void*)(clientAddr + (clientOffset * i) + clanTagAddr), changeClanTag, 8);


            }

        }

    }
    //
    void clanTagChanger_slot(int slot, std::string rank)
    {

        const char* changeClanTag{rank.c_str()};
        slot += 1;
        //loop through clients to get their guid
        memcpy((void*)(clientAddr + (clientOffset * slot) + clanTagAddr), changeClanTag, 8);
    }

    void setrank_guid()
    {
        std::string::size_type sz;   // alias of size_t
        unsigned int guid = std::stoi(Cmd_Argv(1), &sz);
        clanTagChanger_guid(guid, Cmd_Argv(2));

    }
    void setrank()
    {
        std::string::size_type sz;   // alias of size_t
        int client_slot = std::stoi(Cmd_Argv(1), &sz);
        clanTagChanger_slot(client_slot, Cmd_Argv(2));

    }
    void addCommands()
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(15000));
        const auto cmd_function = allocator.allocate<cmd_function_t>();
        const auto cmd_function_2 = allocator.allocate<cmd_function_t>();

        Cmd_AddCommand("setrank", setrank, cmd_function);
        Cmd_AddCommand("setrank_guid", setrank_guid, cmd_function_2);
        //Cmd_AddCommand("commandtest", commandtest);
    }

}


