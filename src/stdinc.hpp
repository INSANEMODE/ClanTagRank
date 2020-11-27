#pragma once

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

using namespace std::literals;

#include "utils/string.hpp"
#include "utils/hook.hpp"
#include "utils/memory.hpp"

#include "game/structs.hpp"
#include "game/game.hpp"
#include "game/chaiscript/chaiscript.hpp"

#include "component/command.hpp"
#include "component/chat.hpp"
#include "component/userinfo.hpp"

#define SELECT_VALUE(t6mp, t6zm, iw5mp) (game::is_t6mp() ? (t6mp) : game::is_t6zm() ? (t6zm) : (iw5mp))

