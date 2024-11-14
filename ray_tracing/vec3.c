#include "vec3.h"

#include "helper.h"

#include <math.h>
#include <stdio.h>

vec3 init_v3(double x, double y, double z)
{
    vec3 v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}

// For surface diffusion
vec3 init_v3_random()
{
    return init_v3(random_double(), random_double(), random_double());
}

vec3 init_v3_random_in_range(double min, double max)
{
    return init_v3(random_double_in_range(min, max), random_double_in_range(min, max), random_double_in_range(min, max));
}

vec3 random_unit_vector()
{
    while (1)
    {
        vec3 p = init_v3_random_in_range(-1.0, 1.0);
        double length_squared = v3_length_squared(p);

        // Make sure unit vector lies within unit circle. If the random vec3 contains very small values, squaring this will result in 0 hence the first condition.
        if (1.0E-160 < length_squared && length_squared <= 1.0)
        {
            return v3_scale(p, 1 / sqrt(length_squared));
        }
    }
}

vec3 random_on_hemisphere(vec3 normal)
{
    vec3 on_unit_sphere = random_unit_vector();

    if (v3_dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal vector.
    {
        return on_unit_sphere;
    }

    return v3_neg(on_unit_sphere);
}

point3 init_p3(double x, double y, double z)
{
    point3 p;

    p.x = x;
    p.y = y;
    p.z = z;

    return p;
}

double v3x(vec3 v) { return v.x; }

double v3y(vec3 v) { return v.y; }

double v3z(vec3 v) { return v.z; }

vec3 v3_add(vec3 v, vec3 u)
{
    v.x += u.x;
    v.y += u.y;
    v.z += u.z;

    return v;
}

vec3 v3_subtract(vec3 v, vec3 u)
{
    v.x -= u.x;
    v.y -= u.y;
    v.z -= u.z;

    return v;
}

vec3 v3_multiply(vec3 v, vec3 u)
{
    v.x *= u.x;
    v.y *= u.y;
    v.z *= u.z;

    return v;
}

vec3 v3_scale(vec3 v, float scale)
{
    v.x *= scale;
    v.y *= scale;
    v.z *= scale;

    return v;
}

double v3_dot(vec3 v, vec3 u)
{
    return (v.x * u.x) + (v.y * u.y) + (v.z * u.z);
}

vec3 v3_cross(vec3 v, vec3 u)
{
    vec3 cross_product;

    cross_product.x = (v.y * u.z) - (v.z * u.y);
    cross_product.y = (v.z * u.x) - (v.x * u.z);
    cross_product.z = (v.x * u.y) - (v.y * u.x);

    return cross_product;
}

double v3_length(vec3 v) { return sqrt(v3_dot(v, v)); }

double v3_length_squared(vec3 v) { return v3_dot(v, v); }

vec3 v3_unit(vec3 v) { return v3_scale(v, 1 / v3_length(v)); }

vec3 v3_neg(vec3 v)
{
    return v3_scale(v, -1);
}

void v3_print(vec3 v)
{
    fprintf(stderr, "x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}