#ifndef EYETRACEBUTLER_WIDGET_H
#define EYETRACEBUTLER_WIDGET_H

#include <QtGui/QMainWindow>
#include <qdir.h>
#include <qpluginloader.h>
#include <qmessagebox.h>
#include "LogFileWriter.hpp"
#include "ui_eyetracebutler.h"

using namespace std;

/**
   @author: katrin sippel
   @doc: class of the central GUI, managing the different operations
*/

class Eyetracebutler_widget : public QMainWindow
{
	Q_OBJECT

public:
	
	Eyetracebutler_widget(LogFileWriter *logfile=0, QWidget *parent = 0, Qt::WFlags flags = 0);	
	~Eyetracebutler_widget();
	Ui::Eyetracebutler_widget _ui;
	LogFileWriter *_log;
	void closeEvent(QCloseEvent *event);

private:
  QStringList get_pluginFileList(QDir *pluginDir);

public slots:
	void refreshSurface();
};

#endif // EYETRACEBUTLER_WIDGET_H
