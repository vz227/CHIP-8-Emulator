#include <chip8.h>

Chip8::Chip8()
{
	//Set program counter to the address of the first instruction, that is, 0x200 or 512 in decimal
	PC = 512;


}

Chip8::~Chip8()
{

}

void Chip8::LoadROM(char* const filename)
{

}