//
// Created by grzes on 30.03.2023.
//



#include "debug_fun.h"





color ray_color(const ray &r) {
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return color(1.0, 1.0, 1.0) - t*color(0.5, 0.3, 0.0);
}

bool testRays() {


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

color ray_color_sphere(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}



bool testSphere(){
    // Img

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);


    //world (hittable list)

    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0,0,-1),0.5));
    world.add(std::make_shared<sphere>(point3(0,-1.5,-1), 10));

    //camera
    const int viewport_height = 2;
    const int viewport_width = static_cast<int>(viewport_height*aspect_ratio);

    const double distance_between_plane = 1.0; //focal_length

    point3 origin = point3(0,0,0);
    vec3 horizontal = vec3(viewport_width,0,0);
    vec3 vertical = vec3(0,viewport_height,0);
    vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, distance_between_plane);

    //ppm file

    ppm_file sphere_test("debug_sphere_test",image_width,image_height);
    //render(there will be a function for it)
    for (int h = 0; h < image_height; ++h) {
        for(int w = 0; w < image_width; ++w){
            auto u = double(w) / (image_width-1);
            auto v = double(h) / (image_height-1);
            ray r(origin,lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color_sphere(r,world);
            sphere_test.writeRGBToPos(pixel_color.x(),pixel_color.y(),pixel_color.z(),h,w);
        }
    }
    sphere_test.saveFile("Testing hittable list aka world by creating spheres and coloring them with weird function taken from the book");
    return 0;
}

