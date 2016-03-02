/**
 * @file   LogFileWriter.hpp
 * @author Esteban Gutierrez <esteban.gutierrez.mlot@uni-tuebingen.de>
 * @date   Fri Jan  9 11:55:19 2015
 * 
 * @brief  Logging system with configurable output
 * 
 * 
 */

#ifndef LOGFILEWRITER_H
#define LOGFILEWRITER_H

#include <string>
#include <fstream>

using namespace std;

/**
 * class LogFileWriter
 * 
 */
class LogFileWriter
{
public:

  /**
   * Constructor
   */
  LogFileWriter (){
    _filepath = "";
  }

  /**
   * Destructor
   */
  ~LogFileWriter (){
    if (_logfile.is_open()) _logfile.close();
  }


  inline void createlogfile(string path){
    _filepath = path;
    _logfile.open(_filepath, ios_base::out);
  }

  inline void copylogfile(string path){
    if( _filepath != "" && path != "" ){
      ifstream log_in;
      ofstream log_out;
      log_in.open(_filepath, ios::binary);
      log_out.open(path, ios::binary);
      if( log_in.is_open() && log_out.is_open() ){
        log_out << log_in.rdbuf();
      }
      if( log_in.is_open()  ) log_in.close();
      if( log_out.is_open() ) log_out.close();
    }
  }


  /**
   * Write General information in log
   * @param  text
   */
  inline void write (string text){
    _logfile << text << endl;
  }

  /**
   * Write Debug information in log
   * @param  text
   */
  inline void writeDebug (string text){
#ifdef DEBUG_MODE
    write("DEBUG: "+text);
#endif
  }

  /**
   * Write Debug information in log
   * @param  text
   */
  inline void writeWarn (string text){
    write("WARN: "+text);
  }

  /**
   * Write Debug information in log
   * @param  text
   */
  inline void writeError (string text){
    write("ERROR: "+text);
  }

private:

  string _filepath;
  ofstream _logfile;

};

#endif // LOGFILEWRITER_H
