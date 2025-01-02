#pragma once

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
#include "./image_processing.hpp"

class image:public virtual image_processing {

  public:
    std::string filename; // 扱うファイル名
    std::ifstream infile; // 入力ファイル
    std::ofstream outfile; // 出力ファイル

    Palette palette; // パレットデータ
    Image   imagepixel; // 画像データ
    image_processing img_processing; // 画像処理クラスのメンバ

    BITMAPFILEHEADER bmpfileheader;
    BITMAPINFOHEADER bmpinfoheader;

    int height; // 画像の高さ
    int width;  // 画像の幅
    int padding; // BMPは画像の幅を4Bytesの倍数にするための調整値

      // default constructor
    image(std::string _filename):filename(_filename){

      std::cout << "default construcor called." << std::endl;
      std::cout << _filename << std::endl;

      infile.open(_filename,std::ios::binary);

      // bmpのheaderを読み込む。
      headerRead();

      // 各種の設定
      initialise();

      // bmpの読み込みとファイルのクローズ
      readBMP();

      // bmpの画像処理のコンストラクタ呼び出し(引数:構造体)
      image_processing img(imagepixel);

      // 処理された構造体を受け取る
      imagepixel=img.returnImage();

      // 出力ファイルをオープン
      outfile.open("./out.bmp");

      // bmpの書き込みとファイルのクローズ
      writeBMP();
    }

    // 初期的な処理(headerを読み込む)
    void initialise();

    // bmpのヘッダーを読み込む
    void headerRead();


    template<typename T>
    void writeBytes(std::ofstream& fp, const T& data);

    template<typename T>
    T readBytes(std::ifstream& fp,std::size_t size);

    bool isLittleEndian() {
      uint32_t value = 0x01'02'03'04;
      return reinterpret_cast<const uint8_t*>(&value)[0] == 0x04;
    }


    // リトルエンディアンへの変換
    template<typename T>
      T toLittleEndian(T value) {
          if (!isLittleEndian()) { // ビッグエンディアンなら変換
              char* data = reinterpret_cast<char*>(&value);
              std::reverse(data, data + sizeof(T));
          }
          return value;
      }

    template<typename T>
    T swapEndian(T val) {
    return (val >> sizeof(T)) | (val << sizeof(T));
    }

    template<typename T>
    T toBigEndian(T value) {
        if (isLittleEndian()) {
            uint8_t* ptr = reinterpret_cast<uint8_t*>(&value);
            std::reverse(ptr, ptr + sizeof(T));
        }
        return value;
    }

    // paddingを求める(画像の横ピクセル数を4の倍数に切り上げる)
    int getPadding(int width);

    // bmp fileのpaletteとimageの読み込み
    void readBMP();

    // bmp fileの書き込み
    void writeBMP();

}; // class image


template <typename T>
T image::readBytes(std::ifstream& fp,std::size_t size){

  if(!fp.is_open()){
    std::cerr << "ファイルが開いていません" << std::endl;
  }

  T data=0;

  if(size!=sizeof(T)) {
    std::cerr << "サイズが一致しません。" << std::endl;
  }

  try{
    fp.read(reinterpret_cast<char*>(&data),sizeof(T));

    if (!fp) {
      throw std::runtime_error("ファイルからデータを読み込むのに失敗しました");
    }

  }catch(const std::exception& e){
    std::cerr<< "error." << e.what() << std::endl;
    throw; // 再スロー
  }

  std::streampos file_position=fp.tellg();

  if (file_position != -1) {
      // std::cout << "--- current fp(" << fp.tellg() << ")--- : " << std::endl;
  }else {
      std::cerr << "ファイル位置の取得に失敗しました。" << std::endl;
  }

    // std::cout << "binary data: "  << static_cast<uint64_t>(data) << std::endl;

    return toLittleEndian(data);

}

// ファイルの位置から値を書き込む
template<typename T>
void image::writeBytes(std::ofstream& fp, const T& data){

  if(!fp.is_open()){
    std::cerr << "ファイルが開いていません" << std::endl ;
  }

  try{

    T littleEndianData=toLittleEndian(data);

    fp.write(reinterpret_cast<const char*>(&littleEndianData),sizeof(T));

    if (!fp) {
      throw std::runtime_error("ファイルにデータを書き込むのに失敗しました");
    }

  }catch(const std::exception& e){

    std::cerr<< "error." << e.what() << std::endl;
    throw; // 再度スロー
  }

  // std::cout << "書き込んだデータ: " << static_cast<uint64_t>(data) << std::endl;

  std::streampos position = fp.tellp();
  
  if (position != -1) {
      // std::cout << "現在のファイル位置: " << position << std::endl;
  } else {
      std::cerr << "ファイル位置の取得に失敗しました。" << std::endl;
  }

}
