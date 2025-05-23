#pragma once
#include <stdint.h>

//Custom type definitions
typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint32_t DWord;

static class Chip8 {

	//16 registers, each 8 bits (one byte) in size
	Byte registers[16]{};

	//4KB (4096B) of memory
	Byte memory[4096]{};

	//Index register (16 bits because max address 0xFFF is too large to store in 8)
	Word index{};

	//Program counter (16 bits because max address 0xFFF is too large to store in 8)
	Word PC{};

	//Stack that holds Program Counter values (CHIP-8 has 16 levels of stack)
	Word stack[16]{};

	//Stack pointer that acts as an index into the stack array. Size of 8 bits as we only need 16 different values, and a byte is the smallest addressable unit of memory
	Byte SP{};

	//Timer registers
	Byte delayTimer{};
	Byte soundTimer{};

	//Keypad to keep track of each key's status, pressed or not pressed
	Byte keypad[16]{};

	//64 * 32 pixel screen, represented as 32 bits for ease of use with SDL
	DWord video[64 * 32]{};
	
	//Current opcode
	Word opcode;

	//Initializer & destructor
	Chip8();
	~Chip8();

	//Method for loading the ROM file into the CHIP-8's memory
	void LoadROM(char* const filename);


};
