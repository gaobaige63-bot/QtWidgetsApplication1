#pragma once
#include <QWidget>
#include<QTimer>
#include"Cube.h"
class CubeWidget :
    public QWidget
{
    Q_OBJECT
public:
    explicit CubeWidget(QWidget* parent = nullptr);
    Cube cube;
    int viewIndex = 0;
    double viewAnim = 1.0;
    QTimer* viewAnimTimer;

    void nextView() {
        viewIndex = (viewIndex + 1) % 4;
        viewAnim = 0.0;
        viewAnimTimer->start(16);
        update();
    }
protected:
    void paintEvent(QPaintEvent* event)override;
};

