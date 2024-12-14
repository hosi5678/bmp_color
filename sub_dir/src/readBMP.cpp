#include "../include/image.hpp"

void image::readBMP() {

    std::cout << "(in read BMP)" << std::endl;

    std::streampos current_pos=infile.tellg();

    std::cout << "current position: " << current_pos << std::endl;

    std::cout << "palette length: " << palette.length << std::endl;

    int temp=0;

    for (int i=0; i<palette.length; i++) {
      temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
      palette.palette.b.push_back(temp);

      temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
      palette.palette.g.push_back(temp);

      temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
      palette.palette.r.push_back(temp);

      temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
      palette.palette.d.push_back(temp);

    }

    std::cout << "palette data were read." << std::endl;

    current_pos=infile.tellg();
    std::cout << "current position: " << current_pos << std::endl;

    temp=0;

    for (int j=0; j<height; j++) {
      for (int i=0; i<width; i++) {

        // 画像データはb,g,rの3画素を読み出す
        temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
        imagepixel.pixel.b.push_back(temp);

        temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
        imagepixel.pixel.g.push_back(temp);

        temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
        imagepixel.pixel.r.push_back(temp);

      }

      // paddingを読み飛ばす
      for (int i=0; i<padding; i++){
        temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
      }

    }

    std::cout << "image data were read." << std::endl;

    current_pos=infile.tellg();
    std::cout << "current position: " << current_pos << std::endl;

    // ファイルのクローズ
    infile.close();

}

/*
valgrind --leak-check=full --track-origins=yes --log-file=valgrind.log ./build/main
*/
