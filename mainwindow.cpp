#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("学生管理系统");
    this->setMaximumSize(800, 500);
    this->setMinimumSize(800, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

