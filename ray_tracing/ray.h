#ifndef RAY_H
#define RAY_H

#include "colour.h"
#include "hit_record.h"
#include "sphere.h"
#include "vec3.h"

#include <stdbool.h>

typedef struct
{
    point3 origin;
    vec3 direction;
} ray;

point3 init_p3(double x, double y, double z);
ray init_ray(point3 origin, vec3 direction);
point3 ray_at(ray r, double t);
bool sphere_list_hit(sphere_list *sl, ray r, interval t, hit_record *hit_rec);
bool hit_sphere(sphere s, ray r, interval t, hit_record *hit_rec);
void set_face_normal(hit_record *hit_rec, ray r, vec3 outward_normal);
colour ray_colour(ray r, sphere_list *world);

#endif