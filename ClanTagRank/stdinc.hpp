#pragma once

#pragma warning(disable: 26812)

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

#include "utils/string.hpp"
#include "utils/hook.hpp"
#include "utils/memory.hpp"

#include "game/structs.hpp"
#include "game/game.hpp"

#include "command/command.hpp"

#include "userinfo/userinfo.hpp"

#define SELECT_VALUE(t6mp, t6zm, iw5mp) (game::is_t6mp() ? (t6mp) : game::is_t6zm() ? (t6zm) : (iw5mp))

