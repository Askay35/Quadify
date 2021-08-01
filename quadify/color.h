#pragma once

#include "types.h"

#define RGB 3
#define DEPTH 24


typedef struct Color {
	uint8 r, g, b;
}Color;

Color createColor(uint8 r, uint8 g, uint8 b);


