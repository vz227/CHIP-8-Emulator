#include "chip8.h"
#include "display.h"
#include <iostream> 
#include <string>
#include <chrono>

int main(int argc, char* argv[])
{
	//Make sure all arguments are provided
	if (argc != 4)
	{
		std::fprintf(stderr, "Usage: %s <ROM> <Scale> <Delay>\n", argv[0]);
		std::exit(EXIT_FAILURE);
	}

	char* const romPath = argv[1];			//ROM Path
	int videoScale = std::stoi(argv[2]);	//Video scale to upscale the original 64x32 video buffer for larger screens
	int cycleDelay = std::stoi(argv[3]);	//Delay between CPU cycles (different ROMs require different delays)

	//Initialize display
	Display display("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	Chip8 chip8;			//Initialize Chip8 instance
	chip8.LoadROM(romPath); //Load ROM from provided file path

	bool quit = false;		//Initialize quit flag

	//While display.ProcessInput() returns true, continue 
	while (!quit)
	{
		display.ProcessInput(chip8.keypad, quit);

		chip8.CPUCycle();

		display.Update(chip8.video_buffer, 0);

		SDL_Delay(cycleDelay);
	}

	return 0;
}