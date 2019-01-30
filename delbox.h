#ifndef DELBOX_H
#define DELBOX_H

#include <QLabel>
#include <QPoint>

#include <QMouseEvent>
#include <QApplication>

class UnPlacedBox;

class DelBox : public QLabel
{
private:
    UnPlacedBox* unPlacedBox;

    QPoint startPosition;

    void mousePressEvent(QMouseEvent* event);

    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
public:
    DelBox(){}
    DelBox(UnPlacedBox* unPlacedBox, QWidget* parent, QPoint pos);

    void reset();

};

#endif // DELBOX_H
