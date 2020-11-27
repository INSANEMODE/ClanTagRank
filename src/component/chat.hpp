#pragma once

namespace chat
{
	void tellraw(int clientNum, std::string message);
	void sayraw(std::string message);

	void add(const char*, std::function<void(int, command::params_sv&, std::function<void()>)> callback);
	void init();
}