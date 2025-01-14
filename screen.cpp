#include <iostream>

#include <SDL2/SDL.h>

#include "screen.h"

int Screen::initializeWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        win = nullptr;
        winSurface = nullptr;
        return -1;
    }

    win = SDL_CreateWindow("CHIP-8 Emulator", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    if (!win)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    return 0;
}

int Screen::initializeSurface()
{
    winSurface = SDL_GetWindowSurface(win);

    if (!winSurface)
    {
        std::cerr << "Error getting surface: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_UpdateWindowSurface(win);

    return 0;
}

Screen::Screen()
{

    if (initializeWindow() >= 0)
    {
        initializeSurface();
    }
}

Screen::~Screen()
{
    SDL_DestroyWindow(win);
    win = NULL;
    winSurface = NULL;

    SDL_Quit();
}