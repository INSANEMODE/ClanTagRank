#include "pch.h"
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
#define GetCurrentDir _getcwd

namespace Game

{

    std::string configfile()
    {

        CSimpleIniA ini;

        std::string currentpath = std::filesystem::current_path().generic_string();
        std::string configfile = currentpath + (R"(/t6r/data/plugins/GetClanTag.ini)");
        SI_Error rc = ini.LoadFile(configfile.c_str());
        //SI_Error rc = ini.LoadFile("\\t6r\\data\\plugins\\GetClanTag.ini");
        if (rc < 0) 
        {
            ini.SetValue("Config", "URL", "127.0.0.1:1624");
            ini.SaveFile(configfile.c_str());
        };
        const char* pVal = ini.GetValue("Config", "URL", "http://127.0.0.1:1624");
        return pVal;
    }


    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
    std::string testcurl(unsigned int clientguid)
    {
        std::string guidstring = std::to_string(clientguid);
        //std::cout << "guid string: " + guidstring + '\n';
        CURL* curl;
        CURLcode res;
        std::string readBuffer;
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, configfile() + "/api/gsc/clientguid/" + guidstring);
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
    std::string ClanTagRequest(unsigned int clientguid)
    {
        std::string readBuffer;
        //const char* constClanTag;
        if (clientguid != 0)
        {
            readBuffer = testcurl(clientguid);
        }
        readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), '\n'), readBuffer.end());
        readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), '\r'), readBuffer.end());

        //readBuffer contains the rank that will be put into the clan tag of the client with the requested username
        return readBuffer;




    }
    void clanTagChanger()
    {

        
        unsigned int clientguid{};
        char emptyname[16]{};
        char currentname[16]{};
        std::string currentname_str;
        char currentClanTag[8]{};
        const char* changeClanTag{};
        std::string changeClanTag_str;



        int clientAddr{ 0x02347D10 - 0x57F8 };// check for client GUID instead of name
        int clientNameAddr{ 0x02347cd4 - 0x57F8 };
        int clanTagAddr{ 0x30 };
        int clientOffset{ 0x57F8 };

        //loop through clients to get their name and current clan tag.
        for (int i = 1; i < 9; i++)
        {
            memcpy(&clientguid, (void*)((clientAddr + (clientOffset * i))), 4);
            memcpy(&currentname, (void*)((clientNameAddr + (clientOffset * i))), 16);
            //currentname_str = std::string(currentname, 16);
            memcpy((void*)currentClanTag, (void*)(((clientAddr +(clientOffset * i)) + clanTagAddr)), 8);
            //std::cout << "guid uint: " + clientguid << '\n';
            
            //if ((strstr(currentClanTag, "Creator") == NULL) && (strstr(currentClanTag, "Admin") == NULL) && (strstr(currentClanTag, "SrAdmin") == NULL) && (strstr(currentClanTag, "Trusted") == NULL) && (strstr(currentClanTag, "Mod") == NULL) && (strstr(currentClanTag, "Owner") == NULL) && (strstr(currentClanTag, "3arc") == NULL) && (clientguid > 0) && (clientguid != NULL))
            if (!*currentClanTag && (clientguid > 0) && (clientguid != NULL))
            {
                changeClanTag_str = ClanTagRequest(clientguid);
                
                changeClanTag = changeClanTag_str.c_str();
                if ((strstr(currentClanTag, changeClanTag) == NULL) || (strstr(changeClanTag, "Error: Client info is null") == NULL))
                {
                    
                    if(!(changeClanTag_str.find("Error:") != std::string::npos)) //&& !(changeClanTag_str.find("User") != std::string::npos))
                    {
                        std::cout << "ClanTag Rank: [" + changeClanTag_str + "]" + currentname + '\n';
                        memcpy((void*)(clientAddr + (clientOffset * i) + clanTagAddr), changeClanTag, 8);

                    }

                }

            }

        }

    }

    void clanTagThread()
    {
        while (true)
        {
            configfile();
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            clanTagChanger();
        }

    }
}


