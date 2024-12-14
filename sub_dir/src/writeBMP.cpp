#include "../include/image.hpp"

void image::writeBMP() {

  std::cout << "(in BMP write)" << std::endl;
  std::cout << "output file name:" << "out.bmp" << std::endl;
  std::cout << "padding:" << padding << std::endl;
  std::cout << "width:" << width << std::endl;
  std::cout << "height:" << height << std::endl;
  std::cout << "length of 1d vector of image:" << imagepixel.pixel.r.size()<< std::endl;
  std::cout << "length of 1d vector of palette:" << palette.palette.r.size() << std::endl;

  std::cout << "endian:" << isLittleEndian() << std::endl;

  std::cout << "biBitCount :" << bmpinfoheader.biBitCount << std::endl;
  std::cout << "biClrUsed :" << bmpinfoheader.biClrUsed << std::endl;
  std::cout << "biSizeImage :" << bmpinfoheader.biSizeImage << std::endl;

  std::streampos pos=outfile.tellp();
  std::cout << "pos=" << pos << std::endl;

    // ヘッダ情報を書き出し
    writeBytes(outfile, (bmpfileheader.bfType));
    writeBytes(outfile, (bmpfileheader.bfSize));
    writeBytes(outfile, (bmpfileheader.bfReserved1));
    writeBytes(outfile, (bmpfileheader.bfReserved2));
    writeBytes(outfile, (bmpfileheader.bfOffBits));

    writeBytes(outfile, (bmpinfoheader.biSize));
    writeBytes(outfile, (bmpinfoheader.biWidth));
    writeBytes(outfile, (bmpinfoheader.biHeight));
    writeBytes(outfile, (bmpinfoheader.biPlanes));
    writeBytes(outfile, (bmpinfoheader.biBitCount));
    writeBytes(outfile, (bmpinfoheader.biCompression));
    writeBytes(outfile, (bmpinfoheader.biSizeImage));
    writeBytes(outfile, (bmpinfoheader.biXPelsPerMeter));
    writeBytes(outfile, (bmpinfoheader.biYPelsPerMeter));
    writeBytes(outfile, (bmpinfoheader.biClrUsed));
    writeBytes(outfile, (bmpinfoheader.biClrImportant));

  pos=outfile.tellp();
  std::cout << "header pos=" << pos << std::endl;

  // パレットの書き出し
  for (std::size_t i=0; i<bmpinfoheader.biClrUsed; i++) {
    writeBytes(outfile,(palette.palette.b[i]));
    writeBytes(outfile,(palette.palette.g[i]));
    writeBytes(outfile,(palette.palette.r[i]));
    writeBytes(outfile,(palette.palette.d[i]));
  }

  pos=outfile.tellp();
  std::cout << "palette pos=" << pos << std::endl;

    // ピクセルデータの書き出し（上から下へ）
    for (int j = 0; j< height ; j++) {
      for (int i = 0; i < width; i++) {
        // カラーは3個のチャンネルを書き込む。
          writeBytes(outfile, (imagepixel.pixel.b[j * width + i]));
          writeBytes(outfile, (imagepixel.pixel.g[j * width + i]));
          writeBytes(outfile, (imagepixel.pixel.r[j * width + i]));

      }

      // paddingは0を埋めて飛ばす。
      for (int i = 0; i < padding; i++) {
          writeBytes(outfile, static_cast<uint8_t>(0));
      }
    }

  pos=outfile.tellp();
  std::cout << "image pos=" << pos << std::endl;

  // fileのクローズ
  outfile.close();
}
