#ifndef GAME_GI_HPP
#define GAME_GI_HPP

// Std includes
#include <vector>
#include <mutex>
// SDL include
#include <SDL2/SDL.h>

// Personal library includes
#include "../include/screen.hpp"
#include "../include/entities.hpp"

// Macros for the screens of the game
#define START_SCREEN   0
#define WAITING_SCREEN 1
#define PLAYING_SCREEN 2
#define TRANSITION_SCREEN_PLAYER_X 3
#define TRANSITION_SCREEN_PLAYER_O 4
#define WINNER_SCREEN  5
#define LOSER_SCREEN   6

class Game_GI
{
    SDL_Window* window_;
    int windowWidth_;
    int windowHeight_;
    SDL_Renderer* renderer_;
    std::vector<Screen> screens_;

public:
    Game_GI(void);
    int const& windowWidth(void);
    int const& windowHeight(void);
    SDL_Renderer*& renderer(void);
    std::vector<Screen>& screens(void);
    void run(std::mutex&, int&, int&, int&, bool&);
    void eventHandler(int&, int&, bool&);
    Drawable symbol(std::string const&);
};
#endif
