#pragma once
#include <QWidget>
#include"Cube.h"
class CubeWidget :
    public QWidget
{
    Q_OBJECT
public:
    explicit CubeWidget(QWidget* parent = nullptr);
    Cube cube;
    int viewIndex = 0;

    void nextView() {
        viewIndex = (viewIndex + 1) % 4;
        update();
    }
protected:
    void paintEvent(QPaintEvent* event)override;
};

