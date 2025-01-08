#ifndef C273C7B6_B7CB_4FEC_A209_515104EEC330
#define C273C7B6_B7CB_4FEC_A209_515104EEC330

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream> // fileの書き込みに使用する
#include <iomanip>  // fileの書き込みに使用する
#include <algorithm>

#include <stdexcept>

#include <sys/stat.h>
#include <sys/types.h>

#include "vec1d.hpp"

class vec2d {

    public:
      size_t ylength;
      size_t xlength;
      std::stringstream file_name;

      // uint8_t型の2次元vector
      std::vector<std::vector<uint8_t>> vec;

      // default constructor
      vec2d():ylength(0),xlength(0),vec(){}

      // constructor with argument
      vec2d(int _ylength, int _xlength): ylength(_ylength),xlength(_xlength),vec(_ylength,std::vector<u_int8_t>(_xlength,0)) {}

      // copy constructor
      vec2d(const vec2d& obj): ylength(obj.ylength),xlength(obj.xlength),vec(obj.vec) {}

      // constructor with vector
      vec2d(std::vector<std::vector<uint8_t>> obj):vec2d(obj.size(),obj[0].size()) {

         if(obj.empty()){
            throw std::runtime_error("(in constructor with vector):obj is empty.");
         }

         for(size_t j=0; j<obj.size(); j++) {
            for (size_t i=0; i<obj[0].size(); i++) {
               this->vec[j][i]=obj[j][i];
            }
         }

         (*this).ylength=obj.size();
         (*this).xlength=obj[0].size();

      }

   // operator=(vector) vectorによる代入
   vec2d& operator=(const std::vector<std::vector<uint8_t>>& obj) {
      if(this->ylength!=obj.size() || this->xlength!=obj[0].size()) {
         throw std::runtime_error("(in operator=vector):size is different.");
      }

      this->vec=obj;
      this->ylength=obj.size();
      this->xlength=obj[0].size();

      return *this;
   }

   // operator=(vec2d) vec2dによる代入
   vec2d& operator=(const vec2d& obj) {
      if(this!=&obj) {
         this->vec=obj.vec;
         this->ylength=obj.ylength;
         this->xlength=obj.xlength;
      }
      return *this;
   }

