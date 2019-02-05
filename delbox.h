#ifndef DELBOX_H
#define DELBOX_H

#include <QApplication>
#include <QLabel>
#include <QPoint>

class UnPlacedBox;

class DelBox : public QLabel
{
private:
    UnPlacedBox* unPlacedBox; //the pointer to its parent

    QPoint startPosition; //the start Position of the delBox

    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
public:
    DelBox(){}
    DelBox(UnPlacedBox* unPlacedBox, QWidget* parent, QPoint pos);

    void reset(); //the function that's moving this box to the start Postion

};

#endif // DELBOX_H
