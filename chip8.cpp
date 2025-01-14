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

void chip8::initialize()
{
  pc = 0x200;
  opcode = 0;
  I = 0;
  sp = 0;

  for (int i = 0; i < sizeof(stack); ++i)
  {
    stack[i] = 0;
  }

  for (int i = 0; i < sizeof(V); ++i)
  {
    V[i] = 0;
  }

  for (int i = 0; i < sizeof(memory); ++i)
  {
    memory[i] = 0;
  }

  for (int i = 0; i < sizeof(chip8_fontset); ++i)
  {
    memory[i] = chip8_fontset[i];
  }
};

int chip8::loadGame(string game)
{

  string filePath = "games/" + game;

  FILE *file = fopen(filePath.c_str(), "rb");
  if (!file)
  {
    cerr << "Error: Could not open file " << filePath << endl;
    return -1;
  }

  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  rewind(file);

  unsigned char *buffer = new unsigned char[fileSize];

  size_t bytesRead = fread(buffer, sizeof(unsigned char), fileSize, file);
  if (bytesRead != fileSize)
  {
    std::cerr << "Error reading the file." << std::endl;
    delete[] buffer;
    fclose(file);
    return 1;
  }

  for (int i = 0; i < bytesRead; ++i)
    memory[i + 512] = buffer[i];

  delete[] buffer;
  fclose(file);

  return 0;
};

void chip8::printMemory()
{
  for (int i = 0; i < sizeof(memory); ++i)
  {
    std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(memory[i]) << "\t";

    if ((i + 1) % 5 == 0)
    {
      std::cout << std::endl;
    }
  }
  std::cout << std::dec;
}

void chip8::emulateCycle()
{
  opcode = memory[pc] << 8 | memory[pc + 1];

  switch (opcode & 0xF000)
  {
  case 0x0000:
    switch (opcode & 0x000F)
    {

    case 0x0000:
      for (int i = 0; i < sizeof(gfx); ++i)
      {
        gfx[i] = 0;
      }
      pc += 2;
      break;

    case 0x000E:
      --sp;
      pc = stack[sp];
      break;

    default:
      cout << "Opcode not supported!" << endl;
    }
    break;

  case 0x1000:
    pc = opcode & 0x0FFF;
    break;

  case 0x2000:
    stack[sp] = pc;
    ++sp;
    pc = opcode & 0x0FFF;
    break;

  case 0x3000:
    if (V[(opcode & 0x0F00) >> 8] == opcode & 0x00FF)
    {
      pc += 4;
    }
    else
    {
      pc += 2;
    }
    break;

  case 0x4000:
    if (V[(opcode & 0x0F00) >> 8] != opcode & 0x00FF)
    {
      pc += 4;
    }
    else
    {
      pc += 2;
    }
    break;

  case 0x5000:
    if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
    {
      pc += 4;
    }
    else
    {
      pc += 2;
    }
    break;

  case 0x6000:
    V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
    pc += 2;
    break;

  case 0x7000:
    V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
    pc += 2;
    break;

  case 0x8000:
    switch (opcode & 0x000F)
    {
    case 0x0000:
      V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0001:
      V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] | V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0002:
      V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] & V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0003:
      V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] ^ V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0004:
      V[0xF] = V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8]) ? 1 : 0;
      V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0005:
      V[0xF] = V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8] ? 0 : 1;
      V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0006:
      V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
      V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] >> 1;
      pc += 2;
      break;

    case 0x0007:
      V[0xF] = V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4] ? 0 : 1;
      V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
      pc += 2;
      break;

    case 0x000E:
      V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
      V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] << 1;
      pc += 2;
      break;

    default:
      cout << "Opcode not supported!" << endl;
      break;
    }
    break;

  case 0x9000:
    if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
    {
      pc += 4;
    }
    else
    {
      pc += 2;
    }
    break;

  case 0xA000:
    I = opcode & 0x0FFF;
    pc += 2;
    break;

  default:
    break;
  }
}