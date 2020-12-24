#include "chip8.h"


int main(int argc, char **argv) {
    initialize();
    loadGame(argv[1]);
    emulateCycle();
}