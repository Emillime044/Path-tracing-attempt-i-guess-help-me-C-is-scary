#ifndef LAMBERTIAN
#define LAMBERTIAN
#include "material.h"
#include "utils.h"

class Lambertian : public Material {
    public: vec3 albedo;
        Lambertian(vec3 albedo) {
            this->albedo = albedo;
        }
    
        bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override {
            vec3 direction = rec.N + random_unit_vector();
            ray ray_reflected(rec.intersection, direction);
            scattered = ray_reflected;
            attenuation = albedo;
            return true;
        }
};

#endif