#include "../include/image.hpp"

void image::initialise(){

  if(!infile.is_open()){
    std::cerr << "ファイルが開いていません。" << filename << std::endl;
  }

  std::cout << "(in initialize:)" << std::endl;

  std::cout << "file readed: " << filename << std::endl;
  std::cout << "bfType:" << std::hex << bmpfileheader.bfType <<std::dec << std::endl;

  if(bmpfileheader.bfType!=FILE_TYPE){
    std::cout << "BMP fileではありません。" << std::endl;
  }else{
    std::cout << "BMP fileです。" << std::endl;
  }

  if(isLittleEndian()){
    std::cout << "リトルエンディアンです。" << std::endl;
  }else{
    std::cout << "ビッグエンディアンです。" << std::endl;
  }

  width =bmpfileheader.biWidth;
  height=bmpfileheader.biHeight;

  std::cout << "width: " << width << std::endl;
  std::cout << "height:" << height << std::endl;

  std::cout << "width x height: " << width*height << std::endl;
  std::cout << "3xwidthxheight:" << 3*width*height << std::endl;
  std::cout << "biSizeImage: " << bmpfileheader.biSizeImage << std::endl;

  std::cout << "padding: " << getPadding(width) << std::endl;
  std::cout << "color depth: " << bmpfileheader.biBitCount << std::endl;

  std::cout << "palette length(biClrUsed): " << bmpfileheader.biClrUsed << std::endl;

  std::streampos _pos = infile.tellg();

  if (_pos!=DEFAULT_HEADER_SIZE){
    std::cerr << "デフォルトサイズを読んでいません。" << std::endl;
  }

  std::cout << "original position: " << _pos << std::endl;

  // std::cout << "size of uint8_t: " << sizeof(uint8_t) << std::endl;
  // std::cout << "size of uint16_t: " << sizeof(uint16_t) << std::endl;
  // std::cout << "size of uint32_t: " << sizeof(uint32_t) << std::endl;
  // std::cout << "uint8 max: " << UINT8_MAX << std::endl;

  std::cout << "file size: " << bmpfileheader.bfSize << std::endl;

  std::cout << "header size+widthxheightx3: " << DEFAULT_HEADER_SIZE+bmpfileheader.biClrUsed*4+(width+(4-padding))*3*(height) << std::endl;

  palette.length=bmpfileheader.biClrUsed;

  imagepixel.width=bmpfileheader.biWidth;
  imagepixel.height=bmpfileheader.biHeight;
  imagepixel.padding=getPadding(bmpfileheader.biWidth);
  padding=imagepixel.padding;

      // palette dataの配列の確保

    palette.palette.b.clear();
    palette.palette.g.clear();
    palette.palette.r.clear();
    // palette.palette_data.dummy.clear();

    palette.palette.b.resize(0);
    palette.palette.g.resize(0);
    palette.palette.r.resize(0);
    palette.palette.d.resize(0);

    imagepixel.pixel.b.clear();
    imagepixel.pixel.g.clear();
    imagepixel.pixel.r.clear();

    imagepixel.pixel.b.resize(0);
    imagepixel.pixel.g.resize(0);
    imagepixel.pixel.r.resize(0);

}
