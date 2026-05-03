#include "CubeWidget.h"
#include<QPainter>

CubeWidget::CubeWidget(QWidget* parent):QWidget(parent){}
void CubeWidget::paintEvent(QPaintEvent*) {
	QPainter p(this);
	int size=40;
	int gap = 2;
	QColor colors[6] = {
		Qt::white,
		Qt::blue,
		Qt::red,
		Qt::green,
		QColor(255,165,0),
		Qt::yellow
	};
	int offsetX[6] = { 3,6,3,0,9,3 };
	int offsetY[6] = { 0,3,3,3,3,6 };
	for(int f=0;f<6;f++){
	    for(int i=0;i<3;i++){
			for (int j = 0;j < 3;j++) {
				int x = (offsetX[f] + j) * (size + gap)+10;
				int y = (offsetY[f] + i) * (size + gap)+10;
				int colorIndex = cube.face[f][i][j];
				QColor c = colors[colorIndex];
				p.fillRect(x, y, size, size, c);
				p.drawRect(x, y, size, size);
			}
		} 
	}
}