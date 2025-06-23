#include "chip8.h"
#include <iostream>

int main(int argc, char* argv[])
{
	//Make sure ROM path is provided
	if (argc < 1) std::fprintf(stderr, "No ROM path specified. Exiting..\n"); return 0;
	Chip8 chip8;

	chip8.LoadROM(argv[0]);

	return 0;
}