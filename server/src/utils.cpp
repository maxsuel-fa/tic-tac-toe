
#include "../include/utils.hpp"
/*
 * @brief Given a number of rows and a number of columns,
 * constructs a new matrix
 */
Matrix::Matrix(int const& row, int const& col)
    : row_(row)
    , column_(col)
    , data_(new char*[row])
{
    for (int i = 0; i < row; ++i)
        Matrix::data_[i] = new char[col];
}

/*
 * @brief Gets the number of rows of a Matrix
 * @return int const reference for the row attribute of the matrix
 */
int const& Matrix::row(void) const
{
    return row_;
}

/*
 * @brief Gets the number of columns of a Matrix
 * @return int const reference for the column attribute of the matrix
 */
int const& Matrix::column(void) const
{
    return column_;
}

char** Matrix::data(void)
{
    return data_;
}
/*
 * @brief Given the row and column of a matrix entry and a value,
 * assigns this value to such entry
 * @param row the row of the entry
 * @param col the column of the entry
 * @param newValue the value to be assigned
 */
void Matrix::changeEntry(int const& row, int const& col, char const& newValue)
{
    data_[row][col] = newValue;
}

/*
 * @brief fill a matrix with zeros
 */
void Matrix::zeros(void)
{
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            changeEntry(i, j, EMPTY);
}

