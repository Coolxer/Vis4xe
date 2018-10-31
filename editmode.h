#ifndef EDITMODE_H
#define EDITMODE_H

#include <QString>

#include <QDebug>

class Lcd;

class EditMode
{
private:
    Lcd* lcd;
    QString string;

public:
    EditMode(Lcd* lcd, QString string);
    ~EditMode();
};

#endif // EDITMODE_H
