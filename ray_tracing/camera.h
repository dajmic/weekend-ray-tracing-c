#ifndef CAMERA_H
#define CAMERA_H

#include "colour.h"
#include "sphere.h"
#include "ray.h"

typedef struct {
	float aspect_ratio, focal_length, pixel_samples_scale;
	int image_width, image_height, samples_per_pixel, max_depth;
	Point3 camera_centre, pixel_upper_left;
	Vec3 pixel_delta_u, pixel_delta_v;
} Camera;

void render(SphereList *world);
Camera camera();
static Colour ray_colour(Ray r, int max_depth, SphereList *world);
static Vec3 sample_square();
static Ray get_ray(Camera *cam, int i, int j);

#endif

