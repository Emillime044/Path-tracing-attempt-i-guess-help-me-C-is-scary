#ifndef MATERIAL
#define MATERIAL
#include "vec3.h"
#include "ray.h"
#include "utils.h"
struct hit_record;

class Material {
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};
#endif

