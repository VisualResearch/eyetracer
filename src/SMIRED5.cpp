#include "common.hpp"
#include "SMIRED5.hpp"
#include <iomanip>
#include <sstream>
#include <algorithm>

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

SMIRED5::SMIRED5 (LogFileWriter *log) 
  : Quality(log), Plugin(log) , _log(log)
{
  _pupils = false;
}

SMIRED5::~SMIRED5 () { }


//  
// Methods
//  


bool SMIRED5::parseDataFile (string file_path, list<Data*> &list_data, streampos *line_num_stop){
  _log->writeDebug("function: bool SMIRED5::parseDataFile (string file_path, list<Data*> &list_data)");
  const regex reg_comment("^## ([^:]+):?\t?([^\n\\r]*).*");
  const regex reg_message("^# Message:([\\s\\w\\-]+)\\.([^\n\\r]*).*");

  streampos afterHeaderPos   = 0; //store line position after heading to start reading data 
  streampos initialHeaderPos = 0;

  //data common to all outputs
  bool    found_header = false;
  Data   *data      = NULL;
  int     counter   = 0;
  string  subjectID = "";
  const unsigned int pos_time  = 0;
  unsigned int pos_lporx = 0;
  unsigned int pos_lpory = 0;
  unsigned int pos_ldiax = 0;
  unsigned int pos_ldiay = 0;
  unsigned int pos_rporx = 0; 
  unsigned int pos_rpory = 0;
  unsigned int pos_rdiax = 0;
  unsigned int pos_rdiay = 0;

  ifstream dataFile;
  dataFile.open (file_path, ios::in );
  if (dataFile.is_open()) {
    string  line;
    list<vector<string>> all_lines;

    //get the header
    while ( getline (dataFile,line) && !found_header ) {
      match_results<std::string::const_iterator> what;
      if( regex_match(line, what, reg_comment) ){ 
        //is a commented line (##)
        if( what.size() > 1 && what[1].str() == "Subject" ){ 
          subjectID = etbutler::trimming(what[2].str());
        }
        // for( unsigned int i = 0; i< what.size(); i++ ) {
        //   _log->writeDebug(" content" + to_string(i) + "= "+ what[i].str() );
        // }
      }else{
        //is not a comment, so separate by tab
        vector<string> line_separate;
        etbutler::split(line, '\t', line_separate);
        if( line_separate.size() > 1 ){
          if( line_separate[0] == "Time" ){
            // is the header (starts with "Time" word)
            for( unsigned int i = 1; i < line_separate.size(); i++){
              if( line_separate[i] == "L POR X [px]"){
                pos_lporx = i;
              }
              else if( line_separate[i] == "L POR Y [px]"){
                pos_lpory = i;
              }
              else if( line_separate[i] == "L Dia X [px]"){
                pos_ldiax = i;
                _pupils = true;
              }
              else if( line_separate[i] == "L Dia Y [px]"){
                pos_ldiay = i;
                _pupils = true;
              }
              else if( line_separate[i] == "R POR X [px]"){
                pos_rporx = i;
              }
              else if( line_separate[i] == "R POR Y [px]"){
                pos_rpory = i;
              }
              else if( line_separate[i] == "R Dia X [px]"){
                pos_rdiax = i;
                _pupils = true;
              }
              else if( line_separate[i] == "R Dia Y [px]"){
                pos_rdiay = i;
                _pupils = true;
              }
            }
            found_header = true;
          }
        }
      }
      afterHeaderPos = dataFile.tellg();
    }
  
    // get back to the position when data starts
    if( afterHeaderPos != initialHeaderPos) dataFile.seekg(afterHeaderPos);

    //get the data
    while ( getline (dataFile,line) ){
      vector<string> line_separate;
      etbutler::split(line, '\t', line_separate);
      if( line_separate[1] == "MSG" ){
        //is the message line, start to collect the data for a particular image
        match_results<std::string::const_iterator> what_msg;
        if( regex_match(line_separate[3], what_msg, reg_message) ){
          if( data != NULL ){
            //there is data to print, add to the list
            _log->writeDebug("Size: " + etbutler::uint2str(data->getList()->size()) );
            list_data.push_back(data);
            data = NULL;
          }

          // check if it is a web image name, then dont process 
          // the rest and save it in a file
          string msg = what_msg[1].str();
          size_t n_occ = std::count(msg.begin(), msg.end(), '-');
          if( n_occ >= 4 ){
            *line_num_stop = dataFile.tellg();
            break;
          }

          std::ostringstream stream;
          stream << setfill('0') << setw(3) << ++counter;
          data = new Data(file_path, stream.str(), subjectID, what_msg[1].str(), what_msg[2].str());
          _log->writeDebug("Processing Image Data: " + what_msg[1].str());
        }
      }else if( line_separate[1] == "SMP" && data != NULL ){
        // is data line
        string d_time  = line_separate[pos_time];
        string d_lx    = "0";    
        string d_ly    = "0";    
        string d_ldiax = "0";    
        string d_ldiay = "0";    
        string d_rx    = "0";    
        string d_ry    = "0";    
        string d_rdiax = "0";    
        string d_rdiay = "0";    

        if( pos_lporx>0     ) { d_lx    = line_separate[pos_lporx];     }
        if( pos_lpory>0     ) { d_ly    = line_separate[pos_lpory];     }
        if( pos_ldiax>0     ) { d_ldiax = line_separate[pos_ldiax];     }
        if( pos_ldiay>0     ) { d_ldiay = line_separate[pos_ldiay];     }
        if( pos_rporx>0     ) { d_rx    = line_separate[pos_rporx];     }
        if( pos_rpory>0     ) { d_ry    = line_separate[pos_rpory];     }
        if( pos_rdiax>0     ) { d_rdiax = line_separate[pos_rdiax];     }
        if( pos_rdiay>0     ) { d_rdiay = line_separate[pos_rdiay];     }
        data->add(d_time, d_lx, d_ly, d_ldiax, d_ldiay, d_rx, d_ry, d_rdiax, d_rdiay);
      }
    }

    //save chunk of data
    if( data != NULL ){ list_data.push_back(data); }

    dataFile.close();
    return true;
  }else{
    _log->writeWarn("Cannot open Data file:" + file_path);
    return false;
  }
}


