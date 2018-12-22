#ifndef PROJECT_H
#define PROJECT_H

#include <QDebug>
#include <QString>

#include "lcd.h"
#include "stringslistwidget.h"

class QWidget;
class Cell;

class Project
{
private:
    QWidget* widget; //the pointer to the main widget to draw Lcd, and Unplaced string boxes
    QString name; //name of the project

    Lcd* lcd; //the pointer / dynamic object Lcd
    StringsListWidget* stringsWidget;

public:
    Project(){}
    Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Project();

    QString getName() { return name; }// the latest thing to dispaly also on the home page

    Lcd* getLcd() { return lcd; }
    StringsListWidget* getStringsWidget() { return stringsWidget; }


    bool check(QPoint point);
    bool writeOnLcd(UnPlacedBox* box); //the function is drawing the text from unplacedBox


    void loadUnplacedBoxes(QVector <UnPlacedBox*> unPlacedBoxes);
    void loadCells(QVector<Cell*> cells);
};

#endif // PROJECT_H
