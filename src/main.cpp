#include "chip8.h"
#include "display.h"
#include <iostream> 
#include <string>
#include <chrono>

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::fprintf(stderr, "Usage: %s <ROM> <Scale> <CPU Cycle Delay>\n", argv[0]);
		return 1;
	}

	char* const romPath{ argv[1] };
	int videoScale{ std::stoi(argv[2]) };
	int cycleDelay{ std::stoi(argv[3]) };

	Display display("CHIP-8", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	Chip8 chip8;
	chip8.LoadROM(romPath);

	int videoPitch{ static_cast<int>(sizeof(chip8.videoBuffer[0])) * VIDEO_WIDTH };
	bool quit{ false };

	while (!quit)
	{
		display.ProcessInput(chip8.keypad, quit);

		chip8.CPUCycle();

		display.Draw(chip8.videoBuffer, videoPitch);

		SDL_Delay(10);
	}

	return 0;
}
