#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "ray.h"
#include "vec3.h"

#include <stdbool.h>

typedef struct
{
    point3 point;
    vec3 normal;
    double t;
    bool front_face;
} hit_record;

void set_face_normal(hit_record *hit_rec, ray r, vec3 outward_normal);

#endif