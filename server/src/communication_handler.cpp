#include <iostream>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "communication_handler.hpp"

CommunicationHandler::CommunicationHandler(void)
{

    fileDescriptor_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fileDescriptor_ < 0)
    {
        std::cerr << "Error in creating the server socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Prevent the bind error
    int opt = 1;
    int socketopt = setsockopt(
                        fileDescriptor_,
                        SOL_SOCKET,
                        SO_REUSEADDR | SO_REUSEPORT,
                        &opt,
                        sizeof(opt)
                    );

    // Setting the server addres
    address_.sin_family = AF_INET;
    address_.sin_port = htons(1234);
    address_.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&address_.sin_zero, 0, sizeof(address_.sin_zero));

    // Biding to the port
    if (bind(fileDescriptor_, (const sockaddr* )&address_, sizeof(address_)))
    {
        std::cerr << "Fail in bind the port" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(fileDescriptor_, 10) < 0)
    {
        std::cerr << "Fail in listenning initialization" << std::endl;
        exit(EXIT_FAILURE);
    }

}

int CommunicationHandler::acceptClient(void)
{
    int clientSocket;
    int addressLen(sizeof(address_));
    if ((clientSocket = accept(fileDescriptor_, (struct sockaddr* )&address_,
                               (socklen_t* )&addressLen)) < 0)
    {
        std::cerr << "Error in accepting the cliente" << std::endl;
        exit(EXIT_FAILURE);
    }

    return clientSocket;
}
