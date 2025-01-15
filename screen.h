#include <SDL2/SDL.h>

class Screen
{

private:
    int initializeWindow();
    int initializeSurface();

public:
    SDL_Window *win;
    SDL_Surface *winSurface;
    SDL_Renderer *renderer;
    Screen();
    ~Screen();
};