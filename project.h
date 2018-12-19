#ifndef PROJECT_H
#define PROJECT_H

#include <QDebug>
#include <QString>

#include "lcd.h"
#include <QVector>

#include "unplacedbox.h"

#include <QJsonObject>

class QWidget;
class Cell;

class Project
{
private:
    QWidget* widget; //the pointer to the main widget to draw Lcd, and Unplaced string boxes
    QString name; //name of the project

    Lcd* lcd; //the pointer / dynamic object Lcd

    //QStringList unPlacedStrings; //the vector of the strings that are not placed in yet

    QVector <UnPlacedBox*> unPlacedBoxes; //the vector of of the boxes that are not placed in ( they are on the strings side menu)

    QJsonObject jsonObject;

public:
    Project(){}
    Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Project();

    QString getName() { return name; }// the latest thing to dispaly also on the home page
    int getRows(){ return lcd->getRowsAmount(); }
    int getCols(){ return lcd->getColsAmount(); }
    QString getColor() { return lcd->getColor().name(); }

    void addString(QString string); //the function that will call after click the add button on the strings
                      // menu. The procedure must get the value of the input field
                      // This function is like a slot but not sure its good idea
                      // its adding the inputted string to the unPlacedStrings vector

    bool writeOnLcd(UnPlacedBox* box); //the function is drawing the text from unplacedBox

    bool check(QPoint point);

    Lcd* getLcd() { return lcd; }

    void organizeBoxes(UnPlacedBox* box);

    void loadUnplacedBoxes(QVector <UnPlacedBox*> unPlacedBoxes);
    void loadCells(QVector<Cell*> cells);

    int getNumberOfUnplacedBoxes(){ return unPlacedBoxes.length(); }

    UnPlacedBox* getUnplacedBox(int i) { return unPlacedBoxes[i]; }
};

#endif // PROJECT_H
