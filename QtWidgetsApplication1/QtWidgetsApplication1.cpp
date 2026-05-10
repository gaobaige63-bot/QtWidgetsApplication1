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
#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton> 
#include<QFile>
#include<QTextStream>
#include<QTextEdit>

QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->resize(1000, 700);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    createMenuPage();
    createGamePage();

    stackedWidget->addWidget(menuPage);
    stackedWidget->addWidget(gamePage);

    loadRecords();

    stackedWidget->setCurrentWidget(menuPage);
}
void QtWidgetsApplication1::createMenuPage()
{
    menuPage = new QWidget(this);

    menuPage->setObjectName("menuPage");
    menuPage->setStyleSheet(
        "#menuPage {"
        "background-image: url(:/Image.png);"
        "background-position: center;"
        "background-repeat: no-repeat;"
        "}"
    );

    QVBoxLayout* layout = new QVBoxLayout(menuPage);
    layout->setAlignment(Qt::AlignCenter);

    QLabel* title = new QLabel("\351\255\224\346\226\271\350\256\255\347\273\203\345\231\250");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 42px; font-weight: bold; color: white;");

    QPushButton* btnPractice = new QPushButton("Practice Mode");
    QPushButton* btnChallenge = new QPushButton("Challenge Mode");
    QPushButton* btnHelp = new QPushButton("Help");
    QPushButton* btnExit = new QPushButton("Exit");

    QString menuBtnStyle =
        "QPushButton {"
        "font-size: 22px;"
        "min-width: 280px;"
        "min-height: 58px;"
        "border-radius: 12px;"
        "background-color: rgba(30, 30, 40, 190);"
        "color: white;"
        "border: 1px solid rgba(255,255,255,100);"
        "}"
        "QPushButton:hover {"
        "background-color: rgba(60, 90, 150, 220);"
        "}"
        "QPushButton:pressed {"
        "background-color: rgba(30, 60, 120, 230);"
        "}";

    btnPractice->setStyleSheet(menuBtnStyle);
    btnChallenge->setStyleSheet(menuBtnStyle);
    btnHelp->setStyleSheet(menuBtnStyle);
    btnExit->setStyleSheet(menuBtnStyle);

    layout->addWidget(title);
    layout->addSpacing(40);
    layout->addWidget(btnPractice, 0, Qt::AlignCenter);
    layout->addWidget(btnChallenge, 0, Qt::AlignCenter);
    layout->addWidget(btnHelp, 0, Qt::AlignCenter);
    layout->addWidget(btnExit, 0, Qt::AlignCenter);

    connect(btnPractice, &QPushButton::clicked, this, [=]() {
        enterGame(false);
        });

    connect(btnChallenge, &QPushButton::clicked, this, [=]() {
        enterGame(true);
        });

    connect(btnHelp, &QPushButton::clicked, this, [=]() {
        QDialog dialog(this);
        dialog.setWindowTitle("Help");
        dialog.resize(650, 520);

        QVBoxLayout* layout = new QVBoxLayout(&dialog);

        QTextEdit* textEdit = new QTextEdit();
        textEdit->setReadOnly(true);
        textEdit->setStyleSheet(
            "font-size: 16px;"
            "background-color: #f5f5f5;"
            "color: #222222;"
        );

        QFile file(":/help.txt");

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray data = file.readAll();
            QString helpText = QString::fromUtf8(data);
            textEdit->setText(helpText);
            file.close();
        }
        else {
            textEdit->setText("Failed to load help.txt.\nPlease make sure help.txt is in the program running directory.");
        }

        QPushButton* btnClose = new QPushButton("Close");
        btnClose->setStyleSheet("font-size: 16px; min-height: 38px;");

        layout->addWidget(textEdit);
        layout->addWidget(btnClose);

        connect(btnClose, &QPushButton::clicked, &dialog, [&]() {
            dialog.accept();
            });

        dialog.exec();
        });

    connect(btnExit, &QPushButton::clicked, this, [=]() {
        close();
        });
}
void QtWidgetsApplication1::createGamePage()
{
    gamePage = new QWidget(this);

    QVBoxLayout* outerLayout = new QVBoxLayout(gamePage);
    QString btnStyle = "font-size: 18px; min-height: 50px;";

    ui.btnU->setStyleSheet(btnStyle);
    ui.btnR->setStyleSheet(btnStyle);
    ui.btnF->setStyleSheet(btnStyle);
    ui.btnL->setStyleSheet(btnStyle);
    ui.btnD->setStyleSheet(btnStyle);
    ui.btnB->setStyleSheet(btnStyle);
    ui.btnScramble->setStyleSheet(btnStyle);
    ui.btnView->setStyleSheet(btnStyle);
   

    //  ¶¥²¿×´Ì¬À¸ 
    QHBoxLayout* statusLayout = new QHBoxLayout();

    lblTitle = new QLabel("\351\255\224\346\226\271\350\256\255\347\273\203\345\231\250");
    lblStatus = new QLabel("Status: Ready");
    lblTime = new QLabel("Time: 0.00s");
    lblView = new QLabel("View: Front");

    QString labelStyle = "font-size: 20px; font-weight: bold; color: white;";

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

    QHBoxLayout* mainlayout = new QHBoxLayout(gamePage);
    QVBoxLayout* cubeAreaLayout = new QVBoxLayout();
    cubeWidget = new CubeWidget(this);
    cubeAreaLayout->addWidget(cubeWidget);
    QHBoxLayout* extraButtonLayout = new QHBoxLayout();

    QPushButton* btnBackMenu = new QPushButton("\350\277\224\345\233\236\350\217\234\345\215\225");
    btnBackMenu->setStyleSheet(btnStyle);

    ui.btnRecord->setStyleSheet(btnStyle);

    extraButtonLayout->addWidget(btnBackMenu);
    extraButtonLayout->addWidget(ui.btnRecord);
    extraButtonLayout->addStretch();   // ÈÃ°´Å¥¿¿×ó

    cubeAreaLayout->addLayout(extraButtonLayout);
    mainlayout->addLayout(cubeAreaLayout, 4);
    QVBoxLayout* layout = new QVBoxLayout();
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
        showRecordsDialog();
        });
    connect(ui.btnScramble, &QPushButton::clicked, this, [=]() {
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
            cubeWidget->cube = Cube();
            cubeWidget->update();
            gameStarted = false; 
            waitingFirstMove = false;
            if (challengeMode) {
                statusText = "Ready";
                setMoveButtonsEnabled(false);
            }
            else {
                statusText = "Ready";
                setMoveButtonsEnabled(true);
            }
            updateStatusLabels();
        }
        else
        {
            cubeWidget->cube.scramble(30);
            cubeWidget->update();
            if (challengeMode) {
                timer.start();
                gameStarted = false;
                waitingFirstMove = true;
                statusText = "Observing";
                setMoveButtonsEnabled(true);
            }else{
                gameStarted = false;
                waitingFirstMove = false;
                statusText = "Practice";
            }
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
    connect(btnBackMenu, &QPushButton::clicked, this, [=]() {
        gameStarted = false;
        waitingFirstMove = false;
        statusText = "Ready";

        cubeWidget->cube = Cube();
        cubeWidget->update();

        updateStatusLabels();

        stackedWidget->setCurrentWidget(menuPage);
        });
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

    if (challengeMode&&gameStarted && cubeWidget->cube.isSolved()) {
        gameStarted = false;
        statusText = "Solved";
        setMoveButtonsEnabled(false);

        double seconds = timer.elapsed() / 1000.0;
        solveTimes.push_back(seconds);
        bool isNewRecord = false;
        if (bestTime < 0 || seconds < bestTime) {
            bestTime = seconds;
            isNewRecord = true;
        }

        saveRecords();

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
void QtWidgetsApplication1::enterGame(bool challenge)
{
    challengeMode = challenge;

    cubeWidget->cube = Cube();
    cubeWidget->update();

    gameStarted = false;
    waitingFirstMove = false;

    if (challengeMode) {
        statusText = "Ready";
        setMoveButtonsEnabled(false);
    }
    else {
        statusText = "Ready";
        setMoveButtonsEnabled(true);
    }

    ui.btnRecord->setVisible(challengeMode);
    updateStatusLabels();

    stackedWidget->setCurrentWidget(gamePage);
}
void QtWidgetsApplication1::setMoveButtonsEnabled(bool enabled)
{
    ui.btnU->setEnabled(enabled);
    ui.btnR->setEnabled(enabled);
    ui.btnF->setEnabled(enabled);
    ui.btnL->setEnabled(enabled);
    ui.btnD->setEnabled(enabled);
    ui.btnB->setEnabled(enabled);
}
void QtWidgetsApplication1::loadRecords()
{
    solveTimes.clear();
    bestTime = -1.0;

    QFile file("records.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) {
            continue;
        }

        bool ok = false;
        double time = line.toDouble(&ok);

        if (ok) {
            solveTimes.push_back(time);

            if (bestTime < 0 || time < bestTime) {
                bestTime = time;
            }
        }
    }

    file.close();
}
void QtWidgetsApplication1::saveRecords()
{
    QFile file("records.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < solveTimes.size(); i++) {
        out << QString::number(solveTimes[i], 'f', 2) << "\n";
    }

    file.close();
}
void QtWidgetsApplication1::recalculateBestTime()
{
    bestTime = -1.0;

    for (double t : solveTimes) {
        if (bestTime < 0 || t < bestTime) {
            bestTime = t;
        }
    }
}
void QtWidgetsApplication1::showRecordsDialog()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Records");
    dialog.resize(420, 360);

    QPushButton* btnDelete = new QPushButton("Delete Selected");
    QPushButton* btnClear = new QPushButton("Clear All");
    QPushButton* btnClose = new QPushButton("Close");
    btnDelete->setEnabled(false);

    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);

    QLabel* title = new QLabel("Solve Records");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 22px; font-weight: bold;");

    QLabel* bestLabel = new QLabel();
    bestLabel->setAlignment(Qt::AlignCenter);

    if (bestTime < 0) {
        bestLabel->setText("Best Time: --");
    }
    else {
        bestLabel->setText(QString("Best Time: %1 s").arg(bestTime, 0, 'f', 2));
    }

    bestLabel->setStyleSheet("font-size: 16px;");

    QTableWidget* table = new QTableWidget();
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList() << "No." << "Time");

    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(table->selectionModel(), &QItemSelectionModel::selectionChanged,
        &dialog, [=]() {
            bool hasSelection = !table->selectionModel()->selectedRows().isEmpty();
            btnDelete->setEnabled(hasSelection);
        });
    table->setRowCount(solveTimes.size());

    for (int i = 0; i < solveTimes.size(); i++) {
        QTableWidgetItem* indexItem = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem* timeItem = new QTableWidgetItem(
            QString("%1 s").arg(solveTimes[i], 0, 'f', 2)
        );

        indexItem->setTextAlignment(Qt::AlignCenter);
        timeItem->setTextAlignment(Qt::AlignCenter);

        table->setItem(i, 0, indexItem);
        table->setItem(i, 1, timeItem);
    }

    table->clearSelection();
    table->setCurrentCell(-1, -1);
    btnDelete->setEnabled(false);

    QString btnStyle = "font-size: 14px; min-height: 35px;";
    btnDelete->setStyleSheet(btnStyle);
    btnClear->setStyleSheet(btnStyle);
    btnClose->setStyleSheet(btnStyle);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(btnDelete);
    buttonLayout->addWidget(btnClear);
    buttonLayout->addStretch();
    buttonLayout->addWidget(btnClose);

    mainLayout->addWidget(title);
    mainLayout->addWidget(bestLabel);
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);

    connect(btnDelete, &QPushButton::clicked, &dialog, [&]() {
        QModelIndexList selectedRows = table->selectionModel()->selectedRows();

        if (selectedRows.isEmpty()) {
            QMessageBox::information(&dialog, "Records", "Please select a record first.");
            return;
        }

        int row = selectedRows.first().row();

        if (row < 0 || row >= solveTimes.size()) {
            QMessageBox::information(&dialog, "Records", "Invalid selection.");
            return;
        }

        solveTimes.removeAt(row);
        recalculateBestTime();
        saveRecords();

        table->removeRow(row);

        for (int i = 0; i < table->rowCount(); i++) {
            table->item(i, 0)->setText(QString::number(i + 1));
        }

        table->clearSelection();
        table->setCurrentCell(-1, -1);
        btnDelete->setEnabled(false);

        if (bestTime < 0) {
            bestLabel->setText("Best Time: --");
        }
        else {
            bestLabel->setText(QString("Best Time: %1 s").arg(bestTime, 0, 'f', 2));
        }
        });

    connect(btnClear, &QPushButton::clicked, &dialog, [&]() {
        solveTimes.clear();
        bestTime = -1.0;
        saveRecords();

        table->setRowCount(0);
        bestLabel->setText("Best Time: --");
        });

    connect(btnClose, &QPushButton::clicked, &dialog, [&]() {
        dialog.accept();
        });

    dialog.exec();
}
QtWidgetsApplication1::~QtWidgetsApplication1()
{}

