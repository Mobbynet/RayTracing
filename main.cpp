#include <iostream>
#include <fstream>

#include "ppm_files.h"
#include "vec3.h"
#include "Color.h"
#include "ray.h"




int main() {
    ppm_file debug;
    if(debug.saveFile())
        return 1;
    if(testRays())
        return 2;
    if(testSphere())
        return 3;


    return 0;
}


