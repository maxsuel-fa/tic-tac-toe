#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <string>

#define EMPTY '$'

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

#endif
