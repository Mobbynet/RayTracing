//
// Created by grzes on 30.03.2023.
//

#include "Color.h"

//stolen from the book I don't know if it will be needed for anything with my ppm file class

void write_color(std::ostream &out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}