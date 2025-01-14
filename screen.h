#include <SDL2/SDL.h>

class Screen
{

private:
    SDL_Window *win;
    SDL_Surface *winSurface;

    int initializeWindow();
    int initializeSurface();

public:
    Screen();
    ~Screen();
};