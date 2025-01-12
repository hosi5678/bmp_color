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
    structImage structimage;

    // 読み書きでアクセスできるように画像データをメンバとして持つ
    // std::vector<std::vector<uint8_t>> image_r,image_g,image_b;

    vec2d image2d_r;
    vec2d image2d_g;
    vec2d image2d_b;

    // default constructor
    image_processing(){}

    // constructor with argument.
    image_processing(structImage& _structimage):
      image2d_r(),
      image2d_g(),
      image2d_b()
    {

      // コンストラクタでwidth,heigthを設定する。
      height=_structimage.height;
      width= _structimage.width;

      // 構造体メンバに値をセットする
      structimage.height=_structimage.height;
      structimage.width= _structimage.width;

      // 領域の確保
      image2d_r=vec2d(height,width);
      image2d_g=vec2d(height,width);
      image2d_b=vec2d(height,width);

      //  1次元配列を2次元配列にコピーする
      image2d_r=_structimage.r;
      image2d_g=_structimage.g;
      image2d_b=_structimage.b;

      // 画像処理
      mainProcess();

      // 2次元配列をImageRGB構造体に設定する。
      setImage();

    }

    virtual void mainProcess();
    
    virtual uint8_t coefofData(uint8_t value);

    // 構造体のメンバを返却する
    virtual structImage returnImage(){
      return structimage;
    }

    // 2次元配列を構造体に格納する。
    virtual void setImage(){
      for (int j=0; j<height; j++ ) {
        for (int i=0; i<width; i++) {
          // int index = j * width + i;
          structimage.r.push_back(image2d_r.vec[j][i]);
          structimage.g.push_back(image2d_g.vec[j][i]);
          structimage.b.push_back(image2d_b.vec[j][i]);
        }
      }
    }


};

#endif /* A2AA8694_7155_4D07_9D37_A44D43814E38 */
