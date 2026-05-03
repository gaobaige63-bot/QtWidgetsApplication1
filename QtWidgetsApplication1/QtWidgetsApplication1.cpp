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
    QWidget* central = new QWidget(this);
    this->setCentralWidget(central);
    QHBoxLayout* mainlayout = new QHBoxLayout(central);
    cubeWidget = new CubeWidget(this);
    mainlayout->addWidget(cubeWidget, 3);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(ui.btnU, 1);
    layout->addWidget(ui.btnR, 1);
    mainlayout->addLayout(layout, 1);
    this->resize(800, 600);
    connect(ui.btnU, &QPushButton::clicked, this, [=]() {
        cubeWidget->cube.moveU();
        cubeWidget->update();
        });
    connect(ui.btnR, &QPushButton::clicked, this, [=]() {
        cubeWidget->cube.moveR();
        cubeWidget->update();
        });
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}

