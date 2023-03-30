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



// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


//utility functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

//common headers

#include "ray.h"
#include "vec3.h"




#endif //RAYTRACINGINONEWEEK_CONSTANTS_H
