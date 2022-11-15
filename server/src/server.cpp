#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include "../include/communication_handler.hpp"
#include "../include/player_handler.hpp"
#include "../include/utils.hpp"

// Player turn macros
#define FIRST_PLAYER_TURN 1
#define SECOND_PLAYER_TURN 2

// Symbols macros
#define X_SYMBOL 'X'
#define O_SYMBOL 'O'

// Default messages
#define QUIT "Q"
#define WIN 'W'
#define LOSS 'L'

#define MESSAGE_SIZE 4

// Function to check if a player has won
bool won(std::string const&, Matrix&);

int main(void)
{
    // Instantiating a communication handler for the server
    CommunicationHandler cHandler;

    // For now, I will work only with one match, so only two
    // players will be instantiated
    PlayerHandler firstPlayer, secondPlayer;

    // Accepting the first player
    int firstPlayerSocket;
    firstPlayerSocket = cHandler.acceptClient();
    firstPlayer.socket(firstPlayerSocket);

    // Wating for the start message of the first player
    std::thread firstPWaitStart(&PlayerHandler::waitStartMessage, 
                                std::ref(firstPlayer), 
                                std::ref(secondPlayer));

    // Accepting the second player
    int secondPlayerSocket;
    secondPlayerSocket = cHandler.acceptClient();
    secondPlayer.socket(secondPlayerSocket);

    // Wating for the start message of the second player
    std::thread secondPWaitStart(&PlayerHandler::waitStartMessage,
                                 std::ref(secondPlayer), std::ref(firstPlayer));


    while (!firstPlayer.hasOpponent() || !secondPlayer.hasOpponent())
    {
        std::cout << "Waiting for two players to start a match" << std::endl;
    }

    // If there are two players in the waiting mode, send a start match
    // message for both of them
    std::string startMessage(START_MESSAGE);
    send(firstPlayer.socket(), startMessage.c_str(),
         sizeof(startMessage.c_str()), 0);
    send(secondPlayer.socket(), startMessage.c_str(),
         sizeof(startMessage.c_str()), 0);

    // Game loop
    Matrix grid(3, 3);
    grid.zeros();
    bool playing(true);
    int turn(FIRST_PLAYER_TURN);
    char move[MESSAGE_SIZE];

    while (playing)
    {
        switch (turn)
        {
        case FIRST_PLAYER_TURN:
            recv(firstPlayer.socket(), move, sizeof(move), 0);
            std::cout << "1: " << move << std::endl;
            // If the recieved message is a move, updates the grid
            if (move[0] == X_SYMBOL || move[0] == O_SYMBOL)
            {
                //grid.changeEntry(atoi(&move[1]), atoi(&move[2]), move[0]);
                // Send the change for both of the players
                send(firstPlayer.socket(), move, sizeof(move), 0);
                send(secondPlayer.socket(), move, sizeof(move), 0);
            }
            // If the first player quit, the second wins
            if (!strcmp(move, QUIT))
            {
                playing = false;
                move[0] = WIN;
                send(secondPlayer.socket(), move, sizeof(move), 0);
                break;
            }

            // Check if the first player won
            if (won(firstPlayer.symbol(), grid))
            {
                playing = false;

                // Send win message to the first player
                move[0] = WIN;
                send(firstPlayer.socket(), move, sizeof(move), 0);
                // Send loss message to the second player
                move[0] = LOSS;
                send(secondPlayer.socket(), move, sizeof(move), 0);
                break;
            }
            turn = SECOND_PLAYER_TURN;
            break;
        case SECOND_PLAYER_TURN:
            recv(secondPlayer.socket(), move, sizeof(move), 0);
            std::cout << "2: " << move << std::endl;
            // If the recieved message is a move, updates the grid
            if (move[0] == X_SYMBOL || move[0] == O_SYMBOL)
            {
                //grid.changeEntry(atoi(&move[1]), atoi(&move[2]), move[0]);
                // Send the change for both of the players
                send(firstPlayer.socket(), move, sizeof(move), 0);
                send(secondPlayer.socket(), move, sizeof(move), 0);
            }
            // If the second player quit, the first wins
            if (!strcmp(move, QUIT))
            {
                playing = false;
                move[0] = WIN;
                send(firstPlayer.socket(), move, sizeof(move), 0);
                break;
            }

            // Check if the second player won
            if (won(secondPlayer.symbol(), grid))
            {
                playing = false;

                // Send win message to the second player
                move[0] = WIN;
                send(secondPlayer.socket(), move, sizeof(move), 0);
                // Send loss message to the first player
                move[0] = LOSS;
                send(firstPlayer.socket(), move, sizeof(move), 0);
                break;
            }
            turn = FIRST_PLAYER_TURN;
            break;
        }
    }
    firstPWaitStart.join();
    secondPWaitStart.join();
    return 0;
}

bool won(std::string const& symbol, Matrix& grid)
{
    // Checking lines
    for (int i = 0; i < 3; ++i)
    {
        if (grid.data()[i][0] == symbol[0]
                && grid.data()[i][1] == symbol[0]
                && grid.data()[i][2] == symbol[0])
            return true;
    }

    // Checking columns
    for (int i = 0; i < 3; ++i)
    {
        if (grid.data()[0][i] == symbol[0]
                && grid.data()[1][i] == symbol[0]
                && grid.data()[2][i] == symbol[0])
            return true;
    }

    // Checking main diagonal
    if (grid.data()[0][0] == symbol[0]
            && grid.data()[1][1] == symbol[0]
            && grid.data()[2][2] == symbol[0])
        return true;

    // Checking second diagonal
    if (grid.data()[0][2] == symbol[0]
            && grid.data()[1][1] == symbol[0]
            && grid.data()[2][0] == symbol[0])
        return true;

    return false;
}
