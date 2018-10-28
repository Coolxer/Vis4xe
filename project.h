#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

#include "lcd.h"
#include "stringslist.h"

#include <QStringList>

class QWidget;

class Project
{
private:
    QString name;

    Lcd* lcd;
    StringsList* stringsList;

    QStringList placedStrings;
    QStringList unPlacedStrings;
public:
    Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Project();

    QString getName() { return name; };

};

#endif // PROJECT_H
