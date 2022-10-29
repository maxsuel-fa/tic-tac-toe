// C includes
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

// C++ includes
#include <iostream>
#include <thread>

// Global variables
struct sockaddr_in address;

int main(int argc, char *argv[]) {
    std::cout << "Bem-vindo ao Tic-Tac-Toe! :)" << std::endl;
    std::cout << std::endl << "Servidor inicializado!" << std::endl;
    // AF_INET for IPV4, SOCK_STREAM for reliable protocol (TCP) and
    // protocol = 0 [protocol value for Internet Protocol (IP)]
    int socketd = socket(AF_INET, SOCK_STREAM, 0); // socketd = socket descriptor

    if(socketd == -1) {
        std::cout << std::endl << "Erro ao criar socket!" << std::endl;
    }

    address.sin_family = AF_INET; // Address family
    address.sin_port = htons(1234); // Port number
    address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY binds the server
                                          // to the local host


    if(bind(socketd, (struct sockaddr*) &address, sizeof(address)) == -1) {
        std::cout << std::endl << "Erro ao fazer o bind() com a porta!" << std::endl;
        return 1;
    }

    // Accepts, at the most, 10 pending connections
    if(listen(socketd, 10) == -1) {
        printf("\nErro na funcao listen()!\n");
        return 1;
    }

    std::cout << "Servidor escutando, aguardando pela conexão de clientes..." << std::endl;

    int client_socket = accept(socketd, 0, 0);

    if(client_socket == -1) {
        std::cout << std::endl << "Erro na funcao accept()" << std::endl;
        return 1;
    }

    shutdown(socketd, SHUT_RDWR); // Closes the listening socket

    return 0;
}