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

Match *createMatch(int player1Socket, int player2Socket)
{
    char message[2];
    message[1] = '\0';

    message[0] = PLAYER_1;
    send(player1Socket, message, 2, 0);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    message[0] = PLAYER_2;
    send(player2Socket, message, 2, 0);

    Match *gameMatch = new Match(player1Socket, player2Socket);

    return gameMatch;
}
