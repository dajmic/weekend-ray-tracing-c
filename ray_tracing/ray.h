#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef vec3 point3;

typedef struct
{
    point3 origin;
    vec3 direction;
} ray;

point3 init_p3(double x, double y, double z);
ray init_ray(point3 origin, vec3 direction);
point3 ray_interpolate(ray r, double t);

#endif