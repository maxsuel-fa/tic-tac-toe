#include "../include/utils.hpp"
/*
 * @brief Given a number of rows and a number of columns,
 * constructs a new matrix
 */
Matrix::Matrix(int const& row, int const& col)
    : row_(row)
    , column_(col)
    , data_(new int*[row])
{
    for (int i = 0; i < row; ++i)
        Matrix::data_[i] = new int[col];
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

/*
 * @brief Given the row and column of a matrix entry and a value,
 * assigns this value to such entry
 * @param row the row of the entry
 * @param col the column of the entry
 * @param newValue the value to be assigned
 */
void Matrix::changeEntry(int const& row, int const& col, int const& newValue)
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
            changeEntry(i, j, 0);
}

/*
 * @brief Given a path and a size, open a ttf font with such size
 * @param fontPath path to the ttf font
 * @param fontSize size to the font
 * @return TTF_Font pointer to the opened font
 */
void loadFont(TTF_Font** font, std::string const& fontPath, int const& fontSize)
{
    *font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!*font)
    {
        std::cout << "The font could not be oppened!" << std::endl;
        std::cerr << "SDL Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}


