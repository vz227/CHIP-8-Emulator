#pragma once

//Include headers
#include <iostream>
#include <SDL3/SDL.h>

class Display
{
public:
	Display(const char* windowTitle, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
	~Display();

private:
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* texture{};
};
