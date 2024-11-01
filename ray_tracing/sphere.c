#include "sphere.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

sphere init_sphere(point3 centre, double radius)
{
    sphere s;

    s.centre = centre;
    s.radius = fmax(0.0, radius); // Avoid negative radius.

    return s;
}

void sphere_list_add(sphere_list *sl, sphere s)
{
    // If the number of spheres is at the list maximum, increment the max value and reallocate memory to fit new sphere.
    if (sl->n == sl->max)
    {
        sl->max = sl->max ? 2 * sl->max : 1;
        assert(sl->spheres = realloc(sl->spheres, sl->max * sizeof(*sl->spheres)));
    }

    // Add new sphere to list.
    sl->spheres[sl->n++] = s;
}

bool hit_sphere(sphere s, ray r, double ray_tmin, double ray_tmax, hit_record hit_rec)
{
    vec3 oc = v3_subtract(s.centre, r.origin);
    double a = length_squared(r.direction);
    double h = v3_dot(r.direction, oc);
    double c = length_squared(oc) - (s.radius * s.radius);
    double discriminant = (h * h) - (a * c);

    // Ray doesn't hit.
    if (discriminant < 0)
    {
        return false;
    }

    // Finding the nearest route that lies between ray_tmin and ray_tmax.
    double sqrt_discriminant = sqrt(discriminant);
    double root = (h - sqrt_discriminant) / a;

    if (root <= ray_tmin || ray_tmax <= root)
    {
        double root = (h + sqrt_discriminant) / a;

        if (root <= ray_tmin || ray_tmax <= root)
        {
            return false;
        }

        hit_rec.t = root;
        hit_rec.point = ray_at(r, hit_rec.t);
        vec3 outward_normal = v3_scale(v3_subtract(hit_rec.point, s.centre), 1 / s.radius);
        set_face_normal(&hit_rec, r, outward_normal);

        return true;
    }
}