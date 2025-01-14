#include <iostream>
#include <SDL2/SDL.h>

#include "chip8.h"

chip8 myChip8;

using namespace std;

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <game_name>" << endl;
        return 1;
    }

    string gameName = argv[1];

    myChip8.initialize();
    myChip8.loadGame(gameName);
    myChip8.printMemory();

    bool running = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
    }
}