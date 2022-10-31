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
 * @param windowWidth width of the current window
 * @param windowHeight height of the current window
 * @param renderer renderer of the current window
 * @return vector list of all the elements of the menu screen
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

/*
 * @brief Function to create all elements of the waiting screen
 * @param windowWidth width of the current window
 * @param windowHeight height of the current window
 * @param renderer renderer of the current window
 * @return vector list of elements to the waiting screen
 */
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
    std::string text("Waiting For Opponent");

    // Creating a drawable waiting message
    SDL_Texture* waitingTexture;
    std::pair<int, int> sizes;
    sizes = text2Texture(&waitingTexture, text, font, color, renderer);
    Drawable waitingMsg(waitingTexture, 0, 56, sizes.first, sizes.second);

    // Defining coordinates for the waiting message
    waitingMsg.x(((windowWidth - waitingMsg.width()) / 2));

    text.clear();
    text.push_back('.');

    // Creating three drawable dots to animete the waiting screen
    SDL_Texture* dotTexture;

    // First dor
    sizes = text2Texture(&dotTexture, text, font, color, renderer);
    Drawable firstDot(dotTexture, 0, 0, sizes.first, sizes.second);
    // Defining the first dot coordinates
    firstDot.x(waitingMsg.x() + waitingMsg.width() + 14);
    firstDot.y(waitingMsg.y());

    // Second dot
    Drawable secondDot(dotTexture, 0, 0, sizes.first, sizes.second);
    // Defining the second dot coorinates
    secondDot.x(firstDot.x() + 14);
    secondDot.y(waitingMsg.y());

    // Third dot
    Drawable thirdDot(dotTexture, 0, 0, sizes.first, sizes.second);
    // Defining the third dot coordinates
    thirdDot.x(secondDot.x() + 14);
    thirdDot.y(waitingMsg.y());

    // Closing the font since it will not be used anymore
    TTF_CloseFont(font);

    // Pushing the elements to the screen's elements list
    elements.push_back(waitingMsg);
    elements.push_back(firstDot);
    elements.push_back(secondDot);
    elements.push_back(thirdDot);

    return elements;

}

/*
 * @brief Function to create all elements of the playing screen
 * @param windowWidth width of the current window
 * @param windowHeight height of the current window
 * @param renderer renderer of the current window
 * @return vector list of elements to the playing screen
 */
std::vector<Drawable> playingScreenInit(int const& windowWidth, int const& windowHeight,
                                        SDL_Renderer* renderer)
{
    std::vector<Drawable> elements;

    // Loading the grid from a PNG
    std::string const gridPath("../textures/grid2white.png");
    SDL_Texture* gridTexture;
    gridTexture = IMG_LoadTexture(renderer, gridPath.c_str());

    // Defining coordinates and sizes for the grid
    int const gridWidth(600);
    int const gridHeight(600);
    int const gridX((windowWidth - gridWidth) / 2);
    int const gridY((windowHeight - gridHeight) / 2);

    // Creating a drawable grid
    Drawable grid(gridTexture, gridX, gridY, gridWidth, gridHeight);

    // Loading font to write in the playing screen
    TTF_Font* font;
    loadFont(&font, "../font/BadMofo.ttf", 60);

    // Color to render the texts
    SDL_Color color;
    color = {0xFF, 0xFF, 0xFF};

    // Opponent header text
    std::string text("Opponent: ");

    /*
    // Creating a drawable opponent header
    SDL_Texture* opHeaderTexture;
    sizes = text2Texture(&opHeaderTexture, text, font, color, renderer);
    int const opHeaderX(gridX);
    int const opHeaderY(gridY + gridHeight + 14);
    Drawable opponentHeader(opHeaderTexture, opHeaderX, opHeaderY,
                            sizes.first, sizes.second);
    */
    // Player header
    text.clear();
    text.append("You: ");

    // Creating a drawable player header
    SDL_Texture* plHeaderTexture;
    std::pair<int, int> sizes;
    sizes = text2Texture(&plHeaderTexture, text, font, color, renderer);
    int const plHeaderX(gridX);
    int const plHeaderY(gridX - sizes.second - 14);
    Drawable playerHeader(plHeaderTexture, plHeaderX, plHeaderY,
                          sizes.first, sizes.second);

    // Pushing the created elements to the playing screen's list of elements
    //elements.push_back(opponentHeader);
    elements.push_back(grid);
    elements.push_back(playerHeader);

    return elements;
}
/*
 * @brief Given a text, a font and a color, build a texture with such text
 * @param texture parameter that will hold the built texture
 * @para font pointer to the font to be used in the texture building
 * @param color color to be used in the texture building
 * @param renderer renderer of the current window
 * @return pair pair of ints containing the texture width and height
 */
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
