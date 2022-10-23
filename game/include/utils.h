#ifndef UTILS_H
#define UTILS_H

template <typename T>
class Matrix
{
public:
    Matrix(int const&, int const&);

    int const& row(void) const;
    int const& column(void) const;
    void changeEntry(int const&, int const&, T const&);

private:
    int const row_;
    int const column_;
    T** data_;
};
#endif
