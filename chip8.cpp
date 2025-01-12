#include <iostream>
#include <string>

#include "chip8.h"

using namespace std;


void chip8::initialize() {
    cout << "Initialized!" << endl;
};

void chip8::loadGame(string game) {
    cout << game << " Loaded!" << endl;
};