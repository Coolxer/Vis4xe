#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QColor>

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

#include <QKeyEvent>

#include <QLabel>

#include "projectslist.h"
#include "filemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    ProjectsList* projectsList;

    FileManager* fileManager;

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
};

#endif // MAINWINDOW_H
