#pragma once
#include "color.h"

#include <stdio.h>

typedef struct Image {
	uint size;
	uint width, height;		
	uint8* pixels;
}Image;

int getPixelIndex(Image image, int x, int y);

Image load_image(FILE *file);

int save_jpg(Image image, char* filename, uint8 quality);

int save_png(Image image, char* filename);

Color getPixel(Image image, int x, int y);
	
void setPixel(Image *image, int x, int y, Color color);