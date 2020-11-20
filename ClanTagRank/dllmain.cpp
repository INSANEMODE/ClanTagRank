#include "stdinc.hpp"
#include "utils/hook.hpp"
#include "utils/memory.hpp"
#include "utils/string.hpp"

utils::memory::allocator allocator;
std::string clantags[18];

int get_maxclients()
{
    if (strcmp(game::gamename.data(), "t6mp") == 0 || strcmp(game::gamename.data(), "t6zm") == 0)
    {
        return game::t6::Dvar_FindVar("sv_maxclients")->current.integer;
    }

    return game::iw5::Dvar_FindVar("sv_maxclients")->current.integer;
}

void set_clan_tag_(int clientNum, std::string clantag)
{
    clantags[clientNum] = clantag;
    game::ClientUserInfoChanged(clientNum);
    printf("setting clantag to %s for client %i\n", clantag.data(), clientNum);
}

void set_clan_tag()
{
    const auto client = game::Cmd_Argv(1);
    auto clantag = game::Cmd_Argv(2);

    const auto clientNum = atoi(client);
    auto sv_maxclients = get_maxclients();

    if (clientNum >= sv_maxclients)
    {
        return;
    }

    char clean_tag[8] = { 0 };
    strncpy_s(clean_tag, clantag, 7);
    game::I_CleanStr(clean_tag);

    set_clan_tag_(clientNum, std::string(clean_tag));
}

void set_clan_tag_raw()
{
    const auto client = game::Cmd_Argv(1);
    auto clantag = game::Cmd_Argv(2);

    const auto clientNum = atoi(client);
    auto sv_maxclients = get_maxclients();

    if (clientNum >= sv_maxclients)
    {
        return;
    }

    set_clan_tag_(clientNum, std::string(clantag));
}

void set_clan_tags()
{
    auto clantag = game::Cmd_Argv(1);
    auto sv_maxclients = get_maxclients();

    char clean_tag[8] = { 0 };
    strncpy_s(clean_tag, clantag, 7);
    game::I_CleanStr(clean_tag);

    for (auto i = 0; i < sv_maxclients; i++)
    {
        set_clan_tag_(i, std::string(clean_tag));
    }
}

void set_clan_tags_raw()
{
    auto clantag = game::Cmd_Argv(1);
    auto sv_maxclients = get_maxclients();

    for (auto i = 0; i < sv_maxclients; i++)
    {
        set_clan_tag_(i, std::string(clantag));
    }
}

game::Info_ValueForKey_t Info_ValueForKey_hook;
const char* Info_ValueForKey_stub(const char* s, const char* key)
{
    if (strcmp(key, "ec_usingTag") == 0)
    {
        return "1";
    }

    if (strcmp(key, "clanAbbrev") != 0 && strcmp(key, "ec_TagText") != 0 && strcmp(key, "clanAbbrevEv") != 0)
    {
        return Info_ValueForKey_hook(s, key);
    }

    const auto sv_maxclients = get_maxclients();

    for (auto i = 0; i < sv_maxclients; i++)
    {
        char buffer[2048];
        game::SV_GetUserInfo(i, buffer, 2048);

        if (!clantags[i].empty() && strcmp(s, buffer) == 0)
        {
            return clantags[i].data();
        }
    }

    return Info_ValueForKey_hook(s, key);
}

void init()
{
    Info_ValueForKey_hook = utils::hook::vp::detour(game::Info_ValueForKey, Info_ValueForKey_stub, 5);

    game::Cmd_AddCommandInternal("setclantag", set_clan_tag, allocator.allocate<game::cmd_function_t>());
    game::Cmd_AddCommandInternal("setclantagraw", set_clan_tag_raw, allocator.allocate<game::cmd_function_t>());
    game::Cmd_AddCommandInternal("setclantags", set_clan_tags, allocator.allocate<game::cmd_function_t>());
    game::Cmd_AddCommandInternal("setclantagsraw", set_clan_tags_raw, allocator.allocate<game::cmd_function_t>());
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        init();
        break;
    }
    return TRUE;
}