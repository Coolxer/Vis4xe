#include "unplacedbox.h"

#include "project.h"

UnPlacedBox::UnPlacedBox(Project* project, int id, QString text, QPoint pos) : QLabel (project->getContainer())
{
    this->project = project;
    this->id = id;

    startPosition = pos;

    setGeometry(startPosition.x(), startPosition.y(), 30, 30);
    setStyleSheet("QLabel{border: 3px solid #0099ff; border-radius: 15px; }");
    setAlignment(Qt::AlignCenter);

    stringBox = new QLabel(project->getContainer());
    stringBox->setGeometry(startPosition.x() + 40, startPosition.y(), 110, 30);
    stringBox->setText(text);
    stringBox->setStyleSheet("QLabel{border: 3px solid #0099ff; color: #FFFFFF; }");
    stringBox->setAlignment(Qt::AlignCenter);
    stringBox->show();

    delBox = new QLabel(project->getContainer());
    delBox->setGeometry(startPosition.x() + 155, startPosition.y(), 30, 30);
    delBox->setStyleSheet("QLabel{border: 3px solid #FF0000 ; text-align: center; font-size: 25px; color: #FFFFFF; }");
    delBox->setText("X");
    delBox->setAlignment(Qt::AlignCenter);
    delBox->show();
}

UnPlacedBox::~UnPlacedBox()
{
    delete stringBox;
    delete delBox;
}

void UnPlacedBox::mousePressEvent(QMouseEvent* event)
{
    qDebug()<<"pressed";

    offset = event->pos();
    QApplication::setOverrideCursor(Qt::PointingHandCursor);

    if(event->buttons() == Qt::LeftButton)
    {
        if((event->pos().x() >= delBox->pos().x()) && (event->pos().x() <= delBox->pos().x() + 30))
        {
           if((event->pos().y() >= delBox->pos().y()) && (event->pos().y() <= delBox->pos().y() + 30))
           {
               project->getStringsWidget()->deleteStringWidget(id);

               setVisible(false);
               stringBox->setVisible(false);
               delBox->setVisible(false);

               deleteLater();
           }
        }
         /*
         else
         {
             offset = event->pos();
             QApplication::setOverrideCursor(Qt::PointingHandCursor);
         }
         */



         /*
         if(delBox->geometry().contains(event->pos()))
         {
             project->getStringsWidget()->deleteStringWidget(id);

             setVisible(false);
             stringBox->setVisible(false);
             delBox->setVisible(false);

             deleteLater();
         }
         */
     }
}

void UnPlacedBox::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() == Qt::LeftButton)
        move(mapToParent(event->pos() - offset));
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
        stringBox->setVisible(false);
        delBox->setVisible(false);

    }
    else
        move(startPosition);
}

void UnPlacedBox::enterEvent(QEvent*)
{
    setStyleSheet("QLabel{ background-color: #0099ff; border-radius: 15px;}");
    stringBox->setStyleSheet("QLabel{background-color: #0099ff; color: #FFFFFF; }");
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void UnPlacedBox::leaveEvent(QEvent*)
{
    setStyleSheet("QLabel{border: 3px solid #0099ff; border-radius: 15px; }");
    stringBox->setStyleSheet("QLabel{border: 3px solid #0099ff; color: #FFFFFF; }");
    QApplication::restoreOverrideCursor();
}

