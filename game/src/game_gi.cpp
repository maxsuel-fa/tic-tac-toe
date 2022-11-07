// Std includes
#include <chrono>
#include <thread>
#include <cstdlib>
// SDL includes
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Personal includes
#include "../include/game_gi.hpp"

Game_GI::Game_GI(void)
    : windowWidth_(784)
    , windowHeight_(868)
    , window_(nullptr)
    , renderer_(nullptr)
    , screens_()
{
    // Initializing the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized!" << std::endl;
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
}


int const& Game_GI::windowWidth(void)
{
    return windowWidth_;
}

int const& Game_GI::windowHeight(void)
{
    return windowHeight_;
}

SDL_Renderer*& Game_GI::renderer(void)
{
    return renderer_;
}

std::vector<Screen>& Game_GI::screens(void)
{
    return screens_;
}

void Game_GI::run(std::mutex& mutex, int& gameScreen,
                  int& xClick, int& yClick,
                  bool& closeWindow)
{
    /*int const startButtonX(screens_[0].elements()[2].x());
    int const startButtonY(screens_[0].elements()[2].y());
    int const startButtonWidth(screens_[0].elements()[2].width());
    int const startButtonHeight(200);

    while(!(mouseX > startButtonX && mouseX < startButtonX + startButtonWidth
            && mouseY > startButtonY && mouseY < startButtonY + startButtonHeight))
    {
        screens_[0].draw(renderer_);
    }
    */
    window_ = SDL_CreateWindow("Tic-Tac-Toe",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               windowWidth_,
                               windowHeight_,
                               SDL_WINDOW_OPENGL);
    if (!window_)
    {
        std::cout << "The window could not be created!" << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    renderer_ = SDL_CreateRenderer(window_, -1,
                                   SDL_RENDERER_ACCELERATED);
    if (!renderer_)
    {
        std::cout << "The renderer could not be created!" << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Instantiating the screens of the game
    Screen startScreen(menuScreenInit(windowWidth_, windowHeight_, renderer_));
    Screen waitingScreen(waitingScreenInit(windowWidth_, windowHeight_, renderer_));
    Screen playingScreen(playingScreenInit(windowWidth_, windowHeight_, renderer_));
    Screen winnerScreen(winScreenInit(windowWidth_, windowHeight_, renderer_, "YOU WIN"));
    Screen loserScreen(winScreenInit(windowWidth_, windowHeight_, renderer_, "YOU LOSE"));

    screens_.push_back(startScreen);
    screens_.push_back(waitingScreen);
    screens_.push_back(playingScreen);
    screens_.push_back(winnerScreen);
    screens_.push_back(loserScreen);

    while (!closeWindow)
    {
        mutex.lock();
        eventHandler(xClick, yClick, closeWindow);
        // Cleaning the screen
        SDL_SetRenderDrawColor(renderer_, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(renderer_);
        switch (gameScreen)
        {
        case START_SCREEN:
            screens_[START_SCREEN].draw(renderer_);
            break;
        case WAITING_SCREEN:
            screens_[WAITING_SCREEN].draw(renderer_, 500);
            break;
        case TRANSITION_SCREEN_PLAYER_X:
            // Inserting the player's symbol in the playing screen
            screens_[PLAYING_SCREEN].elements().push_back(symbol("X"));
            gameScreen = PLAYING_SCREEN;
            break;
        case TRANSITION_SCREEN_PLAYER_O:
            // Inserting the player's symbol in the playing screen
            screens_[PLAYING_SCREEN].elements().push_back(symbol("O"));
            gameScreen = PLAYING_SCREEN;
            break;
        case PLAYING_SCREEN:
            screens_[PLAYING_SCREEN].draw(renderer_);
            break;
        case WINNER_SCREEN:
            screens_[WINNER_SCREEN].draw(renderer_);
            break;
        case LOSER_SCREEN:
            screens_[LOSER_SCREEN].draw(renderer_);
            break;
        }
        mutex.unlock();
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }
}

void Game_GI::eventHandler(int& xClick, int& yClick, bool& closeWindow)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) && !closeWindow)
    {
        if (event.type == SDL_QUIT)
            closeWindow = true;
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            SDL_GetMouseState(&xClick, &yClick);
            break;
        }
    }
}

Drawable Game_GI::symbol(std::string const& symbol)
{
    // Coordinates for the symbol
    int const x(screens_[PLAYING_SCREEN].elements()[1].x()
                + screens_[PLAYING_SCREEN].elements()[1].width()
                + 14);
    int const y(screens_[PLAYING_SCREEN].elements()[1].y() + 14);

    // Path to the png of the symbol
    std::string path;
    if (!symbol.compare("X"))
    {
        path.append("../textures/xwhite.png");
    }
    else
    {
        path.append("../textures/owhite.png");
    }
    SDL_Texture* texture;
    texture = IMG_LoadTexture(renderer_, path.c_str());
    return Drawable(texture, x, y, 56, 56);
}
