#include "chip8.h"
#include "display.h"
#include <iostream> 
#include <chrono>

int main(int argc, char* argv[])
{
	//Make sure a ROM path is provided
	if (argc < 2)
	{
		std::fprintf(stderr, "No ROM path specified. Exiting..\n");
		return 0;
	}
	
	Chip8 chip8;			//Initialize Chip8 instance
	chip8.LoadROM(argv[0]); //Load ROM from provided file path

	//Initialize display
	Display display("CHIP-8 Emulator", VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH, VIDEO_HEIGHT);

	return 0;
}