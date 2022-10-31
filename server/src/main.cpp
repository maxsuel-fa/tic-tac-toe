// C includes
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

// C++ includes
#include <iostream>
#include <thread>
#include <cstring>

#include "../include/entities.hpp"
#include "../include/utils.hpp"

#define OK "#"
// Global variables
struct sockaddr_in address;
int matchesCount;

int main(int argc, char *argv[])
{
    std::cout << "Bem-vindo ao Tic-Tac-Toe! :)" << std::endl;
    std::cout << std::endl << "Servidor inicializado!" << std::endl;
    // AF_INET for IPV4, SOCK_STREAM for reliable protocol (TCP) and
    // protocol = 0 [protocol value for Internet Protocol (IP)]
    int socketd = socket(AF_INET, SOCK_STREAM, 0); // socketd = socket descriptor

    if (socketd == -1)
    {
        std::cout << std::endl << "Erro ao criar socket!" << std::endl;
        return 1;
    }

    int opt = 1;
    int socketopt = setsockopt(
                        socketd,
                        SOL_SOCKET,
                        SO_REUSEADDR | SO_REUSEPORT,
                        &opt,
                        sizeof(opt)
                    );

    if (socketopt == -1)
    {
        std::cout << std::endl << "Erro ao configurar o socket!" << std::endl;
    }

    address.sin_family = AF_INET; // Address family
    address.sin_port = htons(1234); // Port number
    address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY binds the server
    // to the local host


    if (bind(socketd, (struct sockaddr*) &address, sizeof(address)) == -1)
    {
        std::cout << std::endl << "Erro ao fazer o bind() com a porta!" << std::endl;
        return 1;
    }

    // Accepts, at the most, 10 pending connections
    if (listen(socketd, 10) == -1)
    {
        printf("\nErro na funcao listen()!\n");
        return 1;
    }

    std::cout << "Servidor escutando, aguardando pela conexão de clientes...";
    std::cout << std::endl;

    Match *matches[10];      // Game matches
    std::thread threads[10]; // Threads that will run the game matches

    int player1Socket;
    int player2Socket;

    matchesCount = 0;

    while (1)
    {
        std::cout << std::endl;
        std::cout << "Partida " <<  matchesCount << ": Aguardando pela conexão do Player1";
        std::cout << std::endl;

        player1Socket = accept(socketd, 0, 0);

        std::cout << std::endl;
        std::cout << "Partida " <<  matchesCount << ": Aguardando pela conexão do Player2";
        std::cout << std::endl;

        player2Socket = accept(socketd, 0, 0);

        if (player1Socket == -1 || player2Socket == -1)
        {
            std::cout << std::endl << "Erro na funcao accept()" << std::endl;
            return 1;
        }

        if (matchesCount < 10)
        {
            matches[matchesCount] = createMatch(player1Socket, player2Socket);
            threads[matchesCount] = std::thread(&Match::gameLoop, std::ref(matches[matchesCount]));
            matchesCount++;
        }
    }

    shutdown(socketd, SHUT_RDWR); // Closes the listening socket

    return 0;
}
