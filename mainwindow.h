#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "projectsmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    ProjectsManager* projectsManager; //the pointer to store main projectsManager

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openProjectButton_clicked(); //caused after the user clicked the open button in the homepage
    void on_addNewButton_clicked(); //caused after the user clicked the button in the homepage
    void on_finalAddButton_clicked(); //caused after the user clicked the button in the addpage
    void on_cancelAddingButton_clicked(); //caused after the user clicked the button in the addpage
    void on_saveButton_clicked(); //caused after the user clicked the save  button in the edit page
    void on_editingQuitButton_clicked(); //caused after the user clicked the button in the editpage
    void on_addStringButton_clicked(); //casued after the user clicked the add button in the editpage
    void on_stringValueLine_textEdited(const QString &arg1); //caused after the user edit string in Edit line
    void on_stringValueLine_returnPressed(); // caused after the user pressed Enter on focused Edit line
};

#endif // MAINWINDOW_H
