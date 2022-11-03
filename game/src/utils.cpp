
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

std::pair<int, int> checkClick(int const& x, int const& y)
{
    std::pair<int, int> p(-1, -1);

    if (x > GRID_START_X && x < GRID_START_X + SUBGRID_WIDTH)
    {
        p.first = 0;
        if (y > GRID_START_Y && y < GRID_START_Y + SUBGRID_WIDTH)
            p.second = 0;
        else if (y > GRID_START_Y + SUBGRID_WIDTH + LINE_WIDTH
                 && y < GRID_START_Y + 2 * SUBGRID_WIDTH)
            p.second = 1;
        else if (y > GRID_START_Y + 2 * (SUBGRID_WIDTH + LINE_WIDTH)
                 && y < GRID_START_Y + 3 * SUBGRID_WIDTH)
            p.second = 2;
    }
    else if (x >  GRID_START_X + SUBGRID_WIDTH + LINE_WIDTH
             && x < GRID_START_X + 2 * SUBGRID_WIDTH)
    {
        p.first = 1;
        if (y > GRID_START_Y && y < GRID_START_Y + SUBGRID_WIDTH)
            p.second = 0;
        else if (y > GRID_START_Y + SUBGRID_WIDTH + LINE_WIDTH
                 && y < GRID_START_Y + 2 * SUBGRID_WIDTH)
            p.second = 1;
        else if (y > GRID_START_Y + 2 * (SUBGRID_WIDTH + LINE_WIDTH)
                 && y < GRID_START_Y + 3 * SUBGRID_WIDTH)
            p.second = 2;
    }
    else if (x > GRID_START_X + 2 * (SUBGRID_WIDTH + LINE_WIDTH)
             && x < GRID_START_X + 3 * SUBGRID_WIDTH)
    {
        p.first = 2;
        if (y > GRID_START_Y && y < GRID_START_Y + SUBGRID_WIDTH)
            p.second = 0;
        else if (y > GRID_START_Y + SUBGRID_WIDTH + LINE_WIDTH
                 && y < GRID_START_Y + 2 * SUBGRID_WIDTH)
            p.second = 1;
        else if (y > GRID_START_Y + 2 * (SUBGRID_WIDTH + LINE_WIDTH)
                 && y < GRID_START_Y + 3 * SUBGRID_WIDTH)
            p.second = 2;
    }

    return p;
}
