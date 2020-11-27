#include "stdinc.hpp"

namespace
{
	game::ClientCommand_t ClientCommand_hook;

	std::unordered_map<std::string, std::function<void(int, command::params_sv&, std::function<void()>)>> handlers;

	void say_stub(int clientNum, command::params_sv& params, std::function<void()> next)
	{
		std::string name = params.get(1);

		name.erase(0, 1);

		if (handlers.find(name) != handlers.end())
		{
			return handlers[name](clientNum, params, next);
		}

		next();
	}
}

namespace chat
{
	void tellraw(int clientNum, std::string message)
	{
		game::SV_GameSendServerCommand(clientNum, 0, utils::string::va("%c \"%s\"",
			SELECT_VALUE(106, 106, 84), message.data()));
	}

	void sayraw(std::string message)
	{
		game::SV_GameSendServerCommand(-1, 0, utils::string::va("%c \"%s\"",
			SELECT_VALUE(106, 106, 84), message.data()));
	}

	void add(const char* name, std::function<void(int, command::params_sv&, std::function<void()>)> callback)
	{
		handlers[name] = callback;
	}

	void init()
	{
		command::add_sv("say", say_stub);
		command::add_sv("say_team", say_stub);
	}
}