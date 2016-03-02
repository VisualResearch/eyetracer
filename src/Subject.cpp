#include "Subject.hpp"
#include "common.hpp"

// Constructors/Destructors
//  

Subject::Subject (LogFileWriter *log)
  : _log(log)
{
  clear();
}


Subject::~Subject () {}

//  
// Methods
//  

std::ostream& operator<< (std::ostream& out, Subject const& subject){
  out << endl << "----- BEGIN SUBJECT" << endl;
  out << "  HEADER" << endl;
  out << "    ";
  for( unsigned int i=0; i<subject._header.size(); i++){
    out << subject._header[i] << " - ";
  }
  out << endl << "  BODY" << endl;
  list<vector<string>>::const_iterator iter;
  for (iter = subject._body.cbegin(); iter != subject._body.cend(); iter++){
    out << "    ";
    for( unsigned int i=0; i<(*iter).size(); i++){
      out << (*iter)[i] << " - " ;
    }
    out << endl;
  }
  out << "----- END SUBJECT" << endl;
  return out;
}

vector<string> Subject::getField (string field_name){
  _log->writeDebug("function: vector<string> Subject::getField (string field_name)");
  vector<string> temp;

  for( unsigned int i=0; i<_header.size(); i++){
    if( field_name == _header[i] ){
      list<vector<string>>::iterator itr;
      for(itr = _body.begin(); itr != _body.end(); ++itr){
        temp.push_back((*itr)[i]);
      }
    }
  }

  return temp;
}

vector<string> Subject::getSubject (string subjectID){
  _log->writeDebug("function: vector<string> Subject::getSubject (string subjectID)");
  list<vector<string>>::iterator itr;
  vector<string> temp;

  for(itr = _body.begin(); itr != _body.end(); ++itr){
    if( (*itr).size() > 0 && etbutler::compareCaseInsensitive( (*itr)[0], subjectID ) ){
      return (*itr);
    }
  }

  return temp;
}

string Subject::getDominantEye (string subjectID){
  _log->writeDebug("function: vector<string> Subject::getDominant (string subjectID)");
  list<vector<string>>::iterator itr_body;
  unsigned int dominant_field_pos = 0;
  string out = "";

  //check if dominant subject exists
  for( dominant_field_pos = 0; dominant_field_pos < _header.size(); dominant_field_pos++){
    if( _header[dominant_field_pos] == "dominant" ){
      for(itr_body = _body.begin(); itr_body != _body.end(); ++itr_body){
        if( (*itr_body).size() > 0 && (*itr_body)[0] == subjectID ){
          //The subject exists.
          string dom = (*itr_body)[dominant_field_pos];
          if( dom == "no ind." ) out = "empty";
          else if( dom == "right" || dom == "left" || dom == "both" ) out = dom;
          return out;
        }
      }
    }
  }

  return out;
}


void Subject::clear ()
{
  _log->writeDebug("function: void Subject::clear ()");
  _header.clear();
  _num_subjects = 0;
  _body.clear();
}

