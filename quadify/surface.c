#include "surface.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const unsigned int rmask = 0xff000000;
const unsigned int gmask = 0x00ff0000;
const unsigned int bmask = 0x0000ff00;
#else
const unsigned int rmask = 0x000000ff;
const unsigned int gmask = 0x0000ff00;
const unsigned int bmask = 0x00ff0000;
#endif

SDL_Surface* loadSurfaceFromFile(char* path) {
	SDL_Surface *surface = NULL;

	SDL_Surface *loaded_surface = IMG_Load(path);
	if (loaded_surface == NULL) {
		SDL_Log("Failed loading image %s! SDL Error: %s\n", path, SDL_GetError());
	}
	return surface;
}


SDL_Surface* resizeSurface(SDL_Surface* surface, int w, int h) {
	SDL_Surface *stretched = SDL_CreateRGBSurface(0, w,h, DEPTH, 0, 0, 0,0);

	SDL_Rect stretchRect = { 0,0, w, h };

	SDL_BlitScaled(surface, NULL, stretched, &stretchRect);

	return stretched;
}


SDL_Surface* loadSurfaceFromMemory(Image image) {

	SDL_Surface *surface = NULL;

	surface = SDL_CreateRGBSurfaceFrom((void*)image.pixels, image.width, image.height, DEPTH, RGB*image.width, rmask,gmask,bmask,0);

	if (surface == NULL) {
		SDL_Log("Failed loading image from memory! SDL Error: %s\n", SDL_GetError());
	}
	return surface;
}