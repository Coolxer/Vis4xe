#include "unplacedbox.h"

#include "project.h"

UnPlacedBox::UnPlacedBox(Project* project, QWidget* listWidget, int id, QString text, QPoint pos) : QLabel (listWidget)
{
    this->project = project;
    this->listWidget = listWidget;
    this->id = id;

    startPosition = pos;

    setText(text);
    setGeometry(startPosition.x(), startPosition.y(), 110, 30);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QLabel{ background-color: #0099ff; color: #FFFFFF; }");

    delBox = new QLabel(listWidget);
    delBox->setGeometry(startPosition.x() + 110, startPosition.y(), 30, 30);
    delBox->setStyleSheet("QLabel{ background-color: #FF0000; text-align: center; font-size: 25px; }");
    delBox->setText("X");
    delBox->setAlignment(Qt::AlignCenter);
    delBox->show();
}

UnPlacedBox::~UnPlacedBox()
{
    delete delBox;
}

void UnPlacedBox::mousePressEvent(QMouseEvent* event)
{
     if(event->buttons() == Qt::LeftButton)
     {
         if((event->pos().x() >= delBox->pos().x()) && (event->pos().x() <= delBox->pos().x() + 30))
         {
            if((event->pos().y() >= delBox->pos().y()) && (event->pos().y() <= delBox->pos().y() + 30))
            {
                project->getStringsWidget()->deleteStringWidget(id);
                deleteLater();
            }
         }
         else
         {
             offset = event->pos();
             QApplication::setOverrideCursor(Qt::PointingHandCursor);
         }
     }
}

void UnPlacedBox::mouseMoveEvent(QMouseEvent* event)
{
     if(event->buttons() == Qt::LeftButton)
     {
         move(mapToParent(event->pos() - offset));
         delBox->move(mapToParent(QPoint(pos().x() + 110, pos().y())));

         QPoint point = pos();

         if(pos().x() < 0 && insideList == true)
         {
             setParent(project->getContainer());
             move(799, pos().y());
             show();

             insideList = false;
         }
     }
}

void UnPlacedBox::mouseReleaseEvent(QMouseEvent* event)
{

    lastPosition = mapToParent(event->pos());

    QApplication::restoreOverrideCursor();

    if(project->writeOnLcd(this))
    {
        //this->move(0, 0);
        //this->grabBox->move(0, 0);
        setVisible(false);
        delBox->setVisible(false);
    }
    else
    {
        setParent(listWidget);
        move(startPosition);
        delBox->move(startPosition.x() + 110, startPosition.y());
        show();
        insideList = true;
    }
}
