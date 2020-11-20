#include "stdinc.hpp"
#include "utils/hook.hpp"
#include "utils/memory.hpp"
#include "utils/string.hpp"

utils::memory::allocator allocator;
const char* clantags[18];

void set_clan_tag()
{
    const auto client = game::Cmd_Argv(1);
    auto clantag = game::Cmd_Argv(2);

    char clean_tag[8] = { 0 };
    strncpy_s(clean_tag, clantag, 7);
    game::I_CleanStr(clean_tag);

    const auto clientNum = atoi(client);

    if (!clantag || !game::g_entities[clientNum].client)
    {
        return;
    }
    
    printf("setting clantag to %s for client %i\n", clean_tag, clientNum);

    clantags[clientNum] = clean_tag;
    memcpy((void*)(game::g_entities[clientNum].client->sess.cs.clanAbbrev), clean_tag, 8);
}

game::Info_ValueForKey_t Info_ValueForKey_hook;
const char* Info_ValueForKey_stub(const char* s, const char* key)
{
    if (strcmp(key, "clanAbbrev") == 0 || strcmp(key, "clanAbbrevEv") == 0)
    {
        const auto user_info = utils::string::split(s, 92);
        auto client = atoi(user_info[user_info.size() - 3].data());

        if (client > 0 && client < 18 && clantags[client] != NULL)
        {
            return clantags[client];
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