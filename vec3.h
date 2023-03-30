//
// Created by grzes on 29.03.2023.
//

#ifndef RAYTRACINGINONEWEEK_VEC3_H
#define RAYTRACINGINONEWEEK_VEC3_H

#include <cmath>
#include <iostream>



class vec3 {
private:
    double e[3];
    friend class ppm_file;
    bool modX(double x);
    bool modY(double y);
    bool modZ(double z);
    public:
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0,e1,e2}{}

        double x() const;
        double y() const;
        double z() const;



        vec3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);


    vec3& operator+=(const vec3 &v);

    vec3& operator*=(const double t);

    vec3& operator/=(const double t);

    double length() const;

    double length_squared() const;

};

using point3 = vec3;
using color = vec3;


//utility functions
inline std::ostream& operator<<(std::ostream &out,const vec3 &v){
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3 &u, const vec3 &v){
    return vec3(u.x() + v.x(),u.y() + v.y(),u.z()+v.z());
}

inline vec3 operator-(const vec3 &u, const vec3 &v){
    return vec3(u.x() - v.x(),u.y() - v.y(),u.z()-v.z());
}

inline vec3 operator*(const vec3 &u, const vec3 &v){
    return vec3(u.x() * v.x(),u.y() * v.y(),u.z()*v.z());
}

inline vec3 operator*(double t, const vec3 &v){
    return vec3(t * v.x(),t * v.y(),t*v.z());
}

inline vec3 operator*(const vec3 &u, double t){
    return t*u;
}

inline vec3 operator/(const vec3 &v,double t){
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v){
    return u.x() * v.x()
           + u.y() * v.y()
           + u.z() * v.z();
}

inline vec3 cross(const vec3 &u, const vec3 &v){
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline vec3 unit_vector(vec3 v){
    return v/v.length();
}






#endif //RAYTRACINGINONEWEEK_VEC3_H
