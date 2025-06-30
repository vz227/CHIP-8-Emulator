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
	void Update();

	//Process user input, return true 
	bool ProcessInput(uint16_t keypad);

private:
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* texture{};
};
