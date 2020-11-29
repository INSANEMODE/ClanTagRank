#pragma once

namespace game
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];

	struct PlayerDetails_t
	{
		char fullDisplayName[38];
		char clanDisplayName[7];
		char gamerTag[32];
		unsigned int fullDisplayNameLength;
		unsigned int clanDisplayLength;
		unsigned int gamerTagDisplayLength;
		bool inView;
		int inViewStartTime;
		int inViewLastTime;
	};

	struct cmd_function_t
	{
		cmd_function_t* next;
		const char* name;
		const char* autoCompleteDir;
		const char* autoCompleteExt;
		void(__cdecl* function)();
		int flags;
	};

	enum LocalClientNum_t
	{
		LOCAL_CLIENT_INVALID = 0xFFFFFFFF,
		LOCAL_CLIENT_0 = 0x0,
		LOCAL_CLIENT_LAST = 0x0,
		LOCAL_CLIENT_COUNT = 0x1,
	};

	struct playerTeamState_t
	{
		int location;
	};

	union $137F9095F7597C63EB19E8F61F5887B0
	{
		int prestige;
		int lastDaysPlayed;
	};

	struct netUInt64
	{
		unsigned int low;
		unsigned int high;
	};

	union $2DC032B70BCFE3CA19206873C522A617
	{
		unsigned __int64 xuid;
		netUInt64 xuid64;
	};

	union $D561C2CA4B3972B2D1AB0668EC54A9CE
	{
		unsigned __int64 leagueTeamID;
		netUInt64 leagueTeamID64;
	};

	union $DF0DE99D085EDFAB8FF39F5C54C2EAC4
	{
		unsigned __int64 leagueSubdivisionID;
		netUInt64 leagueSubdivisionID64;
	};

	struct score_s
	{
		int ping;
		int status_icon;
		int place;
		int score;
		int kills;
		int assists;
		int deaths;
		int wagerWinnings;
		int scoreboardColumns[5];
		int downs;
		int revives;
		int headshots;
		int scoreMultiplier;
		int currentStreak;
	};

	struct $190F2CF944EC18EE3AF27F473C4F9DBE
	{
		unsigned __int32 weaponIdx : 8;
		unsigned __int32 attachment1 : 6;
		unsigned __int32 attachment2 : 6;
		unsigned __int32 attachment3 : 6;
		unsigned __int32 padding : 6;
	};

	union Weapon
	{
		$190F2CF944EC18EE3AF27F473C4F9DBE __s0;
		unsigned int weaponData;
	};

	enum ClientNum_t
	{
		INVALID_CLIENT_INDEX = 0xFFFFFFFF,
		CLIENT_INDEX_FIRST = 0x0,
		CLIENT_INDEX_0 = 0x0,
		CLIENT_INDEX_1 = 0x1,
		CLIENT_INDEX_2 = 0x2,
		CLIENT_INDEX_3 = 0x3,
		CLIENT_INDEX_4 = 0x4,
		CLIENT_INDEX_5 = 0x5,
		CLIENT_INDEX_6 = 0x6,
		CLIENT_INDEX_7 = 0x7,
		CLIENT_INDEX_8 = 0x8,
		CLIENT_INDEX_9 = 0x9,
		CLIENT_INDEX_10 = 0xA,
		CLIENT_INDEX_11 = 0xB,
		CLIENT_INDEX_12 = 0xC,
		CLIENT_INDEX_13 = 0xD,
		CLIENT_INDEX_14 = 0xE,
		CLIENT_INDEX_15 = 0xF,
		CLIENT_INDEX_16 = 0x10,
		CLIENT_INDEX_17 = 0x11,
		CLIENT_INDEX_18 = 0x12,
		CLIENT_INDEX_19 = 0x13,
		CLIENT_INDEX_20 = 0x14,
		CLIENT_INDEX_21 = 0x15,
		CLIENT_INDEX_22 = 0x16,
		CLIENT_INDEX_23 = 0x17,
		CLIENT_INDEX_24 = 0x18,
		CLIENT_INDEX_25 = 0x19,
		CLIENT_INDEX_26 = 0x1A,
		CLIENT_INDEX_27 = 0x1B,
		CLIENT_INDEX_28 = 0x1C,
		CLIENT_INDEX_29 = 0x1D,
		CLIENT_INDEX_30 = 0x1E,
		CLIENT_INDEX_31 = 0x1F,
		CLIENT_INDEX_COUNT = 0x12,
	};

	struct ScoreInfo
	{
		unsigned short ping;
		char status;
		char pad;
		unsigned short score;
		unsigned short kills;
		unsigned short deaths;
		unsigned short assists;
		unsigned short extrascore0;
		unsigned short extrascore1;
		unsigned short adrenaline;
	};

	namespace iw5
	{
		struct CmdArgs
		{
			int nesting;
			LocalClientNum_t localClientNum[8];
			int controllerIndex[8];
			int argc[8];
			const char** argv[8];
		};

		enum DvarFlags
		{
			DVAR_FLAG_NONE = 0,
			DVAR_FLAG_ARCHIVE = 1,			// config saved
			DVAR_FLAG_LATCHED = 2,			// read only
			DVAR_FLAG_CHEAT = 4,			// cheat protected
			DVAR_FLAG_REPLICATED = 8,		// send to client
			DVAR_FLAG_UNK1 = 16,
			DVAR_FLAG_UNK2 = 32,
			DVAR_FLAG_UNK3 = 64,
			DVAR_FLAG_UNK4 = 128,			// bg_regdvars used
			DVAR_FLAG_USERCREATED = 256,	// set cmd, or script created
			DVAR_FLAG_UNK5 = 512,
			DVAR_FLAG_UNK6 = 1024,
			DVAR_FLAG_UNK7 = 2048,
			DVAR_FLAG_UNK8 = 4096,
		};

		enum DvarType
		{
			DVAR_TYPE_BOOL = 0,
			DVAR_TYPE_FLOAT = 1,
			DVAR_TYPE_FLOAT_2 = 2,
			DVAR_TYPE_FLOAT_3 = 3,
			DVAR_TYPE_FLOAT_4 = 4,
			DVAR_TYPE_INT = 5,
			DVAR_TYPE_ENUM = 6,
			DVAR_TYPE_STRING = 7,
			DVAR_TYPE_COLOR = 8,
			//DVAR_TYPE_INT64 = 9
		};

		union DvarValue
		{
			bool enabled;
			int integer;
			unsigned int unsignedInt;
			float value;
			float vector[4];
			const char* string;
			char color[4];
		};

		struct EnumLimits
		{
			int stringCount;
			const char** strings;
		};

		struct IntegerLimits
		{
			int min;
			int max;
		};

		struct FloatLimits
		{
			float min;
			float max;
		};

		union DvarLimits
		{
			EnumLimits enumeration;
			IntegerLimits integer;
			FloatLimits value;
			FloatLimits vector;
		};

		struct dvar_t
		{
			const char* name;
			unsigned int flags;
			char type;
			bool modified;
			DvarValue current;
			DvarValue latched;
			DvarValue reset;
			DvarLimits domain;
			bool(__cdecl* domainFunc)(dvar_t*, DvarValue);
			dvar_t* hashNext;
		};

		struct __declspec(align(8)) clientState_s
		{
			int clientIndex;
			int team;
			int ffaTeam;
			int modelindex;
			int dualWielding;
			int attachModelIndex[6];
			int attachTagIndex[6];
			char name[32];
			float maxSprintTimeMultiplier;
			int rank;
			int prestige;
			char _0x64[0x68];
			char clanAbbrev[8];
			char _0xB8[0x38];
		};

#pragma pack(push, 4)
		struct usercmd_s
		{
			int serverTime;
			char _0x4[0x4];
			int angles[3];
			Weapon weapon;
			Weapon offHandWeapon;
			Weapon lastWeaponAltModeSwitch;
			char forwardmove;
			char rightmove;
			char upmove;
			char pitchmove;
			char yawmove;
			__int16 gunPitch;
			__int16 gunYaw;
			__int16 wiiumoteAimX;
			__int16 wiiumoteAimY;
			char wiiuControllerType;
			unsigned __int16 meleeChargeEnt;
			char meleeChargeDist;
			char _0x38[0x4];
			char selectedLocation[2];
			char selectedYaw;
			unsigned __int16 airburstMarkDistance;
			unsigned __int16 lastInput;
		};
#pragma pack(pop)

		struct clientSession_t
		{
			int sessionState;
			int forceSpectatorClient;
			int killCamEntity;
			int isInKillcam;
			char __0x332C[0x14];
			usercmd_s cmd;
			usercmd_s oldcmd;
			int localClient;
			char __0x33C4[0x24];
			float moveSpeedScaleMultiplier;
			int viewmodelIndex;
			int noSpectate;
			clientState_s cs;
			ScoreInfo scores;
			char __pad[0x1B0];
		};

		struct playerState_s
		{
			int commandTime;
			int pm_type;
			int pm_time;
			int pm_flags;
			int otherFlags;
			int linkFlags;
			int bobCycle;
			float origin[3];
			float velocity[3];
			int grenadeTimeLeft;
			int throwbackGrenadeOwner;
			int throwbackGrenadeTimeLeft;
			Weapon throwbackWeapon;
			int movingPlatformEntity;
			int remoteEyesEnt;
			int remoteEyesTagname;
			int remoteControlEnt;
			int remoteTurretEnt;
			int foliageSoundTime;
			int gravity; int speed;
			float delta_angles[3];
			int groundEntityNum;
			float vLadderVec[3];
			int jumpTime;
			float jumpOriginZ;
			int legsTimer;
			int legsAnim;
			int torsoTimer;
			int torsoAnim;
			int animMoveType;
			int damageTimer;
			int damageDuration;
			int flinch;
			int movementDir;
			int turnStartTime;
			int turnDirection;
			int turnRemaining;
			int corpseIndex;
			char _0xB8[0x3190];
		};

		struct gclient_t
		{
			playerState_s ps;
			clientSession_t sess;
			int flags;
			int spectatorClient;
			char __0x36B4[0x3B0];
		};

		union EntityStateIndexUnion
		{
			int brushModel;
			int triggerModel;
			int xmodel;
			int primaryLight;
		};

		struct entityState_s
		{
			int	number;
			int	type;
			char lerp[0x68]; //struct LerpEntityState 0x68
			int	staticState; // union StaticEntityStateTypeUnion 0x4
			int	time2;
			int	otherEntityNum;
			int attackerEntityNum;
			int	groundEntityNum;
			int	loopSound;
			int	surfType;
			EntityStateIndexUnion index;
			int	clientNum;
			// clientnum   // 144 0x90
		};

		struct entityShared_s
		{
			char _0x108[0x30];
			vec3_t origin;
			vec3_t angles;
			char _0x14C[0xC];
		};

		struct gentity_t
		{
			char pad[0x108];
			entityShared_s shared;
			gclient_t* client;
		};
	}

	namespace t6
	{
		struct CmdArgs
		{
			int nesting;
			LocalClientNum_t localClientNum[8];
			int controllerIndex[8];
			char pad[0x40];
			int argc[8];
			const char** argv[8];
		};

		enum dvarType_t
		{
			DVAR_TYPE_INVALID = 0x0,
			DVAR_TYPE_BOOL = 0x1,
			DVAR_TYPE_FLOAT = 0x2,
			DVAR_TYPE_FLOAT_2 = 0x3,
			DVAR_TYPE_FLOAT_3 = 0x4,
			DVAR_TYPE_FLOAT_4 = 0x5,
			DVAR_TYPE_INT = 0x6,
			DVAR_TYPE_ENUM = 0x7,
			DVAR_TYPE_STRING = 0x8,
			DVAR_TYPE_COLOR = 0x9,
			DVAR_TYPE_INT64 = 0xA,
			DVAR_TYPE_LINEAR_COLOR_RGB = 0xB,
			DVAR_TYPE_COLOR_XYZ = 0xC,
			DVAR_TYPE_COUNT = 0xD,
		};

		union DvarValue
		{
			bool enabled;
			int integer;
			unsigned int unsignedInt;
			__int64 integer64;
			unsigned __int64 unsignedInt64;
			float value; vec4_t vector;
			const char* string;
			char color[4];
		};

		struct $A37BA207B3DDD6345C554D4661813EDD
		{
			int stringCount;
			const char* const* strings;
		};

		struct $9CA192F9DB66A3CB7E01DE78A0DEA53D
		{
			int min;
			int max;
		};

		struct $251C2428A496074035CACA7AAF3D55BD
		{
			float min;
			float max;
		};

		union DvarLimits
		{
			$A37BA207B3DDD6345C554D4661813EDD enumeration;
			$9CA192F9DB66A3CB7E01DE78A0DEA53D integer;
			$251C2428A496074035CACA7AAF3D55BD value;
			$251C2428A496074035CACA7AAF3D55BD vector;
		};

		struct dvar_t
		{
			const char* name;
			const char* description;
			int hash;
			unsigned int flags;
			dvarType_t type;
			bool modified;
			DvarValue current;
			DvarValue latched;
			DvarValue reset;
			DvarLimits domain;
			dvar_t* hashNext;
		};

		struct __declspec(align(8)) clientState_s
		{
			int clientIndex;
			int team;
			int ffaTeam;
			int modelindex;
			int riotShieldNext;
			int attachModelIndex[6];
			int attachTagIndex[6];
			char name[32];
			float maxSprintTimeMultiplier;
			int rank;
			$137F9095F7597C63EB19E8F61F5887B0 ___u10;
			int lastDamageTime;
			int lastStandStartTime;
			int turnedHumanTime;
			int beingRevived;
			$2DC032B70BCFE3CA19206873C522A617 ___u15;
			$D561C2CA4B3972B2D1AB0668EC54A9CE ___u16;
			int leagueDivisionID;
			char _0x94[0x3];
			$DF0DE99D085EDFAB8FF39F5C54C2EAC4 ___u18;
			int leagueSubdivisionRank;
			unsigned int perks[2];
			int voiceConnectivityBits;
			char clanAbbrev[8];
			int attachedVehEntNum;
			int attachedVehSeat;
			int needsRevive;
			int clanAbbrevEV;
			int vehAnimState;
			score_s score;
			int clientUIVisibilityFlags;
			int offhandWeaponVisible;
		};

#pragma pack(push, 4)
		struct usercmd_s
		{
			int serverTime;
			char _0x4[0x4];
			int angles[3];
			Weapon weapon;
			Weapon offHandWeapon;
			Weapon lastWeaponAltModeSwitch;
			char forwardmove;
			char rightmove;
			char upmove;
			char pitchmove;
			char yawmove;
			__int16 gunPitch;
			__int16 gunYaw;
			__int16 wiiumoteAimX;
			__int16 wiiumoteAimY;
			char wiiuControllerType;
			unsigned __int16 meleeChargeEnt;
			char meleeChargeDist;
			char _0x38[0x4];
			char selectedLocation[2];
			char selectedYaw;
			unsigned __int16 airburstMarkDistance;
			unsigned __int16 lastInput;
		};
#pragma pack(pop)

		struct __declspec(align(8)) clientSession_t
		{
			int sessionState;
			int forceSpectatorClient;
			int killCamEntity;
			int killCamTargetEntity;
			int archiveTime;
			unsigned __int16 scriptPersId;
			char _0x16[0x2];
			int connected;
			usercmd_s cmd;
			usercmd_s old_cmd;
			char _0xAC[0x20];
			int maxHealth;
			int enterTime;
			char _0xD4[0x4];
			int voteCount;
			int teamVoteCount;
			float moveSpeedScaleMultiplier;
			int viewmodelIndex;
			int noSpectate;
			int teamInfo;
			clientState_s cs;
			int psOffsetTime;
			int scoreboardColumnCache[26];
			char _0x27C[0x4];
		};

		struct gclient_t
		{
			char _0x0[0x2A08 * 2];
			clientSession_t sess;
			char _0x5690[0x178];
		};

#pragma pack(push, 4)
		struct gentity_t
		{
			char _0x0[0x154];
			gclient_t* client;
			char _0x158[0x1C4];
		};
	}
}