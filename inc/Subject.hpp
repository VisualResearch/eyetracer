
#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include <ostream>
#include <vector>
#include <list>
#include "LogFileWriter.hpp"

using namespace std;


/**
 * class Subject
 * 
 */

class Subject
{

public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Subject (LogFileWriter *log);

  /**
   * Empty Destructor
   */
  ~Subject ();

  /**
   * @return vector<string>
   * @param  field_name
   */
  vector<string> getField (string field_name);

  /**
   * @return vector<string>
   * @param  field_name
   */
  vector<string> getSubject (string subjectID);

  /**
   * @return string
   * @param  field_name
   */
  string getDominantEye (string subjectID);

  /**
   * 
   */
  void clear ();

private:

  // Private attributes
  //  

  vector<string> _header;
  unsigned short _num_subjects;
  list<vector<string>> _body;

  LogFileWriter *_log;

public:


  friend std::ostream& operator<< (std::ostream& out, Subject const& subject);

  /**
   * Set the value of _header
   * @param new_var the new value of _header
   */
  inline void set_header (vector<string> header)   {
    _header = header;
  }

  /**
   * Get the value of _header
   * @return the value of _header
   */
  inline vector<string> get_header ()   {
    return _header;
  }

  /**
   * Get the value of _num_subjects
   * @return the value of _num_subjects
   */
  inline unsigned short get_num_subjects ()   {
    return _num_subjects;
  }

  /**
   * Set the value of _body
   * @param new_var the new value of _body
   */
  inline void set_body (list<vector<string>> body)   {
    _body = body;
    _num_subjects = _body.size();
  }

  /**
   * Get the value of _body
   * @return the value of _body
   */
  inline list<vector<string>> get_body ()   {
    return _body;
  }

};

#endif // SUBJECT_H
