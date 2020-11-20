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

	struct CmdArgs
	{
		int nesting;
		LocalClientNum_t localClientNum[8];
		int controllerIndex[8];
		int argc[8];
		const char** argv[8];
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

	namespace iw5
	{
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

		struct __declspec(align(8)) clientSession_t
		{
			int sessionState;
			int forceSpectatorClient;
			int isInKillcam;
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
			char _0x1CC[0x1D4];
		};

		struct gclient_t
		{
			char _0x0[0x3300];
			clientSession_t sess;
			char _0x36A0[0x400];
		};

#pragma pack(push, 4)
		struct gentity_t
		{
			char _0x0[0x168];
			gclient_t* client;
			char _0x158[0x180];
		};
	}

	namespace t6
	{
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