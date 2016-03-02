#include "Eyetracebutler_widget.hpp"
#include "Plugin_widget.hpp"
#include <QMouseEvent>
#include <QImageReader>
#include "common.hpp"

#ifdef __unix
  #define BOOST_SYSTEM_NO_DEPRECATED
  #include <boost/regex.hpp>
  using namespace boost;
#else
  #include <regex>
  using namespace std::tr1;
#endif


Eyetracebutler_widget::Eyetracebutler_widget(LogFileWriter *logfile, QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), _log(logfile)
{
	_log->write("CompanyName: University of Tuebingen ");
	_log->write("FileDescription: Eyetrace Butler: Prepares SMI data for processing in Eyetrace");
	_log->write("FileVersion: " + EYETRACEBUTLER_VERSION );
	_log->write("InternalName: Eyetrace Butler widget");
	_log->write("LegalCopyright: Copyright (C) 2015"); 
	_log->write("OriginalFilename: Eyetrace Butler widget");
	_log->write("ProductName: Eyetrace Butler");
	_log->write("ProductVersion: " + EYETRACEBUTLER_VERSION );

  //check the image formats supported
  QList<QByteArray> list = QImageReader::supportedImageFormats();
  _log->write("Image Supported formats: ");
  std::string formats = ""; 
  for(int i=0; i<list.size(); ++i){ QString str(list[i].constData()); formats += "," + str.toStdString(); }
  _log->write("- " + formats );

	_log->write("Starting application...");

  _ui.setupUi(this);

  QDir pluginDir(qApp->applicationDirPath());
  QStringList fileList = get_pluginFileList(&pluginDir);
	for(int i = 0; i < fileList.size(); i++) {
		QPluginLoader pluginLoader(pluginDir.absoluteFilePath(fileList.at(i)));
		QObject *plugin = pluginLoader.instance();
    if (plugin) {
      QWidget* etPlugin = qobject_cast<QWidget*>(plugin);
      if (etPlugin){
        _ui.ET_comboBox->addItem(etPlugin->accessibleName());
      }
		}else{
      _log->writeError(pluginLoader.errorString().toStdString());
    }
	}
}

Eyetracebutler_widget::~Eyetracebutler_widget()
{

}


void Eyetracebutler_widget::closeEvent (QCloseEvent *event){
  _log->writeDebug("function: void Eyetracebutler_widget::closeEvent (QCloseEvent *event)");
  QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Eyetrace Butler",
                                                              tr("Do you really want to quit Eyetrace Butler?\n"),
                                                              QMessageBox::No | QMessageBox::Yes);
  if (resBtn != QMessageBox::Yes) {
    event->ignore();
  } else {
    _log->write("Application closed by user");
    event->accept();
  }
}


void Eyetracebutler_widget::refreshSurface(){
  QDir pluginDir(qApp->applicationDirPath());
  QStringList fileList = get_pluginFileList(&pluginDir);
  for(int i = 0; i < fileList.size(); i++) {
    regex reg_plugname( "plug_([^\\.]+).*" );
    cmatch res_plugname;
    string filename = fileList.at(i).toStdString();
    if( regex_search( filename.c_str(), res_plugname, reg_plugname)){
      QString plugname = QString::fromStdString(string(res_plugname[1]));
      QString comboname = _ui.ET_comboBox->currentText();
      _log->writeDebug("Comboname:"+comboname.toStdString());
      _log->writeDebug("PluginName:"+plugname.toStdString());
      if(plugname == comboname) {
        QPluginLoader pluginLoader(pluginDir.absoluteFilePath(fileList.at(i)));
        Plugin_widget* plugin = qobject_cast<Plugin_widget*>(pluginLoader.instance());
        if (plugin){
          plugin->setLog(_log);
          QWidget *widget = plugin->getWidget();
          this->setCentralWidget(widget);
        }
      }
    }
  }

}

QStringList Eyetracebutler_widget::get_pluginFileList(QDir *pluginDir){
  _log->writeDebug("Pluging dir: "    + pluginDir->absolutePath().toStdString() );

#ifdef __linux__
  //linux operative system
  QStringList filter = (QStringList() << "*.so");
#elif __APPLE__
  //macintosh operative system
  QStringList filter = (QStringList() << "*.dylib");
#else  
  //Windows operative system
  QStringList filter = (QStringList() << "*.dll");
#endif

  pluginDir->setNameFilters(filter);
  QStringList fileList = pluginDir->entryList(QDir::Files);
  _log->writeDebug("Plugin files: " + fileList.join("\n").toStdString());
  return fileList;
}


#include "Eyetracebutler_widget.hpp"
#include <QtGui/QApplication>
#include <QThread>
#include <QPixmap>
#include <QSplashScreen>
#include <QWidget>
#include <QEventLoop>
#include <QTimer>


class I : public QThread
{
public:
  static void sleep(unsigned long secs) {
    QThread::sleep(secs);
  }
};

int main(int argc, char *argv[])
{
  //-----------------------
  QApplication a(argc, argv);
  QPixmap pixmap(":/EyetraceButler/splash");
  QSplashScreen splash(pixmap);
  splash.show();
  //   splash.showMessage("Wait ...");
  QEventLoop loop;
  QTimer::singleShot(1000, &loop, SLOT(quit()));
  loop.exec();
  //  splash.showMessage("Wait some more ...");
  QTimer::singleShot(1000, &loop, SLOT(quit()));
  loop.exec();
  //splash.showMessage("Already done ...");
  QTimer::singleShot(1000, &loop, SLOT(quit()));
  loop.exec();
  // splash.showMessage("Just annoying you ...");
  QTimer::singleShot(1000, &loop, SLOT(quit()));
  loop.exec();
  //-------------------------------------

  setlocale(LC_NUMERIC, "C");
  LogFileWriter logfile;
  logfile.createlogfile("./EyetraceButler.log");
  Eyetracebutler_widget w(&logfile);
  w.show();

  //-------------------------------------
  splash.finish(&w);
  //-------------------------------------

  return a.exec();
}
