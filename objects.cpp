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
    rec.mat_ptr = mat_ptr;


    return 1;
}


bool lambertian::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const {
    //works for not perfect reflective surfaces
    //just normal surfaces like idk wood and stuff

    vec3 scatter_direction = rec.normal + random_unit_vec_sphere();

    //catches degenerate(if random_unit_vec_sphere = -rec.normal ) vectors that would do nothing and make blind spots
    if(scatter_direction.near_zero())
        scatter_direction = rec.normal;


    scattered = ray(rec.p ,scatter_direction);
    attenuation = albedo;
    return true;
}


bool metal::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const {
    //works  perfect reflective surfaces
    //metals

    vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);

    scattered = ray(rec.p ,reflected + fuzz*random_unit_vec_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0); //we check if not 90 degrees
}

bool dielectric::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const {
    attenuation = color(1.0,1.0,1.0);
    double refraction_ratio = rec.front_face ? 1.0/ir : ir;



    vec3 unit_dir = unit_vector(r_in.direction());
    double cos_theta = fmin(dot(-unit_dir,rec.normal),1.0);
    double sin_theta = sqrt(1-cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;

    vec3 direction;
    if(cannot_refract || reflectance(cos_theta,refraction_ratio) > random_double()){
        direction = reflect(unit_dir,rec.normal);
    }
    else{
        direction = refract(unit_dir, rec.normal, refraction_ratio);
    }
    scattered = ray(rec.p, direction);

    return true;
}


double dielectric::reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}