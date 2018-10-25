#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QLabel>
#include <QApplication>
#include <QMouseEvent>
#include <QPoint>

#include <QDebug>

class DraggableLabel : public QLabel
{
     Q_OBJECT

private:
    QPoint offset;

public:
   DraggableLabel(QWidget* parent = nullptr, QString string = "") : QLabel(parent)
   {
       this->setText(string);
       setAutoFillBackground(true);
       setAcceptDrops(true);
   }

protected:

   void mousePressEvent(QMouseEvent* event)
   {
        if(event->buttons() == Qt::LeftButton)
        {
            offset = event->pos();
            QApplication::setOverrideCursor(Qt::PointingHandCursor);
        }
   }

   void mouseMoveEvent(QMouseEvent* event)
   {
        if(event->buttons() == Qt::LeftButton)
            this->move(mapToParent(event->pos() - offset));
   }

   void mouseReleasEvent(QMouseEvent* event)
   {
        QApplication::setOverrideCursor(Qt::ArrowCursor);
   }

};

#endif // DRAGGABLELABEL_H
