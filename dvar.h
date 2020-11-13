#pragma once
//Reversed by CraigChrist8239
//Thanks caboose

#include <Windows.h>
#include <stdio.h>

#define DVAR_ARCHIVE		(1 << 0)	// 0x0001
#define DVAR_USERINFO		(1 << 1)	// 0x0002
#define DVAR_SERVERINFO		(1 << 2)	// 0x0004
#define DVAR_SYSTEMINFO		(1 << 3)	// 0x0008
#define DVAR_INIT		(1 << 4)	// 0x0010
#define DVAR_LATCH		(1 << 5)	// 0x0020
#define DVAR_ROM		(1 << 6)	// 0x0040
#define DVAR_CHEAT		(1 << 7)	// 0x0080
#define DVAR_DEVELOPER		(1 << 8)	// 0x0100
#define DVAR_SAVED		(1 << 9)	// 0x0200
#define DVAR_NORESTART		(1 << 10)	// 0x0400
#define DVAR_CHANGEABLE_RESET	(1 << 12)	// 0x1000
#define DVAR_EXTERNAL		(1 << 14)	// 0x4000
#define DVAR_AUTOEXEC		(1 << 15)	// 0x8000

enum DvarSetSource
{
	DVAR_SOURCE_INTERNAL = 0,
	DVAR_SOURCE_EXTERNAL = 1,
	DVAR_SOURCE_SCRIPT = 2
};

union DvarLimits {
	struct
	{
		int stringCount;
		const char** strings;
	} enumeration;
	struct
	{
		int min;
		int max;
	} integer;
	struct
	{
		float min;
		float max;
	} value, vector; //decimal;
	struct {
		__int64 min;
		__int64 max;
	} integer64;
};

union DvarValue {
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	__int64 integer64;
	unsigned __int64 unsignedInt64;
	float value;
	float vector[4];
	const char* string;
	char color[4];
};

typedef enum DvarType : char
{
	Dvar_Bool = 0x1,
	Dvar_Float = 0x2,
	Dvar_Vec2 = 0x3,
	Dvar_Vec3 = 0x4,
	Dvar_Vec4 = 0x5,
	Dvar_Int = 0x6,
	Dvar_Enum = 0x7,
	Dvar_String = 0x8,
	Dvar_Color = 0x9,
	Dvar_DevTweak = 0x09,
	DVAR_TYPE_INT64 = 0xA,
	DVAR_TYPE_LINEAR_COLOR_RGB = 0xB,
	DVAR_TYPE_COLOR_XYZ = 0xC,
	DVAR_TYPE_COUNT = 0xD,
} DvarType;

typedef struct dvar_s
{
	char* dvarName;
	const char* description;
	unsigned int flags;
	//short flags;
	DvarType type;
	bool modified;

	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarLimits domain;
	dvar_s* next;
} dvar_s;

dvar_s** player_sustainAmmo;
dvar_s* cg_fov = 0;

//typedef bool(__cdecl* Dvar_IsSystemActive_t)();
//Dvar_IsSystemActive_t Dvar_IsSystemActive = (Dvar_IsSystemActive_t)0x8229D028;										//Returns true if the dvar system has been initiated

