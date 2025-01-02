#include "../include/image.hpp"

// BMPファイルのパディングの計算
int image::getPadding(int width) {

   padding = (4 - (width * 3) % 4) % 4;

   return padding;
}

/*
バイトを調べる
バイナリエディタ（odやxxdやhexdumpなど）
*/
