#ifndef HIT_L
#define HIT_L
#include <vector>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class HittableList : public Hittable {
    public:
        std::vector<Hittable*> objects; // lista di puntatori a hittable

        virtual inline void add(Hittable* object) {
            objects.push_back(object);
        }

        virtual inline bool hit(const ray&r, hit_record& rec) const override {
            bool hit_anything = false;
            double closest_t = 1e18;
            hit_record temp_rec;
            for (Hittable* obj: objects) {
                if (obj->hit(r, temp_rec) && temp_rec.t < closest_t) {
                    hit_anything = true;
                    closest_t = temp_rec.t;
                    rec = temp_rec;
                }
            }
            return hit_anything;
        }
};

#endif