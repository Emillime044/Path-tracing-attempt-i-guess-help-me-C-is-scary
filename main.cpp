#include <iostream>
#include <cmath>
#include "vec3.h"
#include "ray.h"

vec3 ray_color(const ray& other) {
    vec3 unit_direction = other.direction.normalize();
    double t = (unit_direction.y + 1) / 2;
    vec3 white(1,1,1);
    vec3 lightblue(0.5,0.7,1.0);
    
    //std::cerr << "t=" << t << " y=" << unit_direction.y << "\n";
    
    return white*(1-t) + lightblue*t;
}

int main() {
    // Image
    int image_width = 256;
    int image_height = 256;
    vec3 origin(0, 0, 0);
    vec3 horizontal(4.0, 0, 0);
    vec3 vertical(0, 2.0, 0);

    vec3 lower_left = origin - horizontal/2 - vertical/2 - vec3(0,0,1);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(int j = 0; j < image_height; j++) {
        std::cerr << image_height-j << " lines remaining\r";
        for(int i = 0; i < image_width; i++) {
            double u = (double)i / (image_width - 1); // Quanto sono avanzato orizzontalmente, in percentuale
            double v = (double)(image_height - 1 - j) / (image_height - 1); // Quanto sono avanzato verticalmente, in percentuale

            vec3 point_viewport = lower_left + horizontal*u + vertical*v;
            vec3 direction = point_viewport - origin;

            ray r(origin, direction);
            vec3 color = ray_color(r);

            color.x = int(255.999 * color.x);
            color.y = int(255.999 * color.y);
            color.z = int(255.999 * color.z);

            std::cout << color.x << ' ' << color.y << ' ' << color.z << '\n';
        }
    }
    return 0;
}
