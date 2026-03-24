#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray {
    public:
        vec3 origin;
        vec3 direction;

    ray(vec3 origin, vec3 direction) {
        this->origin=origin;
        this->direction=direction;
    }

    vec3 at(double t) {
        return origin + direction*t;
    }
};

#endif