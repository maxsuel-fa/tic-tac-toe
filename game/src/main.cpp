#include "../include/entities.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>




int main(void)
{
    SDL_Renderer* renderer;
    SDL_Texture* t = IMG_LoadTexture(renderer, "../textures/tictactoe.png");
    Drawable d(t, 0, 0, 30, 30);
    return 0;
}
