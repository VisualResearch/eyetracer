#include "common.hpp"
#include "IDMT.hpp"
#include <iomanip>
#include <sstream>
#ifdef __unix
#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/regex.hpp>
using namespace boost;
#else
#include <regex>
using namespace std::tr1;
#endif



// Constructors/Destructors
//  

IDMT::IDMT (LogFileWriter *log) 
  : Quality(log), Plugin(log) , _log(log)
{
  _pdetected_lenght = 0;
  _use_pdetected    = false;

  _window_length    = 0;
  _window_min       = 0;
  _use_smooth       = false;

  _quality_file.clear(); 
  _image_height     = 0;
  _image_width      = 0;
  _bilder_name      = "";
  _bilder_ext       = "";

  _combi           = 0;
  _bild_distance_x = 0;
  _bild_distance_y = 0;
  _user_distance   = 0;
  _use_combi       = false;
}

IDMT::~IDMT () { }


//  
// Methods
//  


void IDMT::apply_combi(const Pos_combi &pos_combi, const vector<string> &line_separate, float &left_x, float &left_y, float &right_x, float &right_y){
  double lcx = 0, lvx = 0, lhori  = -1;
  double lcy = 0, lvy = 0, lverti = -1;
  double lcz = 0, lvz = 0, rhori  = -1;
  double rcx = 0, rvx = 0, rverti = -1;
  double rcy = 0, rvy = 0; 
  double rcz = 0, rvz = 0; 

  left_x  = -1;
  left_y  = -1;
  right_x = -1;
  right_y = -1;

  //this part is the same for combi with and without phi
  if( (_combi>=1 && _combi<=4) || (_combi>=COMBI_MIN_PHI && _combi<=12) ){
    //only for first half combi
    //c = 3D Pupillenmittelpunkt im Gazetracker-Koordinatensystem (pupil of the subject)
    lcx = (stof(line_separate[pos_combi.lcx].c_str()));
    lcy = (stof(line_separate[pos_combi.lcy].c_str()));
    lcz = (stof(line_separate[pos_combi.lcz].c_str()));
    rcx = (stof(line_separate[pos_combi.rcx].c_str()));
    rcy = (stof(line_separate[pos_combi.rcy].c_str()));
    rcz = (stof(line_separate[pos_combi.rcz].c_str()));
  }else{
    //only for second half combi
    //vp = 3D Blickpunkt im Gazetracker-Koordinatensystem (viewpoint of the subject)
    lcx = (stof(line_separate[pos_combi.lvpx].c_str()));
    lcy = (stof(line_separate[pos_combi.lvpy].c_str()));
    lcz = (stof(line_separate[pos_combi.lvpz].c_str()));
    rcx = (stof(line_separate[pos_combi.rvpx].c_str()));
    rcy = (stof(line_separate[pos_combi.rvpy].c_str()));
    rcz = (stof(line_separate[pos_combi.rvpz].c_str()));
  }

  if( _combi<COMBI_MIN_PHI ){
    //this part is only without phi
    if( _combi%2 == 1 ){
      //only the odd combinations
      //v = 3D Gaze Vektor im Gazetracker-Koordinatensystem
      lvx = (stof(line_separate[pos_combi.lvx].c_str()));
      lvy = (stof(line_separate[pos_combi.lvy].c_str()));
      lvz = (stof(line_separate[pos_combi.lvz].c_str()));
      rvx = (stof(line_separate[pos_combi.rvx].c_str()));
      rvy = (stof(line_separate[pos_combi.rvy].c_str()));
      rvz = (stof(line_separate[pos_combi.rvz].c_str()));
    }else{
      //vUC = 3D Gaze Vektor (optical axis) im Gazetracker-Koordinatensystem
      lvx = (stof(line_separate[pos_combi.lvxuc].c_str()));
      lvy = (stof(line_separate[pos_combi.lvyuc].c_str()));
      lvz = (stof(line_separate[pos_combi.lvzuc].c_str()));
      rvx = (stof(line_separate[pos_combi.rvxuc].c_str()));
      rvy = (stof(line_separate[pos_combi.rvyuc].c_str()));
      rvz = (stof(line_separate[pos_combi.rvzuc].c_str()));
    }
  }else{
    //this part is only with phi
    if( _combi%2 == 1 ){
      //only the odd combinations
      //phi und theta = 3D Gaze Winkel im Gazetracker-Koordinatensystem
      lhori  = (stof(line_separate[pos_combi.lphi].c_str()));
      lverti = (stof(line_separate[pos_combi.lthe].c_str()));
      rhori  = (stof(line_separate[pos_combi.rphi].c_str()));
      rverti = (stof(line_separate[pos_combi.rthe].c_str()));
    }else{
      //phiUC und thetaUC = 3D Gaze Winkel (optical axis) im Gazetracker-Koordinatensystem
      lhori  = (stof(line_separate[pos_combi.lphiuc].c_str()));
      lverti = (stof(line_separate[pos_combi.ltheuc].c_str()));
      rhori  = (stof(line_separate[pos_combi.rphiuc].c_str()));
      rverti = (stof(line_separate[pos_combi.rtheuc].c_str()));
    }
  }

  if( _combi<COMBI_MIN_PHI ){
    //apply nonphi algo
    if( lvx!=-1 && lcx!=-1 ){
      double multi;

      if( _combi==3 || _combi==4 || _combi==7 || _combi==8 )
        multi=(_user_distance-lcz)/lvz;
      else
        multi=(_user_distance)/lvz;
      
      left_x = (float)(lcx+(lvx*multi))-_bild_distance_x;
      left_y = (float)(lcy+(lvy*multi))-_bild_distance_y;
    }
    if( rvx!=-1 && rcx!=-1 ){
      double multi;
              
      if( _combi==3 || _combi==4 || _combi==7 || _combi==8 )
        multi=(_user_distance-rcz)/rvz;
      else
        multi=(_user_distance)/rvz;
        
      right_x = (float)(rcx+(rvx*multi))-_bild_distance_x;
      right_y = (float)(rcy+(rvy*multi))-_bild_distance_y;
    }
  }else{
    //apply phi algo    
    if( lhori!=-1 && lcx!=-1 ){
      double add_x, add_y;

      if( _combi==11|| _combi==12 || _combi==15 || _combi==16 ){
        add_x=tan(etbutler::degtorad(lhori))*(_user_distance-lcz)*(-1);
        add_y=tan(etbutler::degtorad(lverti))*(_user_distance-lcz)*(-1);
      }else{
        add_x=tan(etbutler::degtorad(lhori))*(-_user_distance);
        add_y=tan(etbutler::degtorad(lverti))*(-_user_distance);
      }

      left_x = (float)(lcx+add_x)-_bild_distance_x;
      left_y = (float)(lcy+add_y)-_bild_distance_y;
    }

    if( rhori!=-1 && rcx!=-1 ){
      double add_x, add_y;

      if( _combi==11 || _combi==12 || _combi==15 || _combi==16 ){
        add_x=tan(etbutler::degtorad(rhori))*(_user_distance-rcz)*(-1);
        add_y=tan(etbutler::degtorad(rverti))*(_user_distance-rcz)*(-1);
      }else{
        add_x=tan(etbutler::degtorad(rhori))*(-_user_distance);
        add_y=tan(etbutler::degtorad(rverti))*(-_user_distance);
      }
    
      right_x = (float)(rcx+add_x)-_bild_distance_x;
      right_y = (float)(rcy+add_y)-_bild_distance_y;
    }
  }
}


