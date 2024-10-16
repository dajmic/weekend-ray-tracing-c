#include "vec3.h"
#include <math.h>

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

vec3 v3_scale(vec3 v, double scale)
{
    v.x *= scale;
    v.y *= scale;
    v.z *= scale;

    return v;
}

double v3_dot(vec3 v, vec3 u) { return (v.x * u.x) + (v.y * u.y) + (v.z * u.z); }

vec3 v3_cross(vec3 v, vec3 u)
{
    vec3 cross_product;

    cross_product.x = (v.y * u.z) - (v.z * u.y);
    cross_product.y = (v.z * u.x) - (v.x * u.z);
    cross_product.z = (v.x * u.y) - (v.y * u.x);

    return cross_product;
}

double v3_length(vec3 v) { return sqrt(v3_dot(v, v)); }

vec3 v3_unit(vec3 v) { return v3_scale(v, 1 / v3_length(v)); }