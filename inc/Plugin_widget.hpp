#ifndef PLUGIN_WIDGET_H
#define PLUGIN_WIDGET_H

#include <QtCore/qplugin.h>
#include <QWidget>
#include <QVBoxLayout>
#include "Data.hpp"
#include "LogFileWriter.hpp"

class Plugin_widget
{
public:
  Plugin_widget();
	~Plugin_widget();
  virtual QWidget* getWidget() = 0;
  inline void setLog(LogFileWriter *logfile){ _log =logfile; }
  void generateHistogram(string output_path, string output_file_name, string file_prefix,
                         bool save_histogram, bool show_histogram, list<Data*> list_data, int &shift_histo_window);
  void generateHistogram(QWidget *neues, QVBoxLayout *lay, string output_file_name, list<Data*> list_data);
  void finishHistogram(QWidget *neues, QString outputPath, QString qualityPrefix, bool save_histogram, bool show_histogram);
  void writeFileError(vector<string> fileError, QString outputPath);
  void closeWidgets();

private:
  QList<QWidget*> _widgets_open;

protected:
  LogFileWriter *_log;

};

Q_DECLARE_INTERFACE(Plugin_widget, "org.test.Plugin_widget/1.0")

#endif // PLUGIN_WIDGET_H
