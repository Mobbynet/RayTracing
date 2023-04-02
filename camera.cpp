//
// Created by grzes on 30.03.2023.
//

#include "camera.h"


camera::camera(double vfov,
               point3 lookfrom,
               point3 lookat,
               vec3   vup,// vertical field of view
               double aspect_ratio,
               double aperture,
               double focus_dist){
    double theta = degrees_to_radians(vfov);
    double h = tan(theta/2);
    double viewport_height = 2 * h;
    double viewport_width = viewport_height*aspect_ratio;


    double distance_between_plane = 1.0; //focal_length

    w = unit_vector(lookfrom-lookat);
    u = unit_vector(cross(vup,w));
    v = cross(w,u);

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

    lens_radius = aperture / 2;




}

ray camera::get_ray(double s, double t) const {
    vec3 rd = lens_radius * random_in_unit_disk(); //depth of field
    vec3 offset = u * rd.x() + v * rd.y();

    return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
}