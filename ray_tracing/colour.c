#include "colour.h"

#include <stdio.h>

colour init_colour(double r, double g, double b)
{
    colour c;

    c.x = r;
    c.y = g;
    c.z = b;

    return c;
}

void write_colour(colour pixel_colour)
{
    double r = pixel_colour.x;
    double g = pixel_colour.y;
    double b = pixel_colour.z;

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = 255.999 * r;
    int gbyte = 255.999 * g;
    int bbyte = 255.999 * b;

    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}
