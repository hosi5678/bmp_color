#include "../include/image.hpp"

void image::readBMP() {

    std::cout << "(in read BMP)" << std::endl;

    std::streampos current_pos=infile.tellg();

    std::cout << "palette length: " << palette.length << std::endl;

    std::cout << "current position: " << current_pos << std::endl;

    int temp=0;

    for (int i=0; i<palette.length; i++) {

      temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
      palette.b.push_back(temp);

      temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
      palette.g.push_back(temp);

      temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
      palette.r.push_back(temp);

      temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
      palette.dummy.push_back(temp);

    }

    std::cout << "palette data were read." << std::endl;

    current_pos=infile.tellg();
    std::cout << "current position: " << current_pos << std::endl;

    temp=0;

    for (int j=0; j<height; j++) {
      for (int i=0; i<width; i++) {

        // 画像データはb,g,rの3画素を読み出す
        temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
        image1dRGB.b.push_back(temp);

        temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
        image1dRGB.g.push_back(temp);

        temp=readBytes<uint8_t>(infile,sizeof(uint8_t));
        image1dRGB.r.push_back(temp);

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
