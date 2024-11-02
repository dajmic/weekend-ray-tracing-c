#include "colour.h"
#include "sphere.h"
#include "ray.h"
#include "vec3.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

const double PI = 3.1415926535897932385;

double degrees_to_radians(double degrees)
{
    return (degrees * PI) / 180.0;
}

main(void)
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
    double viewport_width = viewport_height * ((double)image_width / image_height);

    // World
    sphere_list world;
    sphere_list_add(&world, init_sphere(init_p3(0.0, 0.0, -1.0), 0.5));
    sphere_list_add(&world, init_sphere(init_p3(0.0, -100.5, -1.0), 100));

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = init_v3(viewport_width, 0.0, 0.0);
    vec3 viewport_v = init_v3(0.0, -viewport_height, 0.0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = v3_scale(viewport_u, (1.0 / image_width));
    vec3 pixel_delta_v = v3_scale(viewport_v, (1.0 / image_height));

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

            // Currently camera_centre is at the origin, meaning the ray is directed to the centre of each pixel
            vec3 ray_direction = v3_subtract(pixel_centre, camera_centre);

            ray r = init_ray(camera_centre, ray_direction);

            colour pixel_colour = ray_colour(r, &world);
            write_colour(pixel_colour);
        }
    }

    return 0;
}