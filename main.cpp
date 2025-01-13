#include <iostream>
#include <SDL2/SDL.h>

#include "chip8.h"
#include "screen.h"

chip8 myChip8;

using namespace std;

int main() {

    // myChip8.initialize();
    // myChip8.loadGame("pong");

    Screen screen;


    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

}