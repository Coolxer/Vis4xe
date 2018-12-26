#ifndef UNPLACEDBOX_H
#define UNPLACEDBOX_H

#include <QLabel>
#include <QString>
#include <QPoint>

#include <QtDebug>

#include "dragbox.h"
#include "delbox.h"

class Project;
class QWidget;

class UnPlacedBox : public QLabel
{
private:
    Project* project;
    QWidget* listWidget;

    DragBox* dragBox;
    DelBox* delBox;

    QPoint startPosition;

    int id;

public:
    UnPlacedBox(Project* project, int id, QString text, QPoint pos);
    ~UnPlacedBox();

    int getId() { return id; }
    QString getValue() { return text(); }

    void checkDrop(QPoint point);
    void remove();

};

#endif // UNPLACEDBOX_H