bool IDMT::parseDataFile (string file_path, list<Data*> &list_data, streampos *line_num_stop){
  _log->writeDebug("function: bool IDMT::parseDataFile (string file_path, list<Data*> &list_data)");

  streampos afterHeaderPos   = 0; //store line position after heading to start reading data 
  streampos initialHeaderPos = 0;

  //data common to all outputs
  bool    found_header = false;
  Data   *data = NULL;
  string  subjectID = etbutler::extractFileNameFromPath( file_path );
  float ratioX=1., ratioY=1.; 
  int sizePX=0, sizePY=0;
  string imageName = "";

  //positions for all
  const unsigned int pos_time  = 0;
  unsigned int pos_lspx   = 0;
  unsigned int pos_lspy   = 0;
  unsigned int pos_ldiam  = 0;
  unsigned int pos_lvdiff = 0;
  unsigned int pos_rspx   = 0; 
  unsigned int pos_rspy   = 0;
  unsigned int pos_rdiam  = 0;
  unsigned int pos_rvdiff = 0;
  //positions for person detected
  unsigned int pos_c1aoix = 0;
  unsigned int pos_c1aoiy = 0;
  unsigned int pos_c2aoix = 0;
  unsigned int pos_c2aoiy = 0;
  unsigned int pos_c1lxa  = 0;
  unsigned int pos_c1lya  = 0;
  unsigned int pos_c1rxa  = 0;
  unsigned int pos_c1rya  = 0;
  unsigned int pos_c2lxa  = 0;
  unsigned int pos_c2lya  = 0;
  unsigned int pos_c2rxa  = 0;
  unsigned int pos_c2rya  = 0;
  //position for combinations
  Pos_combi pos_combi = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

  //For smooth algorithm
  uint window_pos;
  uint *window_smooth;

  //For person detected
  uint pd_pos;
  unsigned int *pd_c1aoix;
  unsigned int *pd_c1aoiy;
  unsigned int *pd_c2aoix;
  unsigned int *pd_c2aoiy;
  unsigned int *pd_c1lxa;
  unsigned int *pd_c1lya;
  unsigned int *pd_c1rxa;
  unsigned int *pd_c1rya;
  unsigned int *pd_c2lxa;
  unsigned int *pd_c2lya;
  unsigned int *pd_c2rxa;
  unsigned int *pd_c2rya; 

  //check parameters
  if( _use_smooth && !_use_pdetected ){
    _log->writeWarn("smooth is selected, but person detected is not. Deactivating smooth in: " + file_path);
  }

  //initialize quality info
  _quality_file.setPdetected(_use_pdetected);
  _quality_file.setSmooth(_use_smooth);
  _quality_file.clear();

  //open the file and process
  ifstream dataFile;
  dataFile.open (file_path, ios::in );
  if (dataFile.is_open()) {
    string  line;
    list<vector<string>> all_lines;

    //get the header
    while ( getline (dataFile,line) && !found_header ) {
      //separate by tab
      vector<string> line_separate;
      etbutler::split(line, '\t', line_separate);
      if( line_separate.size() > 1 ){
        if( line_separate[0] == "tsc1" ){
          // is the header (starts with "Time" word)
          for( unsigned int i = 1; i < line_separate.size(); i++){
            if( line_separate[i] == "Lspx"){
              pos_lspx = i;
            }
            else if( line_separate[i] == "Lspy"){
              pos_lspy = i;
            }
            else if( line_separate[i] == "Ldiam"){
              pos_ldiam = i;
            }
            else if( line_separate[i] == "Lvdiff"){
              pos_lvdiff = i;
            }
            else if( line_separate[i] == "Rspx"){
              pos_rspx = i;
            }
            else if( line_separate[i] == "Rspy"){
              pos_rspy = i;
            }
            else if( line_separate[i] == "Rdiam"){
              pos_rdiam = i;
            }
            else if( line_separate[i] == "Rvdiff"){
              pos_rvdiff = i;
            }
            //position for person detected
            else if( line_separate[i] == "c1AOIx"){
              pos_c1aoix = i;
            }
            else if( line_separate[i] == "c1AOIy"){
              pos_c1aoiy = i;
            }
            else if( line_separate[i] == "c2AOIx"){
              pos_c2aoix = i;
            }
            else if( line_separate[i] == "c2AOIy"){
              pos_c2aoiy = i;
            }
            else if( line_separate[i] == "c1LxA"){
              pos_c1lxa = i;
            }
            else if( line_separate[i] == "c1LyA"){
              pos_c1lya = i;
            }
            else if( line_separate[i] == "c1RxA"){
              pos_c1rxa = i;
            }
            else if( line_separate[i] == "c1RyA"){
              pos_c1rya = i;
            }
            else if(line_separate[i] == "c2LxA" ){
              pos_c2lxa = i;
            }
            else if(line_separate[i] == "c2LyA"){
              pos_c2lya = i;
            }
            else if(line_separate[i] == "c2RxA"){
              pos_c2rxa = i;
            }
            else if(line_separate[i] == "c2RyA"){
              pos_c2rya = i;
            }
            //position for combinations
            else if(line_separate[i] == "Lcx"){
              pos_combi.lcx = i;
            }
            else if(line_separate[i] == "Lcy"){
              pos_combi.lcy = i;
            }
            else if(line_separate[i] == "Lcz"){
              pos_combi.lcz = i;
            }
            else if(line_separate[i] == "Lvpx"){
              pos_combi.lvpx = i;
            }
            else if(line_separate[i] == "Lvpy"){
              pos_combi.lvpy = i;
            }
            else if(line_separate[i] == "Lvpz"){
              pos_combi.lvpz = i;
            }
            else if(line_separate[i] == "Rcx"){
              pos_combi.rcx = i;
            }
            else if(line_separate[i] == "Rcy"){
              pos_combi.rcy = i;
            }
            else if(line_separate[i] == "Rcz"){
              pos_combi.rcz = i;
            }
            else if(line_separate[i] == "Rvpx"){
              pos_combi.rvpx = i;
            }
            else if(line_separate[i] == "Rvpy"){
              pos_combi.rvpy = i;
            }
            else if(line_separate[i] == "Rvpz"){
              pos_combi.rvpz = i;
            }
            //position for combinations nonphi
            else if(line_separate[i] == "Lvx"){
              pos_combi.lvx = i;
            }
            else if(line_separate[i] == "Lvy"){
              pos_combi.lvy = i;
            }
            else if(line_separate[i] == "Lvz"){
              pos_combi.lvz = i;
            }
            else if(line_separate[i] == "LvxUC"){
              pos_combi.lvxuc = i;
            }
            else if(line_separate[i] == "LvyUC"){
              pos_combi.lvyuc = i;
            }
            else if(line_separate[i] == "LvzUC"){
              pos_combi.lvzuc = i;
            }
            else if(line_separate[i] == "Rvx"){
              pos_combi.rvx = i;
            }
            else if(line_separate[i] == "Rvy"){
              pos_combi.rvy = i;
            }
            else if(line_separate[i] == "Rvz"){
              pos_combi.rvz = i;
            }
            else if(line_separate[i] == "RvxUC"){
              pos_combi.rvxuc = i;
            }
            else if(line_separate[i] == "RvyUC"){
              pos_combi.rvyuc = i;
            }
            else if(line_separate[i] == "RvzUC"){
              pos_combi.rvzuc = i;
            }
            //position for combinations with phi
            else if(line_separate[i] == "Lphi"){
              pos_combi.lphi = i;
            }
            else if(line_separate[i] == "Ltheta"){
              pos_combi.lthe = i;
            }
            else if(line_separate[i] == "Rphi"){
              pos_combi.rphi = i;
            }
            else if(line_separate[i] == "Rtheta"){
              pos_combi.rthe = i;
            }
            else if(line_separate[i] == "LphiUC"){
              pos_combi.lphiuc = i;
            }
            else if(line_separate[i] == "LthetaUC"){
              pos_combi.ltheuc = i;
            }
            else if(line_separate[i] == "RphiUC"){
              pos_combi.rphiuc = i;
            }
            else if(line_separate[i] == "RthetaUC"){
              pos_combi.rtheuc = i;
            }
          }
          found_header = true;
        }
      }
      afterHeaderPos = dataFile.tellg();
    }

    //check if the header is correct
    if( !pos_lspx  || !pos_lspy  || !pos_ldiam  || !pos_lvdiff
        || !pos_rspx  || !pos_rspy  || !pos_rdiam  || !pos_rvdiff ){
      _log->writeWarn("Header Format not valid in file: " + file_path);
      if( !pos_lspx  ){ _log->writeWarn("lspx not found"); }
      if( !pos_lspy  ){ _log->writeWarn("lspy not found"); }
      if( !pos_ldiam  ){ _log->writeWarn("ldiam not found"); }
      if( !pos_lvdiff   ){ _log->writeWarn("lvdiff not found"); }
      if( !pos_rspx  ){ _log->writeWarn("rspx not found"); }
      if( !pos_rspy  ){ _log->writeWarn("rspy not found"); }
      if( !pos_rdiam  ){ _log->writeWarn("rdiam not found"); }
      if( !pos_rvdiff   ){ _log->writeWarn("rvdiff not found"); }
      dataFile.close();
      return false;
    }

    if( _use_pdetected 
        && ( !pos_c1aoix || !pos_c1aoiy || !pos_c2aoix || !pos_c2aoiy
             || !pos_c1lxa  || !pos_c1lya  || !pos_c1rxa  || !pos_c1rya 
             || !pos_c2lxa  || !pos_c2lya  || !pos_c2rxa  || !pos_c2rya ) ){
      _log->writeWarn("Header Format not valid in file (if person_detected): " + file_path);
      if( !pos_c1aoix ){ _log->writeWarn("c1aoix not found"); }
      if( !pos_c1aoiy ){ _log->writeWarn("c1aoiy not found"); }
      if( !pos_c2aoix ){ _log->writeWarn("c2aoix not found"); }
      if( !pos_c2aoiy ){ _log->writeWarn("c2aoiy not found"); }
      if( !pos_c1lxa  ){ _log->writeWarn("c1lxa not found"); }
      if( !pos_c1lya  ){ _log->writeWarn("c1lya not found"); }
      if( !pos_c1rxa  ){ _log->writeWarn("c1rxa not found"); }
      if( !pos_c1rya  ){ _log->writeWarn("c1rya not found"); }
      if( !pos_c2lxa  ){ _log->writeWarn("c2lxa not found"); }
      if( !pos_c2lya  ){ _log->writeWarn("c2lya not found"); }
      if( !pos_c2rxa  ){ _log->writeWarn("c2rxa not found"); }
      if( !pos_c2rya  ){ _log->writeWarn("c2rya not found"); }
      dataFile.close();
      return false;
    }
    if( _use_combi ){
      if( !pos_combi.lcx      || !pos_combi.lcy   || !pos_combi.lcz   || !pos_combi.lvpx || !pos_combi.lvpy
          || !pos_combi.lvpz  || !pos_combi.rcx   || !pos_combi.rcy   || !pos_combi.rcz  || !pos_combi.rvpx
          || !pos_combi.rvpy  || !pos_combi.rvpz ){
        _log->writeWarn("Header Format not valid in file (for combi algorithm): " + file_path);          
        if( !pos_combi.lcx ){ _log->writeWarn("lcx not found"); }
        if( !pos_combi.lcy ){ _log->writeWarn("lcy not found"); }
        if( !pos_combi.lcz ){ _log->writeWarn("lcz not found"); }
        if( !pos_combi.lvpx ){ _log->writeWarn("lvpx not found"); }
        if( !pos_combi.lvpy ){ _log->writeWarn("lvpy not found"); }
        if( !pos_combi.lvpz ){ _log->writeWarn("lvpz not found"); }
        if( !pos_combi.rcx ){ _log->writeWarn("rcx not found"); }
        if( !pos_combi.rcy ){ _log->writeWarn("rcy not found"); }
        if( !pos_combi.rcz ){ _log->writeWarn("rcz not found"); }
        if( !pos_combi.rvpx ){ _log->writeWarn("rvpx not found"); }
        if( !pos_combi.rvpy ){ _log->writeWarn("rvpy not found"); }
        if( !pos_combi.rvpz ){ _log->writeWarn("rvpz not found"); }
        dataFile.close();
        return false;
      }
      if( _combi < COMBI_MIN_PHI ){
        if( !pos_combi.lvx   || !pos_combi.lvy  || !pos_combi.lvz
            || !pos_combi.lvxuc || !pos_combi.lvyuc || !pos_combi.lvzuc || !pos_combi.rvx  || !pos_combi.rvy
            || !pos_combi.rvz   || !pos_combi.rvxuc || !pos_combi.rvyuc || !pos_combi.rvzuc ){
          _log->writeWarn("Header Format not valid in file (for combi nophi algorithm): " + file_path);
          if( !pos_combi.lvxuc ){ _log->writeWarn("lvxuc not found"); }
          if( !pos_combi.lvyuc ){ _log->writeWarn("lvyuc not found"); }
          if( !pos_combi.lvzuc ){ _log->writeWarn("lvzuc not found"); }
          if( !pos_combi.rvx ){ _log->writeWarn("rvx not found"); }
          if( !pos_combi.rvy ){ _log->writeWarn("rvy not found"); }
          if( !pos_combi.rvz ){ _log->writeWarn("rvz not found"); }
          if( !pos_combi.rvxuc ){ _log->writeWarn("rvxuc not found"); }
          if( !pos_combi.rvyuc ){ _log->writeWarn("rvyuc not found"); }
          if( !pos_combi.rvzuc ){ _log->writeWarn("rvzuc not found"); }
          dataFile.close();
          return false;
        }
      }else{
        if( !pos_combi.lphi      || !pos_combi.lthe   || !pos_combi.rphi   || !pos_combi.rthe
            || !pos_combi.lphiuc || !pos_combi.ltheuc || !pos_combi.rphiuc || !pos_combi.rtheuc ){
          _log->writeWarn("Header Format not valid in file (for combi phi algorithm): " + file_path);
          if( !pos_combi.lphi ){ _log->writeWarn("lphi not found"); }
          if( !pos_combi.lthe ){ _log->writeWarn("lthe not found"); }
          if( !pos_combi.rphi ){ _log->writeWarn("rphi not found"); }
          if( !pos_combi.rthe ){ _log->writeWarn("rthe not found"); }
          if( !pos_combi.lphiuc ){ _log->writeWarn("lphiuc not found"); }
          if( !pos_combi.ltheuc ){ _log->writeWarn("ltheuc not found"); }
          if( !pos_combi.rphiuc ){ _log->writeWarn("rphiuc not found"); }
          if( !pos_combi.rtheuc ){ _log->writeWarn("rtheuc not found"); }
          dataFile.close();
          return false;
        }
      }
    }

    // get back to the position when data starts
    if( afterHeaderPos != initialHeaderPos) dataFile.seekg(afterHeaderPos);

    //calculate conversion millimiters to pixels
    string image_path = _bilder_path + FILE_SLASH + _bilder_name + "." + _bilder_ext;
    if( etbutler::getImageSize( image_path , sizePX, sizePY ) && sizePX > 0 && sizePY > 0 ){
      ratioX = ((float)sizePX)/_image_width; ratioY = ((float)sizePY)/_image_height;
      _log->writeDebug("SizePX=" + etbutler::int2str(sizePX) +  " SizePY=" + etbutler::int2str(sizePY) );
      _log->writeDebug("RatioX=" + etbutler::float2str(ratioX) +  " RatioY=" + etbutler::float2str(ratioY) );
      string value = "imagedimension=" +  etbutler::int2str(sizePX) + "x" + etbutler::int2str(sizePY);
      insertDataExtra("media", value);
    }else{
      _log->writeWarn("Impossible to get pixels image Size from: " + image_path);
      _log->writeWarn("Impossible to use ratio");
      dataFile.close();
      return false;
    }

    //allocate memory for person detected
    if( _use_pdetected ){
      pd_c1aoix = new uint[_pdetected_lenght]();
      pd_c1aoiy = new uint[_pdetected_lenght]();
      pd_c2aoix = new uint[_pdetected_lenght]();
      pd_c2aoiy = new uint[_pdetected_lenght]();
      pd_c1lxa  = new uint[_pdetected_lenght]();
      pd_c1lya  = new uint[_pdetected_lenght]();
      pd_c1rxa  = new uint[_pdetected_lenght]();
      pd_c1rya  = new uint[_pdetected_lenght]();
      pd_c2lxa  = new uint[_pdetected_lenght]();
      pd_c2lya  = new uint[_pdetected_lenght]();
      pd_c2rxa  = new uint[_pdetected_lenght]();
      pd_c2rya  = new uint[_pdetected_lenght](); 
      pd_pos    = 0;
      //allocate memory for window
      if( _use_smooth ){
        window_smooth = new uint[_window_length]();
        window_pos    = 0;
      }
    }

    //allocate memory for data
    data = new Data(file_path, "", subjectID, _bilder_name, _bilder_ext);
    int valid_first = -1; //first valid value to apply cutoff
    int valid_last  = -1; //first valid value to apply cutoff

    //get the data
    while ( getline (dataFile,line) ){
      vector<string> line_separate;
      etbutler::split(line, '\t', line_separate);
      if( line_separate.size() > 0 ){


        //Create the data
        string d_time = line_separate[pos_time];
        string d_lx   = "0";
        string d_rx   = "0";
        string d_ly   = "0";
        string d_ry   = "0";
        string d_ldia = "0";
        string d_rdia = "0";
        bool   d_lval = false;
        bool   d_rval = false;
        Quality_IDMT_type quality_l, quality_r;

        //first check the validity per eye
        float lval, rval;
        istringstream(line_separate[pos_lvdiff]) >> lval;
        istringstream(line_separate[pos_rvdiff]) >> rval;

        //Use combination algorithm if selected
        float lx=-1, ly=-1, rx=-1, ry=-1;
        if( _use_combi ){
          apply_combi( pos_combi, line_separate, lx, ly, rx, ry );
        }else{
          lx = stof(line_separate[pos_lspx].c_str());
          ly = stof(line_separate[pos_lspy].c_str());
          rx = stof(line_separate[pos_rspx].c_str());
          ry = stof(line_separate[pos_rspy].c_str());
        }

        //0,0 is in the centerdown of the bild => translate 0,0 to leftdown corner 
        //distances are in mm => convert to pixel
        if(lx!=-1 && ly!=-1){
          lx = lx+(_image_width/2);
          lx *= ratioX;
          //lx = -lx;
          ly = ly-(_image_height);
          ly *= ratioY;
          ly = -ly;
        }
        if(rx!=-1 && ry!=-1){
          rx = rx+(_image_width/2);
          rx *= ratioX;
          //rx = -rx;
          ry = ry-(_image_height);
          ry *= ratioY;
          ry = -ry;
        }

        //check validity
        if(lval > 0){
          d_lx = etbutler::float2str(lx);
          d_ly = etbutler::float2str(ly);
          d_ldia = etbutler::float2str((stof(line_separate[pos_ldiam].c_str())*100.0f+0.5f)/100.0f);
          if( lx>0 && lx<sizePX && ly>0 && ly<sizePY){
            d_lval = true;
            if( lval <= LIMIT_MAX_GOOD ) quality_l = TYPE_GOOD;
            else quality_l = TYPE_BAD;
          }else{
            quality_l = TYPE_BAD;
          }
        }else quality_l = TYPE_INVALID;

        if(rval > 0){
          d_rx = etbutler::float2str(rx);
          d_ry = etbutler::float2str(ry);
          d_rdia = etbutler::float2str((stof(line_separate[pos_rdiam].c_str())*100.0f+0.5f)/100.0f);
          if( rx>0 && rx<sizePX && ry>0 && ry<sizePY){
            d_rval = true;
            if( rval <= LIMIT_MAX_GOOD ) quality_r = TYPE_GOOD;
            else quality_r = TYPE_BAD;
          }else{
            quality_r = TYPE_BAD;
          }
        }else quality_r = TYPE_INVALID;

        bool detval = false;
        bool smooth = false;
        if( _use_pdetected ){
          //calculate Person Detected
          pd_c1aoix[pd_pos] = stoul(line_separate[pos_c1aoix]);
          pd_c1aoiy[pd_pos] = stoul(line_separate[pos_c1aoiy]);
          pd_c2aoix[pd_pos] = stoul(line_separate[pos_c2aoix]);
          pd_c2aoiy[pd_pos] = stoul(line_separate[pos_c2aoiy]);
          pd_c1lxa[pd_pos]  = stoul(line_separate[pos_c1lxa]);
          pd_c1lya[pd_pos]  = stoul(line_separate[pos_c1lya]);
          pd_c1rxa[pd_pos]  = stoul(line_separate[pos_c1rxa]);
          pd_c1rya[pd_pos]  = stoul(line_separate[pos_c1rya]);
          pd_c2lxa[pd_pos]  = stoul(line_separate[pos_c2lxa]);
          pd_c2lya[pd_pos]  = stoul(line_separate[pos_c2lya]);
          pd_c2rxa[pd_pos]  = stoul(line_separate[pos_c2rxa]);
          pd_c2rya[pd_pos]  = stoul(line_separate[pos_c2rya]);
          pd_pos = (pd_pos+1)%_pdetected_lenght;
          int facemove   = ( (!etbutler::equalArrayElements(pd_c1aoix, _pdetected_lenght)) ||
                             (!etbutler::equalArrayElements(pd_c1aoiy, _pdetected_lenght)) ||
                             (!etbutler::equalArrayElements(pd_c2aoix, _pdetected_lenght)) ||
                             (!etbutler::equalArrayElements(pd_c2aoiy, _pdetected_lenght)) ) ? 1 : 0;
          int c1EyesMove = ( (!etbutler::equalArrayElements(pd_c1lxa, _pdetected_lenght)) ||
                             (!etbutler::equalArrayElements(pd_c1lya, _pdetected_lenght)) ||
                             (!etbutler::equalArrayElements(pd_c1rxa, _pdetected_lenght)) ||
                             (!etbutler::equalArrayElements(pd_c1rya, _pdetected_lenght)) ) ? 1 : 0;
          int c2EyesMove = ( (!etbutler::equalArrayElements(pd_c2lxa, _pdetected_lenght)) ||
                             (!etbutler::equalArrayElements(pd_c2lya, _pdetected_lenght)) ||
                             (!etbutler::equalArrayElements(pd_c2rxa, _pdetected_lenght)) ||
                             (!etbutler::equalArrayElements(pd_c2rya, _pdetected_lenght)) ) ? 1 : 0;
          detval = ( ( facemove && c1EyesMove  ) || ( facemove && c2EyesMove ) || ( c1EyesMove && c2EyesMove ) ) ? true : false;
          detval = ( (d_lval || d_rval) && detval ) ? true : false;

          //smooth algorithm using Person detected and a window of X of Y valid
          if( _use_smooth ){
            window_smooth[window_pos] = ( detval ) ? 1 : 0 ;
            window_pos = (window_pos+1)%_window_length;

            uint sum = 0;
            for(uint i=0; i<_window_length; i++) sum += window_smooth[i];
            if(sum >= _window_min){ smooth = true; }
          }
        }

        bool valid = false;
        if( !_use_pdetected ){
          //person detected is not selected => valid ALL the data
          valid = true;
        }else{ 
          //person detected is selected
          if( detval ){
            // person is detected 
            valid = true;
            if( _quality_file.getStartDetval() < 0 ){ _quality_file.setStartDetval( (_quality_file.getData())->size() );  }
            _quality_file.setStopDetval(_quality_file.getData()->size());
            if( _use_smooth && smooth ){
              // use smooth algorithm and the data is smooth
              if( _quality_file.getStartSmooth() < 0 ){ _quality_file.setStartSmooth( (_quality_file.getData())->size() ); }
              _quality_file.setStopSmooth(_quality_file.getData()->size());
            }
          }
        }

        //add the stadistics data for the quality out
        Quality_IDMT_data quality_data;
        quality_data.smooth    = smooth;
        quality_data.detval    = detval;
        quality_data.quality_l = quality_l;
        quality_data.quality_r = quality_r;
        _quality_file.add(quality_data);

        //write a valid or invalid line
        if( valid ){
          data->add(d_time, d_lx, d_ly, d_ldia, d_ldia, d_lval, d_rx, d_ry, d_rdia, d_rdia, d_rval);
          //store the first valid value
          if( valid_first < 0 ) valid_first = data->last_index(); 
          //store the last valid value
          valid_last = data->last_index(); 
        }else data->add(d_time, "0", "0", "0", "0", false, "0", "0", "0", "0", false );
        //data->add(d_time, d_lx, d_ly, d_ldia, d_ldia, false, d_rx, d_ry, d_rdia, d_rdia, false );
      }
    }

    // do cutoff using the index of the first and last valid data
    if( !data->cutoff(valid_first, valid_last) || !_quality_file.cutoff(valid_first, valid_last)){
      _log->writeWarn("Cutoff does not work. First:" + 
                      etbutler::int2str(valid_first) + " Last:"  + etbutler::int2str(valid_last) + 
                      " File:"  + file_path);
    }

    // save chunk of data
    list_data.push_back(data); //list data is not important in IDMT because every file is independent
    dataFile.close();

    //destory allocated memory
    if( _use_pdetected ){
      delete[](pd_c1aoix);
      delete[](pd_c1aoiy);
      delete[](pd_c2aoix);
      delete[](pd_c2aoiy);
      delete[](pd_c1lxa);
      delete[](pd_c1lya);
      delete[](pd_c1rxa);
      delete[](pd_c1rya);
      delete[](pd_c2lxa);
      delete[](pd_c2lya);
      delete[](pd_c2rxa);
      delete[](pd_c2rya);
      if( _use_smooth ){ delete[](window_smooth); }
    }
    return true;
  }else{
    _log->writeWarn("Cannot open Data file:" + file_path);
    return false;
  }
}


