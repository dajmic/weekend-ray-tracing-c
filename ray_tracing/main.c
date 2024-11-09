#include "camera.h"
#include "sphere.h"
#include "vec3.h"

#include <math.h>
#include <stdlib.h>

const double PI = 3.1415926535897932385;

double degrees_to_radians(double degrees)
{
    return (degrees * PI) / 180.0;
}

int main(void)
{
    // World
    sphere_list *world = malloc(sizeof *world);
    sphere_list_add(world, init_sphere(init_p3(0.0, -100.5, -1.0), 100));
    sphere_list_add(world, init_sphere(init_p3(0.0, 0.0, -1.0), 0.5));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;

    render(&cam, world);

    return 0;
}