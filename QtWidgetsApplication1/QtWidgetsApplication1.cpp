#include "QtWidgetsApplication1.h"
#include"ui_QtWidgetsApplication1.h"
#include"CubeWidget.h"
#include<QHBoxLayout>
#include<QWidget>
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QWidget* central = new QWidget(this);
    this->setCentralWidget(central);
    QHBoxLayout* layout = new QHBoxLayout(central);
    cubeWidget = new CubeWidget(this);
    layout->addWidget(cubeWidget, 3);
    layout->addWidget(ui.btnTest, 1);
    this->resize(800, 600);
    connect(ui.btnTest, &QPushButton::clicked, this, [=]() {
        cubeWidget->cube.moveR();
        cubeWidget->update();
        });
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}

