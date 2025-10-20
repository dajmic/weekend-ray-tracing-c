#include "sphere.h"

#include <math.h>
#include <stdlib.h>

Sphere sphere(Point3 centre, double radius)
{
	return (Sphere){ .centre = centre, .radius = fmax(0.0, radius) };
}

void sphere_list_add(SphereList *sl, Sphere s)
{
	// If the number of spheres is at the list maximum, increment the max value and reallocate memory to fit new sphere.
	if (sl->n == sl->max) {
		sl->max = sl->max ? 2 * sl->max : 1;
		sl->spheres = realloc(sl->spheres, sl->max * sizeof(s));
	}

	// Add new sphere to list.
	sl->spheres[sl->n] = s;
	sl->n++;
}

