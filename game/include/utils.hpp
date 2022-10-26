#ifndef UTILS_HPP
#define UTILS_HPP

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
#endif
