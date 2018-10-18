#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statesStackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addNewButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(1);
}

void MainWindow::on_finalAddButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(2);
}

void MainWindow::on_cancelAddingButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_editingQuitButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(0);
}
