/*
 * @brief Methods to handle with the comunication between the
 * server and the game
 */

#include <cstdlib>
#include <unistd.h>
#include <mutex>
#include <chrono>
#include <thread>

#include "../include/communication_handler.hpp"

CommunicationHandler::CommunicationHandler(void)
{
    // Creating the client socket
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        std::cerr << "Error in creating the client socket!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Setting the server adrress
    serverAddress_.sin_family = AF_INET;
    serverAddress_.sin_port = htons(1234);
    serverAddress_.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&serverAddress_.sin_zero, 0, sizeof(serverAddress_.sin_zero));
}

CommunicationHandler::~CommunicationHandler()
{
    close(CommunicationHandler::socket_);
}

void CommunicationHandler::connectWithServer()
{
    std::cout << "Connecting with the server..." << std::endl;
    while (connect(socket_, (struct sockaddr* )&serverAddress_, sizeof(serverAddress_)) < 0)
    {
        std::cerr << "Error in connecting with the server" << std::endl;
        //exit(EXIT_FAILURE);
    }

    std::cout << "Success in connecting to the server!" << std::endl;
}

void CommunicationHandler::waitOpponent(Player& player)
{
    char aux[256];
    memset(&aux, 0, sizeof(aux));

    int nrecv;
    do
    {
        nrecv = recv(socket_, aux, sizeof(aux), 0);
        aux[nrecv] = '\0';
    }
    while (!strcmp(aux, "X") && !strcmp(aux, "O") && nrecv >= 0);

    if (nrecv < 0)
    {
        std::cerr << "Error in connecting with a second player" << std::endl;
        exit(EXIT_FAILURE);
    }

    player.symbol(aux);
    player.playing = true;
}

void CommunicationHandler::sendChange(Player& player, std::string const& change)
{
    // Just send valid changes
    while (!change.compare("invalid"));

    int nsent;
    while (player.playing)
    {
        nsent = send(socket_, change.c_str(), sizeof(change.c_str()), 0);
        if (nsent < 0)
        {
            std::cerr << "Erro in sending update" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void CommunicationHandler::receiveChange(Player& player, std::string& change)
{
    // Just for test
    std::mutex changeMutex;
    //char aux[256];
    //memset(&aux, 0, sizeof(aux));
    player.playing = true;
    int nrecv = 1;
    do
    {
        //nrecv = recv(socket_, aux, sizeof(aux), 0);
        //aux[nrecv] = '\0';
        if (nrecv > 0)
        {
            std::lock_guard<std::mutex> lock(changeMutex);
            change.clear();
            change.append("Test");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    while (player.playing);
}
