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
protected:
    void paintEvent(QPaintEvent* event)override;
};

