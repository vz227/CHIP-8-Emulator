#pragma once

// Include headers
#include <stdint.h>
#include <fstream>
#include <chrono>
#include <random>

// Custom type definitions
typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint32_t DWord;

// Address constants
const unsigned int ROM_START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

// Video constants
const unsigned int VIDEO_WIDTH = 64;
const unsigned int VIDEO_HEIGHT = 32;

class Chip8
{
private:

	Byte registers[16]{}; // 16 registers, each 8 bits (one byte) in size


	Byte memory[4096]{}; // 4KB (4096B) of memory

	/* Registers */
	Word index{};       // Index register (max address 0xFFF)
	Word PC{};          // Program counter
	Word stack[16]{};   // Stack to hold PC values (16 levels)
	Byte SP{};          // Stack pointer to index into stack[]
	Byte delayTimer{};  // Delay timer (decrements at 60Hz)
	Byte soundTimer{};  // Sound timer (decrements at 60Hz & buzzes while not zero)


	Byte keypad[0xF]{}; //Keypad to keep track of each key's status, pressed or not pressed. We will use the MSB of each Byte to determine whether a key is pressed

	//64 * 32 pixel screen, represented as 32 bits for ease of use with SDL
	DWord video_buffer[VIDEO_WIDTH * VIDEO_HEIGHT]{};

	//Current opcode
	Word opcode;

public:
	//Constructor & destructor
	Chip8();
	~Chip8();

	//Method for loading the ROM file into the CHIP-8's memory
	void LoadROM(char* const filePath);

	//Method for loading sprite-based characters into the location where ROMs will expected them
	void LoadFont();


	std::default_random_engine randGen; // Random engine member used for generating the RNG
	std::uniform_int_distribution<Byte> randByte;

	/* Operations */
	void OP_00E0(); // Clear the screen
	void OP_00EE(); // Return from a subroutine
	void OP_1nnn(); // Jump to location nnn
	void OP_2nnn(); // Call subroutine at location nnn
	void OP_3xkk(); // Skip next instruction if Vx = kk
	void OP_4xkk(); // Skip next instruction if Vx != kk
	void OP_5xy0(); // Skip next instruction if Vx = Vy
	void OP_6xkk(); // Set Vx = kk
	void OP_7xkk(); // Set Vx = Vx + kk
	void OP_8xy0(); // Set Vx = Vy
	void OP_8xy1(); // Set Vx = Vx OR Vy
	void OP_8xy2(); // Set Vx = Vx AND Vy
	void OP_8xy3(); // Set Vx = Vx XOR Vy
	void OP_8xy4(); // Set Vx = Vx + Vy, set VF = carry
	void OP_8xy5(); // Set Vx = Vx - Vy, set VF = NOT borrow
	void OP_8xy6(); // Set Vx = Vx SHR 1
	void OP_8xy7(); // Set Vx = Vy - Vx, set VF = NOT borrow
	void OP_8xyE(); // Set Vx = Vx SHL 1
	void OP_9xy0(); // Skip next instruction if Vx != Vy
	void OP_Annn(); // Set I = nnn
	void OP_Bnnn(); // Jump to location nnn + V0
	void OP_Cxkk(); // Set Vx = random byte AND kk
	void OP_Dxyn(); // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
	void OP_Ex9E(); // Skip next instruction if key with the value of Vx is pressed
	void OP_ExA1(); // Skip next instruction if key with the value of Vx is not pressed
	void OP_Fx07(); // Set Vx = delay timer value
	void OP_Fx0A(); // Wait for a key press, store the value of the key in Vx
	void OP_Fx15(); // Set delay timer = Vx
	void OP_Fx18(); // Set sound timer = Vx
	void OP_Fx1E(); // Set I = I + Vx
	void OP_Fx29(); // Set I = location of sprite for digit Vx
	void OP_Fx33(); // Store BCD representation of Vx in memory locations I, I+1, and I+2
	void OP_Fx55(); // Store registers V0 through Vx in memory starting at location I
	void OP_Fx65(); // Read registers V0 through Vx from memory starting at location I
};

//
class Character
{
public:
	Byte sprite[5]; //Array of 5 bytes to store data of a single character

	//Initializer mapping arguments to bytes in sprite[]
	Character(Byte a, Byte b, Byte c, Byte d, Byte e) : sprite{ a, b, c, d, e } {}
};
