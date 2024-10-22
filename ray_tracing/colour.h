#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

typedef vec3 colour;

colour init_colour(double r, double g, double b);
void write_colour(colour pixel_colour);

#endif