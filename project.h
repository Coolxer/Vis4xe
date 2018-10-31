#ifndef PROJECT_H
#define PROJECT_H

#include <QDebug>
#include <QString>

#include "lcd.h"
#include <QVector>

#include <QStringList>

#include "unplacedbox.h"

class QWidget;

class Project
{
private:
    QWidget* widget; //the pointer to the main widget to draw Lcd, and Unplaced string boxes
    QString name; //name of the project

    Lcd* lcd; //the pointer / dynamic object Lcd

    QStringList placedStrings; //the vector of the strings that are placed in
    //QStringList unPlacedStrings; //the vector of the strings that are not placed in yet

    QVector <UnPlacedBox*> unPlacedBoxes; //the vector of of the boxes that are not placed in ( they are on the strings side menu)

public:
    Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Project();

    QString getName() { return name; }; // the latest thing to dispaly also on the home page

    void addString(QString string); //the function that will call after click the add button on the strings
                      // menu. The procedure must get the value of the input fields
                      // This function is like a slot but not sure its good idea
                      // its adding the inputted string to the unPlacedStrings vector

    bool writeOnLcd(QString string, QPoint point, int id); //the function which is drawing dropped text on LCD
                       //returns true if its succeed (free space)

    bool check(QPoint point);

    Lcd* getLcd() { return lcd; };
};

#endif // PROJECT_H
