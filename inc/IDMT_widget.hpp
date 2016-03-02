#ifndef IDMT_WIDGET_H
#define IDMT_WIDGET_H

#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QFileDialog>
#include <QtCore/qplugin.h>
#include <list>
#include "ui_idmt.h"
#include "Timelinemarker.hpp"
#include "Plugin_widget.hpp"   
#include "Data.hpp"   

using namespace std;

class IDMT_widget : public QWidget, public Plugin_widget
{
  Q_OBJECT
  Q_INTERFACES(Plugin_widget)

public:

  IDMT_widget(QWidget *parent = 0);
  ~IDMT_widget();
  QWidget* getWidget();
private:

  Ui::IDMT_widget     _ui;
  QStringListModel  *_fileListModel;
  QStringList        _fileList;
 
  QStringList openFile(QString filter);
  QString     openFolder();


public slots:

  void sltAddFile();
  void sltRemoveFile();
  void sltRemoveAll();

  void sltStartConversion();
  void sltSetSubjectPath();
  void sltSetImagePath();
  void sltSelectOutputFolder();

  void sltAbleQualitySelection(bool);
  void sltAblePdetectedSelection(bool);
  void sltAbleSmoothingSelection(bool);
  void sltAbleCombiSelection(bool);

signals:

};

#endif // IDMT_WIDGET_H
