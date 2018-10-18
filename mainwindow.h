#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QColor>

#include "projectslist.h"
#include "project.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    ProjectsList* projectsList;
    Project* project;

    void getValues();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addNewButton_clicked();
    void on_finalAddButton_clicked();
    void on_cancelAddingButton_clicked();
    void on_editingQuitButton_clicked();
};

#endif // MAINWINDOW_H
