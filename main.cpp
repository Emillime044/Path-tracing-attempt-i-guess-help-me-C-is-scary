#include <iostream>
#include <cmath>
#include "vec3.h"
#include "ray.h"

double hit_sphere(vec3 center, double radius, const ray& r) {
    vec3 Q = r.origin - center;
    double a = r.direction.dotProduct(r.direction);
    double b = 2*Q.dotProduct(r.direction);
    double c = Q.dotProduct(Q) - radius*radius;
    double discriminant = b*b - 4*(a*c);
    
    if (discriminant < 0) {
        return -1; // non sono su un punto della sfera, resituisco -1
    } else { 
        return ((-b - sqrt(discriminant)) / (2*a)); // se tocco un punto della sfera restituisco t
    }
}

vec3 ray_color(const ray& other) {
    vec3 center(0,0,-1);
    vec3 unit_direction = other.direction.normalize();
    double t = hit_sphere(center, 0.5, other);
    double t_ray_direction = (unit_direction.y + 1) / 2;
    vec3 white(1,1,1);
    vec3 lightblue(0.5,0.7,1.0);
    
    vec3 N = (other.at(t) - center).normalize(); // calcolo la normale per colorare la sfera
    
    if (t > 0) {
        return (N + vec3(1,1,1)) * 0.5;
    }
    return white*(1-t_ray_direction) + lightblue*t_ray_direction;
}

int main() {
    // Image
    int image_width = 6880;
    int image_height = 2880;
    vec3 origin(0, 0, 0);
    double aspect_ratio = (double)image_width / image_height;
    vec3 horizontal(2.0*aspect_ratio, 0, 0);
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
