#include "LogFileWriter.hpp"
#include "common.hpp"
#include "SMIRED5.hpp"
#include "SMIHED.hpp"
#include "IDMT.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#define SMIRED_PLUGIN "SMIRED"
#define SMIHED_PLUGIN "SMIHED"
#define IDMT_PLUGIN "IDMT"
LogFileWriter logfile;


static void show_usage( string name ) {
  cerr << "Usage: " << name << " <options> " << endl
       << "Options:" << endl
       << "\t-h,--help\t\tShow this help message" << endl
       << "\t-p,--plugin PLUGIN\tSpecify the plugin name. Available plugins are:" << endl
       << "\t\t- "  << SMIRED_PLUGIN << endl
       << "\t\t- "  << SMIHED_PLUGIN << endl
       << "\t\t- "  << IDMT_PLUGIN << endl
       << "For " << SMIRED_PLUGIN << " you also have to specify:" << endl
       << "\t-f,--files FILES\tSpecify the files to load separated by \";\"" << endl
       << "\t-o,--output OUTPUT\tSpecify the output folder path" << endl
       << "For " << SMIRED_PLUGIN << " you also can specify (optional):" << endl
       << "\t-s,--subject SUBJECT\tSpecify the subject file path" << endl
       << "\t-i,--image IMAGE\tSpecify the image path" << endl
       << "\t-x,--prefix PREFIX\tSpecify the output quality file prefix" << endl
       << "\t-a,--available\t\tPrint only available pictures" << endl
       << "\t-q,--quality\t\tCheck quality" << endl
       << "For " << SMIHED_PLUGIN << " you also have to specify:" << endl
       << "\t-f,--files FILES\tSpecify the files to load separated by \";\"" << endl
       << "\t-o,--output OUTPUT\tSpecify the output folder path" << endl
       << "For " << SMIHED_PLUGIN << " you also can specify (optional):" << endl
       << "\t-s,--subject SUBJECT\tSpecify the subject file path" << endl
       << "\t-i,--image IMAGE\tSpecify the image path" << endl
       << "\t-x,--prefix PREFIX\tSpecify the output quality file prefix" << endl
       << "\t-u,--use_offset\t\tUse offset in image size" << endl
       << "\t-q,--quality\t\tCheck quality" << endl
       << "For " << IDMT_PLUGIN << " you also have to specify:" << endl
       << "\t-f,--files FILES\tSpecify the files to load separated by \";\"" << endl
       << "\t-o,--output OUTPUT\tSpecify the output folder path" << endl
       << "For " << IDMT_PLUGIN << " you also can specify (optional):" << endl
       << "\t-s,--subject SUBJECT\tSpecify the subject file path" << endl
       << "\t-i,--image IMAGE\tSpecify the image path" << endl
       << "\t-z,--imagesize HEIGHTxWIDTH\tBilder size in milimiters. Ex: 810x1140" << endl
       << "\t-x,--prefix PREFIX\tSpecify the output quality file prefix" << endl
       << "\t-q,--quality\t\tCheck quality" << endl
       << "\t-d,--pdetected\tSIZE\tNumber of detected persons to validate. Ex: 2" << endl
       << "\t-w,--window\tWLENGHTxPMIN\tWindow for smoothing algorithm. Ex: 5x3" << endl
       << "\t-c,--combi\tCOMBI_OPTION\t. Valid options are: 1..16" << endl
       << "\t-r,--bild_distance\tXxY\tDistance between the gazetracker and the bild(in mm). Ex: -310x460" << endl
       << "\t-ru,--user_distance\tDISTANCE\tDistance between the user and the bild(in mm). Ex: 220" << endl;
}


static int processStringOption(int argc, int i, char* argv[], string &option, string optName){
  if (i + 1 < argc) {
    option = argv[++i];
    logfile.writeDebug(optName + ": " + option );
  } else {
    cerr << optName + "option requires one argument" << endl;
    logfile.writeError(optName + "option requires one argument");
    return 1;
  }
  return 0;
}


static int processXOption(int argc, int i, char* argv[], vector<string> &options, string optName){
   if (i + 1 < argc) {
    stringstream ss(argv[++i]);
    string item;
    while (getline(ss, item, 'x')) {
        options.push_back(item);
    }
    for(uint i=0; i<options.size(); i++){
      logfile.writeDebug(optName + ": " + options[i] );
    }
  } else {
    cerr << optName + "option requires one argument" << endl;
    logfile.writeError(optName + "option requires one argument");
    return 1;
  }
  return 0;
}


