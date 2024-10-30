#include "sphere.h"

#include <math.h>
#include <stdbool.h>

sphere init_sphere(point3 centre, double radius)
{
    sphere s;

    s.centre = centre;
    s.radius = fmax(0.0, radius); // Avoid negative radius.

    return s;
}

bool hit_sphere(sphere sphere, ray ray, double ray_tmin, double ray_tmax, hit_record hit_rec)
{
    vec3 oc = v3_subtract(sphere.centre, ray.origin);
    double a = length_squared(ray.direction);
    double h = v3_dot(ray.direction, oc);
    double c = length_squared(oc) - (sphere.radius * sphere.radius);
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
    }

    hit_rec.t = root;
    hit_rec.point = ray_at(ray, hit_rec.t);
    hit_rec.normal = v3_scale(v3_subtract(hit_rec.point, sphere.centre), 1 / sphere.radius);

    return true;
}