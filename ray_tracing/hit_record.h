#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "vec3.h"

#include <stdbool.h>

typedef struct
{
    point3 point;
    vec3 normal;
    double t;
    bool front_face;
} hit_record;

#endif