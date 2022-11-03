#ifndef PLAYER_HANDLER_HPP
#define PLAYER_HANDLER_HPP
#define START_MESSAGE "#"

class PlayerHandler
{   
    int socket_;
    bool hasOpponent_;
public:
    PlayerHandler(void);
    void waitStartMessage(PlayerHandler&);
    void socket(int const&);
    int const& socket(void);
    void hasOpponent(bool const&);

};
#endif
