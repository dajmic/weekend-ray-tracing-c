#include "camera.h"

#include "helper.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
Functionality:
    1. Construct and dispatch rays into the world.
    2. Use the results of these rays to construct the rendered image.
*/

void render(sphere_list *world)
{
    camera cam = init_cam();

    printf("P3\n%d %d\n255\n", cam.image_width, cam.image_height);

    for (int j = 0; j < cam.image_height; j++)
    {
        fprintf(stderr, "Scanlines remaining: %d\n", cam.image_height - j);

        for (int i = 0; i < cam.image_width; i++)
        {
            colour pixel_colour = init_colour(0.0, 0.0, 0.0);

            for (int sample = 0; sample < cam.samples_per_pixel; sample++)
            {
                ray r = get_ray(&cam, i, j);
                pixel_colour = v3_add(pixel_colour, ray_colour(r, cam.max_depth, world));
            }

            write_colour(v3_scale(pixel_colour, cam.pixel_samples_scale));
        }
    }
}

camera init_cam()
{
    camera cam;

    // Static settings
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1920;
    cam.samples_per_pixel = 100;
    cam.max_depth = 10; // Max. number of ray bounces.

    // Pixel samples scale
    cam.pixel_samples_scale = 1.0 / cam.samples_per_pixel;

    // Calculate image height based off width, ensure it's always >= 1
    int image_height = cam.image_width / cam.aspect_ratio;
    cam.image_height = image_height < 1 ? 1 : image_height;

    // Camera
    cam.camera_centre = init_p3(0.0, 0.0, 0.0);
    cam.focal_length = 1.0;
    float viewport_height = 2.0; // Arbitrary viewport height. Width is scaled to reach desired aspect ratio
    double viewport_width = viewport_height * ((double)cam.image_width / image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = init_v3(viewport_width, 0.0, 0.0);
    vec3 viewport_v = init_v3(0.0, -viewport_height, 0.0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    cam.pixel_delta_u = v3_scale(viewport_u, (1.0 / cam.image_width));
    cam.pixel_delta_v = v3_scale(viewport_v, (1.0 / cam.image_height));

    // Calculate the location of the upper left pixel.
    point3 p_focal_length = init_p3(0.0, 0.0, cam.focal_length);

    point3 focal_length_adjust = v3_subtract(cam.camera_centre, p_focal_length);
    point3 horizontal_adjust = v3_subtract(focal_length_adjust, v3_scale(viewport_u, 0.5));
    point3 viewport_upper_left = v3_subtract(horizontal_adjust, v3_scale(viewport_v, 0.5));
    cam.pixel_upper_left = v3_add(viewport_upper_left, v3_scale(v3_add(cam.pixel_delta_u, cam.pixel_delta_v), 0.5));

    return cam;
}

static colour ray_colour(ray r, int max_depth, sphere_list *world)
{
    hit_record hit_rec;

    if (sphere_list_hit(world, r, init_interval(0.0, INFINITY), &hit_rec))
    {
        // Calculate colour based on object hit and diffusion of material.
        vec3 direction = random_on_hemisphere(hit_rec.normal);
        // Recursively generate rays until no more objects are hit.
        return v3_scale(ray_colour(init_ray(hit_rec.point, direction), max_depth, world), 0.5);
    }

    // Background gradient.
    vec3 unit_direction = v3_unit(r.direction);
    double a = 0.5 * (unit_direction.y + 1.0);
    return v3_add(v3_scale(init_colour(1.0, 1.0, 1.0), (1.0 - a)), v3_scale(init_colour(0.5, 0.7, 1.0), a));
}

static vec3 sample_square()
{
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return init_v3(random_double() - 0.5, random_double() - 0.5, 0);
}

static ray get_ray(camera *cam, int i, int j)
{
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    vec3 offset = sample_square();
    point3 offset_x = v3_scale(cam->pixel_delta_u, i + offset.x);
    point3 offset_y = v3_scale(cam->pixel_delta_v, j + offset.y);
    point3 pixel_sample = v3_add(v3_add(cam->pixel_upper_left, offset_x), offset_y);

    point3 ray_origin = cam->camera_centre;
    vec3 ray_direction = v3_subtract(pixel_sample, ray_origin);

    return init_ray(ray_origin, ray_direction);
}