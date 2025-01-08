#ifndef B9B8D291_40EB_4F6C_BA53_03E3CEF4EED3
#define B9B8D291_40EB_4F6C_BA53_03E3CEF4EED3

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

class vec1d {

  public:
    int length;
    std::vector<uint8_t> vec;

    // default constructor
    vec1d():length(0),vec(){}

    // constructor with argument
    vec1d(int _length): length(_length),vec(_length,0) {}

    // copy constructor
      vec1d(const vec1d& obj): length(obj.length),vec(obj.vec) {}

      // destructor
      ~vec1d() = default;

    // constructor with vector
    vec1d(std::vector<uint8_t> obj):vec1d(obj.size()) {

       if(obj.empty()){
          throw std::runtime_error("obj is empty.");
       }

       for(size_t i=0; i<obj.size(); i++) {
          this->vec[i]=obj[i];
       }

       (*this).length=obj.size();

    }

    // operator=() vectorによる代入
    vec1d& operator=(const std::vector<uint8_t>& obj) {

       if(this->vec.size()!=obj.size()) {
          throw std::runtime_error("size is different.");
       }

       this->vec=obj;
       this->length=obj.size();
       return *this;
    }

vec1d& operator=(const vec1d& obj) {
    if (this != &obj) {
        this->length = obj.length;
        this->vec = obj.vec;
    }
    return *this;
}

    // 全要素にdを乗算
    void mul(uint8_t d) {
       for(size_t i=0; i<this->vec.size(); i++) {
         this->vec[i]*=d;
      }

   }

   // 全要素にdを除算
   void div(uint8_t d) {
      if (d==0) {
         throw std::runtime_error("(in div function):division by zero.");
      }

      for(size_t i=0; i<this->vec.size(); i++) {
         this->vec[i]/=d;
      }
   }

    // 全要素でdを除算(friend function)
      friend vec1d operator/(uint8_t d,const vec1d& obj) {
         vec1d ret(obj.length);

         for(size_t i=0; i<obj.vec.size(); i++) {
            if(obj.vec[i]==0) {
               throw std::runtime_error("(in operator d/): division by zero.");
            }
            ret.vec[i]=d/obj.vec[i];
         }

         return ret;
      }

    // 全要素にdを加算
   void add(uint8_t d) {
      for(size_t i=0; i<this->vec.size(); i++) {
         this->vec[i]+=d;
      }
   }

    // 全要素にdを減算(friend function)
      friend vec1d operator-(uint8_t d,const vec1d& obj) {
         vec1d ret(obj.length);
         for(size_t i=0; i<obj.vec.size(); i++) {
            ret.vec[i] = (d >= obj.vec[i]) ? d - obj.vec[i] : 0;
         }

         return ret;
      }

    // vector同士の乗算(friend function)
      friend vec1d operator*(const vec1d& obj1,const vec1d& obj2) {
         if(obj1.length!=obj2.length) {
            throw std::runtime_error("(in operator*): size is different.");
         }

         vec1d ret(obj1.length);

         for(size_t i=0; i<obj1.vec.size(); i++) {
            ret.vec[i] = static_cast<uint8_t>(std::min<int>(obj1.vec[i] * obj2.vec[i], 255));
         }

      return ret;

   }
    // vector同士の減算
    vec1d operator-(const vec1d& obj) {
       if(this->length!=obj.length) {
          throw std::runtime_error("(in operator-):size is different.");
       }

       vec1d ret(this->length);

       for(size_t i=0; i<this->vec.size(); i++) {
          ret.vec[i]=this->vec[i]-obj.vec[i];
       }
       return ret;

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

// vectorの内容を10進でファイルに書き込む
void createFile(const std::string& dir,const std::string& file_name) {

   createDir(dir);

   std::ofstream ofs(dir+"/"+file_name);

   if(!ofs) {
      throw std::runtime_error("(in createFile):can not open file.");
   }

   for(size_t i=0; i<this->vec.size(); i++) {
      ofs << "[" << i << "]: " << static_cast<int>(this->vec[i]) << std::endl;
   }

   ofs.close();
}

// vectorの内容を16進でファイルに書き込む
void createFileHex(const std::string& dir,const std::string& file_name) {

   createDir(dir);

   std::ofstream ofs(dir+"/"+file_name);

   if(!ofs) {
      throw std::runtime_error("(in createFileHex):can not open file.");
   }

   // 16進で出力,2バイトで表示、0埋め、大文字、改行
   for(size_t i=0; i<this->vec.size(); i++) {
      ofs << "[" << i << "]: " << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(this->vec[i]) << std::endl;
   }

   ofs.close();
}

// vectorの内容を表示する
void show() {
   for(size_t i=0; i<this->vec.size(); i++) {
      std::cout <<"[" << i << "]: " << static_cast<int>(this->vec[i]) << std::endl;
   }

}

// vectorを返却する
std::vector<uint8_t> getvector() const {
   return this->vec;
}

};// closing brace for class vec1d

#endif /* B9B8D291_40EB_4F6C_BA53_03E3CEF4EED3 */
