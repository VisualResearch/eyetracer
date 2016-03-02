
#ifndef IDMT_H
#define IDMT_H

#include "Plugin.hpp"
#include "Quality.hpp"
#include <string>

using namespace std;


const string IDMT_VERSION="IDMT_2015.03";

enum Quality_IDMT_type { TYPE_INVALID, TYPE_BAD, TYPE_GOOD };

typedef struct {
  bool smooth;
  bool detval;
  Quality_IDMT_type quality_l;
  Quality_IDMT_type quality_r;
} Quality_IDMT_data;

class Quality_IDMT {
private:
  bool _use_smooth;
  bool _use_pdetected;
  int  _start_smooth;
  int  _stop_smooth;
  int  _start_detval;
  int  _stop_detval;
  list<Quality_IDMT_data> _data;
public:
  inline Quality_IDMT(){ clear(); }
  inline void clear(){ 
    _use_smooth    = false;
    _use_pdetected = false;
    _start_smooth  = -1;
    _stop_smooth   = -1;
    _start_detval  = -1;
    _stop_detval   = -1;
    _data.clear();
  }
  inline bool getSmooth(){ return _use_smooth; }
  inline bool getPdetected() { return _use_pdetected; }
  inline int getStartSmooth(){ return _start_smooth; }
  inline int getStopSmooth() { return _stop_smooth; }
  inline int getStartDetval(){ return _start_detval; }
  inline int getStopDetval() { return _stop_detval; }
  inline const list<Quality_IDMT_data>* getData(){ return &_data; } 

  inline void setSmooth(bool use_smooth){ _use_smooth = use_smooth; }
  inline void setPdetected(bool use_pdetected){ _use_pdetected = use_pdetected; }
  inline void setStartSmooth(uint start_smooth){ _start_smooth = start_smooth; }
  inline void setStopSmooth(uint stop_smooth){ _stop_smooth = stop_smooth; }
  inline void setStartDetval(uint start_detval){ _start_detval = start_detval; }
  inline void setStopDetval(uint stop_detval){ _stop_detval = stop_detval; }
  inline void add(const Quality_IDMT_data &data){ _data.push_back(data); }

  inline bool cutoff(int first_valid_pos, int last_valid_pos){
    int last_pos   = _data.size() -1;
    last_valid_pos = last_valid_pos + 1;

    if ( first_valid_pos >= 0               && first_valid_pos <= last_pos && 
         last_valid_pos  >= first_valid_pos && last_valid_pos  <= last_pos ){
      std::list<Quality_IDMT_data>::iterator it_first, it_last;
      it_first = _data.begin();
      it_last  = _data.begin();
      advance(it_first,first_valid_pos);
      advance(it_last,last_valid_pos);
      //remove firt elements
      _data.erase(_data.begin(),it_first);
      //remove last elements
      _data.erase(it_last,_data.end());
      return true;
    }
    
    return false;
  }

};

/**
 * class IDMT
 * 
 */

class IDMT : public Quality, public Plugin
{
public:

  // Constructors/Destructors
  //  

  /**
   * Empty Constructor
   * @param log
   */
  IDMT (LogFileWriter *log);

  /**
   * Empty Destructor
   */
  virtual ~IDMT ();

  bool parseDataFile (string file_path, list<Data*> &list_data, streampos *line_num_stop = NULL);

  inline string               getEyetrackerCode(){ return "StaticBinocular"; }
  inline string               getPluginVersion() { return IDMT_VERSION;       }
  inline string               getPluginCompany() { return "?";               }
  inline string               getPluginModel()   { return "IDMT";             }
  inline string               getPluginRate()    { return "10Hz";            }

  bool writeQualityHeader (string output_path, string file_prefix);
  bool writeQualityOutput (list<string> &list_quality);
  bool calculateQuality   (list<Data*> &list_data, list<string> &list_quality);


  inline bool setPdetected(bool use_pdetected, uint pdetected_lenght){
    if( !use_pdetected ){ _use_pdetected = use_pdetected; return true; }
    else if( pdetected_lenght > 0 ){
      _pdetected_lenght = pdetected_lenght;
      _use_pdetected    = true;
      return true;
    }else return false;
  }
  inline bool setQualityWindow(bool use_smooth, uint window_lenght, uint window_min) {
    if(!use_smooth){ _use_smooth = use_smooth; return true; }
    else if( window_lenght >= WIN_MIN_VALID && window_lenght >= window_min ){
      _window_length = window_lenght;
      _window_min    = window_min;
      _use_smooth    = true;
      return true;
    }else return false;
  }
  inline bool setImageSize(uint image_height, uint image_width ) {
    if( image_height > 0 && image_width > 0 ){
      _image_height = image_height;
      _image_width  = image_width;
      return true;
    }else return false;
  }
  inline bool setBilderPath (string bilder_path)
  {
    if( bilder_path != "" ){
      _bilder_path = etbutler::extractFileFolderFromPath(bilder_path);
      _bilder_name = etbutler::extractFileNameFromPath(bilder_path, _bilder_ext);
      return true;
    }else return false;
  }
  inline bool setCombi(bool use_combi, uint combi, float bild_distance_x, float bild_distance_y, float user_distance){
    if( !use_combi ){ _use_combi = use_combi; return true; }
    else if( combi >= 1 && combi <= COMBI_MAX && user_distance > 0 ){
      _combi = combi; _bild_distance_x = bild_distance_x; _bild_distance_y = bild_distance_y; _user_distance = user_distance;
      _use_combi = true;
      return true;
    }else return false;
  }

private:

  LogFileWriter      *_log;

  uint _pdetected_lenght;
  bool _use_pdetected;

  uint _window_length;
  uint _window_min;
  bool _use_smooth;

  Quality_IDMT _quality_file;

  uint _image_height;
  uint _image_width;

  string _bilder_name;
  string _bilder_ext;

  uint  _combi;
  float _bild_distance_x;
  float _bild_distance_y;
  float _user_distance;
  bool  _use_combi;

  static const uint WIN_MIN_VALID = 3;
  static const uint LIMIT_MAX_GOOD = 20;
  static const uint COMBI_MAX     = 16;
  static const uint COMBI_MIN_PHI = 9;
  static const uint GAZETRACK_X = -310;
  static const uint GAZETRACK_Y = 460;


  struct Pos_combi{
    unsigned int lcx;
    unsigned int lcy;
    unsigned int lcz;
    unsigned int lvpx;
    unsigned int lvpy;
    unsigned int lvpz;
    unsigned int rcx;
    unsigned int rcy;
    unsigned int rcz;
    unsigned int rvpx;
    unsigned int rvpy;
    unsigned int rvpz;
    unsigned int lvx;
    unsigned int lvy;
    unsigned int lvz;
    unsigned int lvxuc;
    unsigned int lvyuc;
    unsigned int lvzuc;
    unsigned int rvx;
    unsigned int rvy;
    unsigned int rvz;
    unsigned int rvxuc;
    unsigned int rvyuc;
    unsigned int rvzuc;
    //position for combinations with phi algorithm
    unsigned int lphi;
    unsigned int lthe;
    unsigned int rphi;
    unsigned int rthe;
    unsigned int lphiuc;
    unsigned int ltheuc;
    unsigned int rphiuc;
    unsigned int rtheuc;
  };

private:
  //private method
  void apply_combi(const Pos_combi &pos_combi, const vector<string> &line_separate, float &lvx, float &lvy, float &rvx, float &rvy);

};

#endif // IDMT_H
