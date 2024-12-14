#ifndef A2AA8694_7155_4D07_9D37_A44D43814E38
#define A2AA8694_7155_4D07_9D37_A44D43814E38

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

#include <cstdint>
#include <stdexcept>

#include "./pixels.hpp"
#include "./BITMAPHEADER.hpp"

class image_processing {

  public:
    int height;
    int width; // r,g,bを含むwidth

    // Image構造体をメンバとして持たせ、コンストラクタ読み出しで設定する。
    // 変更も構造体にsetする。
    Image image;

    // 読み書きでアクセスできるように画像データをメンバとして持つ
    std::vector<std::vector<uint8_t>> image_r,image_g,image_b;

    // default constructor
    image_processing(){}

    // constructor with argument.
    image_processing(Image& imageData){

      // コンストラクタでwidth,heigthを設定する。
      height=imageData.height;
      width=imageData.width;

      // 構造体メンバに値をセットする
      image.height=imageData.height;
      image.width=imageData.width;

      // 2次元配列の初期化
      image.pixel.r.clear();
      image.pixel.g.clear();
      image.pixel.b.clear();

      // 領域の確保
      image.pixel.r.resize(height*width);
      image.pixel.g.resize(height*width);
      image.pixel.b.resize(height*width);

      //  画像データをコピーする
      for (int j=0; j<height; j++){
        for (int i=0; i<width; i++) {
          int index=j*width+i;
            image.pixel.r[index]=imageData.pixel.r[index];
            image.pixel.g[index]=imageData.pixel.g[index];
            image.pixel.b[index]=imageData.pixel.b[index];

        }
      }

      // 構造体の画像メンバを2次元配列に置き換える.
      toMatrix();

      // 画像処理
      mainProcess();

      // 2次元配列を構造体に設定する。
      setImage();

    }

    virtual void toMatrix();
    virtual void mainProcess();
    virtual void setImage();
    virtual uint8_t coefofData(uint8_t value);
    virtual uint8_t correctValue(uint8_t value);

    // 構造体のメンバを返却する
    virtual Image returnImage(){
      return image;
    }

};

#endif /* A2AA8694_7155_4D07_9D37_A44D43814E38 */
