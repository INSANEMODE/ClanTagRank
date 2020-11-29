#include "stdinc.hpp"

namespace command
{
	std::unordered_map<std::string, std::function<void(params&)>> handlers;
	std::unordered_map<std::string, std::function<void(int, params_sv&, std::function<void()>)>> handlers_sv;

	utils::hook::detour clientcommand_hook;

	void main_handler()
	{
		params params = {};

		const auto command = utils::string::to_lower(params[0]);

		if (handlers.find(command) != handlers.end())
		{
			handlers[command](params);
		}
	}

	int params::size()
	{
		return game::Cmd_Argc();
	}

	const char* params::get(int index)
	{
		return game::Cmd_Argv(index);
	}

	std::string params::join(int index)
	{
		std::string result = {};

		for (int i = index; i < this->size(); i++)
		{
			if (i > index) result.append(" ");
			result.append(this->get(i));
		}

		return result;
	}

	int params_sv::size()
	{
		return game::is_iw5() 
			? game::iw5::SV_Cmd_Argc() 
			: game::t6::SV_Cmd_Argc();
	}

	const char* params_sv::get(int index)
	{
		return game::is_iw5() 
			? game::iw5::SV_Cmd_Argv(index) 
			: game::t6::SV_Cmd_Argv(index);
	}

	std::string params_sv::join(int index)
	{
		std::string result = {};

		for (int i = index; i < this->size(); i++)
		{
			if (i > index) result.append(" ");
			result.append(this->get(i));
		}

		return result;
	}

	void add_raw(const char* name, void (*callback)())
	{
		game::Cmd_AddCommandInternal(name, callback, utils::memory::get_allocator()->allocate<game::cmd_function_t>());
	}

	void add(const char* name, std::function<void(params&)> callback)
	{
		const auto command = utils::string::to_lower(name);

		if (handlers.find(command) == handlers.end())
		{
			add_raw(name, main_handler);
		}

		handlers[command] = callback;
	}

	void add_sv(const char* name, std::function<void(int, params_sv&, std::function<void()>)> callback)
	{
		const auto command = utils::string::to_lower(name);

		handlers_sv[command] = callback;
	}

	namespace
	{
		void clientcommand_stub(int clientNum)
		{
			params_sv params;

			const auto command = utils::string::to_lower(params[0]);

			if (handlers_sv.find(command) != handlers_sv.end())
			{
				return handlers_sv[command](clientNum, params, [clientNum]()
				{
					clientcommand_hook.invoke<void>(clientNum);
				});
			}

			return clientcommand_hook.invoke<void>(clientNum);
		}
	}

	void init()
	{
		clientcommand_hook.create(game::ClientCommand, clientcommand_stub);
	}
}