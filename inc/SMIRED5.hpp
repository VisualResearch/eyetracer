
#ifndef SMIRED5_H
#define SMIRED5_H

#include <string>
#include "Plugin.hpp"
#include "Quality.hpp"

using namespace std;

const string SMIRED5_VERSION="SMIRED5_2015.02";

/**
 * class SMIRED5
 * 
 */

class SMIRED5 : public Quality, public Plugin
{
public:

  // Constructors/Destructors
  //  

  /**
   * Empty Constructor
   * @param log
   */
  SMIRED5 (LogFileWriter *log);

  /**
   * Empty Destructor
   */
  virtual ~SMIRED5 ();


  bool parseDataFile (string file_path, list<Data*> &list_data, streampos *line_num_stop = NULL);

  inline string getEyetrackerCode(){ return "StaticBinocular";         }
  inline string getPluginVersion() { return SMIRED5_VERSION;           }
  inline string getPluginCompany() { return "SMI";                     }
  inline string getPluginModel()   { return "RED5";                    }
  inline string getPluginRate()    { return "120Hz";                   }

  bool writeQualityHeader (string output_path, string file_prefix);
  bool writeQualityOutput (list<string> &list_quality);
  bool calculateQuality   (list<Data*> &list_data, list<string> &list_quality);


private:

  LogFileWriter *_log;
  bool           _pupils;
};

#endif // SMIRED5_H
