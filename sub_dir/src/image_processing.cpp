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

// 画像の構造体を2次元配列に入れていく。
void image_processing::toMatrix(){

  // 2次元配列の構造体の初期化
  image_r.clear();
  image_g.clear();
  image_b.clear();

  // 領域を確保する
  image_r.resize(height, std::vector<uint8_t>(width));
  image_g.resize(height, std::vector<uint8_t>(width));
  image_b.resize(height, std::vector<uint8_t>(width));

  // 画像の構造体を2次元配列に入れていく。
  for (int j=0; j<height; j++) {
    for (int i=0; i< width; i++ ) {

      int index=j*width+i;

      image_r[j][i]=image.pixel.r[index];
      image_g[j][i]=image.pixel.g[index];
      image_b[j][i]=image.pixel.b[index];
    }
  }

}

// 2次元配列の処理(画像処理)を行う。
void image_processing::mainProcess() {

  std::cout << "main processs :" << std::endl;

  // 画像を書き換える
  for (int j=0; j<height; j++) {
    for (int i=0; i<width; i++) {
      image_r[j][i]=coefofData(image_r[j][i]);
      image_g[j][i]=coefofData(image_g[j][i]);
      image_b[j][i]=coefofData(image_b[j][i]);
    }
  }

}

// 処理の内容
uint8_t image_processing::coefofData(uint8_t data) {

  double param2=200;
  double param1=50;

  uint8_t outData=(uint8_t)((double(param2-param1))/255.0*(double)data)+param1;

  return outData;

}

// 2次元配列の値を構造体のメンバに入れてゆく
void image_processing::setImage() {

    // 構造体を一旦クリアする
    image.pixel.r.clear();
    image.pixel.g.clear();
    image.pixel.b.clear();

    // 領域を確保する
    image.pixel.r.resize(height * width);
    image.pixel.g.resize(height * width);
    image.pixel.b.resize(height * width);

  // 書き換えた2次元配列の値を構造体のメンバに入れてゆく
  for (int j=0; j<height; j++ ) {
    for (int i=0; i<width; i++) {
      int index = j * width + i;
      image.pixel.r[index] = image_r[j][i];
      image.pixel.g[index] = image_g[j][i];
      image.pixel.b[index] = image_b[j][i];    }
  }

}

// unsignedなので、0のチェックは不要で255より大きければ255を返却する。
// UINT8_MAXの値が255なので、この処理は不要
uint8_t image_processing::correctValue(uint8_t value){

  if (value>255) return 255;

  return value;

}
