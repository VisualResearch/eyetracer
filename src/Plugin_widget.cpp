#include "Plugin_widget.hpp"
#include "Timelinemarker.hpp"
#include <QLabel>
#include <QPainter>
#include <QMessageBox>

Plugin_widget::Plugin_widget(){
  closeWidgets();
}

Plugin_widget::~Plugin_widget(){}

void Plugin_widget::closeWidgets(){
  // QList<QWidget*>::iterator itr;
  // for(itr = _widgets_open.begin(); itr != _widgets_open.end(); itr++){
  //   QWidget *widget = *itr;
  //   if(widget != NULL){
  //     widget->close();
  //     delete widget;
  //   }
  // }
  // _widgets_open.clear();
}

void Plugin_widget::generateHistogram(string output_path, string output_file_name, string file_prefix, 
                                      bool save_histogram, bool show_histogram, list<Data*> list_data, int &shift_histo_window){
  _log->writeDebug("function:  void SMIRED5_widget::generateHistogram(string output_path, string output_file_name, string file_prefix, bool save_histogram, bool show_histogram, list<Data*> list_data)");

  QWidget        *neues = new QWidget();
  QVBoxLayout    *lay   = new QVBoxLayout();

  _widgets_open.append(neues);
  if( !show_histogram ){ neues->setAttribute(Qt::WA_DontShowOnScreen,true); }
  neues->setGeometry(100+shift_histo_window,100+shift_histo_window,500,50*list_data.size());
  neues->setLayout(lay);

  list<Data*>::iterator iter;
  for( iter=list_data.begin(); iter!=list_data.end(); iter++ ){
    Data *element = *iter;
    QList<int> markers_list;
    double eye_qual[3] = {0,0,0};
    list<Data_element> *sublist_data = element->getList();
    list<Data_element>::iterator subitr;

    //calculate percentage and markers
    for(subitr = sublist_data->begin(); subitr != sublist_data->end(); subitr++){
      unsigned int marker = subitr->left_valid + subitr->right_valid;
      markers_list.append(marker);
      eye_qual[marker]++;
    }
    eye_qual[0]=floor((eye_qual[0]*100)/sublist_data->size());
    eye_qual[1]=floor((eye_qual[1]*100)/sublist_data->size());
    eye_qual[2]=floor((eye_qual[2]*100)/sublist_data->size());
    std::ostringstream  eye_qual_info;
    eye_qual_info <<
      "Both eyes valid: " << eye_qual[2] << "%<br>"
      "One eye valid:   " << eye_qual[1] << "%<br>"
      "No eye valid:    " << eye_qual[0] << "%";

    //create info text + time line marker + quality text
    Timelinemarker *tml = new Timelinemarker();
    QHBoxLayout *lay_h    = new QHBoxLayout();
    QLabel      *txt      = new QLabel();
    QLabel      *qual_txt = new QLabel();

	  if( !show_histogram ){
		  tml->setAttribute(Qt::WA_DontShowOnScreen,true);
	  }
    
    string label = "BilderName:     " + element->getBilderName()  +
      "<br>Subject ID: " + element->getSubjectID() +
      "<br>File ID:    " + element->getFileID();

    QString qlabel = QString::fromStdString(label);
    txt->setText(qlabel);

    QString qeye_equal_info =  QString::fromStdString(eye_qual_info.str());
    qual_txt->setText(qeye_equal_info);
    tml->setMarkers(markers_list);

    lay_h->addWidget(txt);
    lay_h->addWidget(tml);
    lay_h->addWidget(qual_txt);
    lay->addLayout(lay_h);
  }

  if( save_histogram ){
    string histogramFile_path = output_path + FILE_SLASH + file_prefix + "_" + output_file_name + "_histogram.jpg";
    QString qhistogramFile_path = QString::fromStdString(histogramFile_path);
    neues->show();
    QImage draw_widget(neues->size().width(),neues->size().height(),QImage::Format_ARGB32);
    QPainter painter(&draw_widget);  
    neues->render(&painter);
    if( !draw_widget.save(qhistogramFile_path) ){
      _log->writeWarn("Problems saving histogram: " + qhistogramFile_path.toStdString() );
    }
  }
  if( show_histogram ){ neues->show();  }
  else{                 neues->close(); }
  shift_histo_window+=25;
}


