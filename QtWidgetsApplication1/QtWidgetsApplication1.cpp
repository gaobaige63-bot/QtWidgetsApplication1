#include "QtWidgetsApplication1.h"
#include"ui_QtWidgetsApplication1.h"
#include"CubeWidget.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QHBoxLayout* mainlayout = new QHBoxLayout(ui.centralWidget);
    cubeWidget = new CubeWidget(this);
    mainlayout->addWidget(cubeWidget, 3);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(ui.btnScramble);
    layout->addWidget(ui.btnU);
    layout->addWidget(ui.btnR);
    layout->addWidget(ui.btnF);
    layout->addWidget(ui.btnL);
    layout->addWidget(ui.btnD);
    layout->addWidget(ui.btnB);
    mainlayout->addLayout(layout, 1);
    this->resize(800, 600);
    connect(ui.btnScramble, &QPushButton::clicked, this, [=]() {
        cubeWidget->cube.scramble(30);
        cubeWidget->update();
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
        });
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}