//typedef bool(__cdecl* Dvar_IsValidName_t)(const char* dvarName);
//Dvar_IsValidName_t Dvar_IsValidName = (Dvar_IsValidName_t)0x8229D0A8;
//
//typedef void(__cdecl* Dvar_AssignCurrentString_t)(dvar_s* dvar, const char* string);
//Dvar_AssignCurrentString_t Dvar_AssignCurrentString = (Dvar_AssignCurrentString_t)0x8229D250;
//
//typedef void(__cdecl* Dvar_AssignLatchedString_t)(dvar_s* dvar, const char* string);
//Dvar_AssignLatchedString_t Dvar_AssignLatchedString = (Dvar_AssignLatchedString_t)0x8229D330;
//
//typedef void(__cdecl* Dvar_AssignResetString_t)(dvar_s* dvar, const char* string);
//Dvar_AssignResetString_t Dvar_AssignResetString = (Dvar_AssignResetString_t)0x8229D410;
//
//typedef const char* (__cdecl* Dvar_EnumToString_t)(dvar_s* dvar);
//Dvar_EnumToString_t Dvar_EnumToString = (Dvar_EnumToString_t)0x8229D4F0;
//
//typedef const char* (__cdecl* Dvar_IndexStringToEnumString_t)(dvar_s* dvar, const char* indexString);
//Dvar_IndexStringToEnumString_t Dvar_IndexStringToEnumString = (Dvar_IndexStringToEnumString_t)0x8229D520;
//
//typedef const char* (__cdecl* Dvar_ValueToString_t)(dvar_s* dvar, DvarValue value);
//Dvar_ValueToString_t Dvar_ValueToString = (Dvar_ValueToString_t)0x8229D5D0;
//
//typedef bool(__cdecl* Dvar_StringToBool_t)(const char* string);
//Dvar_StringToBool_t Dvar_StringToBool = (Dvar_StringToBool_t)0x8229D888;
//
//typedef int(__cdecl* Dvar_StringToInt_t)(const char* string);
//Dvar_StringToInt_t Dvar_StringToInt = (Dvar_StringToInt_t)0x8229D8B0;
//
//typedef float(__cdecl* Dvar_StringToFloat_t)(const char* string);
//Dvar_StringToFloat_t Dvar_StringToFloat = (Dvar_StringToFloat_t)0x8229D8B8;
//
//typedef void(__cdecl* Dvar_StringToVec2_t)(const char* string, float* vector);
//Dvar_StringToVec2_t Dvar_StringToVec2 = (Dvar_StringToVec2_t)0x8229D8E0;
//
//typedef void(__cdecl* Dvar_StringToVec3_t)(const char* string, float* vector);
//Dvar_StringToVec3_t Dvar_StringToVec3 = (Dvar_StringToVec3_t)0x8229D908;
//
//typedef void(__cdecl* Dvar_StringToVec4_t)(const char* string, float* vector);
//Dvar_StringToVec4_t Dvar_StringToVec4 = (Dvar_StringToVec4_t)0x8229D950;
//
//typedef int(__cdecl* Dvar_StringToEnum_t)(DvarLimits* domain, const char* string);
//Dvar_StringToEnum_t Dvar_StringToEnum = (Dvar_StringToEnum_t)0x8229D988;
//
//typedef void(__cdecl* Dvar_StringToColor_t)(const char* string, char* color);
//Dvar_StringToColor_t Dvar_StringToColor = (Dvar_StringToColor_t)0x8229DAB0;

//typedef DvarValue* (__cdecl* Dvar_StringToValue_t)(DvarValue* result, const char type, DvarLimits domain, const char* string);
//Dvar_StringToValue_t Dvar_StringToValue = (Dvar_StringToValue_t)0x008C6EA0;
//
//typedef const char* (__cdecl* Dvar_DisplayableValue_t)(dvar_s* dvar);
//Dvar_DisplayableValue_t Dvar_DisplayableValue = (Dvar_DisplayableValue_t)0x8229DD80;
//
//typedef const char* (__cdecl* Dvar_DisplayableResetValue_t)(dvar_s* dvar);
//Dvar_DisplayableResetValue_t Dvar_DisplayableResetValue = (Dvar_DisplayableResetValue_t)0x8229DD90;
//
//typedef const char* (__cdecl* Dvar_DisplayableLatchedValue_t)(dvar_s* dvar);
//Dvar_DisplayableLatchedValue_t Dvar_DisplayableLatchedValue = (Dvar_DisplayableLatchedValue_t)0x8229DDA0;

//typedef void(__cdecl* Dvar_ClampVectorToDomain_t)(float* vector, int components, float min, float max);
//Dvar_ClampVectorToDomain_t Dvar_ClampVectorToDomain = (Dvar_ClampVectorToDomain_t)0x8229DDB0;

