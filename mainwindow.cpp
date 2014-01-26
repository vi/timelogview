#include "mainwindow.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QCPGraph* g = ui->plot->addGraph();
    g->addData(1,2);
    g->addData(2,3);
    g->addData(3,1);
    g->addData(13,1);
    ui->plot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
