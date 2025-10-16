#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"

typedef struct {
    point3 centre;
    double radius;
} sphere;

typedef struct {
    sphere *spheres;
    int n, max;
} sphere_list;

sphere init_sphere(point3 centre, double radius);
void sphere_list_add(sphere_list *sl, sphere s);

#endif
