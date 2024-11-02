#include "ray.h"
#include "vec3.h"

#include <math.h>

point3 init_p3(double x, double y, double z)
{
    point3 p;

    p.x = x;
    p.y = y;
    p.z = z;

    return p;
}

ray init_ray(point3 origin, vec3 direction)
{
    ray r;

    r.origin = origin;
    r.direction = direction;

    return r;
}

// P(t) = A + tB
point3 ray_at(ray r, double t) { return v3_add(r.origin, v3_scale(r.direction, t)); }

colour ray_colour(ray r, sphere_list *world)
{
    hit_record hit_rec;

    if (sphere_list_hit(world, r, init_interval(0, INFINITY), &hit_rec))
    {
        return v3_scale(v3_add(hit_rec.normal, init_colour(1.0, 1.0, 1.0)), 0.5);
    }

    vec3 unit_direction = v3_unit(r.direction);
    double a = 0.5 * (unit_direction.y + 1.0);
    return v3_add(v3_scale(init_colour(1.0, 1.0, 1.0), (1.0 - a)), v3_scale(init_colour(0.5, 0.7, 1.0), a));
}