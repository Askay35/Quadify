#include "window.h"
#include "surface.h"
#include "box.h"

#define main main

Image in, out;
SDL_Surface *image_surface;
Window window;
uint repeat_count;

void init(int argc, char *argv[]) {
	FILE *img_1, *img_2;

	sscanf(argv[3], "%d", &repeat_count);

	if (argc - 1 > 3) {
		printf("Too many arguments!");
		exit(-1);
	}
	if (argc - 1 < 3) {
		printf("Too few arguments!");
		exit(-1);
	}

	if ((img_1 = fopen(argv[1], "rb")) == NULL) {
		printf("First argument is incorrect!");
		exit(-1);
	}
	if (strstr(argv[2], ".") == NULL) {
		printf("Second argument must have file extension!");
		exit(-1);
	}

	if ((img_2 = fopen(argv[2], "wb")) == NULL) {
		printf("Second argument is incorrect!");
		exit(-1);
	}

	in = load_image(img_1);

	fclose(img_1);
	fclose(img_2);
	remove(argv[2]);
	window = windowInit(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, "Quadify 1.0v", SDL_WINDOW_SHOWN);
}

void updateImage() {
	image_surface = NULL;

	out = quadify(&in, repeat_count, 10);

	image_surface = loadSurfaceFromMemory(out);
	
	image_surface = resizeSurface(image_surface, window.w-4, window.h-4);
}

int main(int argc, char *argv[]) {
	init(argc, argv);
	
	updateImage();

	if (strstr(argv[2], ".png") != NULL) {
		save_png(out, argv[2]);
	}
	else {
		save_jpg(out, argv[2], 100);
	}




	uint8 close = 0;

	while (!close) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				close = 1;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					repeat_count++;
					updateImage();
					break;
				case SDLK_DOWN:
					if (repeat_count > 1) {
						repeat_count--;
						updateImage();
					}
					break;
				default:
					break;
				}
			}

		}

		windowSwapSurface(&window, image_surface);
	}

	windowDestroy(&window);

	return 0;
}