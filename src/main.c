#include "chip8.h"
#include <stdio.h>


int main(int argc, char **argv) {
    initialize();
    loadGame(argv[1]);
    showMemory();
    printf("\n\n\n");

    while(1){
        emulateCycle();
    }
}