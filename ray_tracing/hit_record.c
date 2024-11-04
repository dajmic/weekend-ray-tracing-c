#include "hit_record.h"

void set_face_normal(hit_record *hit_rec, ray r, vec3 outward_normal)
{
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    bool front_face = dot(r.direction, outward_normal) < 0;

    hit_rec->front_face = front_face;
    hit_rec->normal = front_face ? outward_normal : v3_neg(outward_normal);
}