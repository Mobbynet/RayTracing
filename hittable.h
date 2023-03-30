//
// Created by grzes on 30.03.2023.
//

#ifndef RAYTRACINGINONEWEEK_HITTABLE_H
#define RAYTRACINGINONEWEEK_HITTABLE_H

#include "constants.h"



struct hit_record{
    vec3 normal;
    point3 p;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r,const vec3& outward_normal){ //this helps to make that the normal always faces outward of the surfaces
        front_face = dot(r.direction(),outward_normal) < 0;  //dot products help determine they relative relation to each other
        if(front_face)
            normal = outward_normal; //ray is inside the sphere
        else
            normal = -outward_normal; //ray is outside the sphere
    }
};


class hittable {
public:
    virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& rec) const = 0;
};



class hittable_list : public hittable{
private:
    std::vector<std::shared_ptr<hittable>> objects;

public:
    hittable_list() {};

    hittable_list(std::shared_ptr<hittable> object) {
        add(object);
    }

    void clear() {
        objects.clear();
    }
    void add(std::shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;
};



#endif //RAYTRACINGINONEWEEK_HITTABLE_H
