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
    Project* project; //the pointer to the project
    QWidget* listWidget; //the pointer to its parent

    DragBox* dragBox; //the dynamic object of DragBox
    DelBox* delBox; // the dynamic object of DelBox

    QPoint startPosition; //the startPosition of the UnplacedBox text box
    QPoint dragBoxPoint; // the position of the DragBox

    int id; //the id of the unplacedBox in the StringsListWidget
    int index;

public:
    UnPlacedBox(Project* project, int index, int id, QString text, QPoint pos);
    ~UnPlacedBox();

    int getId() { return id; }
    int getIndex() { return index; }

    void checkDrop(QPoint point); //
    void remove();

    QPoint getDragBoxPoint() { return dragBoxPoint; }
    void show(bool x);
    void reset(); //the function that moves the box to the start position

    void decrease() { index--; }
    void moveTo(QPoint p);

};

#endif // UNPLACEDBOX_H
