#pragma once
#define CURL_STATICLIB
#pragma warning(disable: 4244)
#pragma warning(disable: 26812)

#define DLL_EXPORT extern "C" __declspec(dllexport)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <vector>
#include <cassert>
#include <mutex>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <regex>

#include <MinHook.h>


#include <array>
#include <stdint.h>
#include <stdio.h>
#include <corecrt_io.h>
#include <fstream>
#include <winternl.h>
#include <memory>
#include <direct.h>
#include <map>
#include <chrono>
#include <cctype>
#include <ctime>
#include <math.h>
#include <unordered_map>
#include <deque>

using namespace std::literals;
#pragma warning(disable: 6011)
#pragma warning(disable: 6054)
#pragma warning(disable: 26451)
#pragma warning(disable: 26812)
#pragma warning(disable: 28182)

#include "utils/memory.hpp"
#include "utils/string.hpp"
#include "utils/hook.hpp"

#include "game/structs.hpp"
#include "game/game.hpp"
#include "game/chaiscript/chaiscript.hpp"

#include "component/command.hpp"
#include "component/chat.hpp"
#include "component/userinfo.hpp"

#include "game/functions.hpp"
#include "gsc/gsc.hpp"
#include "gsc/functions.hpp"


#define SELECT_VALUE(t6mp, t6zm, iw5mp) (game::is_t6mp() ? (t6mp) : game::is_t6zm() ? (t6zm) : (iw5mp))

void set_clan_tag(int clientNum, std::string clantag);

