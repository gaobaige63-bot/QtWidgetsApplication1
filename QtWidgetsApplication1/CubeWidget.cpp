#include "CubeWidget.h"
#include<QPainter>

CubeWidget::CubeWidget(QWidget* parent):QWidget(parent){}
void drawParallelogram(QPainter& p, QPoint a, QPoint b, QPoint c, QPoint d, QColor color) {
	QPolygon poly;
	poly << a << b << c << d;

	p.setBrush(color);
	p.drawPolygon(poly);
}
void CubeWidget::paintEvent(QPaintEvent*) {
	QPainter p(this);
	int size = 40;
	int gap = 2;
	QColor colors[6] = {
		Qt::yellow,
		Qt::green,
		Qt::red,
		Qt::blue,
		QColor(255,165,0),
		Qt::white
	};
	int offsetX[6] = { 3,6,3,0,9,3 };
	int offsetY[6] = { 0,3,3,3,3,6 };
	for (int f = 0;f < 6;f++) {
		for (int i = 0;i < 3;i++) {
			for (int j = 0;j < 3;j++) {
				int x = (offsetX[f] + j) * (size + gap) + 10;
				int y = (offsetY[f] + i) * (size + gap) + 10;
				int colorIndex = cube.face[f][i][j];
				QColor c = colors[colorIndex];
				p.fillRect(x, y, size, size, c);
				p.drawRect(x, y, size, size);
			}
		}
	}

    int x0 = 570;
    int y0 = 220;
    int s = 35;
    int dx = 18;
    int dy = -18;

    int topFace = 0;
    int frontFace = 2;
    int rightFace = 1;

    //  前面 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            QColor c = colors[cube.face[frontFace][i][j]];

            int x = x0 + j * s;
            int y = y0 + i * s;

            p.fillRect(x, y, s, s, c);
            p.drawRect(x, y, s, s);
        }
    }

    //  上面 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            QColor c = colors[cube.face[topFace][i][j]];

            int x = x0 + j * s + (2 - i) * dx;
            int y = y0 - 3 * 18 + i * 18+18;

            QPolygon poly;
            poly << QPoint(x, y)
                << QPoint(x + s, y)
                << QPoint(x + s + dx, y + dy)
                << QPoint(x + dx, y + dy);

            p.setBrush(c);
            p.drawPolygon(poly);
        }
    }

    //  右面 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            QColor c = colors[cube.face[rightFace][i][j]];

            int x = x0 + 3 * s + j * dx;
            int y = y0 + i * s + j * dy;

            QPolygon poly;
            poly << QPoint(x, y)
                << QPoint(x + dx, y + dy)
                << QPoint(x + dx, y + dy + s)
                << QPoint(x, y + s);

            p.setBrush(c);
            p.drawPolygon(poly);
        }
    }
}