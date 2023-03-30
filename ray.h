//
// Created by grzes on 30.03.2023.
//

#ifndef RAYTRACINGINONEWEEK_RAY_H
#define RAYTRACINGINONEWEEK_RAY_H

#include "vec3.h"

#include "ppm_files.h"



class ray { //ray is defined as vector of A + tb = ray which defines a line
    point3 orig;
    vec3 dir;
public:
    ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction)
    {}
    point3 origin() const {return orig;}
    vec3 direction() const{return dir;}


    point3 at(double t) const {
        return orig + t*dir;
    }
};

bool testRays();

double hit_Sphere(const point3& center, double radius,const ray& ray);

bool testSphere();
#endif //RAYTRACINGINONEWEEK_RAY_H
