#ifndef MATERIAL
#define MATERIAL
#include "vec3.h"
#include "ray.h"
#include "hit_record.h"
#include "utils.h"

class Material {
    public: virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;

    vec3 random_unit_vector() {
        double x = random_double(-1,1);
        double y = random_double(-1,1);
        double z = random_double(-1,1);
        vec3 v(x,y,z);
        return v.normalize();
    }
};

#endif