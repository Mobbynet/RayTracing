//
// Created by grzes on 29.03.2023.
//

#ifndef RAYTRACINGINONEWEEK_PPM_FILES_H
#define RAYTRACINGINONEWEEK_PPM_FILES_H

#include "constants.h"





class ppm_file {
public:
    ppm_file();
    ppm_file(std::string name,int width,int height);
    ~ppm_file();

    bool saveFile(std::string comment = "");
    bool writeRGBToPos(double red,double green,double blue,int row,int col);

    int getHeight() const;
    int getWidth() const;

private:
    color **image;
    std::string name;
    int height;
    int width;
    std::ofstream file;
    bool createDebugPPMImg();
    bool isInImage(int row,int col) const;
    bool checkTheColor(double color) const;

};


#endif //RAYTRACINGINONEWEEK_PPM_FILES_H
