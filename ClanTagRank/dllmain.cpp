#include "stdinc.hpp"

#include "utils/hook.hpp"
#include "utils/memory.hpp"
#include "utils/string.hpp"

#include "command/command.hpp"
#include "userinfo/userinfo.hpp"

utils::memory::allocator allocator;

std::string clantags[18];

std::string names[18];

void set_clan_tag(int clientNum, std::string clantag)
{
    clantags[clientNum] = clantag;
    game::ClientUserInfoChanged(clientNum);

    printf("setting clantag to %s for client %i\n", clantag.data(), clientNum);
}

const char* clantag_stub(const char* s, const char* key, const char* result, int clientNum)
{
    return clantags[clientNum].empty() ? result : clantags[clientNum].data();
}

const char* name_stub(const char* s, const char* key, const char* result, int clientNum)
{
    return names[clientNum].empty() ? result : names[clientNum].data();
}

const char* using_tag_stub(const char* s, const char* key, const char* result, int clientNum)
{
    return "1";
}

void init()
{
    userinfo::add("ec_TagText", clantag_stub);
    userinfo::add("clanAbbrev", clantag_stub);
    userinfo::add("clanAbbrevEv", clantag_stub);

    userinfo::add("name", name_stub);

    userinfo::add("ec_usingTag", using_tag_stub);

    command::add("setclantag", [](command::params& params)
    {
        const auto client = params.get(1);
        const auto clantag = params.get(2);

        const auto clientNum = atoi(client);
        const auto sv_maxclients = game::get_maxclients();

        if (clientNum >= sv_maxclients)
        {
            return;
        }

        char clean_tag[8] = { 0 };
        strncpy_s(clean_tag, clantag, 7);
        game::I_CleanStr(clean_tag);

        set_clan_tag(clientNum, clean_tag);
    });

    command::add("setclantags", [](command::params& params)
    {
        const auto clantag = params.get(1);

        char clean_tag[8] = { 0 };
        strncpy_s(clean_tag, clantag, 7);
        game::I_CleanStr(clean_tag);

        auto sv_maxclients = game::get_maxclients();

        for (auto i = 0; i < sv_maxclients; i++)
        {
            set_clan_tag(i, clean_tag);
        }
    });

    command::add("setclantagraw", [](command::params& params)
    {
        const auto client = params.get(1);
        auto clantag = params.get(2);

        const auto clientNum = atoi(client);
        auto sv_maxclients = game::get_maxclients();

        if (clientNum >= sv_maxclients)
        {
            return;
        }

        set_clan_tag(clientNum, clantag);
    });

    command::add("setclantagsraw", [](command::params& params)
    {
        const auto clantag = params.get(1);

        auto sv_maxclients = game::get_maxclients();

        for (auto i = 0; i < sv_maxclients; i++)
        {
            set_clan_tag(i, clantag);
        }
    });

    command::add("rename", [](command::params& params)
    {
        const auto client = params.get(1);
        const auto name = params.get(2);

        const auto clientNum = atoi(client);
        const auto sv_maxclients = game::get_maxclients();

        if (clientNum >= sv_maxclients)
        {
            return;
        }

        names[clientNum] = name;
        game::ClientUserInfoChanged(clientNum);

        printf("renamed client %i to %s\n", clientNum, name);
    });
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        userinfo::init();
        init();
        break;
    }
    return TRUE;
}