//typedef bool(__cdecl* Dvar_VectorInDomain_t)(const float* vector, int components, float min, float max);
//Dvar_VectorInDomain_t Dvar_VectorInDomain = (Dvar_VectorInDomain_t)0x8229DDF0;

typedef DvarValue* (__cdecl* Dvar_ClampValueToDomain_t)(DvarValue* result, char type, DvarValue value, DvarValue resetValue, DvarLimits domain);
Dvar_ClampValueToDomain_t Dvar_ClampValueToDomain = (Dvar_ClampValueToDomain_t)0x008C7000;

//typedef bool(__cdecl* Dvar_ValueInDomain_t)(char type, DvarValue value, DvarLimits domain);
//Dvar_ValueInDomain_t Dvar_ValueInDomain = (Dvar_ValueInDomain_t)0x8229E048;

//typedef void(__cdecl* Dvar_VectorDomainToString_t)(int components, DvarLimits domain, char* outBuffer, int outBufferLen);
//Dvar_VectorDomainToString_t Dvar_VectorDomainToString = (Dvar_VectorDomainToString_t)0x8229E228;

//typedef const char* (__cdecl* Dvar_DomainToString_Internal_t)(char type, DvarLimits domain, char* outBuffer, int outBufferLen, int* outLineCount);
//Dvar_DomainToString_Internal_t Dvar_DomainToString_Internal = (Dvar_DomainToString_Internal_t)0x8229E310;
//
//typedef const char* (__cdecl* Dvar_DomainToString_t)(char type, DvarLimits domain, char* outBuffer, int outBufferLen);
//Dvar_DomainToString_t Dvar_DomainToString = (Dvar_DomainToString_t)0x8229E670;
//
//typedef const char* (__cdecl* Dvar_DomainToString_GetLines_t)(char type, DvarLimits domain, char* outBuffer, int outBufferLen, int* outLineCount);
//Dvar_DomainToString_GetLines_t Dvar_DomainToString_GetLines = (Dvar_DomainToString_GetLines_t)0x8229E678;

//typedef int(__cdecl* Dvar_ValuesEqual_t)(char type, DvarValue val0, DvarValue val1);
//Dvar_ValuesEqual_t Dvar_ValuesEqual = (Dvar_ValuesEqual_t)0x8229E680;

typedef void(__cdecl* Dvar_SetLatchedValue_t)(dvar_s* dvar, DvarValue value);
Dvar_SetLatchedValue_t Dvar_SetLatchedValue = (Dvar_SetLatchedValue_t)0x008C73D0;

//typedef bool(__cdecl* Dvar_HasLatchedValue_t)(dvar_s* dvar);
//Dvar_HasLatchedValue_t Dvar_HasLatchedValue = (Dvar_HasLatchedValue_t)0x8229E960;

typedef void(__cdecl* Dvar_SetVariant_t)(dvar_s* dvar, DvarValue value, DvarSetSource source);
Dvar_SetVariant_t Dvar_SetVariant = (Dvar_SetVariant_t)0x008C7ED0;

typedef dvar_s* (__cdecl* Dvar_FindMalleableVar_t)(const char* dvarName);
Dvar_FindMalleableVar_t Dvar_FindMalleableVar = (Dvar_FindMalleableVar_t)0x008C7520;

//typedef dvar_s* (__cdecl* Dvar_FindVar_t)(const char* dvarName);
//Dvar_FindVar_t Dvar_FindVar = (Dvar_FindVar_t)0x8229EDC8;

typedef void(__cdecl* Dvar_ClearModified_t)(dvar_s* dvar);
Dvar_ClearModified_t Dvar_ClearModified = (Dvar_ClearModified_t)0x005C7700;

//typedef void(__cdecl* Dvar_SetModified_t)(dvar_s* dvar);
//Dvar_SetModified_t Dvar_SetModified = (Dvar_SetModified_t)0x8229EDE0;

//typedef void(__cdecl* Dvar_UpdateEnumDomain_t)(dvar_s* dvar, const char** stringTable);
//Dvar_UpdateEnumDomain_t Dvar_UpdateEnumDomain = (Dvar_UpdateEnumDomain_t)0x8229EDF0;

