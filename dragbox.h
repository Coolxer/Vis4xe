#ifndef DRAGBOX_H
#define DRAGBOX_H

#include <QApplication>
#include <QMouseEvent>
#include <QLabel>

class UnPlacedBox;

class DragBox : public QLabel
{
private:
    UnPlacedBox* unPlacedBox;

    QPoint startPosition;
    QPoint offset;
    QPoint lastPosition;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
public:
    DragBox(){}
    DragBox(UnPlacedBox* unPlacedBox, QWidget* parent, QPoint pos);

    void reset();
};

#endif // DRAGBOX_H
