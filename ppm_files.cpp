//
// Created by grzes on 29.03.2023.
//

#include "ppm_files.h"




bool ppm_file::createDebugPPMImg() {
    for(int h = 0; h < height; h++){
        std::cerr << "\rScanlines remaining: " << height - h << ' ' << std::flush;
        for(int w = 0; w < width; w++) {

            double r = double(w) / (width - 1); //filling with colors taken from book RayTracingInOneWeekend
            double g = double(h) / (height - 1);
            double b = 0.3;
            int ir = static_cast<int>(color_range * r);
            int ig = static_cast<int>(color_range * g);
            int ib = static_cast<int>(color_range * b);
            image[h][w].e[0] = ir;
            image[h][w].e[1] = ig;
            image[h][w].e[2] = ib;
        }
    }
    return true;
}

ppm_file::ppm_file() {
    width = 256;
    height = 256;
    image = new color*[height];
    for (int h = 0; h < height; h++) {
        image[h] = new color[width];
    }
    name = "debug_ppm_test_file.ppm";
    if(createDebugPPMImg()) {
        std::cerr << "\nDone generating PPM debug object.\n";
    }
    else //this code is now unreachable but it might change in future so I will leave it for now
        std::cerr << "\nError while generating PPM debug object!\n";
}

ppm_file::ppm_file(std::string name,int width,int height){
    this->width = width;
    this->height = height;
    this->name = name  + ".ppm";
    image = new color*[height];
    for (int h = 0; h < height; h++) {
        image[h] = new color[width];
    }
}

ppm_file::~ppm_file() {
    for(int h = 0; h < height; h++){
        delete[] image[h];
    }
    delete[] image;
}

bool ppm_file::saveFile(std::string comment) {
    file.open(name);
    file << "P3" << std::endl;
    file << "#" << comment << std::endl;
    file << width << " " << height << std::endl;
    file << color_range << std::endl;
    for(int h = 0; h < height; h++){
        for (int w = 0; w < width; w++) {
            file << image[h][w].e[0] << " " << image[h][w].e[2] << " "  << image[h][w].e[1] << " ";
        }
        file << std::endl;
    }
    file.close();
    std:: cerr << name <<" saved successfuly.\n";
    return true;
}


bool ppm_file::isInImage(int row,int col){
    return (row >= 0 && col >= 0 && row < height && col < width);
}

bool ppm_file::checkTheColor(double color) {
    return (color >= 0 && color <= 1 );
}

bool ppm_file::writeRGBToPos(double red,double green,double blue, int row, int col) { //Red green blue is a number bettwen 1 and 0
    if(!isInImage(row,col)){                                                           // it can be changed later but for now I'm doing it this way
        std::cerr << "\nPosition "<< row << " " << col << " is out of an image!\n";
        return false;
    }
    if(!checkTheColor(red)){
        std::cerr << "\nRed is out of range" << "on position " << row << " " << col << std::endl;
        return false;
    }

    if(!checkTheColor(green)){
        std::cerr << "\nGreen is out of range" << "on position " << row << " " << col << std::endl;
        return false;
    }

    if(!checkTheColor(blue)){
        std::cerr << "\nBlue is out of range" << "on position " << row << " " << col << std::endl;
        return false;
    }
    image[row][col].e[0] = static_cast<int>(color_range*red);
    image[row][col].e[1] = static_cast<int>(color_range*green);
    image[row][col].e[2] = static_cast<int>(color_range*blue);
    return true;
}

int ppm_file::getHeight() const{
    return height;
}

int ppm_file::getWidth() const{
    return width;
}