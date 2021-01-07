#pragma once

class method
{
public:
	static void add(const char* name, int min_args, int max_args, void(*f)(game::scr_entref_t));
	static game::BuiltinMethodDef* find(const std::string& name);

	static void example_one(game::scr_entref_t entref);
	static void example_two(game::scr_entref_t entref);
	static void example_three(game::scr_entref_t entref);

private:
	static std::unordered_map<std::string, game::BuiltinMethodDef> registered_methods;
};