static int processSMIRED5(const string &subjectIndexPath, bool printOnlyAvailablePictures, const string &imagePath, const vector<string> &fileList, bool quality, const string &outputPath, const string &qualityPrefix){
  logfile.writeDebug("SMIRED plugin selected");
  SMIRED5 plugin(&logfile);

  if( subjectIndexPath != "" ) {
    if( ! plugin.loadSubject(subjectIndexPath) ){
      cerr << "Error loading Subject file" << endl;
      logfile.writeError("Loading Subject file");
      return 1;
    }
  }

  //Set Bilder info
  plugin.setPrintPics(printOnlyAvailablePictures);
  plugin.setBilderPath(imagePath);

  //create quality output
  if( quality ){
    if( !plugin.writeQualityHeader(outputPath, qualityPrefix ) ){
      cerr << "Error creating quality output" << endl;
      logfile.writeError("Creating quality output");
    }
  }

  vector<string> fileError;

  cout << " - 0%"<< flush;
  for(unsigned int i=0; i<fileList.size(); i++ ){
    list<Data*> list_data;
    list<string> list_quality;
    logfile.writeDebug("Processing file: "  + fileList[i]);

    //parse file
    streampos line_num_stop = LINE_NUM_STOP_INI;
    if( !plugin.parseDataFile(fileList[i], list_data, &line_num_stop) ){
      cerr << endl << "Error Parsing file: " << fileList[i] << endl;
      logfile.writeError("Parsing file");
      fileError.push_back(fileList[i] + ": Parsing file" );
      list_data.remove_if ( Data::deleteAll );
      continue;
    }

    //write data output
    vector<string> file_list_error;
    if( !plugin.writeDataOutput(outputPath, list_data, *plugin.getDataExtra(), file_list_error) ){
      cerr << endl << "Error writing output" << endl;
      logfile.writeError("Writing output");
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
    }

    if( !file_list_error.empty() ){
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
    }

    if( line_num_stop != LINE_NUM_STOP_INI ){
      //save the rest of the input file not processed
      ifstream finput(fileList[i]);
      string outname_rest = outputPath + FILE_SLASH + etbutler::extractFileNameFromPath(fileList[i]) + ".rest";
      ofstream frest (outname_rest);
      if ( finput.good() && finput.good() ) {
        string line;
        finput.seekg(line_num_stop, ios::beg);
        //save the rest in the output file
        while( getline(finput, line) ){
          frest << line << endl;
        }
        frest.close();
        finput.close();
        logfile.writeDebug("Generated fullWebsite output: " + outname_rest);
      }else{
        logfile.writeError("Writing fullWebsite output to a file: " + outname_rest);
        fileError.push_back(fileList[i] + ": Writing fullWebsite output to a file");
      }
    }


    if(quality){
      //calculate quality
      if( !plugin.calculateQuality(list_data, list_quality) ){
        cerr << endl << "Error calculating Quality" << endl;
        logfile.writeError("Calculating Quality");
        fileError.push_back(fileList[i] + ": Calculating Quality");
      }else{
        //write quality output
        if( !plugin.writeQualityOutput(list_quality) ){
          cerr << endl << "Error writing quality output" << endl;
          logfile.writeError("Writing quality output");
          fileError.push_back(fileList[i] + ": Writing quality output");
        }
      }
    }
   
    //deallocate memory of the list
    list_data.remove_if ( Data::deleteAll );
    cout << " - "<< ((i+1)*100/fileList.size()) << "%"<< flush;
  }

  //write fileError to the output
  if( !fileError.empty() ){
    string outputerrorfile_path = outputPath + "errors.txt";
    ofstream outputerrorfile;
      outputerrorfile.open(outputerrorfile_path);
      if( outputerrorfile.is_open() ){
        outputerrorfile << "Files not processed: " << fileError.size() << endl;
        for(size_t idx_error = 0; idx_error < fileError.size(); idx_error++ ){
          outputerrorfile << fileError[idx_error] << endl;
        }
        logfile.writeDebug("Output Error file generated: " + outputerrorfile_path);
        outputerrorfile.close();
      }else{
        cerr << endl << "Error writing Error output" << endl;
        logfile.writeError("Writing Error output");
      }
  }

  logfile.writeDebug("The file fragmentation is done!");

  return 0;
}


