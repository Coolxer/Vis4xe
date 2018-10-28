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
    QVector <MyLabel*> cells;
    QLabel * label;

    QPoint offset;
    QPoint lastPosition;

    QString text;

    unsigned short dropIndex;

    void setUpString()
    {
        if(dropIndex + text.length() <= cells.length())
        {
            for(int i = 0; i < text.length(); i++)
            {
                cells[dropIndex + i]->setText(text.at(i));
                cells[dropIndex + i]->setStyleSheet("MyLabel { border: 2px solid green; }");
            }

            this->deleteLater();
        }
    }

public:
    DraggableLabel(QWidget* parent, QString string, QVector <MyLabel*> xCells ) : QLabel(parent)
    {
       text = string;
       this->setText(text);
       cells = xCells;
       setAutoFillBackground(true);
       setAcceptDrops(true);

       label = new QLabel(parent);
       label->setGeometry(800, 100, 10, 30);
       label->setStyleSheet("QLabel { background-color: red; }");
       //label->show();
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

        setUpString();
   }



};

#endif // DRAGGABLELABEL_H
