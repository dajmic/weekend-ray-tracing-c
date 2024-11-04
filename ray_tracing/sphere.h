#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "hit_record.h"

#include <stdbool.h>

typedef struct
{
    double min, max;
} interval;

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

interval init_interval(double min, double max);
sphere init_sphere(point3 centre, double radius);
void sphere_list_add(sphere_list *sl, sphere s);
bool sphere_list_hit(sphere_list *sl, ray r, interval t, hit_record *hit_rec);
bool hit_sphere(sphere s, ray r, interval t, hit_record *hit_rec);

#endif