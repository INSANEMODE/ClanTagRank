#pragma once

namespace userinfo
{
	void add(std::string, std::function<const char* (const char*, const char*, const char*, int)>);
	void init();
}