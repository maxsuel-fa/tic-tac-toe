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
    // String to send and receive changes
    std::string message;
    // Thread to receive changes
    std::mutex message_mu;
    std::thread receiveThread(&CommunicationHandler::recieveChange,
                              std::ref(cHandler), std::ref(message_mu),
                              std::ref(message), std::ref(closeWindow));

    // Game's grid data structure
    Matrix grid(3, 3);
    grid.zeros();

    // Click position checker
    std::pair<int, int> clickPosCheck;

    while (!closeWindow)
    {
        mutex.lock();
        switch (gameScreen)
        {
        case START_SCREEN:
            if (xClick > startButtonX
                    && xClick < startButtonX + startButtonWidth
                    && yClick > startButtonY
                    && yClick < startButtonY + startButtonHeight)
            {
                cHandler.sendChange(startMessage);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                player.symbol(message);
                std::cout << player.symbol() << std::endl;
                if (!player.symbol().compare("X")
                        || !player.symbol().compare("O"))
                {
                    gameScreen = WAITING_SCREEN;
                }
            }
            break;
        case WAITING_SCREEN:
            std::cout << message << std::endl;
            if (!message.compare(startMessage))
            {
                // Changing the screen
                gameScreen = (!player.symbol().compare("X"))
                             ? TRANSITION_SCREEN_PLAYER_X
                             : TRANSITION_SCREEN_PLAYER_O;
            }
            break;
        case PLAYING_SCREEN:
            clickPosCheck = checkClick(xClick,  yClick);
            if (clickPosCheck.first > 0
                    && clickPosCheck.second > 0
                    && grid.data()[clickPosCheck.first][clickPosCheck.second] == EMPTY)
            {
                message_mu.lock();
                message.clear();
                message.append(player.symbol());
                message.append(std::to_string(clickPosCheck.first));
                message.append(std::to_string(clickPosCheck.second));
                cHandler.sendChange(message);
                message_mu.unlock();
            }

            // Receiving changes in the grid
            if (message.size() > 2
                    && (message[0] == 'X' || message[0] == 'O'))
            {
                grid.changeEntry(message[1] - '0',  message[2] - '0',
                                 message[0]);
                gameScreen = (message[0] == 'X')
                             ? UPDATE_SCREEN_X
                             : UPDATE_SCREEN_O;
                xClick = gi.screens()[PLAYING_SCREEN].elements()[0].x()
                         + 200 * (message[1] - '0');
                yClick = gi.screens()[PLAYING_SCREEN].elements()[0].y()
                         + 200 * (message[2] - '0');
            }
            break;
        }
        mutex.unlock();
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }
}
