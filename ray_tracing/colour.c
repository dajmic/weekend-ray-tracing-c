#include "colour.h"

#include "interval.h"

#include <stdio.h>

Colour colour(double r, double g, double b)
{
	return (Colour){ .x = r, .y = g, .z = b };
}

void write_colour(Colour pixel_colour)
{
	double r = pixel_colour.x;
	double g = pixel_colour.y;
	double b = pixel_colour.z;

	Interval intensity = interval(0.0, 0.999);

	// Translate the [0,1] component values to the byte range [0,255].
	int rbyte = 255.999 * clamp(&intensity, r);
	int gbyte = 255.999 * clamp(&intensity, g);
	int bbyte = 255.999 * clamp(&intensity, b);

	printf("%d %d %d\n", rbyte, gbyte, bbyte);
}
