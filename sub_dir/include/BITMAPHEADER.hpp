#ifndef EAECD5D8_7AFF_4FEF_ADEE_934F0495D5B5
#define EAECD5D8_7AFF_4FEF_ADEE_934F0495D5B5

#include <bitset>

#define FILE_TYPE 0x4D42    /**< "BM"をリトルエンディアンで解釈した値 */
#define FILE_HEADER_SIZE 14 /**< BMPファイルヘッダサイズ */
#define INFO_HEADER_SIZE 40 /**< Windowsヘッダサイズ */
#define BMP_HEADER_SIZE 54 /* 標準のヘッダサイズ */
#define DEFAULT_HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE) /**< 標準のヘッダサイズ */

// 構造体のアライメントを1Byte区切りで行う。
#pragma pack(push, 1)

typedef struct _tagBITMAPFILEHEADER {

  uint16_t bfType;      /**< ファイルタイプ、必ず"BM" */
  uint32_t bfSize;      /**< ファイルサイズ */
  uint16_t bfReserved1; /**< リザーブ */
  uint16_t bfReserved2; /**< リサーブ */
  uint32_t bfOffBits;   /**< 先頭から画像情報までのオフセット */

} BITMAPFILEHEADER;

typedef struct _tagBITMAPINFOHEADER {

  uint32_t biSize;         /**< この構造体のサイズ */
  int32_t biWidth;         /**< 画像の幅 */
  int32_t biHeight;        /**< 画像の高さ */
  uint16_t biPlanes;       /**< 画像の枚数、通常1 */
  uint16_t biBitCount;     /**< 画素1つ(R or G or B)のビット数 */
  uint32_t biCompression;  /**< 圧縮形式,0なら無圧縮 */
  uint32_t biSizeImage;    /**< 画像領域のサイズ */
  int32_t biXPelsPerMeter; /**< 画像の横方向解像度情報 */
  int32_t biYPelsPerMeter; /**< 画像の縦方向解像度情報*/
  uint32_t biClrUsed;      /**< カラーパレットのうち実際に使っている色の個数 */
  uint32_t biClrImportant; /**< カラーパレットのうち重要な色の数 */

} BITMAPINFOHEADER ;

// alignmentの設定を解除
#pragma pack(pop)

#endif /* EAECD5D8_7AFF_4FEF_ADEE_934F0495D5B5 */

/*
(in readBMP:) depth:8
(in readBMP:) colors:256
(in readBMP:) mx:640
(in readBMP:) mxb:640
(in readBMP:) pad:0

*/
