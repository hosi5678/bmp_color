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

#include "./vec1d.hpp"
#include "./vec2d.hpp"

class image_processing:public virtual vec1d,public virtual vec2d {

  public:
    int height;
    int width; // r,g,bを含むwidth

    // Image構造体をメンバとして持たせ、コンストラクタ読み出しで設定する。
    // 変更も構造体にsetする。
    Image image;

    // 読み書きでアクセスできるように画像データをメンバとして持つ
    // std::vector<std::vector<uint8_t>> image_r,image_g,image_b;

    vec2d image_r;
    vec2d image_g;
    vec2d image_b;

    // default constructor
    image_processing(){}

    // constructor with argument.
    image_processing(Image& imageData):image_r(),image_g(),image_b(){ 

      // コンストラクタでwidth,heigthを設定する。
      height=imageData.height;
      width=imageData.width;

      // 構造体メンバに値をセットする
      image.height=imageData.height;
      image.width=imageData.width;

      // 領域の確保
      image_r=vec2d(height,width);
      image_g=vec2d(height,width);
      image_b=vec2d(height,width);

      //  1次元配列を2次元配列にコピーする
      image_r=imageData.r;
      image_g=imageData.g;
      image_b=imageData.b;

      // 画像処理
      mainProcess();

      // 2次元配列をImageRGB構造体に設定する。
      setImage();

    }

    virtual void mainProcess();
    virtual void setImage();
    virtual uint8_t coefofData(uint8_t value);

    // 構造体のメンバを返却する
    virtual Image returnImage(){
      return image;
    }

};

#endif /* A2AA8694_7155_4D07_9D37_A44D43814E38 */
