#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef vec3 point3;

typedef struct
{
    point3 origin;
    vec3 direction;
} ray;

void init_ray(ray *r, point3 origin, vec3 direction);

point3 ray_origin(ray r);

vec3 ray_direction(ray r);

point3 ray_interpolate(ray r, double t);

#endif