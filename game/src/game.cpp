/*
 * @file game.cpp
 * @brief Puts all the created elements together to form the actual game
 */

#include<iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/screen.hpp"
#include "../include/screen_init.hpp"
#include "../include/communication_handler.hpp"

// Screen options
#define MENU 0
#define WAITING 1
#define PLAYING 3
#define WIN 4
#define LOSS 5

// Standart messages
#define START_MESSAGE "#"
#define X_SYMBOL "X"
#define O_SYMBOL "O"

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



    // Instantiating the screens of the game
    Screen menuScreen(menuScreenInit(windowWidth, windowHeight, renderer));
    Screen waitingScreen(waitingScreenInit(windowWidth, windowHeight, renderer));
    Screen playingScreen(playingScreenInit(windowWidth, windowHeight, renderer));
    Screen winScreen(winScreenInit(windowWidth, windowHeight, renderer, "YOU WIN"));
    Screen lossScreen(winScreenInit(windowWidth, windowHeight, renderer, "YOU LOSE"));

    // Instantiating the player
    Player player;
    std::string recvm, sendm;

    // Communication Handler
    CommunicationHandler cHandler;
    cHandler.connectWithServer();

    // Threads to send and receive changes
    //std::thread tSend(&CommunicationHandler::sendChange, std::ref(cHandler),
    //                  std::ref(player), std::ref(sendm));
    //std::thread tRecv(&CommunicationHandler::receiveChange, std::ref(cHandler),
    //                  std::ref(player), std::ref(recvm));
    //std::thread tWait(&CommunicationHandler::waitOpponent, std::ref(cHandler),
    //                  std::ref(player));

    // Grid
    Matrix grid(3, 3);
    grid.zeros();

    // Game loop
    SDL_bool close(SDL_FALSE);
    SDL_Event event;
    int xMouse, yMouse;
    int xAux, yAux;
    int widthAux, heightAux;
    char auxMessage[256];
    std::pair<int, int> pos;
    int gameStatus = MENU;

    while (!close)
    {
        // Dealing with events
        while (SDL_PollEvent(&event) && !close)
        {
            if (event.type == SDL_QUIT)
                close = SDL_TRUE;
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                SDL_GetMouseState(&xMouse, &yMouse);
                std::cout << xMouse << " e " << yMouse << std::endl;
                break;
            }
        }

        // Cleaning the screen
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(renderer);
        switch (gameStatus)
        {
        // Menu screen
        case MENU:
            // Gets the start button coordinates and sizes
            xAux = menuScreen.elements()[2].x();
            yAux = menuScreen.elements()[2].y();
            widthAux = menuScreen.elements()[2].width();
            heightAux =  menuScreen.elements()[2].height();
            // Check if the start button was pressed
            if (xMouse > xAux && xMouse < xAux + widthAux
                    && yMouse > yAux && yMouse < yAux + heightAux)
            {
                // Sending a start message to the server
                sendm.clear();
                sendm.append(START_MESSAGE);
                send(cHandler.socket(), sendm.c_str(),
                     sizeof(sendm.c_str()), 0);

                // Receiving the player's symbol from the srver
                if (recv(cHandler.socket(), auxMessage,
                         sizeof(auxMessage), 0) >= 0)
                    player.symbol(auxMessage);

                if (!player.symbol().compare(X_SYMBOL)
                        || !player.symbol().compare(O_SYMBOL))
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
                if (!player.symbol().compare(X_SYMBOL))
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
            waitingScreen.draw(renderer, 500);
            break;
        case PLAYING:
            // Checking  moves made by the player
            pos = checkClick(xMouse, yMouse);
            if (pos.first >= 0 && pos.second >= 0
                    && grid.data()[pos.first][pos.second] == EMPTY)
            {
                //grid.data()[pos.first][pos.second] = player.symbol().c_str()[0];
                sendm.clear();
                sendm.append(player.symbol());
                sendm.append(std::to_string(pos.first));
                sendm.append(std::to_string(pos.second));
                //std::cout << sendm << std::endl;
            }

            // Updating the game grid based on the message received from the server
            if (recvm.size() && (recvm.c_str()[0] == 'X' || recvm.c_str()[0] == 'O'))
                grid.data()[recvm.c_str()[1] - '0'][recvm.c_str()[2] - '0'] = recvm.c_str()[0];

            // Checking for win/loss
            if (recvm.size() && recvm.c_str()[0] == 'W')
                gameStatus = WIN;
            else if (recvm.size() && recvm.c_str()[0] == 'L')
                gameStatus = LOSS;

            // Drawing all the symbols in the grid
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    xAux = playingScreen.elements()[0].x() + 200 * i + 14;
                    yAux = playingScreen.elements()[0].y() + 200 * j + 14;
                    if (grid.data()[i][j] == 'X')
                    {
                        X.x(xAux);
                        X.y(yAux);
                        X.width(160);
                        X.height(160);
                        X.draw(renderer);
                    }
                    else if (grid.data()[i][j] == 'O')
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
        case WIN:
            winScreen.draw(renderer);
            break;
        case LOSS:
            lossScreen.draw(renderer);
            break;
        }
    }

    return 0;
}
