#ifndef TIMELINEMARKER_H
#define TIMELINEMARKER_H

#include <QtGui/QWidget>
#include <qlist.h>


class Timelinemarker : public QWidget
{
	Q_OBJECT

public:
	Timelinemarker(QWidget *parent = 0);
	~Timelinemarker();

	void paintEvent(QPaintEvent* e);

	void setMarkers(QList<int> markers);
	void setColorPalette(QList<QColor> colors);

private:
	QList<QColor> _colorPalette;
	QList<int> _markers;

	QList<int> getUniqueLabels(QList<int> l);

};

#endif // TIMELINEMARKER_H
