#ifndef STRINGSLIST_H
#define STRINGSLIST_H

#include <QString>
#include <QVector>
#include <QWidget>

#include "mylabel.h"

class StringsList
{
private:
    QVector <MyLabel*> list;

    QWidget* widget;
public:
    StringsList(QWidget* widget);
    ~StringsList();

    void addString(QString string);
    void deleteString(MyLabel* label);
    void changeString(MyLabel* label, QString newString);
};

#endif // STRINGSLIST_H
