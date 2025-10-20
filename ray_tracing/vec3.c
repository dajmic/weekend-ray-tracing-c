#include "vec3.h"

#include "helper.h"

#include <math.h>
#include <stdio.h>

Vec3 v3(double x, double y, double z)
{
	return (Vec3){ .x = x, .y = y, .z = z };
}

Point3 p3(double x, double y, double z)
{
	return (Point3){ .x = x, .y = y, .z = z };
}

// For surface diffusion
Vec3 v3_random()
{
	return v3(random_double(), random_double(), random_double());
}

Vec3 v3_random_in_range(double min, double max)
{
	return v3(random_double_in_range(min, max),
			  random_double_in_range(min, max),
			  random_double_in_range(min, max));
}

Vec3 random_unit_vector()
{
	while (1) {
		Vec3 p = v3_random_in_range(-1.0, 1.0);
		double length_squared = v3_length_squared(p);

		// Make sure unit vector lies within unit circle. If the random Vec3
		// contains very small values, squaring this will result in 0 hence the
		// first condition.
		if (1.0E-160 < length_squared && length_squared <= 1.0) {
			return v3_scale(p, 1 / sqrt(length_squared));
		}
	}
}

Vec3 random_on_hemisphere(Vec3 normal)
{
	Vec3 on_unit_sphere = random_unit_vector();

	if (v3_dot(on_unit_sphere, normal) >
		0.0) // In the same hemisphere as the normal vector.
	{
		return on_unit_sphere;
	}

	return v3_neg(on_unit_sphere);
}

Vec3 v3_add(Vec3 v, Vec3 u)
{
	v.x += u.x;
	v.y += u.y;
	v.z += u.z;

	return v;
}

Vec3 v3_subtract(Vec3 v, Vec3 u)
{
	v.x -= u.x;
	v.y -= u.y;
	v.z -= u.z;

	return v;
}

Vec3 v3_multiply(Vec3 v, Vec3 u)
{
	v.x *= u.x;
	v.y *= u.y;
	v.z *= u.z;

	return v;
}

Vec3 v3_scale(Vec3 v, float scale_factor)
{
	v.x *= scale_factor;
	v.y *= scale_factor;
	v.z *= scale_factor;

	return v;
}

double v3_dot(Vec3 v, Vec3 u)
{
	return (v.x * u.x) + (v.y * u.y) + (v.z * u.z);
}

Vec3 v3_cross(Vec3 v, Vec3 u)
{
	return (Vec3){ .x = (v.y * u.z) - (v.z * u.y),
				   .y = (v.z * u.x) - (v.x * u.z),
				   .z = (v.x * u.y) - (v.y * u.x) };
}

double v3_length(Vec3 v)
{
	return sqrt(v3_dot(v, v));
}

double v3_length_squared(Vec3 v)
{
	return v3_dot(v, v);
}

Vec3 v3_unit(Vec3 v)
{
	return v3_scale(v, 1 / v3_length(v));
}

Vec3 v3_neg(Vec3 v)
{
	return v3_scale(v, -1);
}

void v3_print(Vec3 v)
{
	fprintf(stderr, "x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

