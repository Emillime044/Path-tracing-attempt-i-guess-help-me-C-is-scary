#ifndef HIT_R
#define HIT_R
#include "vec3.h"
#include "ray.h"

struct hit_record {
    double t;
    vec3 intersection;
    vec3 N;
};

#endif