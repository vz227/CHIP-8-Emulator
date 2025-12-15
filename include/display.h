#pragma once

//Include headers
#include <iostream>
#include <SDL3/SDL.h>

class Display
{
public:
	//Constructor & destructor
	Display(const char* windowTitle, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
	~Display();

	//Update current display
	void Draw(const void* buffer, int pitch);

	//Process user input updating keypad flags, quit flag set to true when input terminates program
	void ProcessInput(uint16_t &keypad, bool& quit);

private:
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* texture{};
};
