#ifndef PROJECT_H
#define PROJECT_H

#include <QWidget>
#include <QLabel>

#include "lcd.h"
#include "stringslistwidget.h"

class QPushButton;
class Cell;

class Project
{
private:
    QPushButton* sBtn; //the pointer to the save button

    QLabel* projectNameBox; //the box which is displaying project name in editpage upper crossbar
    QWidget* container; //the widget for storing others widgets like lcd and stringsWidget
    Lcd* lcd; //pointer of lcd, for keeping dynamic object
    StringsListWidget* stringsWidget;  //pointer of stringsListWidget, for keeping dynamic object

    QString name; //name of the project

    QString dirPath; //path where folder with project is placed
    QString visPath; //path where the *.json file is placed
    QString avrPath; //path where the *.txt file is placed (Arduino)

public:
    Project(){}
    Project(QString name, unsigned short rows, unsigned short cols, QWidget* widget, QPushButton* btn);
    ~Project();

    QWidget* getContainer() { return container; }
    Lcd* getLcd() { return lcd; }
    StringsListWidget* getStringsWidget() { return stringsWidget; }

    QString getName() { return name; }
    QString getDirPath() { return dirPath; }
    QString getVisPath() { return visPath; }
    QString getAvrPath() { return avrPath; }

    bool check(QPoint point); //the method checks if the dragBoxPoint is over any cell and returns TRUE if it is or otherwise FALSE
    bool writeOnLcd(UnPlacedBox* box); //the function is drawing the text from unplacedBox on lcd    
    void setPath(QString path); //the function that prepares the paths of the files
    void setSaved(bool x); //turns on that the user made changes which are not saved yet

};

#endif // PROJECT_H
