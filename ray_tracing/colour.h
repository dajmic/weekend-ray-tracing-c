#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

typedef vec3 colour;

void init_colour(colour *c, float r, float g, float b);
void write_colour(colour pixel_colour);

#endif