#pragma once

namespace game
{
	extern std::string gamename;

	extern bool is_t6mp();
	extern bool is_t6zm();
	extern bool is_iw5();

	extern int get_maxclients();

	typedef void (*Cmd_AddCommandInternal_t)(const char*, void(), cmd_function_t*);
	extern Cmd_AddCommandInternal_t Cmd_AddCommandInternal;

	typedef const char* (*Cmd_Argv_t)(int);
	extern Cmd_Argv_t Cmd_Argv;

	typedef const char* (*Cmd_ArgvBuffer_t)(int, char*, int);
	extern Cmd_ArgvBuffer_t Cmd_ArgvBuffer;

	typedef const char* (*ConcatArgs_t)(int);
	extern ConcatArgs_t ConcatArgs;

	typedef void (*ClientCommand_t)(int);
	extern ClientCommand_t ClientCommand;

	typedef void (*ClientUserInfoChanged_t)(int);
	extern ClientUserInfoChanged_t ClientUserInfoChanged;

	namespace iw5
	{
		typedef const dvar_t* (*Dvar_FindVar_t)(const char*);
		extern Dvar_FindVar_t Dvar_FindVar;

		extern CmdArgs* sv_cmd_args;

		inline int SV_Cmd_Argc()
		{
			return sv_cmd_args->argc[sv_cmd_args->nesting];
		}

		inline const char* SV_Cmd_Argv(int argIndex)
		{
			if (argIndex >= sv_cmd_args->argc[sv_cmd_args->nesting])
			{
				return "";
			}
			return sv_cmd_args->argv[sv_cmd_args->nesting][argIndex];
		}
	}

	namespace t6
	{
		typedef const dvar_t* (*Dvar_FindVar_t)(const char*);
		extern Dvar_FindVar_t Dvar_FindVar;

		extern CmdArgs* sv_cmd_args;

		inline int SV_Cmd_Argc()
		{
			return sv_cmd_args->argc[sv_cmd_args->nesting];
		}

		inline const char* SV_Cmd_Argv(int argIndex)
		{
			if (argIndex >= sv_cmd_args->argc[sv_cmd_args->nesting])
			{
				return "";
			}
			return sv_cmd_args->argv[sv_cmd_args->nesting][argIndex];
		}
	}

	typedef void (*SV_Cmd_ArgvBuffer_t)(int, char*, int);
	extern SV_Cmd_ArgvBuffer_t SV_Cmd_ArgvBuffer;

	typedef int (*SV_GetGuid_t)(int clientNum);
	extern SV_GetGuid_t SV_GetGuid;

	typedef const char* (*SEH_StringEd_GetString_t)(const char*);
	extern SEH_StringEd_GetString_t SEH_StringEd_GetString;

	typedef void (*SV_GetUserInfo_t)(int, char*, int);
	extern SV_GetUserInfo_t SV_GetUserInfo;

	typedef void (*SV_GameSendServerCommand_t)(int, int, const char*);
	extern SV_GameSendServerCommand_t SV_GameSendServerCommand;

	typedef const char* (*Info_ValueForKey_t)(const char*, const char*);
	extern Info_ValueForKey_t Info_ValueForKey;

	typedef const char* (*I_CleanStr_t)(char*);
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