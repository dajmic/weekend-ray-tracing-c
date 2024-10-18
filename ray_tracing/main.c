#include "colour.h"
#include "vec3.h"
#include <stdio.h>

int main(void)
{
    const int HEIGHT = 256;
    const int WIDTH = 256;

    printf("P3\n%d %d\n255\n", WIDTH, HEIGHT);

    for (int j = 0; j < HEIGHT; j++)
    {
        fprintf(stderr, "Scanlines remaining: %d\n", HEIGHT - j);

        for (int i = 0; i < WIDTH; i++)
        {
            colour pixel_colour;

            init_vec3(&pixel_colour, (double)i / (WIDTH - 1), (double)j / (HEIGHT - 1), 0.0);

            write_colour(pixel_colour);
        }
    }

    return 0;
}