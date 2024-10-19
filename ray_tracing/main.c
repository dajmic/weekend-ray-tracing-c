#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include <stdio.h>

int main(void)
{
    const float ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 400;

    // Calculate image height based off width, ensure it's always >= 1
    int image_height = IMAGE_WIDTH / ASPECT_RATIO;
    image_height = image_height < 1 ? 1 : image_height;

    // Camera
    const point3 CAMERA_CENTRE;
    init_point3(&CAMERA_CENTRE, 0.0, 0.0, 0.0);
    const float FOCAL_LENGTH = 1.0;
    const float VIEWPORT_HEIGHT = 2.0; // Arbitrary viewport height. Width is scaled to reach desired aspect ratio
    const float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (IMAGE_WIDTH / image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    const vec3 VIEWPORT_U;
    const vec3 VIEWPORT_V;
    init_vec3(&VIEWPORT_U, VIEWPORT_WIDTH, 0.0, 0.0);
    init_vec3(&VIEWPORT_V, 0.0, -VIEWPORT_HEIGHT, 0.0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    const vec3 PIXEL_DELTA_U = v3_scale(VIEWPORT_U, (1 / IMAGE_WIDTH));
    const vec3 PIXEL_DELTA_V = v3_scale(VIEWPORT_V, (1 / image_height));

    // Calculate the location of the upper left pixel.
    // auto viewport_upper_left = camera_center
    //  - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    // auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    printf("P3\n%d %d\n255\n", WIDTH, HEIGHT);

    for (int j = 0; j < HEIGHT; j++)
    {
        fprintf(stderr, "Scanlines remaining: %d\n", HEIGHT - j);

        for (int i = 0; i < WIDTH; i++)
        {
            colour pixel_colour;

            init_colour(&pixel_colour, (double)i / (WIDTH - 1), (double)j / (HEIGHT - 1), 0.0);

            write_colour(pixel_colour);
        }
    }

    return 0;
}