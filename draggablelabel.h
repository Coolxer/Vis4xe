#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QLabel>
#include <QApplication>
#include <QMouseEvent>
#include <QPoint>

#include <QDebug>

#include <mylabel.h>

class DraggableLabel : public QLabel
{
     Q_OBJECT

private:
    QPoint offset;
    QPoint lastPosition;
    QVector <MyLabel*> cells;

    unsigned short dropIndex;

public:
    DraggableLabel(QWidget* parent, QString string, QVector <MyLabel*> xCells ) : QLabel(parent)
   {
       this->setText(string);
       cells = xCells;
       setAutoFillBackground(true);
       setAcceptDrops(true);
   }

    unsigned short getDroppedIndex() { return dropIndex; };

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

   void mouseReleaseEvent(QMouseEvent* event)
   {
        lastPosition = this->mapTo(this->parentWidget(), event->pos());

        QApplication::restoreOverrideCursor();

        for(int i = 0; i< cells.length(); i++)
        {
            if((lastPosition.x() >= cells[i]->geometry().x()) && (lastPosition.x() <= cells[i]->geometry().x() + cells[i]->geometry().width()))
            {
                if((lastPosition.y() >= cells[i]->geometry().y()) && (lastPosition.y() <= cells[i]->geometry().y() + cells[i]->geometry().height()))
                {
                    dropIndex = i;
                    break;
                }
            }
        }
   }

};

#endif // DRAGGABLELABEL_H
