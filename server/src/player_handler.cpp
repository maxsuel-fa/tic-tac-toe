#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/player_handler.hpp"

PlayerHandler::PlayerHandler(void)
    : socket_(0) 
    , hasOpponent_(false) {}

void PlayerHandler::waitStartMessage(PlayerHandler& opponent)
{
    char receiver[256];

    do
    {
        recv(socket_, receiver, sizeof(receiver), 0);
    }
    while (strcmp(receiver, START_MESSAGE));

    std::string symbol;
    if (!hasOpponent_)
        symbol.append("X");
    else
        symbol.append("O");
    send(socket_, symbol.c_str(), sizeof(symbol.c_str()), 0);
    opponent.hasOpponent(true);
}

void PlayerHandler::socket(int const& socket)
{
    socket_ = socket;
}

int const& PlayerHandler::socket(void)
{
    return socket_;
}

void PlayerHandler::hasOpponent(bool const& hasOpponent)
{
    hasOpponent_ = hasOpponent;
}
