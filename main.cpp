// #include <GL/glew.h>  // glew.hを先にincludeしておく。
// #include <GLFW/glfw3.h>
// #include <GL/glut.h>
#include <iostream>
#include <cstdlib>

#include "sub_dir/include/vec1d.hpp"
#include "sub_dir/include/vec2d.hpp"

#include "sub_dir/include/image.hpp"

int main(){

   vec1d a;

   a.vec.push_back(1);
   a.vec.push_back(2);
   a.vec.push_back(3);

   a.show();

   a.createFile("./","vec1d.csv");
   a.createFileHex("./","vec1d_hex.csv");
   // std::string filename="./bmpfiles/sample.bmp";

   // image img(filename);

   return 0;

}
