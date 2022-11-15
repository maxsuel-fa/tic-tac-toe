#ifndef PLAYER_HANDLER_HPP
#define PLAYER_HANDLER_HPP
#define START_MESSAGE "#"

class PlayerHandler
{   
    int socket_;
    bool hasOpponent_;
    std::string symbol_;
public:
    PlayerHandler(void);
    void waitStartMessage(PlayerHandler&);
    void socket(int const&);
    int const& socket(void);
    void hasOpponent(bool const&);
    bool const& hasOpponent(void);
    std::string const& symbol(void);
    void symbol(std::string const&);
};
#endif
