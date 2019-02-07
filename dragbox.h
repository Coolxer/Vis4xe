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

    QPoint startPosition; //start Position of the DragBox
    QPoint offset; //the offset, /\ delta movement
    QPoint lastPosition; //the lastPostion that was registered

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
public:
    DragBox(){}
    DragBox(UnPlacedBox* unPlacedBox, QPoint pos);

    void reset();  //the function that's moving this box to the start Postion

    void setStartPosition(QPoint point) { startPosition = point; }
};

#endif // DRAGBOX_H
