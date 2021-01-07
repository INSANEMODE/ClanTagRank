#pragma once

class function
{
public:
	static void add(const char* name, int min_args, int max_args, void(*f)());
	static game::BuiltinFunctionDef* find(const std::string& name);

	static void example_one();
	static void example_two();
	static void example_three();
	static void setclantag();

private:
	static std::unordered_map<std::string, game::BuiltinFunctionDef> registered_functions;
};