#include <iostream>
#include <random>
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"
#include "hit_record.h"
#include "utils.h"

vec3 ray_color(const ray& other, const HittableList& items) {
    vec3 center(0,0,-1);
    vec3 unit_direction = other.direction.normalize();
    double t_ray_direction = (unit_direction.y + 1) / 2;
    vec3 white(1,1,1);
    vec3 lightblue(0.5,0.7,1.0);
    
    hit_record rec;

    if (items.hit(other, rec)) {
        return (rec.N + vec3(1,1,1)) * 0.5;
    }
    return white*(1-t_ray_direction) + lightblue*t_ray_direction;
}

int main() {
    // Image
    int image_width = 512;
    int image_height = 512;
    vec3 origin(0, 0, 0);
    double aspect_ratio = (double)image_width / image_height;
    vec3 horizontal(2.0*aspect_ratio, 0, 0);
    vec3 vertical(0, 2.0, 0);

    HittableList items;
    // (x,y,z), r
    items.add(new Sphere(vec3(1,0,-5), 0.5));
    items.add(new Sphere(vec3(-1,0,-5), 0.5));
    items.add(new Sphere(vec3(0,1,-5), 0.5));
    items.add(new Sphere(vec3(0,-1,-5), 0.5));
    items.add(new Sphere(vec3(0,0,-5), 0.5));

    vec3 lower_left = origin - horizontal/2 - vertical/2 - vec3(0,0,3);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(int j = 0; j < image_height; j++) {
        std::cerr << image_height-j << " lines remaining\r";
        for(int i = 0; i < image_width; i++) {
            vec3 color(0,0,0);
            for (int s = 0; s < 100; s++) {
                // genero i double randomicamente per fare un loop per antialiasing
                double u = (double)(i + random_double()) / (image_width - 1); 
                double v = (double)(j + random_double()) / (image_height - 1);

                // lancio i raggi
                vec3 point_viewport = lower_left + horizontal*u + vertical*v; 
                vec3 direction = point_viewport - origin;
                ray r(origin, direction);
                
                color = color + ray_color(r, items);
            }
            color = color / 100; // faccio la media del color

            color.x = int(255.999 * color.x);
            color.y = int(255.999 * color.y);
            color.z = int(255.999 * color.z);

            std::cout << color.x << ' ' << color.y << ' ' << color.z << '\n';
        }
    }
    return 0;
}
