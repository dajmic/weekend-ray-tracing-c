#include "colour.h"

#include "interval.h"

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

    interval intensity = init_interval(0.0, 0.999);

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = 255.999 * clamp(&intensity, r);
    int gbyte = 255.999 * clamp(&intensity, g);
    int bbyte = 255.999 * clamp(&intensity, b);

    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}
