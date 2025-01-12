#include "../include/image.hpp"

void image::writeImageRGB(const std::string& filename, const structImage& image) {

    std::ofstream ofs("./bmp/"+filename);

    if (!ofs.is_open()) {
        std::cerr << "Failed to open file for writing image: " << filename << std::endl;
        return;
    }

    ofs << "[i]: red, green, blue" << std::endl;

    for (int j = 0; j <image.height ; j++) {
        for (int i = 0; i < image.width; i++) {
            ofs << "[" << j*image.width+i << "]: "
                << static_cast<int>(image.r[j*image.height+i]) << ","
                << static_cast<int>(image.g[j*image.height+i]) << ","
                << static_cast<int>(image.b[j*image.height+i]) << std::endl;
        }

        ofs << std::endl;
    }

    ofs.close();

}
