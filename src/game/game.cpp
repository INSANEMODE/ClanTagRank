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

	int get_maxclients()
	{
		const auto t6_maxclients = game::t6::Dvar_FindVar("sv_maxclients")->current.integer;
		const auto iw5_maxclients = game::iw5::Dvar_FindVar("sv_maxclients")->current.integer;

		return SELECT_VALUE(t6_maxclients, t6_maxclients, iw5_maxclients);
	}

	Cmd_AddCommandInternal_t Cmd_AddCommandInternal = Cmd_AddCommandInternal_t(SELECT_VALUE(0x5B3070, 0x4DC2A0, 0x545DF0));
	Cmd_Argv_t Cmd_Argv = Cmd_Argv_t(SELECT_VALUE(0x5608F0, 0x6B3D40, 0x467600));

	ClientUserInfoChanged_t ClientUserInfoChanged = ClientUserInfoChanged_t(SELECT_VALUE(0x4ED6A0, 0x427DC0, 0x4FADB0));
	ClientCommand_t ClientCommand = ClientCommand_t(SELECT_VALUE(0x47E590, 0x4490C0, 0x502CB0));

	I_CleanStr_t I_CleanStr = I_CleanStr_t(SELECT_VALUE(0x44F2B0, 0x483F40, 0x5C2C60));

	Info_ValueForKey_t Info_ValueForKey = Info_ValueForKey_t(SELECT_VALUE(0x68B420, 0x46AD00, 0x5C2DB0));

	SEH_StringEd_GetString_t SEH_StringEd_GetString = SEH_StringEd_GetString_t(SELECT_VALUE(0, 0, 0));

	SV_GetUserInfo_t SV_GetUserInfo = SV_GetUserInfo_t(SELECT_VALUE(0x68BB90, 0x4C10F0, 0x573E00));
	SV_GameSendServerCommand_t SV_GameSendServerCommand = SV_GameSendServerCommand_t(SELECT_VALUE(0x45D7D0, 0x40D450, 0x573220));


	namespace iw5
	{
		Dvar_FindVar_t Dvar_FindVar = Dvar_FindVar_t(SELECT_VALUE(0x563A70, 0x673C80, 0x5BDCC0));
		CmdArgs* sv_cmd_args = reinterpret_cast<CmdArgs*>(SELECT_VALUE(0x255DD48, 0x252F8C8, 0x1CAA998));
	}

	namespace t6
	{
		Dvar_FindVar_t Dvar_FindVar = Dvar_FindVar_t(SELECT_VALUE(0x563A70, 0x673C80, 0x5BDCC0));
		CmdArgs* sv_cmd_args = reinterpret_cast<CmdArgs*>(SELECT_VALUE(0x255DD48, 0x252F8C8, 0x1CAA998));
	}
}