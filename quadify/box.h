#pragma once
#include "color.h"
#include "image.h"

typedef struct Box {
	uint x, y;
	uint width, height;
	uint delta_color;
	Color color;
	uint8 splited;
}Box;

void drawBox(Image *out, Box box, uint8 border);

void drawBoxes(Image *out, Box *boxes, uint size, uint8 border);

void processRect(Image image, int x, int y, int width, int height, int *delta_color, Color *avg_color);

Box createBox(int x, int y, int width, int height, int delta_color, Color color);

int maxDelta(Box *boxes, uint size, int max_width);

void splitBox(Image *in, Box *box, Box *boxes, uint size);

Image quadify(Image *in, uint rep_count, int min_width, uint8 border);






