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


bool vec3::near_zero() const {
    //returns true if vec3 is near zero
    const double s = 1e-8;
    return((fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s));
}


/*    v    n
 *    \    |   /    ^   v + 2b = this what we are looking for
 *     \   |  /     |   b = -dot(v,n) *n (beacuse n is unit vector)
 * --------|------  b
 *       \         ^
 *        \        |
 *
 */
vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2*dot(v,n)*n;
}


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

vec3 reflect(const vec3& v, const vec3& n);
vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}


vec3 random_unit_vec_sphere(){
    return unit_vector(random_in_unit_sphere());
}




vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0); //find smallest
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);  //R′⊥=η/η′(R+cosθn) //R′⊥=η/η′(R+(−R⋅n)n) we calcualte here this equation
        vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n; //R′∥=−√(1−|R′⊥|^2)n
    return r_out_perp + r_out_parallel; //vector addition //  //R′=R′⊥+R′∥
}


