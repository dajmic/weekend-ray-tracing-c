#include "camera.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
Functionality:
    1. Construct and dispatch rays into the world.
    2. Use the results of these rays to construct the rendered image.
*/

void render(camera *cam, sphere_list *world)
{
    initialise(cam);

    printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);

    for (int j = 0; j < cam->image_height; j++)
    {
        fprintf(stderr, "Scanlines remaining: %d\n", cam->image_height - j);

        for (int i = 0; i < cam->image_width; i++)
        {
            vec3 pixel_offset_u = v3_scale(cam->pixel_delta_u, i);
            vec3 pixel_offset_v = v3_scale(cam->pixel_delta_v, j);
            point3 pixel_centre = v3_add(cam->pixel_upper_left, v3_add(pixel_offset_u, pixel_offset_v));

            // Currently camera_centre is at the origin, meaning the ray is directed to the centre of each pixel
            vec3 ray_direction = v3_subtract(pixel_centre, cam->camera_centre);

            ray r = init_ray(cam->camera_centre, ray_direction);

            colour pixel_colour = ray_colour(r, world);
            write_colour(pixel_colour);
        }
    }
}

static colour ray_colour(ray r, sphere_list *world)
{
    hit_record hit_rec;
    colour ray_colour;

    if (sphere_list_hit(world, r, init_interval(0.0, INFINITY), &hit_rec))
    {
        // Calculate colour based on object hit
        ray_colour = v3_scale(v3_add(hit_rec.normal, init_colour(1.0, 1.0, 1.0)), 0.5);
    }
    else
    {
        // Background gradient.
        vec3 unit_direction = v3_unit(r.direction);
        double a = 0.5 * (unit_direction.y + 1.0);
        ray_colour = v3_add(v3_scale(init_colour(1.0, 1.0, 1.0), (1.0 - a)), v3_scale(init_colour(0.5, 0.7, 1.0), a));
    }

    return ray_colour;
}

static void initialise(camera *cam)
{
    // Calculate image height based off width, ensure it's always >= 1
    int image_height = cam->image_width / cam->aspect_ratio;
    cam->image_height = image_height < 1 ? 1 : image_height;

    // Camera
    cam->camera_centre = init_p3(0.0, 0.0, 0.0);
    cam->focal_length = 1.0;
    float viewport_height = 2.0; // Arbitrary viewport height. Width is scaled to reach desired aspect ratio
    double viewport_width = viewport_height * ((double)cam->image_width / image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = init_v3(viewport_width, 0.0, 0.0);
    vec3 viewport_v = init_v3(0.0, -viewport_height, 0.0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    cam->pixel_delta_u = v3_scale(viewport_u, (1.0 / cam->image_width));
    cam->pixel_delta_v = v3_scale(viewport_v, (1.0 / cam->image_height));

    // Calculate the location of the upper left pixel.
    point3 p_focal_length = init_p3(0.0, 0.0, cam->focal_length);

    point3 focal_length_adjust = v3_subtract(cam->camera_centre, p_focal_length);
    point3 horizontal_adjust = v3_subtract(focal_length_adjust, v3_scale(viewport_u, 0.5));
    point3 viewport_upper_left = v3_subtract(horizontal_adjust, v3_scale(viewport_v, 0.5));
    cam->pixel_upper_left = v3_add(viewport_upper_left, v3_scale(v3_add(cam->pixel_delta_u, cam->pixel_delta_v), 0.5));
}