static int processSMIHED(const string &subjectIndexPath, bool use_offset, const string &imagePath, const vector<string> &fileList, bool quality, const string &outputPath, const string &qualityPrefix){
  logfile.writeDebug("SMIHED plugin selected");
  SMIHED plugin(&logfile);

  if( subjectIndexPath != "" ) {
    if( ! plugin.loadSubject(subjectIndexPath) ){
      cerr << "Error loading Subject file" << endl;
      logfile.writeError("Loading Subject file");
      return 1;
    }
  }

  //Set Bilder info
  plugin.setPrintPics(true);
  plugin.setUseOffset(use_offset);
  plugin.setBilderPath(imagePath);

  //create quality output
  if( quality ){
    if( !plugin.writeQualityHeader(outputPath, qualityPrefix ) ){
      cerr << "Error creating quality output" << endl;
      logfile.writeError("Creating quality output");
    }
  }

  vector<string> fileError;

  cout << " - 0%"<< flush;
  int num_total_files = 0;
  for(unsigned int i=0; i<fileList.size(); i++ ){
    list<Data*> list_data;
    list<string> list_quality;
    logfile.writeDebug("Processing file: "  + fileList[i]);

    //parse file
    if( !plugin.parseDataFile(fileList[i], list_data) ){
      cerr << endl << "Error Parsing file: " << fileList[i] << endl;
      logfile.writeError("Parsing file");
      fileError.push_back(fileList[i] + ": Parsing file" );
      list_data.remove_if ( Data::deleteAll );
      continue;
    }

    //write data output
    vector<string> file_list_error;
    if( !plugin.writeDataOutput(outputPath, list_data, *plugin.getDataExtra(), file_list_error) ){
      cerr << endl << "Error writing output" << endl;
      logfile.writeError("Writing output");
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
    }

    if( !file_list_error.empty() ){
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
    }

    if(quality){
      //calculate quality
      if( !plugin.calculateQuality(list_data, list_quality) ){
        cerr << endl << "Error calculating Quality" << endl;
        logfile.writeError("Calculating Quality");
        fileError.push_back(fileList[i] + ": Calculating Quality");
      }else{
        //write quality output
        if( !plugin.writeQualityOutput(list_quality) ){
          cerr << endl << "Error writing quality output" << endl;
          logfile.writeError("Writing quality output");
          fileError.push_back(fileList[i] + ": Writing quality output");
        }
      }
    }
   
    //deallocate memory of the list
    list_data.remove_if ( Data::deleteAll );
    cout << " - "<< ((i+1)*100/fileList.size()) << "%"<< flush;
  }

  //write fileError to the output
  if( !fileError.empty() ){
    string outputerrorfile_path = outputPath + "errors.txt";
    ofstream outputerrorfile;
      outputerrorfile.open(outputerrorfile_path);
      if( outputerrorfile.is_open() ){
        outputerrorfile << "Files not processed: " << fileError.size() << endl;
        for(size_t idx_error = 0; idx_error < fileError.size(); idx_error++ ){
          outputerrorfile << fileError[idx_error] << endl;
        }
        logfile.writeDebug("Output Error file generated: " + outputerrorfile_path);
        outputerrorfile.close();
      }else{
        cerr << endl << "Error writing Error output" << endl;
        logfile.writeError("Writing Error output");
      }
  }

  logfile.writeDebug("The file fragmentation is done!");

  return 0;
}


