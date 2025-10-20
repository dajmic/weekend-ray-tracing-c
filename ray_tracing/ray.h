#ifndef RAY_H
#define RAY_H

#include "hit_record.h"
#include "interval.h"
#include "sphere.h"
#include "vec3.h"

#include <stdbool.h>

typedef struct {
	Point3 origin;
	Vec3 direction;
} Ray;

Ray ray(Point3 origin, Vec3 direction);
Point3 ray_at(Ray r, double t);
bool sphere_list_hit(SphereList *sl, Ray r, Interval t, HitRecord *hit_rec);
bool hit_sphere(Sphere s, Ray r, Interval t, HitRecord *hit_rec);
void set_face_normal(HitRecord *hit_rec, Ray r, Vec3 outward_normal);

#endif

