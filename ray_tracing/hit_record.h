#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "ray.h"
#include "vec3.h"

typedef struct
{
    point3 p;
    vec3 normal;
    double t;
} hit_record;

#endif