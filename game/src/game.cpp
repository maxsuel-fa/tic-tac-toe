/*
 * @file game.cpp
 * @brief Puts all the created elements together to form the actual game
 */

#include<iostream>
#include <cstdlib>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/screen.hpp"
#include "../include/screen_init.hpp"
#include "../include/communication_handler.hpp"

#define MENU 0
#define WAITING 1
#define PLAYING 3

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

    // Communication Handler
    CommunicationHandler cHandler;

    // Instantiating the screens of the game
    Screen menuScreen(menuScreenInit(windowWidth, windowHeight, renderer));
    Screen waitingScreen(waitingScreenInit(windowWidth, windowHeight, renderer));
    Screen playingScreen(playingScreenInit(windowWidth, windowHeight, renderer));

    // Player
    Player player;
    std::string recv, send;


    // Threads to send and receive changes
    std::thread tSend(&CommunicationHandler::sendChange, std::ref(cHandler),
                      std::ref(player), std::ref(send));
    std::thread tRecv(&CommunicationHandler::receiveChange, std::ref(cHandler),
                      std::ref(player), std::ref(recv));
    //std::thread tWait(&CommunicationHandler::waitOpponent, std::ref(cHandler),
    //                  std::ref(player));
    // Game loop
    SDL_bool close(SDL_FALSE);
    SDL_Event event;
    int xMouse, yMouse;
    int xAux, yAux;
    int gameStatus = MENU;

    while (!close)
    {
        // Dealing with events
        while (SDL_PollEvent(&event) && !close)
        {
            if (event.type == SDL_QUIT)
                close = SDL_TRUE;
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&xMouse, &yMouse);
                break;
            }
        }

        // Sending and receiving changes

        // Cleaning the screen
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(renderer);
        switch (gameStatus)
        {
        case MENU:
            xAux = menuScreen.elements()[2].x();
            yAux = menuScreen.elements()[2].y();
            if (xMouse > xAux
                    && xMouse < xAux + menuScreen.elements()[2].width()
                    && yMouse > yAux
                    && yMouse < yAux + menuScreen.elements()[2].height())
            {
                gameStatus = WAITING;
            }
            menuScreen.draw(renderer);
            break;
        case WAITING:
            if (player.playing)
            {
                //gameStatus = PLAYING;
            }
            std::cout << recv << std::endl;
            waitingScreen.draw(renderer, 500);
            break;
        case PLAYING:
            break;
        }
    }
}
