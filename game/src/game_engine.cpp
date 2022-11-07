#include <string>
#include <thread>
#include <chrono>
// Personal library includes
#include "../include/game_engine.hpp"
#include "../include/communication_handler.hpp"

void Engine::run(std::mutex& mutex, int& xClick, int& yClick,
                 Game_GI& gi,
                 int& gameScreen,
                 bool& closeWindow)
{
    // Communication handler instance
    CommunicationHandler cHandler;
    cHandler.connectWithServer();

    // Player instance 
    Player player;

    // Sleep for one second so that the gi thread have time 
    // to initialize the screens
    std::this_thread::sleep_for (std::chrono::seconds(1));

    // Getting the position of the button
    int const startButtonX(gi.screens()[START_SCREEN].elements()[2].x());
    int const startButtonY(gi.screens()[START_SCREEN].elements()[2].y());
    int const startButtonWidth(gi.screens()[START_SCREEN].elements()[2].width());
    int const startButtonHeight(200);

    // String that represents the start message
    std::string const startMessage("#");
    
    // String to recieve changes
    std::string recvMessage;

    while (!closeWindow)
    {
        switch (gameScreen)
        {
        case START_SCREEN:
            mutex.lock();
            if (xClick > startButtonX
                    && xClick < startButtonX + startButtonWidth
                    && yClick > startButtonY
                    && yClick < startButtonY + startButtonHeight)
            {
                cHandler.sendChange(startMessage);
                cHandler.recieveChange(player.symbol());
                std::cout << player.symbol() << std::endl;
                if (!player.symbol().compare("X")
                        || !player.symbol().compare("O"))
                {
                    gameScreen = WAITING_SCREEN;
                }
            }
            mutex.unlock();
            break;
        case WAITING_SCREEN:
            cHandler.recieveChange(recvMessage);
            if (!recvMessage.compare(startMessage))
            {
                // Changing the screen
                mutex.lock();
                gameScreen = (!player.symbol().compare("X")) 
                             ? TRANSITION_SCREEN_PLAYER_X
                             : TRANSITION_SCREEN_PLAYER_O;
                mutex.unlock();
            }
            break;
        case PLAYING_SCREEN:
            break;
        }
    }
}


