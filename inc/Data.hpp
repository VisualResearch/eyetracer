
#ifndef DATA_H
#define DATA_H

#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include "common.hpp"


using namespace std;


typedef struct{
  string timestamp;
  string left_x;
  string left_y;
  string left_w;
  string left_h;
  bool   left_valid;
  string right_x;
  string right_y;
  string right_w;
  string right_h;
  bool   right_valid;
}  Data_element;

/**
 * class Data
 * : public QObject
 */

class Data{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Data (const string &file_path, const string &fileID, const string &subjectID, const string &bilder_name, const string &bilder_ext);

  /**
   * Empty Destructor
   */
  ~Data ();
void replace_blink();

  /**
   * @param  ts
   * @param  lx
   * @param  ly
   * @param  lw
   * @param  lh
   * @param  rx
   * @param  ry
   * @param  rw
   * @param  rh
   */
  inline void add (string ts, string lx, string ly, string lw, string lh, string rx, string ry, string rw, string rh) {
    add(ts, lx, ly, lw, lh, checkValidity(lx, ly), rx, ry, rw, rh, checkValidity(rx, ry) );
  }

  inline int last_index(){
    return _list_data.size() - 1;
  } 


  void add (string ts, string lx, string ly, string lw, string lh, bool lv, string rx, string ry, string rw, string rh, bool rv);

  bool cutoff(int first_valid_pos, int last_valid_pos){
    int last_pos   = _list_data.size() - 1;
    last_valid_pos = last_valid_pos + 1;

    if ( first_valid_pos >= 0               && first_valid_pos <= last_pos && 
         last_valid_pos  >= first_valid_pos && last_valid_pos  <= last_pos ){
      std::list<Data_element>::iterator it_first, it_last;
      it_first = _list_data.begin();
      it_last  = _list_data.begin();
      advance(it_first,first_valid_pos);
      advance(it_last,last_valid_pos);
      //remove firt elements
      _list_data.erase(_list_data.begin(),it_first);
      //remove last elements
      _list_data.erase(it_last,_list_data.end());
      return true;
    }
    
    return false;
  }

  friend std::ostream& operator<< (std::ostream& out, Data const& data);

  inline list<Data_element>* getList()       { return &_list_data;                                     }
  inline string              getFilePath()   { return _file_path;                                      }
  inline string              getFileName()   { return etbutler::extractFileNameFromPath(_file_path);   }
  inline string              getFileFolder() { return etbutler::extractFileFolderFromPath(_file_path); }
  inline string              getSubjectID()  { return _subjectID;                                      }
  inline string              getBilderName() { return _bilder_name;                                    }
  inline string              getBilderExt()  { return _bilder_ext;                                     } 
  inline string              getFileID()     { return _fileID;                                         }

  inline static bool         deleteAll( Data* data ) { delete data; return true; }

private:

  string             _file_path;
  string             _fileID;
  string             _subjectID;
  string             _bilder_name;
  string             _bilder_ext;
  list<Data_element> _list_data;


private:

  /**
   * @return int
   * @param  x
   * @param  y
   */
  static inline bool checkValidity (string x, string y){
    std::stringstream x_val(x);
    std::stringstream y_val(y);
    double xdo, ydo;
    x_val >> xdo;
    y_val >> ydo;
    if(ydo>0 && xdo>0){ return 1; }else{ return 0; }
  }

};

#endif // DATA_H
