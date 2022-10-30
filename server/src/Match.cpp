#ifndef _MATCH_
#define _MATCH_

// C includes
#include <sys/socket.h>

// C++ includes
#include <string>

// Project includes
#include "../include/entities.hpp"

class Match {
public:
    // Class constructor. Receives two sockets, which are the players
    Match(int player1Socket, int player2Socket) {
        this->player1Socket = player1Socket;
        this->player2Socket = player2Socket;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) this->gameBoard[i][j] = EMPTY_SPACE;
        }

        this->gameHasEnded = 0;
    }

    // Class destructor.
    ~Match() {

    }

    // Getters
    int getPlayer1Socket() {
        return this->player1Socket;
    }

    int getPlayer2Socket() {
        return this->player2Socket;
    }

    // std::string getPlayer1Name() {
    //     return this->player1Name;
    // }

    // std::string getPlayer2Name() {
    //     return this->player2Name;
    // }

    void gameLoop() {
        int received;
        char move[5];   // String that describes the player move, with symbol
                        // (char), line and column. e.g.: "X32" => Symbol X, in
                        // line 3, column 2.
        int moveLine;   // Line in which the player has done his move
        int moveCol;    // Column in which the player has done his move
        int currentPlayer = 1; // Player that is playing currently
        int moveCount = 0;

        char winner;

        while(1) {
            switch(currentPlayer) {
                case 1:
                    received = recv(player1Socket, move, 5, 0);
                    moveLine = atoi(&move[1]);
                    moveCol = atoi(&move[2]);
                    this->gameBoard[moveLine][moveCol] = PLAYER_1;
                    moveCount++;
                    // The game can't finish with less than 5 moves (3 coming
                    // from one player, and 2 from his opponent)
                    if(moveCount > 4 && checkHasEnded(PLAYER_1) == PLAYER_1) {
                        winner = PLAYER_1;
                        gameHasEnded = 1;
                    }
                    currentPlayer = 2;
                    break;

                case 2:
                    received = recv(player2Socket, move, 5, 0);
                    moveLine = atoi(&move[1]);
                    moveCol = atoi(&move[2]);
                    this->gameBoard[moveLine][moveCol] = PLAYER_2;
                    // The game can't finish with less than 5 moves (3 coming
                    // from one player, and 2 from his opponent)
                    if(moveCount > 4 && checkHasEnded(PLAYER_2) == PLAYER_2) {
                        winner = PLAYER_2;
                        gameHasEnded = 1;
                    }
                    currentPlayer = 1;
                    break;

                default:
                    break;
            }

            if(gameHasEnded) {
                char gameOverMess[5]; // Game over message, to let the client
                                      // know if he has won or lost
                for(int i = 1; i < 5; i++) gameOverMess[i] = move[i - 1];
                if(winner = PLAYER_1) {
                    gameOverMess[0] = 'W'; // Player1 is the winner, so he will
                                           // receive a 'W' and the move
                    send(player1Socket, gameOverMess, 5, 0);

                    gameOverMess[0] = 'L'; // Player2 is the looser, so he will
                                           // receive a 'W' and the move
                    send(player2Socket, gameOverMess, 5, 0);
                } else {
                    gameOverMess[0] = 'L'; // In this case, Player1 is the looser,
                                           // so he will receive a 'W' and the move
                    send(player1Socket, gameOverMess, 5, 0);

                    gameOverMess[0] = 'W'; // Player2 is the winner, so he will
                                           // receive a 'W' and the move
                    send(player2Socket, gameOverMess, 5, 0);
                }
                
                break;
            }
            send(player1Socket, move, 5, 0);
            send(player2Socket, move, 5, 0);
        }

        return;
    }

    // Checks if the match has ended, considering the last move. If it has,
    // returns the symbol (char) of the winner. 
    char checkHasEnded(char player) {
        int i;
        if(player == PLAYER_1) {
            // Check lines
            for(i = 0; i < 3; i++) {
                if(
                    this->gameBoard[i][0] == PLAYER_1 &&
                    this->gameBoard[i][1] == PLAYER_1 &&
                    this->gameBoard[i][2] == PLAYER_1
                ) return PLAYER_1;
            }

            // Check columns
            for(i = 0; i < 3; i++) {
                if(
                    this->gameBoard[0][i] == PLAYER_1 &&
                    this->gameBoard[1][i] == PLAYER_1 &&
                    this->gameBoard[2][i] == PLAYER_1
                ) return PLAYER_1;
            }

            // Check diagonals
            if(
                this->gameBoard[0][0] == PLAYER_1 &&
                this->gameBoard[1][1] == PLAYER_1 &&
                this->gameBoard[2][2] == PLAYER_1
            ) return PLAYER_1;
            else if(
                this->gameBoard[0][2] == PLAYER_1 &&
                this->gameBoard[1][1] == PLAYER_1 &&
                this->gameBoard[2][0] == PLAYER_1
            ) return PLAYER_1;

            return EMPTY_SPACE;
        } else {
            // Check lines
            for(i = 0; i < 3; i++) {
                if(
                    this->gameBoard[i][0] == PLAYER_2 &&
                    this->gameBoard[i][1] == PLAYER_2 &&
                    this->gameBoard[i][2] == PLAYER_2
                ) return PLAYER_2;
            }

            // Check columns
            for(i = 0; i < 3; i++) {
                if(
                    this->gameBoard[0][i] == PLAYER_2 &&
                    this->gameBoard[1][i] == PLAYER_2 &&
                    this->gameBoard[2][i] == PLAYER_2
                ) return PLAYER_2;
            }

            // Check diagonals
            if(
                this->gameBoard[0][0] == PLAYER_2 &&
                this->gameBoard[1][1] == PLAYER_2 &&
                this->gameBoard[2][2] == PLAYER_2
            ) return PLAYER_2;
            else if(
                this->gameBoard[0][2] == PLAYER_2 &&
                this->gameBoard[1][1] == PLAYER_2 &&
                this->gameBoard[2][0] == PLAYER_2
            ) return PLAYER_2;

            return EMPTY_SPACE;
        }
    }

private:
    int player1Socket;
    int player2Socket;
    int gameHasEnded;
    char gameBoard[3][3];
};

#endif