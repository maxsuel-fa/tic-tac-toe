#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>

class Matrix
{
public:
    Matrix(int const&, int const&);

    int const& row(void) const;
    int const& column(void) const;
    void changeEntry(int const&, int const&, int const&);
    void zeros(void);
private:
    int row_;
    int column_;
    int** data_;
};

void loadFont(TTF_Font**, std::string const&, int const&);
#endif
