#ifndef SMIHED_WIDGET_H
#define SMIHED_WIDGET_H

#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QFileDialog>
#include <QtCore/qplugin.h>
#include <list>
#include "ui_smihed.h"
#include "Timelinemarker.hpp"
#include "Plugin_widget.hpp"   
#include "Data.hpp"   

using namespace std;

class SMIHED_widget : public QWidget, public Plugin_widget
{
  Q_OBJECT
  Q_INTERFACES(Plugin_widget)

public:

  SMIHED_widget(QWidget *parent = 0);
  ~SMIHED_widget();
  QWidget* getWidget();
private:

  Ui::SMIHED_widget _ui;
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
  void sltSetImageFolder();
  void sltSelectOutputFolder();

  void sltAbleSelection(bool select);

signals:

};

#endif // SMIHED_WIDGET_H
