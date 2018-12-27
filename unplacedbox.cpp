#include "unplacedbox.h"

#include "project.h"

UnPlacedBox::UnPlacedBox(Project* project, int id, QString text, QPoint pos): QLabel(project->getContainer())
{
    this->project = project;
    this->id = id;
    startPosition = pos;

    dragBox = new DragBox(this, project->getContainer(), QPoint(pos.x() -40, pos.y()));
    delBox = new DelBox(this, project->getContainer(), QPoint(pos.x() + 110, pos.y()));

    setGeometry(pos.x(), pos.y(), 110, 30);
    setStyleSheet("QLabel{border: 3px solid #0099ff; color: #FFFFFF; }");
    setText(text);
    setAlignment(Qt::AlignCenter);
}

UnPlacedBox::~UnPlacedBox()
{
    setVisible(false);

    dragBox->setVisible(false);
    delete dragBox;

    delBox->setVisible(false);
    delete delBox;
}

bool UnPlacedBox::checkDrop(QPoint point)
{
    dragBoxPoint = point;

    if(project->writeOnLcd(this))
    {
        setVisible(false);
        dragBox->setVisible(false);
        delBox->setVisible(false);

        return true;
    }

    return false;
}

void UnPlacedBox::remove()
{
    setVisible(false);
    dragBox->setVisible(false);

}

