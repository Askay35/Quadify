#include "window.h"
#include "SDL/SDL_image.h"

Window windowInit(int x, int y, int width, int height, char* title, int flag) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	Window wind;

	wind.window = SDL_CreateWindow(title, x, y, width, height, flag);

	if (wind.window == NULL) {
		SDL_Log("SDL_CreateWindow() failed: %s", SDL_GetError());
		windowDestroy(&wind);
	}

	wind.surface = SDL_GetWindowSurface(wind.window);
	if (wind.surface == NULL) {
		SDL_Log("SDL_CreateRGBSurfaceFrom() failed: %s\n", SDL_GetError());
		windowDestroy(&wind);
	}

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		windowDestroy(&wind);
	}

	wind.renderer = SDL_CreateRenderer(wind.window, -1, SDL_RENDERER_ACCELERATED);
	if (wind.renderer == NULL) {
		SDL_Log("SDL_CreateRenderer() failed: %s\n", SDL_GetError());
		windowDestroy(&wind);
	}

	wind.w = width;
	wind.h = height;

	return wind;
}

void windowSwapSurface(Window * window, SDL_Surface * surface)
{
	SDL_BlitSurface(surface, NULL, window->surface, NULL);
	SDL_UpdateWindowSurface(window->window);
}


void windowDestroy(Window *window) {
	SDL_FreeSurface(window->surface);
	SDL_DestroyWindow(window->window);
	SDL_DestroyRenderer(window->renderer);
	SDL_Quit();
	exit(-1);
}