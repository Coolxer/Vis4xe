#ifndef DRAGBOX_H
#define DRAGBOX_H

#include <QLabel>

class DragBox : public QLabel
{
private:

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
public:
    DragBox();
};

#endif // DRAGBOX_H
