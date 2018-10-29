#include "unplacedbox.h"

#include "project.h"

UnPlacedBox::UnPlacedBox(Project* project, QWidget* parent, QString text) : QLabel (parent) //?is this needed?
{
    this->project = project;

    this->setText(text);
    this->setGeometry(0, 0, 100, 25);
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("UnPlacedBox{ background-color: red; border: 2px solid red; color: #FFFFFF; }");

    grabBox = new QLabel(parent);
    grabBox->setGeometry(0, 0, 20, 25);
    grabBox->setStyleSheet("QLabel{ background-color: green;");
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
         grabBox->move(mapToParent(event->pos() - offset));
     }
}

void UnPlacedBox::mouseReleaseEvent(QMouseEvent* event)
{
     //lastPosition = this->mapTo(this->parentWidget(), event->pos());
     lastPosition = grabBox->mapTo(this->parentWidget(), event->pos());

     QApplication::restoreOverrideCursor();

     project->writeOnLcd(this->text(), lastPosition);
}
