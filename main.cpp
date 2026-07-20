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

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_1:
                    myChip8.updateKey('1', 1);
                    break;
                case SDL_SCANCODE_2:
                    myChip8.updateKey('2', 1);
                    break;
                case SDL_SCANCODE_3:
                    myChip8.updateKey('3', 1);
                    break;
                case SDL_SCANCODE_4:
                    myChip8.updateKey('4', 1);
                    break;
                case SDL_SCANCODE_Q:
                    myChip8.updateKey('q', 1);
                    break;
                case SDL_SCANCODE_W:
                    myChip8.updateKey('w', 1);
                    break;
                case SDL_SCANCODE_E:
                    myChip8.updateKey('e', 1);
                    break;
                case SDL_SCANCODE_R:
                    myChip8.updateKey('r', 1);
                    break;
                case SDL_SCANCODE_A:
                    myChip8.updateKey('a', 1);
                    break;
                case SDL_SCANCODE_S:
                    myChip8.updateKey('s', 1);
                    break;
                case SDL_SCANCODE_D:
                    myChip8.updateKey('d', 1);
                    break;
                case SDL_SCANCODE_F:
                    myChip8.updateKey('f', 1);
                    break;
                case SDL_SCANCODE_Z:
                    myChip8.updateKey('z', 1);
                    break;
                case SDL_SCANCODE_X:
                    myChip8.updateKey('x', 1);
                    break;
                case SDL_SCANCODE_C:
                    myChip8.updateKey('c', 1);
                    break;
                case SDL_SCANCODE_V:
                    myChip8.updateKey('v', 1);
                    break;
                }
            }

            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_1:
                    myChip8.updateKey('1', 0);
                    break;
                case SDL_SCANCODE_2:
                    myChip8.updateKey('2', 0);
                    break;
                case SDL_SCANCODE_3:
                    myChip8.updateKey('3', 0);
                    break;
                case SDL_SCANCODE_4:
                    myChip8.updateKey('4', 0);
                    break;
                case SDL_SCANCODE_Q:
                    myChip8.updateKey('q', 0);
                    break;
                case SDL_SCANCODE_W:
                    myChip8.updateKey('w', 0);
                    break;
                case SDL_SCANCODE_E:
                    myChip8.updateKey('e', 0);
                    break;
                case SDL_SCANCODE_R:
                    myChip8.updateKey('r', 0);
                    break;
                case SDL_SCANCODE_A:
                    myChip8.updateKey('a', 0);
                    break;
                case SDL_SCANCODE_S:
                    myChip8.updateKey('s', 0);
                    break;
                case SDL_SCANCODE_D:
                    myChip8.updateKey('d', 0);
                    break;
                case SDL_SCANCODE_F:
                    myChip8.updateKey('f', 0);
                    break;
                case SDL_SCANCODE_Z:
                    myChip8.updateKey('z', 0);
                    break;
                case SDL_SCANCODE_X:
                    myChip8.updateKey('x', 0);
                    break;
                case SDL_SCANCODE_C:
                    myChip8.updateKey('c', 0);
                    break;
                case SDL_SCANCODE_V:
                    myChip8.updateKey('v', 0);
                    break;
                }
            }
        }

        myChip8.emulateCycle();

        myChip8.drawGraphics();

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (elapsed < cycleDelay)
        {
            std::this_thread::sleep_for(cycleDelay - elapsed);
        }
    }

    return 0;
}