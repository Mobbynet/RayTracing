

#include "ppm_files.h"
#include "objects.h"
#include "debug_fun.h"

//10X is error for debug test problems



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