typedef bool(__cdecl* Dvar_GetBool_t)(const char* dvarName);
Dvar_GetBool_t Dvar_GetBool = (Dvar_GetBool_t)0x006F1650;

typedef int(__cdecl* Dvar_GetInt_t)(const char* dvarName);
Dvar_GetInt_t Dvar_GetInt = (Dvar_GetInt_t)0x006909F0;

typedef float(__cdecl* Dvar_GetFloat_t)(const char* dvarName);
Dvar_GetFloat_t Dvar_GetFloat = (Dvar_GetFloat_t)0x00698B90;

//typedef void(__cdecl* Dvar_GetVec3_t)(const char* dvarName, float* result);
//Dvar_GetVec3_t Dvar_GetVec3 = (Dvar_GetVec3_t)0x8229F0A0;

typedef const char* (__cdecl* Dvar_GetString_t)(int dvarName);
Dvar_GetString_t Dvar_GetString = (Dvar_GetString_t)0x005C36F0;

//typedef const char* (__cdecl* Dvar_GetVariantString_t)(const char* dvarName);
//Dvar_GetVariantString_t Dvar_GetVariantString = (Dvar_GetVariantString_t)0x8229F120;

//typedef void(__cdecl* Dvar_GetUnpackedColor_t)(dvar_s* dvar, float* expandedColor);
//Dvar_GetUnpackedColor_t Dvar_GetUnpackedColor = (Dvar_GetUnpackedColor_t)0x8229F1C8;

//typedef void(__cdecl* Dvar_GetUnpackedColorByName_t)(const char* dvarName, float* expandedColor);
//Dvar_GetUnpackedColorByName_t Dvar_GetUnpackedColorByName = (Dvar_GetUnpackedColorByName_t)0x8229F290;

//typedef void(__cdecl* Dvar_Shutdown_t)();
//Dvar_Shutdown_t Dvar_Shutdown = (Dvar_Shutdown_t)0x8229F308;

typedef void(__cdecl* Dvar_PerformUnregistration_t)(dvar_s* dvar);
Dvar_PerformUnregistration_t Dvar_PerformUnregistration = (Dvar_PerformUnregistration_t)0x008C75E0;

typedef void(__cdecl* Dvar_UpdateResetValue_t)(dvar_s* dvar, DvarValue value);
Dvar_UpdateResetValue_t Dvar_UpdateResetValue = (Dvar_UpdateResetValue_t)0x008C76D0;

//typedef void(__cdecl* Dvar_ChangeResetValue_t)(dvar_s* dvar, DvarValue value);
//Dvar_ChangeResetValue_t Dvar_ChangeResetValue = (Dvar_ChangeResetValue_t)0x8229F730;

typedef void(__cdecl* Dvar_UpdateValue_t)(dvar_s* dvar, DvarValue value);
Dvar_UpdateValue_t Dvar_UpdateValue = (Dvar_UpdateValue_t)0x008C77F0;

typedef void(__cdecl* Dvar_MakeExplicitType_t)(dvar_s* dvar, const char* dvarName, char type, unsigned __int16 flags, DvarValue resetValue, DvarLimits domain);
Dvar_MakeExplicitType_t Dvar_MakeExplicitType = (Dvar_MakeExplicitType_t)0x008C7960;

//typedef DvarValue* (__cdecl* Dvar_GetReinterpretedResetValue_t)(DvarValue* result, dvar_s* __formal, DvarValue value, char type, unsigned __int16 flags, DvarLimits domain);
//Dvar_GetReinterpretedResetValue_t Dvar_GetReinterpretedResetValue = (Dvar_GetReinterpretedResetValue_t)0x8229FB38;

typedef void(__cdecl* Dvar_ReinterpretDvar_t)(dvar_s* dvar, const char* dvarName, char type, unsigned __int16 flags, DvarValue value, DvarLimits domain);
Dvar_ReinterpretDvar_t Dvar_ReinterpretDvar = (Dvar_ReinterpretDvar_t)0x008C7B40;