   // vec1dのオブジェクトをoperator=(vector 1d)の形式でvec2dに変換
   vec2d& operator=(const vec1d& obj) {
      if(this->ylength*this->xlength!=obj.vec.size()) {
         throw std::runtime_error("(in operator=(vec1d) ):size is different.");
      }

      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            this->vec[j][i]=obj.vec[j*this->xlength+i];
         }
      }

      return *this;
   }

   // vec2dのオブジェクトをoperator=(vec2d)の形式でvec1dに変換
   vec1d to_vec1d(const vec2d& obj) const{
      vec1d ret(obj.ylength*obj.xlength);

      for(size_t j=0; j<obj.ylength; j++) {
         for(size_t i=0; i<obj.xlength; i++) {
            ret.vec[j*obj.xlength+i]=obj.vec[j][i];
         }
      }

      return ret;
   }

   // vec2dのオブジェクト同士の加算
   vec2d operator+(const vec2d& obj) {

      if(this->ylength!=obj.ylength || this->xlength!=obj.xlength) {
         throw std::runtime_error("(in operator+):size is different.");
      }

      vec2d ret(this->ylength,this->xlength);

      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            ret.vec[j][i]=this->vec[j][i]+obj.vec[j][i];
         }
      }

      return ret;
   }

   // vec2dのオブジェクト同士の減算
   vec2d operator-(const vec2d& obj) {

      if(this->ylength!=obj.ylength || this->xlength!=obj.xlength) {
         throw std::runtime_error("(in operator-):size is different.");
      }

      vec2d ret(this->ylength,this->xlength);

      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            ret.vec[j][i]=this->vec[j][i]-obj.vec[j][i];
         }
      }

      return ret;
   }

   // vec2dのオブジェクトとuint8_t型のオブジェクトの加算
   vec2d operator+(uint8_t d) {
      vec2d ret(this->ylength,this->xlength);

      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            ret.vec[j][i]=this->vec[j][i]+d;
         }
      }

      return ret;
   }

   // vec2dのオブジェクトとuint8_t型のオブジェクトの減算
   vec2d operator-(uint8_t d) {
      vec2d ret(this->ylength,this->xlength);

      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            ret.vec[j][i]=(d>=this->vec[j][i]) ? d-this->vec[j][i] : 0;
         }
      }

      return ret;
   }

   // vec2dのオブジェクトとuint8_t型のオブジェクトの乗算
   vec2d operator*(uint8_t d) {
      vec2d ret(this->ylength,this->xlength);

      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            ret.vec[j][i]=static_cast<uint8_t>(std::min<int>(this->vec[j][i]*d,255));
         }
      }

      return ret;
   }

   // vec2dのオブジェクトとuint8_t型のオブジェクトの除算
   vec2d operator/(uint8_t d) {
      vec2d ret(this->ylength,this->xlength);

      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            ret.vec[j][i]=d/this->vec[j][i];
         }
      }

      return ret;
   }

   // 全要素にdを加算
   void add(uint8_t d) {
      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            this->vec[j][i]+=d;
         }
      }
   }

   // 全要素にdを減算
   void sub(uint8_t d) {
      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            this->vec[j][i]-=d;
         }
      }
   }

   // 全要素にdを乗算
   void mul(uint8_t d) {
      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            this->vec[j][i]=static_cast<uint8_t>(std::min<int>(this->vec[j][i]*d,255));
         }
      }
   }

   // 全要素にdを除算
   void div(uint8_t d) {


      for(size_t j=0; j<this->ylength; j++) {
         for(size_t i=0; i<this->xlength; i++) {
            if(this->vec[j][i]==0) {
               throw std::runtime_error("(in div d/ function):division by zero.");
            }

            this->vec[j][i]=d/this->vec[j][i];
         }
      }
   }

// directoryの作成
void createDir(const std::string& dir) {

    struct stat info;

    if (stat(dir.c_str(), &info) != 0) { // ディレクトリが存在しない
         if (mkdir(dir.c_str(), 0755) != 0) {
            throw std::runtime_error("Failed to create directory: " + dir);
         }

    } else if (!(info.st_mode & S_IFDIR)) { // 存在するがディレクトリでない
      throw std::runtime_error(dir + " exists but is not a directory.");
   }
}

// vec2dの内容を10進で1列にファイルに書き込む
void createFile(const std::string& dir,const std::string& file_name) {

   createDir(dir);

   std::ofstream ofs(dir+"/"+file_name);

   if(!ofs) {
      throw std::runtime_error("(in createFile):can not open file.");
   }

   for (size_t j=0; j<this->ylength; j++) {
      for(size_t i=0; i<this->xlength; i++) {
         ofs << "[" << i << "]: " << static_cast<int>(this->vec[j][i]) << std::endl;
      }
   }

   // ファイルを閉じる
   ofs.close();

}

// vec2dの内容を16進で1列にファイルに書き込む
void createFileHex(const std::string& dir,const std::string& file_name) {

   createDir(dir);

   std::ofstream ofs(dir+"/"+file_name);

   if(!ofs) {
      throw std::runtime_error("(in createFileHex):can not open file.");
   }

   for (size_t j=0; j<this->ylength; j++) {
      for(size_t i=0; i<this->xlength; i++) {
         ofs << "[" << i << "]: " << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(this->vec[j][i]) << std::endl;
      }
   }

   // ファイルを閉じる
   ofs.close();
}

// vec2dの内容を表示する。
void show() {
   for (size_t j=0; j<this->ylength; j++) {
      for(size_t i=0; i<this->xlength; i++) {
         std::cout << "[" << i << "]: " << static_cast<int>(this->vec[j][i]) << std::endl;
      }
   }
}

// destructor
~vec2d() = default;


};

#endif /* C273C7B6_B7CB_4FEC_A209_515104EEC330 */
