#include <thread>
#include "../include/communication_handler.hpp"
#include "../include/player_handler.hpp"


int main(void)
{
    // Instantiating a communication handler for the server
    CommunicationHandler cHandler;

    // For now, I will work only with one match, so only two
    // players will be instantiated
    PlayerHandler firstPlayer, secondPlayer;

    // Accepting the first player
    int firstPlayerSocket;
    firstPlayerSocket = cHandler.acceptClient();
    firstPlayer.socket(firstPlayerSocket);

    // Wating for the start message of the first player
    std::thread firstPWaitStart(&PlayerHandler::waitStartMessage, std::ref(firstPlayer), std::ref(secondPlayer));

    // Accepting the second player
    int secondPlayerSocket;
    secondPlayerSocket = cHandler.acceptClient();
    secondPlayer.socket(secondPlayerSocket);

    // Wating for the start message of the second player
    std::thread secondPWaitStart(&PlayerHandler::waitStartMessage,
                                 std::ref(secondPlayer), std::ref(firstPlayer));

    firstPWaitStart.join();
    secondPWaitStart.join();
    return 0;
}
