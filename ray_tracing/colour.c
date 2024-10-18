#include "colour.h"
#include "vec3.h"
#include <stdio.h>

void write_colour(colour pixel_colour)
{
    float r = pixel_colour.x;
    float g = pixel_colour.y;
    float b = pixel_colour.z;

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = 255.999 * r;
    int gbyte = 255.999 * g;
    int bbyte = 255.999 * b;

    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}