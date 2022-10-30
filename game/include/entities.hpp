#ifndef ENTITIES_HPP
#define ENTITIES_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "../include/utils.hpp"

class Drawable
{
    SDL_Texture* texture_;
    SDL_Rect* clipRect_;
    int x_;
    int y_;
    int width_;
    int height_;

public:
    Drawable() = default;
    Drawable(SDL_Texture* const&,
             int const&, int const&,
             int const&, int const&);

    void draw(SDL_Renderer* const&);
    void x(int const&);
    int const& x(void);
    void y(int const&);
    int const& y(void);
    void width(int const&);
    int const& width(void);
    void height(int const&);
    int const& height(void);
    void texture(SDL_Texture**);
    SDL_Texture* const& texture(void);
    void clipRect(SDL_Rect const& clipRect);
    SDL_Rect* const& clipRect(void);
};


class DrawableText: public Drawable
{
    std::string text_;

public:
    DrawableText() = default;
    DrawableText(SDL_Renderer*,
                 std::string const&, TTF_Font*, SDL_Color const&,
                 int const&, int const&);

    void text(std::string const&, SDL_Renderer*, TTF_Font*, SDL_Color const&);
    std::string const& text(void);
};

class Board: public Drawable
{
    Matrix boardMatrix_;

public:
    Board() = default;
    Board(SDL_Texture* const&,
          int const&, int const&,
          int const&, int const&);
    Matrix& boardMatrix(void);
};


class Player
{
    std::string name_;
    int number_;

public:
    Player() = default;
    Player(std::string const&, int const&);

    void name(std::string const&);
    std::string const& name(void);
    void number(int const&);
    int const& number(void);
};
#endif
