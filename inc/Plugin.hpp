
#ifndef PLUGIN_H
#define PLUGIN_H

#include "Subject.hpp"
#include "LogFileWriter.hpp"
#include "Data.hpp"
#include <string>
#include <vector>
#include <map>

using namespace std;


#define LINE_NUM_STOP_INI -1
#define MAX_IMAGE_RES_WIDTH 2560
#define MAX_IMAGE_RES_HEIGHT 1600


/**
  * class Plugin
  * 
  */

class Plugin
{
public:

  /**
   * Empty Constructor
   */
  Plugin (LogFileWriter *log);

      
  /**
   * Empty Destructor
   */
  ~Plugin ();


  /**
   * @return bool
   * @param  file_path
   */
  virtual bool parseDataFile (string file_path, list<Data*> &list_data, streampos *line_num_stop = NULL) = 0;
  virtual string getEyetrackerCode() = 0;
  virtual string getPluginVersion() = 0;
  virtual string getPluginCompany() = 0;
  virtual string getPluginModel() = 0;
  virtual string getPluginRate() = 0;

  /**
   * @return bool
   */
  bool writeDataOutput (string output_path, list<Data*> &list_data, map<string,string> &map_extra, vector<string> &file_error);


  /**
   * @return bool
   * @param  file_path
   */
  bool loadSubject (string file_path);

  bool checkBilderSize (string file_path);

  inline void                 setBilderPath     (string bilder_path)               { _bilder_path = bilder_path; }
  inline void                 setPrintPics      (bool printOnlyAvailablePictures)  { _printOnlyAvailablePictures = printOnlyAvailablePictures; }
  inline void                 setBilderInOutname(bool setBilderInOutname)          { _picture_name_in_outname = setBilderInOutname; }
  inline map<string, string>* getDataExtra      ()                                 { return &_map_extra; }
  inline void                 insertDataExtra   (const string &type, string &value){ _map_extra[type] = value; }

private:
  LogFileWriter *_log;

protected:
  Subject             _subject;
  list<string>        _input_data_files;
  string              _bilder_path;
  bool                _printOnlyAvailablePictures;
  bool                _picture_name_in_outname;
  map<string, string> _map_extra;
};

#endif // PLUGIN_H
