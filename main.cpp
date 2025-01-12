#include <iostream>

#include "chip8.h"

chip8 myChip8;

using namespace std;

int main() {

    myChip8.initialize();
    myChip8.loadGame("pong");

}