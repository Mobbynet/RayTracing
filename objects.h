//
// Created by grzes on 30.03.2023.
//

#ifndef RAYTRACINGINONEWEEK_OBJECTS_H
#define RAYTRACINGINONEWEEK_OBJECTS_H

#include "hittable.h"


//sphere

class sphere :  public hittable {
    public:
        sphere() {};
        sphere(point3 center,double radius) : center(center), radius(radius){};
        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& rec) const override;

    private:
        point3 center;
        double radius;
    };


#endif //RAYTRACINGINONEWEEK_OBJECTS_H
