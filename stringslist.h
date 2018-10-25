#ifndef STRINGSLIST_H
#define STRINGSLIST_H

#include <QString>
#include <QVector>
#include <QWidget>

#include "draggablelabel.h"
#include <QtDebug>

class StringsList
{
private:
    QVector <DraggableLabel*> list;

    QWidget* widget;
public:
    StringsList(QWidget* widget);
    ~StringsList();

    void addString(QString string);
    void deleteString(DraggableLabel* label);
    void changeString(DraggableLabel* label, QString newString);

    void showList();
};

#endif // STRINGSLIST_H