void Plugin_widget::generateHistogram(QWidget *neues, QVBoxLayout *lay, string output_file_name, list<Data*> list_data){
  _log->writeDebug("function: void SMIHED_widget::generateHistogram(QWidget *neues, QVBoxLayout *lay, string output_file_name, list<Data*> list_data)");

  _widgets_open.append(neues);
  neues->setGeometry(100,100,500,50*list_data.size());

  list<Data*>::iterator iter;
  for( iter=list_data.begin(); iter!=list_data.end(); iter++ ){
    Data *element = *iter;
    QList<int> markers_list;
    double eye_qual[3] = {0,0,0};
    list<Data_element> *sublist_data = element->getList();
    list<Data_element>::iterator subitr;

    //calculate percentage and markers
    for(subitr = sublist_data->begin(); subitr != sublist_data->end(); subitr++){
      unsigned int marker = subitr->left_valid + subitr->right_valid;
      markers_list.append(marker);
      eye_qual[marker]++;
    }
    eye_qual[0]=floor((eye_qual[0]*100)/sublist_data->size());
    eye_qual[1]=floor((eye_qual[1]*100)/sublist_data->size());
    eye_qual[2]=floor((eye_qual[2]*100)/sublist_data->size());
    std::ostringstream  eye_qual_info;
    eye_qual_info <<
      "Both eyes valid: " << eye_qual[2] << "%<br>"
      "One eye valid:   " << eye_qual[1] << "%<br>"
      "No eye valid:    " << eye_qual[0] << "%";

    //create info text + time line marker + quality text
    Timelinemarker *tml   = new Timelinemarker();
    QHBoxLayout *lay_h    = new QHBoxLayout();
    QLabel      *txt      = new QLabel();
    QLabel      *qual_txt = new QLabel();


    // string label = "BilderName:     " + element->getBilderName()  +
    //   "<br>FileName: " + output_file_name.substr(0,10);
    string label = "BilderName:     " + element->getBilderName()  +
       "<br>FileName: " + output_file_name;


    QString qlabel = QString::fromStdString(label);
    txt->setText(qlabel);

    QString qeye_equal_info =  QString::fromStdString(eye_qual_info.str());
    qual_txt->setText(qeye_equal_info);
    tml->setMarkers(markers_list);

    lay_h->addWidget(txt);
    lay_h->addStretch();
    lay_h->addWidget(tml);
    lay_h->addStretch();
    lay_h->addWidget(qual_txt);
    lay->addLayout(lay_h);
  }
  neues->update();
}

void Plugin_widget::finishHistogram(QWidget *neues, QString outputPath, QString qualityPrefix, bool save_histogram, bool show_histogram){
  if( save_histogram ){
    string histogramFile_path = outputPath.toStdString() + FILE_SLASH + qualityPrefix.toStdString() + "_histogram.jpg";
    QString qhistogramFile_path = QString::fromStdString(histogramFile_path); 
    neues->show();
    QImage draw_widget(neues->size().width(),neues->size().height(),QImage::Format_ARGB32);
    QPainter painter(&draw_widget);
    neues->render(&painter);
    if( !draw_widget.save(qhistogramFile_path) ){
      _log->writeWarn("Problems saving histogram: " + qhistogramFile_path.toStdString() );
    }
  }

  if( show_histogram ){ neues->show();  }
  else{                 neues->close(); }
}

void Plugin_widget::writeFileError(vector<string> fileError, QString outputPath){
  if( !fileError.empty() ){

    //write to File
    string outputerrorfile_path = outputPath.toStdString() + FILE_SLASH + "errors.txt";
    ofstream outputerrorfile;
    outputerrorfile.open(outputerrorfile_path);
    if( outputerrorfile.is_open() ){
      outputerrorfile << "Files not processed: " << fileError.size() << endl;
      for(size_t idx_error = 0; idx_error < fileError.size(); idx_error++ ){
        outputerrorfile << fileError[idx_error] << endl;
      } 
      _log->writeDebug("Output Error file generated: " + outputerrorfile_path);
      outputerrorfile.close();
    }else{
      cerr << endl << "Error writing Error output" << endl;
      _log->writeError("Writing Error output");
    }

    //show Warning inscreen
    string outerrormsg = "", outerrormsgend = "";
    outerrormsg    += "Files not processed: " + etbutler::uint2str(fileError.size()) +  '\n';
    outerrormsgend += "";
    unsigned int max = fileError.size();
    if( max>10 ){ max = 10; outerrormsgend = "......."; }
    for(size_t idx_error = 0; idx_error < max; idx_error++ ){
      outerrormsg += fileError[idx_error] + '\n';
    }
    outerrormsg += outerrormsgend;
    QMessageBox::warning(0, "Error", QString::fromLocal8Bit(outerrormsg.c_str()) );

  }
}
