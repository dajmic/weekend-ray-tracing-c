#ifndef VEC3_H
#define VEC3_H

typedef struct {
	double x, y, z;
} Vec3;

typedef Vec3 Point3;

Vec3 v3(double x, double y, double z);
Point3 p3(double x, double y, double z);
Vec3 v3_random();
Vec3 v3_random_in_range(double min, double max);
Vec3 random_unit_vector();
Vec3 random_on_hemisphere(Vec3 normal);
Vec3 v3_neg(Vec3 v);
Vec3 v3_add(Vec3 v, Vec3 u);
Vec3 v3_subtract(Vec3 v, Vec3 u);
Vec3 v3_multiply(Vec3 v, Vec3 u);
Vec3 v3_scale(Vec3 v, float scale);
double v3_dot(Vec3 v, Vec3 u);
Vec3 v3_cross(Vec3 v, Vec3 u);
double v3_length(Vec3 v);
double v3_length_squared(Vec3 v);
Vec3 v3_unit(Vec3 v);
void v3_print(Vec3 v);

#endif

