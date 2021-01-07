#include "stdinc.hpp"

std::string clantags[18];
std::string names[18];
std::string auth[18];
std::string get_auth_level(int clientNum)
{
    return auth[clientNum].empty() ? "0" : auth[clientNum].data();
}
void set_auth_level(int clientNum, std::string auth_level)
{
    auth[clientNum] = auth_level;
    //game::ClientUserInfoChanged(clientNum);

    printf("setting auth_level to %s for client %i\n", auth_level.c_str(), clientNum);
}
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
    chat::add("!test", [](int clientNum, command::params_sv& params, std::function<void()> next)
    {
        
        if ( std::stoi(get_auth_level(clientNum)) > 1)
        {
            int v1 = rand() % 100;
            chat::tellraw(clientNum, "test " + std::to_string(v1));
        }
        else
        {
            chat::tellraw(clientNum, "You don't have permission to perform this command");
        }
    });

    userinfo::add("ec_TagText", clantag_stub);
    userinfo::add("clanAbbrev", clantag_stub);
    userinfo::add("clanAbbrevEv", clantag_stub);

    userinfo::add("name", name_stub);


    userinfo::add("ec_usingTag", using_tag_stub);

    command::add("tellraw", [](command::params& params)
    {
        if (params.size() < 3)
        {
            return;
        }

        const auto client = atoi(params.get(1));
        const auto message = params.join(2);

        game::SV_GameSendServerCommand(client, 0, utils::string::va("%c \"%s\"", 
            SELECT_VALUE(106, 106, 84), message.data()));

        printf("tell %i -> %s\n", client, message.data());
    });

    command::add("sayraw", [](command::params& params)
    {
        if (params.size() < 2)
        {
            return;
        }

        const auto message = params.join(1);

        game::SV_GameSendServerCommand(-1, 0, utils::string::va("%c \"%s\"", 
            SELECT_VALUE(106, 106, 84), message.data()));

        printf("say -> %s\n", message.data());
    });

    command::add("clientprint", [](command::params& params)
    {
        if (params.size() < 3)
        {
            return;
        }

        const auto client = atoi(params.get(1));
        const auto message = params.join(2);

        game::SV_GameSendServerCommand(client, 0, utils::string::va("%c \"%s\"",
            SELECT_VALUE(59, 59, 102), message.data()));

        printf("print %i -> %s\n", client, message.data());
    });

    command::add("allclientsprint", [](command::params& params)
    {
        if (params.size() < 2)
        {
            return;
        }

        const auto message = params.join(1);

        game::SV_GameSendServerCommand(-1, 0, utils::string::va("%c \"%s\"",
            SELECT_VALUE(59, 59, 102), message.data()));

        printf("print -> %s\n", message.data());
    });

    command::add("clientprintbold", [](command::params& params)
    {
        if (params.size() < 3)
        {
            return;
        }

        const auto client = atoi(params.get(1));
        const auto message = params.join(2);

        game::SV_GameSendServerCommand(client, 0, utils::string::va("%c \"%s\"", 
            SELECT_VALUE(60, 60, 99), message.data()));

        printf("printbold %i -> %s\n", client, message.data());
    });

    command::add("allclientsprintbold", [](command::params& params)
    {
        if (params.size() < 2)
        {
            return;
        }

        const auto message = params.join(1);

        game::SV_GameSendServerCommand(-1, 0, utils::string::va("%c \"%s\"", 
            SELECT_VALUE(60, 60, 99), message.data()));

        printf("printbold -> %s\n", message.data());
    });

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

    function::add("renameclient", 2, 2, []()
    {
        const auto client = game::Scr_GetInt(game::SCRIPTINSTANCE_SERVER, 0);
        const auto name = game::Scr_GetString(game::SCRIPTINSTANCE_SERVER, 1);

        const auto clientNum = client;
        const auto sv_maxclients = game::get_maxclients();

        if (clientNum >= sv_maxclients)
        {
            return;
        }

        names[clientNum] = name;
        game::ClientUserInfoChanged(clientNum);

        printf("renamed client %i to %s\n", clientNum, name);
    });

    function::add("cbuf_addtext", 2, 2, []()
    {
        const auto client = game::Scr_GetInt(game::SCRIPTINSTANCE_SERVER, 0);
        const auto command = game::Scr_GetString(game::SCRIPTINSTANCE_SERVER, 1);

        const auto clientNum = client;
        const auto sv_maxclients = game::get_maxclients();

        if (clientNum >= sv_maxclients)
        {
            return;
        }
        game::Cbuf_AddText(clientNum, command);
    });

    command::add("authenticate", [](command::params& params)
    {
        const auto client = params.get(1);
        auto auth = params.get(2);

        const auto clientNum = atoi(client);
        auto sv_maxclients = game::get_maxclients();

        if (clientNum >= sv_maxclients)
        {
            return;
        }

        set_auth_level(clientNum, auth);
    });
}

DLL_EXPORT void on_initialize_context(const char* script, chaiscript::ChaiScript* chai) { }

DLL_EXPORT void on_script_loaded(const char* script, chaiscript::ChaiScript* chai) { }

DLL_EXPORT void on_script_unloaded(const char* script, chaiscript::ChaiScript* chai) { }

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        command::init();
        chat::init();
        userinfo::init();

        game::init();

        gsc::setup();

        init();
        break;
    }
    return TRUE;
}