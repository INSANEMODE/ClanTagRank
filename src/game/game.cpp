#include "stdinc.hpp"

namespace
{
	LPSTR cmdString = GetCommandLineA();

	std::string get_gamename()
	{
		const char* delim = " ";
		char* context = NULL;

		char* token = strtok_s(cmdString, delim, &context);
		token = strtok_s(NULL, delim, &context);

		return std::string(token);
	}
}

namespace game
{
	std::string gamename = get_gamename();

	bool is_t6mp()
	{
		return strcmp(gamename.data(), "t6mp") == 0;
	}

	bool is_t6zm()
	{
		return strcmp(gamename.data(), "t6zm") == 0;
	}

	bool is_iw5()
	{
		return strcmp(gamename.data(), "iw5mp") == 0;
	}

	std::string get_dvar_string(const char* name)
	{
		const auto t6_dvar = game::t6::Dvar_FindVar(name);
		const auto iw5_dvar = game::t6::Dvar_FindVar(name);

		const auto result = SELECT_VALUE(t6_dvar, t6_dvar, iw5_dvar);

		if (!result)
		{
			return "";
		}

		return result->current.string;
	}

	int get_maxclients()
	{
		const auto t6_maxclients = game::t6::Dvar_FindVar("sv_maxclients")->current.integer;
		const auto iw5_maxclients = game::iw5::Dvar_FindVar("sv_maxclients")->current.integer;

		return SELECT_VALUE(t6_maxclients, t6_maxclients, iw5_maxclients);
	}

	Cmd_AddCommandInternal_t Cmd_AddCommandInternal = Cmd_AddCommandInternal_t(SELECT_VALUE(0x5B3070, 0x4DC2A0, 0x545DF0));
	Cmd_Argv_t Cmd_Argv = Cmd_Argv_t(SELECT_VALUE(0x5608F0, 0x6B3D40, 0x467600));
	//Cmd_ArgvBuffer_t Cmd_ArgvBuffer = Cmd_ArgvBuffer_t(SELECT_VALUE(0x6600A0, 0, 0));
	//ConcatArgs_t ConcatArgs = ConcatArgs_t(SELECT_VALUE(0x5FB8B0, 0, 0x502150));

	namespace iw5
	{
		Dvar_FindVar_t Dvar_FindVar = Dvar_FindVar_t(SELECT_VALUE(0x563A70, 0x673C80, 0x5BDCC0));
	}

	namespace t6
	{
		Dvar_FindVar_t Dvar_FindVar = Dvar_FindVar_t(SELECT_VALUE(0x563A70, 0x673C80, 0x5BDCC0));
	}

	I_CleanStr_t I_CleanStr = I_CleanStr_t(SELECT_VALUE(0x44F2B0, 0x483F40, 0x5C2C60));

	//Info_SetValueForKey_t Info_SetValueForKey = Info_SetValueForKey_t(SELECT_VALUE(0x497300, 0, 0x5C3170));
	Info_ValueForKey_t Info_ValueForKey = Info_ValueForKey_t(SELECT_VALUE(0x68B420, 0x46AD00, 0x5C2DB0));

	//G_SayTo_t G_SayTo = G_SayTo_t(SELECT_VALUE(0, 0, 0x502980));
	//G_Say_t G_Say = G_Say_t(SELECT_VALUE(0, 0, 0x502B60));

	SV_GetUserInfo_t SV_GetUserInfo = SV_GetUserInfo_t(SELECT_VALUE(0x68BB90, 0x4C10F0, 0x573E00));
	//SV_GetGuid_t SV_GetGuid = SV_GetGuid_t(SELECT_VALUE(0x5DF410, 0, 0));
	//SV_Cmd_Argv_t SV_Cmd_Argv = SV_Cmd_Argv_t(SELECT_VALUE(0x6DBF80, 0, 0));
	//SV_Cmd_ArgvBuffer_t SV_Cmd_ArgvBuffer = SV_Cmd_ArgvBuffer_t(SELECT_VALUE(0x660050, 0, 0));
	SV_GameSendServerCommand_t SV_GameSendServerCommand = SV_GameSendServerCommand_t(SELECT_VALUE(0x45D7D0, 0x40D450, 0x573220));

	ClientUserInfoChanged_t ClientUserInfoChanged = ClientUserInfoChanged_t(SELECT_VALUE(0x4ED6A0, 0x427DC0, 0x4FADB0));
	ClientCommand_t ClientCommand = ClientCommand_t(SELECT_VALUE(0x47E590, 0x4490C0, 0x502CB0));
	//ClientDisconnect_t ClientDisconnect = ClientDisconnect_t(SELECT_VALUE(0x4ED6A0, 0, 0));

	//gclient_t* g_clients = reinterpret_cast<gclient_t*>(SELECT_VALUE(0x2370BA0, 0, 0));
	//iw5::gentity_t* g_entities = reinterpret_cast<iw5::gentity_t*>(SELECT_VALUE(0x21EF7C0, 0x21C13C0, 0x1A66E28));

	//CmdArgs* cmd_args = reinterpret_cast<CmdArgs*>(SELECT_VALUE(0, 0, 0x1C978D0));
	CmdArgs* sv_cmd_args = reinterpret_cast<CmdArgs*>(SELECT_VALUE(0x255DD48, 0x252F8C8, 0x1CAA998));
}