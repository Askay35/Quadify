#include "box.h"

#include <memory.h>
#include <stdlib.h>

void splitBox(Image *in, Box *box, Box *boxes, uint size)
{
	int w = (*box).width / 2;
	int h = (*box).height / 2;

	int dc;
	Color avgc;

	if (box->width % 2 != 0) {
		processRect(*in, (*box).x, (*box).y, w + 1, h, &dc, &avgc);// LT
		boxes[size + 0] = createBox((*box).x, (*box).y, w + 1, h, dc, avgc);

		processRect(*in, (*box).x + w + 1, (*box).y, w, h, &dc, &avgc);//RT
		boxes[size + 1] = createBox((*box).x + w + 1, (*box).y, w, h, dc, avgc);

		if (box->height % 2 != 0) {
			processRect(*in, box->x, box->y + h, w + 1, h + 1, &dc, &avgc);// LB
			boxes[size + 2] = createBox(box->x, box->y + h, w + 1, h + 1, dc, avgc);

			processRect(*in, box->x + w + 1, box->y + h, w, h + 1, &dc, &avgc);//RB
			boxes[size + 3] = createBox(box->x + w + 1, box->y + h, w, h + 1, dc, avgc);
		}
		else {
			processRect(*in, box->x, box->y + h, w + 1, h, &dc, &avgc);//LB
			boxes[size + 2] = createBox(box->x, box->y + h, w + 1, h, dc, avgc);

			processRect(*in, box->x + w + 1, box->y + h, w, h, &dc, &avgc);//RB
			boxes[size + 3] = createBox(box->x + w + 1, box->y + h, w, h, dc, avgc);
		}

	}
	else if (box->height % 2 != 0) {
		processRect(*in, (*box).x, (*box).y, w, h, &dc, &avgc);// LT
		boxes[size + 0] = createBox((*box).x, (*box).y, w, h, dc, avgc);

		processRect(*in, (*box).x + w, (*box).y, w, h, &dc, &avgc);//RT
		boxes[size + 1] = createBox((*box).x + w, (*box).y, w, h, dc, avgc);

		processRect(*in, (*box).x, (*box).y + h, w, h + 1, &dc, &avgc);//LB
		boxes[size + 2] = createBox((*box).x, (*box).y + h, w, h + 1, dc, avgc);

		processRect(*in, (*box).x + w, (*box).y + h, w, h + 1, &dc, &avgc);//RB
		boxes[size + 3] = createBox((*box).x + w, (*box).y + h, w, h + 1, dc, avgc);
	}

	else {
		processRect(*in, (*box).x, (*box).y, w, h, &dc, &avgc);
		boxes[size + 0] = createBox((*box).x, (*box).y, w, h, dc, avgc);

		processRect(*in, (*box).x + w, (*box).y, w, h, &dc, &avgc);
		boxes[size + 1] = createBox((*box).x + w, (*box).y, w, h, dc, avgc);

		processRect(*in, (*box).x + w, (*box).y + h, w, h, &dc, &avgc);
		boxes[size + 2] = createBox((*box).x + w, (*box).y + h, w, h, dc, avgc);

		processRect(*in, (*box).x, (*box).y + h, w, h, &dc, &avgc);
		boxes[size + 3] = createBox((*box).x, (*box).y + h, w, h, dc, avgc);
	}

	(*box).splited = 1;
}



int maxDelta(Box *boxes, uint size, int max_width) {
	int max = 0;
	for (uint i = 1; i < size; i++)
	{
		if (!boxes[i].splited) {
			if (boxes[i].width > max_width) {
				if (boxes[i].delta_color > boxes[max].delta_color) {
					max = i;
				}
				if (boxes[max].splited || boxes[max].width < max_width) {
					max = i;
				}
			}
		}
	}
	return max;
}


void drawBox(Image *out, Box box) {
	for (uint _x = box.x; _x < box.x + box.width; _x++)
	{
		for (uint _y = box.y; _y < box.y + box.height; _y++)
		{
			setPixel(out, _x, _y, box.color);
		}
	}
	Color black = createColor(0, 0, 0);
	for (uint x = box.x; x < box.x + box.width; x++)
	{
		setPixel(out, x, box.y, black);
		setPixel(out, x, box.y + box.height, black);
	}
	for (uint y = box.y; y < box.y + box.height; y++)
	{
		setPixel(out, box.x + box.width, y, black);
		setPixel(out, box.x, y, black);
	}
}

void drawBoxes(Image *out, Box *boxes, uint size) {
	for (uint i = 0; i < size; i++)
	{
		drawBox(out, boxes[i]);
	}
}

void processRect(Image image, int x, int y, int width, int height, int *delta_color, Color *avg_color) {

	int pixels_count = 0;

	int r = 0, g = 0, b = 0;

	uint8 minr = 255, ming = 255, minb = 255;
	uint8 maxr = 0, maxg = 0, maxb = 0;

	for (int _x = x; _x < x + width; _x++)
	{
		for (int _y = y; _y < y + height; _y++)
		{
			Color color = getPixel(image, _x, _y);
			r += color.r;
			g += color.g;
			b += color.b;

			if (color.r > maxr)maxr = color.r;
			if (color.g > maxg)maxg = color.g;
			if (color.b > maxb)maxb = color.b;

			if (color.r < minr)minr = color.r;
			if (color.g < ming)ming = color.g;
			if (color.b < minb)minb = color.b;

			pixels_count++;
		}
	}

	*delta_color = (maxr - minr) + (maxg - ming) + (maxb - minb);

	(*avg_color).r = r / pixels_count;
	(*avg_color).g = g / pixels_count;
	(*avg_color).b = b / pixels_count;

}


Box createBox(int x, int y, int width, int height, int delta_color, Color color) {
	Box box;
	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.delta_color = delta_color;
	box.color = color;
	box.splited = 0;

	return box;
}

Image quadify(Image *in, uint rep_count, int min_width) {
	Image out;
	out.height = in->height;
	out.width = in->width;
	out.size = in->size;
	out.pixels = malloc(sizeof(uint8)*in->size);

	memcpy(out.pixels, in->pixels, sizeof(uint8)*in->size);

	Color c;
	c = getPixel(*in, 50, 50);
	printf("%d %d %d\n", c.r, c.g, c.b);

	setPixel(&out, 50, 50, createColor(123,123,123));

	c = getPixel(*in, 50, 50);
	printf("%d %d %d\n", c.r, c.g, c.b);


	Box img;
	img.x = 0;
	img.y = 0;
	img.width = (*in).width;
	img.height = (*in).height;
	img.splited = 0;

	uint box_count = 4 * rep_count + 1;

	Box *boxes = malloc(box_count * sizeof(Box));

	boxes[0] = img;


	for (uint i = 0; i < rep_count; i++)
	{
		int size = 1 + i * 4;
		int max_delta = maxDelta(boxes, size, min_width);
		splitBox(in, &boxes[max_delta], boxes, size);
	}

	drawBoxes(&out, boxes, box_count);

	free(boxes);

	return out;
}
