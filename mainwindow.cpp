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

    ui->addStringButton->setStyleSheet("QPushButton{border: 2px solid #808080; color: #808080; border-radius:30; font-size: 20px; opacity: 0.5;}");

    projectsManager = new ProjectsManager(ui->homePage, ui->editPage, ui->statesStackedWidget, ui->projectsExists, ui->saveButton);
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
    int rows = ui->rowsLineEdit->text().toInt();
    int cols = ui->colsLineEdit->text().toInt();

    bool valid = true;

    if(name.isEmpty())
    {
        ui->name_alert->setVisible(true);
        valid = false;
    }
    else
        ui->name_alert->setVisible(false);

    if(cols < 1 || cols > 24 || cols - int(cols) !=0)
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
    projectsManager->readBoxes();
    ui->statesStackedWidget->setCurrentIndex(0); 
}

void MainWindow::on_editingQuitButton_clicked()
{
    projectsManager->releaseProject();
    ui->statesStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_addStringButton_clicked()
{
    if(projectsManager->getCurrentProject()->getStringsWidget()->getAmount() >= 10)
        return;

    QString string = ui->stringValueLine->text();

    projectsManager->getCurrentProject()->getStringsWidget()->addStringWidget(string);
    ui->stringValueLine->clear();

    ui->addStringButton->setEnabled(false);
    ui->addStringButton->setStyleSheet("QPushButton{border: 2px solid #808080; color: #808080; border-radius:30; font-size: 20px; opacity: 0.5;}");
}

void MainWindow::on_openProjectButton_clicked()
{
    projectsManager->loadProject(nullptr, "");
}

void MainWindow::on_saveButton_clicked()
{
    projectsManager->saveProject();
}

void MainWindow::on_stringValueLine_textEdited(const QString &arg1)
{
    if(projectsManager->getCurrentProject()->getStringsWidget()->getAmount() >= 10)
        return;

    if(arg1.isEmpty())
    {
        ui->addStringButton->setEnabled(false);
        ui->addStringButton->setStyleSheet("QPushButton{border: 2px solid #808080; color: #808080; border-radius:30; font-size: 20px; opacity: 0.5;}");
    }
    else
    {
        ui->addStringButton->setEnabled(true);
        ui->addStringButton->setStyleSheet("QPushButton{ border: 2px solid #0099ff; color: #0099ff;  border-radius:30px; font-size:20px;} QPushButton:hover{ background-color: #0099ff; color: #333333; }");
    }
}

void MainWindow::on_stringValueLine_returnPressed()
{
    if(projectsManager->getCurrentProject()->getStringsWidget()->getAmount() >= 10)
        return;

    QString string = ui->stringValueLine->text();

    projectsManager->getCurrentProject()->getStringsWidget()->addStringWidget(string);
    ui->stringValueLine->clear();

    ui->addStringButton->setEnabled(false);
    ui->addStringButton->setStyleSheet("QPushButton{border: 2px solid #808080; color: #808080; border-radius:30; font-size: 20px; opacity: 0.5;}");
}
