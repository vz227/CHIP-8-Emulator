#include "display.h"

Display::Display(const char* windowTitle, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
{
	//Initialize SDL video subsystem & handle possible errors
	if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Could not initialize SDL video subsystem.\n SDL_Error: %s\n", SDL_GetError());
		return;
	}

	//Initialize window & handle possible errors upon window creation
	if (window = SDL_CreateWindow(windowTitle, windowWidth, windowHeight, NULL); !window)
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

void Display::Update(const void* buffer, int pitch)
{
	//
	SDL_UpdateTexture(texture, NULL, buffer, pitch);

}

bool Display::ProcessInput(uint16_t keypad)
{
	//Initialize quit flag
	bool quit = false;

	//Initialize current SDL_Event
	SDL_Event event;


	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
		{
			quit = true;
		} break;

		case SDL_EVENT_KEY_DOWN:
		{
			switch (event.key.key)
			{
			case SDLK_X:
			{
				//Set keypad[0x0] to 1
				keypad |= (1 << 0);
			} break;

			case SDLK_1:
			{
				//Set keypad[0x1] to 1
				keypad |= (1 << 1);
			} break;

			case SDLK_2:
			{
				//Set keypad[0x2] to 1
				keypad |= (1 << 2);
			} break;

			case SDLK_3:
			{
				//Set keypad[0x3] to 1
				keypad |= (1 << 3);
			} break;

			case SDLK_Q:
			{
				//Set keypad[0x4] to 1
				keypad |= (1 << 4);
			} break;

			case SDLK_W:
			{
				//Set keypad[0x5] to 1
				keypad |= (1 << 5);
			} break;

			case SDLK_E:
			{
				//Set keypad[0x6] to 1
				keypad |= (1 << 6);
			} break;

			case SDLK_A:
			{
				//Set keypad[0x7] to 1
				keypad |= (1 << 7);
			} break;

			case SDLK_S:
			{
				//Set keypad[0x8] to 1
				keypad |= (1 << 8);
			} break;

			case SDLK_D:
			{
				//Set keypad[0x9] to 1
				keypad |= (1 << 9);
			} break;

			case SDLK_Z:
			{
				//Set keypad[0xA] to 1
				keypad |= (1 << 10);
			} break;

			case SDLK_C:
			{
				//Set keypad[0xB] to 1
				keypad |= (1 << 11);
			} break;

			case SDLK_4:
			{
				//Set keypad[0xC] to 1
				keypad |= (1 << 12);
			} break;

			case SDLK_R:
			{
				//Set keypad[0xD] to 1
				keypad |= (1 << 13);
			} break;

			case SDLK_F:
			{
				//Set keypad[0xE] to 1
				keypad |= (1 << 14);
			} break;

			case SDLK_V:
			{
				//Set keypad[0xF] to 1
				keypad |= (1 << 15);
			} break;
			}

			break;
		}

		case SDL_EVENT_KEY_UP:
		{
			switch (event.key.key)
			{
			case SDLK_X:
			{
				//Set keypad[0x0] to 0
				keypad &= ~(1 << 0);
			} break;

			case SDLK_1:
			{
				//Set keypad[0x1] to 0
				keypad &= ~(1 << 1);
			} break;

			case SDLK_2:
			{
				//Set keypad[0x2] to 0
				keypad &= ~(1 << 2);
			} break;

			case SDLK_3:
			{
				//Set keypad[0x3] to 0
				keypad &= ~(1 << 3);
			} break;

			case SDLK_Q:
			{
				//Set keypad[0x4] to 0
				keypad &= ~(1 << 4);
			} break;

			case SDLK_W:
			{
				//Set keypad[0x5] to 0
				keypad &= ~(1 << 5);
			} break;

			case SDLK_E:
			{
				//Set keypad[0x6] to 0
				keypad &= ~(1 << 6);
			} break;

			case SDLK_A:
			{
				//Set keypad[0x7] to 0
				keypad &= ~(1 << 7);
			} break;

			case SDLK_S:
			{
				//Set keypad[0x8] to 0
				keypad &= ~(1 << 8);
			} break;

			case SDLK_D:
			{
				//Set keypad[0x9] to 0
				keypad &= ~(1 << 9);
			} break;

			case SDLK_Z:
			{
				//Set keypad[0xA] to 0
				keypad &= ~(1 << 10);
			} break;

			case SDLK_C:
			{
				//Set keypad[0xB] to 0
				keypad &= ~(1 << 11);
			} break;

			case SDLK_4:
			{
				//Set keypad[0xC] to 0
				keypad &= ~(1 << 12);
			} break;

			case SDLK_R:
			{
				//Set keypad[0xD] to 0
				keypad &= ~(1 << 13);
			} break;

			case SDLK_F:
			{
				//Set keypad[0xE] to 0
				keypad &= ~(1 << 14);
			} break;

			case SDLK_V:
			{
				//Set keypad[0xF] to 0
				keypad &= ~(1 << 15);
			} break;
			}
		}
		}

		//Return quit flag
		return quit;
	}
}

