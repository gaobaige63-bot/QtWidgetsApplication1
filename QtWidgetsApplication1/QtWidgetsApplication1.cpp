#include "QtWidgetsApplication1.h"
#include"ui_QtWidgetsApplication1.h"
#include"CubeWidget.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>
#include<QMessageBox>
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QString btnStyle = "font-size: 18px; min-height: 50px;";

    ui.btnU->setStyleSheet(btnStyle);
    ui.btnR->setStyleSheet(btnStyle);
    ui.btnF->setStyleSheet(btnStyle);
    ui.btnL->setStyleSheet(btnStyle);
    ui.btnD->setStyleSheet(btnStyle);
    ui.btnB->setStyleSheet(btnStyle);
    ui.btnScramble->setStyleSheet(btnStyle);
    ui.btnView->setStyleSheet(btnStyle);

    QHBoxLayout* mainlayout = new QHBoxLayout(ui.centralWidget);
    cubeWidget = new CubeWidget(this);
    mainlayout->addWidget(cubeWidget, 3);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(ui.btnScramble);
    layout->addWidget(ui.btnView);
    layout->addWidget(ui.btnU);
    layout->addWidget(ui.btnR);
    layout->addWidget(ui.btnF);
    layout->addWidget(ui.btnL);
    layout->addWidget(ui.btnD);
    layout->addWidget(ui.btnB);
    mainlayout->addLayout(layout, 1);
    this->resize(1000, 700);

    connect(ui.btnScramble, &QPushButton::clicked, this, [=]() {
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->cube = Cube();
            cubeWidget->update();
            gameStarted = false;
        }
        else
        {
            cubeWidget->cube.scramble(30);
            cubeWidget->update();
            timer.start();
            gameStarted = true;
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
        });
    connect(ui.btnU, &QPushButton::clicked, this, [=]() {
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
        if (gameStarted && cubeWidget->cube.isSolved()) {
            gameStarted = false;

            double seconds = timer.elapsed() / 1000.0;

            QMessageBox::information(
                this,
                "Solved!",
                QString("You solved the cube in %1 seconds.").arg(seconds, 0, 'f', 2)
            );
        }
        });
    connect(ui.btnR, &QPushButton::clicked, this, [=]() {
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
        if (gameStarted && cubeWidget->cube.isSolved()) {
            gameStarted = false;

            double seconds = timer.elapsed() / 1000.0;

            QMessageBox::information(
                this,
                "Solved!",
                QString("You solved the cube in %1 seconds.").arg(seconds, 0, 'f', 2)
            );
        }
        });
    connect(ui.btnF, &QPushButton::clicked, this, [=]() {
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
        if (gameStarted && cubeWidget->cube.isSolved()) {
            gameStarted = false;

            double seconds = timer.elapsed() / 1000.0;

            QMessageBox::information(
                this,
                "Solved!",
                QString("You solved the cube in %1 seconds.").arg(seconds, 0, 'f', 2)
            );
        }
        });
    connect(ui.btnL, &QPushButton::clicked, this, [=]() {
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
        if (gameStarted && cubeWidget->cube.isSolved()) {
            gameStarted = false;

            double seconds = timer.elapsed() / 1000.0;

            QMessageBox::information(
                this,
                "Solved!",
                QString("You solved the cube in %1 seconds.").arg(seconds, 0, 'f', 2)
            );
        }
        });
    connect(ui.btnD, &QPushButton::clicked, this, [=]() {
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
        if (gameStarted && cubeWidget->cube.isSolved()) {
            gameStarted = false;

            double seconds = timer.elapsed() / 1000.0;

            QMessageBox::information(
                this,
                "Solved!",
                QString("You solved the cube in %1 seconds.").arg(seconds, 0, 'f', 2)
            );
        }
        });
    connect(ui.btnB, &QPushButton::clicked, this, [=]() {
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
        if (gameStarted && cubeWidget->cube.isSolved()) {
            gameStarted = false;

            double seconds = timer.elapsed() / 1000.0;

            QMessageBox::information(
                this,
                "Solved!",
                QString("You solved the cube in %1 seconds.").arg(seconds, 0, 'f', 2)
            );
        }
        });
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}

