#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream> // fileの書き込みに使用する
#include <iomanip>  // fileの書き込みに使用する
#include <string>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <cmath>

#include <cstdint>
#include <stdexcept>

#include "../include/pixels.hpp"
#include "../include/BITMAPHEADER.hpp"

#include "../include/image_processing.hpp"


// 2次元配列の処理(画像処理)を行う。
void image_processing::mainProcess() {

  std::cout << "main processs :" << std::endl;

  // 2次元画像(vec2d)を書き換える
  for (int j=0; j<height; j++) {
    for (int i=0; i<width; i++) {
      image2d_r.vec[j][i]=(image2d_r.vec[j][i]);
      image2d_g.vec[j][i]=(image2d_g.vec[j][i]);
      image2d_b.vec[j][i]=(image2d_b.vec[j][i]);
    }
  }

  std::cout << std::endl;

}

// 処理の内容
uint8_t image_processing::coefofData(uint8_t data) {

  double param2=235;
  double param1=16;

  // uint8_t outData=(uint8_t)((double(param2-param1))/255.0*(double)data)+param1;

  double top=(double)(data-param1)*255;
  double bottom=(double)(param2-param1);

  uint8_t outData=(uint8_t)(top/bottom);

  return outData;

}

