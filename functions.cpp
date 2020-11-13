#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "Header.h"
#include "Dvar.h"
#include <unordered_set>
#include <sstream>
#include <algorithm>

//#include "curl\curl.h"
#include "curl\curl.h"

namespace Game

{
    Com_Printf_t Com_Printf = Com_Printf_t(0x006013A0);
    SV_GameSendServerCommand_t SV_GameSendServerCommand = SV_GameSendServerCommand_t(0x0040D450);
    killserver_t killserver = (killserver_t)(0x00891750);//00A6DA16
    Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x006B9D20);

    //    void Scr_iPrintLn(int clientNum, const std::string& message)
    //    {
    //        //SV_GameSendServerCommand(clientNum, 0, Game::VA("%c \"%s\"", 0x66, message.data()));
    //        SV_GameSendServerCommand(0, 0, "c \"^1Hello there!\"");
    //    }

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
    std::string testcurl(std::string clientname)
    {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;
        //std::cout << clientname << '\n';
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:1624/api/gsc/clientname/" + clientname);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            /* example.com is redirected, so we tell libcurl to follow redirection */
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            /* Perform the request, res will get the return code */
            res = curl_easy_perform(curl);
            
            /* Check for errors */
            if (res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

            /* always cleanup */
            curl_easy_cleanup(curl);
            
        }
        return readBuffer;
    }
    std::string ClanTagRequest(std::string username)
    {
        std::string readBuffer;
        //std::string clantag;
        const char* constClanTag;
        if (username.length() >= 3)
        {
            readBuffer = testcurl(username);
            //std::cout << readBuffer << '\n';
            ////std::string line = "GeeksForGeeks is a must try";

            //// Vector of string to save tokens 
            //std::vector <std::string> tokens;

            //// stringstream class check1 
            //std::stringstream check1(readBuffer);

            //std::string intermediate;

            //// Tokenizing w.r.t. space ' ' 
            //while (std::getline(check1, intermediate, ' '))
            //{
            //    tokens.push_back(intermediate);
            //}

            //// Printing the token vector 
            //for (int i = 0; i < tokens.size(); i++)
            //    std::cout << tokens[i] << '\n';
        }
        //std::unordered_set<std::string> allowedValues = { "Admin","Owner","Mod","Trusted","Creator" };
        //std::unordered_set<std::string>::const_iterator index = allowedValues.find(readBuffer);
        //constClanTag = readBuffer.c_str();
        readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), '\n'), readBuffer.end());
        readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), '\r'), readBuffer.end());
        return readBuffer;
        //if (index != allowedValues.end() && readBuffer != "Error:client info is null")
        //{
        //    constClanTag = readBuffer.c_str();
        //    return constClanTag;
        //}

        //else
        //    return "";
        //if (username == "INSANEMODE")
        //    return "Creator";
        //else if (username == "jmc" || username == "JezuzLizard")
        //    return "Admin";
        //else if (username == "yeah" || username == "zTitan")
        //    return "Trusted";



    }
    void clanTagChanger()
    {

        //char changename[] = "^1INSANEMODE";
        char previousname[16]{};
        char currentname[16]{};
        std::string currentname_str;
        char currentClanTag[8]{};
        //char Creator[8]{"Creator"};
        //char Admin[8]{"Admin"};
        //char treyarc[8]{"3arc"};
        //char Trusted[8]{"Trusted"};
        //char Owner[8]{"Owner"};
        //char Mod[8]{ "Mod" };
        char emptychar[8]{ "" };
        const char* changeClanTag{};
        std::string changeClanTag_str;
        std::string clantag_str;
        //std::unordered_set<std::string> allowedValues = { "Admin","Owner","Mod","Trusted","Creator","Sr.Admin" };
       
        //if (index == allowedValues.end())


        int clientaddr = 0x02347CD4 - 0x57F8;
        int clantagaddr = 0x6C;
        int clientoffset = 0x57F8;

        for (int i = 1; i < 9; i++)
        {
            memcpy((void*)currentname, (void*)(clientaddr + (clientoffset * i)), 16);
            currentname_str = std::string(currentname, 16);
            //std::cout << "current name: " << currentname << '\n';
            memcpy((void*)currentClanTag, (void*)(clientaddr + (clientoffset * i) + clantagaddr), 8);//sizeof((void*)0x02347CD4));
            //std::cout << "current clan tag: " << currentClanTag << '\n';
            clantag_str = std::string(currentClanTag, 8);
            //std::cout << "clantag_str: " << clantag_str << '\n';
            //std::unordered_set<std::string>::const_iterator index = allowedValues.find(currentClanTag);
            if ((strstr(currentClanTag, "Creator") == NULL) && (strstr(currentClanTag, "Admin") == NULL) && (strstr(currentClanTag, "Trusted") == NULL) && (strstr(currentClanTag, "Mod") == NULL) && (strstr(currentClanTag, "Owner") == NULL) && (strstr(currentClanTag, "3arc") == NULL) && (strncmp(currentname, previousname, 16) != 0))
            {
                changeClanTag_str = ClanTagRequest(currentname);
                
                changeClanTag = changeClanTag_str.c_str();
                if ((strstr(currentClanTag, changeClanTag) == NULL) || (strstr(changeClanTag, "Error: Client info is null") == NULL))//!(changeClanTag_str.find("Error:") != std::string::npos))
                {
                    //std::cout << "changeClanTag: " << changeClanTag << '\n';
                    std::cout << "ClanTag Rank: [" + changeClanTag_str + "]" + currentname + '\n';
                    //std::cout << "changeClanTag: " << changeClanTag << '\n';
                    if(!(changeClanTag_str.find("Error:") != std::string::npos) && !(changeClanTag_str.find("User") != std::string::npos))
                    {
                        memcpy((void*)(clientaddr + (clientoffset * i) + clantagaddr), changeClanTag, 8);

                    }

                }

            }

        }


        //std::cout << "previous name: " << previousname << '\n';
        //memcpy((void*)changename, (void*)0x02347CD4, sizeof(changename));

        //memcpy((void*)0x02347CD4, (void*)currentname, sizeof(currentname));
        //std::cout << "current name: " << currentname << '\n';
        //*(std::string*)0x02347CD4 = "^1INSANEMODE";
        //testname = *(std::string*)0x02347CD4;
       // std::cout << "current name: " << testname << '\n';
        //std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
    void Testprint()
    {
        while (true)
        {
            if (GetAsyncKeyState(VK_NUMPAD1) & 1)
            {

                std::cout << "iprintln sent " << '\n'; // print if its on or off

                //Com_Printf(0, "^3test write'\n");
//				Scr_iPrintLn(0, "test");        
                SV_GameSendServerCommand(0, 0, "O \"bo2plugin_test: ^1Hello World^7 \"");
            }
            else if (GetAsyncKeyState(VK_NUMPAD2) & 1)
            {

                std::cout << "Kill server " << '\n'; // print if its on or off

                //Com_Printf(0, "^3test write'\n");
//				Scr_iPrintLn(0, "test");        killserver = (killserver_t)(DWORD)(0x00891750);//00A6DA16
                killserver(NULL);
            }
            else if (GetAsyncKeyState(VK_NUMPAD3) & 1)
            {

                std::cout << "fast_restart" << '\n'; // print if its on or off

                //Com_Printf(0, "^3test write'\n");
//				Scr_iPrintLn(0, "test");        killserver = (killserver_t)(DWORD)(0x00891750);//00A6DA16
                Cbuf_AddText(0, "fast_restart");
            }
            else if (GetAsyncKeyState(VK_NUMPAD4) & 1)
            {

                std::cout << "setting sv_maxclients to 18" << '\n'; // print if its on or off*(BYTE*)0x627049 = 0xE9

                //Com_Printf(0, "^3test write'\n");
//				Scr_iPrintLn(0, "test");        killserver = (killserver_t)(DWORD)(0x00891750);//00A6DA16  02347CD4
                *(BYTE*)0x029F00E0 = 0x12;
                *(BYTE*)0x029F00F0 = 0x12;
                Cbuf_AddText(0, "get sv_maxclients");
            }
            else if (GetAsyncKeyState(VK_NUMPAD5) & 1)
            {

                std::cout << "setting sv_maxclients to 4" << '\n'; // print if its on or off*(BYTE*)0x627049 = 0xE9

                //Com_Printf(0, "^3test write'\n");
//				Scr_iPrintLn(0, "test");        killserver = (killserver_t)(DWORD)(0x00891750);//00A6DA16
                *(BYTE*)0x029F00E0 = 0x04;
                *(BYTE*)0x029F00F0 = 0x04;
            }
            else if (GetAsyncKeyState(VK_NUMPAD6) & 1)
            {

                //std::cout << "setting sv_maxclients to 4" << '\n'; // print if its on or off*(BYTE*)0x627049 = 0xE9

                //Com_Printf(0, "^3test write'\n");
//				Scr_iPrintLn(0, "test");        killserver = (killserver_t)(DWORD)(0x00891750);//00A6DA16
                //std::string testname = *(BYTE*)0x02347CD4;
                //std::cout << "previous name: " << testname << '\n';

                char changename[]{ "^1INSANEMODE" };
                char previousname[16]{};
                char currentname[16]{};
                char currentClanTag[8]{};


                memcpy((void*)previousname, (void*)0x02347CD4, 16);
                std::cout << "previous name: " << previousname << '\n';

                memcpy((void*)0x02347CD4, (void*)changename, sizeof(changename));
                memcpy((void*)currentname, (void*)0x02347CD4, 16);//sizeof((void*)0x02347CD4));
                std::cout << "current name: " << previousname << '\n';
                //std::cout << "previous name: " << previousname << '\n';
                //memcpy((void*)changename, (void*)0x02347CD4, sizeof(changename));

                //memcpy((void*)0x02347CD4, (void*)currentname, sizeof(currentname));
                //std::cout << "current name: " << currentname << '\n';
                //*(std::string*)0x02347CD4 = "^1INSANEMODE";
                //testname = *(std::string*)0x02347CD4;
               // std::cout << "current name: " << testname << '\n';
            }
            else if (GetAsyncKeyState(VK_NUMPAD7) & 1)
            {

                dvar_s* iw4madmin_admins = Dvar_RegisterString("iw4madmin_admins", "none", 0x0001, "contains admins for server, seperated by ;"); //(const char* dvarName, const char* value, unsigned __int16 flags, const char* description);
                char dvarstringtest[]{ "test" };
                iw4madmin_admins->current.string = dvarstringtest;
            }
            //else if (GetAsyncKeyState(VK_NUMPAD8) & 1) {

            //    //std::string mapname = Dvar_GetString("mapname");
            //    const char* hostname_char = Dvar_GetString(0x00574D85);
            //    //std::string&& hostname = hostname_char.c_str();
            //    //char dvarstringtest[] = "test";
            //    //mapname->current.string;
            //    //SetConsoleOutputCP(65001);
            //    //std::cout << hostname_char << '\n';
            //    char hostname[16] = {};
            //    //memcpy((void*)hostname, (void*)hostname_char, sizeof((void*)hostname_char));
            //    std::cout << "host name: " << hostname_char << '\n';

            //}
            else if (GetAsyncKeyState(VK_NUMPAD8) & 1)
            {
                clanTagChanger();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    void clanTagThread()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            clanTagChanger();
        }

    }
}

//void clanTagChanger()
//{
//    while (true)
//    {
//        //char changename[] = "^1INSANEMODE";
//        char previousname[16] = {};
//        char currentname[16] = {};
//        char currentClanTag[8] = {};
//        const char* changeClanTag;
//        std::unordered_set<std::string> allowedValues = { "Admin","Owner","Mod","Trusted","Creator","Sr.Admin" };
//        //std::unordered_set<char>::const_iterator index = allowedValues.find(input);
//        //if (index == allowedValues.end())
//
//        memcpy((void*)currentname, (void*)0x02347CD4, 16);
//        std::cout << "current name: " << currentname << '\n';
//
//
//        memcpy((void*)currentClanTag, (void*)0x0234D4CC, 8);//sizeof((void*)0x02347CD4));
//        std::cout << "current clan tag: " << currentClanTag << '\n';
//        changeClanTag = ClanTagRequest(currentname).c_str();
//        memcpy((void*)0x0234D4CC, changeClanTag, sizeof(changeClanTag));
//
//        //std::cout << "previous name: " << previousname << '\n';
//        //memcpy((void*)changename, (void*)0x02347CD4, sizeof(changename));
//
//        //memcpy((void*)0x02347CD4, (void*)currentname, sizeof(currentname));
//        //std::cout << "current name: " << currentname << '\n';
//        //*(std::string*)0x02347CD4 = "^1INSANEMODE";
//        //testname = *(std::string*)0x02347CD4;
//        // std::cout << "current name: " << testname << '\n';
//        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
//    }
//
//}


