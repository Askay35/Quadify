#pragma once
#include "SDL/SDL_image.h"
#include "image.h"

SDL_Surface* loadSurfaceFromFile(char* path);

SDL_Surface* resizeSurface(SDL_Surface* surface, int w, int h);

SDL_Surface* loadSurfaceFromMemory(Image image);