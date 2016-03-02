
#ifndef QUALITY_H
#define QUALITY_H

#include <string>
#include <list>
#include "Data.hpp"
#include "LogFileWriter.hpp"

using namespace std;


/**
  * class Quality
  * 
  */

class Quality
{
public:

  /**
   * Empty Constructor
   */
  Quality (LogFileWriter *log);

      
  /**
   * Empty Destructor
   */
  ~Quality ();


  /**
   * @return bool
   */
  virtual bool writeQualityHeader (string output_path, string file_prefix) = 0;


  /**
   * @return bool
   */
  virtual bool writeQualityOutput (list<string> &list_quality) = 0;


  /**
   * @return bool
   */
  virtual bool calculateQuality (list<Data*> &list_data, list<string> &list_quality) = 0;


private:
  LogFileWriter *_log;
protected:
  string _qualityFile_path;
  static const char QSEP = ';';
};

#endif // QUALITY_H
