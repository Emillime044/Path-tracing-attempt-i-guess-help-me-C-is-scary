#ifndef HITTABLE
#define HITTABLE
#include "vec3.h"
#include "ray.h"
#include "hit_record.h"

class Hittable {
    public: virtual bool hit(const ray& r, hit_record& rec) const = 0;
};

#endif