bool SMIRED5::calculateQuality (list<Data*> &list_data, list<string> &list_quality){
  _log->writeDebug("function: bool SMIRED5::calculateQuality (list<Data*> &list_data, list<string> &list_quality)");

  list<Data*>::iterator itr;
  for(itr = list_data.begin(); itr != list_data.end(); itr++){
    Data *element = *itr;
    list<Data_element> *sublist_data = element->getList();
    list<Data_element>::iterator subitr;
    list<Data_element>::iterator subprev1 = sublist_data->end();
    list<Data_element>::iterator subprev2 = sublist_data->end();

    int totallines      = sublist_data->size();
    int lefttotalvalid  = 0;
    int leftvalid       = 0;
    list<int> leftoldsections, leftnewsections;
    int lefterrors      = 0;
    int lefttotalerrors = 0;
    int leftchangenext  = 0;
    int righttotalvalid = 0;
    int rightvalid      = 0;
    int righterrors     = 0;
    int righttotalerrors = 0;
    list<int> rightoldsections, rightnewsections;
    int rightchangenext = 0;

    _log->writeDebug("Calculating Quality for:" + element->getFileName() + " - " + element->getBilderName());
    for(subitr = sublist_data->begin(), subprev1 = sublist_data->end(), subprev2 = sublist_data->end();
        subitr != sublist_data->end();
        subprev2 = subprev1, subprev1 = subitr, subitr++){
      //left eye
      leftvalid       = subitr->left_valid;
      lefttotalvalid += leftvalid;
      if( !leftvalid ){
        //actual value is not valid
        lefterrors++;

        if( _pupils && subprev1 != sublist_data->end() && subprev2 != sublist_data->end()){
          //check if pupil height is decreasing
          if( stod(subitr->left_h) == 0 || 
              ( stod(subprev2->left_h) > stod(subprev1->left_h) && 
                stod(subprev1->left_h) > stod(subitr->left_h)     ) ){ 
            //change two previous values
            subprev1->left_valid = 0;
            subprev2->left_valid = 0;
            //anotate to change next two values
            //_log->writeDebug( "Annotate to Change NEXT 2 Left pupil Decreasing: " + subitr->timestamp );
            leftchangenext = 2;
          }
        }else{
          //change two previous values
          if( subprev1 != sublist_data->end() ){ subprev1->left_valid = 0; }
          if( subprev2 != sublist_data->end() ){ subprev2->left_valid = 0; }
          //anotate to change next two values
          //_log->writeDebug( "Annotate to Change NEXT 2 Left: " + subitr->timestamp );
          leftchangenext = 2;
        }
      }else{
        if( leftchangenext > 0 ){
          //previous value was not valid
          subitr->left_valid = 0;
          //_log->writeDebug( "Annotate to Changed: " + subitr->timestamp );
          leftchangenext--;
        }else{
          //add a new section
          leftoldsections.push_back(lefterrors);
          lefttotalerrors += lefterrors;
          lefterrors = 0;
        }
      }     

      
      //right eye
      rightvalid       = subitr->right_valid;
      righttotalvalid += rightvalid;
      if( !rightvalid ){
        //actual value is not valid
        righterrors++;
        
        if( _pupils && subprev1 != sublist_data->end() && subprev2 != sublist_data->end()){
          //check if pupil height is decreasing
          if( stod(subitr->right_h) == 0 || 
              ( stod(subprev2->right_h) > stod(subprev1->right_h) && 
                stod(subprev1->right_h) > stod(subitr->right_h)     ) ){ 
            //change two previous values
            subprev1->right_valid = 0;
            subprev2->right_valid = 0;
            //anotate to change next two values
            rightchangenext = 2;
          }
        }else{
          //change two previous values
          if( subprev1 != sublist_data->end() ){ subprev1->right_valid = 0; }
          if( subprev2 != sublist_data->end() ){ subprev2->right_valid = 0; }
          //anotate to change next two values
          rightchangenext = 2;
        }
      }else{
        if( rightchangenext > 0 ){
          //previous value was not valid
          subitr->right_valid = 0;
          rightchangenext--;
        }else{
          //add a new section
          rightoldsections.push_back(righterrors);
          righttotalerrors += righterrors;
          righterrors = 0;
        }
      }
    }

    //add last section if necessary
    if( lefterrors ){ 
      leftoldsections.push_back(lefterrors);
      lefttotalerrors += lefterrors;
    }
    //add last section if necessary
    if( righterrors ){ 
      rightoldsections.push_back(righterrors);
      righttotalerrors += righterrors;
    }


    //recount to compare
    int leftnewvalid = 0;
    int rightnewvalid = 0;
    lefterrors = 0;
    righterrors = 0;
    for(subitr = sublist_data->begin(); subitr != sublist_data->end(); ++subitr){
      //left eye
      leftnewvalid += subitr->left_valid;
      if( !subitr->left_valid ){ lefterrors++; }
      else{ 
        //add a new section
        leftnewsections.push_back(lefterrors);
        lefterrors = 0;
      }
      //right eye
      rightnewvalid += subitr->right_valid;
      if( !subitr->right_valid ){ righterrors++; }
      else{ 
        //add a new section
        rightnewsections.push_back(righterrors);
        righterrors = 0;
      }
    }
    //add last section if necessary
    if( lefterrors ){ leftnewsections.push_back(lefterrors); }
    if( righterrors ){ rightnewsections.push_back(righterrors); }


    //store the results
    //common header for both eyes
    std::ostringstream commonstream;
    commonstream << 
      element->getSubjectID() << QSEP <<
      element->getBilderName() << "." << element->getBilderExt() << QSEP <<
      element->getFileID() << QSEP <<
      _subject.getDominantEye(element->getSubjectID()) << QSEP;
    //left eye
    double leftpercentold = ((100.0f/(totallines*1.0f))*(lefttotalvalid*1.0f));
    double leftpercentnew = ((100.0f/(totallines*1.0f))*(leftnewvalid*1.0f));
    double leftmeanerrorold = etbutler::calculateAvg(leftoldsections);
    double leftmeanerrornew = etbutler::calculateAvg(leftnewsections);
    double lpo = (int)(leftpercentold*100+0.5)/100.0;
    double lpn = (int)(leftpercentnew*100+0.5)/100.0;
    double lmeo = (int)(leftmeanerrorold*100+0.5)/100.0;
    double lmen = (int)(leftmeanerrornew*100+0.5)/100.0;
    std::ostringstream leftstream;
    leftstream << commonstream.str() <<
      "left" << QSEP <<
      lpo << "%" << QSEP <<
      lpn << "%" << QSEP <<
      totallines << QSEP <<
      lefttotalvalid << QSEP <<
      leftnewvalid << QSEP <<
      lefttotalerrors << QSEP << 
      lmeo << QSEP << 
      lmen;
    list_quality.push_back(leftstream.str());
    //right eye
    double rightpercentold = ((100.0f/(totallines*1.0f))*(righttotalvalid*1.0f));
    double rightpercentnew = ((100.0f/(totallines*1.0f))*(rightnewvalid*1.0f));
    double rightmeanerrorold = etbutler::calculateAvg(rightoldsections);
    double rightmeanerrornew = etbutler::calculateAvg(rightnewsections);
    double rpo = (int)(rightpercentold*100+0.5)/100.0;
    double rpn = (int)(rightpercentnew*100+0.5)/100.0;
    double rmeo = (int)(rightmeanerrorold*100+0.5)/100.0;
    double rmen = (int)(rightmeanerrornew*100+0.5)/100.0;
    ostringstream rightstream;
    rightstream << commonstream.str() <<
      "right" << QSEP <<
      rpo << "%" << QSEP <<
      rpn << "%" << QSEP <<
      totallines << QSEP <<
      righttotalvalid << QSEP <<
      rightnewvalid << QSEP <<
      righttotalerrors << QSEP << 
      rmeo << QSEP << 
      rmen;
    list_quality.push_back(rightstream.str());
  }

  return true;
}


