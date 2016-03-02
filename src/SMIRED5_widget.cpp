#include "SMIRED5_widget.hpp"
#include "common.hpp"
#include "SMIRED5.hpp"
#include <qscrollarea.h>
#include <qprogressdialog.h>
#include <qmessagebox.h>
#include <qpaintengine.h>
#include <sstream>
#include <cmath>

SMIRED5_widget::SMIRED5_widget(QWidget *parent)
  : QWidget(parent)
{

#ifdef RELEASE_MODE
  setAccessibleName("SMIRED5");
#else
  setAccessibleName("SMIRED5_d");
#endif

	_ui.setupUi(this);
	_fileListModel = new QStringListModel();
  _fileListModel->setStringList(_fileList);
	_ui.listView->setModel(_fileListModel);
}

SMIRED5_widget::~SMIRED5_widget(){
  _log->writeDebug("function: SMIRED5_widget::~SMIRED5_widget()");
}


QWidget* SMIRED5_widget::getWidget(){ return this;}


QStringList SMIRED5_widget::openFile(QString filter){
  _log->writeDebug("function: QStringList SMIRED5_widget::openFile(QString filter)");
	QStringList result;
	QFileDialog qfd(getWidget());
  qfd.setFileMode(QFileDialog::ExistingFiles);
  qfd.setNameFilter(filter);
  QStringList fileNames;
  if (qfd.exec()){
	 	fileNames = qfd.selectedFiles();
		result = fileNames;
	}
	return result;
}

QString SMIRED5_widget::openFolder(){
  _log->writeDebug("function: QString SMIRED5_widget::openFolder()");
  QString result;
  QFileDialog qpd(this);
  qpd.setFileMode(QFileDialog::ExistingFile);
  qpd.setOption(QFileDialog::ShowDirsOnly);
  result = qpd.getExistingDirectory();
  return result;
}


void SMIRED5_widget::sltAddFile(){
  _log->writeDebug("function: void SMIRED5_widget::sltAddFile()");
  QStringList fileNames;

	fileNames = openFile("Text files *.txt"); 
  for (int i=0; i<fileNames.size(); i++)
    {
      QString name = fileNames.at(i);
      _fileList.append(name);
    }
  _fileListModel->setStringList(_fileList);
}

void SMIRED5_widget::sltRemoveFile(){
  _log->writeDebug("function: void SMIRED5_widget::sltRemoveFile()");

	int row = _ui.listView->currentIndex().row();
	if(row >= 0){
		QString name = _fileList.at(row);
		_fileList.removeAt(row);
		_fileListModel->setStringList(_fileList);
		_log->writeDebug(name.toStdString() + " removed");
	}
}

void SMIRED5_widget::sltRemoveAll(){
	_log->writeDebug("function: void SMIRED5_widget::sltRemoveAll()");

	while((!_fileList.isEmpty())){
    _fileList.removeAt(0);
    _fileListModel->setStringList(_fileList);
	}

	_log->writeDebug("All files removed");
}

void SMIRED5_widget::sltSetSubjectPath(){
  _log->writeDebug("function: void SMIRED5_widget::sltSetSubjectPath()");
	QStringList fileName;
	fileName = openFile("CSV files *.csv"); 
	if(fileName.size()>0){
		_ui.subjectCsv_pathEdit->setText(fileName.first());
		_log->writeDebug(fileName.first().toStdString() + " as subject information file selected.");
	}
}

void SMIRED5_widget::sltSetImageFolder(){
  _log->writeDebug("function: void SMIRED5_widget::sltSetImageFolder()");
	QString path = openFolder();
	_ui.imageFolder_pathEdit->setText(path);
	_log->writeDebug(path.toStdString() + " as image folder selected.");
}

void SMIRED5_widget::sltSelectOutputFolder(){
  _log->writeDebug("function: void SMIRED5_widget::sltSelectOutputFolder()");
	QString path = openFolder();
	_ui.outputFolder_pathEdit->setText(path);
	_log->writeDebug(path.toStdString() + " as output folder selected.");
}

void SMIRED5_widget::sltAbleSelection(bool select){
  _log->writeDebug("function: void SMIRED5_widget::sltAbleSelection(bool select)");
	_ui.quality_lineEdit->setEnabled(select);
	_ui.quality_label->setEnabled(select);
	_ui.showhistogram_checkBox->setEnabled(select);
	_ui.savehistogram_checkBox->setEnabled(select);
	if(select) _log->writeDebug("Quality check enabled.");
	else    	_log->writeDebug("Quality check disabled.");
}

