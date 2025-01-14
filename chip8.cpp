#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string>

#include "chip8.h"

using namespace std;

unsigned char chip8_fontset[80] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void chip8::initialize() {
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;

    for (int i = 0; i < sizeof(stack); ++i) {
      stack[i] = 0;
    }

    for (int i = 0; i < sizeof(V); ++i) {
      V[i] = 0;
    }

    for (int i = 0; i < sizeof(memory); ++i) {
      memory[i] = 0;
    }

    for (int i = 0; i < sizeof(chip8_fontset); ++i) {
      memory[i] = chip8_fontset[i];
    }
};

int chip8::loadGame(string game) {

    string filePath = "games/" + game;


    FILE* file = fopen(filePath.c_str(), "rb");
    if (!file) {
      cerr << "Error: Could not open file " << filePath << endl;
      return -1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    unsigned char* buffer = new unsigned char[fileSize];

    size_t bytesRead = fread(buffer, sizeof(unsigned char), fileSize, file);
    if (bytesRead != fileSize) {
        std::cerr << "Error reading the file." << std::endl;
        delete[] buffer;
        fclose(file);
        return 1;
    }

    for(int i = 0; i < bytesRead; ++i)
    memory[i + 512] = buffer[i];

    delete[] buffer;
    fclose(file);

    return 0;
};

void chip8::printMemory() {
    for (int i = 0; i < sizeof(memory); ++i) {
        std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(memory[i]) << "\t";

        if ((i + 1) % 5 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::dec;
}

void chip8::emulateCycle() {
    opcode = memory[pc] << 8 | memory[pc + 1];

    switch (opcode & 0xF000)
    {
    case 0xA000:
      I = opcode & 0x0FFF;
      pc += 2;
      break;

    case 0x1000:
      pc = opcode & 0x0FFF;
      break;
      
    default:
      break;
    }
}