#include "unplacedbox.h"

#include "project.h"

UnPlacedBox::UnPlacedBox(Project* project, int index, int id, QString text, QPoint pos): QLabel(project->getContainer())
{
    this->project = project;
    this->index = index;
    this->id = id;
    startPosition = pos;

    dragBox = new DragBox(this, QPoint(pos.x() - 35, pos.y()));
    delBox = new DelBox(this, QPoint(pos.x() + 115, pos.y()));

    setGeometry(pos.x(), pos.y(), 110, 30);
    setStyleSheet("QLabel{border: 3px solid #FFFFFF; color: #FFFFFF; }");
    setText(text);
    setAlignment(Qt::AlignCenter);


    project->setSaved(false);
}

UnPlacedBox::~UnPlacedBox()
{
    setVisible(false);

    dragBox->setVisible(false);
    delete dragBox;

    delBox->setVisible(false);
    delete delBox;
}

void UnPlacedBox::checkDrop(QPoint point)
{
    dragBoxPoint = point;

    if(!project->writeOnLcd(this))
        dragBox->reset();
}

void UnPlacedBox::remove()
{
    project->setSaved(false);
    project->getStringsList()->deleteString(index);
}

void UnPlacedBox::show(bool x)
{
    setVisible(x);
    dragBox->setVisible(x);
    delBox->setVisible(x);
}

void UnPlacedBox::reset()
{
    move(startPosition);
    dragBox->reset();
    delBox->reset();
    show(true);
}

void UnPlacedBox::moveTo(QPoint p)
{
    move(p);
    dragBox->move(p.x() - 35, p.y());
    delBox->move(p.x() + 115, p.y());

    startPosition = p;
    dragBox->setStartPosition(QPoint(p.x() - 35, p.y()));
}

