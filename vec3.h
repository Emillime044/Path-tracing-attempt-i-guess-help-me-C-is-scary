#ifndef VEC3_H
#define VEC3_H

class vec3 {
    public:
        double x, y, z;
    
    vec3() : x(0), y(0), z(0) {}

    vec3(double x, double y, double z) {
        this->x=x;
        this->y=y;
        this->z=z;
    }
    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }
    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }
    vec3 operator*(const double other) const {
        return vec3(x * other, y * other, z * other);
    }
    vec3 operator*(const vec3 other) const {
        return vec3(x * other.x, y * other.y, z * other.z);
    }
    vec3 operator/(const double other) const {
        return vec3(x / other, y/other, z/other);
    }
    vec3 crossProduct(const vec3& other) const  {
        return vec3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
    }
    double length() const {
        return sqrt(x*x + y*y + z*z);
    }
    double dotProduct(const vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    vec3 normalize() const {
        double l = length();
        return vec3(x/l, y/l, z/l);
    }
};

#endif