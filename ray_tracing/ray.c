#include "ray.h"

#include "vec3.h"

void init_point3(point3 *p, float x, float y, float z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

void init_ray(ray *r, point3 origin, vec3 direction)
{
    r->origin = origin;
    r->direction = direction;
}

point3 ray_interpolate(ray r, double t) { return v3_add(r.origin, v3_scale(r.direction, t)); }
