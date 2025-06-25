#include "display.h"

Display::Display(const char* windowTitle, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
{
	//Initialize SDL video subsystem & handle possible errors
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Could not initialize SDL video subsystem.\n SDL_Error: %s\n", SDL_GetError());
		return;
	}

	//Initialize window & handle possible errors upon window creation
	if (window = SDL_CreateWindow(windowTitle, windowWidth, windowHeight, SDL_EVENT_WINDOW_SHOWN); !window)
	{
		fprintf(stderr, "Could not create window.\n SDL_Error: %s\n", SDL_GetError());
	}

	//Initialize renderer & handle possible errors upon renderer creation
	if (renderer = SDL_CreateRenderer(window, NULL); !renderer)
	{
		fprintf(stderr, "Could not create renderer.\n SDL_Error: %s\n", SDL_GetError());
	}

	//Initialize texture & handle possible errors upon texture creation
	if (texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight); !texture)
	{
		fprintf(stderr, "Could not create texture.\n SDL_Error: %s\n", SDL_GetError());
	}
}

Display::~Display()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

