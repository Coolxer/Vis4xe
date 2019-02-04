#ifndef DELBOX_H
#define DELBOX_H

#include <QApplication>
#include <QLabel>
#include <QPoint>

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
