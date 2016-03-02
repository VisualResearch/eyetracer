#ifndef SMIRED5_WIDGET_H
#define SMIRED5_WIDGET_H

#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QFileDialog>
#include <QtCore/qplugin.h>
#include <list>
#include "ui_smired5.h"
#include "Timelinemarker.hpp"
#include "Plugin_widget.hpp"   
#include "Data.hpp"   

using namespace std;

class SMIRED5_widget : public QWidget, public Plugin_widget
{
  Q_OBJECT
  Q_INTERFACES(Plugin_widget)

public:

  SMIRED5_widget(QWidget *parent = 0);
  ~SMIRED5_widget();
  QWidget* getWidget();
private:

  Ui::SMIRED5_widget _ui;
  QStringListModel  *_fileListModel;
  QStringList        _fileList;

  QStringList openFile(QString filter);
  QString     openFolder();


public slots:

  void sltAddFile();
  void sltRemoveFile();
  void sltRemoveAll();

  void sltStartFragmentation();
  void sltSetSubjectPath();
  void sltSetImageFolder();
  void sltSelectOutputFolder();
  void sltAbleSelection(bool select);
  void sltRemoveBlink();

signals:

};

#endif // SMIRED5_WIDGET_H
