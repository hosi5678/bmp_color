#include "../include/image.hpp"

void image::writeImageRGB(const std::string& filename, const Image& image) {

    std::ofstream ofs("./bmp/"+filename);

    if (!ofs.is_open()) {
        std::cerr << "Failed to open file for writing image: " << filename << std::endl;
        return;
    }

    ofs << "red, green, blue" << std::endl;

    for (int j = 0; j <image.height ; j++) {

        for (int i = 0; i < image.width; i++) {
            ofs << "[" << j*image.height+i << "]: " 
                << static_cast<int>(image.pixel.r[j*image.height+i]) << ","
                << static_cast<int>(image.pixel.g[j*image.height+i]) << ","
                << static_cast<int>(image.pixel.b[j*image.height+i]) << std::endl;
        }

        ofs << std::endl;
    }

    ofs.close();

}
