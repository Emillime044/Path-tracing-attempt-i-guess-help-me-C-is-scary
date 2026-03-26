#ifndef DIELECTRIC
#define DIELECTRIC
#include "material.h"
#include "hit_record.h"
#include "utils.h"

class Dielectric : public Material {
    public: 
        double refraction_index = 1;

        Dielectric() {
            this->refraction_index = refraction_index;
        }
        Dielectric(double refraction_index) {
            this->refraction_index = refraction_index;
        }
        
        virtual inline bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override {
            attenuation = vec3(1,1,1);
            bool entering = r_in.direction.dotProduct(rec.N) < 0;

            // Se ti dimentichi (succederà) è un if compatto
            // also, ri = rapporto tra η/η'
            double ri = entering ? (1.0 / refraction_index) : refraction_index;
            vec3 normal = entering ? rec.N : rec.N * -1;
            double cos_theta = (-r_in.direction.normalize()).dotProduct(normal);
            vec3 direction;
            double discriminant = 1.0 - ri*ri*(1.0 - cos_theta*cos_theta);

            if(discriminant > 0) {
                direction = refract(r_in.direction.normalize(), normal, ri);
            } else {
                direction = reflect(r_in.direction.normalize(), normal);
            }
            scattered = ray(rec.intersection, direction);
            return true;
        }
};

#endif