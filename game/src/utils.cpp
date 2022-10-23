#include "../include/utils.h"

/*
 * @brief Given a number of rows and a number of columns,
 * constructs a new matrix
 */
Matrix::Matrix(int const& row, int const& col) 
    : this->row_(row)
    , this->column_(column)
    , this->data_(new T*[row])
{
    for(int i = 0; i < row; ++i)
        data_[i] = new T[col];
}
/*
 * @brief Gets the number of rows of a Matrix
 * @return int const reference for the row attribute of the matrix
 */
int const& Matrix::row(void) { return this->row_; }

/*
 * @brief Gets the number of columns of a Matrix
 * @return int const reference for the column attribute of the matrix
 */
int const& Matrix::column(void) { return this->column_; }

/*
 * @brief Given the row and column of a matrix entry and a value,
 * assigns this value to such entry
 * @param row the row of the entry
 * @param col the column of the entry
 * @param newValue the value to be assigned
 */
void Matrix::changeEntry(int const& row, int const& col, T const& newValue)
{
    this->data_[row][col] = newValue;
}

