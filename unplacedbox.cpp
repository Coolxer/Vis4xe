#include "unplacedbox.h"

#include "project.h"

UnPlacedBox::UnPlacedBox(Project* project, QWidget* parent, int id, QString text, QPoint pos) : QLabel (parent) //?is this needed?
{
    this->project = project;
    this->id = id;
    startPosition = pos;

    setText(text);
    setGeometry(startPosition.x(), startPosition.y(), 100, 30);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QLabel{ background-color: #0099ff; color: #FFFFFF; }");

    //grabBox = new QLabel(parent);
    //grabBox->setGeometry(pos.x() - 5, pos.y(), 20, 30);
    //grabBox->setStyleSheet("QLabel{ background-color: red; }");
}

UnPlacedBox::~UnPlacedBox()
{
    delete project;
    delete grabBox;
}

void UnPlacedBox::mousePressEvent(QMouseEvent* event)
{
     if(event->buttons() == Qt::LeftButton)
     {
         offset = event->pos();
         QApplication::setOverrideCursor(Qt::PointingHandCursor);
     }
}

void UnPlacedBox::mouseMoveEvent(QMouseEvent* event)
{
     if(event->buttons() == Qt::LeftButton)
     {
         this->move(mapToParent(event->pos() - offset));
         //grabBox->move(mapToParent(event->pos() - offset));
     }
}

void UnPlacedBox::mouseReleaseEvent(QMouseEvent* event)
{
     lastPosition = this->mapToParent(event->pos());

     QApplication::restoreOverrideCursor();

     if(project->writeOnLcd(this))
     {
         //this->move(0, 0);
         //this->grabBox->move(0, 0);
         setVisible(false);
     }
     else
     {
         this->move(startPosition);
         //grabBox->move(startPosition.x() - 5, startPosition.y());
     }
}
