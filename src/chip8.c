// fontset do CHIP-8. Deve ser carregado na memória
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

// Armazena opcodes
unsigned short opcode;

// Memória do sistema emulado
unsigned char memory[4096];

// Registradores de uso geral
unsigned char V[16];

// Registradores Program Counter e Index
unsigned short I;
unsigned short PC;

// Estado dos pixels
unsigned char gfx[64 * 32];

// Timers
unsigned char delay_timer;
unsigned char sound_timer;

// Pilha
unsigned char stack[16];
unsigned short sp;

// Keypad
unsigned char key[16];

void initialize() {

    // Programa começa na posição 0x200 da memória
    PC = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;

    // Limpa display
    for(int i = 0; i < (64 * 32); i++) {
        gfx[i] = 0;
    }

    // Limpa pilha
    for(int i = 0; i < 16;i++) {
        stack[i] = 0;
    }

    // Limpa registradores
    for(int i = 0; i < 16; i++) {
        V[i] = 0;
    }

    // Limpa memória
    for(int i = 0; i < 4096; i++) {
        memory[i] = 0;
    }

    // Carrega fontset na memória
    for(int i= 0; i < 80; i++) {
        memory[i] = chip8_fontset[i];
    }

    // TODO: Resetar timers
}

void fetch() {
    opcode = memory[PC] << 8 | memory[PC+1];
}


void emulateCycle() {
    // Fetch opcode
    // Decode opcode
    // Execute opcode

    // Update timers

}