#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include <ctime>

#include "chip8.h"

chip8 myChip8;

using namespace std;

bool soundOn = false;
double audioPhase = 0.0;
int audioSampleRate = 44100;

void audioCallback(void *userdata, Uint8 *stream, int len)
{
    Sint16 *buffer = reinterpret_cast<Sint16 *>(stream);
    int samples = len / 2;
    const double freq = 440.0;
    const Sint16 amplitude = 3000;

    for (int i = 0; i < samples; i++)
    {
        if (!soundOn)
        {
            buffer[i] = 0;
            continue;
        }
        buffer[i] = (audioPhase < 0.5) ? amplitude : -amplitude;
        audioPhase += freq / audioSampleRate;
        if (audioPhase >= 1.0)
            audioPhase -= 1.0;
    }
}

int main(int argc, char **argv)
{

    const int cyclesPerFrame = 10;
    srand(static_cast<unsigned int>(time(0)));

    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <game_name>" << endl;
        return 1;
    }

    string gameName = argv[1];

    SDL_AudioSpec want{}, have{};
    want.freq = audioSampleRate;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
    want.samples = 512;
    want.callback = audioCallback;

    SDL_AudioDeviceID audioDevice = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
    SDL_PauseAudioDevice(audioDevice, 0);

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
                myChip8.updateKey(event.key.keysym.scancode, 1);
            }

            if (event.type == SDL_KEYUP)
            {
                myChip8.updateKey(event.key.keysym.scancode, 0);
            }
        }

        for (int i = 0; i < cyclesPerFrame; i++)
        {
            myChip8.emulateCycle();
        }

        myChip8.updateTimers();

        soundOn = (myChip8.getSoundTimer() > 0);

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