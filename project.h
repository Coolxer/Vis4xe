#ifndef PROJECT_H
#define PROJECT_H

#include <QWidget>

#include "lcd.h"
#include "stringslistwidget.h"

#include <QLabel>

#include <QtDebug>

class QPushButton;

class Cell;

class Project
{
private:
    QLabel* projectNameBox; //the box which is displaying project name in editpage upper crossbar
    QWidget* container; //the widget for storing others widgets like lcd and stringsWidget
    QString name; //name of the project

    QString dirPath; //path where folder with project is placed
    QString visPath; //path where the *.json file is placed
    QString avrPath; //path where the *.txt file is placed (Arduino)

    Lcd* lcd; //pointer of lcd, for keeping dynamic object
    StringsListWidget* stringsWidget;  //pointer of stringsListWidget, for keeping dynamic object

    QPushButton* sBtn;

public:
    Project(){}
    Project(QString name, unsigned short rows, unsigned short cols, QWidget* widget, QPushButton* btn);
    ~Project();

    QString getName() { return name; }

    void setPath(QString path); //the function that prepares the paths of the files

    QString getDirPath() { return dirPath; }
    QString getVisPath() { return visPath; }
    QString getAvrPath() { return avrPath; }

    Lcd* getLcd() { return lcd; }
    StringsListWidget* getStringsWidget() { return stringsWidget; }

    bool check(QPoint point); //the method checks if the dragBoxPoint is over any cell and returns TRUE if it is or otherwise FALSE
    bool writeOnLcd(UnPlacedBox* box); //the function is drawing the text from unplacedBox on lcd

    void loadUnplacedBoxes(QVector <UnPlacedBox*> unPlacedBoxes); //using to load UnplacedBoxes from *.json file
    void loadCells(QVector<Cell*> cells); //using to load cells from *.json file

    QWidget* getContainer() { return container; }

    void setSaved(bool x);

};

#endif // PROJECT_H
