#ifndef C273C7B6_B7CB_4FEC_A209_515104EEC330
#define C273C7B6_B7CB_4FEC_A209_515104EEC330

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream> // fileの書き込みに使用する
#include <iomanip>  // fileの書き込みに使用する
#include <string>
#include <algorithm>

#include <stdexcept>

#include <sys/stat.h>
#include <sys/types.h>

class vec2d {

    public:
      int ylength;
      int xlength;
      int depth;
      std::stringstream file_name;
      
      std::vector<std::vector<uint8_t>> vec;

      // default constructor
      vec2d(){}

      // constructor with argument
      vec2d(int _ylength, int _xlength): ylength(_ylength),xlength(_xlength),vec(_ylength,std::vector<u_int8_t>(_xlength,0)) {}

      // constructor with vector
      vec2d(std::vector<std::vector<uint8_t>> obj):vec2d(obj.size(),obj[0].size()) {

         if(obj.empty()){
            throw std::runtime_error("obj is empty.");
         }

         for(size_t j=0; j<obj.size(); j++) {
            for (size_t i=0; i<obj[0].size(); i++) {
               this->vec[j][i]=obj[j][i];
            }
         }

         (*this).ylength=obj.size();
         (*this).xlength=obj[0].size();

      }

      // constructor with 1D vector.


};

#endif /* C273C7B6_B7CB_4FEC_A209_515104EEC330 */
