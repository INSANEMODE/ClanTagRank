#pragma once

namespace game
{
	typedef void (*Cmd_AddCommandInternal_t)(const char*, void(), cmd_function_t* allocedCmd);
	extern Cmd_AddCommandInternal_t Cmd_AddCommandInternal;

	typedef const char* (*Cmd_Argv_t)(int argIndex);
	extern Cmd_Argv_t Cmd_Argv;

	typedef const char* (*Cmd_ArgvBuffer_t)(int start, char* buffer, int bufLength);
	extern Cmd_ArgvBuffer_t Cmd_ArgvBuffer;

	typedef void (*ClientCommand_t)(int clientNum);
	extern ClientCommand_t ClientCommand;

	typedef void (*ClientDisconnect_t)(ClientNum_t clientNum);
	extern ClientDisconnect_t ClientDisconnect;

	typedef const char* (*ConcatArgs_t)(int start);
	extern ConcatArgs_t ConcatArgs;

	typedef void (*SV_Cmd_ArgvBuffer_t)(int arg, char* buffer, int bufferLength);
	extern SV_Cmd_ArgvBuffer_t SV_Cmd_ArgvBuffer;

	typedef const char* (*SV_Cmd_Argv_t)(int argIndex);
	extern SV_Cmd_Argv_t SV_Cmd_Argv;

	typedef void (*SV_GetUserInfo_t)(int index, char* buffer, int bufferSize);
	extern SV_GetUserInfo_t SV_GetUserInfo;

	typedef void (*Info_SetValueForKey_t)(char* s, const char* key, const char* value);
	extern Info_SetValueForKey_t Info_SetValueForKey;

	typedef void (*ClientUserInfoChanged_t)(ClientNum_t clientNum);
	extern ClientUserInfoChanged_t ClientUserInfoChanged;

	typedef const char* (*Info_ValueForKey_t)(const char* s, const char* key);
	extern Info_ValueForKey_t Info_ValueForKey;

	typedef const char* (*I_CleanStr_t)(char* string);
	extern I_CleanStr_t I_CleanStr;

	extern t6::gentity_t* g_entities;
}