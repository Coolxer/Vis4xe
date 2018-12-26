#include "dragbox.h"

#include "unplacedbox.h"

DragBox::DragBox(UnPlacedBox* unPlacedBox, QWidget* parent, QPoint pos): QLabel(parent)
{
    this->unPlacedBox = unPlacedBox;

    startPosition = pos;
    setGeometry(pos.x(), pos.y(), 30, 30);
    setStyleSheet("QLabel{border: 3px solid #0099ff; border-radius: 15px; }");
    setAlignment(Qt::AlignCenter);
}

void DragBox::mousePressEvent(QMouseEvent* event)
{
    offset = event->pos();
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void DragBox::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() == Qt::LeftButton)
        move(mapToParent(event->pos() - offset));
}

void DragBox::mouseReleaseEvent(QMouseEvent* event)
{
    lastPosition = mapToParent(event->pos());
    QApplication::restoreOverrideCursor();

    unPlacedBox->checkDrop(lastPosition);
}

void DragBox::enterEvent(QEvent*)
{
    setStyleSheet("QLabel{ background-color: #0099ff; border-radius: 15px;}");
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void DragBox::leaveEvent(QEvent*)
{
    setStyleSheet("QLabel{border: 3px solid #0099ff; border-radius: 15px; }");
    QApplication::restoreOverrideCursor();
}