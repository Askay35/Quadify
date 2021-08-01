#include "image.h"

#define STB_IMAGE_IMPLEMENTATION  
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"


int save_jpg(Image image, char* filename, uint8 quality) {
	return stbi_write_jpg(filename, image.width, image.height, RGB, image.pixels, quality);
}

int save_png(Image image, char* filename) {
	return stbi_write_png(filename, image.width, image.height, RGB, image.pixels, image.width*RGB);
}

Color getPixel(Image image, int x, int y) {
	int index = getPixelIndex(image, x, y);
	Color color = createColor(0, 0, 0);
	if (index + 2 < image.size) {
		color.r = image.pixels[index];
		color.g = image.pixels[index + 1];
		color.b = image.pixels[index + 2];
	}
	return color;
}


void setPixel(Image *image, int x, int y, Color color) {
	int index = getPixelIndex(*image, x, y);
	if (index + 2 < image->size) {
		(*image).pixels[index] = color.r;
		(*image).pixels[index + 1] = color.g;
		(*image).pixels[index + 2] = color.b;
	}
}

Image load_image(FILE *file) {
	Image img;
	img.pixels = stbi_load_from_file(file, &img.width, &img.height, NULL, RGB);

	int size = img.width * img.height * RGB;

	img.size = size;

	return img;
}

int getPixelIndex(Image image, int x, int y) {
	return RGB * (y * image.width + x);
}


