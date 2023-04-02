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

//another shamelessly yanked from the book
hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = vec3::random(0,1.0) * vec3::random(0,1.0);
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}