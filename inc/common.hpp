#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <list>

const std::string EYETRACEBUTLER_VERSION="2.04";

//#define FILE_SLASH "//"
#ifdef __linux__
//linux operative system
#define FILE_SLASH "//"
#elif __APPLE__
  //macintosh operative system
#define FILE_SLASH "//"
#else
  //Windows operative system
#define FILE_SLASH "/\\"
#define uint unsigned int
#endif


#define PI 3.14159265 

namespace etbutler
{
  std::string   extractFileNameFromPath(std::string path);
  std::string   extractFileNameFromPath(std::string path, std::string &ext);
  std::string   extractFileFolderFromPath(std::string path);
  void          trim(std::string &line);
  std::string   trimming(const std::string& str, const std::string& whitespace = " \t");
  void          split(const std::string &s, char delim, std::vector<std::string> &elems);
  double        calculateAvg(const std::list<int> &list);
  std::string   float2str(float number);
  std::string   float2str(float num, uint floatpres);
  std::string   double2str(double num);
  std::string   int2str(int num);
  std::string   uint2str(uint num);
  bool          equalArrayElements(uint *array, uint array_size);
  inline double degtorad (double d){ return d * PI / 180; }
  inline double radtodeg (double r){ return r * 180/ PI; }
  bool          getImageSize(const std::string file_path, int &width, int &height);
  bool          compareCaseInsensitive(std::string strFirst, std::string strSecond);
}

#endif // COMMON_H
