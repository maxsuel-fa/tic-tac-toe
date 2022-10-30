// C includes
#include <sys/socket.h>

// C++ includes
#include <string>

// Project includes
#include "../include/entities.hpp"

Match *createMatch(int socketPlayer1, int socketPlayer2) {
    char message[2];
    message[1] = '\0';

    message[0] = PLAYER_1;
    send(socketPlayer1, message, 2, 0);

    message[0] = PLAYER_2;
    send(socketPlayer2, message, 2, 0);

    Match *gameMatch = new Match(socketPlayer1, socketPlayer2);

    return gameMatch;
}