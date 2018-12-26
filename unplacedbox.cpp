#include "unplacedbox.h"

#include "project.h"

UnPlacedBox::UnPlacedBox(Project* project, int id, QString text, QPoint pos): QLabel(project->getContainer())
{
    this->project = project;
    this->id = id;
    startPosition = pos;

    dragBox = new DragBox(, project->getContainer(), QPoint(pos.x() -40, pos.y()));
    delBox = new DelBox(, project->getContainer(), QPoint(pos.x() + 110, pos.y()));

    setGeometry(pos.x(), pos.y(), 110, 30);
    setStyleSheet("QLabel{border: 3px solid #0099ff; color: #FFFFFF; }");
    setText(text);
    setAlignment(Qt::AlignCenter);
}

UnPlacedBox::~UnPlacedBox()
{
    delete dragBox;
    delete delBox;
}

void UnPlacedBox::checkDrop(QPoint point)
{
    if(project->writeOnLcd(this))
    {
        setVisible(false);
        dragBox->setVisible(false);
        delBox->setVisible(false);
    }
    else
        dragBox->move()
}

void UnPlacedBox::remove()
{

}

