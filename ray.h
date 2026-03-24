#include "vec3.h"

class ray {
    public:
        vec3 origin;
        vec3 direction;

    vec3 at(double t) {
        return origin + direction*t;
    }
};