static int processIDMT(const string &subjectIndexPath, const string &imagePath, const vector<string> &imageSize, const vector<string> &fileList, bool quality, const string &outputPath, const string &qualityPrefix, const string &pdetected, const vector<string> &window, const string &combi, const vector<string> &bild_distance_xy, const string &user_distance){
  logfile.writeDebug("IDMT plugin selected");
  IDMT plugin(&logfile);

  if( subjectIndexPath != "" ) {
    if( ! plugin.loadSubject(subjectIndexPath) ){
      cerr << "Error loading Subject file" << endl;
      logfile.writeError("Loading Subject file");
      return 1;
    }
  }

  //Set Bilder info
  plugin.setPrintPics(true);
  plugin.setBilderPath(imagePath);
  if( imageSize.size() == 2 ){
    if( !plugin.setImageSize(stoul(imageSize[0]), stoul(imageSize[1])) ){;
      cerr << "Error setting image size option: \"" << imageSize[0] << "\"x\"" << imageSize[1] << "\"" << endl; 
      logfile.writeWarn("Error setting image size: \"" + imageSize[0] + "\"-\"" + imageSize[1] + "\"");
    }
  }else{
    logfile.writeWarn("Not using imageSize option: " + imageSize.size());
  }

  //Set combi option
  if( combi != "" && user_distance != "" && bild_distance_xy.size() == 2 ){
    if( !plugin.setCombi(true, stoul(combi), stod(bild_distance_xy[0]), stod(bild_distance_xy[1]), stod(user_distance)) ){
      cerr << "Error setting combi option: \"" << combi << "\"-\"" << bild_distance_xy[0] << "x" << bild_distance_xy[1] << "x"<< user_distance << "\"" << endl; 
      logfile.writeWarn("Error setting combi option: \"" + combi + "\"-\"" + bild_distance_xy[0] + "x" + bild_distance_xy[1] + "x" + user_distance  + "\"");
    }
  }else{
    logfile.writeDebug("Not using combi option: \"" + combi + "\"-\"" + etbutler::int2str(bild_distance_xy.size()) + "\"-\"" + user_distance + "\"");
  }

  //dont print picture name in output
  plugin.setBilderInOutname(false);

  //create quality output
  if( quality ){
    if( pdetected == "" || !plugin.setPdetected(true, stoul(pdetected)) ){
        cerr << "Not using pdetected option: " << pdetected << endl;
        logfile.writeWarn("Not using pdetected option: " + pdetected);
    }else if( window.size() != 2 || !plugin.setQualityWindow(true, stoul(window[0]), stoul(window[1]))){
      std::stringstream ss;
      for( size_t i = 0; i<window.size(); ++i){ if(i != 0) ss << ",";  ss << window[i]; }
      cerr << "Not using window option : " << ss.str() << endl;
      logfile.writeWarn("Not using window option : " + ss.str());
    }

    if( !plugin.writeQualityHeader(outputPath, qualityPrefix ) ){
      cerr << "Error creating quality output" << endl;
      logfile.writeError("Creating quality output");
    }

  }

  vector<string> fileError;

  cout << " - 0%"<< flush;
  for(unsigned int i=0; i<fileList.size(); i++ ){
    list<Data*> list_data;
    list<string> list_quality;
    logfile.writeDebug("Processing file: "  + fileList[i]);

    //parse file
    if( !plugin.parseDataFile(fileList[i], list_data) ){
      cerr << endl << "Error Parsing file: " << fileList[i] << endl;
      logfile.writeError("Parsing file");
      fileError.push_back(fileList[i] + ": Parsing file" );
      list_data.remove_if ( Data::deleteAll );
      continue;
    }

    //write data output
    vector<string> file_list_error;
    if( !plugin.writeDataOutput(outputPath, list_data, *plugin.getDataExtra(), file_list_error) ){
      cerr << endl << "Error writing output" << endl;
      logfile.writeError("Writing output");
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
    }

    if( !file_list_error.empty() ){
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
    }

    if(quality){
      //calculate quality
      if( !plugin.calculateQuality(list_data, list_quality) ){
        cerr << endl << "Error calculating Quality" << endl;
        logfile.writeError("Calculating Quality");
        fileError.push_back(fileList[i] + ": Calculating Quality");
      }else{
        //write quality output
        if( !plugin.writeQualityOutput(list_quality) ){
          cerr << endl << "Error writing quality output" << endl;
          logfile.writeError("Writing quality output");
          fileError.push_back(fileList[i] + ": Writing quality output");
        }
      }
    }
  
    //deallocate memory of the list
    list_data.remove_if ( Data::deleteAll );
    cout << " - "<< ((i+1)*100/fileList.size()) << "%"<< flush;
  }

  //write fileError to the output
  if( !fileError.empty() ){
    string outputerrorfile_path = outputPath + FILE_SLASH + "errors.txt";
    ofstream outputerrorfile;
      outputerrorfile.open(outputerrorfile_path);
      if( outputerrorfile.is_open() ){
        outputerrorfile << "Files not processed: " << fileError.size() << endl;
        for(size_t idx_error = 0; idx_error < fileError.size(); idx_error++ ){
          outputerrorfile << fileError[idx_error] << endl;
        }
        logfile.writeDebug("Output Error file generated: " + outputerrorfile_path);
        outputerrorfile.close();
      }else{
        cerr << endl << "Error writing Error output" << endl;
        logfile.writeError("Writing Error output");
      }
  }

  logfile.writeDebug("The file fragmentation is done!");

  return 0;
}