bool IDMT::calculateQuality (list<Data*> &list_data, list<string> &list_quality){
  _log->writeDebug("function: bool IDMT::calculateQuality (list<Data*> &list_data, list<string> &list_quality)");

  const list<Quality_IDMT_data> *list_data_idmt = _quality_file.getData();

  uint lines_total_raw      = 0;
  uint lines_total_smooth   = 0;
  uint lines_total_pd       = 0;

  uint lines_invalid_raw_l    = 0;
  uint lines_invalid_smooth_l = 0;
  uint lines_invalid_pd_l     = 0;
  uint lines_bad_raw_l        = 0;
  uint lines_bad_smooth_l     = 0;
  uint lines_bad_pd_l         = 0;
  uint lines_good_raw_l       = 0;
  uint lines_good_smooth_l    = 0;
  uint lines_good_pd_l        = 0;

  uint lines_invalid_raw_r    = 0;
  uint lines_invalid_smooth_r = 0;
  uint lines_invalid_pd_r     = 0;
  uint lines_bad_raw_r        = 0;
  uint lines_bad_smooth_r     = 0;
  uint lines_bad_pd_r         = 0;
  uint lines_good_raw_r       = 0;
  uint lines_good_smooth_r    = 0;
  uint lines_good_pd_r        = 0;


  list<Quality_IDMT_data>::const_iterator itr;
  int pos;
  for(pos = 0, itr = list_data_idmt->begin(); itr != list_data_idmt->end(); itr++, pos++){
    Quality_IDMT_data element = *itr;
    lines_total_raw++;
    switch(element.quality_l){
    case TYPE_INVALID: lines_invalid_raw_l++; break;
    case TYPE_BAD:     lines_bad_raw_l++; break;
    case TYPE_GOOD:    lines_good_raw_l++; break;
    }
    switch(element.quality_r){
    case TYPE_INVALID: lines_invalid_raw_r++; break;
    case TYPE_BAD:     lines_bad_raw_r++; break;
    case TYPE_GOOD:    lines_good_raw_r++; break;
    }
    if( pos >= _quality_file.getStartDetval() && pos <= _quality_file.getStopDetval() && element.detval ){
      lines_total_pd++;
      switch(element.quality_l){
      case TYPE_INVALID: lines_invalid_pd_l++; break;
      case TYPE_BAD:     lines_bad_pd_l++; break;
      case TYPE_GOOD:    lines_good_pd_l++; break;
      }
      switch(element.quality_r){
      case TYPE_INVALID: lines_invalid_pd_r++; break;
      case TYPE_BAD:     lines_bad_pd_r++; break;
      case TYPE_GOOD:    lines_good_pd_r++; break;
      }
      if( pos >= _quality_file.getStartSmooth() && pos <= _quality_file.getStopSmooth() && element.smooth ){
        lines_total_smooth++;
        switch(element.quality_l){
        case TYPE_INVALID: lines_invalid_smooth_l++; break;
        case TYPE_BAD:     lines_bad_smooth_l++; break;
        case TYPE_GOOD:    lines_good_smooth_l++; break;
        }
        switch(element.quality_r){
        case TYPE_INVALID: lines_invalid_smooth_r++; break;
        case TYPE_BAD:     lines_bad_smooth_r++; break;
        case TYPE_GOOD:    lines_good_smooth_r++; break;
        }
      }
    }
  }

  //calculate general stadistics
  //uint lines_no_detected = lines_total_raw - lines_total_pd;
  float percent_total_raw    = 0;
  float percent_total_pd     = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_total_pd*1.0f))*100+0.5)/100.0f;
  float percent_total_smooth = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_total_smooth*1.0f))*100+0.5)/100.0f;

  //calculate left eye stadistics
  float l_invalid_raw    = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_invalid_raw_l*1.0f))*100+0.5)/100.0f;
  float l_bad_raw        = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_bad_raw_l*1.0f))*100+0.5)/100.0f;
  float l_good_raw       = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_good_raw_l*1.0f))*100+0.5)/100.0f;
  float l_invalid_pd     = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_invalid_pd_l*1.0f))*100+0.5)/100.0f;
  float l_bad_pd         = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_bad_pd_l*1.0f))*100+0.5)/100.0f;
  float l_good_pd        = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_good_pd_l*1.0f))*100+0.5)/100.0f;
  float l_invalid_smooth = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_invalid_smooth_l*1.0f))*100+0.5)/100.0f;
  float l_bad_smooth     = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_bad_smooth_l*1.0f))*100+0.5)/100.0f;
  float l_good_smooth    = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_good_smooth_l*1.0f))*100+0.5)/100.0f;

  float l_sum_raw    = 100;
  float l_sum_pd     = l_good_pd+l_bad_pd+l_invalid_pd;
  float l_sum_smooth = l_good_smooth+l_bad_smooth+l_invalid_smooth;

  float l_invalid_raw_topd    = 0;
  float l_bad_raw_topd        = 0;
  float l_good_raw_topd       = 0;
  float l_invalid_pd_topd     = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_invalid_pd_l*1.0f))*100+0.5)/100.0f;
  float l_bad_pd_topd         = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_bad_pd_l*1.0f))*100+0.5)/100.0f;
  float l_good_pd_topd        = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_good_pd_l*1.0f))*100+0.5)/100.0f;
  float l_invalid_smooth_topd = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_invalid_smooth_l*1.0f))*100+0.5)/100.0f;
  float l_bad_smooth_topd     = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_bad_smooth_l*1.0f))*100+0.5)/100.0f;
  float l_good_smooth_topd    = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_good_smooth_l*1.0f))*100+0.5)/100.0f;

  float l_sum_raw_topd    = 0;
  float l_sum_pd_topd     = l_good_pd_topd+l_bad_pd_topd+l_invalid_pd_topd;
  float l_sum_smooth_topd = l_good_smooth_topd+l_bad_smooth_topd+l_invalid_smooth_topd;

  //calculate right eye stadistics
  float r_invalid_raw    = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_invalid_raw_r*1.0f))*100+0.5)/100.0f;
  float r_bad_raw        = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_bad_raw_r*1.0f))*100+0.5)/100.0f;
  float r_good_raw       = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_good_raw_r*1.0f))*100+0.5)/100.0f;
  float r_invalid_pd     = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_invalid_pd_r*1.0f))*100+0.5)/100.0f;
  float r_bad_pd         = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_bad_pd_r*1.0f))*100+0.5)/100.0f;
  float r_good_pd        = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_good_pd_r*1.0f))*100+0.5)/100.0f;
  float r_invalid_smooth = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_invalid_smooth_r*1.0f))*100+0.5)/100.0f;
  float r_bad_smooth     = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_bad_smooth_r*1.0f))*100+0.5)/100.0f;
  float r_good_smooth    = (float)(((100.0f/(lines_total_raw*1.0f))*(lines_good_smooth_r*1.0f))*100+0.5)/100.0f;

  float r_sum_raw    = 100;
  float r_sum_pd     = r_good_pd+r_bad_pd+r_invalid_pd;
  float r_sum_smooth = r_good_smooth+r_bad_smooth+r_invalid_smooth;

  float r_invalid_raw_topd    = 0;
  float r_bad_raw_topd        = 0;
  float r_good_raw_topd       = 0;
  float r_invalid_pd_topd     = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_invalid_pd_r*1.0f))*100+0.5)/100.0f;
  float r_bad_pd_topd         = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_bad_pd_r*1.0f))*100+0.5)/100.0f;
  float r_good_pd_topd        = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_good_pd_r*1.0f))*100+0.5)/100.0f;
  float r_invalid_smooth_topd = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_invalid_smooth_r*1.0f))*100+0.5)/100.0f;
  float r_bad_smooth_topd     = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_bad_smooth_r*1.0f))*100+0.5)/100.0f;
  float r_good_smooth_topd    = (float)(((100.0f/(lines_total_pd*1.0f))*(lines_good_smooth_r*1.0f))*100+0.5)/100.0f;

  float r_sum_raw_topd    = 0;
  float r_sum_pd_topd     = r_good_pd_topd+r_bad_pd_topd+r_invalid_pd_topd;
  float r_sum_smooth_topd = r_good_smooth_topd+r_bad_smooth_topd+r_invalid_smooth_topd;
  

  //store the results
  //common header for both eyes
  Data *element = *(list_data.begin());
  std::ostringstream commonstream;
  commonstream << 
    element->getSubjectID() << QSEP <<
    _bilder_name << "." << _bilder_ext << QSEP <<
    _subject.getDominantEye(element->getSubjectID()) << QSEP;
  //left raw
  std::ostringstream l_streamraw;
  l_streamraw << commonstream.str() <<
    "none"             << QSEP <<
    "left"             << QSEP <<
    lines_total_raw    << QSEP <<
    etbutler::float2str(percent_total_raw,2)  << QSEP <<
    etbutler::float2str(l_good_raw,2)         << QSEP <<
    etbutler::float2str(l_bad_raw,2)          << QSEP <<
    etbutler::float2str(l_invalid_raw,2)      << QSEP <<
    etbutler::float2str(l_sum_raw,0)          << QSEP <<
    etbutler::float2str(l_good_raw_topd,2)    << QSEP <<
    etbutler::float2str(l_bad_raw_topd,2)     << QSEP <<
    etbutler::float2str(l_invalid_raw_topd,2) << QSEP <<
    etbutler::float2str(l_sum_raw_topd,0);
  list_quality.push_back(l_streamraw.str());
  //right raw
  std::ostringstream r_streamraw;
  r_streamraw << commonstream.str() <<
    "none"             << QSEP <<
    "right"            << QSEP <<
    lines_total_raw    << QSEP <<
    etbutler::float2str(percent_total_raw,2)  << QSEP <<
    etbutler::float2str(r_good_raw,2)         << QSEP <<
    etbutler::float2str(r_bad_raw,2)          << QSEP <<
    etbutler::float2str(r_invalid_raw,2)      << QSEP <<
    etbutler::float2str(r_sum_raw,0)          << QSEP <<
    etbutler::float2str(r_good_raw_topd,2)    << QSEP <<
    etbutler::float2str(r_bad_raw_topd,2)     << QSEP <<
    etbutler::float2str(r_invalid_raw_topd,2) << QSEP <<
    etbutler::float2str(r_sum_raw_topd,0);
  list_quality.push_back(r_streamraw.str());
  //left pd
  std::ostringstream l_streampd;
  l_streampd << commonstream.str() <<
    "face detected"   << QSEP <<
    "left"            << QSEP <<
    lines_total_pd    << QSEP <<
    etbutler::float2str(percent_total_pd,2)  << QSEP <<
    etbutler::float2str(l_good_pd,2)         << QSEP <<
    etbutler::float2str(l_bad_pd,2)          << QSEP <<
    etbutler::float2str(l_invalid_pd,2)      << QSEP <<
    etbutler::float2str(l_sum_pd,0)          << QSEP <<
    etbutler::float2str(l_good_pd_topd,2)    << QSEP <<
    etbutler::float2str(l_bad_pd_topd,2)     << QSEP <<
    etbutler::float2str(l_invalid_pd_topd,2) << QSEP <<
    etbutler::float2str(l_sum_pd_topd,0);
  list_quality.push_back(l_streampd.str());
  //right pd
  std::ostringstream r_streampd;
  r_streampd << commonstream.str() <<
    "face detected"   << QSEP <<
    "right"           << QSEP <<
    lines_total_pd    << QSEP <<
    etbutler::float2str(percent_total_pd,2)  << QSEP <<
    etbutler::float2str(r_good_pd,2)         << QSEP <<
    etbutler::float2str(r_bad_pd,2)          << QSEP <<
    etbutler::float2str(r_invalid_pd,2)      << QSEP <<
    etbutler::float2str(r_sum_pd,0)          << QSEP <<
    etbutler::float2str(r_good_pd_topd,2)    << QSEP <<
    etbutler::float2str(r_bad_pd_topd,2)     << QSEP <<
    etbutler::float2str(r_invalid_pd_topd,2) << QSEP <<
    etbutler::float2str(r_sum_pd_topd,0);
  list_quality.push_back(r_streampd.str());
  //left smooth
  std::ostringstream l_streamsmooth;
  l_streamsmooth << commonstream.str() <<
    "smooth"              << QSEP <<
    "left"                << QSEP <<
    lines_total_smooth    << QSEP <<
    etbutler::float2str(percent_total_smooth,2)  << QSEP <<
    etbutler::float2str(l_good_smooth,2)         << QSEP <<
    etbutler::float2str(l_bad_smooth,2)          << QSEP <<
    etbutler::float2str(l_invalid_smooth,2)      << QSEP <<
    etbutler::float2str(l_sum_smooth,0)          << QSEP <<
    etbutler::float2str(l_good_smooth_topd,2)    << QSEP <<
    etbutler::float2str(l_bad_smooth_topd,2)     << QSEP <<
    etbutler::float2str(l_invalid_smooth_topd,2) << QSEP <<
    etbutler::float2str(l_sum_smooth_topd,0);
  list_quality.push_back(l_streamsmooth.str());
  //right smooth
  std::ostringstream r_streamsmooth;
  r_streamsmooth << commonstream.str() <<
    "smooth"              << QSEP <<
    "right"               << QSEP <<
    lines_total_smooth    << QSEP <<
    etbutler::float2str(percent_total_smooth,2)  << QSEP <<
    etbutler::float2str(r_good_smooth,2)         << QSEP <<
    etbutler::float2str(r_bad_smooth,2)          << QSEP <<
    etbutler::float2str(r_invalid_smooth,2)      << QSEP <<
    etbutler::float2str(r_sum_smooth,0)          << QSEP <<
    etbutler::float2str(r_good_smooth_topd,2)    << QSEP <<
    etbutler::float2str(r_bad_smooth_topd,2)     << QSEP <<
    etbutler::float2str(r_invalid_smooth_topd,2) << QSEP <<
    etbutler::float2str(r_sum_smooth_topd,0);
  list_quality.push_back(r_streamsmooth.str());

  return true;
}


