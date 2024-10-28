#include "ray.h"

#include "vec3.h"

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

point3 ray_at(ray r, double t) { return v3_add(r.origin, v3_scale(r.direction, t)); }
