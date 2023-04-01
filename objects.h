//
// Created by grzes on 30.03.2023.
//

#ifndef RAYTRACINGINONEWEEK_OBJECTS_H
#define RAYTRACINGINONEWEEK_OBJECTS_H

#include "hittable.h"

/* Class for storing objects and materials */





//sphere

class sphere :  public hittable {
    public:
        sphere() {};
        sphere(point3 center,double radius, std::shared_ptr<material> mat_ptr) : center(center), radius(radius), mat_ptr(mat_ptr){};
        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& rec) const override;

    private:
        point3 center;
        double radius;
        std::shared_ptr<material> mat_ptr;
    };


//materials


class material{
public:
    virtual bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation, ray& scattered) const = 0;
};



class lambertian : public material {
public:
    lambertian(const color& albedo) : albedo(albedo) {};
    virtual bool scatter(
    const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
            ) const override;

private:
    color albedo;
};


class metal : public material{
public:
    metal(const color& albedo,double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}; //if fuzz < 1 then fuzz if bigger then round it to 1
    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override;
private:
    color albedo;
    double fuzz;
};

class dielectric : public material{
public:
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}
    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override;


private:
    double ir;
    static double reflectance(double cosine, double ref_idx);
};


#endif //RAYTRACINGINONEWEEK_OBJECTS_H
