#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <vector>
#include "entities.hpp"
#include <SDL2/SDL_ttf.h>

/*
 * @brief Class base for all the screens in the game.
 * Such class will hold all drawable elements of a screen,
 * as well as a method to draw them.
 */
class Screen
{
    std::vector<Drawable> elements_;

public:
    Screen() = default;
    Screen(std::vector<Drawable> const&);

    std::vector<Drawable>& elements(void);
    void draw(SDL_Renderer* const&);
};

/* A set o functions to initialize each screen */
std::vector<Drawable> menuScreenInit(int const&, int const&,
                                     SDL_Renderer*, TTF_Font*, SDL_Color const&);

#endif
