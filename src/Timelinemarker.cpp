#include "Timelinemarker.hpp"
#include <qpaintengine.h>

Timelinemarker::Timelinemarker(QWidget *parent)
	: QWidget(parent)
{
	_colorPalette << QColor(215,25,28) << QColor(255,255,91) << QColor(26,150,65);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setMinimumHeight(4);
  setMinimumWidth(190);
}

Timelinemarker::~Timelinemarker()
{

}

void Timelinemarker::setMarkers(QList<int> markers){
	_markers = markers;
}

void Timelinemarker::setColorPalette(QList<QColor> colors){
	_colorPalette = colors;
}

void Timelinemarker::paintEvent(QPaintEvent* e){
	int count = std::max(1,_markers.size());
	double stepwidth = double(this->width())/double(count);

	QPainter painter(this);
	painter.setPen(QColor(255,0,0));

	for(int i=0; i<_markers.size(); i++){
		int colorIndex = _markers.at(i);
		painter.setPen(_colorPalette[colorIndex]);
		painter.drawRect(i*stepwidth, 0, stepwidth, this->height());
	}
}

QList<int> Timelinemarker::getUniqueLabels(QList<int> label){
	QList<int> uniqueLabels;
	for(int i=0; i<label.size(); i++){
		if(!uniqueLabels.contains(label[i])){
			uniqueLabels.push_back(label[i]);
		}
	}

	return uniqueLabels;
}
