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
    const int image_height = static_cast<int>(image_width * aspect_ratio);
    ppm_file ray_test("debug_ray_test_file",image_width,image_height);

    //camera
    const int viewport_height = 2;
    const int viewport_width = static_cast<int>(viewport_height/aspect_ratio);

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
            ray_test.writeRGBToPos(pixel_color.e[0],pixel_color.e[1],pixel_color.e[2],h,w);
        }
    }
    ray_test.saveFile("Testing Ray functionalty by coloring them with weird function taken from the book");
    return true;
}



//we are calculating t^2b_dot_b +2tb_dot_(A-C) + (A-C)_dot_(A-C) - r^2 = 0
//for t where ray is vector ray = A +tb
//r  = radius of sphere
//C = center of sphere defined in vec3
// we are looking not for a solution to t but only delta
//a,b,c stands for a,b,c in delta = b^2 - 4ac


bool hit_sphere(const point3& center, double radius,const ray& ray){
    vec3 AminusC = ray.origin() - center; //ray.origin is vector A
    double a = dot(ray.direction(),ray.direction()); //ray.direction is vector B
    double b = 2.0 * dot(ray.direction(),AminusC);
    double c = dot(AminusC,AminusC) - radius*radius;
    double delta = b*b - 4*a*c;
    return (delta > 0);
    //this whole thing could've been a one return bool, but it is clearer that way
}   //I may change this in the future cause it takes a lot of time to do it

color ray_color_sphere(const ray& r) {
    if (hit_sphere(point3(0,0,-2), 0.3, r)) //center of sphere is 0,0,-1 and radius 0.5
        return {1, 0, 0};                              //if the ray hits sphere show pixel red
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
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
            auto u = double(w) / (width-1);
            auto v = double(h) / (height-1);
            ray r(origin,lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color_sphere(r);
            ray_test.writeRGBToPos(pixel_color.e[0],pixel_color.e[1],pixel_color.e[2],h,w);
        }
    }
    ray_test.saveFile("Testing sphere detection by coloring them with weird function taken from the book");
    return true;
}


