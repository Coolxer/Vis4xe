#ifndef PROJECT_H
#define PROJECT_H


#include <QDebug>
#include <QWidget>

#include "lcd.h"
#include "stringslistwidget.h"

#include <QLabel>

class Cell;

class Project
{
private:
    QLabel* projectNameBox; //the box which is displaying project name in editpage upper crossbar
    QWidget* container; //the widget for storing others widgets like lcd and stringsWidget
    QString name; //name of the project

    Lcd* lcd; //pointer of lcd, for keeping dynamic object
    StringsListWidget* stringsWidget;  //pointer of stringsListWidget, for keeping dynamic object

public:
    Project(){}
    Project(QString name, unsigned short rows, unsigned short cols, QWidget* widget);
    ~Project();

    QString getName() { return name; }

    Lcd* getLcd() { return lcd; }
    StringsListWidget* getStringsWidget() { return stringsWidget; }

    bool check(QPoint point);
    bool writeOnLcd(UnPlacedBox* box); //the function is drawing the text from unplacedBox

    void loadUnplacedBoxes(QVector <UnPlacedBox*> unPlacedBoxes); //using to load UnplacedBoxes from *.json file
    void loadCells(QVector<Cell*> cells); //using to load cells from *.json file

    QWidget* getContainer() { return container; }

};

#endif // PROJECT_H
