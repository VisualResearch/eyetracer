#ifndef CONSOLE_MODE
  #include <QImage>
  #include <QFileInfo>
#endif

#include "common.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>


std::string etbutler::extractFileNameFromPath(std::string path){
  // Remove directory if present.
  // Do this before extension removal incase directory has a period character.
  std::string out_path;
  const size_t last_slash_idx = path.find_last_of( FILE_SLASH );
  if (std::string::npos != last_slash_idx){ path.erase(0, last_slash_idx + 1); }

  // Remove extension if present.
  const size_t period_idx = path.rfind('.');
  if (std::string::npos != period_idx){ path.erase(period_idx); }
  out_path = path;
  return out_path;
}

std::string etbutler::extractFileNameFromPath(std::string path, std::string &ext){
  // Remove directory if present.
  // Do this before extension removal incase directory has a period character.
  std::string out_path;
  const size_t last_slash_idx = path.find_last_of( FILE_SLASH );
  if (std::string::npos != last_slash_idx){ path.erase(0, last_slash_idx + 1); }

  // Return extension if present.
  std::vector<std::string> out;
  split(path, '.', out);
  if( out.size() > 1 ){
    ext = out[1];
    out_path = out[0];
  }else{
    ext = "";
    out_path = "";
  }
  return out_path;
}


std::string etbutler::extractFileFolderFromPath(std::string path){
  // Remove directory if present.
  // Do this before extension removal incase directory has a period character.
  const size_t last_slash_idx = path.find_last_of( FILE_SLASH );
  if (std::string::npos != last_slash_idx){ path.erase(last_slash_idx, path.size() - last_slash_idx); }

  return path;
}


void etbutler::trim(std::string &line){
  line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
}

std::string etbutler::trimming(const std::string& str, const std::string& whitespace){
  const auto strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos)
    return ""; // no content

  const auto strEnd = str.find_last_not_of(whitespace);
  const auto strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}


void etbutler::split(const std::string &s, char delim, std::vector<std::string> &elems){
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    if (item.length() > 0) {
      elems.push_back(item);  
    }
  }
}



double etbutler::calculateAvg(const std::list<int> &list){
  double avg = 0;
  std::list<int>::const_iterator it;
  for(it = list.begin(); it != list.end(); it++) avg += *it;
  avg /= list.size();
  return avg;
}


#ifdef CONSOLE_MODE

bool etbutler::getImageSize(const std::string file_path, int &width,int &height){
  FILE *f;
  f = fopen(file_path.c_str(),"rb");
  if( !f ) return false;
  fseek(f,0,SEEK_END); long len=ftell(f); fseek(f,0,SEEK_SET); 
  if (len<26) {fclose(f); return false;}

  // Strategy:
  // reading BMP dimensions requires the first 26 bytes of the file
  // reading GIF dimensions requires the first 10 bytes of the file
  // reading PNG dimensions requires the first 24 bytes of the file
  // reading JPEG dimensions requires scanning through jpeg chunks
  // In all formats, the file is at least 26 bytes big, so we'll read that always
  unsigned char buf[26]; fread(buf,1,26,f);

  // For JPEGs, we need to read the first 12 bytes of each chunk.
  // We'll read those 12 bytes at buf+2...buf+14, i.e. overwriting the existing buf.
  // if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F')
  if (buf[0]==0xFF && buf[1]==0xD8 ){
    long pos=2;
    while (buf[2]==0xFF){ 
      if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 
          || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB) break;
      pos += 2+(buf[4]<<8)+buf[5];
      if (pos+12>len) break;
      fseek(f,pos,SEEK_SET); fread(buf+2,1,12,f);    
    }
  }
  fclose(f);

  // BMP:
  if (buf[0]=='B' && buf[1]=='M')
    {
      width = (buf[21]<<24) + (buf[20]<<16) + (buf[19]<<8) + (buf[18]<<0);
      height = (buf[25]<<24) + (buf[24]<<16) + (buf[23]<<8) + (buf[22]<<0);
      return true;
    }

  // JPEG: (first two bytes of buf are first two bytes of the jpeg file; rest of buf is the DCT frame
  if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF)
    { height = (buf[7]<<8) + buf[8];
      width = (buf[9]<<8) + buf[10];
      return true;
    }

  // GIF: first three bytes say "GIF", next three give version number. Then dimensions
  if (buf[0]=='G' && buf[1]=='I' && buf[2]=='F')
    { width = buf[6] + (buf[7]<<8);
      height = buf[8] + (buf[9]<<8);
      return true;
    }

  // PNG: the first frame is by definition an IHDR frame, which gives dimensions
  if ( buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' && buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A && buf[6]==0x1A && buf[7]==0x0A
       && buf[12]=='I' && buf[13]=='H' && buf[14]=='D' && buf[15]=='R')
    { width = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);
      height = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);
      return true;
    }

  return false;
}
#else
bool etbutler::getImageSize(const std::string file_path, int &width, int &height){
  QFileInfo imageInfo(QString(file_path.c_str()));
  if(imageInfo.exists()){
    QImage image(imageInfo.canonicalFilePath());
    width  = image.width();
    height = image.height();
    return true;
  }else return false;
}
#endif


std::string etbutler::float2str(float num){
  std::stringstream sstr;
  std::string result;
  sstr << std::setprecision(6) << num;
  result = sstr.str();
  return result;
}

std::string etbutler::float2str(float num, uint floatpres){
  std::stringstream sstr;
  std::string result;
  if(num == 0){
    sstr << 0;
  }else{
    sstr << std::fixed << std::setprecision(floatpres) << num;
  }
  result = sstr.str();
  return result;
}

std::string etbutler::double2str(double num){
  std::stringstream sstr;
  std::string result;
  sstr << std::setprecision(6) << num;
  result = sstr.str();
  return result;
}

std::string etbutler::int2str(int num){
  std::stringstream sstr;
  sstr << num;
  return sstr.str();
}

std::string etbutler::uint2str(uint num){
  std::stringstream sstr;
  sstr << num;
  return sstr.str();
}

bool etbutler::equalArrayElements(uint *array, uint array_size){
  for(uint i=0; i<array_size-1; i++){
    if( array[i] != array[i+1] ) return false;
  }
  return true;
}

bool etbutler::compareCaseInsensitive(std::string strFirst, std::string strSecond){
  // Convert both strings to upper case by transfrom() before compare.
  std::transform(strFirst.begin(), strFirst.end(), strFirst.begin(), toupper);
  std::transform(strSecond.begin(), strSecond.end(), strSecond.begin(), toupper);
  if(strFirst == strSecond) return true; else return false;
}
