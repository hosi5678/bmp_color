#ifndef AB004A64_177C_4DBB_8542_AC63E3C6F69B
#define AB004A64_177C_4DBB_8542_AC63E3C6F69B

#include <vector>

typedef struct _tagMainPixel {
	std::vector<uint8_t> b;
   std::vector<uint8_t> g;
	std::vector<uint8_t> r;

} PixelData;

typedef struct _tagPalette {
   std::vector<uint8_t> b;
   std::vector<uint8_t> g;
   std::vector<uint8_t> r;
   std::vector<uint8_t> d; // dummy

} PaletteData;

typedef struct _tagMainStructure {
   int width=0;
   int height=0;
   int padding=0;
   PixelData pixel;
} Image;

typedef struct _tagPaletteStructure {
   int length=0;
   PaletteData palette;
} Palette;

#endif /* AB004A64_177C_4DBB_8542_AC63E3C6F69B */
