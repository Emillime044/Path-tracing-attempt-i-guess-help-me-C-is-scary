#ifndef HIT_L
#define HIT_L
#include <vector>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class HittableList : public Hittable {
    public:
        std::vector<Hittable*> objects; // lista di puntatori a hittable

        void add(Hittable* object) {
            objects.push_back(object);
        }

        bool hit(const ray&r, hit_record& rec) override {
            bool hit_anything = false;
            for (Hittable* obj: objects) {
                if (obj->hit(r, rec)) {
                    hit_anything = true;
                }
            }
            return hit_anything;
        }
};

#endif