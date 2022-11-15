#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/player_handler.hpp"

PlayerHandler::PlayerHandler(void)
    : socket_(0) 
    , hasOpponent_(false)
    , symbol_("") {}

void PlayerHandler::waitStartMessage(PlayerHandler& opponent)
{
    char receiver[256];

    do
    {
        recv(socket_, receiver, sizeof(receiver), 0);
    }
    while (strcmp(receiver, START_MESSAGE));

    if (!hasOpponent_)
        symbol_.append("X");
    else
        symbol_.append("O");
    send(socket_, symbol_.c_str(), sizeof(symbol_.c_str()), 0);
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

bool const& PlayerHandler::hasOpponent(void)
{
    return hasOpponent_;
}

std::string const& PlayerHandler::symbol(void)
{
    return symbol_;
}

void PlayerHandler::symbol(std::string const& symbol)
{
    symbol_ = symbol;
}
