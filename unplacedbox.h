#ifndef UNPLACEDBOX_H
#define UNPLACEDBOX_H

#include <QLabel>

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
    QPoint dragBoxPoint;

    int id;

public:
    UnPlacedBox(Project* project, int id, QString text, QPoint pos);
    ~UnPlacedBox();

    int getId() { return id; }

    void checkDrop(QPoint point);
    void remove();

    QPoint getDragBoxPoint() { return dragBoxPoint; }
    void show(bool x);
    void reset();
};

#endif // UNPLACEDBOX_H
