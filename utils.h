#pragma once
#include <random>
#include "vec3.h"

inline double random_double() {
    static thread_local std::mt19937 generator(std::random_device{}());
    static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}
inline double random_double(double min, double max) {
    static thread_local std::uniform_real_distribution<double> distribution(min, max);
    static thread_local std::mt19937 generator;
    return distribution(generator);
}
inline vec3 random_unit_vector() {
    double x = random_double(-1,1);
    double y = random_double(-1,1);
    double z = random_double(-1,1);
    vec3 v(x,y,z);
    return v.normalize();
}
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    // Inverto la direzione del raggio per fare in modo che vada nella stessa direzione della normale
    double cos_theta = (-uv).dotProduct(n);
    // Estraggo la parte del raggio parallela alla superficie
    vec3 r_perp = (uv + n * cos_theta) * etai_over_etat;
    // Manca la parte verticale del vettore, faccio in modo che il vettore abbia lunghezza 1
    double under_sqrt = 1.0 - r_perp.dotProduct(r_perp);
    vec3 r_par = n * -sqrt(fmax(0.0, under_sqrt));
    return r_perp + r_par;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - n * 2 * v.dotProduct(n);
}