int main(int argc, char* argv[])
{
  //set Strings
  vector<string> fileList;
  string pluginName       = ""; 
  string subjectIndexPath = "";
  string imagePath        = "";
  string outputPath       = "";
  string qualityPrefix    = "";
  string pdetected        = "";
  string user_distance    = "";
  string combi            = "";
  //set vectors
  vector<string> window;
  vector<string> bild_distance_xy;
  vector<string> imageSize;
  //set bools
  bool printOnlyAvailablePictures = false; 
  bool quality                    = false;
  bool use_offset                 = false;

  logfile.createlogfile("./EyetraceButler.log");

  //write log file info
  logfile.write("CompanyName: University of Tuebingen ");
  logfile.write("FileDescription: Eyetrace Butler: Prepares SMI data for processing in Eyetrace");
  logfile.write("FileVersion: " + EYETRACEBUTLER_VERSION);
  logfile.write("InternalName: Eyetrace Butler commandline");
  logfile.write("LegalCopyright: Copyright (C) 2015"); 
  logfile.write("OriginalFilename: " + string(argv[0]));
  logfile.write("ProductName: Eyetrace Butler");
  logfile.write("ProductVersion: " + EYETRACEBUTLER_VERSION );
  logfile.write("Starting application...");

  setlocale(LC_NUMERIC, "C");

  // get the arguments
  if (argc < 2) {
    show_usage(argv[0]);
    return 1;
  }
  vector <string> sources;
  string destination;
  for (int i = 1; i < argc; ++i) {
    string arg = argv[i];
    if ((arg == "-h") || (arg == "--help")) {
      show_usage(argv[0]);
      return 0;
    }else if ((arg == "-p") || (arg == "--plugin")) {
      processStringOption(argc, i, argv, pluginName, "--plugin");
    }else if ((arg == "-f") || (arg == "--files")) {
      string files = "";
      if ( !processStringOption(argc, i, argv, files, "--files") ){
        etbutler::split(files, ';', fileList);
      }
    }else if ((arg == "-i") || (arg == "--image")) {
      processStringOption(argc, i, argv, imagePath, "--image");
    }else if ((arg == "-o") || (arg == "--output")) {
      processStringOption(argc, i, argv, outputPath, "--output");
    }else if ((arg == "-x") || (arg == "--prefix")) {
      processStringOption(argc, i, argv, qualityPrefix, "--prefix");
    }else if ((arg == "-s") || (arg == "--subject")) {
      processStringOption(argc, i, argv, subjectIndexPath, "--subject");
    }else if ((arg == "-a") || (arg == "--available")) {
      printOnlyAvailablePictures = true;
    }else if ((arg == "-u") || (arg == "--use_offset")) {
      use_offset = true;
    }else if ((arg == "-q") || (arg == "--quality")) {
      quality = true;
    }else if ((arg == "-z") || (arg == "--imagesize")) {
      processXOption(argc, i, argv, imageSize, "--imagesize");
    }else if ((arg == "-d") || (arg == "--pdetected")) {
      processStringOption(argc, i, argv, pdetected, "--pdetected");
    }else if ((arg == "-w") || (arg == "--window")) {
      processXOption(argc, i, argv, window, "--window");
    }else if ((arg == "-c") || (arg == "--combi")) {
      processStringOption(argc, i, argv, combi, "--combi");
    }else if ((arg == "-r") || (arg == "--bild_distance")) {
      processXOption(argc, i, argv, bild_distance_xy, "--bild_distance");
    }else if ((arg == "-ru") || (arg == "--user_distance")) {
      processStringOption(argc, i, argv, user_distance, "--user_distance");
    }
  }

  if( (pluginName == "") || (fileList.size() == 0) || (outputPath == "") ){
    cerr << "You must specify --plugin, --files and --output options" << endl;
    logfile.writeError("You must specify --plugin, --files and --output options");
    return 1;
  }

  if( pluginName == SMIRED_PLUGIN ){
    processSMIRED5(subjectIndexPath, printOnlyAvailablePictures, imagePath, fileList, quality, outputPath , qualityPrefix);
  }else if( pluginName == SMIHED_PLUGIN ){
    processSMIHED(subjectIndexPath, use_offset, imagePath, fileList, quality, outputPath , qualityPrefix);
  }else if( pluginName == IDMT_PLUGIN ){
    processIDMT(subjectIndexPath, imagePath, imageSize, fileList, quality, outputPath , qualityPrefix, pdetected, window, combi, bild_distance_xy, user_distance);
  }else{
    cerr << "Not valid plugin" + pluginName << endl;
    logfile.writeError("Not valid plugin: " + pluginName);
  }

  cout << endl;

  logfile.write("Application finish");

  return 0;
}
 
