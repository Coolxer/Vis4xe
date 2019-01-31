#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statesStackedWidget->setCurrentIndex(0);

    ui->name_alert->setVisible(false);
    ui->cols_alert->setVisible(false);
    ui->rows_alert->setVisible(false);

    projectsManager = new ProjectsManager(ui->homePage, ui->editPage, ui->statesStackedWidget, ui->projectsExists);
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

    bool valid = true;

    if(name.isEmpty())
    {
        ui->name_alert->setVisible(true);
        valid = false;
    }
    else
        ui->name_alert->setVisible(false);

    if(cols < 1 || cols > 28 || cols - int(cols) !=0)
    {
        ui->cols_alert->setVisible(true);
        valid = false;
    }
    else
         ui->cols_alert->setVisible(false);

    if(rows <= 0 || rows > 10 || rows - int(rows) !=0)
    {
        ui->rows_alert->setVisible(true);
        valid = false;
    }
    else
        ui->rows_alert->setVisible(false);

    //need to be validators here

    if(valid)
    {
        projectsManager->createProject(name, rows, cols);
        ui->statesStackedWidget->setCurrentIndex(2);

        ui->nameLineEdit->clear();
        ui->rowsLineEdit->clear();
        ui->colsLineEdit->clear();

        ui->name_alert->setVisible(false);
        ui->cols_alert->setVisible(false);
        ui->rows_alert->setVisible(false);

        ui->stringValueLine->setMaxLength(cols);
    }
}


void MainWindow::on_cancelAddingButton_clicked()
{
    ui->statesStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_editingQuitButton_clicked()
{
    projectsManager->releaseProject();
    ui->statesStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_editingQuitWithSaveButton_clicked()
{
     projectsManager->saveProject();
     projectsManager->releaseProject();
     ui->statesStackedWidget->setCurrentIndex(0);   
}

void MainWindow::on_addStringButton_clicked()
{
    QString string = ui->stringValueLine->text();

    //checks if the string is not empty
    if(string.length() > 0)
    {
        projectsManager->getCurrentProject()->getStringsWidget()->addStringWidget(string);
        ui->stringValueLine->clear();
    }
}


