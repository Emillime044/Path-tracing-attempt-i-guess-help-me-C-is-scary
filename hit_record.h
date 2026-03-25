#ifndef HIT_R
#define HIT_R
#include "vec3.h"
#include "ray.h"
class Material;

struct hit_record {
    double t;
    Material* material;
    vec3 intersection;
    vec3 N;
};

#endif