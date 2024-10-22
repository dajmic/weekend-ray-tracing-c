#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include <stdio.h>

colour ray_colour(ray r);

int main(void)
{
    float aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate image height based off width, ensure it's always >= 1
    int image_height = image_width / aspect_ratio;
    image_height = image_height < 1 ? 1 : image_height;

    // Camera
    point3 camera_centre = init_p3(0.0, 0.0, 0.0);
    float focal_length = 1.0;
    float viewport_height = 2.0; // Arbitrary viewport height. Width is scaled to reach desired aspect ratio
    float viewport_width = viewport_height * (image_width / image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = init_v3(viewport_width, 0.0, 0.0);
    vec3 viewport_v = init_v3(0.0, -viewport_height, 0.0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = v3_scale(viewport_u, (1 / image_width));
    vec3 pixel_delta_v = v3_scale(viewport_v, (1 / image_height));

    // Calculate the location of the upper left pixel.
    point3 p_focal_length = init_p3(0.0, 0.0, focal_length);

    point3 focal_length_adjust = v3_subtract(camera_centre, p_focal_length);
    point3 horizontal_adjust = v3_subtract(focal_length_adjust, v3_scale(viewport_u, 0.5));
    point3 viewport_upper_left = v3_subtract(horizontal_adjust, v3_scale(viewport_v, 0.5));
    point3 pixel_upper_left = v3_add(viewport_upper_left, v3_scale(v3_add(pixel_delta_u, pixel_delta_v), 0.5));

    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++)
    {
        fprintf(stderr, "Scanlines remaining: %d\n", image_height - j);

        for (int i = 0; i < image_width; i++)
        {
            vec3 pixel_offset_u = v3_scale(pixel_delta_u, i);
            vec3 pixel_offset_v = v3_scale(pixel_delta_v, j);
            point3 pixel_centre = v3_add(pixel_upper_left, v3_add(pixel_offset_u, pixel_offset_v));

            vec3 ray_direction = v3_subtract(pixel_centre, camera_centre);

            ray r = init_ray(camera_centre, ray_direction);

            colour pixel_colour = ray_colour(r);
            write_colour(pixel_colour);
        }
    }

    return 0;
}

colour ray_colour(ray r)
{
    vec3 unit_direction = v3_unit(r.direction);
    float a = 0.5 * (unit_direction.y + 1.0);

    colour white = init_colour(1.0, 1.0, 1.0);
    colour white_gradient = v3_scale(white, (1.0 - a));
    v3_print(white_gradient); // Not changing?
    colour blue = init_colour(0.5, 0.7, 1.0);
    colour blue_gradient = v3_scale(blue, a);

    return v3_add(white_gradient, blue_gradient);
}