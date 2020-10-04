#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "Widgets/D2DWidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(new D2DWidget(this));
    connectSignals();
}

MainWindow::~MainWindow()
{

}

void MainWindow::connectSignals()
{
}