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

#define EMPTY '$'

std::pair<int, int> checkClick(Drawable& grid,
                               int const& x, int const& y)
{
    std::pair<int, int> p(-1, -1);
    int const xAux((grid.x() + grid.width()) / 3);
    int const yAux((grid.y() + grid.height()) / 3);

    if (x > grid.x() && x < xAux)
    {
        p.first = 0;
        if (y > grid.y() && y < yAux)
            p.second = 0;
        else if (y > yAux && y < 2 * yAux)
            p.second = 1;
        else if (y > 2 * yAux && y < 3 * yAux)
            p.second = 2;
    }
    else if (x > xAux && x < 2 * xAux)
    {
        p.first = 1;
        if (y > grid.y() && y < yAux)
            p.second = 0;
        else if (y > yAux && y < 2 * yAux)
            p.second = 1;
        else if (y > 2 * yAux && y < 3 * yAux)
            p.second = 2;
    }
    else if (x > 2 * xAux && x < 3 * xAux)
    {
        p.first = 2;
        if (y > grid.y() && y < yAux)
            p.second = 0;
        else if (y > yAux && y < 2 * yAux)
            p.second = 1;
        else if (y > 2 * yAux && y < 3 * yAux)
            p.second = 2;
    }

    return p;
}
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

    // Creating a drawabel X
    std::string const XPath("../textures/xwhite.png");
    SDL_Texture* XTexture;
    XTexture = IMG_LoadTexture(renderer, XPath.c_str());

    // Defining coordinates and sizes for the X
    int const XWidth(56);
    int const XHeight(56);
    Drawable X(XTexture, 0, 0, XWidth, XHeight);

    // Creating a drawabel O
    std::string const OPath("../textures/owhite.png");
    SDL_Texture* OTexture;
    OTexture = IMG_LoadTexture(renderer, OPath.c_str());
    Drawable O(OTexture, 0, 0, XWidth, XHeight);

    // Communication Handler
    CommunicationHandler cHandler;
    cHandler.connectWithServer();

    // Instantiating the screens of the game
    Screen menuScreen(menuScreenInit(windowWidth, windowHeight, renderer));
    Screen waitingScreen(waitingScreenInit(windowWidth, windowHeight, renderer));
    Screen playingScreen(playingScreenInit(windowWidth, windowHeight, renderer));

    // Player
    Player player;
    std::string recv, sendm;

    // Threads to send and receive changes
    std::thread tSend(&CommunicationHandler::sendChange, std::ref(cHandler),
                      std::ref(player), std::ref(sendm));
    std::thread tRecv(&CommunicationHandler::receiveChange, std::ref(cHandler),
                      std::ref(player), std::ref(recv));
    std::thread tWait(&CommunicationHandler::waitOpponent, std::ref(cHandler),
                      std::ref(player));

    // Grid
    char grid[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            grid[i][j] = EMPTY;

    // Game loop
    SDL_bool close(SDL_FALSE);
    SDL_Event event;
    int xMouse, yMouse;
    int xAux, yAux;
    std::pair<int, int> pos;
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
                sendm.clear();
                sendm.append("#");
                send(cHandler.socket(), sendm.c_str(),
                     sizeof(sendm.c_str()), 0);
                gameStatus = WAITING;
            }
            menuScreen.draw(renderer);
            break;
        case WAITING:
            if (player.playing)
            {
                xAux = playingScreen.elements()[1].x()
                       + playingScreen.elements()[1].width() + 14;
                yAux = playingScreen.elements()[1].y() + 7;
                if (!player.symbol().compare("X"))
                {
                    X.x(xAux);
                    X.y(yAux);
                    playingScreen.elements().push_back(X);
                }
                else
                {
                    O.x(xAux);
                    O.y(yAux);
                    playingScreen.elements().push_back(O);
                }
                gameStatus = PLAYING;
            }
            //std::cout << player.playing << std::endl;
            waitingScreen.draw(renderer, 500);
            break;
        case PLAYING:
            pos = checkClick(playingScreen.elements()[0], xMouse, yMouse);
            if (pos.first > 0 && pos.second > 0 && grid[pos.first][pos.second] == EMPTY)
            {
                grid[pos.first][pos.second] = player.symbol().c_str()[0];
            }

            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    xAux = playingScreen.elements()[0].x() + 228 * i;
                    yAux = playingScreen.elements()[0].y() + 228 * j;
                    if (grid[i][j] == EMPTY)
                    {
                        X.x(xAux);
                        X.y(yAux);
                        X.width(160);
                        X.height(160);
                        X.draw(renderer);
                    }
                    else if (grid[i][j] == 'O')
                    {
                        O.x(xAux);
                        O.y(yAux);
                        O.width(160);
                        O.height(160);
                        O.draw(renderer);
                    }
                }
            }
            playingScreen.draw(renderer);
            break;
        }
    }

    return 0;
}
