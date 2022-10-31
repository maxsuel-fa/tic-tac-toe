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
 *                Implementation of the DrawableText class' methods            *
 *******************************************************************************/

/*
 * @brief Given a text, create a drawable object with it
 * @param renderer renderer of the current window
 * @param text text to be drawn
 * @param font font to use for the text
 * @param color color to use in the drawing of the text
 * @param x the x coordinate for drawing
 * @param y the y coordinate for drawing
 * @param width the width of the object
 * @para height the height of the object
 */
DrawableText::DrawableText(SDL_Renderer* renderer,
                           std::string const& text, TTF_Font* font, SDL_Color const& color,
                           int const& x, int const& y)
    : text_(text)
{
    // Creating a surface using text for the object
    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    Drawable::texture(&texture);

    // Initializing the sizes attributes of the object
    Drawable::x(x);
    Drawable::y(y);
    Drawable::width(surface->w);
    Drawable::height(surface->h);

    // Freeing the surface used to creat the object's texture
    SDL_FreeSurface(surface);
}

/*
 * @brief sets a new text for the object
 * @param text new text to be assigned to the object
 */
void DrawableText::text(std::string const& text, SDL_Renderer* renderer,
                        TTF_Font* font, SDL_Color const& color)
{
    text_ = text;

    // Always the text changes, its texture should also be changed
    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    Drawable::texture(&texture);
    Drawable::width(surface->w);
    Drawable::height(surface->h);

    // Freeing the surface used to update the texture of the object
    SDL_FreeSurface(surface);
}

/*
 * @brief gets the attribute text of the object
 * @return string the attribute text
 */
std::string const& DrawableText::text(void)
{
    return text_;
}


/*******************************************************************************
 *                Implementation of the Board class' methods                   *
 *******************************************************************************/
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


/*******************************************************************************
 *                Implementation of the Player class' methods                  *
 *******************************************************************************/

Player::Player(std::string const& symbol)
    : symbol_(symbol) {}

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
std::string const& Player::symbol()
{
    return symbol_;
}
