
#ifndef SMIHED_H
#define SMIHED_H

#include "Plugin.hpp"
#include "Quality.hpp"
#include <string>

using namespace std;

const string SMIHED_VERSION="SMIHED_2015.03";

/**
 * class SMIHED
 * 
 */

class SMIHED : public Quality, public Plugin
{
public:

  // Constructors/Destructors
  //  

  /**
   * Empty Constructor
   * @param log
   */
  SMIHED (LogFileWriter *log);

  /**
   * Empty Destructor
   */
  virtual ~SMIHED ();


  bool parseDataFile (string file_path, list<Data*> &list_data, streampos *line_num_stop = NULL);

  inline string               getEyetrackerCode(){ return "DynamicMonocular";        }
  inline string               getPluginVersion() { return SMIHED_VERSION;            }
  inline string               getPluginCompany() { return "SMI";                     }
  inline string               getPluginModel()   { return "HED";                     }
  inline string               getPluginRate()    { return "";                        }

  bool writeQualityHeader (string output_path, string file_prefix);
  bool writeQualityOutput (list<string> &list_quality);
  bool calculateQuality   (list<Data*> &list_data, list<string> &list_quality);


  inline void setUseOffset(bool useoffset) { _use_offset = useoffset; }

private:

  LogFileWriter      *_log;
  bool                _pupils;
  bool                _use_offset;
};

#endif // SMIHED_H
