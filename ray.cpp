//
// Created by grzes on 30.03.2023.
//

#include "ray.h"


color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return color(1.0, 1.0, 1.0) - t*color(0.5, 0.3, 0.0);
}


bool testRays(){


    //img
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    ppm_file ray_test("debug_ray_test_file",image_width,image_height);

    //camera
    const int viewport_height = 2;
    const int viewport_width = static_cast<int>(viewport_height*aspect_ratio);

    const double distance_between_plane = 1.0; //focal_length

    point3 origin = point3(0,0,0);
    vec3 horizontal = vec3(viewport_width,0,0);
    vec3 vertical = vec3(0,viewport_height,0);
    vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, distance_between_plane);


    int height = ray_test.getHeight();
    int width = ray_test.getWidth();
    for (int h = 0; h < height; ++h) {
        for(int w = 0; w < width; ++w){
            auto u = double(w) / (width-1);
            auto v = double(h) / (height-1);
            ray r(origin,lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            ray_test.writeRGBToPos(pixel_color.x(),pixel_color.y(),pixel_color.z(),h,w);
        }
    }
    ray_test.saveFile("Testing Ray functionalty by coloring them with weird function taken from the book");
    return 0;
}



//we are calculating t^2b_dot_b +2tb_dot_(A-C) + (A-C)_dot_(A-C) - r^2 = 0
//for t where ray is vector ray = A +tb
//r  = radius of sphere
//C = center of sphere defined in vec3
//a,b,c stands for a,b,c in delta = b^2 - 4ac
// b = 2h

double hit_sphere(const point3& center, double radius,const ray& ray){
    vec3 AminusC = ray.origin() - center; //ray.origin is vector A
    double a = dot(ray.direction(),ray.direction()); //ray.direction is vector B
    double h = dot(ray.direction(),AminusC);
    double c = dot(AminusC,AminusC) - radius*radius;
    double delta = h*h - a*c;
    if(delta < 0)
        return -1.0;
    else{
        return (-h - sqrt(delta)) / (a); //quadratic formula :)))
    }




}

color ray_color_sphere(const ray& r) {
    point3 center(0,0,-1);
    double t = hit_sphere(center, 0.3, r); //we are looking for t to calcualte a surface normal(vector | to the surface)
    if(t > 0.0){
        vec3 N = unit_vector(r.at(t)- center); //normal vector
        return 0.5*color(N.x()+1,N.y()+1,N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return color(1.0, 1.0, 1.0) - t*color(0.5, 0.3, 0.0);
}


bool testSphere(){
    //img
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 900;
    const int image_height = static_cast<int>(image_width/aspect_ratio);
    ppm_file ray_test("debug_sphere_test_file",image_width,image_height);

    //camera
    const int viewport_height = 2;
    const int viewport_width = static_cast<int>(viewport_height * aspect_ratio);

    const double distance_between_plane = 1.0; //focal_length

    point3 origin = point3(0,0,0);
    vec3 horizontal = vec3(viewport_width,0,0);
    vec3 vertical = vec3(0,viewport_height,0);
    vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, distance_between_plane);


    int height = ray_test.getHeight();
    int width = ray_test.getWidth();
    for (int h = 0; h < height; ++h) {
        for(int w = 0; w < width; ++w){
            double u = double(w) / (width-1);
            double v = double(h) / (height-1);
            ray r(origin,lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color_sphere(r);
            ray_test.writeRGBToPos(pixel_color.x(),pixel_color.y(),pixel_color.z(),h,w);
        }
    }
    ray_test.saveFile("Testing sphere detection by coloring them with weird function taken from the book");
    return 0;
}


