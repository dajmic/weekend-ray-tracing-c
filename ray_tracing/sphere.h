#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "hit_record.h"

typedef struct
{
    point3 centre;
    double radius;
} sphere;

typedef struct
{
    sphere *spheres;
    int n, max;
} sphere_list;

sphere init_sphere(point3 centre, double radius);
bool hit_sphere(ray r, double ray_tmin, double ray_tmax, hit_record rec);

#endif