#ifndef COMMUNICATION_HANDLER_HPP
#define COMMUNICATION_HANDLER_HPP
#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "./entities.hpp"
#define OK "#"

class CommunicationHandler
{
    struct sockaddr_in serverAddress_;
    int socket_;

public:
    CommunicationHandler();
    ~CommunicationHandler();

    int const& socket(void);
    void connectWithServer(void);
    void waitOpponent(Player&);
    void sendChange(Player& , std::string const&);
    void receiveChange(Player&, std::string&);
};
#endif
