#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

#include "lcd.h"
#include "stringslist.h"

class Project
{
private:
    QString name;

    Lcd lcd;
    StringsList stringsList;
public:
    Project(){}
    Project(QString name, unsigned short rows, unsigned short cols, QColor color);

    QString getName() { return name; };

};

#endif // PROJECT_H
