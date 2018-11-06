#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statesStackedWidget->setCurrentIndex(2);

    projectsList = new ProjectsList();


    // its move there for faster developing ( not needed to click all the time through pages)
    QString name = ui->nameLineEdit->text();
    unsigned short rows = ui->rowsLineEdit->text().toInt();
    unsigned short cols = ui->colsLineEdit->text().toInt();

    project = new Project(name, rows, cols, Qt::red, ui->editPage);

    ui->statesStackedWidget->setCurrentIndex(2);

    //setAcceptDrops(true);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete projectsList;
    delete project;
}

void MainWindow::on_addNewButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(1);
}

void MainWindow::on_finalAddButton_clicked()
{
    /*
    QString name = ui->nameLineEdit->text();
    unsigned short rows = ui->rowsLineEdit->text().toInt();
    unsigned short cols = ui->colsLineEdit->text().toInt();

    project = new Project(name, rows, cols, Qt::red, ui->editPage);

    ui->statesStackedWidget->setCurrentIndex(2);
    */
}

void MainWindow::on_cancelAddingButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_editingQuitButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_addStringButton_clicked()
{
    QString string = ui->stringValueLine->text();

    //checks if the string is not empty
    //if(string.length() > 0)
    project->addString(string);
}
