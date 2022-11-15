/*
 * @file screen_init.hpp
 * @brief A set of functions to initialize all the screens in the game
 */

/*
 * @brief Function to create all elements of the menu screen
 * @param renderer
 * @param font used in the game
 * @return vector containing all the elements of the menu screen
 */
std::vector<Drawable> menuScreenInit(SDL_Renderer* renderer, TTF_Font *font)
{
    std::vector<Drawable> elements;

    // Creating a texture from text to the title of the game
    SDL_Surface* titleSurface;
    SDL_Color color = {0x0, 0x0, 0x0};
    titleSurface = TTF_RenderText_Solid(font, "TIC TAC TOE", color);
    SDL_Texture* titleTexture;
    titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    // Defining coordinates and sizes for the title of the game

    int const titleWidth(titleSurface->w);
    int const titleHeight(titleSurface->h);
    int const titleX((784-titleWidth)/2);
    int const titleY(56);
    // Creating a drawable title
    Drawable title(titleTexture, titleX, titleY, titleSurface->w, titleSurface->h);

    /*
    std::string const logoPath("../textures/logo.png");
    SDL_Texture* logoTexture;
    logoTexture = IMG_LoadTexture(renderer, logoPath.c_str());
    // Defining coordinates and sizes for the logo
    int const logoX();
    int const logoY(56);
    int const logoWidth(256);
    int const logoHeight(256);
    // Creatomg a drawable logo
    Drawable logo(logoTexture, logoX, logoY, logoWidth, logoHeight);
    Drawable playButton();
    */
    elements.push_back(title);
    //elements.push_back(logo);
    //elements.push_back(playButton);

    return elements;
}





