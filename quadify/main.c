#include "image.h"
#include "box.h"


Image img_in, img_out;
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

	img_in = load_image(img_1);
	
	img_out = img_in;
	
	fclose(img_1);
	fclose(img_2);
	remove(argv[2]);
}

int main(int argc, char *argv[]) {
	init(argc, argv);


	quadify(&img_in, &img_out, repeat_count,20);


	if (strstr(argv[2], ".png") != NULL) {
		save_png(img_out, argv[2]);
	}
	else {
		save_jpg(img_out, argv[2], 100);
	}

	return 0;
}