typedef void(__cdecl* Dvar_MakeLatchedValueCurrent_t)(dvar_s* dvar);
Dvar_MakeLatchedValueCurrent_t Dvar_MakeLatchedValueCurrent = (Dvar_MakeLatchedValueCurrent_t)0x004E3E30;

//typedef void(__cdecl* Dvar_ClearLatchedValue_t)(dvar_s* dvar);
//Dvar_ClearLatchedValue_t Dvar_ClearLatchedValue = (Dvar_ClearLatchedValue_t)0x8229FC08;

typedef void(__cdecl* Dvar_Reregister_t)(dvar_s* dvar, const char* dvarName, char type, unsigned __int16 flags, DvarValue resetValue, DvarLimits domain, const char* description);
Dvar_Reregister_t Dvar_Reregister = (Dvar_Reregister_t)0x008C82C0;

typedef dvar_s* (__cdecl* Dvar_RegisterNew_t)(const char* dvarName, char type, unsigned __int16 flags, DvarValue value, DvarLimits domain, const char* description);
Dvar_RegisterNew_t Dvar_RegisterNew = (Dvar_RegisterNew_t)0x008C7BD0;

//typedef dvar_s* (__cdecl* Dvar_RegisterVarient_t)(const char* dvarName, char type, unsigned __int16 flags, DvarValue value, DvarLimits domain, const char* description);
//Dvar_RegisterVarient_t Dvar_RegisterVarient = (Dvar_RegisterVarient_t)0x8229FFC0;

typedef dvar_s* (__cdecl* Dvar_RegisterBool_t)(const char* dvarName, bool value, unsigned __int16 flags, const char* description);
Dvar_RegisterBool_t Dvar_RegisterBool = (Dvar_RegisterBool_t)0x005FBCC0;

typedef dvar_s* (__cdecl* Dvar_RegisterInt_t)(const char* dvarName, int value, int min, int max, unsigned __int16 flags, const char* description);
Dvar_RegisterInt_t Dvar_RegisterInt = (Dvar_RegisterInt_t)0x005A3D70;

typedef dvar_s* (__cdecl* Dvar_RegisterFloat_t)(const char* dvarName, float value, float min, float max, unsigned __int16 flags, const char* description);
Dvar_RegisterFloat_t Dvar_RegisterFloat = (Dvar_RegisterFloat_t)0x004D0480;

typedef dvar_s* (__cdecl* Dvar_RegisterVec2_t)(const char* dvarName, float x, float y, float min, float max, unsigned __int16 flags, const char* description);
Dvar_RegisterVec2_t Dvar_RegisterVec2 = (Dvar_RegisterVec2_t)0x00499670;;

typedef dvar_s* (__cdecl* Dvar_RegisterVec3_t)(const char* dvarName, float x, float y, float z, float min, float max, unsigned __int16 flags, const char* description);
Dvar_RegisterVec3_t Dvar_RegisterVec3 = (Dvar_RegisterVec3_t)0x005913F0;

//typedef dvar_s* (__cdecl* Dvar_RegisterDevTweak_t)(const char* dvarName, float x, float y, float min, float max, unsigned __int16 flags, const char* description);
//Dvar_RegisterDevTweak_t Dvar_RegisterDevTweak = (Dvar_RegisterDevTweak_t)0x822A01B0;
//
//typedef dvar_s* (__cdecl* Dvar_RegisterVec4_t)(const char* dvarName, float x, float y, float z, float w, float min, float max, unsigned __int16 flags, const char* description);
//Dvar_RegisterVec4_t Dvar_RegisterVec4 = (Dvar_RegisterVec4_t)0x822A0200;

typedef dvar_s* (__cdecl* Dvar_RegisterString_t)(const char* dvarName, const char* value, unsigned __int16 flags, const char* description);
Dvar_RegisterString_t Dvar_RegisterString = (Dvar_RegisterString_t)0x005176B0;

typedef dvar_s* (__cdecl* Dvar_RegisterEnum_t)(const char* dvarName, const char** valueList, int defaultIndex, unsigned __int16 flags, const char* description);
Dvar_RegisterEnum_t Dvar_RegisterEnum = (Dvar_RegisterEnum_t)0x006FA930;

