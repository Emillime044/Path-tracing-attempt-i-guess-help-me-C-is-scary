#ifndef SPHERE
#define SPHERE
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class Sphere : public Hittable {
    public:
        vec3 center;
        double radius;

        Sphere(vec3 center, double radius) {
            this->center = center;
            this->radius = radius;
        }
    
        bool hit(const ray& r, hit_record& rec) const override {
            vec3 Q = r.origin - center;
            double a = r.direction.dotProduct(r.direction);
            double b = 2*Q.dotProduct(r.direction);
            double c = Q.dotProduct(Q) - radius*radius;
            double discriminant = b*b - 4*(a*c);
            
            if (discriminant < 0) {
                return false; // non sono su un punto della sfera
            } else { 
                double t = ((-b - sqrt(discriminant)) / (2*a)); // se tocco un punto della sfera restituisco t
                rec.t = t;
                rec.intersection = r.at(t);
                rec.N = (rec.intersection - center).normalize();
                return true;
            }
        }
};

#endif