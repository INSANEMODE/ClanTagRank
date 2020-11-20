#include "../stdinc.hpp"

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

	std::string gamename = get_gamename();

	DWORD select_value(DWORD t6mp, DWORD t6zm, DWORD iw5)
	{
		return strcmp(gamename.data(), "t6mp") == 0
			? t6mp 
			: strcmp(gamename.data(), "t6zm") == 0 
				? t6zm 
				: iw5;
	}
}

namespace game
{
	Cmd_AddCommandInternal_t Cmd_AddCommandInternal = Cmd_AddCommandInternal_t(select_value(0x5B3070, 0x004DC2A0, 0x545DF0));
	Cmd_Argv_t Cmd_Argv = Cmd_Argv_t(select_value(0x5608F0, 0x6B3D40, 0x467600));

	//ClientCommand_t ClientCommand = ClientCommand_t(select_value(0x47E590, 0, 0x502CB0));
	//ClientDisconnect_t ClientDisconnect = ClientDisconnect_t(select_value(0x4ED6A0, 0, 0));

	//ConcatArgs_t ConcatArgs = ConcatArgs_t(select_value(0x5FB8B0, 0, 0x502150));

	//Info_SetValueForKey_t Info_SetValueForKey = Info_SetValueForKey_t(select_value(0x497300, 0, 0));
	Info_ValueForKey_t Info_ValueForKey = Info_ValueForKey_t(select_value(0x68B420, 0, 0));

	I_CleanStr_t I_CleanStr = I_CleanStr_t(select_value(0x44F2B0, 0, 0));

	//SV_GetUserInfo_t SV_GetUserInfo = SV_GetUserInfo_t(select_value(0x68BB90, 0, 0));
	//SV_Cmd_Argv_t SV_Cmd_Argv = SV_Cmd_Argv_t(select_value(0x6DBF80, 0, 0));

	//ClientUserInfoChanged_t ClientUserInfoChanged = ClientUserInfoChanged_t(select_value(0x4ED6A0, 0, 0));
	//Cmd_ArgvBuffer_t Cmd_ArgvBuffer = Cmd_ArgvBuffer_t(select_value(0x6600A0, 0, 0));

	//SV_Cmd_ArgvBuffer_t SV_Cmd_ArgvBuffer = SV_Cmd_ArgvBuffer_t(select_value(0x660050, 0, 0));

	//gclient_t* g_clients = reinterpret_cast<gclient_t*>(select_value(0x2370BA0, 0, 0));
	t6::gentity_t* g_entities = reinterpret_cast<t6::gentity_t*>(select_value(0x21EF7C0, 0x21C13C0, 0x1A66E28));
}