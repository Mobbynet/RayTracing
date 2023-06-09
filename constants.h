//
// Created by grzes on 30.03.2023.
//

#ifndef RAYTRACINGINONEWEEK_CONSTANTS_H
#define RAYTRACINGINONEWEEK_CONSTANTS_H

//common libraries

#include <vector>
#include <limits>
#include <memory>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Antialiasing options
const bool antialiasing = true;
const auto samples_per_pixel = 100;
//Diffuse material options
const int max_depth = 50;


const int color_range = 255;
//img
const auto aspect_ratio = 16.0/9.0;
const int image_width = 1920;
const int image_height = static_cast<int>(image_width / aspect_ratio);



//utility functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
inline double random_double(double min = 0.0, double max = 1.0) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}




//common headers


#include "ray.h"
#include "vec3.h"




#endif //RAYTRACINGINONEWEEK_CONSTANTS_H
