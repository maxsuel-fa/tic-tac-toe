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
    SDL_RenderPresent(renderer);
}

void Screen::draw(SDL_Renderer* const& renderer, Uint32 const& delay)
{
    for (auto elem : elements_)
    {
        elem.Drawable::draw(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(delay);
    }
}

/*
 * @brief Function to create all elements of the menu screen
 * @param renderer
 * @param font used in the game
 * @return vector containing all the elements of the menu screen
 */
std::vector<Drawable> menuScreenInit(int const& windowWidth, int const& windowHeight,
                                     SDL_Renderer* renderer)
{
    std::vector<Drawable> elements;

    // Loading font to write the title
    TTF_Font* font;
    loadFont(&font, "../font/BadMofo.ttf", 120);

    // Color for the title
    SDL_Color color;
    color = {0xFF, 0xFF, 0xFF};

    // Defining title text
    std::string const& titleTex("TIC TAC TOE");

    // Creating a drawable title
    std::pair<int, int> sizes;
    SDL_Texture* texture;
    sizes = text2Texture(&texture, titleTex, font, color, renderer);
    Drawable title(texture, 0, 0, sizes.first, sizes.second);

    // Defining coordinates for the title of the game
    title.x(((windowWidth - title.width()) / 2));
    title.y(56);

    // Closing the font since it will not be used anymore
    TTF_CloseFont(font);

    // Loading the logo from a PNG
    std::string const logoPath("../textures/logowhite.png");
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
    std::string const startButtonPath("../textures/startbuttonwhite.png");
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
    elements.push_back((Drawable)title);
    elements.push_back(logo);
    elements.push_back(startButton);

    return elements;
}

std::vector<Drawable> waitingScreenInit(int const& windowWidth, int const& windowHeight,
                                        SDL_Renderer* renderer)
{
    std::vector<Drawable> elements;

    // Loading font to write the waiting message
    TTF_Font* font;
    loadFont(&font, "../font/BadMofo.ttf", 60);

    // Color for the waiting message
    SDL_Color color;
    color = {0xFF, 0xFF, 0xFF};

    // Defining the waiting message text
    std::string text("Waiting For Enemy");

    // Creating a drawable waiting message
    SDL_Texture* waitingTexture;
    std::pair<int, int> sizes;
    sizes = text2Texture(&waitingTexture, text, font, color, renderer);
    Drawable waitingMsg(waitingTexture, 0, 0, sizes.first, sizes.second);

    // Defining coordinates for the waiting message
    waitingMsg.x(((windowWidth - waitingMsg.width()) / 2));
    waitingMsg.y(56);

    text.clear();
    text.push_back('.');

    SDL_Texture* dotTexture;
    sizes = text2Texture(&dotTexture, text, font, color, renderer);
    Drawable firstDot(dotTexture, 0, 0, sizes.first, sizes.second);
    firstDot.x(waitingMsg.x() + waitingMsg.width() + 14);
    firstDot.y(waitingMsg.y());

    Drawable secondDot(dotTexture, 0, 0, sizes.first, sizes.second);
    secondDot.x(firstDot.x() + 14);
    secondDot.y(waitingMsg.y());

    Drawable thirdDot(dotTexture, 0, 0, sizes.first, sizes.second);
    thirdDot.x(secondDot.x() + 14);
    thirdDot.y(waitingMsg.y());

    // Closing the font since it will not be used anymore
    TTF_CloseFont(font);

    elements.push_back((Drawable)waitingMsg);
    elements.push_back((Drawable)firstDot);
    elements.push_back((Drawable)secondDot);
    elements.push_back((Drawable)thirdDot);

    return elements;

}

std::pair<int, int> text2Texture(SDL_Texture** texture, std::string const& text, TTF_Font* font, 
        SDL_Color const& color, SDL_Renderer* renderer)
{
    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);

    std::pair<int, int> sizes(surface->w, surface->h);
    SDL_FreeSurface(surface);
    return sizes;
}
