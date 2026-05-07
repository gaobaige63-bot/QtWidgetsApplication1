#include "QtWidgetsApplication1.h"
#include"ui_QtWidgetsApplication1.h"
#include"CubeWidget.h"
#include<QTimer>
#include<QLabel>
#include<QApplication>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>
#include<QMessageBox>
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->resize(1000, 700);
    QString btnStyle = "font-size: 18px; min-height: 50px;";

    ui.btnU->setStyleSheet(btnStyle);
    ui.btnR->setStyleSheet(btnStyle);
    ui.btnF->setStyleSheet(btnStyle);
    ui.btnL->setStyleSheet(btnStyle);
    ui.btnD->setStyleSheet(btnStyle);
    ui.btnB->setStyleSheet(btnStyle);
    ui.btnScramble->setStyleSheet(btnStyle);
    ui.btnView->setStyleSheet(btnStyle);
    ui.btnRecord->setStyleSheet(btnStyle);

    QVBoxLayout* outerLayout = new QVBoxLayout(ui.centralWidget);

    //  ¶¥²¿×´Ì¬À¸ 
    QHBoxLayout* statusLayout = new QHBoxLayout();

    lblTitle = new QLabel("\351\255\224\346\226\271\350\256\255\347\273\203\345\231\250");
    lblStatus = new QLabel("Status: Ready");
    lblTime = new QLabel("Time: 0.00s");
    lblView = new QLabel("View: Front");

    QString labelStyle = "font-size: 16px; font-weight: bold; color: white;";

    lblTitle->setStyleSheet("font-size: 30px; font-weight: bold; color: white;");
    lblStatus->setStyleSheet(labelStyle);
    lblTime->setStyleSheet(labelStyle);
    lblView->setStyleSheet(labelStyle);

    statusLayout->addWidget(lblTitle);
    statusLayout->addStretch();
    statusLayout->addWidget(lblStatus);
    statusLayout->addSpacing(30);
    statusLayout->addWidget(lblTime);
    statusLayout->addSpacing(30);
    statusLayout->addWidget(lblView);

    outerLayout->addLayout(statusLayout);

    QHBoxLayout* mainlayout = new QHBoxLayout(ui.centralWidget);
    cubeWidget = new CubeWidget(this);
    mainlayout->addWidget(cubeWidget, 4);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(ui.btnRecord);
    layout->addWidget(ui.btnScramble);
    layout->addWidget(ui.btnView);
    layout->addSpacing(20);
    layout->addWidget(ui.btnU);
    layout->addWidget(ui.btnR);
    layout->addWidget(ui.btnF);
    layout->addWidget(ui.btnL);
    layout->addWidget(ui.btnD);
    layout->addWidget(ui.btnB);
    layout->addStretch();
    mainlayout->addLayout(layout, 1);
    outerLayout->addLayout(mainlayout);
   
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, [=]() {
        updateStatusLabels();
        });
    refreshTimer->start(50);

    connect(ui.btnRecord, &QPushButton::clicked, this, [=]() {
        if (solveTimes.isEmpty()) {
            QMessageBox::information(this, "Records", "No records yet.");
            return;
        }

        QString text;
        text += "Solve History:\n\n";

        for (int i = 0; i < solveTimes.size(); i++) {
            text += QString("%1. %2 seconds\n")
                .arg(i + 1)
                .arg(solveTimes[i], 0, 'f', 2);
        }

        text += "\nBest Time: ";
        text += QString("%1 seconds").arg(bestTime, 0, 'f', 2);

        QMessageBox::information(this, "Records", text);
        });
    connect(ui.btnScramble, &QPushButton::clicked, this, [=]() {
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->cube = Cube();
            cubeWidget->update();
            gameStarted = false; 
            waitingFirstMove = false;
            statusText = "Ready";
            updateStatusLabels();
        }
        else
        {
            cubeWidget->cube.scramble(30);
            cubeWidget->update();
            timer.start();
            gameStarted = false;
            waitingFirstMove = true;
            statusText = "Observing";
            updateStatusLabels();
        }
        });
    connect(ui.btnView, &QPushButton::clicked, this, [=]() {
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->nextView();
            cubeWidget->nextView();
            cubeWidget->nextView();
        }
        else
        {
            cubeWidget->nextView();
        } 
        updateStatusLabels();
        });
    connect(ui.btnU, &QPushButton::clicked, this, [=]() {
        startTimerOnFirstMove();
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->cube.moveU();
            cubeWidget->cube.moveU();
            cubeWidget->cube.moveU();
        }
        else
        {
            cubeWidget->cube.moveU();
        }  
        cubeWidget->update();
        checkSolved();
        });
    connect(ui.btnR, &QPushButton::clicked, this, [=]() {
        startTimerOnFirstMove();
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->cube.moveR();
            cubeWidget->cube.moveR();
            cubeWidget->cube.moveR();
        }
        else
        {
            cubeWidget->cube.moveR();
        }
        cubeWidget->update();
        checkSolved();
        });
    connect(ui.btnF, &QPushButton::clicked, this, [=]() {
        startTimerOnFirstMove();
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->cube.moveF();
            cubeWidget->cube.moveF();
            cubeWidget->cube.moveF();
        }
        else
        {
            cubeWidget->cube.moveF();
        }
        cubeWidget->update();
        checkSolved();
        });
    connect(ui.btnL, &QPushButton::clicked, this, [=]() {
        startTimerOnFirstMove();
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->cube.moveL();
            cubeWidget->cube.moveL();
            cubeWidget->cube.moveL();
        }
        else
        {
            cubeWidget->cube.moveL();
        }
        cubeWidget->update();
        checkSolved();
        });
    connect(ui.btnD, &QPushButton::clicked, this, [=]() {
        startTimerOnFirstMove();
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->cube.moveD();
            cubeWidget->cube.moveD();
            cubeWidget->cube.moveD();
        }
        else
        {
            cubeWidget->cube.moveD();
        }
        cubeWidget->update();
        checkSolved();
        });
    connect(ui.btnB, &QPushButton::clicked, this, [=]() {
        startTimerOnFirstMove();
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->cube.moveB();
            cubeWidget->cube.moveB();
            cubeWidget->cube.moveB();
        }
        else
        {
            cubeWidget->cube.moveB();
        }
        cubeWidget->update();
        checkSolved();
        });
    updateStatusLabels();
}
void QtWidgetsApplication1::startTimerOnFirstMove()
{
    if (waitingFirstMove) {
        timer.start();
        gameStarted = true;
        waitingFirstMove = false;
        statusText = "Solving";
        updateStatusLabels();
    }
}
void QtWidgetsApplication1::updateStatusLabels()
{
    lblStatus->setText("Status: " + statusText);

    if (gameStarted) {
        double seconds = timer.elapsed() / 1000.0;
        lblTime->setText(QString("Time: %1s").arg(seconds, 0, 'f', 2));
    }
    else {
        lblTime->setText("Time: 0.00s");
    }

    QString viewName;

    switch (cubeWidget->viewIndex) {
    case 0:
        viewName = "Front";
        break;
    case 1:
        viewName = "Right";
        break;
    case 2:
        viewName = "Back";
        break;
    case 3:
        viewName = "Left";
        break;
    default:
        viewName = "Front";
        break;
    }

    lblView->setText("View: " + viewName);
}
void QtWidgetsApplication1::checkSolved()
{
    cubeWidget->update();

    if (gameStarted && cubeWidget->cube.isSolved()) {
        gameStarted = false;
        statusText = "Solved";

        double seconds = timer.elapsed() / 1000.0;
        solveTimes.push_back(seconds);
        bool isNewRecord = false;
        if (bestTime < 0 || seconds < bestTime) {
            bestTime = seconds;
            isNewRecord = true;
        }

        updateStatusLabels();

        if (isNewRecord) {
            QMessageBox::information(
                this,
                "New Record!",
                QString("New best time: %1 seconds!").arg(seconds, 0, 'f', 2)
            );
        }
        else {
            QMessageBox::information(
                this,
                "Solved!",
                QString("Solved in %1 seconds.\nBest time: %2 seconds.")
                .arg(seconds, 0, 'f', 2)
                .arg(bestTime, 0, 'f', 2)
            );
        }
    }
    
    else if (gameStarted) {
        statusText = "Sovling";
    }
    else {
        statusText = cubeWidget->cube.isSolved() ? "Ready" : "Practice";
    }

    updateStatusLabels();
}
QtWidgetsApplication1::~QtWidgetsApplication1()
{}

