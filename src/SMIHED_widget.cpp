#include "SMIHED_widget.hpp"
#include "common.hpp"
#include "SMIHED.hpp"
#include <qscrollarea.h>
#include <qprogressdialog.h>
#include <qmessagebox.h>
#include <qpaintengine.h>
#include <sstream>
#include <cmath>

SMIHED_widget::SMIHED_widget(QWidget *parent)
  : QWidget(parent)
{

#ifdef RELEASE_MODE
  setAccessibleName("SMIHED");
#else
  setAccessibleName("SMIHED_d");
#endif

	_ui.setupUi(this);
	_fileListModel = new QStringListModel();
  _fileListModel->setStringList(_fileList);
	_ui.listView->setModel(_fileListModel);
}

SMIHED_widget::~SMIHED_widget(){
  _log->writeDebug("function: SMIHED_widget::~SMIHED_widget()");
}


QWidget* SMIHED_widget::getWidget(){ return this;}


QStringList SMIHED_widget::openFile(QString filter){
  _log->writeDebug("function: QStringList SMIHED_widget::openFile(QString filter)");
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

QString SMIHED_widget::openFolder(){
  _log->writeDebug("function: QString SMIHED_widget::openFolder()");
  QString result;
  QFileDialog qpd(this);
  qpd.setFileMode(QFileDialog::ExistingFile);
  qpd.setOption(QFileDialog::ShowDirsOnly);
  result = qpd.getExistingDirectory();
  return result;
}


void SMIHED_widget::sltAddFile(){
  _log->writeDebug("function: void SMIHED_widget::sltAddFile()");
  QStringList fileNames;

	fileNames = openFile("Text files *.txt"); 
  for (int i=0; i<fileNames.size(); i++)
    {
      QString name = fileNames.at(i);
      _fileList.append(name);
    }
  _fileListModel->setStringList(_fileList);
}

void SMIHED_widget::sltRemoveFile(){
  _log->writeDebug("function: void SMIHED_widget::sltRemoveFile()");

	int row = _ui.listView->currentIndex().row();
	if(row >= 0){
		QString name = _fileList.at(row);
		_fileList.removeAt(row);
		_fileListModel->setStringList(_fileList);
		_log->writeDebug(name.toStdString() + " removed");
	}
}

void SMIHED_widget::sltRemoveAll(){
	_log->writeDebug("function: void SMIHED_widget::sltRemoveAll()");

	while((!_fileList.isEmpty())){
    _fileList.removeAt(0);
    _fileListModel->setStringList(_fileList);
	}

	_log->writeDebug("All files removed");
}

void SMIHED_widget::sltSetSubjectPath(){
  _log->writeDebug("function: void SMIHED_widget::sltSetSubjectPath()");
	QStringList fileName;
	fileName = openFile("CSV files *.csv"); 
	if(fileName.size()>0){
		_ui.subjectCsv_pathEdit->setText(fileName.first());
		_log->writeDebug(fileName.first().toStdString() + " as subject information file selected.");
	}
}

void SMIHED_widget::sltSetImageFolder(){
  _log->writeDebug("function: void SMIHED_widget::sltSetImageFolder()");
	QString path = openFolder();
	_ui.imageFolder_pathEdit->setText(path);
	_log->writeDebug(path.toStdString() + " as image folder selected.");
}

void SMIHED_widget::sltSelectOutputFolder(){
  _log->writeDebug("function: void SMIHED_widget::sltSelectOutputFolder()");
	QString path = openFolder();
	_ui.outputFolder_pathEdit->setText(path);
	_log->writeDebug(path.toStdString() + " as output folder selected.");
}

void SMIHED_widget::sltAbleSelection(bool select){
  _log->writeDebug("function: void SMIHED_widget::sltAbleSelection(bool select)");
	_ui.quality_lineEdit->setEnabled(select);
	_ui.quality_label->setEnabled(select);
	_ui.showhistogram_checkBox->setEnabled(select);
	_ui.savehistogram_checkBox->setEnabled(select);
	if(select) _log->writeDebug("Quality check enabled.");
	else    	_log->writeDebug("Quality check disabled.");
}

void SMIHED_widget::sltStartConversion(){
  _log->writeDebug("function: void SMIHED_widget::sltStartConversion()");
	//set Strings
	QString subjectindexPath = _ui.subjectCsv_pathEdit->text();
	QString imagePath        = _ui.imageFolder_pathEdit->text();
	QString outputPath       = _ui.outputFolder_pathEdit->text();
	QString qualityPrefix    = _ui.quality_lineEdit->text();
	//set bools
	bool use_offset     = _ui.use_offset->checkState() && _ui.checkQuality_checkBox->isEnabled();
	bool quality        = _ui.checkQuality_checkBox->isChecked() && _ui.checkQuality_checkBox->isEnabled();
  bool show_histogram = _ui.showhistogram_checkBox->checkState() && _ui.showhistogram_checkBox->isEnabled();
  bool save_histogram = _ui.savehistogram_checkBox->checkState() && _ui.savehistogram_checkBox->isEnabled();

  SMIHED plugin(_log);

  //Check Filelist
	if( _fileList.length() <= 0 ) {
		QMessageBox::warning(0, "Error", "Please choose files for conversion!");
		_log->writeError("No files were selected, Error message: 'Please choose files for conversion!'");
    return;
	}
  //Check output path
	if( outputPath == "" ) {
		QMessageBox::warning(0, "Error", "Please set output folder!");
		_log->writeWarn("No output folder selected, Error message: 'Please set output folder!'");
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
      QMessageBox::warning(this,"Error", "Error loading Subject file");
      _log->writeWarn("No subject set, Error message: 'Error loading Subject file': " + subjectindexPath.toStdString());
      return;
    }
  }

  //Set Bilder info
  plugin.setPrintPics(true); //print only if the picture is available
  plugin.setUseOffset(use_offset);
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
  QWidget     *neues = new QWidget();
  QVBoxLayout *lay   = new QVBoxLayout();
  if( !show_histogram ){ neues->setAttribute(Qt::WA_DontShowOnScreen,true); }
  neues->setLayout(lay);
  //_widgets_open.append(neues); 
  for(int i=0; i<_fileList.length(); i++ ){
    list<Data*> list_data;
    list<string> list_quality;
    progressDialog.setValue(i);
    progressDialog.repaint();
    _log->writeDebug("Processing file: "  + _fileList.at(i).toStdString());

    //parse file
    if( !plugin.parseDataFile(_fileList.at(i).toStdString(), list_data) ){
      //QMessageBox::critical(this,"Error", "Parsing file: " + _fileList.at(i));
      _log->writeError("Parsing file");
      fileError.push_back(_fileList.at(i).toStdString() + ": Parsing file");
      list_data.remove_if ( Data::deleteAll );
      continue;
    }

    //write data output
    vector<string> file_list_error;
    if( !plugin.writeDataOutput(outputPath.toStdString(), list_data, *plugin.getDataExtra(), file_list_error) ){
      //QMessageBox::critical(this,"Error", "Writing output");
      _log->writeError("Writing output");
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
      list_data.remove_if ( Data::deleteAll );
      continue;
    }  

    if( !file_list_error.empty() ){
      fileError.insert( fileError.end(), file_list_error.begin(), file_list_error.end() );
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
      generateHistogram(neues, lay, etbutler::extractFileNameFromPath(_fileList.at(i).toStdString()), list_data);
    }

    //deallocate memory of the list
    list_data.remove_if ( Data::deleteAll );
  }

  //save and close the histograms
  finishHistogram(neues, outputPath, qualityPrefix, save_histogram, show_histogram);

  progressDialog.close();

  //write fileError to the output
  writeFileError(fileError, outputPath);

  QMessageBox::information(0, "Information", "The file conversion is done!");
  _log->writeDebug("The file conversion is done!");

  string outputlogfile_path = outputPath.toStdString() + FILE_SLASH + "log.txt";
  _log->copylogfile(outputlogfile_path);
  
}
 

Q_EXPORT_PLUGIN2(smihed_widget, SMIHED_widget)