void SMIRED5_widget::sltStartFragmentation(){
  _log->writeDebug("function: void SMIRED5_widget::sltStartFragmentation()");
	//set Strings
	QString subjectindexPath = _ui.subjectCsv_pathEdit->text();
	QString imagePath        = _ui.imageFolder_pathEdit->text();
	QString outputPath       = _ui.outputFolder_pathEdit->text();
	QString qualityPrefix    = _ui.quality_lineEdit->text();
	//set bools
	bool printOnlyAvailablePictures = _ui.convertOnlyAvaliablePictures_checkBox->checkState() && _ui.convertOnlyAvaliablePictures_checkBox->isEnabled(); 
	bool quality                    = _ui.checkQuality_checkBox->isChecked()  && _ui.checkQuality_checkBox->isEnabled();
  bool show_histogram             = _ui.showhistogram_checkBox->checkState() && _ui.showhistogram_checkBox->isEnabled();
  bool save_histogram             = _ui.savehistogram_checkBox->checkState() && _ui.savehistogram_checkBox->isEnabled();

  int shift_histo_window = 0; // shift each new histogram window position

  SMIRED5 plugin(_log);

  //Check Qtrings
	if( _fileList.length() <= 0 ) {
		QMessageBox::warning(0, "Error", "Please choose files for conversion!");
		_log->writeError("No files were selected, Error message: 'Please choose files for conversion!'");
    return;
	}
	if( outputPath == "" ) {
		QMessageBox::warning(0, "Error", "Please set output folder!");
		_log->writeError("No output folder selected, Error message: 'Please set output folder!'");
    return;
	}

  //read Subjects information
  if( subjectindexPath == "" ) {
    int ret = QMessageBox::question(this, 
                                    "No subjectindex specified", 
                                    "Do you want to continue without subjectindex?",
                                    QMessageBox::Yes|QMessageBox::No);
    if( ret == QMessageBox::No ) return;
  }else{
    if( ! plugin.loadSubject(subjectindexPath.toStdString()) ){
      QMessageBox::critical(this,"Error", "Error loading Subject file");
      _log->writeError("Error loading Subject file");
      return;
    }
  }

  //Set Bilder info
  plugin.setPrintPics(printOnlyAvailablePictures);
  plugin.setBilderPath(imagePath.toStdString());

  //create quality output
  if( quality ){
    if( !plugin.writeQualityHeader(outputPath.toStdString(), qualityPrefix.toStdString() ) ){
      QMessageBox::critical(this,"Error", "Error creating quality output");
      _log->writeError("Error creating quality output");
    }
  }

  //for writting error file
  vector<string> fileError;

  //read Data
  QProgressDialog progressDialog("Loading data, please wait.", "Hide", 0, _fileList.length(), this);
  progressDialog.setAutoClose(true);
  progressDialog.show();
  for(int i=0; i<_fileList.length(); i++ ){
    list<Data*> list_data;
    list<string> list_quality;
    progressDialog.setValue(i);
    progressDialog.repaint();
    _log->writeDebug("Processing file: "  + _fileList.at(i).toStdString());

    //parse file
    streampos line_num_stop = LINE_NUM_STOP_INI;
    if( !plugin.parseDataFile(_fileList.at(i).toStdString(), list_data, &line_num_stop) ){
      //QMessageBox::critical(this,"Error", "Parsing file: " + _fileList.at(i));
      _log->writeError("Parsing file");
      fileError.push_back(_fileList.at(i).toStdString() + ": Parsing file");
      list_data.remove_if ( Data::deleteAll );
      continue;
    }

//    //Replace Blinks
//     list<Data*>::iterator itr;
//     for(itr = list_data.begin(); itr != list_data.end(); ++itr){
//       Data* element = *itr;
//       element->replace_blink();
//     }

    //write data output
    vector<string> file_list_error;
    map<string,string> map_extra;
    map_extra.clear();
    if( !plugin.writeDataOutput(outputPath.toStdString(), list_data, map_extra, file_list_error) ){
      //QMessageBox::critical(this,"Error", "Writing output");
      _log->writeError("Writing output");
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
      list_data.remove_if ( Data::deleteAll );
      continue;
    }  

    if( !file_list_error.empty() ){
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
    }

    if( line_num_stop > LINE_NUM_STOP_INI ){
      //save the rest of the input file not processed
      ifstream finput(_fileList.at(i).toStdString());
      string outname_rest = outputPath.toStdString()
        + FILE_SLASH 
        + etbutler::extractFileNameFromPath(_fileList.at(i).toStdString()) 
        + ".rest";
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
        _log->writeDebug("Generated fullWebsite output: " + outname_rest);
      }else{
        _log->writeError("Writing fullWebsite output to a file: " + outname_rest);
        fileError.push_back(_fileList.at(i).toStdString() + ": Writing fullWebsite output to a file");
      }
    }

    if(quality){
      //calculate quality
      if( !plugin.calculateQuality(list_data, list_quality) ){
        //QMessageBox::critical(this,"Error", "Calculating Quality");
        _log->writeError("Calculating Quality");
        fileError.push_back(_fileList.at(i).toStdString() + ": Calculating Quality" );
      }else{
        //write quality output
        if( !plugin.writeQualityOutput(list_quality) ){
          //QMessageBox::critical(this,"Error", "Writing quality output");
          _log->writeError("Writing quality output");
          fileError.push_back(_fileList.at(i).toStdString() + ": Writing quality output" );
        }
      }
    }
   
    if( save_histogram || show_histogram ){
      //generate histogram
      generateHistogram(outputPath.toStdString(),
                        etbutler::extractFileNameFromPath(_fileList.at(i).toStdString()), 
                        qualityPrefix.toStdString(),
                        save_histogram, show_histogram, list_data, shift_histo_window);
    }

    //deallocate memory of the list
    list_data.remove_if ( Data::deleteAll );
  }

  progressDialog.close();

  //write fileError to the output
  writeFileError(fileError, outputPath);

  QMessageBox::information(0, "Information", "The file fragmentation is done!");
  _log->writeDebug("The file fragmentation is done!");
  
  string outputlogfile_path = outputPath.toStdString() + FILE_SLASH + "log.txt";
  _log->copylogfile(outputlogfile_path);

}
 