typedef dvar_s* (__cdecl* Dvar_RegisterColor_t)(const char* dvarName, float r, float g, float b, float a, unsigned __int16 flags, const char* description);
Dvar_RegisterColor_t Dvar_RegisterColor = (Dvar_RegisterColor_t)0x00585060;

//typedef void(__cdecl* Dvar_SetBoolFromSource_t)(dvar_s* dvar, bool value, DvarSetSource source);
//Dvar_SetBoolFromSource_t Dvar_SetBoolFromSource = (Dvar_SetBoolFromSource_t)0x822A0440;

typedef void(__cdecl* Dvar_SetIntFromSource_t)(dvar_s* dvar, int value, DvarSetSource source);
Dvar_SetIntFromSource_t Dvar_SetIntFromSource = (Dvar_SetIntFromSource_t)0x004707D0;

typedef void(__cdecl* Dvar_SetFloatFromSource_t)(dvar_s* dvar, float value, DvarSetSource source);
Dvar_SetFloatFromSource_t Dvar_SetFloatFromSource = (Dvar_SetFloatFromSource_t)0x00459AA0;

//typedef void(__cdecl* Dvar_SetVec2FromSource_t)(dvar_s* dvar, float x, float y, DvarSetSource source);
//Dvar_SetVec2FromSource_t Dvar_SetVec2FromSource = (Dvar_SetVec2FromSource_t)0x822A05B0;
//
//typedef void(__cdecl* Dvar_SetVec3FromSource_t)(dvar_s* dvar, float x, float y, float z, DvarSetSource source);
//Dvar_SetVec3FromSource_t Dvar_SetVec3FromSource = (Dvar_SetVec3FromSource_t)0x822A0640;
//
//typedef void(__cdecl* Dvar_SetVec4FromSource_t)(dvar_s* dvar, float x, float y, float z, float w, DvarSetSource source);
//Dvar_SetVec4FromSource_t Dvar_SetVec4FromSource = (Dvar_SetVec4FromSource_t)0x822A06E0;

typedef void(__cdecl* Dvar_SetStringFromSource_t)(dvar_s* dvar, const char* string, DvarSetSource source);
Dvar_SetStringFromSource_t Dvar_SetStringFromSource = (Dvar_SetStringFromSource_t)0x008C8480;

//typedef void(__cdecl* Dvar_SetColorFromSource_t)(dvar_s* dvar, float r, float g, float b, float a, DvarSetSource source);
//Dvar_SetColorFromSource_t Dvar_SetColorFromSource = (Dvar_SetColorFromSource_t)0x822A0800;

typedef void(__cdecl* Dvar_SetBool_t)(dvar_s* dvar, bool value);
Dvar_SetBool_t Dvar_SetBool = (Dvar_SetBool_t)0x0068F330;

typedef void(__cdecl* Dvar_SetInt_t)(dvar_s* dvar, int value);
Dvar_SetInt_t Dvar_SetInt = (Dvar_SetInt_t)0x00456B10;

typedef void(__cdecl* Dvar_SetFloat_t)(dvar_s* dvar, float value);
Dvar_SetFloat_t Dvar_SetFloat = (Dvar_SetFloat_t)0x004B8AA0;

//typedef void(__cdecl* Dvar_SetVec2_t)(dvar_s* dvar, float x, float y);
//Dvar_SetVec2_t Dvar_SetVec2 = (Dvar_SetVec2_t)0x822A0A08;
//
//typedef void(__cdecl* Dvar_SetVec3_t)(dvar_s* dvar, float x, float y, float z);
//Dvar_SetVec3_t Dvar_SetVec3 = (Dvar_SetVec3_t)0x822A0A10;
//
//typedef void(__cdecl* Dvar_SetVec4_t)(dvar_s* dvar, float x, float y, float z, float w);
//Dvar_SetVec4_t Dvar_SetVec4 = (Dvar_SetVec4_t)0x822A0A18;