bool IDMT::writeQualityHeader (string output_path, string file_prefix){
  _log->writeDebug("IDMT::writeQualityHeader (string output_path, string file_prefix)");
  ofstream qualityFile;

  _qualityFile_path = output_path + FILE_SLASH + file_prefix + "_quality.csv";

  qualityFile.open(_qualityFile_path);
  if( qualityFile.is_open() ){
    //write header
    qualityFile << "subjectID"                                 << QSEP;
    qualityFile << "media"                                     << QSEP;
    qualityFile << "dominant"                                  << QSEP;
    qualityFile << "quality"                                   << QSEP;
    qualityFile << "eye"                                       << QSEP;
    qualityFile << "#lines_total"                              << QSEP;
    qualityFile << "PersonDetected"                            << QSEP;
    qualityFile << "to total: 0 < vdiff < 20 (good)"           << QSEP;
    qualityFile << "to total: vdiff > 20 (bad)"                << QSEP;
    qualityFile << "to total: vdiff < 0 (invalid)"             << QSEP;
    qualityFile << "to total: sum % vdiff"                     << QSEP;
    qualityFile << "to person detected: 0 < vdiff < 20 (good)" << QSEP;
    qualityFile << "to person detected: vdiff > 20 (bad)"      << QSEP;
    qualityFile << "to person detected: vdiff < 0 (invalid)"   << QSEP;
    qualityFile << "to person detected: sum % vdiff"           << endl;

    qualityFile.close();
    return true;
  }else{
    _log->writeError("Can create quality output file: " + _qualityFile_path);
    return false;
  }
}



bool IDMT::writeQualityOutput (list<string> &list_quality){
  _log->writeDebug("bool IDMT::writeQualityOutput (list<string> &list_quality)");
  ofstream qualityFile;

  if( _qualityFile_path == "" ){
    _log->writeError("Quality file does not exist, first create the Quality File: " + _qualityFile_path);
    return false;
  }

  qualityFile.open(_qualityFile_path, std::ios::app); //dont overwrite, append to the file
  if( qualityFile.is_open() ){
    //write body
    list<string>::iterator itr;
    for(itr = list_quality.begin(); itr != list_quality.end(); itr++ ){
      qualityFile << *itr << endl;
    }
    qualityFile.close();
    return true;
  }else{
    _log->writeError("Can open quality output file: " + _qualityFile_path);
    return false;
  }
}
