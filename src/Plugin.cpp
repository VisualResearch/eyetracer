#include "Plugin.hpp"
#include <regex>
#include <sstream>
using namespace std;

// Constructors/Destructors
//  

Plugin::Plugin (LogFileWriter *log)
  : _log(log), _subject(log)
{
  _input_data_files.clear();
  _bilder_path = "";
  _printOnlyAvailablePictures = false;
  _picture_name_in_outname = true;
  _map_extra.clear();
}


Plugin::~Plugin () {
  _map_extra.clear();
}

//  
// Methods
//  

bool Plugin::writeDataOutput (string output_path, list<Data*> &list_data, map<string,string> &map_extra, vector<string> &file_error){
  _log->writeDebug("function: bool Plugin::writeDataOutput (string output_path, list<Data*> &list_data, map<string,string> &map_extra)");
  
  list<Data*>::iterator itr;

  for(itr = list_data.begin(); itr != list_data.end(); ++itr){
    Data* element = *itr;

    //get Bilder Information
    string bilder_file_path = _bilder_path + FILE_SLASH + element->getBilderName() + "." + element->getBilderExt();
    ifstream bilder_file(bilder_file_path);

    //get output file name information
    string outputfile_path;
    string file_id = "";
    if( element->getFileID() != "" ) file_id = "_" + element->getFileID();

    if( _picture_name_in_outname ){
      outputfile_path = output_path + FILE_SLASH + element->getBilderName() + file_id + "_" + element->getFileName();
    }else{
      outputfile_path = output_path + FILE_SLASH + file_id + element->getFileName();
    }
    string outputdatafile_path = outputfile_path + ".data";
    string outputsetfile_path  = outputfile_path + ".set";


    //check if the image exists
    if ( ( bilder_file.good() && _printOnlyAvailablePictures ) 
         || !_printOnlyAvailablePictures ){

      //check if the size is right
      if( _printOnlyAvailablePictures && !checkBilderSize(bilder_file_path) ){
        _log->writeWarn("Bilder size excess maximum (" 
                        + etbutler::int2str(MAX_IMAGE_RES_WIDTH) + "x"
                        + etbutler::int2str(MAX_IMAGE_RES_HEIGHT)
                        + "): " + bilder_file_path);
        file_error.push_back(outputfile_path + ": Bilder size excess maximum");
      }else{
        //open data and set output file to write
        ofstream outputdatafile;
        ofstream outputsetfile;

        outputdatafile.open(outputdatafile_path);
        outputsetfile.open(outputsetfile_path);
        if( outputdatafile.is_open() && outputsetfile.is_open() ){
          //write ".data" file
          outputdatafile << "#" << getEyetrackerCode() << endl;
          outputdatafile << *element ;

          //write ".set" file
          outputsetfile << "[general]" << endl;
          outputsetfile << "Version=" << getPluginVersion() << endl;
          outputsetfile << endl;
          if( map_extra["general"] != "" ){ outputsetfile << map_extra["general"]  << endl; }
          outputsetfile << "[eyetracker]" << endl;
          outputsetfile << "company=" << getPluginCompany() << endl;
          outputsetfile << "model=" << getPluginModel() << endl;
          if( getPluginRate() != "" ){ outputsetfile << "samplingRate=" << getPluginRate() << endl; }
          outputsetfile << endl;
          if( map_extra["eyetracker"] != "" ){ outputsetfile << map_extra["eyetracker"]  << endl; }
          outputsetfile << "[files]" << endl;
          outputsetfile << "filepath=" << element->getFilePath() << endl;
          outputsetfile << "filename=" << element->getFileName() << endl;
          outputsetfile << "filefolder=" << element->getFileFolder() << endl;
          if( map_extra["files"] != "" ){ outputsetfile << map_extra["files"]  << endl; }
          outputsetfile << endl;
          outputsetfile << "[media]" << endl;
          if ( !(element->getFileID()).empty() )
            outputsetfile << "fileid=" << element->getFileID() << endl;
          outputsetfile << "picturename=" << element->getBilderName() << "." << element->getBilderExt() << endl;
          outputsetfile << "picturefolder=" << _bilder_path << endl;
          outputsetfile << "picturepath=" << _bilder_path << FILE_SLASH 
                        << element->getBilderName() << "." << element->getBilderExt() << endl;
          if( map_extra["media"] != "" ){ outputsetfile << map_extra["media"]  << endl; }
          outputsetfile << endl;
          outputsetfile << "[subject]" << endl;
          vector<string> subject_info = _subject.getSubject(element->getSubjectID());
          if( subject_info.size() > 0){
            //print subject info in the ".set" file
            vector<string> subject_header = _subject.get_header();
            if( subject_header.size() < subject_info.size() ){
              _log->writeWarn("Subject Header column number is smaller than body column number: " + element->getSubjectID());
            }else{
              for( unsigned int i=0; i<subject_info.size(); i++ ){
                outputsetfile << subject_header[i] << "=" << subject_info[i] << endl;
              }
            }
          }else{
            _log->writeWarn("Subject Info not found: " + element->getSubjectID());
          }
          if( map_extra["subject"] != "" ){ outputsetfile << map_extra["subject"]  << endl; }
          outputsetfile << endl;

          _log->writeDebug("Output file generated: " + outputfile_path);
          outputdatafile.close();
          outputsetfile.close();
        }else{
          _log->writeWarn("Can not create output file: " + outputfile_path);
          file_error.push_back(outputfile_path + ": Can not create output file");
        }
      }
    }else{
      if( _printOnlyAvailablePictures ){
        _log->writeWarn("Bilder not available and printOnlyAvailable: " + bilder_file_path);
        file_error.push_back(outputfile_path + ": Bilder not available and printOnlyAvailable");
      }else{
        _log->writeError("Bilder not available: " + bilder_file_path);
        file_error.push_back(outputfile_path + ": Bilder not available");
        return false;
      }
    }
  }

  return true;
}

bool Plugin::loadSubject (string file_path){
  _log->writeDebug("function: bool Plugin::loadSubject (string file_path)");
  ifstream subjectFile;
  _subject.clear();
  subjectFile.open (file_path, ios::in );
  if (subjectFile.is_open()) { 
    string line;
    list<vector<string>> all_lines;
    //get all the lines
    while ( getline (subjectFile,line) ){
      //split in ";"
      etbutler::trim(line);
      vector<string> line_separate;
      etbutler::split(line, ';', line_separate);
      all_lines.push_back(line_separate);
    }
    //add header and body to Subject object
    vector<string> header(all_lines.front());
    _subject.set_header(header);
    list<vector<string>> body(++all_lines.begin(), all_lines.end());
    _subject.set_body(body);
    //close file and return
    subjectFile.close();
    std::ostringstream ost;
    ost << _subject;
    _log->writeDebug( ost.str() );
    return true;
  }else{
    _log->writeWarn("Cannot open subject file:" + file_path);
    return false;
  }
}

bool Plugin::checkBilderSize (string bilder_path){
  //try to get image size
  int width, height;
  if( etbutler::getImageSize(bilder_path, width, height) ){
    if( width > MAX_IMAGE_RES_WIDTH || height > MAX_IMAGE_RES_HEIGHT )
      return false;
    else
      return true;
  }else{
    return false;
  }
}
