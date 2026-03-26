#ifndef METAL
#define METAL
#include "material.h"
#include "hit_record.h"
#include "utils.h"

class Metal : public Material {
    public: 
        vec3 albedo;
        double fuzz = 0.2;
        Metal(vec3 albedo) {
            this->albedo = albedo;
        }
        Metal(vec3 albedo, double fuzz) {
            this->albedo = albedo;
            this->fuzz = fuzz;
        }
        virtual inline bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override {
            vec3 reflected = r_in.direction - rec.N * 2*r_in.direction.dotProduct(rec.N);
            vec3 direction = reflected + random_unit_vector() * fuzz;
            ray ray_reflected(rec.intersection, direction);
            scattered = ray_reflected;
            attenuation = albedo;
            return true;
        }
};

#endif