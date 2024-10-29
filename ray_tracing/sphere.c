#include "sphere.h"

#include <stdbool.h>

sphere init_sphere(point3 centre, double radius)
{
    sphere s;

    s.centre = centre;
    s.radius = radius;

    return s;
}

bool hit_sphere(ray r, double ray_tmin, double ray_tmax, hit_record rec)
{
    return true;
}

// bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
//     vec3 oc = center - r.origin();
//     auto a = r.direction().length_squared();
//     auto h = dot(r.direction(), oc);
//     auto c = oc.length_squared() - radius*radius;

//     auto discriminant = h*h - a*c;
//     if (discriminant < 0)
//         return false;

//     auto sqrtd = std::sqrt(discriminant);

//     // Find the nearest root that lies in the acceptable range.
//     auto root = (h - sqrtd) / a;
//     if (root <= ray_tmin || ray_tmax <= root) {
//         root = (h + sqrtd) / a;
//         if (root <= ray_tmin || ray_tmax <= root)
//             return false;
//     }

//     rec.t = root;
//     rec.p = r.at(rec.t);
//     rec.normal = (rec.p - center) / radius;

//     return true;
// }