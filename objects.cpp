//
// Created by grzes on 30.03.2023.
//

#include <cmath>

#include "objects.h"


//we are calculating t^2b_dot_b +2tb_dot_(A-C) + (A-C)_dot_(A-C) - r^2 = 0
//for t where ray is vector ray = A +tb
//r  = radius of sphere
//C = center of sphere defined in vec3
//a,b,c stands for a,b,c in delta = b^2 - 4ac
// b = 2h



bool sphere::hit(const ray& ray,double t_min, double t_max, hit_record& rec) const {
    vec3 AminusC = ray.origin() - center; //ray.origin is vector A
    double a = dot(ray.direction(),ray.direction()); //ray.direction is vector B
    double h = dot(ray.direction(),AminusC); //b halfed
    double c = dot(AminusC,AminusC) - radius*radius;
    double delta = h*h - a*c;
    if(delta < 0)
        return 0;
    double sqrt_d = sqrt(delta); //delta squared for clearer code

    // finding the nearest root that lies in the t_min t_max range

    double root = (-h - sqrt_d)/a;

    if(root < t_min || root > t_max){
        root = (-h + sqrt_d) / a;
        if(root < t_min || root > t_max)
            return 0; //all the answers are negative (doesn't work)
    }

    rec.t = root;
    rec.p = ray.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(ray,outward_normal);



    return 1;
}