#include "../include/image.hpp"

BITMAPFILEHEADER image::readBMPFileHeader(std::ifstream& ifs) {

    // 構造体のゼロ初期化
    BITMAPFILEHEADER bmpfileheader{};

    if (!ifs.is_open()) {
        std::cerr << "Failed to open file for bmp header reading: " << std::endl;
        return bmpfileheader;
    }

    // 構造体をバイナリ形式で読み込む
    ifs.read(reinterpret_cast<char*>(&bmpfileheader), sizeof(BITMAPFILEHEADER));

    if (!ifs.is_open()) {
        std::cerr << "Failed to read from file for reading bitmap file header: " << std::endl;
    } else {
        std::cout << "Header read from file successfully: " << std::endl;
    }

    return bmpfileheader;
}
