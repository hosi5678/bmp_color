#include "../include/image.hpp"

void image::writeBMPFileHeader(std::ofstream& ofs, const BITMAPFILEHEADER& bmpfileheader) {

    if (!ofs.is_open()) {
        std::cerr << "Failed to open file for writing bmp header: "  << std::endl;
        return;
    }

    // bmpheader構造体をバイナリ形式でfpに書き込む
    ofs.write(reinterpret_cast<const char*>(&bmpfileheader), sizeof(BITMAPFILEHEADER));

    if (!ofs.is_open()) {
        std::cerr << "Failed to write bmp header to file: " << std::endl;
    } else {
        std::cout << "Header written to file successfully: " << filename << std::endl;
    }
}
