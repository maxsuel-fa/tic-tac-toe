#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <mutex>

#include "../include/game_gi.hpp"

namespace Engine
{
void run(std::mutex&, int&, int&,
         Game_GI&, int&, bool&);
}

#endif
