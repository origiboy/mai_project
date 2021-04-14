#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}


void MainWindow::keyPressEvent(QKeyEvent *event) {
 int key=event->key();
 QString str = QString(QChar(key));
 if (key == Qt::Key_Up) {
  int x = ui->tank->x();
  int y = ui->tank->y();
  ui->tank->setGeometry(x, y-10, 60, 60);
 }
 if (key == Qt::Key_Down) {
  int x = ui->tank->x();
  int y = ui->tank->y();
  ui->tank->setGeometry(x, y+10, 60, 60);
 }

}

MainWindow::~MainWindow()
{
    delete ui;
}
