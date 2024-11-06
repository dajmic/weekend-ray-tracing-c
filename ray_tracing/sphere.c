#include "sphere.h"

#include <math.h>
#include <stdlib.h>

sphere init_sphere(point3 centre, double radius)
{
    sphere s;

    s.centre = centre;
    s.radius = fmax(0.0, radius); // Avoid negative radius.

    return s;
}

interval init_interval(double min, double max)
{
    interval i;

    i.min = min;
    i.max = max;

    return i;
}

void sphere_list_add(sphere_list *sl, sphere s)
{
    // If the number of spheres is at the list maximum, increment the max value and reallocate memory to fit new sphere.
    if (sl->n == sl->max)
    {
        sl->max = sl->max ? 2 * sl->max : 1;
        sl->spheres = realloc(sl->spheres, sl->max * sizeof(s));
    }

    // Add new sphere to list.
    sl->spheres[sl->n] = s;
    sl->n++;
}
