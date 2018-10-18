#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addNewButton_clicked();

    void on_finalAddButton_clicked();

    void on_cancelAddingButton_clicked();

    void on_editingQuitButton_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
