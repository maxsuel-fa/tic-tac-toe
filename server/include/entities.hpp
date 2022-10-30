#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#define PLAYER_1 'X'
#define PLAYER_2 'O'
#define EMPTY_SPACE ' '

class Match {
public:
    Match(int, int);
    ~Match();

    // Getters
    int getPlayer1Socket();
    int getPlayer2Socket();
    // std::string getPlayer1Name();
    // std::string getPlayer2Name();
    void gameLoop();
    char checkHasEnded(char player);

private:
    int player1Socket;
    int player2Socket;
    // std::string player1Name;
    // std::string player2Name;
    int gameHasEnded;
    char gameBoard[3][3];
};

#endif