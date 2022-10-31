// C includes
#include <sys/socket.h>

// C++ includes
#include <string>
#include <cstring>
#include <chrono>
#include <thread>

// Project includes
#include "../include/entities.hpp"
#define OK "#"

Match *createMatch(int socketPlayer1, int socketPlayer2)
{
    char message[2];
    message[1] = '\0';

    message[0] = PLAYER_1;
    send(socketPlayer1, message, 2, 0);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    message[0] = PLAYER_2;
    send(socketPlayer2, message, 2, 0);

    Match *gameMatch = new Match(socketPlayer1, socketPlayer2);

    return gameMatch;
}
