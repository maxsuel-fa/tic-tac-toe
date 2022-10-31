/*
 * @file game.cpp
 * @brief Puts all the created elements together to form the actual game
 */

#include<iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/screen.hpp"
#include "../include/screen_init.hpp"
int main(void)
{
    // Initializing the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized!" << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Creating a window
    SDL_Window* window(nullptr);
    std::string const windowCaption("Tic-Tac-Toe");
    int const windowWidth(784);
    int const windowHeight(868);
    window = SDL_CreateWindow(windowCaption.c_str(),
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "The window could not be created!" << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Creating the window renderer
    SDL_Renderer* renderer(nullptr);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "The renderer could not be created!" << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Initializing the SDL_image library
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "SDL_image could not be initialized!" << std::endl;
        std::cerr << "SDL Error: " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Initializing SDL_TTF
    if (TTF_Init() < 0)
    {
        std::cout << "SDL_ttf could not be initialized!" << std::endl;
        std::cerr << "SDL Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Instantiating the screens of the game
    Screen menuScreen(menuScreenInit(windowWidth, windowHeight, renderer));
    Screen waitingScreen(waitingScreenInit(windowWidth, windowHeight, renderer)); 
    // Game loop
    SDL_bool close(SDL_FALSE);
    SDL_Event event;
    while (!close)
    {
        while (SDL_PollEvent(&event) && !close)
            if (event.type == SDL_QUIT)
                close = SDL_TRUE;

        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(renderer);

        waitingScreen.draw(renderer, 500);

    }
}
