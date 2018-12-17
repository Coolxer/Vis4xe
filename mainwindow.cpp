#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statesStackedWidget->setCurrentIndex(0);

    projectsManager = new ProjectsManager(ui->homePage, ui->editPage, ui->statesStackedWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete projectsManager;
}

void MainWindow::on_addNewButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(1);
}

void MainWindow::on_finalAddButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    unsigned short rows = ui->rowsLineEdit->text().toShort();
    unsigned short cols = ui->colsLineEdit->text().toShort();

    //need to be validators here

    //color there should be a circle switch
    projectsManager->createProject(name, rows, cols, Qt::red);

    ui->statesStackedWidget->setCurrentIndex(2);
}

void MainWindow::on_cancelAddingButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_editingQuitButton_clicked()
{
    projectsManager->getCurrentProject()->del();
    ui->statesStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_editingQuitWithSaveButton_clicked()
{
     projectsManager->saveProject();
     ui->statesStackedWidget->setCurrentIndex(0);   
}

void MainWindow::on_addStringButton_clicked()
{
    QString string = ui->stringValueLine->text();

    //checks if the string is not empty
    if(string.length() > 0)
        projectsManager->getCurrentProject()->addString(string);
}

