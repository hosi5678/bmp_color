// #include <GL/glew.h>  // glew.hを先にincludeしておく。
// #include <GLFW/glfw3.h>
// #include <GL/glut.h>
#include <iostream>
#include <cstdlib>

#include "sub_dir/include/vec1d.hpp"
#include "sub_dir/include/vec2d.hpp"

#include "sub_dir/include/image.hpp"

int main(){

   std::string filename="../bmpfiles/cap2_01a.bmp";

   image img(filename);

   return 0;

}
