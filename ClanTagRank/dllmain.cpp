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

void set_clan_tag()
{
    const auto client = game::Cmd_Argv(1);
    auto clantag = game::Cmd_Argv(2);

    const auto clientNum = atoi(client);

    if (clientNum >= get_maxclients())
    {
        return;
    }

    char clean_tag[8] = { 0 };
    strncpy_s(clean_tag, clantag, 7);
    game::I_CleanStr(clean_tag);

    clantags[clientNum] = std::string(clean_tag);
    game::ClientUserInfoChanged(clientNum);

    printf("setting clantag to %s for client %i\n", clantags[clientNum].data(), clientNum);
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