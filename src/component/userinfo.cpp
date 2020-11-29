#include "stdinc.hpp"

namespace
{
	utils::hook::detour info_value_for_key_hook;
	std::unordered_map<std::string, std::function<const char* (const char*, const char*, const char*, int)>> info_callbacks;

	int client_num_from_userinfo(const char* s)
	{
		const auto sv_maxclients = game::get_maxclients();

		for (auto i = 0; i < sv_maxclients; i++)
		{
			char buffer[2048];
			game::SV_GetUserInfo(i, buffer, 2048);

			if (strcmp(s, buffer) == 0)
			{
				return i;
			}
		}

		return -1;
	}

	const char* info_value_for_key_stub(const char* s, const char* key)
	{
		const auto result = info_value_for_key_hook.invoke<const char*>(s, key);

		if (info_callbacks.find(key) != info_callbacks.end())
		{
			const auto clientNum = client_num_from_userinfo(s);

			if (clientNum == -1)
			{
				return result;
			}

			return info_callbacks[key](s, key, result, clientNum);
		}

		return result;
	}
}

namespace userinfo
{
	void add(std::string name, std::function<const char* (const char*, const char*, const char*, int)> callback)
	{
		info_callbacks[name] = callback;
	}

	void init()
	{
		info_value_for_key_hook.create(game::Info_ValueForKey, info_value_for_key_stub);
	}
}