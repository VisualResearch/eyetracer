#include "Data.hpp"
#include <iterator>
#include<cmath>
using namespace std;
// Constructors/Destructors
//  

Data::  Data (const string &file_path, const string &fileID, const string &subjectID, const string &bilder_name, const string &bilder_ext)
  : _file_path(file_path), _fileID(fileID), _subjectID(subjectID), _bilder_name(bilder_name), _bilder_ext(bilder_ext) {
  _list_data.clear();
}
//hhhhhhhhhh
void Data::replace_blink(){
	vector<double> open_time;
    list<Data_element>::iterator it1,/* it1Next,*/ it2 ,it3 /*,it4*/;
    it1 = _list_data.begin();           //it1 point to begin

//    it1Next = _list_data.begin();
//    std::advance(it1Next,1);            //it1Next point to the Next of it1
    list<Data_element>::iterator it1Next = std::next(_list_data.begin(),1);
    list<Data_element>::iterator it4 = std::next(_list_data.begin(),40);

//    it4 = _list_data.begin();
//    std::advance(it4,40);                //it4 point to the Next 80ms of it1, set time window 80ms

    while(it4!=_list_data.end()){
        if(stof(it1->left_h)==0 && stof(it1Next->left_h)!=0){  // begin to open eye
            it3=it1Next;
//            it2=it3;
//            std::advance(it2,14);            //it2 point to the Next 7ms of it3
            it2 = std::next(it3,14);
            while(it2!=it4){
                if(std::abs(stof(it3->left_h) - stof(it2->left_h)) < 2){  // calculate the differ with it3 and it2
                    open_time.push_back(stof(it3->timestamp));
					it3->left_h = "A";                          // find the endpoint of blink
					std::cout<<it3->timestamp<<std::endl;
                    break;
                }
                ++it3;
                ++it2;
            }
        }
        ++it1;
        ++it1Next;
        ++it4;
    }
}

//   //initalize
//   double epsilon = 2.00;
//   vector<double> open_time;
//   int co = 40;

//   if(_list_data.size()> co){
//   list<Data_element>::iterator it1, it2, it3, it4, it5, it6;
//   it1 = _list_data.begin();      //
//   it2 = _list_data.begin();
//   std::advance(it2,40);
//    //for(int i = 0;i < co;i++) ++it2;//cout<< it2.<<endl;   //
//   it4 = _list_data.begin();
//   std::advance(it4,35);
//    //for(int i = 0;i < co-5;i++) ++it4;   //
//   it6 = _list_data.begin();
//    //++it6;
//   std::advance(it6,1);

//   //contrast
//   while(it2!=_list_data.end()){
//     if(stof(it1->left_h)==0 && stof(it6->left_h)!=0){
//          double avg = 0;
//          for(it5 = it4;it5!=it2;++it5){
//            avg += stof(it5->left_h);
//          }
//            avg = avg /5;
//          for(it3 = it1;it3!=it2;++it3){
//            if(std::abs(avg - stof(it3->left_h)) < epsilon)
//            {
//                open_time.push_back(stof(it3->timestamp));
//                it3->left_h = "A";
//                break;
//            }
//           }
//      }
//       ++it1;
//       ++it2;
//       ++it4;
//       ++it6;
//   }
//  }
//}


Data::~Data () { }
//  
// Methods
//  

std::ostream& operator<< (std::ostream& out, Data const& data){
  const string       separator = "\t";  

  //write the header
  out << "time"        << separator;
  out << "left_x"      << separator;
  out << "left_y"      << separator;
  out << "left_w"      << separator;
  out << "left_h"      << separator;
  out << "left_valid"  << separator;
  out << "right_x"     << separator;
  out << "right_y"     << separator;
  out << "right_w"     << separator;
  out << "right_h"     << separator;
  out << "right_valid" << endl;

  //write the data
  list<Data_element>::const_iterator iter;
  iter = data._list_data.cbegin();
  long long int init_timestamp = stoll(iter->timestamp.c_str());
  
  for (; iter != data._list_data.cend(); ++iter ){
    long long int number = stoll(iter->timestamp.c_str());
    long long int diff = (number - init_timestamp) / 1000;
    //if( diff == 0 ){ cout << "InitT: " << init_timestamp << " Timestamp: " << number<< " Diff: " << diff << endl; }
    out << diff              << separator;
    out << etbutler::float2str(stof(iter->left_x),2)      << separator;
    out << etbutler::float2str(stof(iter->left_y),2)      << separator;
    out << etbutler::float2str(stof(iter->left_w),2)      << separator;
    out << etbutler::float2str(stof(iter->left_h),2)      << separator;
    out << iter->left_valid  << separator;
    out << etbutler::float2str(stof(iter->right_x),2)     << separator;
    out << etbutler::float2str(stof(iter->right_y),2)     << separator;
    out << etbutler::float2str(stof(iter->right_w),2)     << separator;
    out << etbutler::float2str(stof(iter->right_h),2)     << separator;
    out << iter->right_valid << endl;
  }
  return out;
}

void Data::add (string ts, string lx, string ly, string lw, string lh, bool lv, string rx, string ry, string rw, string rh, bool rv) {
  Data_element element;

	element.timestamp = ts;
	element.left_x = lx;
	element.left_y = ly;
	element.left_w = lw;
	element.left_h = lh;
	element.left_valid = lv;
	element.right_x = rx;
	element.right_y = ry;
	element.right_w = rw;
	element.right_h = rh;
	element.right_valid = rv;

  _list_data.push_back(element);
}
