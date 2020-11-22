#pragma once

namespace game
{
	extern std::string gamename;

	extern bool is_t6mp();
	extern bool is_t6zm();
	extern bool is_iw5();

	extern int get_maxclients();

	typedef void (*Cmd_AddCommandInternal_t)(const char*, void(), cmd_function_t* allocedCmd);
	extern Cmd_AddCommandInternal_t Cmd_AddCommandInternal;

	typedef const char* (*Cmd_Argv_t)(int argIndex);
	extern Cmd_Argv_t Cmd_Argv;

	typedef const char* (*Cmd_ArgvBuffer_t)(int start, char* buffer, int bufLength);
	extern Cmd_ArgvBuffer_t Cmd_ArgvBuffer;

	typedef const char* (*ConcatArgs_t)(int start);
	extern ConcatArgs_t ConcatArgs;

	typedef void (*ClientCommand_t)(int clientNum);
	extern ClientCommand_t ClientCommand;

	typedef void (*ClientDisconnect_t)(ClientNum_t clientNum);
	extern ClientDisconnect_t ClientDisconnect;

	typedef void (*ClientUserInfoChanged_t)(int clientNum);
	extern ClientUserInfoChanged_t ClientUserInfoChanged;

	namespace iw5
	{
		typedef const dvar_t* (*Dvar_FindVar_t)(const char* name);
		extern Dvar_FindVar_t Dvar_FindVar;
	}

	namespace t6
	{
		typedef const dvar_t* (*Dvar_FindVar_t)(const char* name);
		extern Dvar_FindVar_t Dvar_FindVar;
	}

	typedef void (*SV_Cmd_ArgvBuffer_t)(int arg, char* buffer, int bufferLength);
	extern SV_Cmd_ArgvBuffer_t SV_Cmd_ArgvBuffer;

	typedef const char* (*SV_Cmd_Argv_t)(int argIndex);
	extern SV_Cmd_Argv_t SV_Cmd_Argv;

	typedef int (*SV_GetGuid_t)(int clientNum);
	extern SV_GetGuid_t SV_GetGuid;

	typedef void (*SV_GetUserInfo_t)(int index, char* buffer, int bufferSize);
	extern SV_GetUserInfo_t SV_GetUserInfo;

	typedef void (*SV_GameSendServerCommand_t)(int clientNum, int reliable, const char* command);
	extern SV_GameSendServerCommand_t SV_GameSendServerCommand;

	typedef void (*Info_SetValueForKey_t)(char* s, const char* key, const char* value);
	extern Info_SetValueForKey_t Info_SetValueForKey;

	typedef const char* (*Info_ValueForKey_t)(const char* s, const char* key);
	extern Info_ValueForKey_t Info_ValueForKey;

	typedef const char* (*I_CleanStr_t)(char* string);
	extern I_CleanStr_t I_CleanStr;

	inline int Cmd_Argc()
	{
		auto count = 0;

		for (auto i = 0; strcmp(game::Cmd_Argv(i), "") != 0; i++)
		{
			count++;
		}

		return count;
	}
}