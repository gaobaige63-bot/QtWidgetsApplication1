#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include"CubeWidget.h"
#include <QElapsedTimer>  

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();

private:
    Ui::mainWindow ui;
    CubeWidget* cubeWidget;
    QElapsedTimer timer;
    bool gameStarted = false;
};

