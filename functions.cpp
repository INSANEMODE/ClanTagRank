#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include "curl\curl.h"

namespace Game

{


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
        const char* constClanTag;
        if (username.length() >= 3)
        {
            readBuffer = testcurl(username);
        }
        readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), '\n'), readBuffer.end());
        readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), '\r'), readBuffer.end());

        //readBuffer contains the rank that will be put into the clan tag of the client with the requested username
        return readBuffer;




    }
    void clanTagChanger()
    {


        char emptyname[16]{};
        char currentname[16]{};
        std::string currentname_str;
        char currentClanTag[8]{};
        const char* changeClanTag{};
        std::string changeClanTag_str;



        int clientAddr{ 0x02347CD4 - 0x57F8 };
        int clanTagAddr{ 0x6C };
        int clientOffset{ 0x57F8 };
        int client{ (clientAddr + clientOffset) };
        for (int i = 1; i < 9; i++)
        {
            memcpy((void*)currentname, (void*)(client * i), 16);
            currentname_str = std::string(currentname, 16);
            memcpy((void*)currentClanTag, (void*)((client * i) + clanTagAddr), 8);
            if ((strstr(currentClanTag, "Creator") == NULL) && (strstr(currentClanTag, "Admin") == NULL) && (strstr(currentClanTag, "Trusted") == NULL) && (strstr(currentClanTag, "Mod") == NULL) && (strstr(currentClanTag, "Owner") == NULL) && (strstr(currentClanTag, "3arc") == NULL) && (strncmp(currentname, emptyname, 16) != 0))
            {
                changeClanTag_str = ClanTagRequest(currentname);
                
                changeClanTag = changeClanTag_str.c_str();
                if ((strstr(currentClanTag, changeClanTag) == NULL) || (strstr(changeClanTag, "Error: Client info is null") == NULL))
                {
                    std::cout << "ClanTag Rank: [" + changeClanTag_str + "]" + currentname + '\n';
                    if(!(changeClanTag_str.find("Error:") != std::string::npos) && !(changeClanTag_str.find("User") != std::string::npos))
                    {
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
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            clanTagChanger();
        }

    }
}


