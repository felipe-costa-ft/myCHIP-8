#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include <ctime>

#include "chip8.h"

chip8 myChip8;

using namespace std;

int main(int argc, char **argv)
{
    srand(static_cast<unsigned int>(time(0)));

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

    const std::chrono::milliseconds cycleDelay(16);

    while (running)
    {
        auto start = std::chrono::high_resolution_clock::now();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        myChip8.emulateCycle();

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (elapsed < cycleDelay)
        {
            std::this_thread::sleep_for(cycleDelay - elapsed);
        }
    }

    return 0;
}