#ifndef CAMERA_H
#define CAMERA_H

#include "colour.h"
#include "sphere.h"
#include "ray.h"

typedef struct
{
    float aspect_ratio;
    int image_width;
    int image_height;
    float focal_length;
    point3 camera_centre;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    point3 pixel_upper_left;
} camera;

void render(camera *cam, sphere_list *world);
static colour ray_colour(ray r, sphere_list *world);
static void initialise(camera *cam);

#endif