#include "surface.h"


SDL_Surface* loadSurfaceFromFile(char* path, SDL_PixelFormat *format) {
	SDL_Surface *surface = NULL;

	SDL_Surface *loaded_surface = IMG_Load(path);
	if (loaded_surface == NULL) {
		SDL_Log("Failed loading image %s! SDL Error: %s\n", path, SDL_GetError());
	}
	else {
		surface = SDL_ConvertSurface(loaded_surface, format, 0);
		if (surface == NULL) {
			SDL_Log("Failed optimizing image %s! SDL Error: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(loaded_surface);
	}
	return surface;
}

SDL_Surface* resizeSurface(SDL_Surface* surface, int w, int h) {
	SDL_Surface *stretched = NULL;
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = w;
	stretchRect.h = h;
	SDL_BlitScaled(surface, NULL, stretched, &stretchRect);
	return stretched;
}


SDL_Surface* loadSurfaceFromMemory(Image image, SDL_PixelFormat *format) {
	SDL_Surface *surface = NULL;

	surface = SDL_CreateRGBSurfaceFrom(image.pixels, image.width, image.height, 24, 0, 0, 0, 0, 0);

	if (surface == NULL) {
		SDL_Log("Failed loading image from memory! SDL Error: %s\n", SDL_GetError());
	}
	else {
		surface = SDL_ConvertSurface(surface, format, 0);
		if (surface == NULL) {
			SDL_Log("Failed converting surface! SDL Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(surface);
	}
	return surface;
}