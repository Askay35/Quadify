#pragma once
#include "SDL/SDL.h"
#include "types.h"

typedef struct Window {
	SDL_Window *window;
	SDL_Surface *surface;
	uint w;
	uint h;
}Window;


Window windowInit(int x, int y, int width, int height, char* title, int flag);

void windowSwapSurface(Window *window, SDL_Surface *surface);

void windowDestroy(Window *window);