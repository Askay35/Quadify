#include "window.h"
#include "surface.h"
#include "box.h"
#include <stdlib.h>
#include <string.h>

#define main main

Image in, out;
SDL_Surface *image_surface;
Window window;
uint repeat_count;
uint min_width=10;
SDL_Texture *image_tex;

uint8 border = 0;

void init(int argc, char *argv[]) {
	FILE *img_1, *img_2;

	if (argc - 1 > 3) {
		printf("Too many arguments!");
		exit(-1);
	}
	if (argc - 1 < 3) {
	
		if (argc == 3) {
			repeat_count = 1;
		}
		else {
			printf("Too few arguments!");
			exit(-1);
		}
	}
	else {
		sscanf(argv[3], "%d", &repeat_count);
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
}

void updateImage() {
	free(out.pixels);
	SDL_FreeSurface(image_surface);
	SDL_DestroyTexture(image_tex);

	out = quadify(&in, repeat_count, min_width, border);
	image_surface = loadSurfaceFromMemory(out);
	image_tex = SDL_CreateTextureFromSurface(window.renderer, image_surface);	
	
}


int main(int argc, char *argv[]) {
	init(argc, argv);
	
	window = windowInit(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, "Quadify", SDL_WINDOW_SHOWN);

	updateImage();
	
	SDL_Rect window_rect = { 0,0,window.w-10, window.h-10};

	uint8 close = 0;

	char *fpath = (char*)malloc(strlen(argv[2]+1+10));

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
				case SDLK_LEFT:
					if (min_width > 8) {
						min_width -= 2;
						updateImage();
					}
					break;
				case SDLK_RIGHT:
					min_width += 2;
					updateImage();
					break;
				case SDLK_b:
					if (border) {
						border = 0;
					}
					else {
						border = 1;
					}
					updateImage();
					break;
				case SDLK_SPACE:
					_itoa(repeat_count, fpath, 10);
					strcat(fpath, argv[2]);
					saveImage(&out, fpath);
					break;
				default:
					break;
				}
			}

		}

		SDL_RenderClear(window.renderer);
		
		SDL_RenderCopy(window.renderer, image_tex, NULL, &window_rect);

		SDL_RenderPresent(window.renderer);

	}

	free(fpath);
	windowDestroy(&window);
	SDL_DestroyTexture(image_tex);
	SDL_FreeSurface(image_surface);

	return 0;
}