typedef void(__cdecl* Dvar_SetString_t)(dvar_s* dvar, const char* string);
Dvar_SetString_t Dvar_SetString = (Dvar_SetString_t)0x004EC3C0;

//typedef void(__cdecl* Dvar_SetColor_t)(dvar_s* dvar, float r, float g, float b, float a);
//Dvar_SetColor_t Dvar_SetColor = (Dvar_SetColor_t)0x822A0A28;

//typedef void(__cdecl* Dvar_SetFromStringFromSource_t)(dvar_s* dvar, const char* string, DvarSetSource source);
//Dvar_SetFromStringFromSource_t Dvar_SetFromStringFromSource = (Dvar_SetFromStringFromSource_t)0x822A0A30;

//typedef void(__cdecl* Dvar_SetFromString_t)(dvar_s* dvar, const char* string);
//Dvar_SetFromString_t Dvar_SetFromString = (Dvar_SetFromString_t)0x822A0B00;

//typedef void(__cdecl* Dvar_SetBoolByName_t)(const char* dvarName, bool value);
//Dvar_SetBoolByName_t Dvar_SetBoolByName = (Dvar_SetBoolByName_t)0x822A0B08;
//
//typedef void(__cdecl* Dvar_SetIntByName_t)(const char* dvarName, int value);
//Dvar_SetIntByName_t Dvar_SetIntByName = (Dvar_SetIntByName_t)0x822A0BA0;
//
//typedef void(__cdecl* Dvar_SetFloatByName_t)(const char* dvarName, float value);
//Dvar_SetFloatByName_t Dvar_SetFloatByName = (Dvar_SetFloatByName_t)0x822A0C38;
//
//typedef void(__cdecl* Dvar_SetVec2ByName_t)(const char* dvarName, float x, float y);
//Dvar_SetVec2ByName_t Dvar_SetVec2ByName = (Dvar_SetVec2ByName_t)0x822A0CD0;
//
//typedef void(__cdecl* Dvar_SetVec3ByName_t)(const char* dvarName, float x, float y, float z);
//Dvar_SetVec3ByName_t Dvar_SetVec3ByName = (Dvar_SetVec3ByName_t)0x822A0D80;
//
//typedef void(__cdecl* Dvar_SetVec4ByName_t)(const char* dvarName, float x, float y, float z, float w);
//Dvar_SetVec4ByName_t Dvar_SetVec4ByName = (Dvar_SetVec4ByName_t)0x822A0E50;
//
//typedef void(__cdecl* Dvar_SetStringByName_t)(const char* dvarName, const char* string);
//Dvar_SetStringByName_t Dvar_SetStringByName = (Dvar_SetStringByName_t)0x822A0F28;
//
//typedef void(__cdecl* Dvar_SetColorByName_t)(const char* dvarName, float r, float g, float b, float a);
//Dvar_SetColorByName_t Dvar_SetColorByName = (Dvar_SetColorByName_t)0x822A0FA8;

//typedef void(__cdecl* Dvar_SetFromStringByNameFromSource_t)(const char* dvarName, const char* string, DvarSetSource source);
//Dvar_SetFromStringByNameFromSource_t Dvar_SetFromStringByNameFromSource = (Dvar_SetFromStringByNameFromSource_t)0x822A1080;
//
//typedef void(__cdecl* Dvar_SetFromStringByName_t)(const char* dvarName, const char* string);
//Dvar_SetFromStringByName_t Dvar_SetFromStringByName = (Dvar_SetFromStringByName_t)0x822A10F8;
//
//typedef void(__cdecl* Dvar_AddFlags_t)(dvar_s* dvar, int flags);
//Dvar_AddFlags_t Dvar_AddFlags = (Dvar_AddFlags_t)0x822A1100;
//
//typedef void(__cdecl* Dvar_Reset_t)(dvar_s* dvar, DvarSetSource setSource);
//Dvar_Reset_t Dvar_Reset = (Dvar_Reset_t)0x822A1128;
const char* getDvar(int dvar)
{

	return Dvar_GetString(dvar);
}