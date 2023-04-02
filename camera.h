//
// Created by grzes on 30.03.2023.
//

#ifndef RAYTRACINGINONEWEEK_CAMERA_H
#define RAYTRACINGINONEWEEK_CAMERA_H

#include "constants.h"

class camera {
private:
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 lower_left_corner;
    vec3 u, v, w;
    double lens_radius;


public:
    camera(double vfov,
           point3 lookfrom,
           point3 lookat,
           vec3   vup,// vertical field of view
           double aspect_ratio,
    double aperture,
    double focus_dist);
    ray get_ray(double s, double t) const;
    point3 getOrigin(){return origin;}
    vec3 getHorizontal(){return horizontal;}
    vec3 getVertical(){return vertical;}
    vec3 getLower_left_corner(){return lower_left_corner;}



};


#endif //RAYTRACINGINONEWEEK_CAMERA_H