bool SMIRED5::writeQualityHeader (string output_path, string file_prefix){
  _log->writeDebug("bool SMIRED5::writeQualityHeader (string output_path, string file_prefix)");
  ofstream qualityFile;

  _qualityFile_path = output_path + FILE_SLASH + file_prefix + "_quality.csv";

  qualityFile.open(_qualityFile_path);
  if( qualityFile.is_open() ){
    //write header
    qualityFile << "subjectID"           << QSEP;
    qualityFile << "media"               << QSEP;
    qualityFile << "examination"         << QSEP;
    qualityFile << "dominant"            << QSEP;
    qualityFile << "eye"                 << QSEP;
    qualityFile << "quality_old"         << QSEP;
    qualityFile << "quality_new"         << QSEP;
    qualityFile << "lines_total"         << QSEP;
    qualityFile << "valid_lines_old"     << QSEP;
    qualityFile << "valid_lines_new"     << QSEP;
    qualityFile << "#errors"             << QSEP;
    qualityFile << "mean_error_size_old" << QSEP;
    qualityFile << "mean_error_size_new" << endl;

    qualityFile.close();
    return true;
  }else{
    _log->writeError("Can create quality output file: " + _qualityFile_path);
    return false;
  }
}


bool SMIRED5::writeQualityOutput (list<string> &list_quality){
  _log->writeDebug("bool SMIRED5::writeQualityOutput (list<string> &list_quality)");
  ofstream qualityFile;
  
  if( _qualityFile_path == "" ){
    _log->writeError("Quality file does not exist, first create the Quality File: " + _qualityFile_path);
    return false;
  }

  qualityFile.open(_qualityFile_path, std::ios::app);
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
