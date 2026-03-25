#include <iostream>
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"
#include "hit_record.h"
#include "utils.h"
#include "lambertian.h"

vec3 ray_color(const ray& r, const HittableList& items, int depth) {
    if (depth <= 0) return vec3(0,0,0);

    hit_record rec;
    if (items.hit(r, rec)) {
        vec3 attenuation;
        ray scattered(vec3(0,0,0), vec3(0,0,0));
        if (rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, items, depth-1);
        }
        return vec3(0,0,0);
    }

    // Gradiente cielo
    vec3 unit_direction = r.direction.normalize();
    double t = (unit_direction.y + 1.0) * 0.5;
    vec3 white(1.0, 1.0, 1.0);
    vec3 lightblue(0.5, 0.7, 1.0);
    return white*(1.0-t) + lightblue*t;
}

int main() {
    // Immagine
    const double aspect_ratio = 21.0 / 9.0;
    const int image_width = 3440;
    const int image_height = int(image_width / aspect_ratio);

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * aspect_ratio;
    vec3 camera_center(0, 0, 0);

    // Vettori del viewport
    vec3 viewport_u(viewport_width, 0, 0);   // orizzontale, sinistra->destra
    vec3 viewport_v(0, viewport_height, 0); // verticale, alto->basso (negativo!)

    // Delta da pixel a pixel
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Angolo in alto a sinistra del viewport
    vec3 viewport_upper_left = camera_center
        - vec3(0, 0, focal_length)
        - viewport_u / 2
        - viewport_v / 2;

    // Centro del primo pixel (0,0)
    vec3 pixel00 = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

    // Scena
    HittableList items;
    items.add(new Sphere(vec3(2, 0, -3), 0.4, new Lambertian(vec3(0.8, 0.2, 0.2))));
    items.add(new Sphere(vec3(-2, 0, -3), 0.4, new Lambertian(vec3(0.2, 0.2, 0.8))));
    items.add(new Sphere(vec3(0, 0, -3), 0.4, new Lambertian(vec3(0.2, 0.8, 0.2))));
    
    items.add(new Sphere(vec3(0, -100.5, -10), 100.0, new Lambertian(vec3(0.7, 0.7, 0.7))));

    // Render
    const int samples = 100;
    const int max_depth = 10;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::cerr << image_height - j << " lines remaining\r";
        for (int i = 0; i < image_width; i++) {
            vec3 color(0, 0, 0);
            for (int s = 0; s < samples; s++) {
                // Offset casuale per antialiasing
                double offset_u = random_double() - 0.5;
                double offset_v = random_double() - 0.5;

                vec3 pixel_center = pixel00
                    + pixel_delta_u * (i + offset_u)
                    + pixel_delta_v * ((image_height - 1 - j) + offset_v);

                vec3 direction = pixel_center - camera_center;
                ray r(camera_center, direction);
                color = color + ray_color(r, items, max_depth);
            }
            color = color / samples;

            // Gamma correction (gamma 2)
            color = vec3(sqrt(color.x), sqrt(color.y), sqrt(color.z));

            std::cout << int(255.999 * color.x) << ' '
                      << int(255.999 * color.y) << ' '
                      << int(255.999 * color.z) << '\n';
        }
    }

    std::cerr << "\nDone.\n";
    return 0;
}