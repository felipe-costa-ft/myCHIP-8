#include <string>
#include <SDL2/SDL.h>

#include "screen.h"

using namespace std;

const unsigned int FONTSET_START_ADDRESS = 0x50;

class chip8
{

private:
    Screen screen;

    unsigned short opcode;
    unsigned char memory[4096];
    unsigned char V[16];
    unsigned short I;
    unsigned short pc;
    unsigned char gfx[64 * 32];
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short stack[16];
    unsigned short sp;
    unsigned char key[16];
    bool drawFlag;

public:
    void initialize();
    int loadGame(string game);
    void drawGraphics();
    void emulateCycle();

    void printMemory();
};