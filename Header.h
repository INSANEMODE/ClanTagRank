#ifndef HEADER_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define HEADER_H

typedef void(__cdecl* Com_Printf_t)(int channel, const char* fmt, ...);
Com_Printf_t Com_Printf;

typedef void(__cdecl* SV_GameSendServerCommand_t)(int clientNum, /*svscmd_type*/int type, const char* text);
SV_GameSendServerCommand_t SV_GameSendServerCommand;
//void Scr_iPrintLn(int clientNum, const std::string& message);
//typedef int (__cdcel *LogFunction)(char*, char);
//typedef int (__cdecl *G_LogPrintf)(char *, char);
//G_LogPrintf pG_LogPrintf;
//typedef int (__cdecl *cod_printf)(const char*, ...);
//cod_printf pcod_printf;
typedef int (__cdecl* killserver_t)(int);
killserver_t killserver;
typedef void(__cdecl* Cbuf_AddText_t)(int localClientNum, const char* text);
Cbuf_AddText_t Cbuf_AddText;

#endif