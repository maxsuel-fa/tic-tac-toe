#include "../include/screen.hpp"

/*
 * @brief given a vector of drawable elements, constructs
 * a screen containing such elements
 * @param elements elements to be assigned to the elements
 * attrinute of the screen
 */
Screen::Screen(std::vector<Drawable> const& elements)
    : elements_(elements) {}

/*
 * @brief gets the elements list of the screen object
 * @return vector the elements list of the screen
 */
std::vector<Drawable>& Screen::elements(void)
{
    return elements_;
}

/*
 * @brief draws all the elements of the screen
 * @param renderer the ..
 */
void Screen::draw(SDL_Renderer* const& renderer)
{
    for (auto elem : elements_)
        elem.Drawable::draw(renderer);
}

/*
 * @brief Function to create all elements of the menu screen
 * @param renderer
 * @param font used in the game
 * @return vector containing all the elements of the menu screen
 */
std::vector<Drawable> menuScreenInit(int const& windowWidth, int const& windowHeight,
                                     SDL_Renderer* renderer, TTF_Font *font,
                                     SDL_Color const& color)
{
    std::vector<Drawable> elements;

    // Creating a texture from text to the title of the game
    SDL_Surface* titleSurface;
    titleSurface = TTF_RenderText_Solid(font, "TIC TAC TOE", color);
    SDL_Texture* titleTexture;
    titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

    // Defining coordinates and sizes for the title of the game
    int const titleWidth(titleSurface->w);
    int const titleHeight(titleSurface->h);
    int const titleX((windowWidth - titleWidth) / 2);
    int const titleY(56);

    // Creating a drawable title
    Drawable title(titleTexture, titleX, titleY, titleSurface->w, titleSurface->h);

    // Freeing the surface created for title
    SDL_FreeSurface(titleSurface);

    // Loading the logo from a PNG
    std::string const logoPath("../textures/logo.png");
    SDL_Texture* logoTexture;
    logoTexture = IMG_LoadTexture(renderer, logoPath.c_str());

    // Defining coordinates and sizes for the logo
    int const logoWidth(256);
    int const logoHeight(256);
    int const logoX((windowWidth - logoWidth) / 2);
    int const logoY((windowHeight - logoHeight) / 2);

    // Creating a drawable logo
    Drawable logo(logoTexture, logoX, logoY, logoWidth, logoHeight);

    // Loading the start button froma PNG
    std::string const startButtonPath("../textures/startbutton.png");
    SDL_Texture* startTexture;
    startTexture = IMG_LoadTexture(renderer, startButtonPath.c_str());

    // Defining coordinates and sizes for the start button
    int const startWidth(256);
    int const startHeight(256);
    int const startX((windowWidth - startWidth) / 2);
    int const startY(windowHeight - startHeight);

    // Creating a drawable start button
    Drawable startButton(startTexture, startX, startY, startWidth, startHeight);

    // Pushing the drawable elements to the menu screen elements list
    elements.push_back(title);
    elements.push_back(logo);
    elements.push_back(startButton);

    return elements;
}


