#include <iostream>
#include <fstream>

#include "ppm_files.h"
#include "vec3.h"
#include "Color.h"
#include "ray.h"




int main() {
    ppm_file debug;
    debug.saveFile();
    testRays();
    testSphere();

}


