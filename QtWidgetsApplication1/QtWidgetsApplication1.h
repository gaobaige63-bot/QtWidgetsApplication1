#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include"CubeWidget.h"
#include <QLabel>
#include <QTimer>
#include <QElapsedTimer>  
#include<QVector>

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();

private:
    Ui::mainWindow ui;
    CubeWidget* cubeWidget;
    QLabel* lblTitle;
    QLabel* lblStatus;
    QLabel* lblTime;
    QLabel* lblView;

    QTimer* refreshTimer;
    QElapsedTimer timer;
    bool waitingFirstMove = false;
    bool gameStarted = false;
    QString statusText = "Ready";

    QVector<double> solveTimes;
    double bestTime = -1.0;

    void updateStatusLabels();
    void startTimerOnFirstMove();
    void checkSolved();

};

