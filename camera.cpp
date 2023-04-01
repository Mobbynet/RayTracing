//
// Created by grzes on 30.03.2023.
//

#include "camera.h"


camera::camera(double vfov, // vertical field of view
               double aspect_ratio){
    double theta = degrees_to_radians(vfov);
    double h = tan(theta/2);
    double viewport_height = 2 * h;
    double viewport_width = viewport_height*aspect_ratio;


    double distance_between_plane = 1.0; //focal_length

    origin = point3(0,0,0);
    horizontal = vec3(viewport_width,0,0);
    vertical = vec3(0,viewport_height,0);
    lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, distance_between_plane);
}

ray camera::get_ray(double u, double v) const {
    return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}