#include "../include/BITMAPHEADER.hpp"
#include "../include/image.hpp"

void image::headerRead() {

  try{
    infile.read(reinterpret_cast<char*>(&bmpfileheader),sizeof(bmpfileheader));
    infile.read(reinterpret_cast<char*>(&bmpinfoheader),sizeof(bmpinfoheader));

  }catch(std::exception& e){
    std::cerr << e.what() << std::endl;
  }


}
