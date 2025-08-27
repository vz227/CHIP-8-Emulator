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
		std::fprintf(stderr, "Usage: %s <ROM> <Scale> <CPU Cycle Delay>\n", argv[0]);
		return 1;
	}

	char* const romPath{ argv[1] };															//ROM Path
	int videoScale{ std::stoi(argv[2]) };													//Video scale to upscale the original 64x32 video buffer for larger screens
	int cycleDelay{ std::stoi(argv[3]) };													//Delay between CPU cycles (different ROMs require different delays)

	//Initialize display
	Display display("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	Chip8 chip8;																			//Initialize Chip8 instance
	chip8.LoadROM(romPath);																	//Load ROM from provided file path

	int videoPitch{ static_cast<int>(sizeof(chip8.videoBuffer[0])) * VIDEO_WIDTH };			//Initialize pitch (pixels per row)
	bool quit{ false };																		//Initialize quit flag for main loop

	//Main loop
	while (!quit)
	{
		display.ProcessInput(chip8.keypad, quit);											//Process any input & set quit flag if necessary

		chip8.CPUCycle();																	//Run through a CPU cycle

		display.Draw(chip8.videoBuffer, videoPitch);										//Update the display
	}

	return 0;
}