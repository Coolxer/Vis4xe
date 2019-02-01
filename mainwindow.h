#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>

#include "projectsmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    ProjectsManager* projectsManager;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addNewButton_clicked(); //caused after the user clicked the button in the homepage
    void on_finalAddButton_clicked(); //caused after the user clicked the button in the addpage
    void on_cancelAddingButton_clicked(); //caused after the user clicked the button in the addpage
    void on_editingQuitButton_clicked(); //caused after the user clicked the button in the editpage

    void on_addStringButton_clicked();
    void on_editingQuitWithSaveButton_clicked();
    void on_openProjectButton_clicked();
};

#endif // MAINWINDOW_H