void SMIRED5_widget::sltRemoveBlink(){
  _log->writeDebug("function: void SMIRED5_widget::sltRemoveBlink()");
    //set Strings
    QString subjectindexPath = _ui.subjectCsv_pathEdit->text();
    QString imagePath        = _ui.imageFolder_pathEdit->text();
    QString outputPath       = _ui.outputFolder_pathEdit->text();
    QString qualityPrefix    = _ui.quality_lineEdit->text();
    //set bools
    bool printOnlyAvailablePictures = _ui.convertOnlyAvaliablePictures_checkBox->checkState() && _ui.convertOnlyAvaliablePictures_checkBox->isEnabled();
    bool quality                    = _ui.checkQuality_checkBox->isChecked()  && _ui.checkQuality_checkBox->isEnabled();
    bool show_histogram             = _ui.showhistogram_checkBox->checkState() && _ui.showhistogram_checkBox->isEnabled();
    bool save_histogram             = _ui.savehistogram_checkBox->checkState() && _ui.savehistogram_checkBox->isEnabled();

  int shift_histo_window = 0; // shift each new histogram window position

  SMIRED5 plugin(_log);

  //Check Qtrings
    if( _fileList.length() <= 0 ) {
        QMessageBox::warning(0, "Error", "Please choose files for conversion!");
        _log->writeError("No files were selected, Error message: 'Please choose files for conversion!'");
    return;
    }
    if( outputPath == "" ) {
        QMessageBox::warning(0, "Error", "Please set output folder!");
        _log->writeError("No output folder selected, Error message: 'Please set output folder!'");
    return;
    }

  //read Subjects information
  if( subjectindexPath == "" ) {
    int ret = QMessageBox::question(this,
                                    "No subjectindex specified",
                                    "Do you want to continue without subjectindex?",
                                    QMessageBox::Yes|QMessageBox::No);
    if( ret == QMessageBox::No ) return;
  }else{
    if( ! plugin.loadSubject(subjectindexPath.toStdString()) ){
      QMessageBox::critical(this,"Error", "Error loading Subject file");
      _log->writeError("Error loading Subject file");
      return;
    }
  }

  //Set Bilder info
  plugin.setPrintPics(printOnlyAvailablePictures);
  plugin.setBilderPath(imagePath.toStdString());

  //create quality output
  if( quality ){
    if( !plugin.writeQualityHeader(outputPath.toStdString(), qualityPrefix.toStdString() ) ){
      QMessageBox::critical(this,"Error", "Error creating quality output");
      _log->writeError("Error creating quality output");
    }
  }

  //for writting error file
  vector<string> fileError;

  //read Data
  QProgressDialog progressDialog("Loading data, please wait.", "Hide", 0, _fileList.length(), this);
  progressDialog.setAutoClose(true);
  progressDialog.show();
  for(int i=0; i<_fileList.length(); i++ ){
    list<Data*> list_data;
    list<string> list_quality;
    progressDialog.setValue(i);
    progressDialog.repaint();
    _log->writeDebug("Processing file: "  + _fileList.at(i).toStdString());

    //parse file
    streampos line_num_stop = LINE_NUM_STOP_INI;
    if( !plugin.parseDataFile(_fileList.at(i).toStdString(), list_data, &line_num_stop) ){
      //QMessageBox::critical(this,"Error", "Parsing file: " + _fileList.at(i));
      _log->writeError("Parsing file");
      fileError.push_back(_fileList.at(i).toStdString() + ": Parsing file");
      list_data.remove_if ( Data::deleteAll );
      continue;
    }

    //Replace Blinks
     list<Data*>::iterator itr;
     for(itr = list_data.begin(); itr != list_data.end(); ++itr){
       Data* element = *itr;
       element->replace_blink();
     }

    //write data output
    vector<string> file_list_error;
    map<string,string> map_extra;
    map_extra.clear();
    if( !plugin.writeDataOutput(outputPath.toStdString(), list_data, map_extra, file_list_error) ){
      //QMessageBox::critical(this,"Error", "Writing output");
      _log->writeError("Writing output");
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
      list_data.remove_if ( Data::deleteAll );
      continue;
    }

    if( !file_list_error.empty() ){
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
    }

    if( line_num_stop > LINE_NUM_STOP_INI ){
      //save the rest of the input file not processed
      ifstream finput(_fileList.at(i).toStdString());
      string outname_rest = outputPath.toStdString()// + "test"
        + FILE_SLASH
        + etbutler::extractFileNameFromPath(_fileList.at(i).toStdString())
        + ".rest";
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
        _log->writeDebug("Generated fullWebsite output: " + outname_rest);
      }else{
        _log->writeError("Writing fullWebsite output to a file: " + outname_rest);
        fileError.push_back(_fileList.at(i).toStdString() + ": Writing fullWebsite output to a file");
      }
    }

    if(quality){
      //calculate quality
      if( !plugin.calculateQuality(list_data, list_quality) ){
        //QMessageBox::critical(this,"Error", "Calculating Quality");
        _log->writeError("Calculating Quality");
        fileError.push_back(_fileList.at(i).toStdString() + ": Calculating Quality" );
      }else{
        //write quality output
        if( !plugin.writeQualityOutput(list_quality) ){
          //QMessageBox::critical(this,"Error", "Writing quality output");
          _log->writeError("Writing quality output");
          fileError.push_back(_fileList.at(i).toStdString() + ": Writing quality output" );
        }
      }
    }

    if( save_histogram || show_histogram ){
      //generate histogram
      generateHistogram(outputPath.toStdString(),
                        etbutler::extractFileNameFromPath(_fileList.at(i).toStdString()),
                        qualityPrefix.toStdString(),
                        save_histogram, show_histogram, list_data, shift_histo_window);
    }

    //deallocate memory of the list
    list_data.remove_if ( Data::deleteAll );
  }

  progressDialog.close();

  //write fileError to the output
  writeFileError(fileError, outputPath);

  QMessageBox::information(0, "Information", "The file fragmentation is done!");
  _log->writeDebug("The file fragmentation is done!");

  string outputlogfile_path = outputPath.toStdString() + FILE_SLASH + "log.txt";
  _log->copylogfile(outputlogfile_path);

}

Q_EXPORT_PLUGIN2(smired5_widget, SMIRED5_widget)
