

#include "ppm_files.h"
#include "objects.h"
#include "debug_fun.h"



int main() {
    ppm_file debug;
    if(debug.saveFile())
        return 101;
    if(testRays())
        return 102;
    if(testSphere())
        return 103;



    return 0;
}


