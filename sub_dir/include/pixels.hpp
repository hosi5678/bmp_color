#ifndef AB004A64_177C_4DBB_8542_AC63E3C6F69B
#define AB004A64_177C_4DBB_8542_AC63E3C6F69B

#include <vector>

typedef struct _tagImageRGBStructure {
   int width=0;
   int height=0;
   int padding=0;
   std::vector<uint8_t> b;
   std::vector<uint8_t> g;
	std::vector<uint8_t> r;
} Image;

typedef struct _tagPaletteStructure {
   int length=0;
   std::vector<uint8_t> b;
   std::vector<uint8_t> g;
   std::vector<uint8_t> r;
   std::vector<uint8_t> dummy; // dummy
} Palette;

#endif /* AB004A64_177C_4DBB_8542_AC63E3C6F69B */
