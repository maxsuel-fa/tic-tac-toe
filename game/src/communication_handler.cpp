/*
 * @brief Methods to handle with the comunication between the
 * server and the game
 */
#include <unistd.h>
#include <chrono>
#include <thread>

#include "../include/communication_handler.hpp"

CommunicationHandler::CommunicationHandler(void)
{
    // Creating the client socket
    socket_ = ::socket(AF_INET, SOCK_STREAM, 0);
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

int const& CommunicationHandler::socket()
{
    return socket_;
}

void CommunicationHandler::connectWithServer()
{
    std::cout << "Connecting with the server..." << std::endl;
    while (connect(socket_, (struct sockaddr* )&serverAddress_, sizeof(serverAddress_)) < 0)
    {
        std::cerr << "Error in connecting with the server" << std::endl;
        std::cout << "Trying to connect again..." << std::endl;
    }

    std::cout << "Success in connecting to the server!" << std::endl;
}

/*void CommunicationHandler::waitOpponent(std::mutex mutex, Player& player)
{
    char reciever[5];
    memset(&reciever, 0, sizeof(reciever));
    do
    {
        recv(socket_, reciever, sizeof(reciever), 0);
    }
    while (strcmp(reciever, START_MESSAGE));
    player.playing = true;
}*/

void CommunicationHandler::sendChange(std::string const& sendm)
{
    send(socket_, sendm.c_str(), sizeof(sendm.c_str()), 0);
}

void CommunicationHandler::recieveChange(std::string& recvm)
{
    char reciever[5];
    memset(&reciever, 0, sizeof(reciever));
    recv(socket_, reciever, sizeof(reciever), 0);
    recvm.clear();
    recvm.append(reciever);
}

