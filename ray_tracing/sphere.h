#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"

typedef struct {
	Point3 centre;
	double radius;
} Sphere;

typedef struct {
	Sphere *spheres;
	int n, max;
} SphereList;

Sphere sphere(Point3 centre, double radius);
void sphere_list_add(SphereList *sl, Sphere s);

#endif
