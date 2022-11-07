#include "../include/entities.hpp"

/*******************************************************************************
 *                Implementation of the Drawable class' methods                *
 *******************************************************************************/

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
 * @return int reference to the x coordinate attribute
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
 * @return int reference to the y coordinate attribute
 */
int const& Drawable::y()
{
    return y_;
}

/*
 * @brief sets a new value to the width attribute
 * @param width the value to be assigned to the width
 */
void Drawable::width(int const& width)
{
    width_ = width;
}

/*
 * @brief gets the value of the width attribute
 * @return int reference to the width attribute
 */
int const& Drawable::width(void)
{
    return width_;
}

/*
 * @brief sets a new value to the height attribute
 * @param width the value to be assigned to the height
 */
void Drawable::height(int const& height)
{
    height_ = height;
}

/*
 * @brief gets the value of the height attribute
 * @return int reference to the height attribute
 */
int const& Drawable::height(void)
{
    return height_;
}

/*
 * @brief sets a texture for the drawable object
 * @param texture texture to be assigned to the texture attribute
 */
void Drawable::texture(SDL_Texture** texture)
{
    texture_ = *texture;
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


/*******************************************************************************
 *                Implementation of the Player class' methods                  *
 *******************************************************************************/

Player::Player(void)
    : playing(false) {}

/*
 * @brief sets the symbol attribute for the player
 * @param symbol new symbol to be assigned to the player
 */
void Player::symbol(std::string const& symbol)
{
    symbol_ = symbol;
}

/*
 * @brief gets the symbol attribute of the player
 * @return string& reference to the symbol attribute
 */
std::string& Player::symbol()
{
    return symbol_;
}
