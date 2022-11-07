#ifndef COMMUNICATION_HANDLER_HPP
#define COMMUNICATION_HANDLER_HPP
// Std includes
#include <cstdlib>
#include <iostream>
#include <mutex>

// Socket includes
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// Personal library includes
#include "./entities.hpp"

// Default start message
#define START_MESSAGE "#"

/*
 * @brief Class to handle all the communication between the game and 
 * the server
 */
class CommunicationHandler
{
    struct sockaddr_in serverAddress_;
    int socket_;
    std::mutex mutex_;

public:
    CommunicationHandler();
    ~CommunicationHandler();

    int const& socket(void);
    void connectWithServer(void);
    //void waitOpponent(Player&);
    void sendChange(std::string const&);
    void recieveChange(std::string&);
};
#endif
