//
// Created by grzes on 30.03.2023.
//
#include "vec3.h"

double vec3::x() const {return e[0];}
double vec3::y() const {return e[1];}
double vec3::z() const {return e[2];}



inline double random_double(double min = 0.0, double max = 1.0) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}
//snatched from constants



vec3 vec3::operator-() const {
    return vec3(-e[0],-e[1],-e[2]);
}

double vec3::operator[](int i) const{
    return e[i];
}


double& vec3::operator[](int i) {
    return e[i];
}

vec3& vec3::operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}


vec3& vec3::operator/=(const double t) {
    return *this *= 1/t;
}


double vec3::length() const {
    return std::sqrt(length_squared());
}

double vec3::length_squared() const {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

bool vec3::modX(double x){
    e[0] = x;
}
bool vec3::modY(double y){
    e[1] = y;
}
bool vec3::modZ(double z){
    e[2] = z;
}

vec3 vec3::random() {
    return vec3(random_double(),random_double(),random_double());
}

vec3 vec3::random(double min, double max) {
    return vec3(random_double(min,max),random_double(min,max),random_double(min,max));
}


vec3 random_in_unit_sphere() {
    vec3 p;
    do{
        p = vec3::random(-1,1);
    }while(p.length_squared() >= 1);
    return p;
}




