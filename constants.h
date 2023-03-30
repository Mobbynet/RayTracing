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
//


const int color_range = 255;




//utility functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}




//common headers






#include "ray.h"
#include "vec3.h"




#endif //RAYTRACINGINONEWEEK_CONSTANTS_H
