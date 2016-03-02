#include "IDMT_widget.hpp"
#include "common.hpp"
#include "IDMT.hpp"
#include <qscrollarea.h>
#include <qprogressdialog.h>
#include <qmessagebox.h>
#include <qpaintengine.h>
#include <sstream>
#include <cmath>

IDMT_widget::IDMT_widget(QWidget *parent)
  : QWidget(parent)
{

#ifdef RELEASE_MODE
  setAccessibleName("IDMT");
#else
  setAccessibleName("IDMT_d");
#endif

	_ui.setupUi(this);
	_fileListModel = new QStringListModel();
  _fileListModel->setStringList(_fileList);
	_ui.listView->setModel(_fileListModel);

}

IDMT_widget::~IDMT_widget(){
  _log->writeDebug("function: IDMT_widget::~IDMT_widget()");
}


QWidget* IDMT_widget::getWidget(){ return this;}


QStringList IDMT_widget::openFile(QString filter){
  _log->writeDebug("function: QStringList IDMT_widget::openFile(QString filter)");
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

QString IDMT_widget::openFolder(){
  _log->writeDebug("function: QString IDMT_widget::openFolder()");
  QString result;
  QFileDialog qpd(this);
  qpd.setFileMode(QFileDialog::ExistingFile);
  qpd.setOption(QFileDialog::ShowDirsOnly);
  result = qpd.getExistingDirectory();
  return result;
}


void IDMT_widget::sltAddFile(){
  _log->writeDebug("function: void IDMT_widget::sltAddFile()");
  QStringList fileNames;

	fileNames = openFile("Text files *.txt"); 
  for (int i=0; i<fileNames.size(); i++)
    {
      QString name = fileNames.at(i);
      _fileList.append(name);
    }
  _fileListModel->setStringList(_fileList);
}

void IDMT_widget::sltRemoveFile(){
  _log->writeDebug("function: void IDMT_widget::sltRemoveFile()");

	int row = _ui.listView->currentIndex().row();
	if(row >= 0){
		QString name = _fileList.at(row);
		_fileList.removeAt(row);
		_fileListModel->setStringList(_fileList);
		_log->writeDebug(name.toStdString() + " removed");
	}
}

void IDMT_widget::sltRemoveAll(){
	_log->writeDebug("function: void IDMT_widget::sltRemoveAll()");

	while((!_fileList.isEmpty())){
    _fileList.removeAt(0);
    _fileListModel->setStringList(_fileList);
	}

	_log->writeDebug("All files removed");
}

void IDMT_widget::sltSetSubjectPath(){
  _log->writeDebug("function: void IDMT_widget::sltSetSubjectPath()");
	QStringList fileName;
	fileName = openFile("CSV files *.csv"); 
	if(fileName.size()>0){
		_ui.subjectCsv_pathEdit->setText(fileName.first());
		_log->writeDebug(fileName.first().toStdString() + " as subject information file selected.");
	}
}

void IDMT_widget::sltSetImagePath(){
  _log->writeDebug("function: void IDMT_widget::sltSetImagePath()");
  QStringList pathList = openFile("Image files *.png *.jpg *.bmp *.gif *.tif");
  if(pathList.size() > 0) {
    _ui.image_pathEdit->setText(pathList.first());
    _log->writeDebug(pathList.first().toStdString() + " as image path selected.");
  }
}

void IDMT_widget::sltSelectOutputFolder(){
  _log->writeDebug("function: void IDMT_widget::sltSelectOutputFolder()");
	QString path = openFolder();
	_ui.outputFolder_pathEdit->setText(path);
	_log->writeDebug(path.toStdString() + " as output folder selected.");
}

void IDMT_widget::sltAbleQualitySelection(bool select){
  _log->writeDebug("function: void IDMT_widget::sltAbleQualitySelection(bool select)");
	_ui.quality_lineEdit->setEnabled(select);
	_ui.quality_label1->setEnabled(select);
	_ui.showhistogram_checkBox->setEnabled(select);
	_ui.savehistogram_checkBox->setEnabled(select);
  _ui.quality_label2->setEnabled(select);
  _ui.applypdetected_checkBox->setEnabled(select);
  sltAblePdetectedSelection(select);
	if( select ) _log->writeDebug("Quality check enabled.");
	else    	   _log->writeDebug("Quality check disabled.");
}

void IDMT_widget::sltAblePdetectedSelection(bool select){
  _log->writeDebug("function: void IDMT_widget::sltAblePdetectedSelection(bool select)");
  _ui.pd_label1->setEnabled(select);
	_ui.pd_lineEdit->setEnabled(select);
  if( select ){ 
    _ui.applysmooth_checkBox->setEnabled(_ui.applypdetected_checkBox->checkState());
    sltAbleSmoothingSelection(_ui.applypdetected_checkBox->checkState());
  }else{
    _ui.applysmooth_checkBox->setEnabled(false);
    sltAbleSmoothingSelection(false);
  }
	if( select ) _log->writeDebug("Pdetected check enabled.");
	else         _log->writeDebug("Pdetected check disabled.");
}


void IDMT_widget::sltAbleSmoothingSelection(bool select){
  _log->writeDebug("function: void IDMT_widget::sltAbleSmoothingSelection(bool select)");
  _ui.window_label->setEnabled(select);
	_ui.window_length_lineEdit->setEnabled(select);
  _ui.minpd_label->setEnabled(select);
	_ui.window_valid_lineEdit->setEnabled(select);
	if( select ) _log->writeDebug("Smooth check enabled.");
	else    	   _log->writeDebug("Smooth check disabled.");
}

void IDMT_widget::sltAbleCombiSelection(bool select){
  _log->writeDebug("function: void IDMT_widget::sltAbleCombiSelection(bool)");
	_ui.combi_label1->setEnabled(select);
	_ui.combi_lineEdit->setEnabled(select);
	_ui.bild_distance_label->setEnabled(select);
	_ui.bild_distance_label1->setEnabled(select);
	_ui.bild_distance_lineEdit_X->setEnabled(select);
	_ui.bild_distance_label2->setEnabled(select);
	_ui.bild_distance_lineEdit_Y->setEnabled(select);
	_ui.bild_distance_label3->setEnabled(select);
	_ui.user_distance_label->setEnabled(select);
	_ui.user_distance_lineEdit->setEnabled(select);

	if( select ) _log->writeDebug("Combi check enabled.");
	else         _log->writeDebug("Combi check disabled.");
}

void IDMT_widget::sltStartConversion(){
  _log->writeDebug("function: void IDMT_widget::sltStartConversion()");
	//set Strings
	QString subjectindexPath = _ui.subjectCsv_pathEdit->text();
	QString imagePath        = _ui.image_pathEdit->text();
	QString qImage_width     = _ui.width_lineEdit->text();
	QString qImage_height    = _ui.height_lineEdit->text();
	QString outputPath       = _ui.outputFolder_pathEdit->text();
	QString qualityPrefix    = _ui.quality_lineEdit->text();
  QString qPdetected       = _ui.pd_lineEdit->text();
	QString qCombi           = _ui.combi_lineEdit->text();
	QString qBild_distance_x = _ui.bild_distance_lineEdit_X->text();
	QString qBild_distance_y = _ui.bild_distance_lineEdit_Y->text();
	QString qUser_distance   = _ui.user_distance_lineEdit->text();
  QString qWindow_length   = _ui.window_length_lineEdit->text();
  QString qWindow_minpd    = _ui.window_valid_lineEdit->text();

	//set bools
	bool quality        = _ui.checkQuality_checkBox->isChecked() && _ui.checkQuality_checkBox->isEnabled();
  bool show_histogram = _ui.showhistogram_checkBox->checkState() && _ui.showhistogram_checkBox->isEnabled();
  bool save_histogram = _ui.savehistogram_checkBox->checkState() && _ui.savehistogram_checkBox->isEnabled();
  bool use_pdetected  = _ui.applypdetected_checkBox->checkState() && _ui.applypdetected_checkBox->isEnabled();
  bool use_smooth     = _ui.applysmooth_checkBox->checkState() && _ui.applysmooth_checkBox->isEnabled();
  bool use_combi      = _ui.checkCombi_checkBox->checkState() && _ui.checkCombi_checkBox->isEnabled();

  IDMT plugin(_log);

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
    if( !plugin.loadSubject(subjectindexPath.toStdString()) ){
      QMessageBox::warning(this,"Error", "Error loading Subject file");
      _log->writeWarn("No subject set, Error message: 'Error loading Subject file': " + subjectindexPath.toStdString());
      return;
    }
  }

  //Set Bilder info
  plugin.setPrintPics(true); //print only if the picture is available
  plugin.setBilderPath(imagePath.toStdString());
  bool ok1, ok2;
  uint image_height = qImage_height.toUInt(&ok1, 10);
  uint image_width  = qImage_width.toUInt(&ok2, 10);
  if( !ok1 || !ok2 || !plugin.setImageSize(image_height, image_width) ){
		QMessageBox::warning(0, "Error", "Image size values are not valid!");
    _log->writeWarn("Image size values are not valid: \"" + qImage_height.toStdString() + "\"x\"" + qImage_width.toStdString() +"\"" );
    return;
  }


  //Set combi option
  if( use_combi ){
    bool ok1, ok2, ok3, ok4;
    uint   combi             = qCombi.toUInt(&ok1, 10);;
    double bild_distance_x = qBild_distance_x.toDouble(&ok2);
    double bild_distance_y = qBild_distance_y.toDouble(&ok3);
    double user_distance   = qUser_distance.toDouble(&ok4);
    if( !ok1 || !ok2 || !ok3|| !ok4 || !plugin.setCombi(true, combi, bild_distance_x, bild_distance_y, user_distance) ){
      QMessageBox::warning(0, "Error", "Combi algortihm options are not valid!");
      _log->writeWarn("Combi algortihm options are not valid: \"" + qCombi.toStdString() 
                      + "\"x\"" + qBild_distance_x.toStdString() + "x" + qBild_distance_y.toStdString() + "x" + qUser_distance.toStdString() + "\"");
      return;
    }
  }

  //dont print picture name in output
  plugin.setBilderInOutname(false);

  //create quality output
  if( quality ){

    //Check person detected length
    if( use_pdetected ){
      bool ok1, ok2;
      uint pdetected = qPdetected.toUInt(&ok1, 10);
      if( !ok1 || !plugin.setPdetected(use_pdetected, pdetected) ){
        QMessageBox::warning(0, "Error", "Person detected value is not valid: " + qPdetected);
        _log->writeWarn("Person detected value is not valid: " + qPdetected.toStdString());
      }else if( use_smooth ){
        uint window_length = qWindow_length.toUInt(&ok1, 10);
        uint window_minpd  = qWindow_minpd.toUInt(&ok2, 10);
        if( !ok1 || !ok2 || !plugin.setQualityWindow(use_smooth, window_length, window_minpd) ){
          QMessageBox::warning(0, "Error", "Smooth windows values are not valid" );
          _log->writeWarn("Smooth windows values are not valid!': \"" + qWindow_length.toStdString() + "\"-\"" + qWindow_minpd.toStdString() + "\"");
        }
      }
    }

    //Write quality output
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

  finishHistogram(neues, outputPath, qualityPrefix, save_histogram, show_histogram);

  progressDialog.close();

  //write fileError to the output
  writeFileError(fileError, outputPath);

  QMessageBox::information(0, "Information", "The file fragmentation is done!");
  _log->writeDebug("The file fragmentation is done!");

  string outputlogfile_path = outputPath.toStdString() + FILE_SLASH + "log.txt";
  _log->copylogfile(outputlogfile_path);
}


Q_EXPORT_PLUGIN2(idmt_widget, IDMT_widget)
