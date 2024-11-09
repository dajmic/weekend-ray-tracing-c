#include "ray.h"

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

bool sphere_list_hit(sphere_list *sl, ray r, interval t, hit_record *hit_rec)
{
    bool hit = false;
    double closest_so_far = t.max;
    hit_record tmp_hit_rec;

    // Iterate over spheres, start at the back of the scene and work forward by reassigning 'closest_so_far'.
    for (int i = 0; i < sl->n; i++)
    {
        if (hit_sphere(sl->spheres[i], r, init_interval(t.min, closest_so_far), &tmp_hit_rec))
        {
            hit = true;
            closest_so_far = tmp_hit_rec.t;
            *hit_rec = tmp_hit_rec;
        }
    }

    return hit;
}

bool hit_sphere(sphere s, ray r, interval t, hit_record *hit_rec)
{
    vec3 oc = v3_subtract(s.centre, r.origin);
    double a = v3_length_squared(r.direction);
    double h = v3_dot(r.direction, oc);
    double c = v3_length_squared(oc) - (s.radius * s.radius);
    double discriminant = (h * h) - (a * c);

    // Ray doesn't hit.
    if (discriminant < 0)
    {
        return false;
    }

    // Finding the route that lies between ray_tmin and ray_tmax.
    double sqrt_discriminant = sqrt(discriminant);
    double root = (h - sqrt_discriminant) / a;

    if (!surrounds(&t, root))
    {
        double root = (h + sqrt_discriminant) / a;

        if (!surrounds(&t, root))
        {
            return false;
        }
    }

    hit_rec->t = root;
    hit_rec->point = ray_at(r, hit_rec->t);
    vec3 outward_normal = v3_scale(v3_subtract(hit_rec->point, s.centre), 1.0 / s.radius);
    set_face_normal(hit_rec, r, outward_normal);

    return true;
}

void set_face_normal(hit_record *hit_rec, ray r, vec3 outward_normal)
{
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    bool front_face = v3_dot(r.direction, outward_normal) < 0;

    hit_rec->front_face = front_face;
    hit_rec->normal = front_face ? outward_normal : v3_neg(outward_normal);
}

colour ray_colour(ray r, sphere_list *world)
{
    hit_record hit_rec;
    colour ray_colour;

    if (sphere_list_hit(world, r, init_interval(0.0, INFINITY), &hit_rec))
    {
        // Calculate colour based on object hit
        ray_colour = v3_scale(v3_add(hit_rec.normal, init_colour(1.0, 1.0, 1.0)), 0.5);
    }
    else
    {
        // Background gradient.
        vec3 unit_direction = v3_unit(r.direction);
        double a = 0.5 * (unit_direction.y + 1.0);
        ray_colour = v3_add(v3_scale(init_colour(1.0, 1.0, 1.0), (1.0 - a)), v3_scale(init_colour(0.5, 0.7, 1.0), a));
    }

    return ray_colour;
}