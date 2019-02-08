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

    int id; //the id of the unplacedBox in the StringsList (->Lcd)
    int index; //the index of the unplacedBox in the StringsList

public:
    UnPlacedBox(Project* project, int index, int id, QString text, QPoint pos);
    ~UnPlacedBox();

    int getId() { return id; }
    int getIndex() { return index; }
    QPoint getDragBoxPoint() { return dragBoxPoint; }

    void checkDrop(QPoint point); //checks the dragBox position
    void remove(); //gives a signal to its parent to delete itself
    void show(bool x); //the function to show/hide drag & unplaced & del [boxes]
    void reset(); //the function that moves the box to the start position
    void decrease() { index--; } //decreases the index of the unplacedBox after removed another
    void moveTo(QPoint p); //moves the box one level up

};

#endif // UNPLACEDBOX_H
