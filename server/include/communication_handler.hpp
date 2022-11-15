#ifndef COMMUNICATION_HANDLER_HPP
#define COMMUNICATION_HANDLER_HPP
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class CommunicationHandler
{
    int fileDescriptor_;
    struct sockaddr_in address_;

public:
    CommunicationHandler(void);
    int acceptClient(void);
};

#endif
