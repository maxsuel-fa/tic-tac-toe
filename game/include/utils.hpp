#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>

#define EMPTY '$'
#define GRID_START_X 92
#define GRID_START_Y 134
#define SUBGRID_WIDTH 190
#define LINE_WIDTH 0

class Matrix
{
public:
    Matrix(int const&, int const&);

    int const& row(void) const;
    int const& column(void) const;
    void changeEntry(int const&, int const&, char const&);
    char** data(void);
    void zeros(void);
private:
    int row_;
    int column_;
    char** data_;
};

void loadFont(TTF_Font**, std::string const&, int const&);
std::pair<int, int> checkClick(int const&, int const&);
#endif
