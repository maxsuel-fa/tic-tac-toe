#include "../include/entities.hpp"

/* Implementation of the methods of the Drawable class */

Drawable::Drawable(SDL_Texture* const& texture,
                   int const& x, int const& y,
                   int const& width, int const& height)
    : texture_(texture)
    , clipRect_(nullptr)
    , x_(x)
    , y_(y)
    , width_(width)
    , height_(height) {}

/*
 * @brief sets a new value to the x coordinate attribute
 * @param x the value to be assigned to the x coordinate
 */
void Drawable::x(int const& x)
{
    x_ = x;
}

/*
 * @brief gets the value of the x coordinate attribute
 * @return double reference to the x coordinate attribute
 */
int const& Drawable::x()
{
    return x_;
}

/*
 * @brief sets a new value to the y coordinate attribute
 * @param y the value to be assigned to the y coordinate
 */
void Drawable::y(int const& y)
{
    y_ = y;
}

/*
 * @brief gets the value of the y coordinate attribute
 * @return double reference to the y coordinate attribute
 */
int const& Drawable::y()
{
    return y_;
}


/*
 * @brief sets a texture for the drawable object
 * @param texture texture to be assigned to the texture attribute
 */
void Drawable::texture(SDL_Texture* const& texture)
{
    texture_ = texture;
}

/*
 * @brief gets the texture of a drawable object
 * @return SDL_Texture pointer for the object's texture
 */
SDL_Texture* const& Drawable::texture(void)
{
    return texture_;
}

/*
 * @brief
 */
void Drawable::clipRect(SDL_Rect const& clipRect)
{
    *clipRect_ = clipRect;
}

/*
 * @brief
 */
SDL_Rect* const& Drawable::clipRect(void)
{
    return clipRect_;
}

/*
 *
 */
void Drawable::draw(SDL_Renderer* const& renderer)
{
    SDL_Rect destRect{x_, y_, width_, height_};
    SDL_RenderCopy(renderer, texture_, clipRect_, &destRect);
}

/* 
 * Implementation of the Board class' methods 
 */

Board::Board(SDL_Texture* const& texture,
             int const& x, int const& y,
             int const& width, int const& height)
    : Drawable::Drawable(texture, width, height, x, y)
    , boardMatrix_(3, 3)
{
    boardMatrix_.zeros();
}

/*
 * @brief gets the matrix data structure of the board
 * @return Matrix& reference to the board matrix
 */
Matrix& Board::boardMatrix()
{
    return boardMatrix_;
}

/* Implementation of the Player class' methods */

Player::Player(std::string const& name, int const& number)
    : name_(name)
    , number_(number) {}

/*
 * @brief sets the name attribute of the player
 * @param name new name to be assigned to the player
 */
void Player::name(std::string const& name)
{
    name_ = name;
}

/*
 * @brief gets the name attribute of the player
 * @return string& reference for the name attribute
 */
std::string const& Player::name()
{
    return name_;
}
